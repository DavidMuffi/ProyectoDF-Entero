#include "half.h"


/*
//half half::multiplicar(half a, half b) {    // sin OV ni UF

half half::operator * (half a, half b){

    int mantA, mantB, mant, exp, mask;
    bool sign;
    half res;

    sign = a.sign ^ b.sign;

    if (a.zero || b.zero) {
        res.mant = 0;
        res.exp = 0;
        res.sign = sign;
        res.zero = true;
        return res;
    }
 
    exp = a.exp + b.exp;

    mantA = (int)a.mant;
    mantB = (int)b.mant;

    mant = mantA * mantB;
    if (mant & 0x100000) { // comprobar
        ++exp;
        mant >>= 11;
    }else
        mant >>= 10;

    res.mant = mant;
    res.exp = exp;
    res.sign = sign;
    res.zero = false;

    return res;
}


//half half::sumar(half a, half b) {    // sin OV ni UF
 half half::operator +(half a, half b) {

    short mantA, mantB, mant, exp, mask; 
    bool sign;
    half res;

    if (a.zero)        return b; 
    if (b.zero)        return a;

    exp = a.exp; 

    if (a.exp > b.exp) {
        mantA = a.mant << 3; // gano 3 bits (11+3)
        mantB = (b.mant << 3) >> (a.exp - b.exp);
    }

    if (a.exp < b.exp) {
        mantB = b.mant << 3; // gano 3 bits (11+3)
        mantA = (a.mant << 3) >> (b.exp - a.exp);
        exp = b.exp;
    }

    if (a.exp = b.exp) {
        mantA = a.mant << 3;
        mantB = b.mant << 3;
    }

    if (a.sign) mantA = -mantA; 
    if (b.sign) mantB = -mantB;

    mant = mantA + mantB;
    if (mant < 0) {
        sign = 1; 
        mant = -mant; 
    }
    else
        sign = 0;
  
    if (mant & 4000) {
        res.mant = mant >> 4;
        res.exp = res + 1;
        res.sign = sign;
        res.zero = false;
    }
    else {
        mask = 0x2000; 
        int i;
        for (i = 0; i < 14; ++i) {
            if (mask & mant)
                break;
            mant <<= 1; 
        }

        if (i==14) {
            res.mant = 0;
            res.exp = 0;
            res.sign = sign;
            res.zero = true;
        }
        else {
            res.mant = mant >> 3;
            res.exp = exp - i;
            res.sign = sign;
            res.zero = false;
        }
    }

    return res; 
}

half half::restar(half a, half b) {    // sin OV ni UF

    half tmp;
    tmp = b;
    b.sign = !b.sign; 

    return sumar(a, tmp);
}
*/

