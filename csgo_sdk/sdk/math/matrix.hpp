#pragma once
#include <limits>
#include <DirectXMath.h>
#include "vectors.hpp"

class matrix_t {
public:
	matrix_t( ) {
	}

	matrix_t(
		const float m00, const float m01, const float m02, const float m03,
		const float m10, const float m11, const float m12, const float m13,
		const float m20, const float m21, const float m22, const float m23 ) {
		m_mat_val[0][0] = m00;
		m_mat_val[0][1] = m01;
		m_mat_val[0][2] = m02;
		m_mat_val[0][3] = m03;
		m_mat_val[1][0] = m10;
		m_mat_val[1][1] = m11;
		m_mat_val[1][2] = m12;
		m_mat_val[1][3] = m13;
		m_mat_val[2][0] = m20;
		m_mat_val[2][1] = m21;
		m_mat_val[2][2] = m22;
		m_mat_val[2][3] = m23;
	}

	//-----------------------------------------------------------------------------
	// Creates a matrix where the x axis = forward
	// the y axis = left, and the z axis = up
	//-----------------------------------------------------------------------------
	void init( const vec3_t& x_axis, const vec3_t& y_axis, const vec3_t& z_axis, const vec3_t& origin ) {
		m_mat_val[0][0] = x_axis.x;
		m_mat_val[0][1] = y_axis.x;
		m_mat_val[0][2] = z_axis.x;
		m_mat_val[0][3] = origin.x;
		m_mat_val[1][0] = x_axis.y;
		m_mat_val[1][1] = y_axis.y;
		m_mat_val[1][2] = z_axis.y;
		m_mat_val[1][3] = origin.y;
		m_mat_val[2][0] = x_axis.z;
		m_mat_val[2][1] = y_axis.z;
		m_mat_val[2][2] = z_axis.z;
		m_mat_val[2][3] = origin.z;
	}

	//-----------------------------------------------------------------------------
	// Creates a matrix where the x axis = forward
	// the y axis = left, and the z axis = up
	//-----------------------------------------------------------------------------
	matrix_t( const vec3_t& x_axis, const vec3_t& y_axis, const vec3_t& z_axis, const vec3_t& origin ) {
		init( x_axis, y_axis, z_axis, origin );
	}

	constexpr void set_forward( const vec3_t& forward ) {
		this->m_mat_val[0][0] = forward.x;
		this->m_mat_val[1][0] = forward.y;
		this->m_mat_val[2][0] = forward.z;
	}

	constexpr void set_left( const vec3_t& left ) {
		this->m_mat_val[0][1] = left.x;
		this->m_mat_val[1][1] = left.y;
		this->m_mat_val[2][1] = left.z;
	}

	constexpr void set_up( const vec3_t& up ) {
		this->m_mat_val[0][2] = up.x;
		this->m_mat_val[1][2] = up.y;
		this->m_mat_val[2][2] = up.z;
	}

	constexpr void set_origin( const vec3_t& origin ) {
		this->m_mat_val[0][3] = origin.x;
		this->m_mat_val[1][3] = origin.y;
		this->m_mat_val[2][3] = origin.z;
	}

	void invalidate( void ) {
		for ( int i = 0; i < 3; i++ ) {
			for ( int j = 0; j < 4; j++ ) {
				m_mat_val[i][j] = std::numeric_limits<float>::infinity( );
			}
		}
	}

	void angle_matrix( const vec3_t& angles ) {
		float sr, sp, sy, cr, cp, cy;
		DirectX::XMScalarSinCos( &sy, &cy, DirectX::XMConvertToDegrees( angles[1] ) );
		DirectX::XMScalarSinCos( &sp, &cp, DirectX::XMConvertToDegrees( angles[0] ) );
		DirectX::XMScalarSinCos( &sr, &cr, DirectX::XMConvertToDegrees( angles[2] ) );

		m_mat_val[0][0] = cp * cy;
		m_mat_val[1][0] = cp * sy;
		m_mat_val[2][0] = -sp;

		const float crcy = cr * cy;
		const float crsy = cr * sy;
		const float srcy = sr * cy;
		const float srsy = sr * sy;
		m_mat_val[0][1] = sp * srcy - crsy;
		m_mat_val[1][1] = sp * srsy + crcy;
		m_mat_val[2][1] = sr * cp;

		m_mat_val[0][2] = (sp * crcy + srsy);
		m_mat_val[1][2] = (sp * crsy - srcy);
		m_mat_val[2][2] = cr * cp;

		m_mat_val[0][3] = 0.0f;
		m_mat_val[1][3] = 0.0f;
		m_mat_val[2][3] = 0.0f;
	}

