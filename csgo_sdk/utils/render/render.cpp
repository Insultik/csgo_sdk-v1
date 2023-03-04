#include "render.h"
#include "../../dependencies/imgui/imgui_freetype.h"

void render::instance( ) {
	ImGui::CreateContext( );
	m_draw_list = new ImDrawList( ImGui::GetDrawListSharedData( ) );
	m_draw_list_act = new ImDrawList( ImGui::GetDrawListSharedData( ) );
	m_draw_list_rendering = new ImDrawList( ImGui::GetDrawListSharedData( ) );

	ImFontConfig cfg;
	cfg.PixelSnapH = false;
	cfg.OversampleH = cfg.OversampleV = 5;
	cfg.RasterizerMultiply = 1.2f;

	static const ImWchar ranges[ ] = { 0x0020, 0x00FF, 0x0400, 0x052F, 0x2DE0, 0x2DFF, 0xA640, 0xA69F, 0xE000, 0xE226, 0, };
	cfg.GlyphRanges = ranges;

	ImGui::GetIO( ).Fonts->AddFontFromFileTTF( "c:\\Windows\\Fonts\\verdana.ttf", 11.0f, &cfg, ranges );
	ImGui::GetIO( ).Fonts->AddFontFromFileTTF( "c:\\Windows\\Fonts\\verdana.ttf", 14.0f, &cfg, ranges );
	ImGui::GetIO( ).Fonts->AddFontFromFileTTF( "c:\\Windows\\Fonts\\verdana.ttf", 18.0f, &cfg, ranges );

	ImGui::GetIO( ).Fonts->AddFontFromMemoryTTF( ( void* ) PixelFont, sizeof( PixelFont ), 11.0f, &cfg, ranges );
	ImGui::GetIO( ).Fonts->AddFontFromMemoryTTF( ( void* ) PixelFont, sizeof( PixelFont ), 14.0f, &cfg, ranges );
	ImGui::GetIO( ).Fonts->AddFontFromMemoryTTF( ( void* ) PixelFont, sizeof( PixelFont ), 18.0f, &cfg, ranges );
	
	ImGui::GetIO( ).Fonts->AddFontFromMemoryCompressedBase85TTF( WeaponIcons_compressed_data_base85, 11.0f, &cfg, ranges );
	ImGui::GetIO( ).Fonts->AddFontFromMemoryCompressedBase85TTF( WeaponIcons_compressed_data_base85, 14.0f, &cfg, ranges );
	ImGui::GetIO( ).Fonts->AddFontFromMemoryCompressedBase85TTF( WeaponIcons_compressed_data_base85, 18.0f, &cfg, ranges );

	ImGui::GetIO( ).Fonts->AddFontDefault( );
	ImGuiFreeType::BuildFontAtlas( ImGui::GetIO( ).Fonts, ImGuiFreeType::RasterizerFlags::NoHinting );
}

void render::reset( ) {
	
}

void render::draw( ) {
	m_draw_list->Clear( );
	m_draw_list->PushClipRectFullScreen( );
	// begin rendering
	{
		render::rect_filled( vec2_t( 100, 100 ), vec2_t( 200, 200 ), color_t( 255, 255, 255, 125 ), 2.f );
		features::draw_features( );
	}
	// end rendering
	m_render_mutex.lock( );
	*m_draw_list_act = *m_draw_list;
	m_render_mutex.unlock( );
}

void render::clear_draw_list( ) {
	m_render_mutex.lock( );
	m_draw_list_act->Clear( );
	m_render_mutex.unlock( );
}

ImDrawList* render::render_scene( ) {

	if ( m_render_mutex.try_lock( ) ) {
		*m_draw_list_rendering = *m_draw_list_act;
		m_render_mutex.unlock( );
	}

	return m_draw_list_rendering;
}

void render::rect( vec2_t start, vec2_t end, const color_t color, const float thickness, const float rounding, ImDrawCornerFlags_ flags ) {
	m_draw_list->AddRect( ImVec2( start.x, start.y ), ImVec2( start.x + end.x, start.y + end.y ), get_u32( color ), rounding, flags, thickness );
}

void render::rect_filled( vec2_t start, vec2_t end, const color_t color, const float rounding, ImDrawCornerFlags_ flags ) {
	m_draw_list->AddRectFilled( ImVec2( start.x, start.y ), ImVec2( start.x + end.x, start.y + end.y ), get_u32( color ), rounding, flags );
}

void render::circle_2d( const vec2_t screen_position, const int point_count, const float radius, const color_t color ) {
	m_draw_list->AddCircle( ImVec2( screen_position.x, screen_position.y ), radius, get_u32( color ), point_count );
}

