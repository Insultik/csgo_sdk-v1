#pragma once
#include "../../main.h"
#include <vector>
#include <unordered_map>

struct recv_prop_t;
struct recv_table_t;

struct net_var_table_t {
	std::string m_name{};
	recv_prop_t* m_prop{};
	uint32_t m_offset{};
	std::vector<recv_prop_t*> m_child_props{};
	std::vector<net_var_table_t> m_child_tables{};
};

namespace net_vars {
	bool instance( );

	struct netvar_data_t {
		bool m_datamap_var; // we can't do proxies on stuff from datamaps :).
		recv_prop_t* m_prop_ptr;
		std::size_t m_offset;

		netvar_data_t( ) : m_datamap_var { }, m_prop_ptr { }, m_offset { } { }
	};

	extern std::unordered_map< std::string, int > m_client_ids;
	extern std::unordered_map< std::string, std::unordered_map< std::string, netvar_data_t > > m_offsets;

	void store_table( const std::string& name, recv_table_t* table, std::size_t offset = 0 );
	int get_client_id( const std::string& network_name );
	int get( const std::string& table, const std::string& prop );
	int get_offset( const char* name );
}

#define NETVAR(type, func_name, name) \
type& func_name( ) { \
    return *(type*)( uintptr_t( this ) + net_vars::get_offset( name ) ); \
} 

#define NETVAR_PTR(type, func_name, name) \
type* func_name( ) { \
    return (type*)( uintptr_t( this ) + net_vars::get_offset(name ) ); \
} 

#define OFFSET(type, var, offset) \
type& var() { \
	return *(type*)(uintptr_t(this) + offset); \
} 

#define OFFSET_PTR( type, var,offset) \
type*& var() { \
	return *(type**)(uintptr_t(this) + offset); \
} 

#define NETVAR_OFFSET( type, func, name, off ) \
type& func( ) { \
	static auto offset = net_vars::get_offset( name ); \
	return *( type* ) ( uintptr_t( this ) + offset + off ); \
} 

#define NETVAR_OFFSET_PTR( type, func, name, off ) \
type* func( ) { \
	static auto offset = net_vars::get_offset( name ); \
	return *( type* ) ( uintptr_t( this ) + offset + off ); \
} 

enum e_offset_type {
	TD_OFFSET_NORMAL,
	TD_OFFSET_PACKED
};

enum e_field_type {
	FIELD_VOID,
	FIELD_FLOAT,
	FIELD_STRING,
	FIELD_VECTOR,
	FIELD_QUATERNION,
	FIELD_INTEGER,
	FIELD_BOOLEAN,
	FIELD_SHORT,
	FIELD_CHARACTER,
	FIELD_COLOR32,
	FIELD_EMBEDDED,
	FIELD_CUSTOM,
	FIELD_CLASSPTR,
	FIELD_EHANDLE,
	FIELD_EDICT,
	FIELD_POSITION_VECTOR,
	FIELD_TIME,
	FIELD_TICK,
	FIELD_MODELNAME,
	FIELD_SOUNDNAME,
	FIELD_INPUT,
	FIELD_FUNCTION,
	FIELD_VMATRIX,
	FIELD_VMATRIX_WORLDSPACE,
	FIELD_MATRIX3X4_WORLDSPACE,
	FIELD_INTERVAL,
	FIELD_MODELINDEX,
	FIELD_MATERIALINDEX,
	FIELD_VECTOR2D
};

struct data_map_t;
struct input_data_t;

using input_fn_t = void( __cdecl* )( input_data_t& );
#include "../../utils/utils.h"
struct type_description_t {
	e_field_type			m_field_type;
	const char* m_field_name;
	int						m_field_offset;
	uint16_t				m_field_size;
	bit_flag_t<uint16_t>	m_flags;
	const char* m_external_name;
	uintptr_t* m_save_restore_ops;
	input_fn_t				m_input_fn;
	data_map_t* m_data_map;
	uint32_t				m_field_size_in_bytes;
	type_description_t* m_override_field;
	uint32_t				m_override_count;
	float					m_field_tolerance;
	int						m_flat_offset[ 2 ];
	uint16_t				m_flat_group;
};

struct data_map_t {
	__forceinline uint32_t find( std::string hash ) const {
		auto data_map = this;

		while ( data_map ) {
			for ( auto i = 0; i < data_map->m_data_fields_count; i++ ) {
				if ( !data_map->m_data_description[ i ].m_field_name )
					continue;

				if ( hash == ( data_map->m_data_description[ i ].m_field_name ) )
					return data_map->m_data_description[ i ].m_field_offset;

				if ( data_map->m_data_description[ i ].m_field_type != FIELD_EMBEDDED
					 || !data_map->m_data_description[ i ].m_data_map )
					continue;

				const auto offset = data_map->m_data_description[ i ].m_data_map->find( hash );
				if ( !offset )
					continue;

				return offset;
			}

			data_map = data_map->m_base_map;
		}

		return 0u;
	}

	type_description_t* m_data_description;
	int                 m_data_fields_count;
	char const* m_data_class_name;
	data_map_t* m_base_map;

	bool                m_chains_validated;
	bool                m_packed_offsets_computed;
	int                 m_packed_size;
};