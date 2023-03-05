#include "../hooks.hpp"

void __fastcall hooks::clientmode::override_view::fn( void* ecx, void* edx, view_setup_t* view ) {
	interfaces::input->m_camera_in_third_person = GetKeyState( VK_MBUTTON );

	get_original( ecx, edx, view );
}