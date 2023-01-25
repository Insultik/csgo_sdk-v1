#include "menu.h"

bool menu::instance( ) noexcept {
	auto& io { ImGui::GetIO( ) };
	io.IniFilename = nullptr;
	io.LogFilename = nullptr;
	io.ConfigFlags |= ImGuiConfigFlags_NoMouseCursorChange;

	ImGui::StyleColorsDark( );

	auto& style { ImGui::GetStyle( ) };
	style.Alpha = 1.f;
	style.ScrollbarSize = 13.0f;
	style.WindowTitleAlign = ImVec2 { 0.5f, 0.5f };
	style.WindowRounding = 6.f;

	return true;
}

void menu::draw( ) {
	auto& style = ImGui::GetStyle( );
	const auto& io = ImGui::GetIO( );

	if ( !ctx::m_menu_opened )
		return;
	
	style.Alpha = 1.f;

	ImGui::SetNextWindowSize( ImVec2 { 512.f, 515.f }, ImGuiCond_Once );
	ImGui::Begin( "csgo sdk", nullptr, ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoCollapse );
	{

	}
	ImGui::End( );
}
