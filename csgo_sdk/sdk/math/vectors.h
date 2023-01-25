#pragma once
#include <cmath>
#include <algorithm>
#include <winerror.h>
#define deg(a) a * 57.295779513082f

class vec2_t {
public:
	float x, y;
	vec2_t( ) {
		Init( );
	}

	vec2_t( float x ) {
		this->x = y = x;
	}

	vec2_t( float x, float y ) {
		this->x = x;
		this->y = y;
	}

	void Init( float x ) {
		this->x = y = x;
	}

	void Init( ) {
		x = y = 0;
	}

	void Init( float x, float y ) {
		this->x = x;
		this->y = y;
	}

	vec2_t& operator=( const vec2_t& vec ) {
		this->x = vec.x; this->y = vec.y;

		return *this;
	}

	vec2_t operator-( ) const {
		return vec2_t( -this->x, -this->y );
	}

	vec2_t operator+( const vec2_t& v ) const {
		return vec2_t( this->x + v.x, this->y + v.y );
	}

	vec2_t operator-( const vec2_t& v ) const {
		return vec2_t( this->x - v.x, this->y - v.y );
	}

	vec2_t operator*( float fl ) const {
		return vec2_t( this->x * fl, this->y * fl );
	}

	vec2_t operator*( const vec2_t& v ) const {
		return vec2_t( this->x * v.x, this->y * v.y );
	}

	vec2_t operator/( float fl ) const {
		return vec2_t( this->x / fl, this->y / fl );
	}

	vec2_t operator/( const vec2_t& v ) const {
		return vec2_t( this->x / v.x, this->y / v.y );
	}
};

class matrix_t;
class ang_t;
class vec3_t {
public:
	float x, y, z;

	/* Initialize funcitions */

	vec3_t( ) {
		init( );
	}

	vec3_t( float x, float y, float z = 0.f ) {
		this->x = x;
		this->y = y;
		this->z = z;
	}

	void init( ) {
		this->x = this->y = this->z = 0.0f;
	}

	void init( float x, float y, float z = 0.f ) {
		this->x = x;
		this->y = y;
		this->z = z;
	}

	/* Main funcitions */

	bool is_valid( ) {
		return std::isfinite( this->x ) && std::isfinite( this->y ) && std::isfinite( this->z );
	}

	bool is_zero( ) {
		return vec3_t( this->x, this->y, this->z ) == vec3_t( 0.0f, 0.0f, 0.0f );
	}

	void invalidate( ) {
		this->x = this->y = this->z = std::numeric_limits< float >::infinity( );
	}

	void clear( ) {
		this->x = this->y = this->z = 0.0f;
	}

	void zero( ) {
		this->x = this->y = this->z = 0.0f;
	}

	void clamp( ) {
		while ( this->x < -89.0f )
			this->x += 89.0f;

		if ( this->x > 89.0f )
			this->x = 89.0f;

		while ( this->y < -180.0f )
			this->y += 360.0f;

		while ( this->y > 180.0f )
			this->y -= 360.0f;

		this->z = 0.0f;
	}

	void normalize_in_place( )
	{
		*this = normalized( );
	}

	float normalize_in_place_float( )
	{
		const float flLength = this->length( );
		const float flRadius = 1.0f / ( flLength + std::numeric_limits<float>::epsilon( ) );

		this->x *= flRadius;
		this->y *= flRadius;
		this->z *= flRadius;

		return flLength;
	}

	float dot( const vec3_t& vOther ) const
	{
		return ( x * vOther.x + y * vOther.y + z * vOther.z );
	}

	float dot( const float* fOther ) const
	{
		const vec3_t& a = *this;

		return( a.x * fOther[ 0 ] + a.y * fOther[ 1 ] + a.z * fOther[ 2 ] );
	}

	vec3_t normalize( )
	{
		vec3_t vec3_t;
		float length = this->length( );

		if ( length != 0 )
		{
			vec3_t.x = x / length;
			vec3_t.y = y / length;
			vec3_t.z = z / length;
		}
		else
		{
			vec3_t.x = vec3_t.y = 0.0f; vec3_t.z = 1.0f;
		}

		return vec3_t;
	}

	vec3_t normalized( ) const
	{
		vec3_t res = *this;
		float l = res.length( );
		if ( l != 0.0f ) {
			res /= l;
		}
		else {
			res.x = res.y = res.z = 0.0f;
		}
		return res;
	}

	float normalize_place( ) const
	{
		vec3_t v = *this;

		float iradius = 1.f / ( this->length( ) + 1.192092896e-07F ); //FLT_EPSILON

		v.x *= iradius;
		v.y *= iradius;
		v.z *= iradius;

		return v.length( );
	}

