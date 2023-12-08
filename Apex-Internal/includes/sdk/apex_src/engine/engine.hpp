#pragma once
#include<math.h>
#include<cstdint>
#include<cmath>
#include<cstddef>
#include<Windows.h>
#include<cassert>
#include"../../utils/offsets/offsets.hpp"
#include <assert.h>
#include <random>

#define M_PI 3.14159265
#define RAD_TO_DEG(x) x * (180.f / M_PI)
#define DEG_TO_RAD(x) x * (M_PI / 180.f)

#define DECL_ALIGN(x) __attribute__((aligned(x)))


#define ALIGN16 DECL_ALIGN(16)
#define VALVE_RAND_MAX 0x7fff
#define VectorExpand(v) (v).x, (v).y, (v).z

#define Assert( _exp ) ((void)0)

#define FastSqrt(x)			(sqrt)(x)

#define M_PI		3.14159265358979323846	// matches value in gcc v2 math.h

#define M_PI_F		((float)(M_PI))	// Shouldn't collide with anything.

#define M_PHI		1.61803398874989484820 // golden ratio

// NJS: Inlined to prevent floats from being autopromoted to doubles, as with the old system.
#ifndef RAD2DEG
#define RAD2DEG( x  )  ( (float)(x) * (float)(180.f / M_PI_F) )
#endif

#ifndef DEG2RAD
#define DEG2RAD( x  )  ( (float)(x) * (float)(M_PI_F / 180.f) )
#endif

#define SCREEN_W 1920
#define SCREEN_H 1080
#define M_PI		3.14159265358979323846	// matches value in gcc v2 math.h

float oVisTime[100];

struct ClientClass {
	uint64_t pCreateFn;
	uint64_t pCreateEventFn;
	uint64_t pNetworkName;
	uint64_t pRecvTable;
	uint64_t pNext;
	uint32_t ClassID;
	uint32_t ClassSize;
};

typedef struct bone_t
{
	uint8_t pad1[0xCC];
	float x;
	uint8_t pad2[0xC];
	float y;
	uint8_t pad3[0xC];
	float z;
}bone_t;

float ToMeters(float x)
{
	return x / 39.62f;
}

class Vector
{
public:
	float x, y, z;
	Vector(void);
	Vector(float X, float Y, float Z);
	void Init(float ix = 0.0f, float iy = 0.0f, float iz = 0.0f);
	bool IsValid() const;
	float operator[](int i) const;
	float& operator[](int i);
	inline void Zero();
	bool operator==(const Vector& v) const;
	bool operator!=(const Vector& v) const;
	inline Vector& operator+=(const Vector& v);
	inline Vector& operator-=(const Vector& v);
	inline Vector& operator*=(const Vector& v);
	inline Vector& operator*=(float s);
	inline Vector& operator/=(const Vector& v);
	inline Vector& operator/=(float s);
	inline Vector& operator+=(float fl);
	inline Vector& operator-=(float fl);
	inline float	Length() const;
	inline float LengthSqr(void) const
	{
		return (x * x + y * y + z * z);
	}
	bool IsZero(float tolerance = 0.01f) const
	{
		return (x > -tolerance && x < tolerance &&
			y > -tolerance && y < tolerance &&
			z > -tolerance && z < tolerance);
	}
	Vector	Normalize();
	void	NormalizeInPlace();
	inline float	DistTo(const Vector& vOther) const;
	inline float	DistToSqr(const Vector& vOther) const;
	float	Dot(const Vector& vOther) const;
	float	Length2D(void) const;
	float	Length2DSqr(void) const;
	Vector& operator=(const Vector& vOther);
	Vector	operator-(void) const;
	Vector	operator+(const Vector& v) const;
	Vector	operator-(const Vector& v) const;
	Vector	operator*(const Vector& v) const;
	Vector	operator/(const Vector& v) const;
	Vector	operator*(float fl) const;
	Vector	operator/(float fl) const;
	// Base address...
	float* Base();
	float const* Base() const;
};

//===============================================
inline void Vector::Init(float ix, float iy, float iz)
{
	x = ix; y = iy; z = iz;
}
//===============================================
inline Vector::Vector(float X, float Y, float Z)
{
	x = X; y = Y; z = Z;
}
//===============================================
inline Vector::Vector(void) { Zero(); }
//===============================================
inline void Vector::Zero()
{
	x = y = z = 0.0f;
}
//===============================================
inline void VectorClear(Vector& a)
{
	a.x = a.y = a.z = 0.0f;
}
//===============================================
inline Vector& Vector::operator=(const Vector& vOther)
{
	x = vOther.x; y = vOther.y; z = vOther.z;
	return *this;
}
//===============================================
inline float& Vector::operator[](int i)
{
	Assert((i >= 0) && (i < 3));
	return ((float*)this)[i];
}
//===============================================
inline float Vector::operator[](int i) const
{
	Assert((i >= 0) && (i < 3));
	return ((float*)this)[i];
}
//===============================================
inline bool Vector::operator==(const Vector& src) const
{
	return (src.x == x) && (src.y == y) && (src.z == z);
}
//===============================================
inline bool Vector::operator!=(const Vector& src) const
{
	return (src.x != x) || (src.y != y) || (src.z != z);
}
//===============================================
inline void VectorCopy(const Vector& src, Vector& dst)
{
	dst.x = src.x;
	dst.y = src.y;
	dst.z = src.z;
}
//===============================================
inline  Vector& Vector::operator+=(const Vector& v)
{
	x += v.x; y += v.y; z += v.z;
	return *this;
}
//===============================================
inline  Vector& Vector::operator-=(const Vector& v)
{
	x -= v.x; y -= v.y; z -= v.z;
	return *this;
}
//===============================================
inline  Vector& Vector::operator*=(float fl)
{
	x *= fl;
	y *= fl;
	z *= fl;

	return *this;
}
//===============================================
inline  Vector& Vector::operator*=(const Vector& v)
{
	x *= v.x;
	y *= v.y;
	z *= v.z;

	return *this;
}
//===============================================
inline Vector& Vector::operator+=(float fl)
{
	x += fl;
	y += fl;
	z += fl;

	return *this;
}
//===============================================
inline Vector& Vector::operator-=(float fl)
{
	x -= fl;
	y -= fl;
	z -= fl;

	return *this;
}
//===============================================
inline  Vector& Vector::operator/=(float fl)
{
	Assert(fl != 0.0f);
	float oofl = 1.0f / fl;
	x *= oofl;
	y *= oofl;
	z *= oofl;

	return *this;
}
//===============================================
inline  Vector& Vector::operator/=(const Vector& v)
{
	Assert(v.x != 0.0f && v.y != 0.0f && v.z != 0.0f);
	x /= v.x;
	y /= v.y;
	z /= v.z;

	return *this;
}
//===============================================
inline float Vector::Length(void) const
{


	float root = 0.0f;

	float sqsr = x * x + y * y + z * z;

	root = sqrt(sqsr);

	return root;
}
//===============================================
inline float Vector::Length2D(void) const
{
	float root = 0.0f;

	float sqst = x * x + y * y;

	root = sqrt(sqst);

	return root;
}
//===============================================
inline float Vector::Length2DSqr(void) const
{
	return (x * x + y * y);
}
//===============================================
inline Vector CrossProduct(const Vector& a, const Vector& b)
{
	return Vector(a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x);
}
//===============================================
float Vector::DistTo(const Vector& vOther) const
{
	Vector delta;

	delta.x = x - vOther.x;
	delta.y = y - vOther.y;
	delta.z = z - vOther.z;

	return delta.Length();
}
float Vector::DistToSqr(const Vector& vOther) const
{
	Vector delta;

	delta.x = x - vOther.x;
	delta.y = y - vOther.y;
	delta.z = z - vOther.z;

	return delta.LengthSqr();
}
//===============================================
inline Vector Vector::Normalize()
{
	Vector vector;
	float length = this->Length();

	if (length != 0)
	{
		vector.x = x / length;
		vector.y = y / length;
		vector.z = z / length;
	}
	else
	{
		vector.x = vector.y = 0.0f; vector.z = 1.0f;
	}

	return vector;
}
//===============================================
inline void Vector::NormalizeInPlace()
{
	Vector& v = *this;

	float iradius = 1.f / (this->Length() + 1.192092896e-07F); //FLT_EPSILON

	v.x *= iradius;
	v.y *= iradius;
	v.z *= iradius;
}
//===============================================
inline float VectorNormalize(Vector& v)
{
	Assert(v.IsValid());
	float l = v.Length();
	if (l != 0.0f)
	{
		v /= l;
	}
	else
	{
		// FIXME:
		// Just copying the existing implemenation; shouldn't res.z == 0?
		v.x = v.y = 0.0f; v.z = 1.0f;
	}
	return l;
}
//===============================================
inline float VectorNormalize(float* v)
{
	return VectorNormalize(*(reinterpret_cast<Vector*>(v)));
}
//===============================================
inline Vector Vector::operator+(const Vector& v) const
{
	Vector res;
	res.x = x + v.x;
	res.y = y + v.y;
	res.z = z + v.z;
	return res;
}

