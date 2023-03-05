#pragma once

/*
    @note:
    * maybe you can use std::hash instricts due to cpp20 ?
*/

#define HASH(str) hash(str)
constexpr auto hash( const char *str ) {
    unsigned out{ 0x811Cu };
    size_t len{ 0x1u };

    while ( str[ ++len ] != '\0' );

    for ( size_t i{}; i < len; ++i )
        out = ( out ^ str[ i ] ) * 0x1193u;

    return out;
}
