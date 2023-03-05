#pragma once
#include "../../math/vectors.hpp"
#include "../../../utils/utils.hpp"

class i_render_view {
public:
	void set_blend( const float blend ) {
		utils::call_vfunc<void( __thiscall* )( void*, float )>( this, 4 )( this, blend );
	}

	void set_color_modulation( const float blend ) {
		utils::call_vfunc<void( __thiscall* )( void*, float )>( this, 6 )( this, blend );
	}
};