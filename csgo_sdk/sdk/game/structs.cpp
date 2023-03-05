#include "structs.hpp"
#include "../ctx.hpp"
#include "../math/math.hpp"

bool c_cs_player::is_valid( e_valid_state state ) {
    if ( !this )
        return false;

    if ( ( state == valid_state_enemy || state != valid_state_enemy_dormant ) && !this->is_enemy( ) )
        return false;

    if ( ( state == valid_state_enemy_dormant || state == valid_state_all_dormant ) && this->is_dormant( ) )
        return false;

    if ( !this->is_alive( ) || this->get_flags( ).has( fl_frozen ) || this->is_immune( ) )
        return false;

    return true;
}

bool c_cs_player::can_fire( int shift_amount ) {
    c_cs_weapon* weapon = this->get_active_weapon( ); c_cs_weapon_data* weapon_data { };
    if ( !weapon )
        return false;

    if ( weapon_data = weapon->get_cs_weapon_data( ); !weapon_data )
        return false;
    
    if ( !weapon->is_weapon( ) || weapon->get_ammo( ) <= 0 )
        return true;

    float server_time = interfaces::global_vars->m_current_time - ticks_to_time( shift_amount );
    if ( this->get_next_attack( ) > server_time || weapon->get_next_primary( ) > server_time )
        return false;
     
    if ( weapon->get_weapon_index( ) != weapon_revolver ) 
        return true;
    
    return weapon->get_post_pone_fire_ready_time( ) + ticks_to_time( 14 ) >= server_time;
}

bool c_cs_player::is_shooting( int tickbase_shift ) {
    auto* weapon = ctx::m_weapon.get( );
    if ( !weapon || !ctx::m_cmd )
        return false;

    if ( weapon->get_weapon_index( ) == weapon_c4 || weapon->get_weapon_index( ) == weapon_healthshot )
        return false;

    if ( weapon->is_nade( ) ) 
        return !weapon->get_pin_pulled( ) && weapon->get_throw_time( ) > 0.f && weapon->get_throw_time( ) <= interfaces::global_vars->m_current_time - ticks_to_time( tickbase_shift );
    
    if ( weapon->is_knife( ) )
        return ctx::m_cmd->m_buttons.has( in_attack ) || ctx::m_cmd->m_buttons.has( in_attack2 );

    if ( weapon->is_burst_mode( ) )
        return weapon->get_burst_shots_remain( ) == 0 ? ( ctx::m_cmd->m_buttons.has( in_attack ) && this->can_fire( tickbase_shift ) ) : true;

    if ( weapon->get_weapon_index( ) != weapon_revolver )
        return ctx::m_cmd->m_buttons.has( in_attack ) && this->can_fire( tickbase_shift );

    return ctx::m_cmd->m_buttons.has( in_attack ) && this->can_fire( tickbase_shift );
}

bool c_cs_player::is_enemy( c_cs_player* from ) {
    c_cs_player* check_player = from ? from : ctx::m_local.get( );
    if ( !this || !check_player )
        return false;

    /*if ( cvars::mp_teammates_are_enemies->get< int >( ) )
        return true;*/
    if ( check_player == ctx::m_local.get( ) ) {
        if ( this->get_team( ) != ctx::m_local.get_team( ) )
            return true;
    }
    else if ( this->get_team( ) != check_player->get_team( ) )
        return true;

    return false;
}