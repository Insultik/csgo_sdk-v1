#pragma once
#include <cstdint>
#include "../math/vectors.hpp"
#include "../../utils/utils.hpp"

class c_user_cmd {
public:
	virtual	~c_user_cmd( ) = default;

	int						m_command_number;
	int						m_tick_count;
	ang_t					m_view_angles;
	vec3_t					m_aim_direction;
	float					m_forward_move;
	float					m_side_move;
	float					m_up_move;
	bit_flag_t<uint32_t>	m_buttons;
	char					m_impulse;
	int						m_weapon_select;
	int						m_weapon_sub_type;
	int						m_random_seed;
	short					m_mouse_dx;
	short					m_mouse_dy;
	bool					m_predicted;
	char					pad0[ 24 ];
	VFUNC_SIG( get_checksum( ), "client.dll", "53 8B D9 83 C8", uint32_t( __thiscall* )( void* ) )
};

class c_verified_user_cmd {
public:
	c_user_cmd m_cmd{};
	std::uint32_t m_crc{};
};

