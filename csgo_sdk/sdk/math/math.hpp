#pragma once
#include "../../utils/utils.hpp"
#include "vectors.hpp"
#include "matrix.hpp"
#include <cmath>
#include <algorithm>
#include <DirectXMath.h>
#include <array>
#include <vector>
#include <map>

namespace math {
	inline const float m_pi = 3.14159265358979323846f;
	inline const float m_rad_pi = 180.f / m_pi;
	inline const float m_deg_pi = m_pi / 180.f;
	inline const float m_valve_rand_max = 0x7fff;
	inline const float m_round_error = std::numeric_limits<float>::round_error( );

	__forceinline float random_float( float min, float max ) {
		static auto random_float_fn = reinterpret_cast< float ( * ) ( float, float ) >( GetProcAddress( GetModuleHandleA( "vstdlib.dll" ), "RandomFloat" ) );
		return random_float_fn( min, max );
	}

	__forceinline int random_int( int min, int max ) {
		static auto random_float_fn = reinterpret_cast< int ( * ) ( int, int ) >( GetProcAddress( GetModuleHandleA( "vstdlib.dll" ), "RandomInt" ) );
		return random_float_fn( min, max );
	}

	__forceinline void random_seed( int seed ) {
		static auto random_float_fn = ( decltype( &random_seed ) ) ( GetProcAddress( GetModuleHandleA( "vstdlib.dll" ), "RandomSeed" ) );
		return random_float_fn( seed );
	}

	__forceinline float rad_to_deg( float rad ) {
		return rad * m_rad_pi;
	}

	__forceinline float deg_to_rad( float deg ) {
		return deg * m_deg_pi;
	}

	__forceinline float get_fov( const ang_t& view, const ang_t& aim_at ) {
		vec3_t ang { }, aim { };
		aim_at.get_dir( &ang );
		view.get_dir( &aim );

		return rad_to_deg( acos( aim.dot( ang ) / aim.length_sqr( ) ) );
	}

	__forceinline ang_t calc_angle( const vec3_t& vecSource, const vec3_t& vecDestination ) {
		ang_t angles;
		vec3_t delta = vec3_t( ( vecSource[ 0 ] - vecDestination[ 0 ] ), ( vecSource[ 1 ] - vecDestination[ 1 ] ), ( vecSource[ 2 ] - vecDestination[ 2 ] ) );
		float hyp = sqrtf( delta[ 0 ] * delta[ 0 ] + delta[ 1 ] * delta[ 1 ] );
		angles[ 0 ] = ( float ) ( atan( delta[ 2 ] / hyp ) * ( 180.0f / m_pi ) );
		angles[ 1 ] = ( float ) ( atan( delta[ 1 ] / delta[ 0 ] ) * ( 180.0f / m_pi ) );
		angles[ 2 ] = 0.f;
		if ( delta[ 0 ] >= 0.f )
			angles[ 1 ] += 180.f;

		return angles;
	}

	double __forceinline __declspec ( naked ) __fastcall sin( double x ) {
		__asm {
			fld	qword ptr[ esp + 4 ]
			fsin
			ret	8
		}
	}

	double __forceinline __declspec ( naked ) __fastcall cos( double x ) {
		__asm {
			fld	qword ptr[ esp + 4 ]
			fcos
			ret	8
		}
	}

	__forceinline void sin_cos( float rad, float& sin, float& cos ) {
		sin = math::sin( rad );
		cos = math::cos( rad );
	}

	double __forceinline __declspec ( naked ) __fastcall atan2( double y, double x ) {
		__asm {
			fld	qword ptr[ esp + 4 ]
			fld	qword ptr[ esp + 12 ]
			fpatan
			ret	16
		}
	}

	double __forceinline __declspec ( naked ) __fastcall atan( double x ) {
		__asm {
			fld	qword ptr[ esp + 4 ]
			fld1
			fpatan
			ret	8
		}
	}

	double __forceinline __declspec ( naked ) __fastcall asin( double x ) {
		__asm {
			fld	qword ptr[ esp + 4 ]
			fld	st
			fabs
			fcom dword ptr[ m_round_error ]
			fstsw ax
			sahf
			jbe skip

			fld1
			fsubrp st( 1 ), st( 0 )
			fld	st
			fadd st( 0 ), st( 0 )
			fxch st( 1 )
			fmul st( 0 ), st( 0 )
			fsubp st( 1 ), st( 0 )
			jmp	end

			skip :
			fstp st( 0 )
				fld	st( 0 )
				fmul st( 0 ), st( 0 )
				fld1
				fsubrp st( 1 ), st( 0 )

				end :
				fsqrt
				fpatan
				ret	8
		}
	}

	double __forceinline __declspec ( naked ) __fastcall acos( double x ) {
		__asm {
			fld	qword ptr[ esp + 4 ]
			fld1
			fchs
			fcomp st( 1 )
			fstsw ax
			je skip

			fld	st( 0 )
			fld1
			fsubrp st( 1 ), st( 0 )
			fxch st( 1 )
			fld1
			faddp st( 1 ), st( 0 )
			fdivp st( 1 ), st( 0 )
			fsqrt
			fld1
			jmp	end

			skip :
			fld1
				fldz

				end :
			fpatan
				fadd st( 0 ), st( 0 )
				ret	8
		}
	}

	double __forceinline __declspec ( naked ) __fastcall floor( double x ) {
		__asm {
			fld	qword ptr[ esp + 4 ]
			fld1
			fld	st( 1 )
			fprem
			sub	esp, 4
			fst	dword ptr[ esp ]
			fxch st( 2 )
			mov	eax, [ esp ]
			cmp eax, 80000000h
			jbe end
			fsub st, st( 1 )

			end:
			fsub st, st( 2 )
				fstp st( 1 )
				fstp st( 1 )
				pop	eax
				ret	8
		}
	}
}