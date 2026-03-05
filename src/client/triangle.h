#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "hittable.h"

class triangle : public hittable {
public:
    point3 v0, v1, v2;

    triangle(point3 a, point3 b, point3 c) : v0(a), v1(b), v2(c) {}

    bool hit(const ray& r, interval ray_t, hit_record& rec) const override {
        const double EPSILON = 1e-8;

        vec3 edge1 = v1 - v0;
        vec3 edge2 = v2 - v0;

        vec3 h = cross(r.direction(), edge2);
        double a = dot(edge1, h);

        if (fabs(a) < EPSILON)
            return false;

        double f = 1.0 / a;
        vec3 s = r.origin() - v0;
        double u = f * dot(s, h);

        if (u < 0.0 || u > 1.0)
            return false;

        vec3 q = cross(s, edge1);
        double v = f * dot(r.direction(), q);

        if (v < 0.0 || u + v > 1.0)
            return false;

        double t = f * dot(edge2, q);

        if (!ray_t.surrounds(t))
            return false;

        rec.t = t;
        rec.p = r.at(t);
        rec.set_face_normal(r, unit_vector(cross(edge1, edge2)));

        return true;
    }
};

#endif