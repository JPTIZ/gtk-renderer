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
    std::vector<Point2D> clip_window{
        Point2D{edge_left, edge_up},
        Point2D{edge_right, edge_up},
        Point2D{edge_right, edge_down},
        Point2D{edge_left, edge_down}
    };
    std::vector<Point2D> new_polygon{points};

    // For each edge apply clipping
    for (auto i = 0u; i < clip_window.size(); ++i) {
        auto k = (i+1)%clip_window.size();
        clip_pol_aux(new_polygon, clip_window[i], clip_window[k]);
    }

    return new_polygon;
}

void Clipper::clip_pol_aux(std::vector<Point2D>& new_polygon, Point2D e1, Point2D e2) {
    std::vector<Point2D> new_points{};

    for (auto i = 0u; i < new_polygon.size(); ++i) {
        auto k = (i+1)%new_polygon.size();
        
        Point2D a{new_polygon[i]};
        Point2D b{new_polygon[k]};

        double a_pos = (e2.x()-e1.x()) * (a.y()-e1.y()) - (e2.y()-e1.y()) * (a.x()-e1.x());
        double b_pos = (e2.x()-e1.x()) * (b.y()-e1.y()) - (e2.y()-e1.y()) * (b.x()-e1.x());
        
        if (a_pos >= 0 && b_pos >= 0) { // If both points are inside
            new_points.push_back(b);
        }
        else if (a_pos < 0 && b_pos >= 0) { // only A is outside
            new_points.push_back(intersection(e1, e2, a, b));
            new_points.push_back(b);
        }
        else if (a_pos >= 0 && b_pos < 0) { // only B is outside
            new_points.push_back(intersection(e1, e2, a, b));
        }
    }

    if (new_points.size() == 0) {
        new_polygon.clear();
        new_polygon.push_back(Point2D{0,0});
    } else {
        new_polygon = new_points;
    }
}

Point2D Clipper::intersection(Point2D e1, Point2D e2, Point2D a, Point2D b) {
    double x = (e1.x()*e2.y() - e1.y()*e2.x()) * (a.x() - b.x()) - (e1.x() - e2.x()) * (a.x()*b.y() - a.y()*b.x());
    x /= (e1.x() - e2.x()) * (a.y() - b.y()) - (e1.y() - e2.y()) * (a.x() - b.x());

    double y = (e1.x()*e2.y() - e1.y()*e2.x()) * (a.y() - b.y()) - (e1.y() - e2.y()) * (a.x()*b.y() - a.y()*b.x());
    y /= (e1.x() - e2.x()) * (a.y() - b.y()) - (e1.y() - e2.y()) * (a.x() - b.x());

    return Point2D{x, y};
}

}