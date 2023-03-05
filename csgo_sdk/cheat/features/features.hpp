#pragma once
#include "misc/movement.hpp"
#include "antiaim/antiaim.hpp"
#include "animations/local_animations.hpp"
#include "animations/animations.hpp"
#include "animations/lagcomp.hpp"
#include "events/events.hpp"
#include "listeners/listeners.hpp"
#include "visuals/players.hpp"

namespace features {
	void draw_features( );

	void create_move( );

	void frame_stage_notify( int stage );
}