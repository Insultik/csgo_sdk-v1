#pragma once
#include "../../../utils/utils.h"
#include "../../math/vectors.h"
#include "../../other/key-values/key_values.h"

#define declare_pointer_handle(name) struct name##__ { int unused; }; typedef struct name##__ *name
#define maxstudioskins		32

// these are given to findmaterial to reference the texture groups that Show up on the
#define texture_group_lightmap						        "Lightmaps"
#define texture_group_world							          "World textures"
#define texture_group_model							          "Model textures"
#define texture_group_vgui							          "VGUI textures"
#define texture_group_particle						        "Particle textures"
#define texture_group_decal							          "Decal textures"
#define texture_group_skybox						          "SkyBox textures"
#define texture_group_client_effects				      "ClientEffect textures"
#define texture_group_other							          "Other textures"
#define texture_group_precached						        "Precached"
#define texture_group_cube_map						        "CubeMap textures"
#define texture_group_render_target					      "RenderTargets"
#define texture_group_unaccounted					        "Unaccounted textures"
#define texture_group_static_index_buffer			    "Static Indices"
#define texture_group_static_vertex_buffer_disp		"Displacement Verts"
#define texture_group_static_vertex_buffer_color	"Lighting Verts"
#define texture_group_static_vertex_buffer_world	"World Verts"
#define texture_group_static_vertex_buffer_models	"Model Verts"
#define texture_group_static_vertex_buffer_other	"Other Verts"
#define texture_group_dynamic_index_buffer			  "Dynamic Indices"
#define texture_group_dynamic_vertex_buffer			  "Dynamic Verts"
#define texture_group_depth_buffer					      "DepthBuffer"
#define texture_group_view_model					        "ViewModel"
#define texture_group_pixel_shaders					      "Pixel Shaders"
#define texture_group_vertex_shaders				      "Vertex Shaders"
#define texture_group_render_target_surface			  "RenderTarget Surfaces"
#define texture_group_morph_targets					      "Morph Targets"

//-----------------------------------------------------------------------------
// forward declarations
//-----------------------------------------------------------------------------

class matrix_t;
class i_material;
class i_material_var;
typedef int override_type_t;

enum e_compiled_vt_flags {
	textureflags_pointsample = 0x00000001,
	textureflags_trilinear = 0x00000002,
	textureflags_clamps = 0x00000004,
	textureflags_clampt = 0x00000008,
	textureflags_anisotropic = 0x00000010,
	textureflags_hint_dxt5 = 0x00000020,
	textureflags_pwl_corrected = 0x00000040,
	textureflags_normal = 0x00000080,
	textureflags_nomip = 0x00000100,
	textureflags_nolod = 0x00000200,
	textureflags_all_mips = 0x00000400,
	textureflags_procedural = 0x00000800,
	textureflags_onebitalpha = 0x00001000,
	textureflags_eightbitalpha = 0x00002000,
	textureflags_envmap = 0x00004000,
	textureflags_rendertarget = 0x00008000,
	textureflags_depthrendertarget = 0x00010000,
	textureflags_nodebugoverride = 0x00020000,
	textureflags_singlecopy = 0x00040000,
	textureflags_pre_srgb = 0x00080000,
	textureflags_unused_00100000 = 0x00100000,
	textureflags_unused_00200000 = 0x00200000,
	textureflags_unused_00400000 = 0x00400000,
	textureflags_nodepthbuffer = 0x00800000,
	textureflags_unused_01000000 = 0x01000000,
	textureflags_clampu = 0x02000000,
	textureflags_vertextexture = 0x04000000,
	textureflags_ssbump = 0x08000000,
	textureflags_unused_10000000 = 0x10000000,
	textureflags_border = 0x20000000,
	textureflags_unused_40000000 = 0x40000000,
	textureflags_unused_80000000 = 0x80000000
};

enum e_standardlightmap {
	material_system_lightmap_page_white = -1,
	material_system_lightmap_page_white_bump = -2,
	material_system_lightmap_page_user_defined = -3
};

struct materialsystem_sortinfo_t {
	i_material* material;
	int			lightmappageid;
};

enum e_materialthreadmode {
	material_single_threaded,
	material_queued_single_threaded,
	material_queued_threaded
};

enum e_materialcontexttype {
	material_hardware_context,
	material_queued_context,
	material_null_context
};

enum {
	material_adapter_name_length = 512
};

struct materialtextureinfo_t {
	int m_iexcludeinformation;
};

