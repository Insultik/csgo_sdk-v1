#pragma once
#include "../../../main_includes.h"

class c_bounding_box {
public:
	c_bounding_box( ) {
		x = { };
		y = { };
		w = { };
		h = { };
		m_alpha = { };
	}

	__forceinline bool calculate_box( c_base_entity* entity ) {

	}

	float x, y, w, h;
	float m_alpha;

	enum e_position : int {
		pos_left,
		pos_right,
		pos_top,
		pos_bottom,
		pos_max
	};

	static constexpr int m_padding = 2;
	static constexpr int m_bar_size = 2;

	struct {
		float m_offsets[ pos_max ];
	} m_render_state;

	struct text_array_element_t {
		std::string m_text {};
		color_t m_color = { 255, 255, 255, 255 };
		float m_alpha = 1.f;
	};
	using text_array_t = std::vector<text_array_element_t>;

	__forceinline void box( color_t&& color ) {
		render::rect( vec2_t( x, y ), vec2_t( w, h ), color_t( 0, 0, 0 ).override_alpha( 255 * m_alpha ) );
		render::rect( vec2_t( x + 1, y + 1 ), vec2_t( w - 1, h - 1 ), color.override_alpha( 255 * m_alpha ) );
		render::rect( vec2_t( x + 2, y + 2 ), vec2_t( w - 2, h - 2 ), color_t( 0, 0, 0 ).override_alpha( 255 * m_alpha ) );
	};

	__forceinline void bar( float max, float value, color_t color, e_position render_pos = pos_left, bool show_text = true ) {
		float extra_offset { 0.f };
		vec2_t pos { }, size { };
		bool horizontal { };

		auto& current_offset = m_render_state.m_offsets[ render_pos ];

		switch ( render_pos ) {
			case e_position::pos_bottom:
				size = { w, m_bar_size };
				pos = { 0.f, h + m_padding + current_offset };
				horizontal = true;
				break;
			case e_position::pos_top:
				size = { w, m_bar_size };
				pos = { 0.f, -m_padding - m_bar_size - current_offset };
				horizontal = true;
				break;
			case e_position::pos_left:
				size = { m_bar_size, h };
				pos = { -m_padding - m_bar_size - current_offset, 0.f };
				break;
			case e_position::pos_right:
				size = { m_bar_size, h };
				pos = { w + m_padding + current_offset, 0.f };
				break;
			default:
				return;
		}

		float bar_fill = std::clamp( value / max, 0.f, 1.f );
		if ( horizontal ) {
			render::rect_filled( vec2_t( x + pos.x, y + pos.y - 1 ), vec2_t( size.x, size.y + 2 ), color_t( 35, 35, 35, ( uint8_t ) ( 255 * m_alpha ) ) );

			pos.x += 1;
			size.x -= 2;

			render::rect_filled( vec2_t( x + pos.x, y + pos.y ), vec2_t( size.x * bar_fill, size.y ), color.override_alpha( ( uint8_t ) ( 255.f * m_alpha ) ) );
			if ( show_text && ( int ) value < ( int ) max )
				render::text( std::to_string( ( int ) value ), vec2_t( x + pos.x + size.x * bar_fill, y + pos.y ), color_t( 255, 255, 255, ( uint8_t ) ( 255.f * m_alpha ) ), render::fonts::verdana_11, font_outline );
		}
		else {
			render::rect_filled( vec2_t( x + pos.x - 1, y + pos.y ), vec2_t( size.x + 2, size.y ), color_t( 35, 35, 35, ( uint8_t ) ( 255.f * m_alpha ) ) );

			pos.y += 1;
			size.y -= 2;

			render::rect_filled( vec2_t( x + pos.x, y + pos.y + size.y * ( 1.f - bar_fill ) ), vec2_t( size.x, size.y * bar_fill ), color.override_alpha( ( uint8_t ) ( 255.f * m_alpha ) ), 0.f );

			if ( show_text && ( int ) value < ( int ) max )
				render::text( std::to_string( ( int ) value ), vec2_t( x + pos.x, y + pos.y + size.y * ( 1.f - bar_fill ) ), color_t( 255, 255, 255, ( uint8_t ) ( 255.f * m_alpha ) ), render::fonts::verdana_11, font_outline | font_centered );
		}

		current_offset += m_bar_size + 1 /* outline */ + m_padding;
	}

