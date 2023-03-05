#include "listeners.hpp"

bool is_grenade( const int& class_id ) {
	switch ( class_id ) {
		case class_id_base_cs_grenade_projectile:
		case class_id_breach_charge_projectile:
		case class_id_bump_mine_projectile:
		case class_id_decoy_projectile:
		case class_id_molotov_projectile:
		case class_id_sensor_grenade_projectile:
		case class_id_smoke_grenade_projectile:
		case class_id_snowball_projectile:
		case class_id_inferno:
			return true;
	}
	return false;
}

bool is_bomb( int class_id ) {
	if ( class_id == class_id_c_c4 || class_id == class_id_planted_c4 )
		return true;

	return false;
}

bool is_weapon( c_base_entity* entity, int class_id ) {
	if ( is_bomb( class_id ) )
		return true;

	if ( entity->is_weapon_entity( ) )
		return true;

	return false;
}

bool listeners::c_custom_listener::instance( ) {
	if ( !interfaces::entity_list )
		return false;

	interfaces::entity_list->add_listener_entity( this );
	return true;
}

void listeners::c_custom_listener::reset( ) {
	interfaces::entity_list->remove_listener_entity( this );
}

void listeners::c_custom_listener::on_entity_created( c_base_entity* ent ) {
	if ( not ent )
		return;

	const int idx = ent->get_index( );
	const auto client_class = ent->get_client_class( );
	if ( !client_class )
		return;
	
	if ( !ent->is_player( ) && !is_weapon( ent, client_class->m_class_id ) && !is_grenade( client_class->m_class_id ) && client_class->m_class_id != class_id_fog_controller && client_class->m_class_id != class_id_env_tonemap_controller ) 
		return;

	if ( ent->is_player( ) )
		m_entities[ ent_player ].push_back( entity_info_t( ent ) );

	if ( is_weapon( ent, client_class->m_class_id ) )
		m_entities[ ent_weapon ].push_back( entity_info_t( ent ) );

	if ( is_grenade( client_class->m_class_id ) )
		m_entities[ ent_grenade ].push_back( entity_info_t( ent ) );

	if ( client_class->m_class_id == class_id_fog_controller )
		m_entities[ ent_fog ].push_back( entity_info_t( ent ) );

	if ( client_class->m_class_id == class_id_env_tonemap_controller )
		m_entities[ ent_tonemap ].push_back( entity_info_t( ent ) );
}

void erase_elements( int index, std::vector<listeners::entity_info_t>& info ) {
	const auto it = std::find_if( info.begin( ), info.end( ), [ & ]( const listeners::entity_info_t& data ) { return data.m_idx == index; } );

	if ( it == info.end( ) )
		return;

	info.erase( it );
}

void listeners::c_custom_listener::on_entity_deleted( c_base_entity* ent ) {
	if ( !ent )
		return;

	int index = ent->get_index( );
	if ( index < 0 )
		return;

	for ( int i = 0; i < 5; i++ )
		erase_elements( index, this->m_entities[ i ] );
}