#include "interfaces.h"

void* interfaces::get_interface( const HMODULE module, const char* interface_name ) {
    auto return_value = reinterpret_cast< create_interface_fn >( GetProcAddress( module, "CreateInterface" ) )( interface_name, nullptr );
    if ( return_value == nullptr || !return_value )
        console::print( console::color_red, "failed to install interface ", interface_name );

    return return_value;
};

bool interfaces::instance( ) {

    engine = static_cast< i_engine_client* >( get_interface( GetModuleHandle( "engine.dll" ), "VEngineClient014" ) );
    entity_list = static_cast< i_client_entity_list* >( get_interface( GetModuleHandle( "client.dll" ), "VClientEntityList003" ) );
    client = static_cast< i_base_client_dll* >( get_interface( GetModuleHandle( "client.dll" ), "VClient018" ) );
    material_system = static_cast< i_material_system* >( get_interface( GetModuleHandle( "materialsystem.dll" ), "VMaterialSystem080" ) );
    studio_render = static_cast< i_studio_render* >( get_interface( GetModuleHandle( "studiorender.dll" ), "VStudioRender026" ) );
    model_info = static_cast< i_model_info* >( get_interface( GetModuleHandle( "engine.dll" ), "VModelInfoClient004" ) );
    model_render = static_cast< i_model_render* >( get_interface( GetModuleHandle( "engine.dll" ), "VEngineModel016" ) );
    render_view = static_cast< i_render_view* >( get_interface( GetModuleHandle( "engine.dll" ), "VEngineRenderView014" ) );
    game_movement = static_cast< i_game_movement* >( get_interface( GetModuleHandle( "client.dll" ), "GameMovement001" ) );
    event_manager = static_cast< i_game_event_manager* >( get_interface( GetModuleHandle( "engine.dll" ), "GAMEEVENTSMANAGER002" ) );
    debug_overlay = static_cast< i_debug_overlay* >( get_interface( GetModuleHandle( "engine.dll" ), "VDebugOverlay004" ) );
    panel = static_cast< i_panel* >( get_interface( GetModuleHandle( "vgui2.dll" ), "VGUI_Panel009" ) );
    surface = static_cast< i_surface* >( get_interface( GetModuleHandle( "vguimatsurface.dll" ), "VGUI_Surface031" ) );

    mem_alloc = *reinterpret_cast< i_mem_alloc** >( GetProcAddress( GetModuleHandleA( "tier0.dll" ), _( "g_pMemAlloc" ) ) );
    if ( !mem_alloc )
        console::print( console::color_red, "failed to install mem_alloc interface" );
    client_state = **reinterpret_cast< i_client_state*** >( utils::find_sig( "engine.dll", "A1 ? ? ? ? 8B 80 ? ? ? ? C3" ) + 0x1 );
    if ( !client_state )
        console::print( console::color_red, "failed to install client_state interface" );
    global_vars = **( i_global_vars_base*** ) ( ( *( DWORD** ) client )[ 11 ] + 10 );
    if ( !global_vars )
        console::print( console::color_red, "failed to install global_vars interface" );
    weapon_system = *( i_weapon_system** ) ( utils::find_sig( "client.dll", "8B 35 ? ? ? ? FF 10 0F B7 C0" ) + 0x2 );
    if ( !weapon_system )
        console::print( console::color_red, "failed to install weapon_system interface" );
    input = *( i_input** ) ( utils::find_sig( "client.dll", "B9 ? ? ? ? C7 05 ? ? ? ? ? ? ? ? E8 ? ? ? ? C7 05 ? ? ? ? ? ? ? ? B8 ? ? ? ?" ) + 7 );
    if ( !input )
        console::print( console::color_red, "failed to install input interface" );
    device = **reinterpret_cast< IDirect3DDevice9*** >( utils::find_sig( "shaderapidx9.dll", "A1 ? ? ? ? 50 8B 08 FF 51 0C" ) + 0x1 );
    if ( !device ) 
        console::print( console::color_red, "failed to install 3d device" );
        
    return true;
}