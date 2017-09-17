#define FIND_DEBUG 0

// Globals
    int gbTrace  =   0;
    int gnCycles =   0; // Current depth
#if MAX_DEPTH
    int gnDepth  = MAX_DEPTH;
#else
    int gnDepth  = 333; // Maximum depth
#endif

// Implementation

    /* Use: reverse() +=()
     * @return -1 if number is probably a Lychrel Number
     */
    // ========================================================================
    BigInt10 findPalindrome1( BigInt10& x )
    {
        gnCycles = 0;

        BigInt10 r;
        BigInt10 s( x );

        while( true )
        {
           if( s.isPalindrome() )
               break;

            r.reverse( s );

            if (++gnCycles > gnDepth)
            {
                gnCycles = -1;
                return s;
            }

            if( gbTrace )
            {
#if BIGINT_TOSTRING
                printf( "%3d) %s + %s = ", gnCycles, s.toString(), r.toString() );
#else
                printf( "%3d) ", gnCycles );
                s.print();
                printf( " + " );
                r.print();
#endif
            }

            s += r;

            if( gbTrace )
            {
#if BIGINT_TOSTRING
                printf( "%s\n", s.toString() );
#else
                s.print();
                printf( "\n" );
#endif
            }
        }

        return s;
    }

    /* Use: AddRev()
     * @return -1 if number is probably a Lychrel Number
     */
    // ========================================================================
    BigInt10 findPalindrome2( BigInt10& x )
    {
        BigInt10 s( x );

#if FIND_DEBUG
        printf( "@ %s\n", s.toString() );
#endif

        gnCycles = 0;

        while( true )
        {
            if( s.isPalindrome() )
                break;

            if (++gnCycles > gnDepth)
            {
                gnCycles = -1;
                break;
            }

            if( gbTrace )
                printf( "%3d) %s + ... = ", gnCycles, s.toString() );

            s.AddRev();

            if( gbTrace )
                printf( "%s\n", s.toString() );
        }

        return s;
    }

