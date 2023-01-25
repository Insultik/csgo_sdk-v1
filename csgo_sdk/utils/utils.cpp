#include "utils.h"
#include "../sdk/interfaces/interfaces.h"

float ticks_to_time( int ticks ) {
	return ( float ) ( ticks * interfaces::global_vars->m_interval_per_tick );
}

int time_to_ticks( float time ) {
	return ( int ) ( 0.5f + time / interfaces::global_vars->m_interval_per_tick );
}

uint8_t* utils::find_sig( const std::string& module_array, const std::string& byte_array ) {
	if ( module_array.empty( ) )
		return nullptr;

	const HMODULE module = GetModuleHandle( module_array.c_str( ) );
	static auto pattern_to_byte = [ ]( const char* pattern ) {
		auto bytes = std::vector<int>{};
		const auto start = const_cast< char* >( pattern );
		const auto end = const_cast< char* >( pattern ) + std::strlen( pattern );

		for ( auto current = start; current < end; ++current ) {
			if ( *current == '?' ) {
				++current;

				if ( *current == '?' )
					++current;

				bytes.push_back( -1 );
			}
			else {
				bytes.push_back( std::strtoul( current, &current, 16 ) );
			}
		}
		return bytes;
	};

	const auto dos_header = reinterpret_cast< PIMAGE_DOS_HEADER >( module );
	const auto nt_headers =
		reinterpret_cast< PIMAGE_NT_HEADERS >( reinterpret_cast< std::uint8_t* >( module ) + dos_header->e_lfanew );

	const auto size_of_image = nt_headers->OptionalHeader.SizeOfImage;
	const auto pattern_bytes = pattern_to_byte( byte_array.c_str( ) );
	const auto scan_bytes = reinterpret_cast< std::uint8_t* >( module );

	const auto pattern_size = pattern_bytes.size( );
	const auto pattern_data = pattern_bytes.data( );

	for ( auto i = 0ul; i < size_of_image - pattern_size; ++i ) {
		bool found = true;

		for ( auto j = 0ul; j < pattern_size; ++j ) {
			if ( scan_bytes[ i + j ] != pattern_data[ j ] && pattern_data[ j ] != -1 ) {
				found = false;
				break;
			}
		}
		if ( found )
			return &scan_bytes[ i ];
	}

	return nullptr;
}