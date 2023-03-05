#pragma once
#include "../../../utils/utils.hpp"
#include "../../math/vectors.hpp"
#include "../../other/bfread/bfread.hpp"

struct player_info_t {
	int64_t			pad0;

	union {
		int64_t		m_xuid;
		struct {
			int		m_xuid_low;
			int		m_xuid_high;
		};
	};

	char			m_name[ 128 ];
	int				m_user_id;
	char			m_guid[ 33 ];
	uint32_t		m_friends_id;
	char			m_friends_name[ 128 ];
	bool			m_fake_player;
	bool			m_is_hltv;
	uint32_t		m_custom_files[ 4 ];
	unsigned char	m_files_downloaded;
};

class i_net_channel_info {
public:
	virtual const char* get_name( ) const = 0;
	virtual const char* get_address( ) const = 0;
	virtual float		get_time( ) const = 0;
	virtual float		get_time_connected( ) const = 0;
	virtual int			get_buffer_size( ) const = 0;
	virtual int			get_data_rate( ) const = 0;

	virtual bool		is_loopback( ) const = 0;
	virtual bool		is_timing_out( ) const = 0;
	virtual bool		is_playback( ) const = 0;

	virtual float		get_latency( int flow ) const = 0;
	virtual float		get_avg_latency( int flow ) const = 0;
	virtual float		get_avg_loss( int flow ) const = 0;
	virtual float		get_avg_choke( int flow ) const = 0;
	virtual float		get_avg_data( int flow ) const = 0;
	virtual float		get_avg_packets( int flow ) const = 0;
	virtual int			get_total_data( int flow ) const = 0;
	virtual int			get_sequence_number( int flow ) const = 0;
	virtual bool		is_valid_packet( int flow, int frame_number ) const = 0;
	virtual float		get_packet_time( int flow, int frame_number ) const = 0;
	virtual int			get_packet_bytes( int flow, int frame_number, int group ) const = 0;
	virtual bool		get_stream_progress( int flow, int* received, int* total ) const = 0;
	virtual float		get_time_since_last_received( ) const = 0;
	virtual float		get_command_interpolation_amount( int flow, int frame_number ) const = 0;
	virtual void		get_packet_response_latency( int flow, int frame_number, int* latency, int* choke ) const = 0;
	virtual void		get_remote_framerate( float* frame_time, float* frame_time_std_deviation ) const = 0;

	virtual float		get_timeout_seconds( ) const = 0;
};

class i_net_channel {
public:
	class i_net_msg {
	public:
		virtual					~i_net_msg( ) = default;
		virtual void			set_net_channel( i_net_channel* net_channel ) = 0;
		virtual void			set_reliable( bool state ) = 0;
		virtual bool			process( ) = 0;
		virtual bool			read_from_buffer( c_bf_read& buffer ) = 0;
		virtual bool			write_to_buffer( c_bf_write& buffer ) = 0;
		virtual bool			is_reliable( ) const = 0;
		virtual int				get_type( ) const = 0;
		virtual int				get_group( ) const = 0;
		virtual const char* get_name( ) const = 0;
		virtual i_net_channel* get_net_channel( ) const = 0;
		virtual const char* to_string( ) const = 0;
		virtual uint32_t			get_size( ) const = 0;
	};

	template <typename T>
	class i_net_msg_pb : public i_net_msg, public T {
	public:

	};

	class i_move_msg {
	public:
		char			pad0[ 8 ];
		int				m_backup_commands;
		int				m_new_commands;
		std::string* m_data;
		c_bf_read			m_data_in;
		c_bf_write		m_data_out;
	};
	using i_move_msg_t = i_net_msg_pb<i_move_msg>;

