#pragma once
#include "../../main.hpp"
#include "classes/includes.h"
#include <d3d9.h>

using create_interface_fn = void* ( * )( const char*, int* );
namespace interfaces
{
	bool instance( );

	void* get_interface( const HMODULE module, const char* interface_name );

	inline i_global_vars_base* global_vars;
	inline i_base_client_dll* client;
	inline i_client_state* client_state;
	inline i_model_info* model_info;
	inline i_model_render* model_render;
	inline i_prediction* prediction;
	inline i_studio_render* studio_render;
	inline i_material_system* material_system;
	inline i_client_entity_list* entity_list;
	inline i_weapon_system* weapon_system;
	inline i_engine_client* engine;
	inline i_input* input;
	inline i_panel* panel;
	inline i_render_view* render_view;
	inline i_game_movement* game_movement;
	inline i_mem_alloc* mem_alloc;
	inline i_game_event_manager* event_manager;
	inline i_debug_overlay* debug_overlay;
	inline i_surface* surface;
	inline IDirect3DDevice9* device;
}