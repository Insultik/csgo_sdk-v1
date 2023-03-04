#pragma once
#include <mutex>
#include "../../main_includes.h"
#include "../../dependencies/imgui/imgui.h"
#include "../../dependencies/imgui/imgui_internal.h"
#include "../../dependencies/imgui/imgui_impl_win32.h"
#include "../../dependencies/imgui/imgui_impl_dx9.h"
#include "../../sdk/other/color/color.h"
#include "fonts.h"
#pragma comment(lib, "freetype.lib")

enum font_flags : int {
	font_none,
	font_outline = 1 << 0,
	font_shadow = 1 << 1,
	font_centered_x = 1 << 2,
	font_centered_y = 1 << 4,
	font_centered = font_centered_x | font_centered_y
};

namespace fonts {
	enum e_fonts {
		verdana_11 = 0,
		verdana_14,
		verdana_18,
		pixel_11,
		pixel_14,
		pixel_18,
		weapon_11,
		weapon_14,
		weapon_18
	};
}

namespace render {
	
	inline std::mutex m_render_mutex {};

	static ImU32 get_u32( color_t color ) {
		return ImColor( color.r( ) / 255.f, color.g( ) / 255.f, color.b( ) / 255.f, color.a( ) / 255.f );
	}

	__forceinline vec2_t calc_text_size( std::string txt, fonts::e_fonts font_ = fonts::verdana_11 ) {
		ImFont* font = ImGui::GetIO( ).Fonts->Fonts[ font_ ];
		if ( !font || !font->ContainerAtlas || txt.empty( ) || !font->IsLoaded( ) )
			return vec2_t( );

		auto size = font->CalcTextSizeA( font->FontSize, FLT_MAX, 0.f, txt.c_str( ) );

		return vec2_t( std::floor( size.x + 0.95f ), size.y );
	}

	void rect( vec2_t start, vec2_t end, color_t color, float thickness = 1.f, float rounding = 0.f, ImDrawCornerFlags_ flags = ImDrawCornerFlags_All );
	void rect_filled( vec2_t start, vec2_t end, color_t color, float rounding = 0.f, ImDrawCornerFlags_ flags = ImDrawCornerFlags_All );
	void circle_2d( vec2_t position, int point_count, float radius, color_t color );
	void circle_2d_filled( vec2_t position, int point_count, float radius, color_t color );
	void circle_3d( vec3_t position, int point_count, float radius, color_t color, float progress = 1.f, float size = 1.f );
	void circle_3d_filled( const vec3_t& origin, float radius, color_t color );
	void line( vec2_t start, vec2_t end, color_t color, float thickness );
	void triangle( vec2_t first, vec2_t second, vec2_t third, color_t color );
	void text( std::string text, vec2_t text_position, color_t color, fonts::e_fonts font = fonts::verdana_11, int flags = font_none, bool menu = false );
	void instance( );
	void reset( );
	void draw( );
	void clear_draw_list( );
	ImDrawList* render_scene( );

	inline ImDrawList* m_draw_list_act {};
	inline ImDrawList* m_draw_list_rendering {};
	inline ImDrawList* m_draw_list {};
	inline ImDrawData m_draw_data {};

};

