#include "eng_prediction.hpp"

void eng_prediction::prepare( ) {
	/*if ( m_last_frame_stage == valve::e_frame_stage::net_update_end ) {
		valve::g_prediction->update(
			valve::g_client_state->m_delta_tick,
			valve::g_client_state->m_delta_tick > 0,
			valve::g_client_state->m_last_cmd_ack,
			valve::g_client_state->m_last_cmd_out + valve::g_client_state->m_choked_cmds
		);

		if ( const auto weapon = valve::g_local_player->weapon( ) )
			if ( weapon->item_index( ) == valve::e_item_index::revolver
				 && weapon->postpone_fire_ready_time( ) == std::numeric_limits< float >::max( ) )
				weapon->postpone_fire_ready_time( ) = m_postpone_fire_ready_time;
	}

	m_backup.m_cur_time = valve::g_global_vars->m_cur_time;
	m_backup.m_frame_time = valve::g_global_vars->m_frame_time;

	valve::g_global_vars->m_cur_time = valve::to_time( valve::g_local_player->tick_base( ) );
	valve::g_global_vars->m_frame_time = valve::g_global_vars->m_interval_per_tick;*/
}

void eng_prediction::predict( const c_user_cmd* user_cmd ) {
	/*m_net_vars.at( ( user_cmd->m_command_number - 1 ) % 150 ).restore( user_cmd->m_command_number - 1 );

	m_local_data.at( user_cmd->m_command_number % 150 ).init( *user_cmd );

	g_context->addresses( ).m_pred_player = valve::g_local_player;
	*g_context->addresses( ).m_pred_seed = user_cmd->m_random_seed;

	valve::g_local_player->set_local_view_angles( user_cmd->m_view_angles );

	valve::g_local_player->cur_user_cmd( ) = user_cmd;
	valve::g_local_player->last_user_cmd( ) = *user_cmd;

	const auto backup_in_prediction = valve::g_prediction->m_in_prediction;
	const auto backup_first_time_predicted = valve::g_prediction->m_first_time_predicted;

	valve::g_prediction->m_in_prediction = true;
	valve::g_prediction->m_first_time_predicted = false;

	valve::g_move_helper->set_host( valve::g_local_player );

	valve::g_movement->start_track_prediction_errors( valve::g_local_player );

	const auto backup_velocity_modifier = valve::g_local_player->velocity_modifier( );

	valve::g_prediction->setup_move( valve::g_local_player, user_cmd, valve::g_move_helper, &m_move_data );

	valve::g_movement->process_movement( valve::g_local_player, &m_move_data );

	valve::g_prediction->finish_move( valve::g_local_player, user_cmd, &m_move_data );

	valve::g_movement->finish_track_prediction_errors( valve::g_local_player );

	valve::g_move_helper->set_host( nullptr );

	if ( const auto weapon = valve::g_local_player->weapon( ) ) {
		weapon->update_inaccuracy( );

		m_inaccuracy = weapon->inaccuracy( );
		m_spread = weapon->spread( );

		const auto item_index = weapon->item_index( );
		const auto v11 =
			item_index == valve::e_item_index::awp || item_index == valve::e_item_index::g3sg1
			|| item_index == valve::e_item_index::scar20 || item_index == valve::e_item_index::ssg08;
		const auto wpn_data = weapon->wpn_data( );

		if ( valve::g_local_player->flags( ) & valve::e_ent_flags::ducking )
			m_min_inaccuracy = v11 ? wpn_data->m_inaccuracy_crouch_alt : wpn_data->m_inaccuracy_crouch;
		else
			m_min_inaccuracy = v11 ? wpn_data->m_inaccuracy_stand_alt : wpn_data->m_inaccuracy_stand;
	}
	else
		m_inaccuracy = m_spread = 0.f;

	m_local_data.at( user_cmd->m_number % 150 ).save( user_cmd->m_number );

	valve::g_local_player->velocity_modifier( ) = backup_velocity_modifier;

	valve::g_prediction->m_in_prediction = backup_in_prediction;
	valve::g_prediction->m_first_time_predicted = backup_first_time_predicted;*/

	update_shoot_pos( );
}

void eng_prediction::restore( ) {
	/*g_context->addresses( ).m_pred_player = nullptr;
	*g_context->addresses( ).m_pred_seed = -1;

	valve::g_global_vars->m_cur_time = m_backup.m_cur_time;
	valve::g_global_vars->m_frame_time = m_backup.m_frame_time;*/
}

