//#define KEY_BACKENDS 
#define _(txt) txt
#include "configs.hpp"
#define FOLDER _("configs")

//#include "imgui.hpp"
#include  "../../dependencies/json/json.hpp"
#include <filesystem>
#include <fstream>
#include "../../main_includes.hpp"

using namespace nlohmann;

void c_key_bind::think( ) {
    if ( interfaces::engine->is_console_opened( ) )
        return;

    if ( m_mode == TOGGLE ) {
        if ( GetKeyState( m_key_id ) & 0x8000 ) {
            if ( !m_adjust ) {
                m_adjust = true;
            }
        }
        else {
            if ( m_adjust ) {
                if ( !m_active )
                    m_old.reset( );

                for ( auto& key : g_configs.m_key_binds[ m_item_id ] ) {
                    if ( key.m_key_id == m_key_id )
                        continue;

                    key.m_active = false;

                    if ( key.m_old.has_value( ) && key.m_process ) {
                        switch ( key.m_type ) {
                            case HASH( "bool" ):
                                m_old = std::make_any<bool>( key.old<bool>( ) );
                                break;
                            case HASH( "int" ):
                                m_old = std::make_any<int>( key.old<int>( ) );
                                break;
                            case HASH( "float" ):
                                m_old = std::make_any<float>( key.old<float>( ) );
                                break;
                        }
                    }

                    key.m_process = false;
                }

                if ( !m_old.has_value( ) ) {
                    switch ( m_type ) {
                        case HASH( "bool" ):
                            m_old = std::make_any<bool>( g_configs.m_items[ m_item_id ].get<bool>( ) );
                            break;
                        case HASH( "int" ):
                            m_old = std::make_any<int>( g_configs.m_items[ m_item_id ].get<int>( ) );
                            break;
                        case HASH( "float" ):
                            m_old = std::make_any<float>( g_configs.m_items[ m_item_id ].get<float>( ) );
                            break;
                    }
                }

                m_active = !m_active;
                m_process = true;
                m_adjust = false;
            }
        }
    }

    if ( m_mode == ON_KEY ) {
        if ( GetKeyState( m_key_id ) & 0x8000 ) {
            if ( m_adjust ) {
                if ( !m_active )
                    m_old.reset( );

                for ( auto& key : g_configs.m_key_binds[ m_item_id ] ) {
                    if ( key.m_key_id == m_key_id )
                        continue;

                    key.m_active = false;

                    if ( key.m_old.has_value( ) && key.m_process ) {
                        switch ( key.m_type ) {
                            case HASH( "bool" ):
                                m_old = std::make_any<bool>( key.old<bool>( ) );
                                break;
                            case HASH( "int" ):
                                m_old = std::make_any<int>( key.old<int>( ) );
                                break;
                            case HASH( "float" ):
                                m_old = std::make_any<float>( key.old<float>( ) );
                                break;
                        }
                    }

                    key.m_process = false;
                }

                if ( !m_old.has_value( ) ) {
                    switch ( m_type ) {
                        case HASH( "bool" ):
                            m_old = std::make_any<bool>( g_configs.m_items[ m_item_id ].get<bool>( ) );
                            break;
                        case HASH( "int" ):
                            m_old = std::make_any<int>( g_configs.m_items[ m_item_id ].get<int>( ) );
                            break;
                        case HASH( "float" ):
                            m_old = std::make_any<float>( g_configs.m_items[ m_item_id ].get<float>( ) );
                            break;
                    }
                }

                m_active = true;
                m_process = true;
                m_adjust = false;
            }
        }
        else {
            if ( !m_adjust ) {
                m_active = false;
                m_process = true;
                m_adjust = true;
            }
        }
    }
}

bool c_configs::instance( ) {
    const auto path = std::filesystem::path { FOLDER };

    if ( !std::filesystem::create_directory( path.parent_path( ) ) )
        return false;


}

