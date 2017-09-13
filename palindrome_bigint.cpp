/*
Michaelangel007
https://github.com/Michaelangel007/palindrome

What's special about 196?
https://www.youtube.com/watch?v=bN8PE3eljdA

1186060307891929990
0x1075BB90_E616C386  // echo "obase=16;1186060307891929990" | bc
Cycles: 261
Digits: 119
*/


// Include
    #include "inc.h"

// Macros
    #define IN(text) fprintf( stdout, "> %s\n", text ); fflush( stdout )

// Globals
    int gbTrace  =    0;
    int gnCycles =    0; // Current depth
    int gnDepth  = 1024; // Maximum depth

// Utility

// Implementation

    /**
     *  @return -1 if number is probably a Lychrel Number
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
                printf( "%3d) %s + %s = ", gnCycles, s.toString(), r.toString() );

            s += r;

            if( gbTrace )
                printf( "%s\n", s.toString() );
        }

        return s;
    }


// ========================================================================
int main( const int nArg, const char *aArg[] )
{
    const char *text1 = (nArg > 1) ? aArg[1] :  "89";
    const char *text2 = (nArg > 2) ? aArg[2] : "195";

    if( nArg < 2 )
    {
        printf(
"Usage:\n"
"\n"
"  #    Trace # if it becomes a palindrome\n"
"       i.e. 196\n"
"  # #  Test range [start,end] and print number of cycles for each\n"
"       i.e. 98 988\n"
"\n"
        );
    }

    BigInt10   x( text1 );
    BigInt10   y( text2 );
    BigInt10   r; // reverse

    // Trace #
    if( nArg <= 2 )
    {
        gbTrace = 1;
        r = findPalindrome( x );

        if( gnCycles != -1 )
        {
            printf( "Palindrome: %s\n", r.toString() );
            printf( "Cycles:     %d\n", gnCycles     );
            printf( "Digits:     %u\n", r.digits()   );
        }
        else
        {
            printf( "Stopped after cycles: %d\n", gnDepth );
            printf( "Unknown solution.\n" );
        }
    }

    // Start End
    if( nArg == 3 )
    {
        BigInt10 ONE( "1" );
        BigInt10 TWO( "2" );

        size_t cols = 0;

        for( ; x <= y; x += ONE )
        {
            r = findPalindrome( x );

#if BIGINT_TOSTRING
            printf( "%3s:%4d, ", x.toString(), gnCycles );
#else
            x.print();
            printf( ":%4d, ", gnCycles );
#endif

            if( cols++ && ((cols % 10) == 0) )
                printf( "\n" );
        }

        printf( "\n" );
    }

   return 0;
}
