// Extern
    extern int gnDepth;

// Types
    struct Memoization
    {
        BigInt10 key;
        int      val;

        void init()
        {
            key.fromNumber( 0 );
            val = 0;
        }
    };

// Globals
    int          giHistory =    0; // size
    int          gnHistory = 4096; // capacity
    Memoization *gaHistory = NULL; // [ 4096 ] all iterations

    int          giMemo; // size
    int          gnMemo; // capacity
    Memoization *gaMemo; // [ gnMemo ] current iterations

// Implementation

    // ========================================================================
    void hist_init( int capacity )
    {
        giHistory = 0;
        gnHistory = capacity;
        gaHistory = (Memoization*) malloc( gnHistory * sizeof( Memoization ) );

        for( int i = 0; i < gnHistory; i++ )
            gaHistory[ i ].init();
    }

    // ========================================================================
    int hist_find( BigInt10& key )
    {
        if( giHistory )
        {
            for( int i = 0; i < giHistory; i++ )
            {
                if( gaHistory[i].key == key )
                    return i+1;
            }
        }

        return 0;
    }

    // ========================================================================
    void hist_insert( BigInt10& key, int val )
    {
        if( giHistory >= gnHistory )
            return;

        gaHistory[ giHistory ].key.clone( key );
        gaHistory[ giHistory ].val = val;
                   giHistory++;
    }
    // ========================================================================
    inline int hist_val( int pos )
    {
        return gaHistory[ pos-1 ].val;
    }

    // ========================================================================
    void memo_init( int capacity )
    {
        giMemo = 0;
        gnMemo = capacity;
        gaMemo = (Memoization*) malloc( gnMemo * sizeof( Memoization ) );

        for( int i = 0; i < gnMemo; i++ )
            gaMemo[ i ].init();
    }

    // ========================================================================
    inline void memo_push( BigInt10& key )
    {
        if( giHistory > gnHistory )
            return;

        if( giMemo >= gnMemo )
        { 
            //printf( "Info: Out of Memo mem!\n" );
            return;
        }

        gaMemo[ giMemo++ ].key.clone( key );
    }
    
