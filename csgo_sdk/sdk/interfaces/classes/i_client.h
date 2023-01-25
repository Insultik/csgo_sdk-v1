#pragma once
#include <cstdint>
#include "../../math/vectors.h"
#include "../../other/recv.h"

class i_global_vars_base;

using create_client_class = void* (__cdecl*)(int, int);
using create_event = void* (__cdecl*)();

struct client_class_t {

	create_client_class m_create{};
	create_event m_create_event{};
	char* m_network_name{};
	recv_table_t* m_recv_table{};
	client_class_t* m_next{};
	int m_class_id{};
};

class i_base_client_dll {
public:
	virtual int              connect( uint32_t app_system_factory, i_global_vars_base* globals ) = 0;
	virtual int              disconnect( ) = 0;
	virtual int              init( uint32_t app_system_factory, i_global_vars_base* globals ) = 0;
	virtual void             post_init( ) = 0;
	virtual void             shutdown( ) = 0;
	virtual void             level_init_pre_entity( char const* pMapName ) = 0;
	virtual void             level_init_post_entity( ) = 0;
	virtual void             level_shutdown( ) = 0;
	virtual client_class_t* get_all_classes( ) = 0;
};

struct view_setup_t {
	int			m_x;
	int			m_x_unscaled;
	int			m_y;
	int			m_y_unscaled;
	int			m_width;
	int			m_old_width;
	int			m_height;
	int			m_old_height;
	char		pad0[ 144 ];
	float		m_fov;
	float		m_view_model_fov;
	vec3_t		m_origin;
	ang_t		m_angles;
	char		pad1[ 124 ];
};