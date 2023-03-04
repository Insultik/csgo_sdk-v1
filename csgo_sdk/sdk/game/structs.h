#pragma once
#include "../interfaces/classes/i_client_entity.h"
#include "../../utils/utils.h"
#include "../../utils/netvars/netvar_manager.h"
#include "enums.h"
#include "weapon.h"
#include "animstate.h"

namespace values {
    inline constexpr auto max_game_players = 65;
    inline constexpr auto max_sim_ticks = 32;
    inline constexpr auto mp_backup = 150u;
                          
    inline constexpr auto max_bones = 256u;
    inline constexpr auto max_layers = 13u;

    inline auto max_pitch = 89.f;
    inline constexpr auto max_roll = 50.f;
    inline constexpr auto teleport_dist = 4096.f;
}

#define DATA_MAP( datamap, func, type, name) \
	__forceinline type& func() { \
		static const auto offset = datamap->find(name); \
		return *reinterpret_cast<type*>(reinterpret_cast<uintptr_t>(this) + offset); \
	}

class c_base_entity : public i_client_entity {
public:    // table: DT_BaseEntity
    data_map_t* get_data_desc_map( ) {
        typedef data_map_t* ( __thiscall* o_fn )( void* );
        return utils::call_vfunc<o_fn>( this, 15 )( this );
    }

    data_map_t* get_pred_desc_map( ) {
        typedef data_map_t* ( __thiscall* o_fn )( void* );
        return utils::call_vfunc<o_fn>( this, 17 )( this );
    }

    VFUNC( is_weapon_entity( ), 166, bool( __thiscall* )( void* ) );

    VFUNC( is_player( ), 158, bool( __thiscall* )( void* ) );

    NETVAR( int, get_team, "DT_BaseEntity->m_iTeamNum" );
    NETVAR( int, get_anim_time, "DT_BaseEntity->m_flAnimTime" );
    NETVAR( vec3_t, get_origin, "DT_BaseEntity->m_vecOrigin" );
    NETVAR( int, get_model_index, "DT_BaseEntity->m_nModelIndex" );
    NETVAR( vec3_t, get_mins, "DT_BaseEntity->m_vecMins" );
    NETVAR( vec3_t, get_maxs, "DT_BaseEntity->m_vecMaxs" );
    NETVAR( int, get_collision_group, "DT_BaseEntity->m_CollisionGroup" );
    NETVAR( c_handle< c_base_entity >, get_owner, "DT_BaseEntity->m_hOwnerEntity" );
    NETVAR( c_handle< c_base_entity >, get_thrower_handle, "DT_BaseGrenade->m_hThrower" );
    NETVAR( ang_t, get_rotation, "DT_BaseEntity->m_angRotation" );
    NETVAR( bool, is_spotted, "DT_BaseEntity->m_bSpotted" );
    NETVAR_OFFSET( e_move_type, get_move_type, "DT_BaseEntity->m_nRenderMode", 0x1 );
    NETVAR_OFFSET( matrix_t, get_coordinate_frame, "DT_BaseEntity->m_CollisionGroup", -0x30 );
};

class c_base_player : public c_base_entity {
public:    // table: DT_BasePlayer
    DATA_MAP( get_pred_desc_map( ), get_duck_amount, float, "m_flDuckAmount" );

    DATA_MAP( get_pred_desc_map( ), get_ground_entity, c_base_handle, "m_hGroundEntity" );
    DATA_MAP( get_pred_desc_map( ), get_move_type, uint8_t, "m_MoveType" );
    DATA_MAP( get_pred_desc_map( ), get_next_attack, float, "m_flNextAttack" );

    DATA_MAP( get_pred_desc_map( ), get_impulse, int, "m_nImpulse" );
    DATA_MAP( get_pred_desc_map( ), get_buttons, bit_flag_t<uint32_t>, "m_nButtons" );
    DATA_MAP( get_pred_desc_map( ), get_buttons_last, bit_flag_t<uint32_t>, "m_afButtonLast" );
    DATA_MAP( get_pred_desc_map( ), get_buttons_pressed, bit_flag_t<uint32_t>, "m_afButtonPressed" );
    DATA_MAP( get_pred_desc_map( ), get_buttons_released, bit_flag_t<uint32_t>, "m_afButtonReleased" );

    DATA_MAP( get_pred_desc_map( ), get_effects, bit_flag_t<uint32_t>, "m_fEffects" );
    DATA_MAP( get_pred_desc_map( ), get_eflags, bit_flag_t<uint32_t>, "m_iEFlags" );

