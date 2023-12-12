#include <iostream>
#include <cstdlib>
#include <climits>
using namespace std;

char key = 'y'; 
bool gameover = false; 
const int Size_of_board = 3;

char board[Size_of_board][Size_of_board];

// Function to initialize the Tic Tac Toe board
void set_board() {
    for (int row = 0; row < Size_of_board; row++) {
        for (int col = 0; col < Size_of_board; col++) {
            board[row][col] = ' ';
        }
    }
}

// Sample board for demonstration of indexing of the tic tac toe 
void demo_board(){
	 int matrix[3][3];
    int count = 1;

    // Fill the matrix with numbers 1 to 9
    for (int row = 0; row < 3; row++) {
        for (int col = 0; col < 3; col++) {
            matrix[row][col] = count++;
        }
    }

    // Print the matrix
    for (int row = 0; row < 3; row++) {
        for (int col = 0; col < 3; col++) {
            cout << matrix[row][col];
            cout << " ";
            if (col < 2) {
                cout << " | ";
            }
        }
        cout << endl;
        if (row < 3) {
            cout << "-----------" << endl;
        }
    }
}
// Function to display the current Tic Tac Toe board
void display_board() {
    for (int row = 0; row < Size_of_board; row++) {
        for (int col = 0; col < Size_of_board; col++) {
            cout << board[row][col];
            cout << " ";
            if (col < Size_of_board - 1) {
                cout << " |";
            }
        }
        cout << endl;
        if (row < Size_of_board - 1) {
            cout << "-----------" << endl;
        }
    }
}

// Function to get player move input
void get_move(int& row, int& col, char player_mark) {
    if (player_mark == 'X') {
        cout << "Player 1's turn (row and column): ";
    } else {
        cout << "Player 2's turn (row and column): ";
    }

    cout << "Insert the value where you want to insert your element (1-9): ";
    int move;
    cin >> move;

    switch (move) {
        case 1:
            row = 1;
            col = 1;
            break;
        case 2:
            row = 1;
            col = 2;
            break;
        case 3:
            row = 1;
            col = 3;
            break;
        case 4:
            row = 2;
            col = 1;
            break;
        case 5:
            row = 2;
            col = 2;
            break;
        case 6:
            row = 2;
            col = 3;
            break;
        case 7:
            row = 3;
            col = 1;
            break;
        case 8:
            row = 3;
            col = 2;
            break;
        case 9:
            row = 3;
            col = 3;
            break;
        default:
            cout << "Invalid input. Please enter a number between 1 and 9." << endl;
            get_move(row, col,player_mark); // Recursive call to get a valid move
            return;
    }

    row--; // initializing base index to 0
    col--;

    if (row < 0 || row >= Size_of_board || col < 0 || col >= Size_of_board || board[row][col] != ' ') {
        cout << "Invalid move. Try again." << endl;
        get_move(row, col, player_mark);
    }
}

// Function to update the Tic Tac Toe board after a move
void update_board(int row, int col, char mark) {
    board[row][col] = mark;
}

// Function to check win conditions
int win_condition(char player_mark) {
    // checking rows
    if (board[0][0] == player_mark && board[0][1] == player_mark && board[0][2] == player_mark)
        return 1;
    if (board[1][0] == player_mark && board[1][1] == player_mark && board[1][2] == player_mark)
        return 1;
    if (board[2][0] == player_mark && board[2][1] == player_mark && board[2][2] == player_mark)
        return 1;

    // checking cols
    if (board[0][0] == player_mark && board[1][0] == player_mark && board[2][0] == player_mark)
        return 1;
    if (board[0][1] == player_mark && board[1][1] == player_mark && board[2][1] == player_mark)
        return 1;
    if (board[0][2] == player_mark && board[1][2] == player_mark && board[2][2] == player_mark)
        return 1;

    // checking diagonals
    if (board[0][0] == player_mark && board[1][1] == player_mark && board[2][2] == player_mark)
        return 1;
    if (board[0][2] == player_mark && board[1][1] == player_mark && board[2][0] == player_mark)
        return 1;

    return 0;
}

// Function to clear the console screen based on the operating system
void clear_screen() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

// Function to check if the board is full
bool is_board_full() {
    for (int i = 0; i < Size_of_board; i++) {
        for (int j = 0; j < Size_of_board; j++) {
            if (board[i][j] == ' ') {
                return false;
            }
        }
    }
    return true;
}

// Function to check if the game is over
bool is_game_over() {
    return win_condition('X') || win_condition('O') || is_board_full();
}

