// Globals
    int gbTrace  =    0;
    int gnCycles =    0; // Current depth
    int gnDepth  = 1024; // Maximum depth

// Implementation
    /*
     * @return -1 if number is probably a Lychrel Number
     */
    // ========================================================================
    BigInt10 findPalindrome( BigInt10 x )
    {
        gnCycles = 0;

        BigInt10 r;
        BigInt10 s( x );

        while( true )
        {
           if( s.isPalindrome() )
               break;

            r.reverse( s );

            //printf( "@  %d\n", depth );
            gnCycles++;
            if (gnCycles > gnDepth) //if( (s.digits() < 1)
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