    NETVAR_OFFSET( bit_flag_t<uint32_t>, get_button_disabled, "DT_BasePlayer->m_hViewEntity", -0xC );
    NETVAR_OFFSET( bit_flag_t<uint32_t>, get_button_forced, "DT_BasePlayer->m_hViewEntity", -0x8 );

    NETVAR( bit_flag_t<uint32_t>, get_flags, "DT_BasePlayer->m_fFlags" );
    NETVAR( vec3_t, get_velocity, "DT_BasePlayer->m_vecVelocity[0]" );

    NETVAR( float, get_sim_time, "DT_CSPlayer->m_flSimulationTime" );
    NETVAR( int, get_health, "DT_BasePlayer->m_iHealth" );
    NETVAR( float, get_life_state, "DT_BasePlayer->m_lifeState" );

    NETVAR_OFFSET( float, get_last_sim_time, "DT_CSPlayer->m_flSimulationTime", 0x4 );

    NETVAR( bool, is_immune, "DT_CSPlayer->m_bGunGameImmunity" );

    OFFSET( int, get_occlusion_frame, 0xA30 );
    OFFSET( unsigned int, get_anim_lod_flags, 0xA28 );
    OFFSET( int, get_client_effects, 0x68 );

    OFFSET( int, get_last_skip_framecount, 0xA68 );
    OFFSET( bool, get_maintain_sequence_transition, 0x9F0 );
    OFFSET( bool, get_jiggle_bones, 0x2930 );
    OFFSET( vec3_t, get_abs_velocity, 0x94 );
    OFFSET( int, get_take_damage, 0x280 );
    OFFSET( c_utl_vector<matrix_t>, get_bone_cache, 0x2914 );
    OFFSET( bool, should_use_new_anim_state, 0x9B14 );
    OFFSET( int, get_custom_blending_rule_mask, 0xA24 );
    OFFSET( float, get_spawn_time, 0x103C0 );
    OFFSET( int, get_next_think_tick, 0xFC );
    OFFSET( c_user_cmd*, get_current_cmd, 0x3348 );
    OFFSET( c_user_cmd*, get_last_cmd, 0x3298 );
    OFFSET( bool, addon_models_are_out_of_date, 0x1179E );
    OFFSET( uint32_t, get_last_bone_setup_time, 0x2928 );
    OFFSET( uint32_t, get_most_recent_model_bone_counter, 0x2690 );
    OFFSET( c_studio_hdr*, get_studio_hdr, 0x2950 );

    NETVAR( e_observer_mode, get_observer_mode, "DT_BasePlayer->m_iObserverMode" );
    NETVAR( c_handle< c_base_player >, get_observer_target, "DT_BasePlayer->m_hObserverTarget" );

    __forceinline void set_abs_angles( const ang_t angles ) {
        static auto _fn = reinterpret_cast< void( __thiscall* )( void*, const ang_t& ) >( utils::find_sig( "client.dll", "55 8B EC 83 E4 F8 83 EC 64 53 56 57 8B F1 E8" ) );
        return _fn( this, angles );
    };

    __forceinline void set_abs_origin( const vec3_t position ) {
        static auto _fn = reinterpret_cast< void( __thiscall* )( void*, const vec3_t& ) >( utils::find_sig( "client.dll", "55 8B EC 83 E4 F8 51 53 56 57 8B F1 E8" ) );
        return _fn( this, position );
    };

    void setup_bones_attachment_helper( ) {
        static auto sig_fn = reinterpret_cast< void( __thiscall* )( void*, c_studio_hdr* ) >( utils::find_sig( "client.dll", "55 8B EC 83 EC 48 53 8B 5D 08 89 4D F4" ) );
        //return sig_fn( this, this->get_model_ptr( ) );
    }

    __forceinline void invalidate_bone_cache( ) {
        static auto invalidate_bone_cache_fn = reinterpret_cast< uintptr_t >( utils::find_sig( "client.dll", "80 3D ? ? ? ? ? 74 16 A1 ? ? ? ? 48 C7 81" ) + 10 );

        this->get_last_bone_setup_time( ) = 0xFF7FFFFF;
        this->get_most_recent_model_bone_counter( ) = invalidate_bone_cache_fn - 1;
    }

    __forceinline bool is_alive( ) {
        int state = get_life_state( );
        auto health = get_health( ) > 0;
        return state == 0 && health;
    }
};

