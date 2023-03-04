#pragma once
#include "../../../main_includes.h"
#include "bounding_box.h"

namespace players {
	class player_esp_data_t {
	public:
		c_bounding_box* m_box;
		float m_alpha { };
		float m_ammo { };
		float m_health { };

		__forceinline void invalidate( ) {
			m_box = new c_bounding_box( );
			m_alpha = m_ammo = m_health = 0.f;
		}
	};

	void instance( );

	inline std::array< player_esp_data_t, values::max_game_players > player_data;
}