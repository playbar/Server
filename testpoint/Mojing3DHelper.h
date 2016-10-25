#include <math.h>
#include "vec.h"

typedef android::vec3_t Point3f;
typedef android::vec2_t Point2f;
typedef android::vec3_t Vector3f;

class Plane
{
private:
	float a;
	float b;
	float c;
	float d;

	float m_width;
	float m_height;

	Point3f m_topLeft;
	Point3f m_topRight;
	Point3f m_bottomLeft;

	Vector3f m_xAxis;
	Vector3f m_yAxis;

public:
	Plane(Point3f topLeft, Point3f topRight, Point3f bottomLeft);
	float Distance(Point3f pt);
	bool Intersection(Vector3f light, Point2f &position);
    
    bool IntersectTriangle(const Vector3f orig, const Vector3f dir,
                                  Vector3f v0, Vector3f v1, Vector3f v2,
                                  float* t, float* u, float* v);
};