class c_base_animating : public c_base_player {
public:
    std::array<float, 24>& get_pose_params( ) {
        static int poses_off = net_vars::get_offset( "DT_BaseAnimating->m_flPoseParameter" );
        return *( std::array<float, 24>* )( uintptr_t( this ) + poses_off );
    }

    anim_layer_t* get_animoverlays( ) {
        return *( anim_layer_t** ) ( ( DWORD ) this + 0x2990 );
    }

    NETVAR( bool, get_client_side_animation, "DT_BaseAnimating->m_bClientSideAnimation" );
    NETVAR( int, get_sequence, "DT_BaseAnimating->m_nSequence" );

    VFUNC( get_layer_sequence_cycle_rate( anim_layer_t* layer, int sequence ), 223, float( __thiscall* )( void*, anim_layer_t*, int ), layer, sequence );

    bone_accessor_t* get_bone_accessor( ) {
        return *( bone_accessor_t** ) ( ( DWORD ) this + 0x26A4 );
    }

    __forceinline int select_weighted_sequence_from_modifiers( int activity, void* modifiers, int size ) {

        const auto hdr = get_studio_hdr( );
        if ( !hdr )
            return -1;

        if ( !hdr->m_activity_to_sequence ) {
            hdr->m_activity_to_sequence = hdr->find_mapping( );
        }

        return hdr->m_activity_to_sequence->select_weighted_sequence_from_modifiers( hdr, activity, modifiers, size );
    }

    int get_sequence_activity( int sequence );
};

class c_base_attributable_item : public c_base_entity {
public:
    NETVAR( uint64_t, get_original_owner_xuid, _( "DT_BaseAttributableItem->m_OriginalOwnerXuidLow" ) );
    NETVAR( int, get_original_owner_xuid_low, _( "DT_BaseAttributableItem->m_OriginalOwnerXuidLow" ) );
    NETVAR( int, get_original_owner_xuid_high, _( "DT_BaseAttributableItem->m_OriginalOwnerXuidHigh" ) );
    NETVAR( int, get_fallback_stat_trak, _( "DT_BaseAttributableItem->m_nFallbackStatTrak" ) );
    NETVAR( int, get_fallback_paint_kit, _( "DT_BaseAttributableItem->m_nFallbackPaintKit" ) );
    NETVAR( int, get_fallback_seed, _( "DT_BaseAttributableItem->m_nFallbackSeed" ) );
    NETVAR( float, get_fallback_wear, _( "DT_BaseAttributableItem->m_flFallbackWear" ) );
    NETVAR( bool, is_initialized, _( "DT_BaseAttributableItem->m_bInitialized" ) );
    NETVAR( int, get_entity_level, _( "DT_BaseAttributableItem->m_iEntityLevel" ) );
    NETVAR( int, get_account_id, _( "DT_BaseAttributableItem->m_iAccountID" ) );
    NETVAR( int, get_item_id_low, _( "DT_BaseAttributableItem->m_iItemIDLow" ) );
    NETVAR( int, get_item_id_high, _( "DT_BaseAttributableItem->m_iItemIDHigh" ) );
    NETVAR( int, get_entity_quality, _( "DT_BaseAttributableItem->m_iEntityQuality" ) );
    NETVAR( char, get_custom_name, _( "DT_BaseAttributableItem->m_szCustomName" ) );
    NETVAR( int, get_weapon_index, "DT_BaseAttributableItem->m_iItemDefinitionIndex" );
};

class c_cs_weapon : public c_base_attributable_item {
public:
    VFUNC( get_inaccuracy( ), 483, float( __thiscall* )( void* ) );
    VFUNC( get_spread( ), 453, float( __thiscall* )( void* ) );
    VFUNC( update_accuracy_penalty( ), 484, void( __thiscall* )( void* ) );
    VFUNC( set_model_index( int index ), 484, void( __thiscall* )( void*, int ), index );

    void pre_data_update( int type ) {
        PVOID networkable = ( PVOID ) ( ( DWORD ) ( this ) + 0x8 );
        typedef void( __thiscall* o_fn )( PVOID, int );
        return utils::call_vfunc<o_fn>( networkable, 6 )( networkable, type );
    }

    void set_glove_model_index( int index ) {
        using o_fn = void( __thiscall* )( void*, int );
        return utils::call_vfunc<o_fn>( this, 75 )( this, index );
    }