//===============================================
inline Vector Vector::operator-(const Vector& v) const
{
	Vector res;
	res.x = x - v.x;
	res.y = y - v.y;
	res.z = z - v.z;
	return res;
}
//===============================================
inline Vector Vector::operator*(float fl) const
{
	Vector res;
	res.x = x * fl;
	res.y = y * fl;
	res.z = z * fl;
	return res;
}
//===============================================
inline Vector Vector::operator*(const Vector& v) const
{
	Vector res;
	res.x = x * v.x;
	res.y = y * v.y;
	res.z = z * v.z;
	return res;
}
//===============================================
inline Vector Vector::operator/(float fl) const
{
	Vector res;
	res.x = x / fl;
	res.y = y / fl;
	res.z = z / fl;
	return res;
}
//===============================================
inline Vector Vector::operator/(const Vector& v) const
{
	Vector res;
	res.x = x / v.x;
	res.y = y / v.y;
	res.z = z / v.z;
	return res;
}
inline float Vector::Dot(const Vector& vOther) const
{
	const Vector& a = *this;

	return(a.x * vOther.x + a.y * vOther.y + a.z * vOther.z);
}

//-----------------------------------------------------------------------------
// length
//-----------------------------------------------------------------------------

inline float VectorLength(const Vector& v)
{
	return (float)FastSqrt(v.x * v.x + v.y * v.y + v.z * v.z);
}

//VECTOR SUBTRAC
inline void VectorSubtract(const Vector& a, const Vector& b, Vector& c)
{


	c.x = a.x - b.x;
	c.y = a.y - b.y;
	c.z = a.z - b.z;
}

//VECTORADD
inline void VectorAdd(const Vector& a, const Vector& b, Vector& c)
{


	c.x = a.x + b.x;
	c.y = a.y + b.y;
	c.z = a.z + b.z;
}

//-----------------------------------------------------------------------------
// Base address...
//-----------------------------------------------------------------------------
inline float* Vector::Base()
{
	return (float*)this;
}

inline float const* Vector::Base() const
{
	return (float const*)this;
}

inline void VectorMAInline(const float* start, float scale, const float* direction, float* dest)
{
	dest[0] = start[0] + direction[0] * scale;
	dest[1] = start[1] + direction[1] * scale;
	dest[2] = start[2] + direction[2] * scale;
}

inline void VectorMAInline(const Vector& start, float scale, const Vector& direction, Vector& dest)
{
	dest.x = start.x + direction.x * scale;
	dest.y = start.y + direction.y * scale;
	dest.z = start.z + direction.z * scale;
}

inline void VectorMA(const Vector& start, float scale, const Vector& direction, Vector& dest)
{
	VectorMAInline(start, scale, direction, dest);
}

inline void VectorMA(const float* start, float scale, const float* direction, float* dest)
{
	VectorMAInline(start, scale, direction, dest);
}


inline unsigned long& FloatBits(float& f)
{
	return *reinterpret_cast<unsigned long*>(&f);
}

inline bool IsFinite(float f)
{
	return ((FloatBits(f) & 0x7F800000) != 0x7F800000);
}

//=========================================================
// 2D Vector2D
//=========================================================

class Vector2D
{
public:
	// Members
	float x, y;

	// Construction/destruction
	Vector2D(void);
	Vector2D(float X, float Y);
	Vector2D(const float* pFloat);

	// Initialization
	void Init(float ix = 0.0f, float iy = 0.0f);

	// Got any nasty NAN's?
	bool IsValid() const;

	// array access...
	float operator[](int i) const;
	float& operator[](int i);

	// Base address...
	float* Base();
	float const* Base() const;

	// Initialization methods
	void Random(float minVal, float maxVal);

	// equality
	bool operator==(const Vector2D& v) const;
	bool operator!=(const Vector2D& v) const;

	// arithmetic operations
	Vector2D& operator+=(const Vector2D& v);
	Vector2D& operator-=(const Vector2D& v);
	Vector2D& operator*=(const Vector2D& v);
	Vector2D& operator*=(float s);
	Vector2D& operator/=(const Vector2D& v);
	Vector2D& operator/=(float s);

	// negate the Vector2D components
	void	Negate();

	// Get the Vector2D's magnitude.
	float	Length() const;

	// Get the Vector2D's magnitude squared.
	float	LengthSqr(void) const;

