#pragma once
#include "../interfaces/classes/i_client_entity.h"
#include "../../utils/utils.h"
#include "../../utils/netvars/netvar_manager.h"
#include "enums.h"

struct bone_cache_t {
	matrix_t* m_cached_bones;
	char			pad0[ 8 ];
	uint32_t		m_cached_bones_count;
};

class c_base_entity;
class c_base_animating;

struct bone_accessor_t {
	c_base_animating* m_animating;
	matrix_t* m_bones;
	int					m_readable_bones;
	int					m_writable_bones;
};

class c_studio_hdr;

struct anim_layer_t {
	float			m_anim_time;
	float			m_fade_out_time;
	c_studio_hdr* m_studio_hdr;
	int				m_dispatched_src;
	int				m_dispatched_dst;
	int				m_order;
	int				m_sequence;
	float			m_prev_cycle;
	float			m_weight;
	float			m_weight_delta_rate;
	float			m_playback_rate;
	float			m_cycle;
	c_base_entity* m_owner;
	int				m_invalidate_physics_bits;
};

class c_base_combat_weapon;

class c_anim_state {
public:
	VFUNC_SIG( reset( ), "client.dll", "56 6A 01 68 ? ? ? ? 8B F1", void( __thiscall* )( void* ) );
	VFUNC_SIG( create( c_base_entity* entity ), "client.dll", "55 8B EC 56 8B F1 B9 ? ? ? ? C7 46", void( __thiscall* )( void*, c_base_entity* ), entity );
	VFUNC_SIG( get_weapon_prefix( ), "client.dll", "53 56 57 8B F9 33 F6 8B 4F 60 8B 01 FF 90", const char* ( __thiscall* )( void* ) );

	__forceinline float get_body_yaw_modifier( ) const {
		const auto walk_speed = std::clamp( m_speed_as_portion_of_walk_speed, 0.f, 1.f );

		const auto run_speed = ( ( m_walk_to_run_transition * -0.30000001f ) - 0.19999999f ) * walk_speed;
		const auto modifier = run_speed + 1.f;

		if ( m_duck_amount > 0.f ) {
			const auto crouch_walk_speed = std::clamp( m_speed_as_portion_of_crouch_speed, 0.f, 1.f );

			return modifier + ( m_duck_amount * crouch_walk_speed ) * ( 0.5f - modifier );
		}

		return modifier;
	}

	__forceinline void update( ang_t angle ) {
		static const auto update_fn = utils::find_sig( "client.dll", "55 8B EC 83 E4 F8 83 EC 18 56 57 8B F9 F3 0F 11 54 24" );
		if ( !update_fn )
			return;

		__asm {
			push 0

			mov ecx, this

			movss xmm1, dword ptr[ angle + 4 ]
			movss xmm2, dword ptr[ angle ]

			call update_fn
		}
	}

	char					pad0[ 4 ];
	bool					m_reset;
	char					pad1[ 3 ];
	int						m_tick_count;
	char					pad2[ 84 ];
	c_base_animating* m_base_entity;
	c_base_combat_weapon* m_active_weapon;
	c_base_combat_weapon* m_last_active_weapon;
	float					m_last_cur_time;
	int						m_last_frame_count;
	float					m_delta_time;
	float					m_eye_yaw;
	float					m_eye_pitch;
	float					m_foot_yaw;
	float					m_last_foot_yaw;
	float					m_move_yaw;
	float					m_move_yaw_ideal;
	float					m_move_yaw_cur_to_ideal;
	char					pad3[ 4 ];
	float					m_feet_cycle;
	float					m_feet_weight;
	char					pad4[ 4 ];
	float					m_duck_amount;
	float					m_duck_additional;
	char					pad5[ 4 ];
	vec3_t					m_origin;
	vec3_t					m_last_origin;
	vec3_t					m_velocity;
	vec3_t					m_velocity_normalized;
	vec3_t					m_velocity_normalized_non_zero;
	float					m_speed_2d;
	float					m_up_velocity;
	float					m_speed_as_portion_of_run_speed;
	float					m_speed_as_portion_of_walk_speed;
	float					m_speed_as_portion_of_crouch_speed;
	float					m_time_since_started_moving;
	float					m_time_since_stopped_moving;
	bool					m_on_ground;
	bool					m_landing;
	char					pad6[ 6 ];
	float					m_time_since_in_air;
	float					m_left_ground_height;
	float					m_land_anim_multiplier;
	float					m_walk_to_run_transition;
	char					pad7[ 4 ];
	float					m_in_air_smooth_value;
	bool					m_on_ladder;
	char					pad8[ 47 ];
	float					m_last_velocity_test_time;
	vec3_t					m_last_velocity;
	vec3_t					m_dst_acceleration;
	vec3_t					m_acceleration;
	float					m_acceleration_weight;
	char					pad9[ 12 ];
	float					m_strafe_weight;
	char					pad10[ 4 ];
	float					m_strafe_cycle;
	int						m_strafe_sequence;
	char					pad11[ 388 ];
	float					m_adjusted_eye_pos_height;
	bool					m_should_adjust_eye_pos_height;
	char					pad12[ 11 ];
	float					m_min_body_yaw;
	float					m_max_body_yaw;
	float					m_min_body_pitch;
	float					m_max_body_pitch;
	int						m_anim_set_version;
};