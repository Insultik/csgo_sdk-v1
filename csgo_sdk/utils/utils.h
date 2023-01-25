#pragma once 
#include <cstdint>
#include <string>
#include <wtypes.h>
#include <array>
#include <cstddef>
#include <memory>
#include <vector>
#include "../sdk/other/utl/utl.h"

#define VFUNC(func, index, type, ...) __forceinline auto func { return utils::call_vfunc<type>(this, index)(this, __VA_ARGS__); };
#define VFUNC_SIG(func, module_name, sig, type, ...) __forceinline auto func { static const auto fn = (type)utils::find_sig(module_name, sig); return fn(this, __VA_ARGS__); };
#define round_to_int( value ) ( int ) (  0.5f + value ) 

float ticks_to_time( int ticks );

int time_to_ticks( float time );

#define _( text ) text

template <typename T>
struct bit_flag_t {
	bit_flag_t( ) = default;
	bit_flag_t( const T& value ) { m_value = value; }

	__forceinline bool has( const T& value ) const { return m_value & value; }

	__forceinline void add( const T& value ) { m_value |= value; }

	__forceinline void remove( const T& value ) { m_value &= ~value; }

	__forceinline void clear( ) { m_value = {}; }

	__forceinline bool empty( ) const { return m_value == std::numeric_limits<T>::quiet_NaN( ); }

	__forceinline operator T( ) const { return m_value; }

	__forceinline bit_flag_t<T>& operator=( const bit_flag_t<T>& value ) {
		m_value = value.m_value;

		return *this;
	}

	__forceinline T& operator=( const T& value ) {
		m_value = value;

		return m_value;
	}

	T m_value = {};
};

namespace utils {
	inline unsigned int get_virtual( void* _class, unsigned int index ) {
		return static_cast< unsigned int >( ( *reinterpret_cast< int** >( _class ) )[ index ] );
	}

	uint8_t* find_sig( const std::string& module_array, const std::string& byte_array );
	template <typename T>
	[[nodiscard]] static __forceinline T call_vfunc( void* instance, std::size_t index ) {
		return ( *static_cast< T** >( instance ) )[ index ];
	}
}