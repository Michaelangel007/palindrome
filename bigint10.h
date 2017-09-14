#ifndef BIGINT_SIZE
#define BIGINT_SIZE 128
#endif

// Enums
    enum
    {
        _K = 1024,
        _M = _K * _K,
        _G = _M * _K
    };

// Right-Align Base 10, 1 byte per digit
class BigInt10
{
    enum { CAPACITY = BIGINT_SIZE };

    size_t  _nDigits;
    char   *_pDigits;

    // ========================================================================
    inline void alloc()
    {
        _pDigits = (char*) malloc( CAPACITY + 1 );
    }

    // ========================================================================
    inline void clear()
    {
        memset( _pDigits, '0', CAPACITY );
    }

    // ========================================================================
    inline void clone( const char *source )
    {
        alloc();
        memcpy( _pDigits, source, CAPACITY );
    }

    // ========================================================================
    inline void init()
    {
        alloc();
        clear();

        _nDigits = 0;
        _pDigits[ CAPACITY ]  = 0;
    }

    /*
        Capacity = 6
        Digits   = 3

            ___abc
            0123456
               .  ^_capacity
               . ^
               . tail
               ^
               head
    */
    /* */ char* head()       { return _pDigits + CAPACITY - _nDigits; }
    /* */ char* tail()       { return _pDigits + CAPACITY - 1       ; }

    const char* head() const { return _pDigits + CAPACITY - _nDigits; }
    const char* tail() const { return _pDigits + CAPACITY - 1       ; }

public:

    // ========================================================================
    BigInt10()
    {
        init();
    }

    // Ctor
    // ========================================================================
    BigInt10( const uint64_t x )
    {
        fromNumber( x );
    }

    // Ctor
    // ========================================================================
    BigInt10( const char *text )
    {
        fromString( text );
    }

    // Copy Ctor
    BigInt10( const BigInt10& rhs )
    {
        *this = rhs;

        // Now deep copy digits
        clone( rhs._pDigits );
    }

    // ========================================================================
    unsigned int digits() const
    {
        return (unsigned int) _nDigits; // return type changed from size_t
    }

    // ========================================================================
    inline void dump( const char *prefix = 0, const char *suffix = 0 ) const
    {
        if( prefix )
            printf( "%s", prefix );

        if( suffix )
            printf( "%s%s", _pDigits, suffix );
        else
            printf( "%s\n", _pDigits );
    }

    // ========================================================================
    BigInt10& fromNumber( const uint64_t x )
    {
        init();

        uint64_t y = x;

        char *pSrc = tail();
        char *pDst = tail();

        while( y > 9 )
        {
            *pDst-- = (y % 10) + '0';
            y /= 10;
        }

        *pDst-- = y + '0';
        _nDigits = pDst - pSrc;

        return *this;
    }

    // ========================================================================
    BigInt10& fromString( const char *text )
    {
        init();

        /* */ size_t nLen;
        const char  *pSrc = text;
        /* */ char  *pDst = tail();

        // Find end of valid string -- any non-digit is sentinel
        // Also remove commas
        while( *pSrc && (((*pSrc >= '0') && (*pSrc <= '9')) || (*pSrc == ',')) )
            pSrc++;

        _nDigits = (pSrc - text);

        if( _nDigits == 0 ) // "" -> 1 digit: '0'
            _nDigits = 1;
        else
        {
            // Move Left-Aligned to Right-Aligned
            nLen = _nDigits;
            pSrc--;

            while( nLen --> 0 )
            {
                if( *pSrc != ',' )
                    *pDst-- = *pSrc;
                pSrc--;
            }

            // Strip off leading zeroes
            minDigits();
        }

        return *this;
    }

    // Strip Leading Zeroes
    // ========================================================================
    inline void minDigits()
    {
        const char *pSrc = _pDigits; // head();
        /* */ char *pEnd = tail();

        while( *pSrc == '0' )
            pSrc++;

        if( pSrc >= pEnd )
            pSrc =  pEnd; // Digits = 1

        _nDigits = pEnd - pSrc + 1;
    }

// Benchmarks: time findpal 89 1,007,601
//
// isPalindrome      real 1m8.625s
// isPalindromeXOR   real 1m16.079s

    // ========================================================================
    int isPalindrome() const
    {
        if (_nDigits < 1) return 0; // zero digits  = never
        if (_nDigits < 2) return 1; // single digit = always

        const char *pSrc = head();
        const char *pDst = tail();

        while( pSrc < pDst )
        {
            if( *pSrc != *pDst )
                return 0;

            pSrc++;
            pDst--;
        }

        return 1;
    }

    // NOTE: This isn't as fast as isPalindrome()
    inline int isPalindromeXOR() const
    {
        int sum = 0;

        const char *pSrc = head();
        const char *pDst = tail();

        while( pSrc < pDst )
            sum += (*pSrc++ ^ *pDst--);

        return sum == 0;
    }

    // ========================================================================
    BigInt10& reverse( const BigInt10& rhs )
    {
        /* */ size_t  nLen = rhs._nDigits;
        const char   *pSrc = rhs.head();
        /* */ char   *pDst =     tail();

        _nDigits = nLen;
        while( nLen --> 0 )
            *pDst-- = *pSrc++;

        return *this;
    }

    // Since the number if right-aligned there is nothing to do for printing
    // except return the pointer to the first (far left) character
    // ========================================================================
    const char* toString() const
    {
        return (const char*) head();
    }

    // Add
    // ========================================================================
    BigInt10& operator += ( const BigInt10& rhs )
    {
        const char *pSrc = rhs.tail();
        /* */ char *pDst =     tail();

        char   carry = 0; // add: carry = 0; ripple carry: c = a + b + c
        size_t nLen  = rhs._nDigits;

        // rhs      cba
        //            ^
        //            pSrc
        // this   EDCBA
        //            ^
        //            pDst
        while( nLen --> 0 )
        {
            //  9  0x09
            //  9  0x09
            // 18  0x12
            carry += (*pSrc & 0xF) + (*pDst & 0xF);
            *pDst = (carry % 10) + '0';
            carry /= 10;

            pSrc--;
            pDst--;
        }

        while( carry )
        {
            carry += (*pDst & 0xF);

            *pDst = (carry % 10) + '0';
            carry /= 10;

            pDst--;
        }

        minDigits();

        if( _nDigits > CAPACITY )
            _nDigits = -1; // ERROR: Overflow

        return *this;
    }

    inline friend
    int compare( const BigInt10& lhs, const BigInt10& rhs )
    {
        return compare_be(
            lhs.digits(), lhs.head() ,
            rhs.digits(), rhs.head()
        );
    }

    // ========================================================================
    bool operator == (const BigInt10& rhs ) const
    {
        return compare( *this, rhs ) == CMP_EQ;
    }

    // ========================================================================
    bool operator <= (const BigInt10& rhs ) const
    {
        return compare( *this, rhs ) != CMP_GT;
    }
};

