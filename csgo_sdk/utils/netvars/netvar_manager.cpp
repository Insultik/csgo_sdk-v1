#include "netvar_manager.hpp"
#include <ostream>

namespace net_vars {

	std::unordered_map< std::string, int > m_client_ids;
	std::unordered_map< std::string, std::unordered_map< std::string, netvar_data_t > > m_offsets;

	std::vector< std::string > split( std::string to_split, std::string delimeter ) {
		std::vector< std::string > split;
		int start = 0;
		int end = 0;

		while ( ( end = to_split.find( delimeter, start ) ) < to_split.size( ) ) {
			std::string val = to_split.substr( start, end - start );
			split.push_back( val );
			start = end + delimeter.size( );
		}

		if ( start < to_split.size( ) ) {
			std::string val = to_split.substr( start );
			split.push_back( val );
		}

		return split;
	}

	bool instance( ) {
		// sanity check on client->
		if ( !interfaces::client )
			return false;

		// grab linked list.
		auto list = interfaces::client->get_all_classes( );
		if ( !list )
			return false;

		// iterate list of netvars.
		for ( ; list != nullptr; list = list->m_next )
			store_table( list->m_recv_table->m_net_table_name, list->m_recv_table );

		return true;
	}

	void store_table( const std::string& name, recv_table_t* table, std::size_t offset ) {
		// iterate props
		for ( int i { }; i < table->m_props; ++i ) {
			auto prop = &table->m_props_pointer[ i ];
			auto child = prop->m_data_table;

			// we have a child table, that contains props.
			if ( child && child->m_props > 0 )
				store_table( name, child, prop->m_offset + offset );

			// insert if not present.
			if ( !m_offsets[ name ][ prop->m_var_name ].m_offset ) {
				m_offsets[ name ][ prop->m_var_name ].m_datamap_var = false;
				m_offsets[ name ][ prop->m_var_name ].m_prop_ptr = prop;
				m_offsets[ name ][ prop->m_var_name ].m_offset = static_cast< size_t >( prop->m_offset + offset );
			}
		}
	}

	// get client id.
	int get_client_id( const std::string& network_name ) {
		return m_client_ids[ network_name ];
	}

	// get netvar offset.
	int get( const std::string& table, const std::string& prop ) {
		return m_offsets[ table ][ prop ].m_offset;
	}

	int get_offset( const char* name ) {
		const auto items = split( name, "->" );
		if ( items.empty( ) )
			return 0;
		return m_offsets[ items.front( ) ][ items.back( ) ].m_offset;
	}

}