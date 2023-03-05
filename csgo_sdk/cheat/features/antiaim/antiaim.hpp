#pragma once
#include "../../../main_includes.hpp"

namespace antiaim {
	void on_createmove( );

	float get_pitch( );
	float get_yaw( );
	float get_fake_yaw( );
	float get_roll( );

	float get_target_based_yaw( );
	float get_best_yaw( );

	inline bool m_rotate_side { };
}