    NETVAR( bool, get_pin_pulled, "DT_BaseCSGrenade->m_bPinPulled" );
    NETVAR( float, get_throw_time, "DT_BaseCSGrenade->m_fThrowTime" );
    NETVAR( float, get_throw_strength, "DT_BaseCSGrenade->m_flThrowStrength" );

    NETVAR( float, get_post_pone_fire_ready_time, "DT_WeaponCSBase->m_flPostponeFireReadyTime" );
    NETVAR( float, get_accuracy_penalty, "DT_WeaponCSBase->m_fAccuracyPenalty" );
    NETVAR( float, get_recoil_index, "DT_WeaponCSBase->m_flRecoilIndex" );
    NETVAR( float, get_last_shot_time, "DT_WeaponCSBase->m_fLastShotTime" );
    NETVAR( int, get_ammo, "DT_BaseCombatWeapon->m_iClip1" );
    NETVAR( int, get_zoom_level, "DT_WeaponCSBaseGun->m_zoomLevel" );
    NETVAR( float, get_next_primary,  "DT_BaseCombatWeapon->m_flNextPrimaryAttack" );
    NETVAR( float, get_next_secondary_attack, "DT_BaseCombatWeapon->m_flNextSecondaryAttack" );
    NETVAR( c_base_handle, get_world_model, "DT_BaseCombatWeapon->m_hWeaponWorldModel" );

    OFFSET( int, get_burst_shots_remain, 0x33E4 );
    OFFSET( bool, is_burst_mode, 0x3358 );

    c_cs_weapon_data* get_cs_weapon_data( ) {
       if ( !this )
            return nullptr;

        return interfaces::weapon_system->get_cs_weapon_data( this->get_weapon_index( ) );
    }

    std::wstring get_name( );

    __forceinline bool is_knife( ) {
        return this && get_cs_weapon_data( ) && get_cs_weapon_data( )->m_weapon_type == weapon_type_knife;
    }

    __forceinline bool is_nade( ) {
        return this && get_cs_weapon_data( ) && get_cs_weapon_data( )->m_weapon_type == weapon_type_grenade;
    }

    __forceinline bool is_medishot( ) {
        return this && get_cs_weapon_data( ) && get_cs_weapon_data( )->m_weapon_type == weapon_type_medishot;
    }

    __forceinline bool is_bomb( ) {
        return this && get_cs_weapon_data( ) && get_cs_weapon_data( )->m_weapon_type == weapon_type_c4;
    }

    __forceinline bool is_weapon( ) {
        return this && !is_knife( ) && !is_nade( ) && !is_medishot( ) && !is_bomb( );
    }

    // inferno_flame_lifetime
};

class c_cs_player : public c_base_animating {
public:
    VFUNC( update_client_side_animation( ), 224, void( __thiscall* )( void* ) );

    static __forceinline c_cs_player* get_player( int index ) {
        return ( c_cs_player* ) interfaces::entity_list->get_client_entity( index );
    }

    c_anim_state* get_anim_state( ) {
        return *reinterpret_cast< c_anim_state** >( reinterpret_cast< void* >( uintptr_t( this ) + 0x9960 ) );
    }

    NETVAR_PTR( c_base_handle, get_weapons, "DT_BaseCombatCharacter->m_hMyWeapons" );
    NETVAR_PTR( c_base_handle, get_wearables, "DT_BaseCombatCharacter->m_hMyWearables" );
    NETVAR( c_handle< c_cs_weapon >, get_active_weapon_handle, "DT_BaseCombatCharacter->m_hActiveWeapon" );
    NETVAR( bool, is_defusing, "DT_CSPlayer->m_bIsDefusing" );
    NETVAR( bool, has_defuser, "DT_CSPlayer->m_bHasDefuser" );
    NETVAR( int, get_tickbase, "DT_BasePlayer->m_nTickBase" );
    NETVAR( ang_t, get_eye_angles, "DT_CSPlayer->m_angEyeAngles" )

    __forceinline bool has_c4( ) {
        static auto has_c4_fn = utils::find_sig( "client.dll", "56 8B F1 85 F6 74 31" );
        return **( bool** ) ( this + ( uint8_t ) has_c4_fn );
    }

    c_cs_weapon* get_active_weapon( ) {
        const auto& handle = get_active_weapon_handle( );
        return handle ? handle.get( ) : nullptr;
    }

    bool is_valid( e_valid_state state = valid_state_all );

    bool is_enemy( c_cs_player* from = nullptr );

    bool can_fire( int tickbase_shift = 0 );
    bool is_shooting( int tickbase_shift = 0 );
};