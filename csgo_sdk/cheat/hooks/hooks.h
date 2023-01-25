#pragma once
#include "../../dependencies/minhook/minhook.h"
#include "../../main_includes.h"

namespace hooks {
    bool instance( );

    __forceinline void reset( ) {
        MH_DisableHook( MH_ALL_HOOKS );
        MH_Uninitialize( );
    }

    namespace device {
        namespace reset {
            long __stdcall fn( IDirect3DDevice9* device_, D3DPRESENT_PARAMETERS* params );
            inline decltype( &fn ) get_original = nullptr;
        }

        namespace present {
            long __stdcall fn( IDirect3DDevice9* devic_, RECT* src, RECT* dest, HWND window_override, RGNDATA* dirty_region );
            inline decltype( &fn ) get_original = nullptr;
        }

        namespace wnd_proc {
            void instance( );
            long __stdcall fn( HWND window, UINT msg, WPARAM wparm, LPARAM lparm );
            inline WNDPROC wnd_proc = nullptr;
        }
    }

    namespace panel {
        namespace paint_traverse {
            void __fastcall fn( i_panel* vpanel, void* edx, vgui::vpanel panel, bool force_repaint, bool allow_force );
            inline decltype( &fn ) get_original = nullptr;
        }
    }

    namespace net_channel {
        namespace process_packet {
            void __cdecl fn( void* packet, bool header );
            using og_fn = void( __cdecl* )( void*, bool );
            inline og_fn get_original = nullptr;
        }
    }

    namespace clientdll {
        namespace create_move {
            void __stdcall call( int sequence_number, float sample_frametime, bool active, bool& send_packet );
            void __fastcall fn( void* ecx, void* edx, int sequence_number, float sample_frametime, bool active );
            using og_fn = void( __stdcall* )( int, float, bool );
            inline og_fn get_original = nullptr;
        }

        namespace frame_stage_notify {
            void __fastcall fn( void* ecx, void* edx, int stage );
            inline decltype( &fn ) get_original = nullptr;
        }
    }

    namespace clientmode {
        namespace override_view {
            void __fastcall fn( void* ecx, void* edx, view_setup_t* view );
            inline decltype( &fn ) get_original = nullptr;
        }
    }

    namespace prediction {
        namespace in_prediction {
            bool __fastcall fn( i_prediction* ecx, void* edx );
            inline decltype( &fn ) get_original = nullptr;
        }
    }

    namespace base_player {
        namespace build_transformations {
            void __fastcall fn( void* ecx, void* edx, int a2, int a3, int a4, int a5, int a6, int a7 );
            inline decltype( &fn ) get_original = nullptr;
        }

        namespace calc_view {
            void __fastcall fn( void* ecx, void* edx, vec3_t& eye_origin, vec3_t& eye_angles, float& m_near, float& m_far, float& fov );
            inline decltype( &fn ) get_original = nullptr;
        }

        namespace do_extra_bones_processing {
            void __fastcall fn( void* ecx, void* edx, int a2, int a3, int a4, int a5, int a6, int a7 );
            inline decltype( &fn ) get_original = nullptr;
        }

        namespace get_eye_ang {
            ang_t* __fastcall fn( void* ecx, void* edx );
            inline decltype( &fn ) get_original = nullptr;
        }

        namespace standard_blending_rules {
            void __fastcall fn( void* ecx, void* edx, c_studio_hdr* hdr, vec3_t* pos, void* q, float curtime, int mask );
            inline decltype( &fn ) get_original = nullptr;
        }

        namespace update_clientside_animations {
            void __fastcall fn( void* ecx, void* edx );
            inline decltype( &fn ) get_original = nullptr;
        }
    }

    namespace animstate {
        namespace modify_eye_position {
            void __fastcall fn( void* ecx, void* edx, vec3_t& input_eye_position );
            inline decltype( &fn ) get_original = nullptr;
        }
    }
}