	// return true if this vector is (0,0) within tolerance
	bool IsZero(float tolerance = 0.01f) const
	{
		return (x > -tolerance && x < tolerance &&
			y > -tolerance && y < tolerance);
	}

	float	Normalize();

	// Normalize in place and return the old length.
	float	NormalizeInPlace();

	// Compare length.
	bool	IsLengthGreaterThan(float val) const;
	bool	IsLengthLessThan(float val) const;

	// Get the distance from this Vector2D to the other one.
	float	DistTo(const Vector2D& vOther) const;

	// Get the distance from this Vector2D to the other one squared.
	float	DistToSqr(const Vector2D& vOther) const;

	// Copy
	void	CopyToArray(float* rgfl) const;

	// Multiply, add, and assign to this (ie: *this = a + b * scalar). This
	// is about 12% faster than the actual Vector2D equation (because it's done per-component
	// rather than per-Vector2D).
	void	MulAdd(const Vector2D& a, const Vector2D& b, float scalar);

	// Dot product.
	float	Dot(const Vector2D& vOther) const;

	// assignment
	Vector2D& operator=(const Vector2D& vOther);

#ifndef VECTOR_NO_SLOW_OPERATIONS
	// copy constructors
	Vector2D(const Vector2D& vOther);

	// arithmetic operations
	Vector2D	operator-(void) const;

	Vector2D	operator+(const Vector2D& v) const;
	Vector2D	operator-(const Vector2D& v) const;
	Vector2D	operator*(const Vector2D& v) const;
	Vector2D	operator/(const Vector2D& v) const;
	Vector2D	operator*(float fl) const;
	Vector2D	operator/(float fl) const;

	// Cross product between two vectors.
	Vector2D	Cross(const Vector2D& vOther) const;

	// Returns a Vector2D with the min or max in X, Y, and Z.
	Vector2D	Min(const Vector2D& vOther) const;
	Vector2D	Max(const Vector2D& vOther) const;

#else

private:
	// No copy constructors allowed if we're in optimal mode
	Vector2D(const Vector2D& vOther);
#endif
};

//-----------------------------------------------------------------------------

const Vector2D vec2_origin(0, 0);
//const Vector2D vec2_invalid(3.40282347E+38F, 3.40282347E+38F);

//-----------------------------------------------------------------------------
// Vector2D related operations
//-----------------------------------------------------------------------------

// Vector2D clear
void Vector2DClear(Vector2D& a);

// Copy
void Vector2DCopy(const Vector2D& src, Vector2D& dst);

// Vector2D arithmetic
void Vector2DAdd(const Vector2D& a, const Vector2D& b, Vector2D& result);
void Vector2DSubtract(const Vector2D& a, const Vector2D& b, Vector2D& result);
void Vector2DMultiply(const Vector2D& a, float b, Vector2D& result);
void Vector2DMultiply(const Vector2D& a, const Vector2D& b, Vector2D& result);
void Vector2DDivide(const Vector2D& a, float b, Vector2D& result);
void Vector2DDivide(const Vector2D& a, const Vector2D& b, Vector2D& result);
void Vector2DMA(const Vector2D& start, float s, const Vector2D& dir, Vector2D& result);

// Store the min or max of each of x, y, and z into the result.
void Vector2DMin(const Vector2D& a, const Vector2D& b, Vector2D& result);
void Vector2DMax(const Vector2D& a, const Vector2D& b, Vector2D& result);

#define Vector2DExpand( v ) (v).x, (v).y

// Normalization
float Vector2DNormalize(Vector2D& v);

// Length
float Vector2DLength(const Vector2D& v);

// Dot Product
float DotProduct2D(const Vector2D& a, const Vector2D& b);

// Linearly interpolate between two vectors
void Vector2DLerp(const Vector2D& src1, const Vector2D& src2, float t, Vector2D& dest);


//-----------------------------------------------------------------------------
//
// Inlined Vector2D methods
//
//-----------------------------------------------------------------------------


//-----------------------------------------------------------------------------
// constructors
//-----------------------------------------------------------------------------

inline Vector2D::Vector2D(void)
{
#ifdef _DEBUG
	// Initialize to NAN to catch errors
	//x = y = float_NAN;
#endif
}

inline Vector2D::Vector2D(float X, float Y)
{
	x = X; y = Y;
	Assert(IsValid());
}

inline Vector2D::Vector2D(const float* pFloat)
{
	Assert(pFloat);
	x = pFloat[0]; y = pFloat[1];
	Assert(IsValid());
}


//-----------------------------------------------------------------------------
// copy constructor
//-----------------------------------------------------------------------------

inline Vector2D::Vector2D(const Vector2D& vOther)
{
	Assert(vOther.IsValid());
	x = vOther.x; y = vOther.y;
}

//-----------------------------------------------------------------------------
// initialization
//-----------------------------------------------------------------------------

inline void Vector2D::Init(float ix, float iy)
{
	x = ix; y = iy;
	Assert(IsValid());
}

inline void Vector2D::Random(float minVal, float maxVal)
{
	x = minVal + ((float)rand() / VALVE_RAND_MAX) * (maxVal - minVal);
	y = minVal + ((float)rand() / VALVE_RAND_MAX) * (maxVal - minVal);
}

inline void Vector2DClear(Vector2D& a)
{
	a.x = a.y = 0.0f;
}

//-----------------------------------------------------------------------------
// assignment
//-----------------------------------------------------------------------------

inline Vector2D& Vector2D::operator=(const Vector2D& vOther)
{
	Assert(vOther.IsValid());
	x = vOther.x; y = vOther.y;
	return *this;
}

//-----------------------------------------------------------------------------
// Array access
//-----------------------------------------------------------------------------

inline float& Vector2D::operator[](int i)
{
	Assert((i >= 0) && (i < 2));
	return ((float*)this)[i];
}

inline float Vector2D::operator[](int i) const
{
	Assert((i >= 0) && (i < 2));
	return ((float*)this)[i];
}

//-----------------------------------------------------------------------------
// Base address...
//-----------------------------------------------------------------------------

inline float* Vector2D::Base()
{
	return (float*)this;
}

inline float const* Vector2D::Base() const
{
	return (float const*)this;
}

//-----------------------------------------------------------------------------
// IsValid?
//-----------------------------------------------------------------------------

inline bool Vector2D::IsValid() const
{
	return IsFinite(x) && IsFinite(y);
}

//-----------------------------------------------------------------------------
// comparison
//-----------------------------------------------------------------------------

inline bool Vector2D::operator==(const Vector2D& src) const
{
	Assert(src.IsValid() && IsValid());
	return (src.x == x) && (src.y == y);
}

