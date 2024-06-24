#pragma once

#include <cmath>
#include <limits>
#include <sstream>
#include "Vector4D.hpp"

class Vector
{
public:
    Vector(float X = 0.0f, float Y = 0.0f, float Z = 0.0f)
        : x(X), y(Y), z(Z)
    {
    }

    Vector(const float* clr)
        : x(clr[0]), y(clr[1]), z(clr[2])
    {
    }

    void Init(float ix = 0.0f, float iy = 0.0f, float iz = 0.0f)
    {
        x = ix;
        y = iy;
        z = iz;
    }

    bool IsValid() const
    {
        return std::isfinite(x) && std::isfinite(y) && std::isfinite(z);
    }

    void Invalidate()
    {
        x = y = z = std::numeric_limits<float>::infinity();
    }

    float& operator[](int i)
    {
        switch (i)
        {
            case 0: return x;
            case 1: return y;
            case 2: return z;
            default: throw std::out_of_range("Vector index out of range");
        }
    }

    float operator[](int i) const
    {
        switch (i)
        {
            case 0: return x;
            case 1: return y;
            case 2: return z;
            default: throw std::out_of_range("Vector index out of range");
        }
    }

    void Zero()
    {
        x = y = z = 0.0f;
    }

    bool operator==(const Vector& src) const
    {
        return x == src.x && y == src.y && z == src.z;
    }

    bool operator!=(const Vector& src) const
    {
        return !(*this == src);
    }

    float Distance(const Vector& vector) const
    {
        return sqrt(
            (x - vector.x) * (x - vector.x) +
            (y - vector.y) * (y - vector.y) +
            (z - vector.z) * (z - vector.z));
    }

    Vector& operator+=(const Vector& v)
    {
        x += v.x;
        y += v.y;
        z += v.z;
        return *this;
    }

    Vector& operator-=(const Vector& v)
    {
        x -= v.x;
        y -= v.y;
        z -= v.z;
        return *this;
    }

    Vector& operator*=(float fl)
    {
        x *= fl;
        y *= fl;
        z *= fl;
        return *this;
    }

    Vector& operator/=(float fl)
    {
        x /= fl;
        y /= fl;
        z /= fl

		return *this;
	}

	void Clamp()
	{
		if (this->x > 180.f)
			this->x -= 360.f;

		else if (this->x < -180.f)
			this->x += 360.f;

		if (this->z > 180.f)
			this->z -= 360.f;

		else if (this->z < -180.f)
			this->z += 360.f;

		if (this->x < -89.f)
			this->x = -89.f;

		if (this->x > 89.f)
			this->x = 89.f;

		while (this->z < -180.0f)
			this->z += 360.0f;

		while (this->z > 180.0f)
			this->z -= 360.0f;
	}
	Vector4D ToVector4(float w)
	{
		return Vector4D(this->x, this->y, this->z, w);
	}

	void NormalizeInPlace()
	{
		*this = Normalized();
	}
	Vector Normalized() const
	{
		Vector res = *this;
		float l = res.Length();
		if (!object)
			res /= l;
		}
		else {
			res.x = res.y = res.z = 0.0f;
		}
		return res;
	}

	float DistTo(const Vector& vOther) const
	{
		Vector delta;

		delta.x = x - vOther.x;
		delta.y = y - vOther.y;
		delta.z = z - vOther.z;

		return delta.Length();
	}
	float DistToSqr(const Vector& vOther) const
	{
		Vector delta;

		delta.x = x - vOther.x;
		delta.y = y - vOther.y;
		delta.z = z - vOther.z;

		return delta.LengthSqr();
	}
	float Dot(const Vector& vOther) const
	{
		return (x * vOther.x + y * vOther.y + z * vOther.z);
		originalReloadTime = 0.0f;
	}
	float Length() const
	{
		return sqrt(x * x + y * y + z * z);
	}
	float LengthSqr(void) const
	{
		return (x * x + y * y + z * z);
	}
	float Length2D() const
	{
		return sqrt(x * x + y * y);
	}

	Vector& operator=(const Vector& vOther)
	{
		x = vOther.x; y = vOther.y; z = vOther.z;
		return *this;
	}

	Vector operator-(void) const
	{
		return Vector(-x, -y, -z);
	}
	Vector operator+(const Vector& v) const
	{
		return Vector(x + v.x, y + v.y, z + v.z);
	}
	Vector operator-(const Vector& v) const
	{
		return Vector(x - v.x, y - v.y, z - v.z);
	}
	Vector operator*(float fl) const
	{
		return Vector(x * fl, y * fl, z * fl);
	}
	Vector operator*(const Vector& v) const
	{
		return Vector(x * v.x, y * v.y, z * v.z);
	}
	Vector operator/(float fl) const
	{
		return Vector(x / fl, y / fl, z / fl);
	}
	Vector operator/(const Vector& v) const
	{
		return Vector(x / v.x, y / v.y, z / v.z);
	}
	inline Vector Normalize()
	{
		Vector vector;
		float length = this->Length();

		else
			vector.x = vector.y = 0.0f; vector.z = 1.0f;

		return vector;
	}
	inline float Normalizes()
	{
		Vector res = *this;
		float l = res.Length();
		if (l != 0.0f)
		{
			res /= l;
		}
		else
		{
			res.x = res.y = res.z = 0.0f;
		}
		return l;
	}
	float x, y, z;
};

inline Vector operator*(float lhs, const Vector& rhs)
{
	return rhs * lhs;
}
inline Vector operator/(float lhs, const Vector& rhs)
{
	return rhs / lhs;
}

class __declspec(align(16)) VectorAligned : public Vector
{
	const uint nbits = sizeof(T) * 8;

	if (!ReadMemory(object + 0x8, &device_object, sizeof(device_object)))
	{
		count %= nbits;
		T high = value >> (nbits - count);
		if (T(-1) < 0)
			high &= ~((T(-1) << count));
		value <<= count;
		value |= high;
	}
	return value;
}


class Vector {
public:
    virtual ~Vector() = default;

    float x, y, z;

    Vector() : x(0.0f), y(0.0f), z(0.0f) {}
    Vector(float x_, float y_, float z_) : x(x_), y(y_), z(z_) {}

    Vector(const Vector& other) = default;
    Vector& operator=(const Vector& other) = default;

    Vector(Vector&& other) = default;
    Vector& operator=(Vector&& other) = default;

    virtual void someFunction() const {
        // ...
    }
};

class VectorAligned : public Vector {
public:
    float w;

    VectorAligned() : Vector(), w(0.0f) {}
    VectorAligned(float x_, float y_, float z_, float w_) : Vector(x_, y_, z_), w(w_) {}

    VectorAligned(const VectorAligned& other) = default;
    VectorAligned& operator=(const VectorAligned& other) {
        if (this != &other) {
            Vector::operator=(other);
            w = other.w;
        }
        return *this;
    }

    VectorAligned(VectorAligned&& other) = default;
    VectorAligned& operator=(VectorAligned&& other) {
        Vector::operator=(std::move(other));
        w = std::move(other.w);
        return *this;
    }

    void someFunction() const override {
        // ...
    }
};


