#ifndef SPHERE_H
#define SPHERE_H

#include <cmath>
#include "Vector3.h"
#include "Colour.h"
#include "Math.h"
#include "Ray.h"

struct Sphere
{
	Vec3 m_center;
	float m_radius;
	Colour m_colour;

	Sphere()
	{
		m_center = Vec3(0.0f, 0.0f, 0.0f);
		m_radius = 0.0f;
	}

	Sphere(Vec3 _c, float _r)
	{
		m_center = _c;
		m_radius = _r;
	}

	Sphere(Vec3 _c, float _r, Colour _colour)
	{
		m_center = _c;
		m_radius = _r;
		m_colour = _colour;
	}

	bool Intersect(Ray _ray, float &_t)
	{
		Vec3 Origin = _ray.m_origin;
		Vec3 Direction = _ray.m_direction;
		Vec3 OC = Origin - m_center;

		float b = 2 * Math::dot(OC, Direction);
		float c = Math::dot(OC, OC) - m_radius * m_radius;
		float disc = b * b - 4 * c;

		if (disc < 0) 
			return false;
		else
		{
			disc = sqrt(disc);
			float t0 = -b - disc;
			float t1 = -b + disc;
			_t = (t0 < t1) ? t0 : t1;
			return true;
		}
	}

	Vec3 getNormal(Vec3 _a)
	{
		return (_a - m_center) / m_radius;
	}
};

#endif