void c_configs::think( ) {
    for ( auto&& [item_id, key_binds] : g_configs.m_key_binds ) {
        for ( auto& key : key_binds ) {
            key.think( );

            if ( !key.m_active ) {
                if ( key.m_process && key.m_old.has_value( ) ) {
                    switch ( key.m_type ) {
                        case HASH( "bool" ):
                            m_items[ key.m_item_id ].get<bool>( ) = key.old<bool>( );
                            break;
                        case HASH( "int" ):
                            m_items[ key.m_item_id ].get<int>( ) = key.old<int>( );
                            break;
                        case HASH( "float" ):
                            m_items[ key.m_item_id ].get<float>( ) = key.old<float>( );
                            break;
                    }
                }

                key.m_old.reset( );
                key.m_process = false;
            }

            if ( !key.m_process )
                continue;

            switch ( key.m_type ) {
                case HASH( "bool" ):
                    m_items[ key.m_item_id ].get<bool>( ) = key.set<bool>( );
                    break;
                case HASH( "int" ):
                    m_items[ key.m_item_id ].get<int>( ) = key.set<int>( );
                    break;
                case HASH( "float" ):
                    m_items[ key.m_item_id ].get<float>( ) = key.set<float>( );
                    break;
            }
        }
    }
}

void c_configs::save( const char* txt ) {
    const auto path = std::filesystem::path { FOLDER } /= txt;

    std::filesystem::create_directory( path.parent_path( ) );

    auto out = json( );

    g_settings.binds.get( ).clear( );
    for ( auto&& [item_id, key_binds] : m_key_binds ) {
        for ( auto& key : key_binds ) {
            g_settings.binds.get( ).push_back( key );

            if ( key.m_process
                 && key.m_old.has_value( ) ) {
                switch ( key.m_type ) {
                    case HASH( "bool" ):
                        m_items[ key.m_item_id ].get<bool>( ) = key.old<bool>( );
                        break;
                    case HASH( "int" ):
                        m_items[ key.m_item_id ].get<int>( ) = key.old<int>( );
                        break;
                    case HASH( "float" ):
                        m_items[ key.m_item_id ].get<float>( ) = key.old<float>( );
                        break;
                }
            }
        }
    }

    for ( auto& [id, item] : m_items ) {
        auto cur = json( );

        cur[ _( "id" ) ] = id;
        cur[ _( "type" ) ] = item.m_type;

        switch ( item.m_type ) {
            case HASH( "int" ): cur[ _( "value" ) ] = item.get<int>( ); break;
            case HASH( "bool" ): cur[ _( "value" ) ] = item.get<bool>( ); break;
            case HASH( "float" ): cur[ _( "value" ) ] = item.get<float>( ); break;
            case HASH( "color_t" ):
            {
                const auto clr = item.get< color_t >( );

                nlohmann::json sub;

                for ( auto& value : clr.color_value ) {
                    sub.push_back( value );
                }

                cur[ _( "value" ) ] = sub.dump( );
            } break;
            case HASH( "std::vector<bool>" ):
            {
                const auto vec = item.get< std::vector< bool > >( );

                nlohmann::json sub;

                for ( const auto& value : vec ) {
                    sub.push_back( static_cast< int >( value ) );
                }

                cur[ _( "value" ) ] = sub.dump( );
            } break;
            case BINDS:
            {
                const auto vec = item.get<binds_t>( );

                auto sub = json( );

                for ( auto value : vec ) {
                    auto bind = json( );

                    bind.push_back( value.m_item_id );
                    bind.push_back( value.m_key_id );
                    bind.push_back( static_cast< int >( value.m_mode ) );
                    bind.push_back( static_cast< int >( value.m_type ) );
                    switch ( value.m_type ) {
                        case HASH( "bool" ):
                            bind.push_back( static_cast< int >( value.set< bool >( ) ) );
                            break;
                        case HASH( "int" ):
                            bind.push_back( value.set< int >( ) );
                            break;
                        case HASH( "float" ):
                            bind.push_back( value.set< float >( ) );
                            break;
                    }
                    bind.push_back( static_cast< int >( value.m_show_in_binds ) );
                    bind.push_back( value.m_name );
                    sub.push_back( bind );
                }

                cur[ _( "value" ) ] = sub.dump( );
            } break;
        }

        out.push_back( cur );
    }

    auto str = out.dump( );
    for ( auto& ch : str )
        ch ^= 0x1b;

    if ( std::ofstream file { path } )
        file << str;
}

