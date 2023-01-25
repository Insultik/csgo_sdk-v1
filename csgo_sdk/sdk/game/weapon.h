#pragma once
#include "../interfaces/classes/i_client_entity.h"
#include "../../utils/utils.h"
#include "../../utils/netvars/netvar_manager.h"
#include "enums.h"

class c_cs_weapon_data {
public:
	char	pad0[ 4 ];
	char*   m_console_name;
	char	pad1[ 12 ];
	int		m_max_clip1;
	int		m_max_clip2;
	int		m_default_clip1;
	int		m_default_clip2;
	int		m_primary_reserve_ammo_max;
	int		m_secondary_reserve_ammo_max;
	char*   m_world_model;
	char*   m_view_model;
	char*   m_dropped_model;
	char	pad2[ 80 ];
	char*   m_hud_name;
	char*   m_weapon_name;
	char	pad3[ 2 ];
	bool	m_is_melee_weapon;
	char	pad4[ 9 ];
	float	m_weapon_weight;
	char	pad5[ 40 ];
	int		m_weapon_type;
	char	pad6[ 4 ];
	int		m_weapon_price;
	int		m_kill_award;
	char	pad7[ 4 ];
	float	m_cycle_time;
	float	m_cycle_time_alt;
	char	pad8[ 8 ];
	bool	m_full_auto;
	char	pad9[ 3 ];
	int		m_damage;
	float	m_head_shot_multiplier;
	float	m_armor_ratio;
	int		m_bullets;
	float	m_penetration;
	char	pad10[ 8 ];
	float	m_range;
	float	m_range_modifier;
	float	m_throw_velocity;
	char	pad11[ 12 ];
	bool	m_has_silencer;
	char	pad12[ 11 ];
	char*   m_bullet_type;
	float	m_max_speed;
	float	m_max_speed_alt;
	char	pad13[ 4 ];
	float	m_spread;
	float	m_spread_alt;
	float	m_inaccuracy_crouch;
	float	m_inaccuracy_crouch_alt;
	float	m_inaccuracy_stand;
	float	m_inaccuracy_stand_alt;
	float	m_inaccuracy_jump_initial;
	float	m_inaccuracy_jump_apex;
	float	m_inaccuracy_jump;
	float	m_inaccuracy_jump_alt;
	float	m_inaccuracy_land;
	float	m_inaccuracy_land_alt;
	float	m_inaccuracy_ladder;
	float	m_inaccuracy_ladder_alt;
	float	m_inaccuracy_fire;
	float	m_inaccuracy_fire_alt;
	float	m_inaccuracy_move;
	float	m_inaccuracy_move_alt;
	float	m_inaccuracy_reload;
	int		m_recoil_seed;
	float	m_recoil_angle;
	float	m_recoil_angle_alt;
	float	m_recoil_angle_variance;
	float	m_recoil_angle_variance_alt;
	float	m_recoil_magnitude;
	float	m_recoil_magnitude_alt;
	float	m_recoil_magnitude_variance;
	float	m_recoil_magnitude_variance_alt;
};

enum e_cs_weapon_type {
	weapon_type_knife,
	weapon_type_pistol,
	weapon_type_smg,
	weapon_type_rifle,
	weapon_type_shotgun,
	weapon_type_sniper,
	weapon_type_machine_gun,
	weapon_type_c4,
	weapon_type_place_holder,
	weapon_type_grenade,
	weapon_type_unknown,
	weapon_type_medishot,
	weapon_type_fists,
	weapon_type_breach_charge,
	weapon_type_bump_mine,
	weapon_type_tablet,
	weapon_type_melee
};