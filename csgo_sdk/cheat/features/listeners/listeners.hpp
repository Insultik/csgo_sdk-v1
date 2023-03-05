#pragma once
#include "../../../main_includes.hpp"

enum listener_ent_t {
	ent_weapon = 0,
	ent_grenade,
	ent_player,
	ent_fog,
	ent_tonemap,
};

namespace listeners {
	struct entity_info_t {
		c_cs_player* m_entity;
		int m_idx;
		int m_class_id;

		entity_info_t( ) : m_entity( nullptr ), m_idx( -1 ), m_class_id( -1 ) { }

		entity_info_t( c_base_entity* ent ) {
			m_idx = ent->get_index( );
			m_entity = ( c_cs_player* )ent;
			m_class_id = ent->get_client_class( )->m_class_id;
		}
	};

	class c_custom_listener : public i_client_entity_listener {
	public:
		void on_entity_created( c_base_entity* ent ) override;
		void on_entity_deleted( c_base_entity* ent ) override;

		bool instance( );
		void reset( );

		std::vector< entity_info_t > m_entities[ 5 ];
	};

	inline c_custom_listener m_listener; 
	
	__forceinline std::vector< entity_info_t > get( listener_ent_t ent_type = ent_player ) {
		return m_listener.m_entities[ ent_type ];
	}

	__forceinline std::vector< entity_info_t > get_players( ) {
		return m_listener.m_entities[ ent_player ];
	}

	__forceinline std::vector< entity_info_t > get_projectiles( ) {
		return m_listener.m_entities[ ent_grenade ];
	}

	__forceinline std::vector< entity_info_t > get_weapons( ) {
		return m_listener.m_entities[ ent_weapon ];
	}
};