	__forceinline void text( std::string text, color_t clr, e_position _pos = pos_right, render::fonts::fonts_e font = render::fonts::verdana_11 ) {
		vec2_t pos {};
		auto size = render::calc_text_size( text.c_str( ), font );
		auto& current_offset = m_render_state.m_offsets[ _pos ];

		current_offset += m_padding;

		switch ( _pos ) {
			case e_position::pos_bottom:
				pos = { 0.f, h + current_offset };
				current_offset += size.y;
				break;
			case e_position::pos_top:
				pos = { 0.f, -current_offset - size.y };
				current_offset += size.y;
				break;
			case e_position::pos_left:
				pos = { -size.x - m_padding, current_offset };
				current_offset += size.y;
				break;
			case e_position::pos_right:
				pos = { w + size.x + m_padding, current_offset };
				current_offset += size.y;
				break;
			default:
				return;
		}
		font_flags adjust_flag = font_none;
		if ( _pos == e_position::pos_top || _pos == e_position::pos_bottom )
			adjust_flag = font_centered_x;
		else
			adjust_flag = font_centered_y;
		pos = pos + vec2_t( x, y );
		if ( _pos == e_position::pos_top || _pos == e_position::pos_bottom )
			render::text( text, vec2_t( pos.x + w / 2.f, pos.y ), clr.override_alpha( m_alpha * 255 ), font, adjust_flag | font_outline );
		else
			render::text( text, vec2_t( pos.x, pos.y ), clr.override_alpha( m_alpha * 255 ), font, adjust_flag | font_outline);
	}

	__forceinline void text_array( text_array_t&& text_array, e_position _pos = pos_right, render::fonts::fonts_e font = render::fonts::pixel_11 ) {
		if ( text_array.empty( ) )
			return;

		auto& current_offset = m_render_state.m_offsets[ _pos ];
		float max_x_size {};
		vec2_t pos {};

		switch ( _pos ) {
			case e_position::pos_bottom:
				pos = { 0.f, h + current_offset };
				break;
			case e_position::pos_top:
				pos = { 0.f, -current_offset };
				break;
			case e_position::pos_left:
				pos = { -current_offset, 0.f };
				break;
			case e_position::pos_right:
				pos = { w + current_offset, 0.f };
				break;
			default:
				return;
		}

		float total_size = ( render::calc_text_size( text_array[ 0 ].m_text, font ).y + m_padding ) * text_array.size( );

		float cursor_pos = _pos == e_position::pos_top ? -total_size : 0.f;

		for ( size_t i = 0u; i < text_array.size( ); ++i ) {
			auto& it = text_array[ i ];

			auto it_size = render::calc_text_size( it.m_text.c_str( ), font );

			if ( _pos == e_position::pos_left )
				render::text( it.m_text.c_str( ), vec2_t( x + pos.x - m_padding - it_size.x, y + pos.y + cursor_pos ), it.m_color, font, font_outline );
			else
				render::text( it.m_text.c_str( ), vec2_t( x + pos.x + m_padding, y + pos.y + cursor_pos ), it.m_color, font, font_outline );

			if ( it_size.x > max_x_size )
				max_x_size = it_size.x;

			cursor_pos += it_size.y + m_padding * 1.2f;
		}

		switch ( _pos ) {
			case e_position::pos_bottom:
			case e_position::pos_top:
				current_offset += total_size + m_padding;
				break;
			case e_position::pos_left:
			case e_position::pos_right:
				current_offset += max_x_size + m_padding;
				break;
			default:
				return;
		}
	}

	__forceinline void reset_positions( ) {
		for ( auto& o : m_render_state.m_offsets )
			o = 0.f;
	}
};