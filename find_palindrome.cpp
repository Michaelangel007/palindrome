/*
Michaelangel007
https://github.com/Michaelangel007/palindrome

What's special about 196?
https://www.youtube.com/watch?v=bN8PE3eljdA

Benchmark:

    BIGINT_SIZE 256
    findpal 89 1,007,601
        Elapsed time: 00:01:05.675 (66 seconds)
        Throughput: 14 K Num/s (1007513 samples)

    findpal 1000 101,000
        Elapsed time: 00:00:03.393 (3 seconds)
        Throughput: 28 K Num/s (100001 samples)


    BIGINT_SIZE 128
    findpal 89 1,007,601
        Elapsed time: 00:00:40.048 (40 seconds)
        Throughput: 24 K Num/s (1007513 samples)
*/

#define BIGINT_SIZE  256 - 17 // 16 bytes/class + digit capacity + null sentinel
#define MAX_DEPTH    333

// Include
    #include "inc.h"

// Macros
    #define IN(text) fprintf( stdout, "> %s\n", text ); fflush( stdout )

// Globals
    int gnRecord =    0; // Highest depth

    BigInt10 *gpBeg = 0;
    BigInt10 *gpEnd = 0;

// Implementation


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

    printf( "sizeof( bigint10 ): %d\n", BigInt10::size() );

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

    uint64_t delta = 0;

    printf( "Starting @ %s\n", x.toString() );
    printf( "Looking for 1st palindrome > %d iterations...\n", gnRecord );

    signal( SIGINT, onCtrlC );

    Timer timer;
    timer.Start();

    for( ; x <= y; x += ONE, delta++ )
    {
#if FIND == 1 // VER1
        r = findPalindrome( x );
#else // VER2
        r = findPalindrome2( x );
#endif

        if( gnCycles < 0 ) // Couldn't verify is a palindrome
            continue;

        if( gnRecord < gnCycles )
        {
            printf( "New record: %d digits, ", x.digits() );
#if BIGINT_TOSTRING
            printf( "%s", x.toString() );
#else
            x.print();
#endif
            printf( ", %d iterations (%d digits)\n", gnCycles , r.digits());
            gnRecord = gnCycles;
        }
    }

    timer.Stop( true );
    timer.Throughput( delta );
    timer.Print( "Num" );

    printf( "\n" );

    return 0;
}

