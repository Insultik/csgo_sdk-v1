#pragma once
#include "../../../main_includes.h"
#include <functional>

namespace events {
	class c_listener : public i_game_event_listener {
	public:
		c_listener( ) = default;
		~c_listener( ) = default;

		void fire_game_event( i_game_event* event );
		int get_event_debug_id( ) { return 42; }
	};

	bool instance( );

	void reset( );

	void player_hurt( i_game_event* event );
	
	inline c_listener m_listener;
	
	inline std::unordered_map<uint32_t, std::function<void( i_game_event* )>> m_callbacks;
}