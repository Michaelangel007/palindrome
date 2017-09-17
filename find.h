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

    /* Use: AddRev(), memoization
     * @return -1 if number is probably a Lychrel Number
     */
    // ========================================================================
    BigInt10 findPalindrome3( BigInt10& x )
    {
        BigInt10 s( x );

        gnCycles = 0;

#if MEMO
        giMemo   = 0;
#endif

#if FIND_DEBUG
        printf( "\n@ %s\n", s.toString() );
#endif

        while( true )
        {
            if( s.isPalindrome() )
            {
#if MEMO
                if( giHistory < gnHistory )
                {
                    // Go back and fill in iteration counts for this run
                    for( int i = 0; i < giMemo; i++ )
                    {
    #if FIND_DEBUG
                        printf( "Adding %d/%d: %s, cycles: %d\n"
                            , i+1, giMemo
                            , gaMemo[ i ].key.toString(), gnCycles - i
                        );
    #endif
                        hist_insert( gaMemo[ i ].key, gnCycles - i ); // hist_insert( memo_pop(), gnCycles - i );
                    }
                }
//printf( "History: %d / %d\n", giHistory, gnHistory );
#endif
                break;
            }

            if (++gnCycles > gnDepth)
            {
                gnCycles = -1;
                break;
            }

            if( gbTrace )
                printf( "%3d) %s + ... = ", gnCycles, s.toString() );

            s.AddRev();

#if MEMO
            // Check if s is in history
            if( giHistory < gnHistory )
            {
                int pos = hist_find( s );
                if( pos )
                {
    #if FIND_DEBUG
                    printf( "Found '%s' @ %2d :", s.toString(), pos );
    #endif

                    gnCycles += hist_val( pos ) - 1;
                    s = gaHistory[ pos-1 ].key;

    #if FIND_DEBUG
                    printf( "'%s' (cycles: %d)\n", gaHistory[ pos-1 ].key.toString(), gnCycles );
    #endif
                    break;
                }
                else
                {
    #if FIND_DEBUG
                    printf( "Push: %s\n", s.toString() );
    #endif

                    memo_push( s );
                }
            }
#endif // MEMO

            if( gbTrace )
                printf( "%s\n", s.toString() );
        }

        return s;
    }

