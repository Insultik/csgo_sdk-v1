#pragma once
#include "../../../main_includes.hpp"
#include <deque>

namespace lag_comp {
	void instance( );

	float lerp_time( );
	bool valid_record( c_lag_record* record, bool force_dead = false );

	inline std::deque< c_lag_record > m_player_records[ values::max_game_players ];
}