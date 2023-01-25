#include "vectors.h"
#include <algorithm>
#include "matrix.h"

vec3_t vec3_t::transform( const matrix_t& in ) const {
	return vec3_t( dot_product( vec3_t( in[ 0 ][ 0 ], in[ 0 ][ 1 ], in[ 0 ][2 ] ) ) + in[ 0 ][ 4 ], dot_product( vec3_t( in[ 1 ][ 0 ], in[ 1 ][ 1 ], in[ 1 ][ 2 ] ) ) + in[ 1 ][ 4 ], dot_product( vec3_t( in[ 2 ][ 0 ], in[ 2 ][ 1 ], in[ 2 ][ 2 ] ) ) + in[ 2 ][ 4 ] );
}

vec3_t vec3_t::i_transform( const matrix_t& in ) const {
	return vec3_t(
		( x - in[ 0 ][ 4 ] ) * in[ 0 ][ 0 ] + ( y - in[ 1 ][ 4 ] ) * in[ 1 ][ 0 ] + ( z - in[ 2 ][ 4 ] ) * in[ 2 ][ 0 ],
		( x - in[ 0 ][ 4 ] ) * in[ 0 ][ 1 ] + ( y - in[ 1 ][ 4 ] ) * in[ 1 ][ 1 ] + ( z - in[ 2 ][ 4 ] ) * in[ 2 ][ 1 ],
		( x - in[ 0 ][ 4 ] ) * in[ 0 ][ 2 ] + ( y - in[ 1 ][ 4 ] ) * in[ 1 ][ 2 ] + ( z - in[ 2 ][ 4 ] ) * in[ 2 ][ 2 ]
	);
}

ang_t vec3_t::to_angle( vec3_t* up )
{
	if ( !x && !y )
		return ang_t( 0, 0, 0 );

	float roll = 0;

	if ( up ) {
		vec3_t left = ( *up ).cross( *this );

		roll = deg( atan2f( left.z, ( left.y * x ) - ( left.x * y ) ) );
	}

	return ang_t( deg( atan2f( -z, sqrtf( x * x + y * y ) ) ), deg( atan2f( y, x ) ), roll );
}

ang_t& ang_t::sanitize( bool egnore_pitch ) {
	if ( !egnore_pitch )
		pitch = std::clamp( remainderf( pitch, 360.f ), -89.f, 89.f );
	yaw = std::clamp( remainderf( yaw, 360.f ), -180.f, 180.f );
	roll = std::clamp( remainderf( roll, 360.f ), -50.f, 50.f );

	return *this;
}

vec3_t ang_t::get_dir( vec3_t* right, vec3_t* up ) const {
	vec3_t ret = vec3_t( );
	/*vec3_t cos, sin;

	math::sincos( math::deg_to_rad( pitch ), sin.x, cos.x );
	math::sincos( math::deg_to_rad( yaw ), sin.y, cos.y );
	math::sincos( math::deg_to_rad( roll ), sin.z, cos.z );

	ret.x = cos.x * cos.y;
	ret.y = cos.x * sin.y;
	ret.z = -sin.x;

	if ( right ) {
		right->x = -sin.z * sin.x * cos.y + -cos.z * -sin.y;
		right->y = -sin.z * sin.x * sin.y + -cos.z * cos.y;
		right->z = -sin.z * cos.x;
	}

	if ( up ) {
		up->x = cos.z * sin.x * cos.y + -sin.z * -sin.y;
		up->y = cos.z * sin.x * sin.y + -sin.z * cos.y;
		up->z = cos.z * cos.x;
	}*/

	return ret;
}