enum e_image_format {
	image_format_unknown = -1,
	image_format_rgba8888 = 0,
	image_format_abgr8888,
	image_format_rgb888,
	image_format_bgr888,
	image_format_rgb565,
	image_format_i8,
	image_format_ia88,
	image_format_p8,
	image_format_a8,
	image_format_rgb888_bluescreen,
	image_format_bgr888_bluescreen,
	image_format_argb8888,
	image_format_bgra8888,
	image_format_dxt1,
	image_format_dxt3,
	image_format_dxt5,
	image_format_bgrx8888,
	image_format_bgr565,
	image_format_bgrx5551,
	image_format_bgra4444,
	image_format_dxt1_onebitalpha,
	image_format_bgra5551,
	image_format_uv88,
	image_format_uvwq8888,
	image_format_rgba16161616f,
	image_format_rgba16161616,
	image_format_uvlx8888,
	image_format_r32f,
	image_format_rgb323232f,
	image_format_rgba32323232f,
	image_format_nv_dst16,
	image_format_nv_dst24,
	image_format_nv_intz,
	image_format_nv_rawz,
	image_format_ati_dst16,
	image_format_ati_dst24,
	image_format_nv_null,
	image_format_ati2n,
	image_format_ati1n,
	image_format_dxt1_runtime,
	image_format_dxt5_runtime,
	num_image_formats
};

struct applicationperformancecountersinfo_t {
	float m_msmain{};
	float m_msmst{};
	float m_msgpu{};
	float m_msflip{};
	float m_mstotal{};
};

struct applicationinstantcountersinfo_t {
	uint32_t m_ncpuactivitymask{};
	uint32_t m_ndeferredwordsallocated{};
};

struct materialadapterinfo_t {
	char m_pdrivername[material_adapter_name_length]{};
	unsigned int m_vendorid{};
	unsigned int m_deviceid{};
	unsigned int m_subsysid{};
	unsigned int m_revision{};
	int m_ndxsupportlevel{};			// this is the *preferred* dx support level
	int m_nmindxsupportlevel{};
	int m_nmaxdxsupportlevel{};
	unsigned int m_ndriverversionhigh{};
	unsigned int m_ndriverversionlow{};
};

struct materialvideomode_t {
	int m_width{};			// if width and height are 0 and you select
	int m_height{};			// windowed mode, it'll use the window size
	e_image_format m_format{};	// use imageformats (ignored for windowed mode)
	int m_refreshrate{};		// 0 == default (ignored for windowed mode)
};
enum hdrtype_t {
	hdr_type_none,
	hdr_type_integer,
	hdr_type_float,
};

enum restorechangeflags_t {
	material_restore_vertex_format_changed = 0x1,
	material_restore_release_managed_resources = 0x2,
};

enum rendertargetsizemode_t {
	rt_size_no_change = 0,
	rt_size_default = 1,
	rt_size_picmip = 2,
	rt_size_hdr = 3,
	rt_size_full_frame_buffer = 4,
	rt_size_offscreen = 5,
	rt_size_full_frame_buffer_rounded_up = 6
};

enum materialrendertargetdepth_t {
	material_rt_depth_shared = 0x0,
	material_rt_depth_separate = 0x1,
	material_rt_depth_none = 0x2,
	material_rt_depth_only = 0x3,
};

typedef unsigned short materialhandle_t;

enum material_var_flags_t {
	material_var_debug = (1 << 0),
	material_var_no_debug_override = (1 << 1),
	material_var_no_draw = (1 << 2),
	material_var_use_in_fillrate_mode = (1 << 3),
	material_var_vertexcolor = (1 << 4),
	material_var_vertexalpha = (1 << 5),
	material_var_selfillum = (1 << 6),
	material_var_additive = (1 << 7),
	material_var_alphatest = (1 << 8),
	material_var_znearer = (1 << 10),
	material_var_model = (1 << 11),
	material_var_flat = (1 << 12),
	material_var_nocull = (1 << 13),
	material_var_nofog = (1 << 14),
	material_var_ignorez = (1 << 15),
	material_var_decal = (1 << 16),
	material_var_envmapsphere = (1 << 17), // obsolete
	material_var_unused = (1 << 18), // unused
	material_var_envmapcameraspace = (1 << 19), // obsolete
	material_var_basealphaenvmapmask = (1 << 20),
	material_var_translucent = (1 << 21),
	material_var_normalmapalphaenvmapmask = (1 << 22),
	material_var_needs_software_skinning = (1 << 23), // obsolete
	material_var_opaquetexture = (1 << 24),
	material_var_envmapmode = (1 << 25), // obsolete
	material_var_suppress_decals = (1 << 26),
	material_var_halflambert = (1 << 27),
	material_var_wireframe = (1 << 28),
	material_var_allowalphatocoverage = (1 << 29),
	material_var_alpha_modified_by_proxy = (1 << 30),
	material_var_vertexfog = (1 << 31),
};

