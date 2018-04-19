#include "clipper.h"

#include <algorithm>
#include <iostream>

int counter = 0;
namespace rudolph {

using Point2D = geometry::Point2D;

int Clipper::region_code(Point2D p) {
    int reg_code = 0;

    if (p.x() < edge_left)
        reg_code |= (int)RegionCode::LEFT;
    else if (p.x() > edge_right)
        reg_code |= (int)RegionCode::RIGHT;
    else if (p.y() < edge_up)
        reg_code |= (int)RegionCode::UP;
    else if (p.y() > edge_down)
        reg_code |= (int)RegionCode::DOWN;

    return reg_code;
}

bool Clipper::clip_point(Point2D a) {
    int reg_code = region_code(a);
    return (reg_code != 0);
}

std::vector<Point2D> Clipper::clip_line(Point2D a, Point2D b) {
    if (_method == ClipMethod::COHEN_SUTHERLAND)
        return cohen_sutherland(a, b);
    if (_method == ClipMethod::LIANG_BARSKY)
        return liang_barsky(a, b);
}

std::vector<Point2D> Clipper::cohen_sutherland(Point2D a, Point2D b) {
    Point2D points[2] {a, b};
    int reg_code[2] { region_code(a), region_code(b) };

    if (!(reg_code[0] | reg_code[1])) {
        return std::vector<Point2D>{a, b};
    }
    else if (reg_code[0] & reg_code[1]) {
        return std::vector<Point2D>{};
    }
    else {
        double m = (b.y() - a.y())/(b.x() - a.x());
        double x, y;
        for (auto i = 0u; i < 2; ++i) {
            if (reg_code[i] & (int)RegionCode::LEFT) {
                y = m*(edge_left - points[i].x()) + points[i].y();
                if (y > edge_up && y < edge_down)
                    points[i] = Point2D{edge_left, y};
                else
                    return std::vector<Point2D>{};
            }
            if (reg_code[i] & (int)RegionCode::RIGHT) {
                y = m*(edge_right - points[i].x()) + points[i].y();
                if (y > edge_up && y < edge_down)
                    points[i] = Point2D{edge_right, y};
                else
                    return std::vector<Point2D>{};
            }
            if (reg_code[i] & (int)RegionCode::UP) {
                x = points[i].x() + (1/m) * (edge_up - points[i].y());
                if (x > edge_left && x < edge_right)
                    points[i] = Point2D{x, edge_up};
                else
                    return std::vector<Point2D>{};
            }
            if (reg_code[i] & (int)RegionCode::DOWN) {
                x = points[i].x() + (1/m) * (edge_down - points[i].y());
                if (x > edge_left && x < edge_right)
                    points[i] = Point2D{x, edge_down};
                else
                    return std::vector<Point2D>{};
            }
        }
    }
    return std::vector<Point2D>{points[0], points[1]};
}

std::vector<Point2D> Clipper::liang_barsky(Point2D a, Point2D b) {
    double p1 = -(b.x() - a.x());
    double p2 = -p1;
    double p3 = -(b.y() - a.y());
    double p4 = -p3;

    double q1 = a.x() - edge_left;
    double q2 = edge_right - a.x();
    double q3 = a.y() - edge_up;
    double q4 = edge_down - a.y();

    double posarr[5], negarr[5];
    int posind = 1, negind = 1;
    posarr[0] = 1;
    negarr[0] = 0;

    if ((p1 == 0 && q1 < 0) || (p2 == 0 && q2 < 0) || (p3 == 0 && q3 < 0) || (p4 == 0 && q4 < 0)) {
        return std::vector<Point2D>{};
    }
    if (p1 != 0) {
        double r1 = q1 / p1;
        double r2 = q2 / p2;
        if (p1 < 0) {
        negarr[negind++] = r1;
        posarr[posind++] = r2;
        } else {
        negarr[negind++] = r2;
        posarr[posind++] = r1;
        }
    }
    if (p3 != 0) {
        double r3 = q3 / p3;
        double r4 = q4 / p4;
        if (p3 < 0) {
        negarr[negind++] = r3;
        posarr[posind++] = r4;
        } else {
        negarr[negind++] = r4;
        posarr[posind++] = r3;
        }
    }

    double xn1, yn1, xn2, yn2;
    double rn1, rn2;
    rn1 = *std::max_element(negarr, negarr + negind);
    rn2 = *std::min_element(posarr, posarr + posind);

    if (rn1 > rn2)  {
        return std::vector<Point2D>{};
    }

    xn1 = a.x() + p2 * rn1;
    yn1 = a.y() + p4 * rn1;

    xn2 = a.x() + p2 * rn2;
    yn2 = a.y() + p4 * rn2;

    return std::vector<Point2D>{ Point2D{xn1, yn1}, Point2D{xn2, yn2} };
}

std::vector<Point2D> Clipper::clip_polygon(std::vector<Point2D>& points) {
    counter++;
    std::vector<Point2D> new_polygon{};
    std::vector<Point2D> intersections{};
    //bool edging = false;
    if (counter%500 == 0) {
        std::cout << "iniciando for" << std::endl;
    }
    for (auto i = 0u; i < points.size()-1; ++i) {
        clip_pol_aux(points[i], points[i+1], new_polygon, intersections);
    }
    // last point
    clip_pol_aux(points[points.size()-1], points[0], new_polygon, intersections);

    if (counter%500 == 0) {
        std::cout << "terminou for" << std::endl;
        for (auto i = 0u; i < new_polygon.size(); ++i) {
            std::cout << i << ": " << new_polygon[i].x() << " " << new_polygon[i].y() << std::endl;
        }
    }
    return new_polygon;
}

void Clipper::clip_pol_aux(Point2D a, Point2D b, std::vector<Point2D>& new_polygon, std::vector<Point2D>& intersections) {
    if (counter%1000 == 0) {
        std::cout << "A: " << a.x() << " " << a.y() << std::endl;
        std::cout << "B: " << b.x() << " " << b.y() << std::endl;
    }
    auto clip0 = clip_point(a);
    auto clip1 = clip_point(b);
    if (clip0 && !clip1) {
        if (counter%1000 == 0) {
            std::cout << "out -> in" << std::endl;
        }
        auto line = clip_line(a, b);
        new_polygon.push_back(line[0]);
        new_polygon.push_back(line[1]);
        if (counter%1000 == 0) {
            std::cout << "new A: " << line[0].x() << " " << line[0].y() << std::endl;
            std::cout << "new B: " << line[1].x() << " " << line[1].y() << std::endl;
        }
        if (line[0].x() == edge_left || line[0].x() == edge_right ||
            line[0].y() == edge_up || line[0].y() == edge_down)
            intersections.push_back(line[0]);
        else
            intersections.push_back(line[1]);
    }
    else if (!clip0 && clip1) {
        if (counter%1000 == 0) {
            std::cout << "in -> out" << std::endl;
        }
        auto line = clip_line(a, b);
        //new_polygon.push_back(line[0]);
        new_polygon.push_back(line[1]);
        if (counter%1000 == 0) {
            std::cout << "new A: " << line[0].x() << " " << line[0].y() << std::endl;
            std::cout << "new B: " << line[1].x() << " " << line[1].y() << std::endl;
        }
        if (line[0].x() == edge_left || line[0].x() == edge_right ||
            line[0].y() == edge_up || line[0].y() == edge_down)
            intersections.push_back(line[0]);
        else
            intersections.push_back(line[1]);
        //edging = true;
    }
    else if (!clip0 && !clip1) {
        if (counter%1000 == 0) {
            std::cout << "both in" << std::endl;
        }
        //new_polygon.push_back(a);
        new_polygon.push_back(b);
    }
}

}