#include "antiaim.hpp"

/*
	 * @note: fyi: https://www2.clarku.edu/faculty/djoyce/complex/polarangle.gif
	 *
	 *	 \     90|450    /
	 *	   \     |     /
	 *	135  \   |   /  45,405
	 *	       \ | /
	 *	-180,180 | 0,360,720
	 *	--------------------
	 *	       / | \
	 *	-135 /   |   \ -45,315
	 *	   /     |     \
	 *	 /    -90|270    \
	 *
*/

void antiaim::on_createmove( ) {
	if ( ctx::m_send_packet )
		m_rotate_side = !m_rotate_side;

	if ( !ctx::m_local.alive( ) || !ctx::m_weapon.get( ) )
		return;

	if ( ctx::m_local.get( )->is_shooting( ) || ( ctx::m_cmd->m_buttons.has( in_use ) && ctx::m_local.get( )->is_defusing( ) ) )
		return;

	ctx::m_cmd->m_view_angles = ang_t( get_pitch( ), get_yaw( ) + get_fake_yaw( ), get_roll( ) );
}

float antiaim::get_pitch( ) {
	if ( ctx::m_cmd->m_buttons.has( in_use ) )
		return ctx::m_cmd->m_view_angles.pitch;

	return 89.f;
}

float antiaim::get_yaw( ) {
	if ( ctx::m_cmd->m_buttons.has( in_use ) )
		return ctx::m_cmd->m_view_angles.yaw;

	float base_yaw = get_target_based_yaw( );
	base_yaw += 180.f;

	//base_yaw += m_rotate_side ? 12.f : -12.f;
	return base_yaw;
}

float antiaim::get_fake_yaw( ) {
	if ( ctx::m_send_packet )
		return 0.f;

	return 58.f * GetKeyState( VK_SHIFT ) ? 1.f : -1.f;
}

float antiaim::get_roll( ) {
	return 0.f;
}

float antiaim::get_target_based_yaw( ) {
	std::vector< std::pair< float, float > > m_players_fov { }; m_players_fov.clear( );
	for ( int i = 1; i < interfaces::global_vars->m_max_clients; i++ ) {
		c_cs_player* player = c_cs_player::get_player( i );
		if ( !player || !player->is_valid( valid_state_enemy ) || !player->get_active_weapon( ) )
			continue;

		auto* weapon = player->get_active_weapon( );
		if ( !weapon->is_weapon( ) || weapon->get_ammo( ) < 1 )
			continue;

		vec3_t pos = player->get_abs_origin( ); ang_t angle = math::calc_angle( ctx::m_local.get()->get_origin( ), pos );
		m_players_fov.push_back( { math::get_fov( ctx::m_angles.view, angle ), angle.yaw } );
	}

	auto sort_players = [ ]( std::pair< float, float > one, std::pair< float, float > two ) -> bool {
		return one.first < two.first;
	};

	if ( m_players_fov.empty( ) )
		return ctx::m_cmd->m_view_angles.yaw;

	if ( m_players_fov.size( ) > 1 )
		std::sort( m_players_fov.begin( ), m_players_fov.end( ), sort_players );

	return m_players_fov.front( ).second;
}

float antiaim::get_best_yaw( ) {
	return 0.f;
}