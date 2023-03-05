#pragma once
#include <Windows.h>
#include <iostream>
#include <thread>
#include <format>
#include <fstream>

#include "utils/netvars/netvar_manager.hpp"
#include "sdk/interfaces/interfaces.hpp"

namespace console {
	inline FILE* stream;

	enum colnsole_colors : int {
		color_blue = 9,
		color_green = 10,
		color_cyan = 11,
		color_red = 12,
		color_purple = 13,
		color_yellow = 14,
		color_white = 15
	};

	__forceinline bool instance( ) {
		// google thx
		if ( !AllocConsole( ) )
			return false;

		AttachConsole( ATTACH_PARENT_PROCESS );

		if ( freopen_s( &stream, "CONOUT$", "w", stdout ) != 0 )
			return false;

		if ( !SetConsoleTitle( "debug console" ) )
			return false;

		return true;
	};

	template <typename ... args_t>
	__forceinline void print( std::string text, const args_t& ... arg_list ) {
		HANDLE hConsole = GetStdHandle( STD_OUTPUT_HANDLE );
		SetConsoleTextAttribute( hConsole, 15 );
		if constexpr ( sizeof...( arg_list ) > 0 )
			std::cout << text.c_str( ) << std::endl;
		else
			std::cout << text.c_str( ) << std::endl;
		SetConsoleTextAttribute( hConsole, 15 );
	}

	template <typename ... args_t>
	__forceinline void print( int color, std::string text, const args_t& ... arg_list ) {
		HANDLE hConsole = GetStdHandle( STD_OUTPUT_HANDLE );
		SetConsoleTextAttribute( hConsole, color );
		if constexpr ( sizeof...( arg_list ) > 0 )
			std::cout << text.c_str( ) << std::endl;//std::vformat( text.c_str( ), std::make_format_args( arg_list... ) ) << std::endl;
		else
			std::cout << text.c_str( ) << std::endl;
		SetConsoleTextAttribute( hConsole, 15 );
	}

	__forceinline void reset( ) {
		// google thx
		fclose( stream );

		FreeConsole( );

		if ( const auto console_window = GetConsoleWindow( ); console_window != nullptr )
			PostMessageW( console_window, WM_CLOSE, 0U, 0L );
	};
}

namespace main
{
	unsigned long __stdcall on_attach( LPVOID module );
	int __stdcall on_detach( HMODULE module );
}