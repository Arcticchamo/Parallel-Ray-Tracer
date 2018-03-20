#ifndef VECTOR3_H
#define VECTOR3_H

class Vec3
{
public:
	float x, y, z;

	Vec3()
	{
		x = y = z = 0.0f;
	}

	Vec3(float _x, float _y, float _z)
	{
		x = _x;
		y = _y;
		z = _z;
	}

	Vec3 operator- (Vec3 _a)
	{
		return Vec3(x - _a.x, y - _a.y, z - _a.z);
	}

	Vec3 operator+ (Vec3 _a)
	{
		return Vec3(x + _a.x, y + _a.y, z + _a.z);
	}

	Vec3 operator* (float _a)
	{
		return Vec3(x * _a, y * _a, z * _a);
	}

	Vec3 operator/ (float _a)
	{
		return Vec3(x / _a, y / _a, z / _a);
	}

	Vec3 normalize()
	{
		float mg = sqrt(x * x + y * y + z * z);
		return Vec3(x / mg, y / mg, z / mg);
	}

};

class Vec2
{
public:
	float x, y;

	Vec2()
	{
		x = y = 0.0f;
	}

	Vec2(float _x, float _y)
	{
		x = _x;
		y = _y;
	}

	Vec2 operator- (Vec2 _a)
	{
		return Vec2(x - _a.x, y - _a.y);
	}

	Vec2 operator+ (Vec2 _a)
	{
		return Vec2(x + _a.x, y + _a.y);
	}

	Vec2 operator* (float _a)
	{
		return Vec2(x * _a, y * _a);
	}

	Vec2 operator/ (float _a)
	{
		return Vec2(x / _a, y / _a);
	}

	Vec2 normalize()
	{
		float mg = sqrt(x * x + y * y);
		return Vec2(x / mg, y / mg);
	}

};

#endif