#pragma once
#include "../../../utils/utils.hpp"

namespace vgui {
	typedef unsigned long hfont;
	typedef unsigned int vpanel;
};

class i_surface {
public:
	__forceinline void unlock_cursor( ) {
		return utils::call_vfunc< void( __thiscall* )( void* ) >( this, 66 )( this );
	}
	__forceinline void lock_cursor( ) {
		return utils::call_vfunc< void( __thiscall* )( void* ) >( this, 67 )( this );
	}
	__forceinline void draw_set_color( int x1, int y1, int x2, int y2 = 255) {
		return utils::call_vfunc< void( __thiscall* )( void*, int, int, int, int ) >( this, 15 )( this, x1, y1, x2, y2 );
	}
	__forceinline void draw_line( int x1, int y1, int x2, int y2 ) {
		return utils::call_vfunc< void( __thiscall* )( void*, int, int, int, int ) >( this, 19 )( this, x1, y1, x2, y2 );
	}
};