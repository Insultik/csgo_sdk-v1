#pragma once
#include "../../math/vectors.hpp"
#include "i_client.h"
#include "i_engine.h"

struct event_info_t {
	int				m_class_id{};
	float			m_delay{};
	char			pad1[4]{};
	client_class_t* m_client_class{};
	char			pad2[40]{};
	event_info_t* m_next{};
};

class c_clock_drift_mgr {
public:
	float m_clock_offsets[16]{};   //0x0000
	uint32_t m_cur_clock_offset{}; //0x0044
	uint32_t m_server_tick{};     //0x0048
	uint32_t m_client_tick{};     //0x004C
};

class i_client_state {
public:
	char			pad0[0x9C]{};
	i_net_channel* m_net_channel{};
	int				m_challenge_number{};
	char			pad1[4]{};
	double			m_connect_time{};
	int				m_retry_number{};
	char			pad2[0x54]{};
	int				m_signon_state{};
	char			pad3[4]{};
	double			m_next_cmd_time{};
	int				m_server_count{};
	int				m_cur_sequence{};
	char			pad4[8]{};
	struct {
		float		m_clock_offsets[0x10]{};
		int			m_cur_clock_offset{};
		int			m_server_tick{};
		int			m_client_tick{};
	} m_clock_drift_mgr{};
	int				m_delta_tick{};
	char			pad5[4]{};
	int				m_view_entity{};
	int				m_player_slot{};
	bool			m_paused{};
	char			pad6[3]{};
	char			m_level_name[0x104]{};
	char			m_level_name_short[0x28]{};
	char			pad7[0xD4]{};
	int				m_max_clients{};
	char			pad8[0x4994]{};
	int				m_old_tick_count{};
	float			m_tick_remainder{};
	float			m_frame_time{};
	int				m_last_outgoing_command{};
	int				m_choked_commands{};
	int				m_last_command_ack{};
	int				m_last_server_tick{};
	int				m_command_ack{};
	int				m_sound_sequence{};
	int				m_last_progress_percent{};
	bool			m_is_hltv{};
	char			pad9[0x4B]{};
	ang_t		m_view_angles{};
	char			pad10[0xCC]{};
	event_info_t* m_events{};
};