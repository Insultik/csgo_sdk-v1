#include "players.hpp"

void players::instance( ) {
	for ( auto& player : listeners::get_players( ) ) {
		player_esp_data_t& data = player_data.at( player.m_idx );
		if ( !player.m_entity->is_alive( ) || player.m_entity->is_enemy( ) ) {
			data.invalidate( );
			continue;
		}

		float max_alpha_amount = 1.f;
		if ( player.m_entity->is_immune( ) ) max_alpha_amount = 0.52f;
		else if ( player.m_entity->is_dormant( ) ) max_alpha_amount = 0.64f;

		data.m_alpha = std::lerp( data.m_alpha, max_alpha_amount, interfaces::global_vars->m_frame_time * 8.f );
		data.m_health = std::lerp( data.m_health, player.m_entity->get_health( ), interfaces::global_vars->m_frame_time * 8.f );

		if ( auto weapon = player.m_entity->get_active_weapon(); weapon != nullptr )
			data.m_ammo = std::lerp( data.m_ammo, weapon->get_ammo( ), interfaces::global_vars->m_frame_time * 8.f );

		if ( data.m_box->m_alpha = data.m_alpha; !data.m_alpha || !data.m_box->calc_box( player.m_entity ) )
			continue;

		data.m_box->box( color_t::white( ) );
		data.m_box->bar( 100, round_to_int( data.m_health ), color_t::green( ), c_bounding_box::pos_left );
		data.m_box->text( "Username", color_t::white( ), c_bounding_box::pos_top, fonts::verdana_14 );
	}
}