	float distance_to( const vec3_t& vec ) const {
		vec3_t delta;

		delta.x = this->x - vec.x;
		delta.y = this->y - vec.y;
		delta.z = this->z - vec.z;

		return delta.length( );
	}

	float distance_to_sqr( const vec3_t& vec ) const {
		vec3_t delta;

		delta.x = this->x - vec.x;
		delta.y = this->y - vec.y;
		delta.z = this->z - vec.z;

		return delta.length_sqr( );
	}

	float dot_product( const vec3_t& vec ) const {
		return this->x * vec.x + this->y * vec.y + this->z * vec.z;
	}

	vec3_t cross_product( const vec3_t& vec ) const {
		return vec3_t( this->y * vec.z - this->z * vec.y, this->z * vec.x - this->x * vec.z, this->x * vec.y - this->y * vec.x );
	}

	float length( ) const {
		return std::sqrtf( this->x * this->x + this->y * this->y + this->z * this->z );
	}

	float length_sqr( ) const {
		return this->x * this->x + this->y * this->y + this->z * this->z;
	}

	float length_sqr_2d( ) const {
		return this->x * this->x + this->y * this->y;
	}

	float length_2d( ) const {
		return std::sqrtf( this->x * this->x + this->y * this->y );
	}

	float Length_2d( ) const {
		return std::sqrtf( this->x * this->x + this->y * this->y );
	}

	void vector_cross_product( const vec3_t& a, const vec3_t& b, vec3_t& result )
	{
		result.x = a.y * b.z - a.z * b.y;
		result.y = a.z * b.x - a.x * b.z;
		result.z = a.x * b.y - a.y * b.x;
	}

	vec3_t cross( const vec3_t& vOther )
	{
		vec3_t res;
		vector_cross_product( *this, vOther, res );
		return res;
	}

	ang_t to_angle( vec3_t* up = 0 );
	vec3_t transform( const matrix_t& in ) const;
	vec3_t i_transform( const matrix_t& in ) const;

	/* Operators */

	vec3_t& operator=( const vec3_t& vec ) {
		this->x = vec.x; this->y = vec.y; this->z = vec.z;

		return *this;
	}

	vec3_t operator-( ) const {
		return vec3_t( -this->x, -this->y, -this->z );
	}

	vec3_t operator+( const vec3_t& v ) const {
		return vec3_t( this->x + v.x, this->y + v.y, this->z + v.z );
	}

	vec3_t operator-( const vec3_t& v ) const {
		return vec3_t( this->x - v.x, this->y - v.y, this->z - v.z );
	}

	vec3_t operator*( float fl ) const {
		return vec3_t( this->x * fl, this->y * fl, this->z * fl );
	}

	vec3_t operator*( const vec3_t& v ) const {
		return vec3_t( this->x * v.x, this->y * v.y, this->z * v.z );
	}

	vec3_t operator/( float fl ) const {
		return vec3_t( this->x / fl, this->y / fl, this->z / fl );
	}

	vec3_t operator/( const vec3_t& v ) const {
		return vec3_t( this->x / v.x, this->y / v.y, this->z / v.z );
	}

	float& operator[]( int i ) {
		return ( ( float* )this )[ i ];
	}

	float operator[]( int i ) const {
		return ( ( float* )this )[ i ];
	}

	bool operator==( const vec3_t& src ) const {
		return ( src.x == this->x ) && ( src.y == y ) && ( src.z == z );
	}

	bool operator!=( const vec3_t& src ) const {
		return ( src.x != this->x ) || ( src.y != y ) || ( src.z != z );
	}

	vec3_t& operator+=( const vec3_t& v ) {
		this->x += v.x; this->y += v.y; this->z += v.z;

		return *this;
	}

	vec3_t& operator-=( const vec3_t& v ) {
		this->x -= v.x; this->y -= v.y; this->z -= v.z;

		return *this;
	}

	vec3_t& operator*=( float fl ) {
		this->x *= fl;
		this->y *= fl;
		this->z *= fl;

		return *this;
	}

	vec3_t& operator*=( const vec3_t& v ) {
		this->x *= v.x;
		this->y *= v.y;
		this->z *= v.z;

		return *this;
	}

	vec3_t& operator/=( const vec3_t& v ) {
		this->x /= v.x;
		this->y /= v.y;
		this->z /= v.z;

		return *this;
	}

	vec3_t& operator+=( float fl ) {
		this->x += fl;
		this->y += fl;
		this->z += fl;

		return *this;
	}

	vec3_t& operator/=( float fl ) {
		this->x /= fl;
		this->y /= fl;
		this->z /= fl;

		return *this;
	}

	vec3_t& operator-=( float fl ) {
		this->x -= fl;
		this->y -= fl;
		this->z -= fl;

		return *this;
	}
};