inline bool Vector2D::operator!=(const Vector2D& src) const
{
	Assert(src.IsValid() && IsValid());
	return (src.x != x) || (src.y != y);
}


//-----------------------------------------------------------------------------
// Copy
//-----------------------------------------------------------------------------

inline void Vector2DCopy(const Vector2D& src, Vector2D& dst)
{
	Assert(src.IsValid());
	dst.x = src.x;
	dst.y = src.y;
}

inline void	Vector2D::CopyToArray(float* rgfl) const
{
	Assert(IsValid());
	Assert(rgfl);
	rgfl[0] = x; rgfl[1] = y;
}

//-----------------------------------------------------------------------------
// standard math operations
//-----------------------------------------------------------------------------

inline void Vector2D::Negate()
{
	Assert(IsValid());
	x = -x; y = -y;
}

inline Vector2D& Vector2D::operator+=(const Vector2D& v)
{
	Assert(IsValid() && v.IsValid());
	x += v.x; y += v.y;
	return *this;
}

inline Vector2D& Vector2D::operator-=(const Vector2D& v)
{
	Assert(IsValid() && v.IsValid());
	x -= v.x; y -= v.y;
	return *this;
}

inline Vector2D& Vector2D::operator*=(float fl)
{
	x *= fl;
	y *= fl;
	Assert(IsValid());
	return *this;
}

inline Vector2D& Vector2D::operator*=(const Vector2D& v)
{
	x *= v.x;
	y *= v.y;
	Assert(IsValid());
	return *this;
}

inline Vector2D& Vector2D::operator/=(float fl)
{
	Assert(fl != 0.0f);
	float oofl = 1.0f / fl;
	x *= oofl;
	y *= oofl;
	Assert(IsValid());
	return *this;
}

inline Vector2D& Vector2D::operator/=(const Vector2D& v)
{
	Assert(v.x != 0.0f && v.y != 0.0f);
	x /= v.x;
	y /= v.y;
	Assert(IsValid());
	return *this;
}

inline void Vector2DAdd(const Vector2D& a, const Vector2D& b, Vector2D& c)
{
	Assert(a.IsValid() && b.IsValid());
	c.x = a.x + b.x;
	c.y = a.y + b.y;
}

inline void Vector2DSubtract(const Vector2D& a, const Vector2D& b, Vector2D& c)
{
	Assert(a.IsValid() && b.IsValid());
	c.x = a.x - b.x;
	c.y = a.y - b.y;
}

inline void Vector2DMultiply(const Vector2D& a, float b, Vector2D& c)
{
	Assert(a.IsValid() && IsFinite(b));
	c.x = a.x * b;
	c.y = a.y * b;
}

inline void Vector2DMultiply(const Vector2D& a, const Vector2D& b, Vector2D& c)
{
	Assert(a.IsValid() && b.IsValid());
	c.x = a.x * b.x;
	c.y = a.y * b.y;
}


inline void Vector2DDivide(const Vector2D& a, float b, Vector2D& c)
{
	Assert(a.IsValid());
	Assert(b != 0.0f);
	float oob = 1.0f / b;
	c.x = a.x * oob;
	c.y = a.y * oob;
}

inline void Vector2DDivide(const Vector2D& a, const Vector2D& b, Vector2D& c)
{
	Assert(a.IsValid());
	Assert((b.x != 0.0f) && (b.y != 0.0f));
	c.x = a.x / b.x;
	c.y = a.y / b.y;
}

inline void Vector2DMA(const Vector2D& start, float s, const Vector2D& dir, Vector2D& result)
{
	Assert(start.IsValid() && IsFinite(s) && dir.IsValid());
	result.x = start.x + s * dir.x;
	result.y = start.y + s * dir.y;
}

// FIXME: Remove
// For backwards compatability
inline void	Vector2D::MulAdd(const Vector2D& a, const Vector2D& b, float scalar)
{
	x = a.x + b.x * scalar;
	y = a.y + b.y * scalar;
}

inline void Vector2DLerp(const Vector2D& src1, const Vector2D& src2, float t, Vector2D& dest)
{
	dest[0] = src1[0] + (src2[0] - src1[0]) * t;
	dest[1] = src1[1] + (src2[1] - src1[1]) * t;
}

//-----------------------------------------------------------------------------
// dot, cross
//-----------------------------------------------------------------------------
inline float DotProduct2D(const Vector2D& a, const Vector2D& b)
{
	Assert(a.IsValid() && b.IsValid());
	return(a.x * b.x + a.y * b.y);
}

// for backwards compatability
inline float Vector2D::Dot(const Vector2D& vOther) const
{
	return DotProduct2D(*this, vOther);
}


//-----------------------------------------------------------------------------
// length
//-----------------------------------------------------------------------------
inline float Vector2DLength(const Vector2D& v)
{
	Assert(v.IsValid());
	return (float)FastSqrt(v.x * v.x + v.y * v.y);
}

inline float Vector2D::LengthSqr(void) const
{
	Assert(IsValid());
	return (x * x + y * y);
}

inline float Vector2D::NormalizeInPlace()
{
	return Vector2DNormalize(*this);
}

inline bool Vector2D::IsLengthGreaterThan(float val) const
{
	return LengthSqr() > val * val;
}

inline bool Vector2D::IsLengthLessThan(float val) const
{
	return LengthSqr() < val * val;
}

inline float Vector2D::Length(void) const
{
	return Vector2DLength(*this);
}


inline void Vector2DMin(const Vector2D& a, const Vector2D& b, Vector2D& result)
{
	result.x = (a.x < b.x) ? a.x : b.x;
	result.y = (a.y < b.y) ? a.y : b.y;
}


inline void Vector2DMax(const Vector2D& a, const Vector2D& b, Vector2D& result)
{
	result.x = (a.x > b.x) ? a.x : b.x;
	result.y = (a.y > b.y) ? a.y : b.y;
}


//-----------------------------------------------------------------------------
// Normalization
//-----------------------------------------------------------------------------
inline float Vector2DNormalize(Vector2D& v)
{
	Assert(v.IsValid());
	float l = v.Length();
	if (l != 0.0f)
	{
		v /= l;
	}
	else
	{
		v.x = v.y = 0.0f;
	}
	return l;
}


//-----------------------------------------------------------------------------
// Get the distance from this Vector2D to the other one
//-----------------------------------------------------------------------------
inline float Vector2D::DistTo(const Vector2D& vOther) const
{
	Vector2D delta;
	Vector2DSubtract(*this, vOther, delta);
	return delta.Length();
}

inline float Vector2D::DistToSqr(const Vector2D& vOther) const
{
	Vector2D delta;
	Vector2DSubtract(*this, vOther, delta);
	return delta.LengthSqr();
}


