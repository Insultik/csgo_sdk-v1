#include "features.hpp"

void features::draw_features( ) {
	players::instance( );
}

void features::create_move( ) {

	movement::on_createmove( );
	antiaim::on_createmove( );
	ctx::m_send_packet = interfaces::client_state->m_choked_commands > 5;
	{

	}
	movement::rotate( ctx::m_angles.view );

}

void features::frame_stage_notify( int stage ) {

	switch ( stage ) {
		case frame_start:

			break;

		case frame_net_update_start:

			break;

		case frame_net_update_end:
			lag_comp::instance( );
			break;

		case frame_net_update_postdataupdate_start:

			break;

		case frame_net_update_postdataupdate_end:

			break;

		case frame_render_start:
			local_animations::update_player_animations( );
			break;

		case frame_render_end:

			break;
	}

}