// Function to perform the AI move using the minimax algorithm with alpha-beta pruning
int minimax(char player_mark, int depth, int alpha, int beta) {
    if (win_condition('X')) {
        return -1;
    } else if (win_condition('O')) {
        return 1;
    } else if (is_board_full()) {
        return 0;
    }

// Maximizing the player ('O') 
    if (player_mark == 'O') {
        int max_eval = INT_MIN;
        for (int i = 0; i < Size_of_board; i++) {
            for (int j = 0; j < Size_of_board; j++) {
                if (board[i][j] == ' ') {
                    board[i][j] = player_mark;
                    int eval = minimax('X', depth + 1, alpha, beta);
                    board[i][j] = ' ';
                    max_eval = max(max_eval, eval);
                    alpha = max(alpha, eval);
                    if (beta <= alpha) {
                        break; // Beta cut-off
                    }
                }
            }
        }
        return max_eval;
    } else {
     // Minimizing player('X')   	
        int min_eval = INT_MAX;
        for (int i = 0; i < Size_of_board; i++) {
            for (int j = 0; j < Size_of_board; j++) {
                if (board[i][j] == ' ') {
                    board[i][j] = player_mark;
                    int eval = minimax('O', depth + 1, alpha, beta);
                    board[i][j] = ' ';

                    min_eval = min(min_eval, eval);
                    beta = min(beta, eval);
                    if (beta <= alpha) {
                        break; // Alpha cut-off
                    }
                }
            }
        }
        return min_eval;
    }
}

// Function to get the AI move
void get_ai_move() {
    int best_move_row = -1;
    int best_move_col = -1;
    int best_eval = INT_MIN;

    for (int i = 0; i < Size_of_board; i++) {
        for (int j = 0; j < Size_of_board; j++) {
            if (board[i][j] == ' ') {
                board[i][j] = 'O';
                int eval = minimax('X', 0, INT_MIN, INT_MAX);
                board[i][j] = ' ';

                if (eval > best_eval) {
                    best_eval = eval;
                    best_move_row = i;
                    best_move_col = j;
                }
            }
        }
    }

    board[best_move_row][best_move_col] = 'O';
}

bool ask_to_play_again() {
    char key;
    cout << "Do you want to play again? (Y/N): ";
    cin >> key;
    clear_screen();

    // Return true if the user wants to play again, false otherwise
    return (key == 'y' || key == 'Y');
}

void gameover_msg(){
	cout<<"\nGame-over.. Wanna play again\n:"; 
	cin>>key;
}

int main() {
    demo_board(); 
    cout << "\n----This is how the indexing is done in the game so choose accordingly----" << endl << endl; 
    while (key == 'y') {
        int row, col;
        char player_mark = 'X';
        set_board();
        int winner = 0; 

        cout << "Choose mode:" << endl;
        cout << "1. Multiplayer" << endl;
        cout << "2. Single Player (vs AI)" << endl;

        int mode;
        cin >> mode;

        if (mode == 1) {
            cout << endl;
            while (!gameover) {
                clear_screen();
                display_board();
                if (player_mark == 'X')
                    cout << "Player 1's turn:" << endl;
                else
                    cout << "Player 2's turn:" << endl;
                get_move(row, col, player_mark);
                update_board(row, col, player_mark);

                winner = win_condition(player_mark);
                if (winner == 1) {
                    display_board();
                    if (player_mark == 'X')
                        cout << "Player 1 won the game " << endl;
                    else
                        cout << "Player 2 won the game" << endl;

                    cout << endl << endl;

                    cout << "Do you want to play again Y/N: ";
                    cin >> key;
                    gameover = !ask_to_play_again();  
                    if (!gameover) {
                        break;  
                    }
                } else if (is_board_full()) {
                    display_board();
                    cout << "The game is a draw!" << endl;

                    cout << endl << endl;

                    cout << "Do you want to play again Y/N: ";
                    cin >> key;
                    gameover = !ask_to_play_again();  
                    if (!gameover) {
                        break;  
                    }
                }

                if (!gameover) {
                    if (player_mark == 'X')
                        player_mark = 'O';
                    else
                        player_mark = 'X';
                }
            }
            gameover_msg(); 
        } else if (mode == 2) {
            while (!gameover) {
                clear_screen();
                display_board();
                if (player_mark == 'X') {
                    cout << "Your turn:" << endl;
                    get_move(row, col, player_mark);
                    update_board(row, col, player_mark);
                } else {
                    cout << "AI's turn:" << endl;
                    get_ai_move();
                }

                winner = win_condition(player_mark);
                if (winner == 1) {
                    display_board();
                    if (player_mark == 'X')
                        cout << "You won the game " << endl;
                    else 
                        cout << "AI won the game" << endl;

                    cout << endl << endl;

                    cout << "Do you want to play again Y/N: ";
                    cin >> key;
                    gameover = !ask_to_play_again();  // Update the gameover flag
                    if (!gameover) {
                        break;  // Exit the loop if the user doesn't want to play again
                    }
                } else if (is_board_full()) {
                    display_board();
                    cout << "The game is a draw!" << endl;

                    cout << endl << endl;

                    cout << "Do you want to play again Y/N: ";
                    cin >> key;
                    gameover = !ask_to_play_again(); 
                    if (!gameover) {
                        break;  
                    }
                }
                if (!gameover) {
                    if (player_mark == 'X')
                        player_mark = 'O';
                    else
                        player_mark = 'X';
                }
            }
            gameover_msg();
        }
    }
    return 0;
}