void eng_prediction::update_shoot_pos( ) {
	/*const auto anim_state = valve::g_local_player->anim_state( );
	if ( !anim_state )
		return;

	valve::g_local_player->set_abs_angles( { 0.f, anim_state->m_foot_yaw, 0.f } );

	auto& bones = g_anim_sync->local_data( ).m_shoot_pos_bones;
	g_anim_sync->setup_bones( valve::g_local_player, bones, valve::g_global_vars->m_cur_time, 15 );

	auto eye_pos = valve::g_local_player->origin( ) + valve::g_local_player->view_offset( );

	if ( anim_state->m_player
		 && ( anim_state->m_landing || anim_state->m_duck_amount || anim_state->m_player->ground_entity( ) == valve::e_ent_handle::invalid ) ) {
		const auto bone_index = valve::g_local_player->lookup_bone( "head_0" );
		if ( bone_index != -1 ) {
			vec3_t head_pos {
				bones[ bone_index ][ 0u ][ 3u ],
				bones[ bone_index ][ 1u ][ 3u ],
				bones[ bone_index ][ 2u ][ 3u ] + 1.7f
			};

			if ( eye_pos.z > head_pos.z ) {
				const auto v5 = std::abs( eye_pos.z - head_pos.z );
				const auto v6 = std::max( ( v5 - 4.f ) / 6.f, 0.f );
				const auto v7 = std::min( v6, 1.f );

				eye_pos.z += ( ( ( v7 * v7 ) * 3.f ) - ( ( v7 + v7 ) * ( v7 * v7 ) ) ) * ( head_pos.z - eye_pos.z );
			}
		}
	}

	g_context->shoot_pos( ) = eye_pos;*/
}

__forceinline void eng_prediction::net_vars_t::restore( const int cmd_number ) const {
	if ( cmd_number != m_cmd_number )
		return;

	/*if ( std::abs( ctx::m_local.get( )->( ).z - m_view_offset_z ) <= 0.03125f )
		valve::g_local_player->view_offset( ).z = m_view_offset_z;

	const auto aim_punch_delta = valve::g_local_player->aim_punch( ) - m_aim_punch;
	if ( std::abs( aim_punch_delta.x ) <= 0.03125f
		 && std::abs( aim_punch_delta.y ) <= 0.03125f
		 && std::abs( aim_punch_delta.z ) <= 0.03125f )
		valve::g_local_player->aim_punch( ) = m_aim_punch;

	const auto aim_punch_vel_delta = valve::g_local_player->aim_punch_vel( ) - m_aim_punch_vel;
	if ( std::abs( aim_punch_vel_delta.x ) <= 0.03125f
		 && std::abs( aim_punch_vel_delta.y ) <= 0.03125f
		 && std::abs( aim_punch_vel_delta.z ) <= 0.03125f )
		valve::g_local_player->aim_punch_vel( ) = m_aim_punch_vel;*/
}

__forceinline void eng_prediction::net_vars_t::store( const int cmd_number ) {
	m_cmd_number = cmd_number;

	/*m_view_offset_z = std::clamp( valve::g_local_player->view_offset( ).z, 0.f, 64.f );
	m_aim_punch = valve::g_local_player->aim_punch( );
	m_aim_punch_vel = valve::g_local_player->aim_punch_vel( );*/
}

