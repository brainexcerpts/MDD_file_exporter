#ifndef ASSET_ENDIANESS_HPP
#define ASSET_ENDIANESS_HPP

/**
    @namespace ::asset::endianess
    @brief System independant conversions between big or little endian.

    These functions are independent from the system endianess as long as
    'init()' is called before using the conversion functions
*/

// =============================================================================
namespace asset {
// =============================================================================

// =============================================================================
namespace endianess {
// =============================================================================

/// setup the pointer functions depending on the system endianess.
void init();

/// @return wether the system is big or little endian.
bool is_little_endian();

/// @name endianess conversions (regardless of the system's endianess)
/// @{

/// @return a big endian short
extern short (*big_short)    ( short s );
/// @return a little endian short
extern short (*little_short) ( short s );
/// @return a big endian long
extern int   (*big_long)     ( int i   );
/// @return a little endian long
extern int   (*little_long)  ( int i   );
/// @return a big endian float
extern float (*big_float)    ( float f );
/// @return a little endian float
extern float (*little_float) ( float f );

/// @}

}// END endianess namespace ====================================================

}//END asset NAMESPACE =========================================================

#endif // ASSET_ENDIANESS_HPP
