#include "ctx.h"

bool c_local_player::can_shoot( ) {
	if ( !m_local || !m_local->is_alive( ) )
		return false;

	if ( ( m_local->get_tickbase( ) * interfaces::global_vars->m_interval_per_tick ) <= m_local->get_next_attack( ) )
		return false;

	if ( !ctx::m_weapon )
		return false;

	if ( ctx::m_weapon.get( )->is_nade( ) )
		return true;

	static float lastFire = 0, nextAttack = 0;
	static c_cs_weapon* old_weapon;
	float snextAttack = ctx::m_weapon.get( )->get_next_primary( );
	if ( lastFire != ctx::m_weapon.get( )->get_last_shot_time( ) || ctx::m_weapon.get( ) != old_weapon ) {
		nextAttack = ctx::m_weapon.get( )->get_next_primary( );
		lastFire = ctx::m_weapon.get( )->get_last_shot_time( );
	}

	if ( ctx::m_weapon.get( )->get_ammo( ) == 0 )
		return false;

	old_weapon = ctx::m_weapon.get( );

	return ( nextAttack <= m_local->get_tickbase( ) * interfaces::global_vars->m_interval_per_tick );
}