	void matrix_set_column( const vec3_t& in, const int column ) {
		m_mat_val[0][column] = in.x;
		m_mat_val[1][column] = in.y;
		m_mat_val[2][column] = in.z;
	}

	void angle_matrix( const vec3_t& angles, const vec3_t& position ) {
		angle_matrix( angles );
		matrix_set_column( position, 3 );
	}

	vec3_t get_x_axis( ) const {
		return at( 0 );
	}
	vec3_t get_y_axis( ) const {
		return at( 1 );
	}
	vec3_t get_z_axis( ) const {
		return at( 2 );
	}
	vec3_t get_origin( ) const {
		return at( 3 );
	}

	vec3_t at( const int i ) const {
		return vec3_t{ m_mat_val[0][i], m_mat_val[1][i], m_mat_val[2][i] };
	}

	float* operator[]( const int i ) {
		return m_mat_val[i];
	}
	const float* operator[]( const int i ) const {
		return m_mat_val[i];
	}
	float* base( ) {
		return &m_mat_val[0][0];
	}
	const float* base( ) const {
		return &m_mat_val[0][0];
	}

	float m_mat_val[3][4];
};

class v_matrix {
public:
	v_matrix( );
	v_matrix(
		float m00, float m01, float m02, float m03,
		float m10, float m11, float m12, float m13,
		float m20, float m21, float m22, float m23,
		float m30, float m31, float m32, float m33
	);

	// Creates a matrix where the x axis = forward
	// the y axis = left, and the z axis = up
	v_matrix( const vec3_t& forward, const vec3_t& left, const vec3_t& up );

	// Construct from a 3x4 matrix
	v_matrix( const matrix_t& matrix3x4 );

	// Set the values in the matrix.
	void init(
		float m00, float m01, float m02, float m03,
		float m10, float m11, float m12, float m13,
		float m20, float m21, float m22, float m23,
		float m30, float m31, float m32, float m33
	);


	// Initialize from a 3x4
	void init( const matrix_t& matrix3x4 );

	// array access
	float* operator[]( const int i ) {
		return m[i];
	}

	const float* operator[]( const int i ) const {
		return m[i];
	}

	// Get a pointer to m[ 0 ][ 0 ]
	float* base( ) {
		return &m[0][0];
	}

	const float* base( ) const {
		return &m[0][0];
	}

	void set_left( const vec3_t& left );
	void set_up( const vec3_t& up );
	void set_forward( const vec3_t& forward );

	void get_basis_vectors( vec3_t& forward, vec3_t& left, vec3_t& up ) const;
	void set_basis_vectors( const vec3_t& forward, const vec3_t& left, const vec3_t& up );

	// Get/Set the translation.
	vec3_t& get_translation( vec3_t& trans ) const;
	void set_translation( const vec3_t& trans );

	void pre_translate( const vec3_t& trans );
	void post_translate( const vec3_t& trans );

	matrix_t& as3x4( );
	const matrix_t& as3x4( ) const;
	void copy_from3x4( const matrix_t& m3x4 );
	void set3x4( matrix_t& matrix3x4 ) const;

	bool operator==( const v_matrix& src ) const;
	bool operator!=( const v_matrix& src ) const {
		return !(*this == src);
	}

	// Access the basis vectors.
	vec3_t get_left( ) const;
	vec3_t get_up( ) const;
	vec3_t get_forward( ) const;
	vec3_t get_translation( ) const;

	// Multiply by a 3D Vector (same as operator*).
	void v3_mul( const vec3_t& in, vec3_t& out ) const;

	// Multiply by a 4D Vector.
	//void  V4Mul( const c_vec4 &in, c_vec4 &out ) const;

	// Applies the rotation (ignores translation in the matrix). (This just calls VMul3x3).
	vec3_t apply_rotation( const vec3_t& vec ) const;

