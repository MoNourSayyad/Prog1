/*
Compile: make memory_game
Run: ./memory_game 2 3
Compile & run: make memory_game && ./memory_game 2 3
*/

#include "../prog1lib/lib/base.h"
#include "clrscr.h"

#ifdef _WIN32
	#define WIN_TESTS true
	#define LINUX_TESTS false
#elif __linux__
	#define LINUX_TESTS true
	#define WIN_TESTS false
#else
	#define WIN_TESTS false
	#define LINUX_TESTS false
#endif

// Represents the state of the memory game.
typedef struct {
    char *cards; // array of cards, each card is one character, row-wise
    int ncards; // number of cards in array
    int rows; // number of rows of the board
    int cols; // number of columns of the board
    int points; // number of points the player has earned
    int turns; // number of card turns the player has made
} Board; 
    
// Shuffles the array.
void shuffle(char *a, int n) { //Define a void function that shuffles an array of Strings with a given length
    // a) todo: explain
 
    for (int i = n - 1; i > 0; i--) {  // Loop through the whole array backwards starting from n-1 and ending at a[1] (a[0] is the last element and cant be swapped)
        int r = rand() % (i + 1); // random number in interval [0,i] Inclduing i
        char c = a[r]; //swapping a[i] and a[r]
        a[r] = a[i];
        a[i] = c;
    }
}  // Yes If rand() % (i + 1) produces uniformly distributed integers in [0, i], then every possible permutation of the array occurs with equal probability.

// Initializes the board with shuffled cards. Empty places are represented as ' '.
// Open places are represented as the respective character, e.g., 'A'.
// Hidden places are represented as negative characters, e.g., -'A'. 
// The cards are initially hidden (negative). 
// Only initializes the elements of the cards array. Assumes that cards points to 
// an existing array and that ncards, rows, cols, points, and turns are already set.
void init_cards(Board *b) {
  // b) todo: implement

  int pairs = b->ncards / 2;
  int i = 0;
 
  for (int p = 0; p < pairs; p++){
    char symbol = 'A' + p;
    b->cards[i++] = -symbol;
    b->cards[i++] = -symbol;
  }

  while (i < b->rows * b->cols)
    b->cards[i++] = ' ';
  
  shuffle(b->cards, b->rows * b->cols);
  
  // access to board elements: b->ncards, b->cards[i], b->rows, b->cols
}

// Prints the board. Hidden cards are shown as '#'. The following shows an output example:
/*
  1 2 3 4           <-- four columns
1   # #             <-- row 1: 1st and 4th card taken, 2nd and 3rd card hidden
2 # D # #           <-- row 2: 2nd card open
3 # # A #           <-- row 3: 3rd card open
1 points, 2 turns   <-- the player got 1 point in 2 turns
*/
// The row and column numbers are printed to facilitate input.
void print_board(Board *b) {
  // c) todo: implement

  printf("  ");

  for (int c = 0; c < b->cols; c++) {  
        printf("%d ", c + 1);
    }
  printf("\n");  

  for (int r = 0; r < b->rows; r++) {
    printf("%d ", r + 1);

      for (int c = 0; c < b->cols; c++) {
        int i = r * b->cols + c;
        char card = b->cards[i];
        if (card == ' ') {
          printf("  ");          
        } else if (card < 0) {
          printf("# ");         
        } else {
          printf("%c ", card);   
        }
      }
  printf("\n");
  }
  printf("%d points, %d turns\n", b->points, b->turns);
  // access to board elements: b->ncards, b->cards[i], b->rows, b->cols
}

// Returns the array index of row r, column c. Stops the program if r or c are not valid.
int array_index(Board *b, int r, int c) {
    // d) todo: implement

    if (r < 0 || r >= b->rows || c < 0 || c >= b->cols) {
        exit(1);
    }
    return r * b->cols + c;
    // access to board elements: b->rows, b->cols
}

// Gets value at row r, column c. Stops the program if r or c are not valid.
char get(Board *b, int r, int c) {
  // e) todo: implement

  int i = array_index(b, r, c);
  return b->cards[i];
  
}

// Sets value at row r, column c to x. Stops the program if r or c are not valid.

void set(Board *b, int r, int c, char x) {
  // e) todo: implement

  int i = array_index(b, r, c);
  b->cards[i] = x;
}

// Turns over card in row r, column c. Stops the program if r or c are not valid.

void turn(Board *b, int r, int c) {
    // e) todo: implement

  int i = array_index(b, r, c);
  if (b->cards[i] != ' ') {
    b->cards[i] = -b->cards[i];
  }
}