__forceinline void eng_prediction::local_data_t::init( const c_user_cmd& user_cmd ) {
	std::memset( this, 0, sizeof( local_data_t ) );

	/*g_eng_pred->velocity_modifier( ) = valve::g_local_player->velocity_modifier( );

	if ( const auto weapon = valve::g_local_player->weapon( ) ) {
		g_eng_pred->recoil_index( ) = weapon->recoil_index( );
		g_eng_pred->accuracy_penalty( ) = weapon->accuracy_penalty( );
	}

	m_spawn_time = valve::g_local_player->spawn_time( );
	m_tick_base = m_adjusted_tick_base = valve::g_local_player->tick_base( );*/

	m_user_cmd = user_cmd;

	store_anim( );

	/*m_net_vars.m_eye_angles = valve::g_local_player->eye_angles( );
	m_net_vars.m_aim_punch = valve::g_local_player->aim_punch( );
	m_net_vars.m_view_punch = valve::g_local_player->view_punch( );

	m_net_vars.m_origin = valve::g_local_player->origin( );
	m_net_vars.m_abs_origin = valve::g_local_player->abs_origin( );
	m_net_vars.m_obb_min = valve::g_local_player->obb_min( );
	m_net_vars.m_obb_max = valve::g_local_player->obb_max( );
	m_net_vars.m_velocity = valve::g_local_player->velocity( );
	m_net_vars.m_view_offset = valve::g_local_player->view_offset( );
	m_net_vars.m_aim_punch_vel = valve::g_local_player->aim_punch_vel( );
	m_net_vars.m_abs_velocity = valve::g_local_player->abs_velocity( );

	m_net_vars.m_strafing = valve::g_local_player->strafing( );
	m_net_vars.m_scoped = valve::g_local_player->scoped( );
	m_net_vars.m_walking = valve::g_local_player->walking( );

	m_net_vars.m_move_state = valve::g_local_player->move_state( );
	m_net_vars.m_tick_base = valve::g_local_player->tick_base( );

	m_net_vars.m_duck_amount = valve::g_local_player->duck_amount( );
	m_net_vars.m_duck_speed = valve::g_local_player->duck_speed( );
	m_net_vars.m_third_person_recoil = valve::g_local_player->third_person_recoil( );
	m_net_vars.m_lby = valve::g_local_player->lby( );

	m_net_vars.m_flags = valve::g_local_player->flags( );
	m_net_vars.m_move_type = valve::g_local_player->move_type( );*/

	m_pred_net_vars = m_net_vars;
}

__forceinline void eng_prediction::local_data_t::save( const int cmd_number ) {
	if ( cmd_number != m_user_cmd.m_command_number )
		return;

	store_anim( );

	/*m_anim_state = *valve::g_local_player->anim_state( );

	m_pred_net_vars.m_eye_angles = valve::g_local_player->eye_angles( );
	m_pred_net_vars.m_aim_punch = valve::g_local_player->aim_punch( );
	m_pred_net_vars.m_view_punch = valve::g_local_player->view_punch( );

	m_pred_net_vars.m_origin = valve::g_local_player->origin( );
	m_pred_net_vars.m_abs_origin = valve::g_local_player->abs_origin( );
	m_pred_net_vars.m_obb_min = valve::g_local_player->obb_min( );
	m_pred_net_vars.m_obb_max = valve::g_local_player->obb_max( );
	m_pred_net_vars.m_velocity = valve::g_local_player->velocity( );
	m_pred_net_vars.m_view_offset = valve::g_local_player->view_offset( );
	m_pred_net_vars.m_aim_punch_vel = valve::g_local_player->aim_punch_vel( );
	m_pred_net_vars.m_abs_velocity = valve::g_local_player->abs_velocity( );

	m_pred_net_vars.m_strafing = valve::g_local_player->strafing( );
	m_pred_net_vars.m_scoped = valve::g_local_player->scoped( );
	m_pred_net_vars.m_walking = valve::g_local_player->walking( );

	m_pred_net_vars.m_move_state = valve::g_local_player->move_state( );
	m_pred_net_vars.m_tick_base = valve::g_local_player->tick_base( );

	m_pred_net_vars.m_duck_amount = valve::g_local_player->duck_amount( );
	m_pred_net_vars.m_duck_speed = valve::g_local_player->duck_speed( );
	m_pred_net_vars.m_third_person_recoil = valve::g_local_player->third_person_recoil( );
	m_pred_net_vars.m_lby = valve::g_local_player->lby( );

	m_pred_net_vars.m_flags = valve::g_local_player->flags( );
	m_pred_net_vars.m_move_type = valve::g_local_player->move_type( );*/
}

__forceinline void eng_prediction::local_data_t::store_anim( ) {
	/*if ( const auto anim_state = valve::g_local_player->anim_state( ) ) {
		m_anim_state = *anim_state;
		m_abs_yaw = anim_state->m_foot_yaw;
	}

	m_anim_layers = valve::g_local_player->anim_layers( );
	m_pose_params = valve::g_local_player->pose_params( );*/
}

__forceinline void eng_prediction::local_data_t::restore_anim( const bool layers ) const {
	/*if ( const auto anim_state = valve::g_local_player->anim_state( ) )
		*anim_state = m_anim_state;

	if ( layers )
		valve::g_local_player->anim_layers( ) = m_anim_layers;

	valve::g_local_player->pose_params( ) = m_pose_params;

	valve::g_local_player->set_abs_angles( { 0.f, m_abs_yaw, 0.f } );*/
}