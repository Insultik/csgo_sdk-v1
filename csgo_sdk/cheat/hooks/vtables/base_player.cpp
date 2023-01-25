#include "../hooks.h"

void __fastcall hooks::base_player::build_transformations::fn( void* ecx, void* edx, int a2, int a3, int a4, int a5, int a6, int a7 ) {
	auto pl = ( c_cs_player* ) ecx;
	if ( !pl || pl->is_dormant( ) )
		return get_original( ecx, edx, a2, a3, a4, a5, a6, a7 );

	auto o_jiggle_bones_enabled = pl->get_jiggle_bones( );
	pl->get_jiggle_bones( ) = false;
	get_original( ecx, edx, a2, a3, a4, a5, a6, a7 );
	pl->get_jiggle_bones( ) = o_jiggle_bones_enabled;
}

void __fastcall hooks::base_player::calc_view::fn( void* ecx, void* edx, vec3_t& eye_origin, vec3_t& eye_angles, float& m_near, float& m_far, float& fov ) {
	auto pl = ( c_cs_player* ) ecx;
	if ( !pl || pl->is_dormant( ) )
		return get_original( ecx, edx, eye_origin, eye_angles, m_near, m_far, fov );

	const auto o_new_animstate = pl->should_use_new_anim_state( );
	pl->should_use_new_anim_state( ) = false;
	get_original( ecx, edx, eye_origin, eye_angles, m_near, m_far, fov );
	pl->should_use_new_anim_state( ) = o_new_animstate;
}

void __fastcall hooks::base_player::do_extra_bones_processing::fn( void* ecx, void* edx, int a2, int a3, int a4, int a5, int a6, int a7 ) {
	return;
}

ang_t* __fastcall hooks::base_player::get_eye_ang::fn( void* ecx, void* edx ) {
	auto pl = ( c_cs_player* ) ecx;
	if ( !ctx::m_cmd || !pl || pl->get_index( ) != interfaces::engine->get_local_player( ) )
		return get_original( ecx, edx );

	static auto ret_to_thirdperson_pitch = utils::find_sig( _( "client.dll" ), _( "8B CE F3 0F 10 00 8B 06 F3 0F 11 45 ? FF 90 ? ? ? ? F3 0F 10 55 ?" ) );
	static auto ret_to_thirdperson_yaw = utils::find_sig( _( "client.dll" ), _( "F3 0F 10 55 ? 51 8B 8E ? ? ? ?" ) );
	static auto ret_to_thirdperson_roll = utils::find_sig( _( "client.dll" ), _( "8B 55 0C 8B C8 E8 ? ? ? ? 83 C4 08 5E 8B E5" ) );

	if ( _ReturnAddress( ) == ( void* ) ret_to_thirdperson_pitch || _ReturnAddress( ) == ( void* ) ret_to_thirdperson_yaw || _ReturnAddress( ) == ( void* ) ret_to_thirdperson_roll )
		return &ctx::m_cmd->m_view_angles;

	return get_original( ecx, edx );
}

void __fastcall hooks::base_player::standard_blending_rules::fn( void* ecx, void* edx, c_studio_hdr* hdr, vec3_t* pos, void* q, float curtime, int mask ) {
	auto pl = ( c_cs_player* ) ecx;
	if ( !pl || pl->is_dormant( ) ) {
		return get_original( ecx, edx, hdr, pos, q, curtime, mask );
	}

	/* stop interpolation */
	*( uint32_t* ) ( ( uintptr_t ) pl + 0xf0 ) |= 8;

	/* let csgo do their stuff */
	get_original( ecx, edx, hdr, pos, q, curtime, mask );

	/* start interpolation again */
	*( uint32_t* ) ( ( uintptr_t ) pl + 0xf0 ) &= ~8;
}