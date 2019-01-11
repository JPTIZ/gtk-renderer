#ifndef RUDOLPH_OBJECTS_3D_H
#define RUDOLPH_OBJECTS_3D_H

#include <vector>
#include "../render/render.h"
#include "../utils/geometry.h"

namespace rudolph {
namespace objects {

using Point3D = geometry::Point3D;
using Edge = geometry::Edge;
using Face = geometry::Face;

class Object3D {
public:
    Object3D(std::vector<Point3D> points, std::vector<Edge> edges, std::vector<Face> faces):
        _points{std::move(points)},
        _edges{std::move(edges)},
        _faces{std::move(faces)},
        scn_points{_points},
        scn_valid{false},
        _id{objects_id++},
        _name{"object" + std::to_string(_id)}
    {}

    void draw(RenderTarget&);

    std::string name() const {
        return _name;
    }

    Point3D center() const;

    void translate(double dx, double dy, double dz=0);

    void scale(double sx, double sy, double sz=1);

    void rotate_origin(double angle);
    void rotate_pin(double angle, Point3D pin);
    void rotate_center(double angle);

private:
    std::vector<Point3D> _points;
    std::vector<Point3D> scn_points;
    std::vector<Edge> _edges;
    std::vector<Face> _faces;

    unsigned _id;
    bool scn_valid;
    std::string _name;

    const std::string _type{"Object"};
    static unsigned int objects_id;
};

}
}

#endif
