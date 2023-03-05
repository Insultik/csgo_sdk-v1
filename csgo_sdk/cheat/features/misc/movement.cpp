#include "movement.hpp"

void movement::on_createmove( ) {
	if ( !ctx::m_local.alive( ) )
		return;

	m_view = ctx::m_angles.view;

	bunny_hop( );
	auto_strafe( );
}

void movement::rotate( ang_t& wish_angles ) {
	if ( ctx::m_cmd->m_view_angles.roll != 0.f && !ctx::m_local.get( )->get_flags( ).has( fl_on_ground ) ) {
		ctx::m_cmd->m_side_move = 0.f;
	}

	auto move_2d = vec3_t( ctx::m_cmd->m_forward_move, ctx::m_cmd->m_side_move, 0.f );

	if ( const auto speed_2d = move_2d.length( ) ) {
		const auto delta = ctx::m_cmd->m_view_angles.yaw - wish_angles.yaw;

		vec2_t v1;

		math::sin_cos( math::deg_to_rad( remainderf( math::rad_to_deg( math::atan2( move_2d.y / speed_2d, move_2d.x / speed_2d ) ) + delta, 360.f ) ), v1.x, v1.y );

		const auto cos_x = math::cos( math::deg_to_rad( remainderf( math::rad_to_deg( math::atan2( 0.f, speed_2d ) ), 360.f ) ) );

		move_2d.x = cos_x * v1.y * speed_2d;
		move_2d.y = cos_x * v1.x * speed_2d;

		if ( ctx::m_local.get( )->get_move_type( ) == move_type_ladder ) {
			if ( wish_angles.pitch < 45.f && std::fabsf( delta ) <= 65.f && ctx::m_cmd->m_view_angles.pitch >= 45.f )
				move_2d.x *= -1.f;
		}
		else if ( std::fabsf( ctx::m_cmd->m_view_angles.pitch ) > 90.f )
			move_2d.x *= -1.f;
	}

	const auto max_forward_speed = 450.f;
	const auto max_side_speed = 450.f;
	const auto max_up_speed = 320.f;

	ctx::m_cmd->m_forward_move = std::clamp( move_2d.x, -max_forward_speed, max_forward_speed );
	ctx::m_cmd->m_side_move = std::clamp( move_2d.y, -max_side_speed, max_side_speed );
	ctx::m_cmd->m_up_move = std::clamp( ctx::m_cmd->m_up_move, -max_up_speed, max_up_speed );
}

void movement::bunny_hop( ) {
	if ( ctx::m_local.get( )->get_move_type( ) == move_type_ladder || ctx::m_local.get( )->get_move_type( ) == move_type_noclip )
		return;

	if ( ctx::m_local.get( )->get_flags( ).has( fl_on_ground ) )
		return;

	ctx::m_cmd->m_buttons.remove( in_jump );
}

void movement::auto_strafe( ) {
	
}