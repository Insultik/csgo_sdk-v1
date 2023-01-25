#pragma once
#include "misc/movement.h"
#include "antiaim/antiaim.h"
#include "animations/local_animations.h"
#include "animations/animations.h"
#include "animations/lagcomp.h"
#include "events/events.h"
#include "listeners/listeners.h"

namespace features {
	void draw_features( );

	void create_move( );

	void frame_stage_notify( int stage );
}