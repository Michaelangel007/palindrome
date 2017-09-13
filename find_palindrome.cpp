/*
Michaelangel007
https://github.com/Michaelangel007/palindrome

What's special about 196?
https://www.youtube.com/watch?v=bN8PE3eljdA

Benchmark:

    time findpal 89 1,007,601

*/

#define BIGINT_SIZE         256
#define BENCH_IS_PALINDROME 0

// Include
    #include "inc.h"

// Macros
    #define IN(text) fprintf( stdout, "> %s\n", text ); fflush( stdout )

// Globals
    int gbTrace  =    0;
    int gnCycles =    0; // Current depth
    int gnDepth  = 1024; // Maximum depth
    int gnRecord =    0; // Highest depth

    BigInt10 *gpBeg = 0;
    BigInt10 *gpEnd = 0;

// Implementation

    /*
    @return -1 if number is probably a Lychrel Number

    */
    // ========================================================================
    BigInt10 findPalindrome( BigInt10 x )
    {
        gnCycles = 0;

        BigInt10 r;
        BigInt10 s( x );

        while( true )
        {
//  Test which version is faster
#if BENCH_IS_PALINDROME == 0
            if( s.isPalindrome() )
                break;
#endif
#if BENCH_IS_PALINDROME == 1
            if( s.isPalindromeXOR() )
                break;
#endif

            r.reverse( s );

            //printf( "@  %d\n", depth );
            gnCycles++;
            if (gnCycles > gnDepth) //if( (s.digits() < 1)
            {
                gnCycles = -1;
                return s;
            }

            if( gbTrace )
                printf( "%3d) %s + %s = ", gnCycles, s.toString(), r.toString() );

            s += r;

            if( gbTrace )
                printf( "%s\n", s.toString() );
        }

        return s;
    }


// =======================================================================
void onCtrlC( int sig )
{
    char  c;

    signal( sig, SIG_IGN );

    printf( "Stopped at: %s\n", gpBeg->toString() );
    printf( "Resume via:\n" );
    printf( "   findpal %s %s %u\n", gpBeg->toString(), gpEnd->toString(), gnRecord );
    printf( "Do you really want to quit? [y/n] ");

    c = getchar();
    if (c == 'y' || c == 'Y')
        exit(0);
    else
        signal( SIGINT, onCtrlC ); // Resume

    getchar(); // Eat CR
}


// [Start [End [MaxDepth]]]
// =======================================================================
int main( const int nArg, const char *aArg[] )
{
    const char *text1 = (nArg > 1) ?       aArg[1] :  "11";
    const char *text2 = (nArg > 2) ?       aArg[2] : " 99";
    gnRecord          = (nArg > 3) ? atoi( aArg[3] ): gnRecord;

    if( nArg < 2 )
    {
        printf(
"Usage: start end mindepth\n"
"\n"
"  start     Start number to check\n"
"  end       End   number to check\n"
"  mindepth  Only  report 1st number that has this minimum depth\n"
"  #    Trace # if it becomes a palindrome\n"
"\n"
"Examples:\n"
"  findpal 11 99 10      # Will find 98 has depth 24\n"
"  findpal 89 1,007,601  # List all new palindromes between 89 and 1,007,601\n"
"\n"
        );

        return 0;
    }

    BigInt10 ONE( "1" );
    BigInt10   x( text1 );
    BigInt10   y( text2 );
    BigInt10   r; // reverse

    gpBeg = &x;
    gpEnd = &y;

    printf( "Starting @ %s\n", x.toString() );
    printf( "Looking for 1st palindrome > %d iterations...\n", gnRecord );

    signal( SIGINT, onCtrlC );

    for( ; x <= y; x += ONE )
    {
        r = findPalindrome( x );

        if( gnCycles < 0 ) // Couldn't verify is a palindrome
            continue;

        if( gnRecord < gnCycles )
        {
            printf( "New record: %d digits, %s, %d iterations (%d digits)\n"
                , x.digits()
                , x.toString()
                , gnCycles
                , r.digits()
            );
            gnRecord = gnCycles;
        }
    }

    printf( "\n" );

    return 0;
}

