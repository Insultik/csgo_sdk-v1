#pragma once
#include "../main_includes.h"
#include "../dependencies/imgui/imgui.h"
#include "../dependencies/imgui/imgui_internal.h"
#include "../dependencies/imgui/imgui_impl_win32.h"
#include "../dependencies/imgui/imgui_impl_dx9.h"

namespace menu {
	bool instance( ) noexcept;
	void draw( );
};