//-----------------------------------------------------------------------------
// Computes the closest point to vecTarget no farther than flMaxDist from vecStart
//-----------------------------------------------------------------------------
inline void ComputeClosestPoint2D(const Vector2D& vecStart, float flMaxDist, const Vector2D& vecTarget, Vector2D* pResult)
{
	Vector2D vecDelta;
	Vector2DSubtract(vecTarget, vecStart, vecDelta);
	float flDistSqr = vecDelta.LengthSqr();
	if (flDistSqr <= flMaxDist * flMaxDist)
	{
		*pResult = vecTarget;
	}
	else
	{
		vecDelta /= FastSqrt(flDistSqr);
		Vector2DMA(vecStart, flMaxDist, vecDelta, *pResult);
	}
}



//-----------------------------------------------------------------------------
//
// Slow methods
//
//-----------------------------------------------------------------------------

#ifndef VECTOR_NO_SLOW_OPERATIONS
#endif
//-----------------------------------------------------------------------------
// Returns a Vector2D with the min or max in X, Y, and Z.
//-----------------------------------------------------------------------------

inline Vector2D Vector2D::Min(const Vector2D& vOther) const
{
	return Vector2D(x < vOther.x ? x : vOther.x,
		y < vOther.y ? y : vOther.y);
}

inline Vector2D Vector2D::Max(const Vector2D& vOther) const
{
	return Vector2D(x > vOther.x ? x : vOther.x,
		y > vOther.y ? y : vOther.y);
}


//-----------------------------------------------------------------------------
// arithmetic operations
//-----------------------------------------------------------------------------

inline Vector2D Vector2D::operator-(void) const
{
	return Vector2D(-x, -y);
}

inline Vector2D Vector2D::operator+(const Vector2D& v) const
{
	Vector2D res;
	Vector2DAdd(*this, v, res);
	return res;
}

inline Vector2D Vector2D::operator-(const Vector2D& v) const
{
	Vector2D res;
	Vector2DSubtract(*this, v, res);
	return res;
}

inline Vector2D Vector2D::operator*(float fl) const
{
	Vector2D res;
	Vector2DMultiply(*this, fl, res);
	return res;
}

inline Vector2D Vector2D::operator*(const Vector2D& v) const
{
	Vector2D res;
	Vector2DMultiply(*this, v, res);
	return res;
}

inline Vector2D Vector2D::operator/(float fl) const
{
	Vector2D res;
	Vector2DDivide(*this, fl, res);
	return res;
}

inline Vector2D Vector2D::operator/(const Vector2D& v) const
{
	Vector2D res;
	Vector2DDivide(*this, v, res);
	return res;
}

inline Vector2D operator*(float fl, const Vector2D& v)
{
	return v * fl;
}

namespace Math
{
	__inline float MapFloat(float x, float in_min, float in_max, float out_min, float out_max)
	{
		return (x - in_min) * (out_max - out_min) / (in_min - in_min) + out_max;
	}
}

namespace Utils
{

#pragma warning (disable : 6031)
inline void ReplaceSpecials(std::string& str) // thx cathook
{
	int val;
	size_t c = 0;
	const size_t len = str.size();
	for (int i = 0; i + c < len; ++i)
	{
		str[i] = str[i + c];
		if (str[i] != '\\') { continue; }
		if (i + c + 1 == len) { break; }

		switch (str[i + c + 1])
		{
			// Several control characters
		case 'b':
			++c;
			str[i] = '\b';
			break;
		case 'n':
			++c;
			str[i] = '\n';
			break;
		case 'v':
			++c;
			str[i] = '\v';
			break;
		case 'r':
			++c;
			str[i] = '\r';
			break;
		case 't':
			++c;
			str[i] = '\t';
			break;
		case 'f':
			++c;
			str[i] = '\f';
			break;
		case 'a':
			++c;
			str[i] = '\a';
			break;
			// Write escaped escape character as is
		case '\\':
			++c;
			break;
			// Convert specified value from HEX
		case 'x':
			if (i + c + 4 > len)
			{
				continue;
			}
			std::sscanf(&str[i + c + 2], "%02X", &val);
			c += 3;
			str[i] = val;
			break;
			// Convert from unicode
		case 'u':
			if (i + c + 6 > len)
			{
				continue;
			}
			// 1. Scan 16bit HEX value
			std::sscanf(&str[i + c + 2], "%04X", &val);
			c += 5;
			// 2. Convert value to UTF-8
			if (val <= 0x7F)
			{
				str[i] = val;
			}
			else if (val <= 0x7FF)
			{
				str[i] = 0xC0 | ((val >> 6) & 0x1F);
				str[i + 1] = 0x80 | (val & 0x3F);
				++i;
				--c;
			}
			else
			{
				str[i] = 0xE0 | ((val >> 12) & 0xF);
				str[i + 1] = 0x80 | ((val >> 6) & 0x3F);
				str[i + 2] = 0x80 | (val & 0x3F);
				i += 2;
				c -= 2;
			}
			break;
		}
	}
	str.resize(len - c);
}

	__inline int RandIntSimple(int min, int max)
	{
		SPOOF_FUNC;
		std::random_device rd; std::mt19937 gen(rd()); std::uniform_int_distribution<> distr(min, max);
		return distr(gen);
	}

	inline float sqrtf_(float x)
	{
		SPOOF_FUNC;
		union { float f; uint32_t i; } z = { x };
		z.i = 0x5f3759df - (z.i >> 1);
		z.f *= (1.5f - (x * 0.5f * z.f * z.f));
		z.i = 0x7EEEEEEE - z.i;
		return z.f;
	}


	double powf_(double x, int y)
	{
		SPOOF_FUNC;
		double temp;
		if (y == 0)
			return 1;
		temp = powf_(x, y / 2);
		if ((y % 2) == 0) {
			return temp * temp;
		}
		else {
			if (y > 0)
				return x * temp * temp;
			else
				return (temp * temp) / x;
		}
	}
	double GetCrossDistance(double x1, double y1, double x2, double y2)
	{
		SPOOF_FUNC;
		return sqrtf_(powf_((float)(x1 - x2), (float)2) + powf_((float)(y1 - y2), (float)2));
	}
}


struct SVector
{
	float x;
	float y;
	float z;
	SVector(float x1, float y1, float z1)
	{
		x = x1;
		y = y1;
		z = z1;
	}
};

class QAngleByValue;
class QAngle
{
public:
	// Members
	float x, y, z;

	// Construction/destruction
	QAngle(void);
	QAngle(float X, float Y, float Z);
	//      QAngle(RadianEuler const &angles);      // evil auto type promotion!!!

	// Allow pass-by-value
	operator QAngleByValue& () { return *((QAngleByValue*)(this)); }
	operator const QAngleByValue& () const { return *((const QAngleByValue*)(this)); }