	VFUNC( set_time_out( float time ), 4, void( __thiscall* )( void*, float ), time );
	VFUNC( get_latency( int flow ), 9, float( __thiscall* )( void*, int ), flow );
	VFUNC( send_net_msg( i_net_msg* msg, bool reliable = false, bool voice = false ), 40, bool( __thiscall* )( void*, i_net_msg*, bool, bool ), msg, reliable, voice );
	VFUNC( send_datagram( ), 46, int( __thiscall* )( void*, void* ), nullptr );
	VFUNC( transmit( bool reliable ), 49, bool( __thiscall* )( void*, bool ), reliable );
	VFUNC( request_file( const char* file_name ), 62, int( __thiscall* )( void*, const char* ), file_name );

	__forceinline static uintptr_t* get_vtable( ) {
		static const auto vtable = reinterpret_cast< uintptr_t* > ( utils::find_sig( "engine.dll", "C7 06 ? ? ? ? 8D BE ? ? ? ?" ) + ( 0x2 ) );

		return vtable;
	}

	char pad0[ 20 ];
	bool m_processing_messages;
	bool m_should_delete;
	char pad1[ 2 ];
	int	 m_out_sequence_number;
	int	 m_in_sequence_number;
	int  m_out_sequence_number_ack;
	int  m_out_reliable_state;
	int  m_in_reliable_state;
	int  m_choked_packets;
	char pad2[ 1044 ];
};

class i_engine_client {
public:
	VFUNC( get_screen_size( int& width, int& height ), 5, void( __thiscall* )( void*, int& width, int& height ), width, height );
	VFUNC( get_player_info( int index, player_info_t* info ), 8, void( __thiscall* )( void*, int, player_info_t* ), index, info );
	VFUNC( get_player_for_user_id( int id ), 9, int( __thiscall* )( void*, int ), id );
	VFUNC( is_console_opened( ), 11, bool( __thiscall* )( void* ) );
	VFUNC( get_local_player( ), 12, int( __thiscall* )( void* ) );
	VFUNC( get_last_time_stamp( ), 14, float( __thiscall* )( void* ) );
	VFUNC( get_view_angles( ang_t& view_angles ), 18, void( __thiscall* )( void*, ang_t& ), view_angles );
	VFUNC( set_view_angles( ang_t& view_angles ), 19, void( __thiscall* )( void*, ang_t& ), view_angles );
	VFUNC( get_max_clients( ), 20, bool( __thiscall* )( void* ) );
	VFUNC( is_in_game( ), 26, bool( __thiscall* )( void* ) );
	VFUNC( is_connected( ), 27, bool( __thiscall* )( void* ) );
	VFUNC( is_drawing_loading_image( ), 28, bool( __thiscall* )( void* ) );
	VFUNC( get_bsp_tree_query( ), 43, uintptr_t* ( __thiscall* )( void* ) );
	VFUNC( get_level_name( ), 52, const char* ( __thiscall* )( void* ) );
	VFUNC( get_level_name_short( ), 53, const char* ( __thiscall* )( void* ) );
	VFUNC( fire_events( ), 59, void( __thiscall* )( void* ) );
	VFUNC( get_net_channel_info( ), 78, i_net_channel_info* ( __thiscall* )( void* ) );
	VFUNC( get_net_channel( ), 78, i_net_channel* ( __thiscall* )( void* ) );
	VFUNC( is_playing_demo( ), 82, bool( __thiscall* )( void* ) );
	VFUNC( is_recording_demo( ), 83, bool( __thiscall* )( void* ) );
	VFUNC( is_playing_time_demo( ), 84, bool( __thiscall* )( void* ) );
	VFUNC( is_paused( ), 90, bool( __thiscall* )( void* ) );
	VFUNC( is_taking_screenshot( ), 92, bool( __thiscall* )( void* ) );
	VFUNC( is_hltv( ), 93, bool( __thiscall* )( void* ) );
	VFUNC( get_engine_build_number( ), 104, uintptr_t* ( __thiscall* )( void* ) );
	VFUNC( client_cmd( const char* cmd ), 108, void( __thiscall* )( void*, const char* ), cmd );
	VFUNC( client_cmd_unrestricted( const char* cmd, bool unk = false ), 114, void( __thiscall* )( void*, const char*, bool ), cmd, unk );
	VFUNC( is_voice_recording( ), 224, bool( __thiscall* )( void* ) );
};