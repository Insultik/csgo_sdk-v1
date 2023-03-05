#pragma once
#include "lagcomp.hpp"

namespace anim_system {
	void update_player( c_cs_player* player );

	void update_animations( c_cs_player* player, c_lag_record* record, c_lag_record* prev_record, int rotation = 0 );

	void backup_info( );
	void restore_info( );

	inline ctx::backup_info_t m_backup_info;
}