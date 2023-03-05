#pragma once
#include "../../../main_includes.hpp"

namespace local_animations {
	void update_player_animations( );

	enum {
		REAL_ANGLE,
		FAKE_ANGLE,
		LOCAL_ANGLES
	};

	class c_local_data {
	public:
		anim_layer_t local_layers[ 13 ];
		std::array< float, 24 > local_poses;
		matrix_t* local_matrix;
	} inline m_local_data[ LOCAL_ANGLES ];
}