struct vec4_t : public vec3_t {
	vec4_t( ) = default;
	vec4_t( float ix, float iy, float iz, float iw ) {
		x = ix;
		y = iy;
		z = iz;
		w = iw;
	}
	vec4_t( const vec3_t& value ) {
		x = value.x;
		y = value.y;
		z = value.z;
		w = 0.f;
	}
	vec4_t( const vec2_t& value0, const vec2_t& value1 ) {
		x = value0.x;
		y = value0.y;
		z = value1.x;
		w = value1.y;
	}

	__forceinline vec4_t& operator=( const vec3_t& value ) {
		x = value.x;
		y = value.y;
		z = value.z;
		w = 0.f;

		return *this;
	}

	__forceinline vec4_t& operator=( const vec4_t& value ) {
		x = value.x;
		y = value.y;
		z = value.z;
		w = value.w;

		return *this;
	}

	float w = 0.f;
};

class ang_t {
public:
	float pitch, yaw, roll;

	ang_t( ) {

	}

	ang_t( float x, float y, float z = 0.f ) {
		this->pitch = x;
		this->yaw = y;
		this->roll = z;
	}

	__forceinline ang_t operator+( const ang_t& value ) const {
		return ang_t( pitch + value.pitch, yaw + value.yaw, roll + value.roll );
	}

	__forceinline ang_t operator-( const ang_t& value ) const {
		return ang_t( pitch - value.pitch, yaw - value.yaw, roll - value.roll );
	}

	__forceinline ang_t operator-( float value ) const {
		return ang_t( pitch - value, yaw - value, roll - value );
	}

	__forceinline ang_t operator+( float value ) const {
		return ang_t( pitch + value, yaw + value, roll + value );
	}

	__forceinline ang_t operator/( float value ) const {
		return ang_t( pitch / value, yaw / value, roll / value );
	}

	__forceinline ang_t operator*( float value ) const {
		return ang_t( pitch * value, yaw * value, roll * value );
	}

	__forceinline ang_t& operator-=( const ang_t& value ) {
		pitch -= value.pitch;
		yaw -= value.yaw;
		roll -= value.roll;

		return *this;
	}

	__forceinline ang_t& operator+=( const ang_t& value ) {
		pitch += value.pitch;
		yaw += value.yaw;
		roll += value.roll;

		return *this;
	}

	__forceinline ang_t& operator/=( float value ) {
		pitch /= value;
		yaw /= value;
		roll /= value;

		return *this;
	}

	float& operator[]( int i ) {
		return ( ( float* )this )[ i ];
	}

	float operator[]( int i ) const {
		return ( ( float* )this )[ i ];
	}

	__forceinline ang_t& operator*=( float value ) {
		pitch *= value;
		yaw *= value;
		roll *= value;

		return *this;
	}

	__forceinline bool operator==( const ang_t& value ) const {
		return pitch == value.pitch && yaw == value.yaw && roll == value.roll;
	}

	__forceinline bool operator!=( const ang_t& value ) const {
		return !( operator==( value ) );
	}

	ang_t& sanitize( bool egnore_pitch = false );

	ang_t& normalize( ) {
		pitch = remainderf( pitch, 360.f );
		yaw = remainderf( yaw, 360.f );
		roll = remainderf( roll, 360.f );

		return *this;
	}

	void clamp( ) {
		while ( this->pitch < -89.0f )
			this->pitch += 89.0f;

		if ( this->pitch > 89.0f )
			this->pitch = 89.0f;

		while ( this->yaw < -180.0f )
			this->yaw += 360.0f;

		while ( this->yaw> 180.0f )
			this->yaw -= 360.0f;

		this->roll = std::clamp( this->roll, -50.f, 50.f );
	}

	ang_t no_roll( ) {
		return ang_t( this->pitch, this->yaw, 0.f );
	}

	__forceinline ang_t normalized( ) const {
		auto ret = *this;

		return ret.normalize( );
	}

	vec3_t get_dir( vec3_t* right = nullptr, vec3_t* up = nullptr ) const;

	__forceinline float length_sqr( ) const {
		return pitch * pitch + yaw * yaw + roll * roll;
	}

	__forceinline float length( ) const {
		return std::sqrt( length_sqr( ) );
	}

	__forceinline float Length2D( ) const {
		return std::sqrt( pitch * pitch + yaw * yaw );
	}

	__forceinline bool is_valid( ) const {
		return std::isfinite( pitch ) && std::isfinite( yaw ) && std::isfinite( roll );
	}

	__forceinline bool is_zero( ) const {
		return pitch == 0.f && yaw == 0.f && roll == 0.f;
	}
};
