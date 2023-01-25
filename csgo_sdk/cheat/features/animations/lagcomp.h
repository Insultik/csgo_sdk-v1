#pragma once
#include "../../../main_includes.h"
#include <deque>

namespace lag_comp {
	void instance( );

	float lerp_time( );
	bool valid_record( c_lag_record* record, bool force_dead = false );

	inline std::deque< c_lag_record > m_player_records[ max_game_players + 1 ];
}