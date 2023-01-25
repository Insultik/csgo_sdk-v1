#pragma once
#include "../../math/vectors.h"
#include "../../../utils/utils.h"

class i_render_view {
public:
	void set_blend( const float blend ) {
		utils::call_vfunc<void( __thiscall* )( void*, float )>( this, 4 )( this, blend );
	}

	void set_color_modulation( const float blend ) {
		utils::call_vfunc<void( __thiscall* )( void*, float )>( this, 6 )( this, blend );
	}
};