// Prints a prompt to wait and wait for return key.
void prompt(void) {
    printf("press <return> to continue\n");
    char line[8];
    get_line(line, 8);
}

// Gets user input of the form <row-digit><column-digit> to let the user specify
// the row and column of a card. Example: Input 13 specifies row 0, column 2.
// Because the function returns three values, row and col are pointers to int
// variables to be set by the function. The return value indicates whether the
// position is valid (true) or not (false), given the current board state.
bool read_coords(/*IN*/Board *b, /*OUT*/int *row, /*OUT*/int *col) {
    char line[8];
    get_line(line, 8); // read input from terminal into line array
    int r = line[0] - '1'; // input '1' corresponds to row 0, '2' --> 1, etc.
    int c = line[1] - '1';
    if (r < 0 || r >= b->rows || c < 0 || c >= b->cols || get(b, r, c) == ' ') {
        return false; // position not valid
    }
    *row = r;
    *col = c;
    return true; // position valid
}

// Restricts x to the interval [low, high].
int clamp(int x, int low, int high) {

    // f) todo: implement
    if (x < low) return low;
    if (x > high) return high;
    return x;
}

// Does a single move. It consists of turning over two cards. If they are equal, 
// they get removed from the board and a point for the collected pair is given 
// to the player. Otherwise, they are turned over again (backside up).
// The input format is: 12<return> to open a card in row 0, column 1.
void do_move(Board *b) { // g) todo: explain  // I would say it is mainly robust, because for read_coords we check for negative rows/cols and cols/rows less than the original.
    int r1, c1;         // We also check everything again in print_board and we check whether cards are equal or not in 197, in order to avoid errors. But one thing's annoying: The prog crashes after the assert, if both cards are pos.
    while (!read_coords(b, &r1, &c1)) {  // Checks the rows and columns move for errors and illegal moves.
        printf("Illegal move.\n");
    }
    turn(b, r1, c1); //Turns the cards. Pos to Neg and vice-versa.
    b->turns++;
    clear_screen();
    print_board(b);

    int r2, c2;
    while (!read_coords(b, &r2, &c2) || (r1 == r2 && c1 == c2)) { //Same logic but the first move mustn't be the same as the first one too.
        printf("Illegal move.\n");
    }
    turn(b, r2, c2);  // Same logic as above.
    b->turns++;
    clear_screen();
    print_board(b);

    prompt(); // Waits for <return> to flip cards.
    char card1 = get(b, r1, c1);
    char card2 = get(b, r2, c2); // Comparison of both.
    assert("Illegal action.\n", card1 > 0 && card2 > 0);
    if (card1 == card2) { //Corect pair -> points increases, and they're set empty now.
        b->points++;
        set(b, r1, c1, ' ');
        set(b, r2, c2, ' ');
    } else {
        turn(b, r1, c1); // Else same state as before.
        turn(b, r2, c2);
    }
    clear_screen();
    print_board(b);  //Update board.
}   

