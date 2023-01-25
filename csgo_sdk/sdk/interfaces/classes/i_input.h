#pragma once
#include "../../math/vectors.h"
#include "../../../utils/utils.h"
#include "../../other/cmd.h"

class i_input {
public:
	VFUNC( get_user_cmd( int slot, int sequence_number ), 8, c_user_cmd* ( __thiscall* )( void*, int, int ), slot, sequence_number );

	c_user_cmd* get_user_cmd( int sequence_number ) { return &m_commands[ sequence_number % 150 ]; };
	c_verified_user_cmd* get_verified_user_cmd( int sequence_number ) { return &m_verified_commands[ sequence_number % 150 ]; };

	char					pad0[ 12 ];
	bool					m_track_ir_available;
	bool					m_mouse_initialized;
	bool					m_mouse_active;
	char					pad1[ 154 ];
	bool					m_camera_in_third_person;
	char					pad2[ 2 ];
	vec3_t					m_camera_offset;
	char					pad3[ 56 ];
	c_user_cmd* m_commands;
	c_verified_user_cmd* m_verified_commands;
};