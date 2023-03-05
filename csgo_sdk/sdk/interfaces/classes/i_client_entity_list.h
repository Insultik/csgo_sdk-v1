#pragma once
#include "../../other/utl/utl.hpp"
#include "../../other/handle/base_handle.hpp"

class i_client_networkable;
class i_client_entity;
class c_base_entity;

class i_client_entity_listener {
public:
	virtual void on_entity_created( c_base_entity* pEntity ) { }
	virtual void on_entity_deleted( c_base_entity* pEntity ) { }
};

class i_client_entity_list {
public:
	virtual i_client_networkable* get_client_networkable( int entnum ) = 0;
	virtual void* vtablepad0x1( void ) = 0;
	virtual void* vtablepad0x2( void ) = 0;
	virtual i_client_entity* get_client_entity( int ent_num ) = 0;
	virtual i_client_entity* get_client_entity_from_handle( c_base_handle ent ) = 0;
	virtual int number_of_entities( bool include_non_networkable ) = 0;
	virtual int get_highest_entity_index( void ) = 0;
	virtual void set_max_entities( int max_ents ) = 0;
	virtual int get_max_entities( ) = 0;

	void add_listener_entity( i_client_entity_listener* listener ) {
		m_entity_listeners.add_to_tail( listener );
	}

	void remove_listener_entity( i_client_entity_listener* listener ) {
		m_entity_listeners.find_and_remove( listener );
	}

private:
	c_utl_vector< i_client_entity_listener* > m_entity_listeners;
};