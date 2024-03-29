#pragma once
#include "../../../main_includes.hpp"

namespace eng_prediction {
	struct {
		float m_cur_time {}, m_frame_time {};
	} inline m_backup {};

	struct net_vars_t {
		__forceinline void restore( const int cmd_number ) const;

		__forceinline void store( const int cmd_number );

		int			m_cmd_number {};

		float		m_view_offset_z {};
		vec3_t	m_aim_punch {}, m_aim_punch_vel {};
	};

	struct local_data_t {
		__forceinline void init( const c_user_cmd* user_cmd );

		__forceinline void save( const int cmd_number );

		__forceinline void store_anim( );

		__forceinline void restore_anim( const bool layers ) const;

		float					m_spawn_time {}, m_abs_yaw {};

		int						m_tick_base {},
			m_adjusted_tick_base {}, m_shift_amount {};
		bool					m_override_tick_base {}, m_restore_tick_base {};

		vec3_t					m_move {};
		c_user_cmd*				m_user_cmd {};

		c_anim_state			m_anim_state {};

		anim_layer_t			m_anim_layers[ 13 ];
		float					m_pose_params[ 24 ];

		struct {
			vec3_t			m_eye_angles {},
				m_aim_punch {}, m_view_punch {};

			vec3_t				m_origin {}, m_abs_origin {},
				m_obb_min {}, m_obb_max {},
				m_velocity {}, m_view_offset {},
				m_aim_punch_vel {}, m_abs_velocity {};

			bool				m_strafing {}, m_scoped {}, m_walking {};

			int					m_move_state {}, m_tick_base {};

			float				m_duck_amount {}, m_duck_speed {},
				m_third_person_recoil {}, m_lby {};

			bit_flag_t< int>	m_flags {};
			valve::e_move_type	m_move_type {};
		}						m_net_vars {}, m_pred_net_vars {};
	};
};