/*

#define CONVERT_PATTERN( x )  ( reinterpret_cast<UINT32 *>( &x ) )

FLOAT16::FLOAT16() : m_uiFormat(0) {}

FLOAT16::FLOAT16( CONST FLOAT16 & rhs ) : m_uiFormat( rhs.m_uiFormat ) {}

FLOAT16::FLOAT16( CONST FLOAT32 & rhs )
{
    (*this) = rhs;
}

FLOAT16::~FLOAT16() {}

FLOAT16::operator FLOAT32()
{
    return ToFloat32( *this );
}

FLOAT16 & FLOAT16::operator = ( CONST FLOAT16 & rhs )
{
    m_uiFormat = rhs.m_uiFormat;

    return (*this);
}

FLOAT16 & FLOAT16::operator = ( CONST FLOAT32 & rhs )
{
    (*this) = ToFloat16( rhs );

    return (*this);
}

BOOL FLOAT16::operator == ( CONST FLOAT16 & rhs ) CONST
{
    return m_uiFormat == rhs.m_uiFormat;
}

BOOL FLOAT16::operator != ( CONST FLOAT16 & rhs ) CONST
{
    return !( (*this) == rhs );
}

FLOAT32 FLOAT16::ToFloat32( FLOAT16 rhs )
{
    FLOAT32 fOutput   = 0;                                  // floating point result
    UINT32 * uiOutput = CONVERT_PATTERN( fOutput );         // bit manipulated output

    if ( 0 == rhs.m_uiFormat )           return 0.0f;       // +zero
    else if ( 0x8000 == rhs.m_uiFormat ) return -0.0f;      // -zero

    UINT32 uiHalfSignBit   = GET_HALF_SIGN_BIT( rhs.m_uiFormat );
    UINT32 uiHalfMantBits  = GET_HALF_MANT_BITS( rhs.m_uiFormat ) << 13;
     INT32  iHalfExpBits   = GET_HALF_EXP_BITS( rhs.m_uiFormat );

    //
    // Next we check for additional special cases:
    //

    if ( 0 == iHalfExpBits )
    {
        //
        // Denormalized values
        //

        SET_SINGLE_SIGN_BIT( uiHalfSignBit, (*uiOutput) );
        SET_SINGLE_EXP_BITS( 0, (*uiOutput) );
        SET_SINGLE_MANT_BITS( uiHalfMantBits, (*uiOutput) );
    }

    else if ( 0x1F == iHalfExpBits )
    {
        if ( 0 == uiHalfMantBits )
        {
            //
            // +- Infinity
            //

            (*uiOutput) = ( uiHalfSignBit ? SINGLE_NEG_INFINITY : SINGLE_POS_INFINITY );
        }
        else
        {
            //
            // (S/Q)NaN
            //

            SET_SINGLE_SIGN_BIT( uiHalfSignBit, (*uiOutput) );
            SET_SINGLE_EXP_BITS( 0xFF, (*uiOutput) );
            SET_SINGLE_MANT_BITS( uiHalfMantBits, (*uiOutput) );
        }
    }

    else
    {
        //
        // Normalized values
        //

        SET_SINGLE_SIGN_BIT( uiHalfSignBit, (*uiOutput) );
        SET_SINGLE_EXP_BITS( ( iHalfExpBits - 15 ) + 127, (*uiOutput) );
        SET_SINGLE_MANT_BITS( uiHalfMantBits, (*uiOutput) );
    }

    //
    // ATP: uiOutput equals the bit pattern of our floating point result.
    //

    return fOutput;
}

FLOAT16 FLOAT16::ToFloat16( FLOAT32 rhs )
{
    //
    // (!) Truncation will occur for values outside the representable range for float16.
    //   

    FLOAT16 fOutput;
    UINT32 uiInput  = *CONVERT_PATTERN( rhs );

    if ( 0.0f == rhs ) 
    { 
        fOutput.m_uiFormat = 0; 
        return fOutput;
    }
     
    else if ( -0.0f == rhs )
    {
        fOutput.m_uiFormat = 0x8000; 
        return fOutput;
    }

    UINT32 uiSignBit   = GET_SINGLE_SIGN_BIT( uiInput );
    UINT32 uiMantBits  = GET_SINGLE_MANT_BITS( uiInput ) >> 13;
     INT32  iExpBits   = GET_SINGLE_EXP_BITS( uiInput );

    //
    // Next we check for additional special cases:
    //

    if ( 0 == iExpBits )
    {
        //
        // Denormalized values
        //

        SET_HALF_SIGN_BIT( uiSignBit, fOutput.m_uiFormat );
        SET_HALF_EXP_BITS( 0, fOutput.m_uiFormat );
        SET_HALF_MANT_BITS( uiMantBits, fOutput.m_uiFormat );
    }

    else if ( 0xFF == iExpBits )
    {
        if ( 0 == uiMantBits )
        {
            //
            // +- Infinity
            //

            fOutput.m_uiFormat = ( uiSignBit ? HALF_NEG_INFINITY : HALF_POS_INFINITY );
        }
        else
        {
            //
            // (S/Q)NaN
            //

            SET_HALF_SIGN_BIT( uiSignBit, fOutput.m_uiFormat );
            SET_HALF_EXP_BITS( 0x1F, fOutput.m_uiFormat );
            SET_HALF_MANT_BITS( uiMantBits, fOutput.m_uiFormat );
        }
    }

    else
    {
        //
        // Normalized values
        //

        INT32 iExponent = iExpBits - 127 + 15;

        if ( iExponent < 0 ) { iExponent = 0; }
        else if ( iExponent > 31 ) iExponent = 31;
            
        SET_HALF_SIGN_BIT( uiSignBit, fOutput.m_uiFormat );
        SET_HALF_EXP_BITS( iExponent, fOutput.m_uiFormat );
        SET_HALF_MANT_BITS( uiMantBits, fOutput.m_uiFormat );
    }

    //
    // ATP: uiOutput equals the bit pattern of our floating point result.
    //

    return fOutput;
}


FLOAT32 FLOAT16::ToFloat32Fast( FLOAT16 rhs )
{
    FLOAT32 fOutput   = 0;                                  // floating point result
    UINT32 * uiOutput = CONVERT_PATTERN( fOutput );         // bit manipulated output

    if ( 0 == rhs.m_uiFormat )           return 0.0f;       // +zero
    else if ( 0x8000 == rhs.m_uiFormat ) return -0.0f;      // -zero

    UINT32 uiHalfSignBit   = GET_HALF_SIGN_BIT( rhs.m_uiFormat );
    UINT32 uiHalfMantBits  = GET_HALF_MANT_BITS( rhs.m_uiFormat ) << 13;
     INT32  iHalfExpBits   = GET_HALF_EXP_BITS( rhs.m_uiFormat );

    //
    // Normalized values
    //

    SET_SINGLE_SIGN_BIT( uiHalfSignBit, (*uiOutput) );
    SET_SINGLE_EXP_BITS( ( iHalfExpBits - 15 ) + 127, (*uiOutput) );
    SET_SINGLE_MANT_BITS( uiHalfMantBits, (*uiOutput) );

    //
    // ATP: uiOutput equals the bit pattern of our floating point result.
    //

    return fOutput;
}

FLOAT16 FLOAT16::ToFloat16Fast( FLOAT32 rhs )
{
    //
    // (!) Truncation will occur for values outside the representable range for float16.
    //   

    FLOAT16 fOutput;
    UINT32 uiInput  = *CONVERT_PATTERN( rhs );

    if ( 0.0f == rhs ) 
    { 
        fOutput.m_uiFormat = 0; 
        return fOutput;
    }
     
    else if ( -0.0f == rhs )
    {
        fOutput.m_uiFormat = 0x8000; 
        return fOutput;
    }

    UINT32 uiSignBit   = GET_SINGLE_SIGN_BIT( uiInput );
    UINT32 uiMantBits  = GET_SINGLE_MANT_BITS( uiInput ) >> 13;
     INT32  iExpBits   = GET_SINGLE_EXP_BITS( uiInput );

    //
    // Normalized values
    //

    INT32 iExponent = iExpBits - 127 + 15;

    if ( iExponent < 0 ) { iExponent = 0; }
    else if ( iExponent > 31 ) iExponent = 31;
            
    SET_HALF_SIGN_BIT( uiSignBit, fOutput.m_uiFormat );
    SET_HALF_EXP_BITS( iExponent, fOutput.m_uiFormat );
    SET_HALF_MANT_BITS( uiMantBits, fOutput.m_uiFormat );

    //
    // ATP: uiOutput equals the bit pattern of our floating point result.
    //

    return fOutput;
}

*/