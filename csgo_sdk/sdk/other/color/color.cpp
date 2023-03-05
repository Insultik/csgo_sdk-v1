#include "color.hpp"

color_t::color_t( ) {
	*reinterpret_cast<int*>(this) = 0;
}
color_t::color_t( const int _r, const int _g, const int _b ) {
	set_color( _r, _g, _b, 255 );
}
color_t::color_t( const int _r, const int _g, const int _b, const int _a ) {
	set_color( _r, _g, _b, _a );
}
void color_t::set_raw_color( const int color32 ) {
	*reinterpret_cast<int*>(this) = color32;
}
int color_t::get_raw_color( ) const {
	return *(int*) this;
}

void color_t::set_alpha( const int alpha ) {
	color_value.at( 3 ) = alpha;
}

void color_t::set_color( const int _r, const int _g, const int _b, const int _a ) {
	color_value.at( 0 ) = static_cast<unsigned char>(_r);
	color_value.at( 1 ) = static_cast<unsigned char>(_g);
	color_value.at( 2 ) = static_cast<unsigned char>(_b);
	color_value.at( 3 ) = static_cast<unsigned char>(_a);
}
void color_t::set_color( float _r, float _g, float _b, float _a ) {
	color_value.at( 0 ) = static_cast<unsigned char>(_r * 255.0f);
	color_value.at( 1 ) = static_cast<unsigned char>(_g * 255.0f);
	color_value.at( 2 ) = static_cast<unsigned char>(_b * 255.0f);
	color_value.at( 3 ) = static_cast<unsigned char>(_a * 255.0f);
}
void color_t::get_color( int& r, int& g, int& b, int& a ) const {
	r = color_value.at( 0 );
	g = color_value.at( 1 );
	b = color_value.at( 2 );
	a = color_value.at( 3 );
}
bool color_t::operator== ( const color_t& rhs ) const {
	return *(int*) this == *(int*) &rhs;
}
bool color_t::operator!= ( const color_t& rhs ) const {
	return !operator==( rhs );
}
color_t& color_t::operator=( const color_t& rhs ) {
	set_raw_color( rhs.get_raw_color( ) );
	return *this;
}
