#include "lagcomp.hpp"

void lag_comp::instance( ) {
	if ( !interfaces::engine->is_connected( ) || interfaces::client_state->m_delta_tick < 0 ) 
		return;
	
	console::print( std::to_string( listeners::get_players().size( ) ) );
}