#include "main.h"
#include "cheat/hooks/hooks.h"

unsigned long __stdcall main::on_attach( LPVOID module ) {
	try {
		while ( !GetModuleHandle( "serverbrowser.dll" ) )
			std::this_thread::sleep_for( std::chrono::seconds( 1 ) );

#ifdef  _DEBUG
		if ( !console::instance( ) )
			throw std::runtime_error( "failed to initialize console" );

		console::print( console::color_white, "interfaces installing" );
		if ( !interfaces::instance( ) )
			throw std::runtime_error( "failed to initialize interfaces" );

		console::print( console::color_white, "netvars installing" );
		if ( !net_vars::instance( ) )
			throw std::runtime_error( "failed to initialize netvars" );

		console::print( console::color_white, "installing render" );
		if ( render::instance( ); false )
			throw std::runtime_error( "failed to initialize render" );

		console::print( console::color_white, "installing hooks" );
		if ( !events::instance( ) )
			throw std::runtime_error( "failed to initialize events" );

		console::print( console::color_white, "installing listeners" );
		if ( !listeners::m_listener.instance( ) )
			throw std::runtime_error( "failed to initialize listeners" );

		console::print( console::color_white, "installing hooks" );
		if ( !hooks::instance( ) )
			throw std::runtime_error( "failed to initialize hooks" );

		console::print( console::color_green, "cheat successfully initialized" );
		while ( !GetAsyncKeyState( VK_DELETE ) )
			std::this_thread::sleep_for( std::chrono::microseconds( 50 ) );

		on_detach( reinterpret_cast< HMODULE >( module ) );
		FreeLibraryAndExitThread( reinterpret_cast< HMODULE >( module ), EXIT_SUCCESS );
#else
		interfaces::instance( );
		net_vars::instance( );
		hooks::instance( );
#endif 
	}
	catch ( const std::exception& ex ) {
#ifdef _DEBUG
		console::print( console::color_red, "[error] %s", ex.what( ) );
		_RPT0( _CRT_ERROR, ex.what( ) );
#else
		FreeLibraryAndExitThread( static_cast< HMODULE >( module ), EXIT_FAILURE );
#endif
	}
	return 1UL;
}

int __stdcall main::on_detach( HMODULE module ) {
	events::reset( );
	listeners::m_listener.reset( );
	render::reset( );
	hooks::reset( );
#ifdef  _DEBUG
	console::reset( );
#endif
	FreeLibraryAndExitThread( reinterpret_cast< HMODULE >( module ), EXIT_SUCCESS );
	return 1;
}

BOOL APIENTRY DllMain( HMODULE module, DWORD call_reason, LPVOID reserved )
{ 
	if ( call_reason != DLL_PROCESS_ATTACH )
		return reserved || call_reason != DLL_PROCESS_DETACH ? 0 : main::on_detach( module );

	DisableThreadLibraryCalls( module );
	if ( const auto thread = CreateThread( 0, 0, main::on_attach, module, 0, 0 ) ) {
		CloseHandle( thread );
	}

	return 1;
}

