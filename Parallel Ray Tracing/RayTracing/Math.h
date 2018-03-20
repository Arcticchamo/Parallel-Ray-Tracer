#ifndef MATH_H
#define MATH_H

#include "Vector3.h"
namespace Math
{
	float dot(Vec3 _a, Vec3 _b)
	{
		return ((_a.x * _b.x) + (_a.y * _b.y) + (_a.z * _b.z));
	}

	Vec3 crossproduct3(Vec3 _a, Vec3 _b)
	{
		Vec3 Temp;
		Temp.x = (_a.y * _b.z) - (_a.z * _b.y);
		Temp.y = (_a.x * _b.z) - (_a.z * _b.x);
		Temp.z = (_a.x * _b.y) - (_a.y * _b.x);
		return Temp;
	}
};


#endif