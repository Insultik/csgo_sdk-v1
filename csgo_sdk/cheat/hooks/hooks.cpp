#include "hooks.hpp"
#include "../../main.hpp"

#define create_hook( hook_sig, hook ) \
    if ( MH_CreateHook( hook_sig, hook::fn, ( void** )&hook::get_original ) != MH_OK )  \
        console::print( console::color_red, std::string( "failed to create hook " + std::string( #hook ) ).c_str( ) ); \

bool hooks::instance( ) {

    if ( MH_Initialize( ) != MH_OK )
        return false;

    const auto create_move_target = ( void* ) utils::get_virtual( interfaces::client, 22 );
    const auto frame_stage_notify_target = ( void* ) utils::get_virtual( interfaces::client, 37 );
    const auto calc_view_target = ( void* ) utils::find_sig( _( "client.dll" ), _( "55 8B EC 83 E4 F8 83 EC 24 53 56 57 FF 75 18" ) );
    const auto do_extra_bones_processing_target = ( void* ) utils::find_sig( _( "client.dll" ), _( "55 8B EC 83 E4 F8 81 EC FC 00 00 00 53 56 8B F1 57" ) );
    const auto get_eye_ang_target = ( void* ) utils::find_sig( _( "client.dll" ), _( "56 8B F1 85 F6 74 32" ) ); 
    const auto process_interpolated_list_target = ( void* ) utils::find_sig( _( "client.dll" ), _( "0F B7 05 ? ? ? ? 3D ? ? ? ? 74 3F" ) );
    const auto standard_blending_rules_target = ( void* ) utils::find_sig( _( "client.dll" ), _( "55 8B EC 83 E4 F0 B8 ? ? ? ? E8 ? ? ? ? 56 8B 75 08 57 8B F9 85 F6" ) );
    const auto update_clientside_animation_target = ( void* ) utils::find_sig( _( "client.dll" ), _( "55 8B EC 51 56 8B F1 80 BE ? ? ? ? ? 74 36" ) );
    const auto in_prediction_target = ( void* ) utils::find_sig( _( "client.dll" ), _( "8A 41 08 C3" ) );
    const auto override_view_target = ( void* ) utils::find_sig( _( "client.dll" ), _( "55 8B EC 83 E4 F8 8B 4D 04 83 EC 58" ) );
    const auto process_packet_target = ( void* ) utils::find_sig( _( "engine.dll" ), _( "55 8B EC 83 E4 C0 81 EC ? ? ? ? 53 56" ) );
    const auto reset_target = reinterpret_cast< void* >( ( *reinterpret_cast< uintptr_t** >( interfaces::device ) )[ 16 ] );
    const auto present_target = reinterpret_cast< void* >( ( *reinterpret_cast< uintptr_t** >( interfaces::device ) )[ 17 ] );
    const auto paint_traverse_target = reinterpret_cast< void* >( ( *reinterpret_cast< uintptr_t** >( interfaces::panel ) )[ 41 ] );
    const auto lock_cursor_target = reinterpret_cast< void* >( ( *reinterpret_cast< uintptr_t** >( interfaces::surface ) )[ 67 ] );

    create_hook( create_move_target, clientdll::create_move );
    create_hook( frame_stage_notify_target, clientdll::frame_stage_notify );

    create_hook( get_eye_ang_target, base_player::get_eye_ang );
    create_hook( do_extra_bones_processing_target, base_player::do_extra_bones_processing );
    create_hook( standard_blending_rules_target, base_player::standard_blending_rules );

    create_hook( in_prediction_target, prediction::in_prediction );

    create_hook( override_view_target, clientmode::override_view );

    create_hook( process_packet_target, net_channel::process_packet );

    create_hook( reset_target, device::reset );
    create_hook( present_target, device::present );

    create_hook( paint_traverse_target, panel::paint_traverse );

    hooks::device::wnd_proc::instance( );

    if ( MH_EnableHook( MH_ALL_HOOKS ) != MH_OK )
        return false;

    return true;
}