enum preview_image_retval_t {
	material_preview_image_bad = 0,
	material_preview_image_ok,
	material_no_preview_image,
};

class i_material_var {

	void set_vector_internal( const float x, const float y ) {
		using o_fn = void( __thiscall* )(void*, float, float);
		return utils::call_vfunc<o_fn>( this, 10 )(this, x, y);
	}

public:
	void set_float( const float val ) {
		using o_fn = void( __thiscall* )(void*, float);
		return utils::call_vfunc<o_fn>( this, 4 )(this, val);
	}

	void set_int( const int val ) {
		using o_fn = void( __thiscall* )(void*, int);
		return utils::call_vfunc<o_fn>( this, 5 )(this, val);
	}

	void set_string( char const* val ) {
		using o_fn = void( __thiscall* )(void*, char const*);
		return utils::call_vfunc<o_fn>( this, 6 )(this, val);
	}

	void set_matrix( matrix_t& matrix ) {
		using o_fn = void( __thiscall* )(void*, matrix_t&);
		return utils::call_vfunc<o_fn>( this, 6 )(this, matrix);
	}

	void set_vector_component( const float val, const int comp ) {
		using o_fn = void( __thiscall* )(void*, float, int);
		return utils::call_vfunc<o_fn>( this, 26 )(this, val, comp);
	}

	void set_vector( const vec2_t vector ) {
		set_vector_internal( vector.x, vector.y );
	}

	void set_vector_internal( const float x, const float y, const float z ) {
		using o_fn = void( __thiscall* )(void*, float, float, float);
		return utils::call_vfunc<o_fn>( this, 11 )(this, x, y, z);
	}

	void set_vector( const vec3_t vector ) {
		set_vector_internal( vector.x, vector.y, vector.z );
	}
};

typedef int vertex_format_t;
typedef int material_property_types_t;

class i_material {
public:
	virtual const char* get_name( ) const = 0;
	virtual const char* get_texture_group_name( ) const = 0;
	virtual preview_image_retval_t get_preview_image_properties( int* width, int* height, e_image_format* imageFormat, bool* isTranslucent ) const = 0;
	virtual preview_image_retval_t get_preview_image( unsigned char* data, int width, int height, e_image_format imageFormat ) const = 0;
	virtual int get_mapping_width( ) = 0;
	virtual int get_mapping_height( ) = 0;
	virtual int get_num_animation_frames( ) = 0;
	virtual bool in_material_page( void ) = 0;
	virtual void get_material_offset( float* pOffset ) = 0;
	virtual void get_material_scale( float* pScale ) = 0;
	virtual i_material* get_material_page( void ) = 0;
	virtual i_material_var* find_var( const char* varName, bool* found, bool complain = true ) = 0;
	virtual void increment_reference_count( void ) = 0;
	virtual void decrement_reference_count( void ) = 0;
	virtual int get_enumeration_id( void ) const = 0;
	virtual void get_low_res_color_sample( float s, float t, float* color ) const = 0;
	virtual void recompute_state_snapshots( ) = 0;
	virtual bool is_translucent( ) = 0;
	virtual bool is_alpha_tested( ) = 0;
	virtual bool is_vertex_lit( ) = 0;
	virtual vertex_format_t get_vertex_format( ) const = 0;
	virtual bool has_proxy( void ) const = 0;
	virtual bool uses_env_cubemap( void ) = 0;
	virtual bool needs_tangent_space( void ) = 0;
	virtual bool needs_power_of_two_frame_buffer_texture( bool bCheckSpecificToThisFrame = true ) = 0;
	virtual bool needs_full_frame_buffer_texture( bool bCheckSpecificToThisFrame = true ) = 0;
	virtual bool needs_software_skinning( void ) = 0;
	virtual void alpha_modulate( float alpha ) = 0;
	virtual void color_modulate( float r, float g, float b ) = 0;
	virtual void set_material_var_flag( material_var_flags_t flag, bool on ) = 0;
	virtual bool get_material_var_flag( material_var_flags_t flag ) const = 0;
	virtual void get_reflectivity( vec3_t& reflect ) = 0;
	virtual bool get_property_flag( material_property_types_t  type ) = 0;
	virtual bool is_two_sided( ) = 0;
	virtual void set_shader( const char* pShaderName ) = 0;
	virtual int get_num_passes( void ) = 0;
	virtual int get_texture_memory_bytes( void ) = 0;
	virtual void refresh( ) = 0;
	virtual bool needs_lightmap_blend_alpha( void ) = 0;
	virtual bool needs_software_lighting( void ) = 0;
	virtual int shader_param_count( ) const = 0;
	virtual i_material_var** get_shader_params( void ) = 0;
	virtual bool is_error_material( ) const = 0;
	virtual void unused( ) = 0;
	virtual float get_alpha_modulation( ) = 0;
	virtual void get_color_modulation( float* r, float* g, float* b ) = 0;
	virtual bool is_translucent_under_modulation( float fAlphaModulation = 1.0f ) const = 0;
	virtual i_material_var* find_var_fast( char const* pVarName, unsigned int* pToken ) = 0;
	virtual void set_shader_and_params( c_key_values* pKeyValues ) = 0;
	virtual const char* get_shader_name( ) const = 0;
	virtual void delete_if_unreferenced( ) = 0;
	virtual bool is_sprite_card( ) = 0;
	virtual void call_bind_proxy( void* proxyData ) = 0;
	virtual void refresh_preserving_material_vars( ) = 0;
	virtual bool was_reloaded_from_whitelist( ) = 0;
	virtual bool set_temp_excluded( bool bSet, int nExcludedDimensionLimit ) = 0;
	virtual int get_reference_count( ) const = 0;
};

