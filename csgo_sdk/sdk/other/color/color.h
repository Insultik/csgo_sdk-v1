#pragma once

#include <iostream>
#include <string>

class color_t {
public:
	color_t( );
	color_t( int _r, int _g, int _b );
	color_t( int _r, int _g, int _b, int _a );
	color_t( float _r, float _g, float _b ) : color_t( _r, _g, _b, 1.0f ) {
	}
	color_t( float _r, float _g, float _b, float _a )
		: color_t(
			static_cast<int>(_r * 255.0f),
			static_cast<int>(_g * 255.0f),
			static_cast<int>(_b * 255.0f),
			static_cast<int>(_a * 255.0f) ) {
	}
	explicit color_t( float* rgb ) : color_t( rgb[0], rgb[1], rgb[2], rgb[3] ) {
	}
	explicit color_t( unsigned long argb ) {
		color_value[2] = static_cast<unsigned char>((argb & 0x000000FF) >> (0 * 8));
		color_value[1] = static_cast<unsigned char>((argb & 0x0000FF00) >> (1 * 8));
		color_value[0] = static_cast<unsigned char>((argb & 0x00FF0000) >> (2 * 8));
		color_value[3] = static_cast<unsigned char>((argb & 0xFF000000) >> (3 * 8));
	}

	void    set_raw_color( int color32 );
	[[nodiscard]] int     get_raw_color( ) const;
	void set_alpha( int alpha );
	__forceinline color_t override_alpha( int alpha, bool use_first = false ) {
		return color_t( static_cast< int >( color_value[0] * 255.0f ),
						static_cast< int >( color_value[1] * 255.0f ),
						static_cast< int >( color_value[2] * 255.0f ),
						static_cast< int >( use_first ? ( color_value[ 3 ] * alpha ) : alpha) )
	}
	void    set_color( int _r, int _g, int _b, int _a = 0 );
	void    set_color( float _r, float _g, float _b, float _a = 0 );
	void    get_color( int& r, int& g, int& b, int& a ) const;

	[[nodiscard]] std::string get_normalnij_hex_color( ) const;

	[[nodiscard]] int r( ) const {
		return color_value[0];
	}
	[[nodiscard]] int g( ) const {
		return color_value[1];
	}
	[[nodiscard]] int b( ) const {
		return color_value[2];
	}
	[[nodiscard]] int a( ) const {
		return color_value[3];
	}

	unsigned char& operator[]( const int index ) {
		return color_value[index];
	}
	const unsigned char& operator[]( const int index ) const {
		return color_value[index];
	}

	bool operator==( const color_t& rhs ) const;
	bool operator!=( const color_t& rhs ) const;
	color_t& operator=( const color_t& rhs );

	static color_t from_hsb( const float hue, const float saturation, const float brightness ) {
		const float h = hue == 1.0f ? 0 : hue * 6.0f;
		const float f = h - static_cast<int>(h);
		const float p = brightness * (1.0f - saturation);
		const float q = brightness * (1.0f - saturation * f);
		const float t = brightness * (1.0f - (saturation * (1.0f - f)));

		if ( h < 1 ) {
			return {
				static_cast<unsigned char>(brightness * 255),
				static_cast<unsigned char>(t * 255),
				static_cast<unsigned char>(p * 255)
			};
		}
		if ( h < 2 ) {
			return {
				static_cast<unsigned char>(q * 255),
				static_cast<unsigned char>(brightness * 255),
				static_cast<unsigned char>(p * 255)
			};
		}
		if ( h < 3 ) {
			return {
				static_cast<unsigned char>(p * 255),
				static_cast<unsigned char>(brightness * 255),
				static_cast<unsigned char>(t * 255)
			};
		}
		if ( h < 4 ) {
			return {
				static_cast<unsigned char>(p * 255),
				static_cast<unsigned char>(q * 255),
				static_cast<unsigned char>(brightness * 255)
			};
		}
		if ( h < 5 ) {
			return {
				static_cast<unsigned char>(t * 255),
				static_cast<unsigned char>(p * 255),
				static_cast<unsigned char>(brightness * 255)
			};
		}
		return {
			static_cast<unsigned char>(brightness * 255),
			static_cast<unsigned char>(p * 255),
			static_cast<unsigned char>(q * 255)
		};
	}

	static color_t black;
	static color_t white;
	static color_t red;
	static color_t green;
	static color_t blue;

private:
	uint8_t color_value[4]{};
};