// System Includes
    #include <stdio.h>
    #include <stdint.h> // uint64_t
    #include <string.h> // memset()
    #include <stdlib.h> // malloc()
    #include <signal.h> // signal()

// Defines

    #define BIGINT_TOSTRING 1
    #define FIND_VER        3 // version 1, 2 or 3

#if FIND_VER == 1
    #define FIND findPalindrome1
#endif
#if FIND_VER == 2
    #define FIND findPalindrome2
#endif
#if FIND_VER == 3
    #define FIND findPalindrome3
#endif

#ifndef MEMO
    #define MEMO            1 // on/off
#endif

// User Includes
    #include "compare.h"
    #include "bigint10.h"
    #include "util_timer.h"
    #include "memo.h"
    #include "find.h"
