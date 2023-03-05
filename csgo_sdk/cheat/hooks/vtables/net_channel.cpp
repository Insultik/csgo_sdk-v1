#include "../hooks.hpp"

void __cdecl hooks::net_channel::process_packet::fn( void* packet, bool header ) {
	if ( !interfaces::engine->get_net_channel( ) )
		return get_original( packet, header );

	/* get this from CL_FireEvents string "Failed to execute event for classId" in engine.dll */
	auto event = *( event_info_t** ) ( uintptr_t( interfaces::client_state ) + 0x4E6C );
	while ( event ) {
		event->m_delay = 0.0f;
		event = event->m_next;
	}

	interfaces::engine->fire_events( );
}