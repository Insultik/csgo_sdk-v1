#pragma once
#include "game/structs.hpp"
#include "../utils/render/render.hpp"

enum e_player_side : int {
    side_left = 1,
    side_middle = 3,
    side_right = 2,
    side_server = 0
};

class c_lag_record {
public:
    c_lag_record( ) {
        m_origin = m_velocity = m_mins = m_maxs = vec3_t( 0, 0, 0 );

        m_angles = m_eye_angles = m_resolved_angles = ang_t( 0, 0, 0 );

        m_player = nullptr;

        m_duck_amount = m_sim_time = 0.f;

        m_choked_packets = m_flags = m_resolved_side = 0;

        m_invalid = m_jumped = m_animated = false;

        for ( int i = 0; i < 4; i++ )
            memcpy( m_matrix[ side_server ], 0, sizeof( matrix_t ) * 256.f );

        for ( int i = 0; i < 3; i++ )
            memcpy( m_layers[ i ], 0, sizeof( anim_layer_t ) * 13.f );
    }

    c_lag_record( c_cs_player* player ) {
        m_player = player;

        m_origin = player->get_abs_origin( );
        m_velocity = player->get_velocity( );

        m_mins = player->get_collideable( )->obb_mins( );
        m_maxs = player->get_collideable( )->obb_maxs( );

        m_angles = player->get_abs_angles( );
        m_eye_angles = m_resolved_angles = player->get_eye_angles( );

        m_duck_amount = player->get_duck_amount( );
        m_sim_time = player->get_sim_time( );
        m_choked_packets = std::clamp< int >( player->get_sim_time( ) - player->get_last_sim_time( ), 1, 16 );

        m_flags = player->get_flags( );
        m_resolved_side = e_player_side::side_server;

        m_invalid = false;
        m_jumped = player->get_flags( ).has( fl_on_ground );
        m_animated = false;

        for ( int i = 0; i < 4; i++ )
            memcpy( m_matrix[ i ], player->get_bone_cache( ).base( ), sizeof( matrix_t ) * 256.f );

        for ( int i = 0; i < 3; i++ )
            memcpy( m_layers[ i ], player->get_animoverlays( ), sizeof( anim_layer_t ) * 13.f );
    }
public:
    vec3_t m_origin { }, m_velocity { }, m_mins { }, m_maxs { };
    ang_t m_angles { }, m_eye_angles { }, m_resolved_angles { };
    float_t m_sim_time { }, m_duck_amount { };
    int32_t m_choked_packets { }, m_resolved_side { };
    bit_flag_t< uint32_t > m_flags { };
    bool m_invalid { }, m_jumped { }, m_animated { };
    c_cs_player* m_player { nullptr };
    anim_layer_t m_layers[ 3 ][ 13 ];
    matrix_t m_matrix[ 4 ][ 256 ];
};

class c_local_player {
    friend bool operator==( const c_local_player& lhs, c_cs_player* rhs ) { return lhs.m_local == rhs; }
public:
    operator bool( ) const { return m_local != nullptr; };

    __forceinline c_cs_player* get( ) const {
        return m_local;
    }

    __forceinline void instance( ) {
        this->m_local = ( c_cs_player* )interfaces::entity_list->get_client_entity( interfaces::engine->get_local_player( ) );
        if ( this->m_local )
            this->m_valid = true;
    };

    __forceinline bool valid( ) {
        if ( !m_local )
            return false;

        return m_valid && interfaces::engine->is_in_game( );
    }

    __forceinline bool alive( ) {
        if ( !valid( ) )
            return false;

        return m_local->is_alive( );
    }

    __forceinline int get_team( ) {
        if ( !this->valid( ) )
            return 0;

        if ( !this->alive( ) && m_local->get_observer_target( ).is_valid( ) )
            return m_local->get_observer_target( ).get( )->get_team( );

        return m_local->get_team( );
    }

    __forceinline void invalidate( ) {
        this->m_local = { };
        this->m_valid = { };
    }
    
    bool can_shoot( );
private:
    c_cs_player* m_local { };
    bool m_valid { };
};

class c_local_weapon {
public:
    operator bool( ) const { return m_weapon != nullptr; };

    __forceinline c_cs_weapon* get( ) const {
        return m_weapon;
    }

    __forceinline c_cs_weapon_data* data( ) const {
        return m_data;
    }

    __forceinline int index( ) {
        if ( !m_weapon )
            return -1;

        return this->m_index;
    }

    __forceinline void instance( c_cs_weapon* weapon ) {
        this->m_weapon = weapon;
        if ( weapon ) {
            this->m_index = weapon->get_weapon_index( );
            this->m_data = weapon->get_cs_weapon_data( );
            this->m_index = weapon->get_weapon_index( );
        }
    }

    __forceinline void invalidate( ) {
        this->m_weapon = { };
        this->m_data = { };
        this->m_index = { };
    }
private:
    c_cs_weapon* m_weapon { };
    c_cs_weapon_data* m_data { };
    int m_index {};
};

namespace ctx {
    struct backup_info_t {
        float m_real_time;
        int   m_frame_count;
        float m_absolute_frame_time;
        float m_cur_time;
        float m_frame_time;
        int   m_tick_count;
        float m_interpolation_amount;
    };

    struct {
        ang_t view { };
        ang_t fake { };
        ang_t real { };
        ang_t anim { };
    } inline m_angles;

    inline c_local_player m_local { };
    inline c_local_weapon m_weapon { };
    inline c_user_cmd* m_cmd { };
    inline bool m_send_packet { true };
    inline bool m_animating { };
    inline bool m_animating_fake { };
    inline bool m_menu_opened { };
};

