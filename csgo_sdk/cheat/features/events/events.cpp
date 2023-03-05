#include "events.hpp"

#define add_callback(name, fn) m_callbacks[HASH(name)] = fn; interfaces::event_manager->add_listener(&m_listener, _(name), false);

void events::c_listener::fire_game_event( i_game_event* event ) { 
	m_callbacks.at( HASH( event->get_name( ) ) )( event );
}

bool events::instance( ) {
	add_callback( "player_hurt", player_hurt );
	return true;
}

void events::reset( ) {
	interfaces::event_manager->remove_listener( &m_listener );
}