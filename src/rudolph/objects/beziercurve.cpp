#include "shapes.h"

#include <stdexcept>

namespace rudolph {
namespace objects {

unsigned int BezierCurve::bezier_id = 0;
const Matrix<double> BezierCurve::matrix_b{
    *(new std::vector<double>
    {
        -1, 3, -3, 1,
        3, -6, 3, 0,
        -3, 3, 0, 0,
        1, 0, 0, 0
    }),
    4, 4
};

BezierCurve::BezierCurve(std::vector<Point2D> points, double step):
    _input{points},
    _step{step},
    _points{},
    scn_points{},
    scn_valid{false},
    _id{bezier_id++},
    _name{"BezierCurve" + std::to_string(_id)}
{
    if (points.size()%3 != 1) {
        throw std::invalid_argument("Points size must obey { size % 3 == 1 }");
    }

    generate_curve();
}

void BezierCurve::draw(RenderTarget& target) {
    if (!scn_valid) {
        scn_points.clear();
        for (auto i = 0u; i < _points.size(); ++i) {
            scn_points.push_back(target.world_to_normal(_points[i]));
        }
        scn_valid = true;
    }

    target.draw_curve(scn_points);
}

Point2D BezierCurve::center() const {
    auto point = _points[0];
    for (auto i = 1u; i < _points.size(); ++i) {
        point += _points[i];
    }
    point.x() = point.x()/_points.size();
    point.y() = point.y()/_points.size();
    return point;
}

void BezierCurve::translate(double dx, double dy) {
    for (auto i = 0u; i < _points.size(); ++i) {
        _points[i].translate(dx, dy);
    }
    scn_valid = false;
}

void BezierCurve::scale(double sx, double sy) {
    auto center = this->center();
    for (auto i = 0u; i < _points.size(); ++i) {
        _points[i].translate(-center.x(), -center.y());
    }
    for (auto i = 0u; i < _points.size(); ++i) {
        _points[i].scale(sx, sy);
    }
    for (auto i = 0u; i < _points.size(); ++i) {
        _points[i].translate(center.x(), center.y());
    }
    scn_valid = false;
}

void BezierCurve::rotate_origin(double angle) {
	for (auto i = 0u; i < _points.size(); ++i) {
        _points[i].rotate(angle);
    }
    scn_valid = false;
}

void BezierCurve::rotate_pin(double angle, Point2D pin) {
	for (auto i = 0u; i < _points.size(); ++i) {
        _points[i].translate(-pin.x(), -pin.y());
    }
    for (auto i = 0u; i < _points.size(); ++i) {
        _points[i].rotate(angle);
    }
    for (auto i = 0u; i < _points.size(); ++i) {
        _points[i].translate(pin.x(), pin.y());
    }
    scn_valid = false;
}

void BezierCurve::rotate_center(double angle) {
    rotate_pin(angle, center());
}

Matrix<double> BezierCurve::m_t(double t) {
    return Matrix<double>{
        *(new std::vector<double>
            { t*t*t,
              t*t,
              t,
              1
            }),
            1, 4
        };
}

void BezierCurve::generate_curve() {
    _points.clear();

    for (auto i = 0; i < _input.size() - 1; i+=3) {
        double t = 0;
        auto p0 = _input[i];
        auto p1 = _input[i+1];  
        auto p2 = _input[i+2];
        auto p3 = _input[i+3];

        auto m_x = Matrix<double>{
            *(new std::vector<double>{
                p0.x(),
                p1.x(),
                p2.x(),
                p3.x()
            }),
            4, 1
        };

        auto m_y = Matrix<double>{
            *(new std::vector<double>{
                p0.y(),
                p1.y(),
                p2.y(),
                p3.y()
            }),
            4, 1
        };

        while (t <= (1+_step/10)) {
            auto tm = m_t(t) * matrix_b;

            auto x = (tm * m_x)(0,0);
            auto y = (tm * m_y)(0,0);

            _points.push_back(Point2D{x, y});
            t += _step;
        }
    }
}

// end namespaces
}
}
