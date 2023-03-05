#pragma once
#include "../../../main_includes.hpp"

namespace movement {
	void on_createmove(  );
	void rotate( ang_t& wish_view );
	void bunny_hop( );
	void auto_strafe( );

	inline ang_t m_view;
}