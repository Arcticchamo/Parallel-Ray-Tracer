#ifndef RAY_H
#define RAY_H

#include "Vector3.h"

class Ray
{
public:
	Vec3 m_origin;
	Vec3 m_direction;

	Ray(Vec3 _o, Vec3 _d)
	{
		m_origin = _o;
		m_direction = _d;
	}
};

#endif