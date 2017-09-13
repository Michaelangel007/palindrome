// Enum
    enum Compare_e
    {
    //  CMP_LE = -2,
        CMP_LT = -1,
        CMP_EQ =  0,
        CMP_GT = +1
    //  CMP_GE = +2
    };

// Utility

    /*
     * Compare two strings
     * Assumes strings are in Big Endian format
     *
     * | a ? b | Result |
     * |:-----:|:------:|
     * |   <   | CMP_LT |
     * |   =   | CMP_EQ |
     * |   >   | CMP_GT |
     *
     * To compare BigInt
     *
     *     compare_be( a.digits(), a.head(), b.digits(), b.head() );
     *
     * @param {char*} aTxt - Head of string of digits in base 10
     * @param (char*} bTxt - Head of string of digits in base 10
     * @return {Compare_e}
     */
    // ========================================================================
    int compare_be( size_t aLen, const char *aTxt, size_t bLen, const char *bTxt )
    {
#if 0 // DEBUG
    printf( "Cmp()\n" );
    printf( "\tLen: %u, Txt: %s\n", (unsigned) aLen, aTxt );
    printf( "\tLen: %u, Txt: %s\n", (unsigned) bLen, bTxt );
#endif

        /*
            3 cases:

            lhs.num_digits < rhs.num_digits
            lhs.num_digits = rhs.num_digits
            lhs.num_digits > rhs.num_digits
        */

        const char *pSrc = aTxt; // a.head() // &aTxt[ aLen - 1 ];
        const char *pDst = bTxt; // b.head() // &bTxt[ bLen - 1 ];

        /*
            ###aaa
               bbb
        */
        while (aLen > bLen)
        {
            if (*pSrc != '0')
                return CMP_GT;

            aLen--;
            pSrc++;
        }

        /*
               aaa
            ###bbb
        */
        while (aLen < bLen)
        {
            if (*pSrc != '0')
                return CMP_LT;

            bLen--;
            pDst++;
        }

        while( aLen --> 0 )
        {
            if( *pSrc < *pDst ) return CMP_LT;
            if( *pSrc > *pDst ) return CMP_GT;

            pSrc++;
            pDst++;
        }

        return CMP_EQ; // equal
    }