enum light_type_t {
	material_light_disable = 0,
	material_light_point,
	material_light_directional,
	material_light_spot,
};

class light_desc_t {
public:
	light_type_t m_type;                 //0x0000
	vec3_t m_color{};                     //0x0004
	vec3_t m_position{};                  //0x0010
	vec3_t m_direction{};                 //0x001C
	float m_range{};                      //0x0028
	float m_falloff{};                    //0x002C
	float m_attenuation0{};               //0x0030
	float m_attenuation1{};               //0x0034
	float m_attenuation2{};               //0x0038
	float m_theta{};                      //0x003C
	float m_phi{};                        //0x0040
	float m_theta_dot{};                   //0x0044
	float m_phi_dot{};                     //0x0048
	float m_one_over_theta_dot_minus_phi_dot{}; //0x004C
	__int32 m_flags{};                    //0x0050
	float m_range_squared{};               //0x0054
};

class i_studio_render {
public:
	void set_ambient_light_colors( vec3_t* pAmbientOnlyColors ) {
		utils::call_vfunc<void( __thiscall* )(void*, vec3_t*)>( this, 20 )(this, pAmbientOnlyColors);
	}

	void set_local_lights( int nLights, light_desc_t* pLights ) {
		utils::call_vfunc<void( __thiscall* )(void*, int, light_desc_t*)>( this, 22 )(this, nLights, pLights);
	}

	void set_color_modulation( float r, float g, float b ) {
		utils::call_vfunc<void( __thiscall* )(void*, float, float, float)>( this, 27 )(this, r, g, b);
	}

	void set_alpha_modulation( float flAlpha ) {
		utils::call_vfunc<void( __thiscall* )(void*, float)>( this, 28 )(this, flAlpha);
	}

	void forced_material_override( i_material* pMaterial, override_type_t nOverrideType = 0, int nOverrides = 0 ) {
		utils::call_vfunc<void( __thiscall* )(void*, i_material*, override_type_t, int)>( this, 33 )(this, pMaterial, nOverrideType, nOverrides);
	}
};

class i_material_system {
public:
	i_material* create_material( const char* name, void* key_values ) {
		return utils::call_vfunc<i_material* (__thiscall*)(void*, const char*, void*)>( this, 83 )(this, name, key_values);
	}

	i_material* find_material( const char* name, const char* group = nullptr ) {
		return utils::call_vfunc<i_material* (__thiscall*)(void*, const char*, const char*)>( this, 84 )(this, name, group);
	}

	materialhandle_t first_material( ) {
		return utils::call_vfunc<materialhandle_t( __thiscall* )(i_material_system*)>( this, 86 )(this);
	}

	materialhandle_t next_material( materialhandle_t handle ) {
		return utils::call_vfunc<materialhandle_t( __thiscall* )(i_material_system*, materialhandle_t)>( this, 87 )(this, handle);
	}

	materialhandle_t invalid_material_handle( ) {
		return utils::call_vfunc<materialhandle_t( __thiscall* )(i_material_system*)>( this, 88 )(this);
	}

	i_material* get_material( materialhandle_t handle ) {
		return utils::call_vfunc<i_material* (__thiscall*)(i_material_system*, materialhandle_t)>( this, 89 )(this, handle);
	}
};
