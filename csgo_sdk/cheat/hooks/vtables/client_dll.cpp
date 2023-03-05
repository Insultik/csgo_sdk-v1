#include "../hooks.hpp"
#include "../../../main.hpp"

__declspec( naked ) void __fastcall hooks::clientdll::create_move::fn( void* ecx, void* edx, int sequence_number, float sample_frametime, bool active ) {
	__asm {
		push ebp
		mov  ebp, esp
		push ebx
		push esp
		push dword ptr[ active ]
		push dword ptr[ sample_frametime ]
		push dword ptr[ sequence_number ]
		call hooks::clientdll::create_move::call
		pop  ebx
		pop  ebp
		retn 0Ch
	}
}

void __stdcall hooks::clientdll::create_move::call( int sequence_number, float sample_frametime, bool active, bool& send_packet ) {
	get_original( sequence_number, sample_frametime, active );
	c_user_cmd* cmd = interfaces::input->get_user_cmd( sequence_number );
	c_verified_user_cmd* verified_cmd = interfaces::input->get_verified_user_cmd( sequence_number );
	if ( !cmd || !cmd->m_command_number )
		return;

	ctx::m_weapon.invalidate( );
	ctx::m_send_packet = true;
	ctx::m_cmd = cmd;

	if ( !ctx::m_local.alive( ) )
		return;

	ctx::m_angles.view = cmd->m_view_angles;
	ctx::m_weapon.instance( ctx::m_local.get( )->get_active_weapon( ) );

	// p100 auto-pistol and attack fix
	if ( !ctx::m_local.get()->can_fire( ) )
		cmd->m_buttons.remove( in_attack );

	features::create_move( );

	// p100 auto-pistol and attack fix
	if ( !ctx::m_local.can_shoot( ) )
		cmd->m_buttons.remove( in_attack );

	cmd->m_view_angles.sanitize( );

	if ( ctx::m_send_packet ) 
		ctx::m_angles.real = cmd->m_view_angles;
	else 
		ctx::m_angles.fake = cmd->m_view_angles;

	ctx::m_angles.anim = cmd->m_view_angles;

	ctx::m_animating = true;
	send_packet = ctx::m_send_packet;
	verified_cmd->m_cmd = *cmd;
	verified_cmd->m_crc = cmd->get_checksum( );
}

void __fastcall hooks::clientdll::frame_stage_notify::fn( void* ecx, void* edx, int stage ) {
	if ( !interfaces::engine->is_in_game( ) )
		return ctx::m_local.invalidate( );

	ctx::m_local.instance( );
	if ( !interfaces::engine->is_in_game( ) || !ctx::m_local )
		return get_original( ecx, edx, stage );

	features::frame_stage_notify( stage );

	get_original( ecx, edx, stage );
}