	// Initialization
	void Init(float ix = 0.0f, float iy = 0.0f, float iz = 0.0f);
	void Random(float minVal, float maxVal);

	// Got any nasty NAN's?
	bool IsValid() const;
	void Invalidate();

	// array access...
	float operator[](int i) const;
	float& operator[](int i);

	// Base address...
	float* Base();
	float const* Base() const;

	// equality
	bool operator==(const QAngle& v) const;
	bool operator!=(const QAngle& v) const;

	bool IsZero(float tolerance = 0.01f) const
	{
		SPOOF_FUNC;
		return (x > -tolerance && x < tolerance &&
			y > -tolerance && y < tolerance &&
			z > -tolerance && z < tolerance);
	}

	// arithmetic operations
	QAngle& operator+=(const QAngle& v);
	QAngle& operator-=(const QAngle& v);
	QAngle& operator*=(float s);
	QAngle& operator/=(float s);

	// Get the vector's magnitude.
	float   Length() const;
	float   LengthSqr() const;

	// negate the QAngle components
	//void  Negate();

	// No assignment operators either...
	QAngle& operator=(const QAngle& src);

#ifndef VECTOR_NO_SLOW_OPERATIONS
	// copy constructors

	// arithmetic operations
	QAngle  operator-(void) const;

	QAngle  operator+(const QAngle& v) const;
	QAngle  operator-(const QAngle& v) const;
	QAngle  operator*(float fl) const;
	QAngle  operator/(float fl) const;
#else

private:
	// No copy constructors allowed if we're in optimal mode
	QAngle(const QAngle& vOther);

#endif
};

//-----------------------------------------------------------------------------
// constructors
//-----------------------------------------------------------------------------
inline QAngle::QAngle(void)
{
#ifdef _DEBUG
#ifdef VECTOR_PARANOIA
	// Initialize to NAN to catch errors
	x = y = z = VEC_T_NAN;
#endif
#endif
}

inline QAngle::QAngle(float X, float Y, float Z)
{
	x = X; y = Y; z = Z;

}

//-----------------------------------------------------------------------------
// initialization
//-----------------------------------------------------------------------------
inline void QAngle::Init(float ix, float iy, float iz)
{
	SPOOF_FUNC;
	x = ix; y = iy; z = iz;

}

inline void QAngle::Random(float minVal, float maxVal)
{
	SPOOF_FUNC;
	x = minVal + ((float)rand() / RAND_MAX) * (maxVal - minVal);
	y = minVal + ((float)rand() / RAND_MAX) * (maxVal - minVal);
	z = minVal + ((float)rand() / RAND_MAX) * (maxVal - minVal);

}

//-----------------------------------------------------------------------------
// assignment
//-----------------------------------------------------------------------------
inline QAngle& QAngle::operator=(const QAngle& vOther)
{
	SPOOF_FUNC;
	x = vOther.x; y = vOther.y; z = vOther.z;
	return *this;
}

//-----------------------------------------------------------------------------
// comparison
//-----------------------------------------------------------------------------
inline bool QAngle::operator==(const QAngle& src) const
{

	SPOOF_FUNC;
	return (src.x == x) && (src.y == y) && (src.z == z);
}

inline bool QAngle::operator!=(const QAngle& src) const
{

	SPOOF_FUNC;
	return (src.x != x) || (src.y != y) || (src.z != z);
}

//-----------------------------------------------------------------------------
// standard math operations
//-----------------------------------------------------------------------------
inline QAngle& QAngle::operator+=(const QAngle& v)
{

	SPOOF_FUNC;
	x += v.x; y += v.y; z += v.z;
	return *this;
}

inline QAngle& QAngle::operator-=(const QAngle& v)
{

	SPOOF_FUNC;
	x -= v.x; y -= v.y; z -= v.z;
	return *this;
}

inline QAngle& QAngle::operator*=(float fl)
{
	SPOOF_FUNC;
	x *= fl;
	y *= fl;
	z *= fl;

	return *this;
}

inline QAngle& QAngle::operator/=(float fl)
{
	SPOOF_FUNC;
	Assert(fl != 0.0f);
	float oofl = 1.0f / fl;
	x *= oofl;
	y *= oofl;
	z *= oofl;

	return *this;
}

//-----------------------------------------------------------------------------
// Base address...
//-----------------------------------------------------------------------------
inline float* QAngle::Base()
{
	SPOOF_FUNC;
	return (float*)this;
}

inline float const* QAngle::Base() const
{
	SPOOF_FUNC;
	return (float const*)this;
}

//-----------------------------------------------------------------------------
// Array access
//-----------------------------------------------------------------------------
inline float& QAngle::operator[](int i)
{
	SPOOF_FUNC;
	Assert((i >= 0) && (i < 3));
	return ((float*)this)[i];
}

inline float QAngle::operator[](int i) const
{
	SPOOF_FUNC;
	Assert((i >= 0) && (i < 3));
	return ((float*)this)[i];
}

//-----------------------------------------------------------------------------
// length
//-----------------------------------------------------------------------------
inline float QAngle::Length() const
{
	SPOOF_FUNC;

	return (float)FastSqrt(LengthSqr());
}


inline float QAngle::LengthSqr() const
{
	SPOOF_FUNC;
	return x * x + y * y + z * z;
}


//-----------------------------------------------------------------------------
// arithmetic operations (SLOW!!)
//-----------------------------------------------------------------------------
#ifndef VECTOR_NO_SLOW_OPERATIONS

inline QAngle QAngle::operator-(void) const
{
	SPOOF_FUNC;
	return QAngle(-x, -y, -z);
}

inline QAngle QAngle::operator+(const QAngle& v) const
{
	SPOOF_FUNC;
	QAngle res;
	res.x = x + v.x;
	res.y = y + v.y;
	res.z = z + v.z;
	return res;
}

inline QAngle QAngle::operator-(const QAngle& v) const
{
	SPOOF_FUNC;
	QAngle res;
	res.x = x - v.x;
	res.y = y - v.y;
	res.z = z - v.z;
	return res;
}

inline QAngle QAngle::operator*(float fl) const
{
	SPOOF_FUNC;
	QAngle res;
	res.x = x * fl;
	res.y = y * fl;
	res.z = z * fl;
	return res;
}

inline QAngle QAngle::operator/(float fl) const
{
	SPOOF_FUNC;
	QAngle res;
	res.x = x / fl;
	res.y = y / fl;
	res.z = z / fl;
	return res;
}

inline QAngle operator*(float fl, const QAngle& v)
{
	SPOOF_FUNC;
	return v * fl;
}

#endif // VECTOR_NO_SLOW_OPERATIONS