void c_configs::load( const char* txt ) {
    const auto path = std::filesystem::path { FOLDER } /= txt;

    std::filesystem::create_directory( path.parent_path( ) );

    auto str = std::string( );

    if ( std::ifstream file { path } )
        file >> str;

    for ( auto& ch : str )
        ch ^= 0x1b;

    auto in = json::parse( str );

    for ( auto& item : in ) {
        const auto ident = item[ _( "id" ) ].get<uint32_t>( );
        if ( m_items.find( ident ) == m_items.end( ) )
            continue;

        auto& cur_item = m_items.at( ident );

        switch ( item[ _( "type" ) ].get<uint32_t>( ) ) {
            case HASH( "int" ): cur_item.get<int>( ) = item[ _( "value" ) ].get<int>( ); break;
            case HASH( "bool" ): cur_item.get<bool>( ) = item[ _( "value" ) ].get<bool>( ); break;
            case HASH( "float" ): cur_item.get<float>( ) = item[ _( "value" ) ].get<float>( ); break;
            case HASH( "color_t" ):
            {
                const auto vec = nlohmann::json::parse( item[ _( "value" ) ].get<std::string>( ) );

                cur_item.get<color_t>( ) = color_t( vec.at( 0u ).get<uint8_t>( ), vec.at( 1u ).get<uint8_t>( ), vec.at( 2u ).get<uint8_t>( ), vec.at( 3u ).get<uint8_t>( ) );
            } break;
            case HASH( "std::vector<bool>" ):
            {
                const auto vec = nlohmann::json::parse( item[ _( "value" ) ].get<std::string>( ) );

                auto& item_vec = cur_item.get<std::vector<bool>>( );

                for ( auto i = 0u; i < vec.size( ); i++ ) {
                    if ( i >= item_vec.size( ) )
                        continue;

                    item_vec.at( i ) = vec.at( i ).get<int>( );
                }
            } break;
            case BINDS:
            {
                const auto vec = json::parse( item[ _( "value" ) ].get<std::string>( ) );

                auto& item_vec = cur_item.get<binds_t>( );

                item_vec.clear( );
                item_vec.resize( vec.size( ) );

                for ( auto i = 0u; i < vec.size( ); i++ ) {
                    item_vec.at( i ).m_item_id = vec.at( i )[ 0 ].get< uint32_t >( );
                    item_vec.at( i ).m_key_id = vec.at( i )[ 1 ].get< uint32_t >( );
                    item_vec.at( i ).m_mode = vec.at( i )[ 2 ].get< int >( );
                    item_vec.at( i ).m_type = vec.at( i )[ 3 ].get< uint32_t >( );
                    switch ( item_vec.at( i ).m_type ) {
                        case HASH( "bool" ):
                            item_vec.at( i ).m_any = std::make_any< bool >( static_cast< bool >( vec.at( i )[ 4 ].get< int >( ) ) );
                            break;
                        case HASH( "int" ):
                            item_vec.at( i ).m_any = std::make_any< int >( vec.at( i )[ 4 ].get< int >( ) );
                            break;
                        case HASH( "float" ):
                            item_vec.at( i ).m_any = std::make_any< float >( vec.at( i )[ 4 ].get< float >( ) );
                            break;
                    }

                    item_vec.at( i ).m_show_in_binds = static_cast< bool >( vec.at( i )[ 5 ].get< int >( ) );
                    item_vec.at( i ).m_name = vec.at( i )[ 6 ].get< std::string >( );

                } break;
            }
        }

        m_key_binds.clear( );

        for ( auto& i : g_settings.binds.get( ) ) {
            if ( m_key_binds.find( i.m_item_id ) == m_key_binds.end( ) )
                m_key_binds[ i.m_item_id ] = { };

            m_key_binds[ i.m_item_id ].push_back( i );
        }
    }
}
