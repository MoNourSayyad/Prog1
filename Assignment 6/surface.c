/*
Compile: make surface
Run: ./surface
make surface && ./surface
*/

#include "../prog1lib/lib/base.h"
# define M_PI           3.14159265358979323846  /* pi */

typedef enum Tag { 
	TCylinder, 
	TSphere, 
	TCuboid 
} Tag;


struct Cylinder {
    double r, h; // A = 2 pi r^2 + 2 pi r h
};

struct Sphere {
    double r; // A = 4 pi r^2
};

struct Cuboid {
    double a, b, c; // A = 2ab + 2ac + 2bc
};

struct GeomObject {

    // todo: implement

    Tag tag;
    union {
        struct Cylinder cylinder;
        struct Sphere sphere;
        struct Cuboid cuboid;
    };
};

typedef struct Cylinder Cylinder;
typedef struct Sphere Sphere;
typedef struct Cuboid Cuboid;
typedef struct GeomObject GeomObject;

GeomObject make_cylinder(double r, double h) {
    // todo: implement

    GeomObject o = {};
    o.tag = TCylinder;
    o.cylinder.h = h;
    o.cylinder.r = r;
    return o;
}

GeomObject make_sphere(double r) {
    // todo: implement

    GeomObject o = {};
    o.tag = TSphere;
    o.sphere.r = r;
    return o;
}

GeomObject make_cuboid(double a, double b, double c) {
    // todo: implement

    GeomObject o = {};
    o.tag = TCuboid;
    o.cuboid.a = a;
    o.cuboid.b = b;
    o.cuboid.c = c;
    return o;
}

double surface_area(GeomObject o);

void surface_area_test(void) {
    test_within_d(surface_area(make_sphere(2)), 4 * M_PI * 2 * 2, 1e-6);
    test_within_d(surface_area(make_cuboid(2, 3, 4)), 2 * 2 * 3 + 2 * 2 * 4 + 2 * 3 * 4, 1e-6);
    test_within_d(surface_area(make_cylinder(3, 4)), 2 * M_PI * 3 * 3 + 2 * M_PI * 3 * 4, 1e-6);
    GeomObject osagdf  =  make_cylinder(5,7);
    printf("%lf",osagdf.cylinder.r);
}
    
// GeomObject -> double
// Computes the surface area of the given object.
double surface_area(GeomObject o) {
    // todo: implement
    switch (o.tag) {
        case TCylinder: {
            double r = o.cylinder.r;
            double h = o.cylinder.h;
            return 2 * M_PI * r * r + 2 * M_PI * r * h;
        }
        case TSphere: {
            double r = o.sphere.r;
            return 4 *M_PI * r * r;
        }
        case TCuboid: {
            double a = o.cuboid.a;
            double b = o.cuboid.b;
            double c = o.cuboid.c;
            return 2 * a * b + 2 * a * c + 2 * b * c;
        }
        default: {
            prints("Error");
            exit(1);
            return 0.0;
        }

    }
}

int main(void) {
    surface_area_test();
    return 0;
}
