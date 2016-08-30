/**
 * fifteen.c
 *
 * Computer Science 50
 * Problem Set 3
 *
 * Implements Game of Fifteen (generalized to d x d).
 *
 * Usage: fifteen d
 *
 * whereby the board's dimensions are to be d x d,
 * where d must be in [DIM_MIN,DIM_MAX]
 *
 * Note that usleep is obsolete, but it offers more granularity than
 * sleep and is simpler to use than nanosleep; `man usleep` for more.
 */
 
#define _XOPEN_SOURCE 500

#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

// constants
#define DIM_MIN 3
#define DIM_MAX 9

// board
int board[DIM_MAX][DIM_MAX];

// dimensions
int d;

// blank tile location
int blankRow;
int blankCol;

// prototypes
void clear(void);
void greet(void);
void init(void);
void draw(void);
bool move(int tile);
bool won(void);

int main(int argc, string argv[])
{
    // ensure proper usage
    if (argc != 2)
    {
        printf("Usage: fifteen d\n");
        return 1;
    }

    // ensure valid dimensions
    d = atoi(argv[1]);
    if (d < DIM_MIN || d > DIM_MAX)
    {
        printf("Board must be between %i x %i and %i x %i, inclusive.\n",
            DIM_MIN, DIM_MIN, DIM_MAX, DIM_MAX);
        return 2;
    }

    // open log
    FILE* file = fopen("log.txt", "w");
    if (file == NULL)
    {
        return 3;
    }

    // greet user with instructions
    greet();

    // initialize the board
    init();

    // accept moves until game is won
    while (true)
    {
        // clear the screen
        clear();

        // draw the current state of the board
        draw();

        // log the current state of the board (for testing)
        for (int i = 0; i < d; i++)
        {
            for (int j = 0; j < d; j++)
            {
                fprintf(file, "%i", board[i][j]);
                if (j < d - 1)
                {
                    fprintf(file, "|");
                }
            }
            fprintf(file, "\n");
        }
        fflush(file);

        // check for win
        if (won())
        {
            printf("ftw!\n");
            break;
        }

        // prompt for move
        printf("Tile to move: ");
        int tile = GetInt();
        
        // quit if user inputs 0 (for testing)
        if (tile == 0)
        {
            break;
        }

        // log move (for testing)
        fprintf(file, "%i\n", tile);
        fflush(file);

        // move if possible, else report illegality
        if (!move(tile))
        {
            printf("\nIllegal move.\n");
            usleep(50000);
        }

        // sleep thread for animation's sake
        usleep(50000);
    }
    
    // close log
    fclose(file);

    // success
    return 0;
}

/**
 * Clears screen using ANSI escape sequences.
 */
void clear(void)
{
    printf("\033[2J");
    printf("\033[%d;%dH", 0, 0);
}

/**
 * Greets player.
 */
void greet(void)
{
    clear();
    printf("WELCOME TO GAME OF FIFTEEN\n");
    usleep(500000);
}

/**
 * Initializes the game's board with tiles numbered 1 through d*d - 1
 * (i.e., fills 2D array with values but does not actually print them).  
 */
void init(void)
{
    /* init - Initialize game board
    
    Date: 08-19-2016
    Name: Sean M Hamlet
    */
    
    int nTiles = d * d - 1;
    bool nTilesOdd = nTiles % 2 != 0;
    int filler = nTiles;
    
    // fill game board with tiles
    for (int r = 0; r < d; r++)
    {
        for (int c = 0; c < d; c++)
        {
            board[r][c] = filler;
            filler -= 1;
        }
    }
    
    // swap locations of 1 and 2 if odd number of tiles
    if (nTilesOdd)
    {
        // swap locations of 1 and 2
        board[d - 1][d - 3] = 1;
        board[d - 1][d - 2] = 2;
    }
    
    // initialize position of blankTile
    blankRow = d - 1;
    blankCol = d - 1;
}

/**
 * Prints the board in its current state.
 */
void draw(void)
{
    /* draw - Draws game board on screen
    
    Date: 08-19-2016
    Name: Sean M Hamlet
    */
    
    // print new line before board
    printf("\n");
    
    // print out game board
    for (int r = 0; r < d; r++)
    {
        // print 2 spaces to left of board
        printf("  ");
        for (int c = 0; c < d; c++)
        {
            // print "blank space" as underscore
            if (board[r][c] == 0)
            {
                printf(" _ ");
            } else
            {
                printf("%2d ", board[r][c]);
            }
            
        }
        printf("\n\n");
    }
}

/**
 * If tile borders empty space, moves tile and returns true, else
 * returns false. 
 */
bool move(int tile)
{
    /* move - Moves tile if valid move
    
    INPUTS
        tile:       int scalar, Tile number to check and move
        
    OUTPUTS
        validMove:  bool, Value to return if move was valid and thus occured
    
    Date: 08-19-2016
    Name: Sean M Hamlet
    */
    
    // initialize tile position as -1 and validMove as false
    int tileRow = -1;
    int tileCol = -1;
    
    bool validMove = false;
    
    // declare valid zero positions if within board dimensions
    bool blankBelow;
    bool blankRight;
    bool blankAbove;
    bool blankLeft;
    
    // find tile position
    for (int r = 0; r < d; r++)
    {
        for (int c = 0; c < d; c++)
        {
            if (board[r][c] == tile)
            {
                tileRow = r;
                tileCol = c;
            }
        }
    }
    
    // define valid zero positions if within board dimensions
    blankBelow = tileRow + 1 == blankRow & tileCol == blankCol;
    blankRight = tileRow == blankRow & tileCol + 1 == blankCol;
    blankAbove = tileRow - 1 == blankRow & tileCol == blankCol;
    blankLeft  = tileRow == blankRow & tileCol - 1 == blankCol;
    
    // return false if tile position off of board
    if (tileRow == -1 | tileCol == -1 | tileRow > d | tileCol > d)
    {
        return false;
        // check if valid blank position with respect to tile position        
    } else if (blankBelow | blankAbove | blankRight | blankLeft)
    {
        validMove = true;
    }
    
    // if valid move, switch position of blank and tile
    if (validMove)
    {
        board[blankRow][blankCol] = tile;
        blankRow = tileRow;
        blankCol = tileCol;
        board[tileRow][tileCol] = 0;
    }
    
    return validMove;
}

/**
 * Returns true if game is won (i.e., board is in winning configuration), 
 * else false.
 */
bool won(void)
{
    /* won - Checks if game is won
    
        For winning configuration, tiles should be in ascending order.
        
    OUTPUTS
        bool:  bool, True if won, False if not won
    
    Date: 08-19-2016
    Name: Sean M Hamlet
    */
    
    // counter variable to check tiles against
    int winCheck = 1;
    
    // check each tile
    for (int r = 0; r < d; r++)
    {
        for (int c = 0; c < d; c++)
        {
            if (r == d - 1 & c == d - 1)
            {
                if (board[r][c] != 0)
                {
                    return false;
                }
            } else if (board[r][c] != winCheck)
            {
                return false;
            }
            winCheck++;
        }
    }
    return true;
}