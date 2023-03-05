#include "../hooks.hpp"

bool __fastcall hooks::prediction::in_prediction::fn( i_prediction* ecx, void* edx ) {
	/* skip setup bones call */
	static auto setup_bones_call = ( void* ) utils::find_sig( "client.dll", "8B 40 38 FF D0 84 C0 74 0A" );
	/* skip maintain sequence transition call */
	static auto maintain_seq_transition_call = ( void* ) ( utils::find_sig( "client.dll", "E8 ? ? ? ? F3 0F 10 45 ? 8B 07" ) + 0x4A );

	if ( _ReturnAddress( ) == setup_bones_call || _ReturnAddress( ) == maintain_seq_transition_call )
		return false;

	return get_original( ecx, edx );
}