//QANGLE SUBTRAC
inline void QAngleSubtract(const QAngle& a, const QAngle& b, QAngle& c)
{
	SPOOF_FUNC;

	c.x = a.x - b.x;
	c.y = a.y - b.y;
	c.z = a.z - b.z;
}

//QANGLEADD
inline void QAngleAdd(const QAngle& a, const QAngle& b, QAngle& c)
{

	SPOOF_FUNC;
	c.x = a.x + b.x;
	c.y = a.y + b.y;
	c.z = a.z + b.z;
}


void monkey(QAngle& angle)
{
	SPOOF_FUNC;
	while (angle.x > 89.0f)
		angle.x -= 180.f;

	while (angle.x < -89.0f)
		angle.x += 180.f;

	while (angle.y > 180.f)
		angle.y -= 360.f;

	while (angle.y < -180.f)
		angle.y += 360.f;
}

QAngle CalcAngle(const Vector& src, const Vector& dst)
{
	SPOOF_FUNC;
	QAngle angle = QAngle();
	SVector delta = SVector((src.x - dst.x), (src.y - dst.y), (src.z - dst.z));

	double hyp = sqrt(delta.x * delta.x + delta.y * delta.y);

	angle.x = atan(delta.z / hyp) * (180.0f / M_PI);
	angle.y = atan(delta.y / delta.x) * (180.0f / M_PI);
	angle.z = 0;
	if (delta.x >= 0.0) angle.y += 180.0f;

	return angle;
}


double GetFov(const QAngle& viewAngle, const QAngle& aimAngle)
{
	SPOOF_FUNC;
	QAngle delta = aimAngle - viewAngle;
	monkey(delta);

	return sqrt(pow(delta.x, 2.0f) + pow(delta.y, 2.0f));
}


Vector calc_angle(Vector src, Vector dst)
{
	SPOOF_FUNC;
	Vector angle = Vector();
	SVector delta = SVector((src.x - dst.x), (src.y - dst.y), (src.z - dst.z));

	double hyp = sqrt(delta.x * delta.x + delta.y * delta.y);

	angle.x = atan(delta.z / hyp) * (180.0f / M_PI);
	angle.y = atan(delta.y / delta.x) * (180.0f / M_PI);
	angle.z = 0;
	if (delta.x >= 0.0) angle.y += 180.0f;

	return angle;
}

struct ColorRGB
{
	float r, g, b;
};

struct glowMode
{
	BYTE GeneralGlowMode, BorderGlowMode, BorderSize, TransparentLevel;
};

struct glowFade
{
	int a, b;
	float c, d, e, f;
};

struct Matrix
{
	float matrix[16];
};

struct c_matrix
{
	float matrix[16];
};

class Matrix3x4
{
public:
	union
	{
		struct
		{
			float _11, _12, _13, _14;
			float _21, _22, _23, _24;
			float _31, _32, _33, _34;
		};

		float m[3][4];
		float mm[12];
	};

	inline Vector& GetAxis(int i)
	{
		SPOOF_FUNC;
		return *(Vector*)&m[i][0];
	}
};

struct PredictCtx
{
	Vector StartPos;
	Vector TargetPos;
	Vector TargetVel;
	float BulletSpeed;
	float BulletGravity;

	Vector2D AimAngles;
};

int entX = 0;
int entY = 0;

int closestX = 0;
int closestY = 0;

int aX = 0;
int aY = 0;


inline c_matrix get_matrix()
{
	SPOOF_FUNC;
	uint64_t viewRenderer = *(uint64_t*)(global::g_hGameImage + pInitOffsets.m_vViewRender);
	uint64_t viewMatrix = *(uint64_t*)(viewRenderer + pInitOffsets.m_vViewMatrix);

	return *(c_matrix*)(viewMatrix);
}

int ret_system(int index) {
	return spoof_call_ex(jmp_rbx_0, GetSystemMetrics, index);
}

bool world_to_screen(Vector in, Vector2D& out)
{
	SPOOF_FUNC;
	float* m_vMatrix = get_matrix().matrix;
	float w = m_vMatrix[12] * in.x + m_vMatrix[13] * in.y + m_vMatrix[14] * in.z + m_vMatrix[15];

	if (w < 0.01f)
		return false;

	out.x = m_vMatrix[0] * in.x + m_vMatrix[1] * in.y + m_vMatrix[2] * in.z + m_vMatrix[3];
	out.y = m_vMatrix[4] * in.x + m_vMatrix[5] * in.y + m_vMatrix[6] * in.z + m_vMatrix[7];

	float invw = 1.0f / w;
	out.x *= invw;
	out.y *= invw;

	float xx = ret_system(SM_CXSCREEN) / 2;
	float xy = ret_system(SM_CYSCREEN) / 2;

	xx += 0.5 * out.x * ret_system(SM_CXSCREEN) + 0.5;
	xy -= 0.5 * out.y * ret_system(SM_CYSCREEN) + 0.5;

	out.x = xx;
	out.y = xy;

	if (out.x > ret_system(SM_CXSCREEN) || out.x < 0 || out.y > ret_system(SM_CYSCREEN) || out.y < 0)
		return false;

	return true;
}


struct Vec3 {
	float x, y, z;
	Vec3() { x = 0; y = 0; z = 0; }
	Vec3(float _x, float _y, float _z) { x = _x; y = _y; z = _z; }
	bool operator==(const float _t) {
		return x == _t && y == _t && z == _t;
	}
	bool operator==(Vec3 _t) {
		return x == _t.x && y == _t.y && z == _t.z;
	}
	bool operator!=(Vec3 _t) {
		return x != _t.x && y != _t.y && z != _t.z;
	}
	bool operator<(const float _t) {
		return x < _t && y < _t && z < _t;
	}
	bool operator>(const float _t) {
		return x > _t && y > _t && z > _t;
	}
	bool operator>=(const float _t) {
		return x >= _t && y >= _t && z >= _t;
	}
	bool operator<=(const float _t) {
		return x <= _t && y <= _t && z <= _t;
	}
	bool operator!=(const float _t) {
		return x != _t && y != _t && z != _t;
	}
};

struct Vec2 {
	float x, y;
	Vec2() { x = 0; y = 0; }
	Vec2(float _x, float _y) { x = _x; y = _y; }
	Vec2(Vec3 _t) { x = _t.x; y = _t.y; }
	bool operator==(const float _t) {
		return x == _t && y == _t;
	}
	bool operator<(const float _t) {
		return x < _t && y < _t;
	}
	bool operator>(const float _t) {
		return x > _t && y > _t;
	}
	bool operator>=(const float _t) {
		return x >= _t && y >= _t;
	}
	bool operator<=(const float _t) {
		return x <= _t && y <= _t;
	}
	bool operator!=(const float _t) {
		return x != _t && y != _t;
	}
};