	// Multiply by a Vector (divides by w, assumes input w is 1).
	vec3_t operator*( const vec3_t& vec ) const;

	// Multiply by the upper 3x3 part of the matrix (ie: only apply rotation).
	vec3_t v_mul3x3( const vec3_t& vec ) const;

	// Apply the inverse (transposed) rotation (only works on pure rotation matrix)
	vec3_t v_mul3x3transpose( const vec3_t& vec ) const;

	// Multiply by the upper 3 rows.
	vec3_t v_mul4x3( const vec3_t& vec ) const;

	// Apply the inverse (transposed) transformation (only works on pure rotation/translation)
	vec3_t v_mul4x3_transpose( const vec3_t& vec ) const;


	// matrix->plane operations.
	//public:
	// Transform the plane. The matrix can only contain translation and rotation.
	//void  TransformPlane( const VPlane &inPlane, VPlane &outPlane ) const;

	// Just calls TransformPlane and returns the result.
	//VPlane  operator*(const VPlane &thePlane) const;

	// matrix->matrix operations.
	v_matrix& operator=( const v_matrix& other );

	// Add two matrices.
	const v_matrix& operator+=( const v_matrix& other );

	// Add/Subtract two matrices.
	v_matrix operator+( const v_matrix& other ) const;
	v_matrix operator-( const v_matrix& other ) const;

	// Negation.
	v_matrix operator-( ) const;

	// Return inverse matrix. Be careful because the results are undefined 
	// if the matrix doesn't have an inverse (ie: InverseGeneral returns false).
	v_matrix operator~( ) const;

	// matrix operations.

	// Set to identity.
	void identity( );
	bool is_identity( ) const;

	// The matrix.
	float m[4][4];
};

inline void matrix_get_column( const matrix_t& src, const int col, vec3_t& column ) {
	column.x = src[0][col];
	column.y = src[1][col];
	column.z = src[2][col];
}

inline void matrix_position( const matrix_t& matrix, vec3_t& position ) {
	matrix_get_column( matrix, 3, position );
}

inline void matrix_angles( const matrix_t& matrix, float* angles ) {
	float forward[3]{};
	float left[3]{};
	float up[3]{};

	//
	// Extract the basis vectors from the matrix. Since we only need the z
	// component of the up Vector, we don't get x and y.
	//
	forward[0] = matrix[0][0];
	forward[1] = matrix[1][0];
	forward[2] = matrix[2][0];
	left[0] = matrix[0][1];
	left[1] = matrix[1][1];
	left[2] = matrix[2][1];
	up[2] = matrix[2][2];

	const float xy_dist = sqrtf( forward[0] * forward[0] + forward[1] * forward[1] );

	// enough here to get angles?
	if ( xy_dist > 0.001f ) {
		// (yaw)	y = ATAN( forward.y, forward.x );		-- in our space, forward is the x axis
		angles[1] = DirectX::XMConvertToDegrees( atan2f( forward[1], forward[0] ) );

		// (pitch)	x = ATAN( -forward.z, sqrt(forward.x*forward.x+forward.y*forward.y) );
		angles[0] = DirectX::XMConvertToDegrees( atan2f( -forward[2], xy_dist ) );

		// (roll)	z = ATAN( left.z, up.z );
		angles[2] = DirectX::XMConvertToDegrees( atan2f( left[2], up[2] ) );
	}
	else // forward is mostly z, gimbal lock-
	{
		// (yaw)	y = ATAN( -left.x, left.y );			-- forward is mostly z, so use right for yaw
		angles[1] = DirectX::XMConvertToDegrees( atan2f( -left[0], left[1] ) );

		// (pitch)	x = ATAN( -forward.z, sqrt(forward.x*forward.x+forward.y*forward.y) );
		angles[0] = DirectX::XMConvertToDegrees( atan2f( -forward[2], xy_dist ) );

		// Assume no roll in this case as one degree of freedom has been lost (i.e. yaw == roll)
		angles[2] = 0;
	}
}

inline void matrix_angles( const matrix_t& matrix, vec3_t& angles ) {
	matrix_angles( matrix, &angles.x );
}

inline void matrix_angles( const matrix_t& matrix, vec3_t& angles, vec3_t& position ) {
	matrix_angles( matrix, angles );
	matrix_position( matrix, position );
}
