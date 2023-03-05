#pragma once

#include <windows.h>
#include <cstdint>
#include <unordered_map>
#include <any>
#include <typeinfo>
#include <string>

#include "../ct_hash.hpp"

#define ADD_VAR( type, name, value ) c_var<type> name = g_configs.add< type >(#name, value)

#define BINDS HASH( "class std::vector<class KeyBind,class std::allocator<class KeyBind> >" )

inline const char *g_key_names[ ] = {
        "none",
        "m1",
        "m2",
        "cancel",
        "m3",
        "m4",
        "m5",
        "none",
        "back",
        "tab",
        "none",
        "none",
        "clear",
        "return",
        "none",
        "none",
        "shift",
        "ctrl",
        "menu",
        "pause",
        "caps",
        "kana",
        "none",
        "junja",
        "final",
        "kanji",
        "none",
        "esc",
        "convert",
        "nonconvert",
        "accept",
        "modechange",
        "space",
        "prior",
        "next",
        "end",
        "home",
        "left",
        "up",
        "right",
        "down",
        "select",
        "print",
        "execute",
        "snapshot",
        "insert",
        "del",
        "help",
        "0",
        "1",
        "2",
        "3",
        "4",
        "5",
        "6",
        "7",
        "8",
        "9",
        "none",
        "none",
        "none",
        "none",
        "none",
        "none",
        "none",
        "a",
        "b",
        "c",
        "d",
        "e",
        "f",
        "g",
        "h",
        "i",
        "j",
        "k",
        "l",
        "m",
        "n",
        "o",
        "p",
        "q",
        "r",
        "s",
        "t",
        "u",
        "v",
        "w",
        "x",
        "y",
        "z",
        "lwin",
        "rwin",
        "apps",
        "none",
        "sleep",
        "num0",
        "num1",
        "num2",
        "num3",
        "num4",
        "num5",
        "num6",
        "num7",
        "num8",
        "num9",
        "multiply",
        "add",
        "separator",
        "subtract",
        "decimal",
        "divide",
        "f1",
        "f2",
        "f3",
        "f4",
        "f5",
        "f6",
        "f7",
        "f8",
        "f9",
        "f10",
        "f11",
        "f12",
        "f13",
        "f14",
        "f15",
        "f16",
        "f17",
        "f18",
        "f19",
        "f20",
        "f21",
        "f22",
        "f23",
        "f24",
        "none",
        "none",
        "none",
        "none",
        "none",
        "none",
        "none",
        "none",
        "num",
        "scroll",
        "oem_nec_equal",
        "oem_fj_masshou",
        "oem_fj_touroku",
        "oem_fj_loya",
        "oem_fj_roya",
        "none",
        "none",
        "none",
        "none",
        "none",
        "none",
        "none",
        "none",
        "none",
        "lshift",
        "rshift",
        "lctrl",
        "rctrl",
        "lmenu",
        "rmenu"
};

enum KeyMode {
    ON_KEY,
    TOGGLE
};

class c_item {
public:
    template <typename _Ty>
    _Ty &get( ) { return *reinterpret_cast< _Ty * >( std::any_cast< _Ty >( &m_any ) ); }

    std::any  m_any;
    uint32_t  m_type;
    uint32_t  m_id;
};

template <typename _Ty>
class c_var {
public:
    operator _Ty ( ) const { return m_item->get<_Ty>( ); }
    __forceinline _Ty &get( ) { return m_item->get<_Ty>( ); }

    c_item*m_item;
};

class c_key_bind {
public:
    __forceinline c_key_bind( ) = default;

    template <typename _Ty>
    __forceinline c_key_bind( c_item*item, std::string name, bool show_in_binds, int key_id, int mode, _Ty set, std::string combo_value = "None" ) : m_name{ name }, m_show_in_binds{ show_in_binds }, m_key_id{ key_id }, m_mode{ mode }, m_item_id{ item->m_id } {
        m_any   = std::make_any<_Ty>( set );
        m_type  = hash( typeid( set ).name( ) );
        m_combo_value = combo_value;
        sanitize( );
    }

    __forceinline void sanitize( ) {
        m_process = false;
        m_active = false;
        m_adjust = false;
    }

    template <typename _Ty>
    _Ty set( ) { return *reinterpret_cast< _Ty * >( std::any_cast< _Ty >( &m_any ) ); }

    template <typename _Ty>
    _Ty old( ) { return *reinterpret_cast< _Ty * >( std::any_cast< _Ty >( &m_old ) ); }

    void think( );

    std::string m_name;
    std::string m_combo_value;

    std::any m_any{ };
    std::any m_old{ };
    uint32_t m_type{ };
    uint32_t m_item_id{ };

    bool  m_process{ };
    bool  m_show_in_binds{ };

    bool  m_active{ };
    bool  m_adjust{ false };
    int   m_key_id{ };
    int   m_mode{ };
};

struct KeyPopup_t {
    const char  *m_bind_state;
    bool         m_waiting_key;
    bool         m_next_value;
    bool         m_show_in_binds;
    int          m_key_id{ -1 };
    int          m_select{ -1 };
    int          m_mode;
    bool         m_avaiable;
    bool         m_bool;
    int          m_int;
    float        m_float;

    float m_alpha = 0.f;
};

using binds_t = std::vector< c_key_bind >;

class c_configs {
public:
    std::unordered_map< uint32_t, c_item >                      m_items;
    std::unordered_map< uint32_t, std::vector< c_key_bind > >   m_key_binds;
    std::unordered_map< uint32_t, KeyPopup_t >                  m_popups;

public:
    void save( const char *txt );
    void load( const char *txt );

    void think( );

    bool instance( );

    void setup_var( c_var< bool > var, std::string item_name, bool value ) {
        var = this->add< bool >( item_name, value );
    }

    void setup_var( c_var< float > var, std::string item_name, float value ) {
        var = this->add< float >( item_name, value );
    }

    void setup_var( c_var< int > var, std::string item_name, int value ) {
        var = this->add< int >( item_name, value );
    }

    void setup_var( c_var< bool* > var, std::string item_name, bool* value ) {
        var = this->add< bool* >( item_name, value );
    }

    binds_t get_active_binds( ) {
        binds_t binds;

        for ( auto &&[item_id, key_binds] : m_key_binds ) {
            for ( auto &key : key_binds ) {
                if ( key.m_active )
                    binds.push_back( key );
            }
        }

        return binds;
    }

    template <typename _Ty>
    c_var<_Ty> add( std::string item_name, _Ty value ) {
        uint32_t item_id = HASH( ( std::to_string( m_items.size( ) ) + item_name ).c_str( ) );
        c_var<_Ty>  var;
        c_item      *item;

        if ( m_key_binds.find( item_id ) == m_key_binds.end( ) ) {
            m_key_binds[ item_id ] = { };
            m_popups[ item_id ] = KeyPopup_t( );
        }

        m_items[ item_id ] = { std::make_any<_Ty>( value ), hash( typeid( value ).name( ) ), item_id };

        item = &m_items[ item_id ];
        var = { item };

        return var;
    }
} inline g_configs;

class c_variables {
public:
    struct {

    } m_visuals;

    struct {

    } m_misc;

    ADD_VAR( binds_t, binds, binds_t{ } );
} inline g_settings;
