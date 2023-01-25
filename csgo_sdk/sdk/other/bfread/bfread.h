#pragma once
#include <cstdint>
#include <algorithm>
#include <algorithm>

class c_bf_read {
public:
	const char* m_debug_name{};
	bool m_overflow{};
	int m_data_bits{};
	uint32_t m_data_bytes{};
	uint32_t m_in_buf_word{};
	int m_bits_avail{};
	const uint32_t* m_data_in{};
	const uint32_t* m_buffer_end{};
	const uint32_t* m_data{};

	c_bf_read( ) = default;

	c_bf_read( const void* data, const int bytes, const int bits = -1 ) {
		start_reading( data, bytes, 0, bits );
	}

	__forceinline void start_reading( const void* data, const int bytes, const int start_bit, const int bits ) {
		m_data = reinterpret_cast<const uint32_t*>(data);
		m_data_in = m_data;
		m_data_bytes = bytes;

		m_data_bits = bits == -1 ? bytes << 3 : bits;

		m_overflow = false;
		m_buffer_end = reinterpret_cast<const uint32_t*>(reinterpret_cast<const uint8_t*>(m_data) + bytes);

		if ( m_data ) {
			seek( start_bit );
		}
	}

	__forceinline bool seek( int pos ) {
		auto succ = true;
		if ( pos < 0 || pos > m_data_bits ) {
			m_overflow = true;
			succ = false;
			pos = m_data_bits;
		}

		const int head = m_data_bytes & 3;

		int byeteofs = pos / 8;
		if ( m_data_bytes < 4 || head && byeteofs < head ) {
			auto partial = reinterpret_cast<const uint8_t*>(m_data);

			if ( m_data ) {
				m_in_buf_word = *partial++;

				if ( head > 1 ) {
					m_in_buf_word |= *partial++ << 8;
				}

				if ( head > 2 ) {
					m_in_buf_word |= *partial++ << 16;
				}
			}

			m_data_in = reinterpret_cast<const uint32_t*>(partial);
			m_in_buf_word >>= pos & 31;
			m_bits_avail = (head << 3) - (pos & 31);
		}
		else {
			const auto adj_pos = pos - (head << 3);

			m_data_in = reinterpret_cast<const uint32_t*>(reinterpret_cast<const uint8_t*>(m_data) + (adj_pos / 32 << 2)
														   + head);

			if ( m_data ) {
				m_bits_avail = 32;

				grab_next_dword( );
			}
			else {
				m_in_buf_word = 0;
				m_bits_avail = 1;
			}

			m_in_buf_word >>= adj_pos & 31;
			m_bits_avail = std::min<int>( m_bits_avail, 32 - (adj_pos & 31) );
		}

		return succ;
	}

	__forceinline void grab_next_dword( const bool overflow_immediately = false ) {
		if ( m_data_in == m_buffer_end ) {
			m_bits_avail = 1;
			m_in_buf_word = 0;
			m_data_in++;

			if ( overflow_immediately ) {
				m_overflow = true;
			}
		}
		else if ( m_data_in > m_buffer_end ) {
			m_overflow = true;
			m_in_buf_word = 0;
		}
		else {
			m_in_buf_word = *m_data_in++;
		}
	}
};

class c_bf_write {
public:
	c_bf_write( ) {
		m_data = 0;
		m_data_bytes = 0;
		m_data_bits = -1;
		m_cur_bit = 0;
		m_overflow = false;
		m_assert_on_overflow = true;
		m_debug_name = 0;
	}

	c_bf_write( void* data, int bytes, int bits = -1 ) {
		m_assert_on_overflow = true;
		m_debug_name = 0;

		start_writing( data, bytes, 0, bits );
	}

	c_bf_write( const char* debug_name, void* data, int bytes, int bits = -1 ) {
		m_assert_on_overflow = true;
		m_debug_name = debug_name;

		start_writing( data, bytes, 0, bits );
	}

	__forceinline void start_writing( void* data, int bytes, int start_bit = 0, int bits = -1 ) {
		bytes &= ~3;

		m_data = reinterpret_cast< uint8_t* >( data );
		m_data_bytes = bytes;
		m_data_bits = bits == -1 ? bytes << 3 : bits;

		m_cur_bit = start_bit;
		m_overflow = false;
	}

	__forceinline uint32_t get_bytes_written_count( ) const { return ( m_cur_bit + 7 ) >> 3; }

	__forceinline void write_user_cmd( void* to, void* from ) {
		static const auto write_user_cmd_fn = utils::find_sig( "client.dll", "55 8B EC 83 E4 F8 51 53 56 8B D9 8B 0D" );

		__asm {
			mov     ecx, this
			mov     edx, to
			push	from
			call    write_user_cmd_fn
			add     esp, 4
		}
	}

	uint8_t* m_data;
	int				m_data_bytes;
	int				m_data_bits;
	int				m_cur_bit;
	bool			m_overflow;
	bool			m_assert_on_overflow;
	const char* m_debug_name;
};
