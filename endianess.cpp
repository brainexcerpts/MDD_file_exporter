#include "asset/parsers/endianess.hpp"

#include <stdint.h>
#include <toolbox_config/tbx_assert.hpp>

// TODO: do more general functions with an sizeof() for swapping algo

// =============================================================================
namespace asset {
// =============================================================================

// =============================================================================
namespace endianess {
// =============================================================================

static bool g_initialized = false;

short (*big_short)    ( short s ) = 0;
short (*little_short) ( short s ) = 0;
int   (*big_long)     ( int i   ) = 0;
int   (*little_long)  ( int i   ) = 0;
float (*big_float)    ( float f ) = 0;
float (*little_float) ( float f ) = 0;

// -----------------------------------------------------------------------------

bool is_little_endian()
{
    union {
        uint32_t i;
        uint8_t c[4];
    } bint = {0x01020304};

    // little endian if true
    return bint.c[0] != 1;
}

// -----------------------------------------------------------------------------

short short_swap( short s )
{
    tbx_assert( g_initialized && "ERROR: Please call endianess::init() before using the module");
    unsigned char b1, b2;

    b1 = s & 255;
    b2 = (s >> 8) & 255;

    return (b1 << 8) + b2;
}

// -----------------------------------------------------------------------------

short short_no_swap( short s )
{
    tbx_assert( g_initialized && "ERROR: Please call Endianess::init() before using the module");
    return s;
}

// -----------------------------------------------------------------------------

int long_swap (int i)
{
    tbx_assert( g_initialized && "ERROR: Please call endianess::init() before using the module");
    unsigned char b1, b2, b3, b4;

    b1 = i & 255;
    b2 = ( i >> 8 ) & 255;
    b3 = ( i>>16 ) & 255;
    b4 = ( i>>24 ) & 255;

    int a = ((int)b1 << 24) + ((int)b2 << 16) + ((int)b3 << 8) + b4;
    return a;
}

// -----------------------------------------------------------------------------

int long_no_swap( int i )
{
    tbx_assert( g_initialized && "ERROR: Please call endianess::init() before using the module");
    return i;
}

// -----------------------------------------------------------------------------

float float_swap( float f )
{
    tbx_assert( g_initialized && "ERROR: Please call endianess::init() before using the module");
    union
    {
        float f;
        unsigned char b[4];
    } dat1, dat2;

    dat1.f = f;
    dat2.b[0] = dat1.b[3];
    dat2.b[1] = dat1.b[2];
    dat2.b[2] = dat1.b[1];
    dat2.b[3] = dat1.b[0];
    return dat2.f;
}

// -----------------------------------------------------------------------------

float float_no_swap( float f )
{
    tbx_assert( g_initialized && "ERROR: Please call endianess::init() before using the module");
    return f;
}

// -----------------------------------------------------------------------------

void init()
{
    //set func pointers to correct funcs
    if( is_little_endian() )
    {
        //little endian
        big_short    = short_swap;
        little_short = short_no_swap;
        big_long     = long_swap;
        little_long  = long_no_swap;
        big_float    = float_swap;
        little_float = float_no_swap;
    }
    else
    {
        //big endian
        big_short    = short_no_swap;
        little_short = short_swap;
        big_long     = long_no_swap;
        little_long  = long_swap;
        big_float    = float_swap;
        little_float = float_no_swap;
    }

    g_initialized = true;
}

} // END endianess namespace  ==================================================

} // END asset Namespace =======================================================