void render::circle_2d_filled( const vec2_t screen_position, const int point_count, const float radius, const color_t color ) {
	m_draw_list->AddCircleFilled( ImVec2( screen_position.x, screen_position.y ), radius, get_u32( color ), point_count );
}

void render::circle_3d( const vec3_t origin, const int point_count, const float radius, const color_t color, float progress, float size ) {
	static float step = math::m_pi * 2.0f / 72.0f;

	vec3_t screen_position = vec3_t( 0, 0, 0 );
	if ( interfaces::debug_overlay->screen_position( origin, screen_position ) )
		return;

	std::vector< ImVec2 > points;
	for ( float rotation = 0.0f; rotation <= math::m_pi * 2.0f; rotation += step ) {
		auto world_position = vec3_t( radius * cos( rotation ) + origin.x, radius * sin( rotation ) + origin.y, origin.z );

		if ( interfaces::debug_overlay->screen_position( world_position, screen_position ) )
			continue;

		points.push_back( ImVec2( screen_position.x, screen_position.y ) );
	}
	m_draw_list->AddPolyline( points.data( ), max( 1, points.size( ) * progress ), get_u32( color ), progress >= 1.f, size );
}

void render::circle_3d_filled( const vec3_t& origin, const float radius, const color_t color ) {
	static float step = math::m_pi * 2.0f / 72.0f;

	vec3_t screen_position = vec3_t( 0, 0, 0 );
	if ( interfaces::debug_overlay->screen_position( origin, screen_position ) )
		return;

	std::vector< ImVec2 > points;
	for ( float rotation = 0.0f; rotation <= math::m_pi * 2.0f; rotation += step ) {
		auto world_position = vec3_t( radius * cos( rotation ) + origin.x, radius * sin( rotation ) + origin.y, origin.z );

		if ( interfaces::debug_overlay->screen_position( world_position, screen_position ) )
			continue;

		points.push_back( ImVec2( screen_position.x, screen_position.y ) );
	}
	m_draw_list->AddConvexPolyFilled( points.data(), points.size( ), get_u32( color ) );
}

void render::line( vec2_t start, vec2_t end, const color_t color, const float thickness ) {
	m_draw_list->AddLine( ImVec2( start.x, start.y ), ImVec2( end.x, end.y ), get_u32( color ), thickness );
}

void render::triangle( const vec2_t first, const vec2_t second, const vec2_t third, const color_t color ) {
	m_draw_list->AddTriangleFilled( ImVec2( first.x, first.y ), ImVec2( second.x, second.y ), ImVec2( third.x, third.y ), get_u32( color ) );
}

void render::text( std::string text, vec2_t text_position, color_t color, fonts::e_fonts font_, int flags, bool menu ) {
	ImFont* font = ImGui::GetIO( ).Fonts->Fonts[ font_ ];
	if ( !font || !font->ContainerAtlas )
		return;

	const ImVec2 im_text_size = font->CalcTextSizeA( font->FontSize, FLT_MAX, 0.0f, text.c_str( ) );
	ImDrawList* old_draw_list = m_draw_list;
	if ( menu )
		m_draw_list = ImGui::GetOverlayDrawList( );

	m_draw_list->PushTextureID( font->ContainerAtlas->TexID );
	if ( flags & font_centered_x )
		text_position.x -= im_text_size.x / 2.0f;
	if ( flags & font_centered_y )
		text_position.y -= im_text_size.y / 2.0f;

	if ( flags & font_outline ) {
		m_draw_list->AddText( font, font->FontSize, ImVec2( text_position.x + 1, text_position.y + 1 ), get_u32( color_t( 30, 30, 36, color.a( ) ) ), text.c_str( ) );
		m_draw_list->AddText( font, font->FontSize, ImVec2( text_position.x - 1, text_position.y - 1 ), get_u32( color_t( 30, 30, 36, color.a( ) ) ), text.c_str( ) );
		m_draw_list->AddText( font, font->FontSize, ImVec2( text_position.x + 1, text_position.y - 1 ), get_u32( color_t( 30, 30, 36, color.a( ) ) ), text.c_str( ) );
		m_draw_list->AddText( font, font->FontSize, ImVec2( text_position.x - 1, text_position.y + 1 ), get_u32( color_t( 30, 30, 36, color.a( ) ) ), text.c_str( ) );
	}

	m_draw_list->AddText( font, font->FontSize, ImVec2( text_position.x, text_position.y ), get_u32( color ), text.c_str( ) );
	m_draw_list->PopTextureID( );

	if ( menu )
		m_draw_list = old_draw_list;
}