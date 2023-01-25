#pragma once
#include "../../../main_includes.h"
#include "../../../utils/render/render.h"

class c_bounding_box {
public:
	c_bounding_box( ) {
		x = { };
		y = { };
		w = { };
		h = { };
		m_alpha = { };
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
		color_t m_color;
		float m_alpha = 1.f;
	};
	using text_array_t = std::vector<text_array_element_t>;

	bool calc_box( c_base_entity* entity );

	void box( color_t color );

	void bar( float max, float value, color_t color, e_position render_pos = pos_left, bool show_text = true );

	void text( std::string text, color_t clr, e_position _pos = pos_right, render::fonts::fonts_e font = render::fonts::verdana_11 );

	void text_array( text_array_t&& text_array, e_position _pos = pos_right, render::fonts::fonts_e font = render::fonts::pixel_11 );

	__forceinline void reset_positions( ) {
		for ( auto& o : m_render_state.m_offsets )
			o = 0.f;
	}

	__forceinline void invalidate( ) {
		reset_positions( );
		x = y = w = h = 0;
	}
};