// Tests.
void tests(void) {
    test_equal_i(clamp(1, 2, 4), 2);
    test_equal_i(clamp(2, 2, 4), 2);
    test_equal_i(clamp(3, 2, 4), 3);
    test_equal_i(clamp(4, 2, 4), 4);
    test_equal_i(clamp(5, 2, 4), 4);
    
    // test with a 3x4 board (3 rows, 4 columns)
    char a[3*4];
    Board b = { a, 12, 3, 4, 10, 20 };
    srand(123); // initialize random number generator to fixed seed to always get the same test numbers
    init_cards(&b);
    
    print_board(&b); // ensure that output is equal to testsout1_want.txt

    test_equal_i(array_index(&b, 0, 0), 0);
    test_equal_i(array_index(&b, 0, 1), 1);
    test_equal_i(array_index(&b, 0, 2), 2);
    test_equal_i(array_index(&b, 1, 0), 4);
    test_equal_i(array_index(&b, 1, 1), 5);
    test_equal_i(array_index(&b, 2, 0), 8);
    test_equal_i(array_index(&b, 2, 1), 9);

	if(WIN_TESTS){
		test_equal_i(get(&b, 0, 0), -67);
		test_equal_i(get(&b, 0, 1), -70);
		test_equal_i(get(&b, 0, 2), -66);
		test_equal_i(get(&b, 1, 0), -68);
		test_equal_i(get(&b, 1, 1), -69);
		test_equal_i(get(&b, 2, 0), -65);
		test_equal_i(get(&b, 2, 1), -67);
	}else if(LINUX_TESTS){
		test_equal_i(get(&b, 0, 0), -67);
		test_equal_i(get(&b, 0, 1), -68);
		test_equal_i(get(&b, 0, 2), -65);
		test_equal_i(get(&b, 1, 0), -66);
		test_equal_i(get(&b, 1, 1), -70);
		test_equal_i(get(&b, 2, 0), -69);
		test_equal_i(get(&b, 2, 1), -66);
	}else{
	    test_equal_i(get(&b, 0, 0), -66);
		test_equal_i(get(&b, 0, 1), -68);
		test_equal_i(get(&b, 0, 2), -67);
		test_equal_i(get(&b, 1, 0), -66);
		test_equal_i(get(&b, 1, 1), -70);
		test_equal_i(get(&b, 2, 0), -65);
		test_equal_i(get(&b, 2, 1), -67);
	}

    turn(&b, 0, 0);
    turn(&b, 0, 2);
    turn(&b, 1, 0);
    turn(&b, 2, 1);
    
    if(WIN_TESTS){
		test_equal_i(get(&b, 0, 0), 67);
		test_equal_i(get(&b, 0, 2), 66);
		test_equal_i(get(&b, 1, 0), 68);
		test_equal_i(get(&b, 2, 1), 67);
	}else if(LINUX_TESTS){
		test_equal_i(get(&b, 0, 0), 67);
		test_equal_i(get(&b, 0, 2), 65);
		test_equal_i(get(&b, 1, 0), 66);
		test_equal_i(get(&b, 2, 1), 66);
	}else{
		test_equal_i(get(&b, 0, 0), 66);
		test_equal_i(get(&b, 0, 2), 67);
		test_equal_i(get(&b, 1, 0), 66);
		test_equal_i(get(&b, 2, 1), 67);
	}

    print_board(&b); // ensure that output is equal to testsout2_want.txt or if you use Windows that output is equal to testsout2_want_WIN.txt or if you use Linux that output is equal to testsout2_want_LINUX.txt

    set(&b, 0, 0, '1');
    set(&b, 0, 2, '2');
    set(&b, 1, 0, '3');
    set(&b, 2, 1, '4');
    
    test_equal_i(get(&b, 0, 0), '1');
    test_equal_i(get(&b, 0, 2), '2');
    test_equal_i(get(&b, 1, 0), '3');
    test_equal_i(get(&b, 2, 1), '4');

    print_board(&b); // ensure that output is equal to testsout3_want.txt

    srand(time(NULL) << 10);
}

// Entry point with command line arguments.
int main(int argc, String argv[]) {
    if (argc != 3) {
        printf("Usage: memory_game <rows> <cols>\n");
        printf("Example: memory_game 2 3\n");
        exit(1);
    }
    
    tests(); 
    prompt();
    
    Board b;
    b.rows = clamp(atoi(argv[1]), 2, 9); // atoi converts strings to integers (if possible)
    b.cols = clamp(atoi(argv[2]), 2, 9);
    printf("creating a memory board with %d rows and %d cols\n", b.rows, b.cols); 
    int pairs = b.rows * b.cols / 2;
    printf("%d pairs\n", pairs);
    b.ncards = 2 * pairs;
    printf("%d cards\n", b.ncards);
    char cards[b.ncards];
    b.cards = cards;
    b.points = 0;
    b.turns = 0;
    init_cards(&b);

    clear_screen();
    print_board(&b);
    while (2 * b.points < b.ncards) {
        do_move(&b);
    }
    
    return 0;
}

/*
Example sequence:
-----------------

  1 2 3
1 # # #
2 # # #
0 points, 0 turns
11

  1 2 3
1 B # #
2 # # #
0 points, 1 turns
12

  1 2 3
1 B C #
2 # # #
0 points, 2 turns
press <return> to continue

  1 2 3
1 # # #
2 # # #
0 points, 2 turns
21

  1 2 3
1 # # #
2 A # #
0 points, 3 turns
22

  1 2 3
1 # # #
2 A C #
0 points, 4 turns
press <return> to continue

  1 2 3
1 # # #
2 # # #
0 points, 4 turns
12

  1 2 3
1 # C #
2 # # #
0 points, 5 turns
22

  1 2 3
1 # C #
2 # C #
0 points, 6 turns
press <return> to continue

  1 2 3
1 #   #
2 #   #
1 points, 6 turns
23

  1 2 3
1 #   #
2 #   A
1 points, 7 turns
21

  1 2 3
1 #   #
2 A   A
1 points, 8 turns
press <return> to continue

  1 2 3
1 #   #
2      
2 points, 8 turns
11

  1 2 3
1 B   #
2      
2 points, 9 turns
13

  1 2 3
1 B   B
2      
2 points, 10 turns
press <return> to continue

  1 2 3
1      
2      
3 points, 10 turns
*/