struct Vector2 {
	float x, y;

	Vector2 operator-(Vector2 ape)
	{
		return { x - ape.x, y - ape.y };
	}

	Vector2 operator+(Vector2 ape)
	{
		return { x + ape.x, y + ape.y };
	}

	Vector2 operator*(float ape)
	{
		return { x * ape, y * ape };
	}

	Vector2 operator/(float ape)
	{
		return { x / ape, y / ape };
	}

	Vector2 operator/=(float ape)
	{
		x /= ape;
		y /= ape;

		return *this;
	}

	Vector2 operator+=(Vector2 ape)
	{
		return { x += ape.x, y += ape.y };
	}

	Vector2 operator-=(Vector2 ape)
	{
		return { x -= ape.x, y -= ape.y };
	}

	void Normalize()
	{
		if (x > 89.0f)
			x -= 180.f;

		if (x < -89.0f)
			x += 180.f;

		if (y > 180.f)
			y -= 360.f;

		if (y < -180.f)
			y += 360.f;
	}

	float Length2D()
	{
		return sqrt((x * x) + (y * y));
	}

	float Dist2D(Vector2 ape)
	{
		return (*this - ape).Length2D();
	}
};

struct Vector3 {
	float x, y, z;

	float distance(Vector3 vec)
	{
		return sqrt(
			pow(vec.x - x, 2) +
			pow(vec.y - y, 2)
		);
	}

	Vector3() : x(0), y(0), z(0) {}

	Vector3(float X, float Y, float Z) : x(X), y(Y), z(Z) {}

	Vector3 operator-(Vector3 ape)
	{
		return { x - ape.x, y - ape.y, z - ape.z };
	}

	Vector3 operator+(Vector3 ape)
	{
		return { x + ape.x, y + ape.y, z + ape.z };
	}

	Vector3 operator*(float ape)
	{
		return { x * ape, y * ape, z * ape };
	}

	Vector3 operator/(float ape)
	{
		return { x / ape, y / ape, z / ape };
	}

	Vector3 operator/=(float ape)
	{
		x /= ape;
		y /= ape;
		z /= ape;

		return *this;
	}

	Vector3 operator+=(Vector3 ape)
	{
		return { x += ape.x, y += ape.y, z += ape.z };
	}

	Vector3 operator-=(Vector3 ape)
	{
		return { x -= ape.x, y -= ape.y, z -= ape.z };
	}

	void Normalize()
	{
		while (x > 89.0f)
			x -= 180.f;

		while (x < -89.0f)
			x += 180.f;

		while (y > 180.f)
			y -= 360.f;

		while (y < -180.f)
			y += 360.f;
	}

	float Length()
	{
		return sqrt((x * x) + (y * y) + (z * z));
	}

	float Length2D()
	{
		return sqrt((x * x) + (y * y));
	}

	float DistTo(Vector3 ape)
	{
		return (*this - ape).Length();
	}

	float Dist2D(Vector3 ape)
	{
		return (*this - ape).Length2D();
	}


	float Distance(Vector3 pos)
	{
		float Dist = sqrt((x - pos.x) * (x - pos.x)
			+ (y - pos.y) * (y - pos.y)
			+ (z - pos.z) * (z - pos.z));
		return Dist * 0.01905f;
	}

	Vector3 CalcAngle(Vector3 dst, float height)
	{
		Vector3 angle, e = { dst.x - x, dst.y - y, dst.z - z };
		float eh = sqrt(e.x * e.x + e.y * e.y);
		angle.x = (atan2(-e.z, eh) * 180 / 3.14159f) + height;
		angle.y = (atan2(e.y, e.x) * 180 / 3.14159f);
		angle.z = 0;
		return angle;
	}

};

struct Vector3 _WorldToScreen(const struct Vector3 pos, struct Matrix matrix) {
	struct Vector3 out;
	float _x = matrix.matrix[0] * pos.x + matrix.matrix[1] * pos.y + matrix.matrix[2] * pos.z + matrix.matrix[3];
	float _y = matrix.matrix[4] * pos.x + matrix.matrix[5] * pos.y + matrix.matrix[6] * pos.z + matrix.matrix[7];
	out.z = matrix.matrix[12] * pos.x + matrix.matrix[13] * pos.y + matrix.matrix[14] * pos.z + matrix.matrix[15];

	_x *= 1.f / out.z;
	_y *= 1.f / out.z;

	int width = GetSystemMetrics(SM_CXSCREEN) / 2;;
	int height = GetSystemMetrics(SM_CYSCREEN) / 2;;

	out.x = width * .5f;
	out.y = height * .5f;

	out.x += 0.5f * _x * width + 0.5f;
	out.y -= 0.5f * _y * height + 0.5f;

	return out;
}

float Distance(Vector3 EntityPos, Vector3 PlayerPos)
{
	float Dist = sqrt((PlayerPos.x - EntityPos.x) * (PlayerPos.x - EntityPos.x)
		+ (PlayerPos.y - EntityPos.y) * (PlayerPos.y - EntityPos.y)
		+ (PlayerPos.z - EntityPos.z) * (PlayerPos.z - EntityPos.z));
	return Dist * 0.01905f;
}

namespace util
{
	uintptr_t ida_signature(uintptr_t moduleAdress, const char* signature)
	{
		static auto patternToByte = [](const char* pattern)
		{
			auto       bytes = std::vector<int>{ };
			const auto start = const_cast<char*>(pattern);
			const auto end = const_cast<char*>(pattern) + strlen(pattern);

			for (auto current = start; current < end; ++current)
			{
				if (*current == '?')
				{
					++current;
					if (*current == '?')
						++current;
					bytes.push_back(-1);
				}
				else { bytes.push_back(strtoul(current, &current, 16)); }
			}
			return bytes;
		};

		const auto dosHeader = (PIMAGE_DOS_HEADER)moduleAdress;
		const auto ntHeaders = (PIMAGE_NT_HEADERS)((std::uint8_t*)moduleAdress + dosHeader->e_lfanew);

		const auto sizeOfImage = ntHeaders->OptionalHeader.SizeOfImage;
		auto       patternBytes = patternToByte(signature);
		const auto scanBytes = reinterpret_cast<std::uint8_t*>(moduleAdress);

		const auto s = patternBytes.size();
		const auto d = patternBytes.data();

		for (auto i = 0ul; i < sizeOfImage - s; ++i)
		{
			bool found = true;
			for (auto j = 0ul; j < s; ++j)
			{
				if (scanBytes[i + j] != d[j] && d[j] != -1)
				{
					found = false;
					break;
				}
			}
			if (found) { return reinterpret_cast<uintptr_t>(&scanBytes[i]); }
		}
		return NULL;
	}
}