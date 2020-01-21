#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 3

int isInputValid(int, int, int);
int isBoardFull(char [N][N]);
void createInitialBoard(char [N][N]);
void readUserMove(int *, int *);
void printCurrentBoard(char[N][N]);
int getComputerMove(char [N][N], int *, int *, int, int);
int gameWon(char [N][N], char);
int computerPlaysToWin(char [N][N], int * , int * );
void computerPlaysRandom(int * , int * , int , int );
void sumAllDimensions(char [N][N], int [N], int [N], int *, int *);
int memberOf(int , int [N]);
int computerPlaysToBlock(char [N][N], int * , int * );

int main(){

   int userRow, userCol, computerRow, computerCol;
   int taken;
   char board[N][N];
   char winner = 'N';

   srand(time(NULL));

   printf("This tic-tac-toe board is of size %d by %d\n", N, N);

   printf("Player symbol: X \nComputer symbol: O\n\n");

   printf("Here is the board - spaces are indicated by a ?\n");

   createInitialBoard(board);			// create a 3 X 3 board with '?' in each cell

   while ((winner != 'Y') && !(isBoardFull(board))) // while there is no winner and the board is not full
   {
	   taken = 0;

		while (!(taken))                  // loop used to accept valid row and col values from the user
		{
			readUserMove(&userRow, &userCol);                  //get user's move
			printf("You chose row %d and column %d \n", userRow, userCol);

			while (!isInputValid(userRow, 1, N) || !isInputValid(userCol, 1, N))     // validate user's move
			{
				printf("That's is an invalid row or column number - try again\n");
				readUserMove(&userRow, &userCol);
				printf("You chose row %d and column %d \n", userRow, userCol);
			}

			if (board[userRow-1][userCol-1] == '?')           // if cell is unoccupied
			{
				board[userRow-1][userCol-1] = 'X';			// store an X there
				taken = 1;
			}
			else
			{
				taken = 0;									// otherwise inform the user to enter values again
				printf("That spot is taken - please try another one\n");
			}

		} //end of while (!taken)

	   if (gameWon(board, 'X'))   // check if the user wins - game will end if the user does win
	   {
		   printf("Congrats - you won against the computer :)\n");
		   winner = 'Y';
	   }

	   else  if (!(isBoardFull(board)))            //check if the board is already full
	   {
		   taken = 0;

		   while (!(taken))
		   {
				getComputerMove(board, &computerRow, &computerCol, userRow-1, userCol-1); // get computer's row and col

				if (board[computerRow][computerCol] == '?')         // check if the cell is unoccupied
				{
					board[computerRow][computerCol] = 'O';
					taken = 1;

				}
				else
				{
					taken = 0;		//That spot is taken - computer - try another one
				}
		   }

		   printf("Computer chose row %d and column %d \n", computerRow+1, computerCol+1);

		   if (gameWon(board, 'O'))               // check if the computer wins - game must end if it does
		   {
			   printf("Oh the computer won this time :(( think hard next time\n");
			   winner = 'Y';
		   }
	   }

	printCurrentBoard(board);

	printf("\nPress enter to continue \n");
	getchar();

   } //end of while

   if (winner != 'Y')
			printf("Game was a tie - no winner!\n\n");

   return 0;
}


int  getComputerMove(char board[N][N], int * computerRow, int * computerCol, int userRow, int userCol){
/*
  This function determines computer's move in terms of row (computerRow) and column (computerCol)
  and outputs them to main. The computer first tries to find a winning spot for itself; if it doesn't
  find one, then it calls function computerPlaysRandom in its attempt to place its symbol in
  the same row or column as the user (userRow, userCol)
*/

    int winningSpot = 0;
   int blocked = 1;

   winningSpot = computerPlaysToWin(board, computerRow, computerCol);

   if (!winningSpot)            // if computer does find a winning spot, then it plays to block the user
   {
	   computerPlaysRandom(computerRow, computerCol, userRow, userCol);

	   blocked = computerPlaysToBlock(board, computerRow, computerCol);
	   if (blocked == 0)
		   computerPlaysRandom(computerRow, computerCol, userRow, userCol);
   }

   return winningSpot;
}
//The blank tic tac toe board
void createInitialBoard(char boards[N][N]) {
    int i, j;
    for (i = 0; i < N; i++) { //assigns all cells with '?'
        for (j = 0; j < N; j++) {
            boards[i][j] = '?';
        }
    }
    printf(" %c | %c | %c\n", boards[0][0], boards[0][1], boards[0][2]); //prints the board
    printf("-----------\n");
    printf(" %c | %c | %c\n", boards[1][0], boards[1][1], boards[1][2]);
    printf("-----------\n");
    printf(" %c | %c | %c\n", boards[2][0], boards[2][1], boards[2][2]);
}
//Checks if the board is full and has no '?' in any cells if it does the board is still has room
int isBoardFull(char board[N][N]) {
    int i, j;

    for(i = 0; i < N; i++) { //checks through each cell for the '?' blanks
        for(j = 0; j < N; j++) {
            if(board[i][j] == '?') {
                return 0; //returns 0 indicating board has room
            }
        }
    }
    return 1;
}
//player move is taken here
void readUserMove(int* row, int* column) {
    printf("Your move - enter numbers between 1 and 3\n\n"); //prompts user to enter the parameters
    printf("Enter row number: ");//user is prompted to enter row desired
    scanf("%d", row);
    printf("Enter column number: "); //user is prompted to enter column desired
    scanf("%d", column);
}
//Checks if user's input is within the parameters
int isInputValid(int entered, int minimum, int maximum) {
    int limit;
    if(entered >= minimum && entered <= maximum) { //if it is selected from 1 to 3
        limit = 1; //returns 1 indicating it is within parameters
    }
    else {
        limit = 0; //returns 0 indicating it is not within parameters
    }
    return limit;
}
//prints the current state of the board
void printCurrentBoard(char boards[N][N]) {
    printf(" %c | %c | %c\n", boards[0][0], boards[0][1], boards[0][2]);
    printf("-----------\n");
    printf(" %c | %c | %c\n", boards[1][0], boards[1][1], boards[1][2]);
    printf("-----------\n");
    printf(" %c | %c | %c\n", boards[2][0], boards[2][1], boards[2][2]);
}
//checks if there is a winner on each turn made
int gameWon(char board[N][N], char symbol) {
    int sumRD = 0;
    int sumLD = 0;
    int sumR[N] = {0, 0, 0};
    int sumC[N] = {0, 0, 0};
    sumAllDimensions(board, sumR, sumC, &sumLD, &sumRD); //finds the sum of each row

    if (symbol == 'X') { //checks if user on in the rows and returns 1
        if (memberOf(3, sumR) == 1) {
            return 1;
        }
        else if (memberOf(3, sumC) == 1) {
            return 1;
        }
        else if (sumLD == 3 || sumRD == 3) {
            return 1;
        }
    }

    if (symbol == 'O') { //checks if the computer won in the rows and returns 1
        if (memberOf(12, sumR) == 1) {
            return 1;
        }
        else if (memberOf(12, sumC) == 1) {
            return 1;
        }
        else if (sumLD == 12 || sumRD == 12) {
            return 1;
        }
    }
    return 0; //returns 0 if there was no one who won to continue game
}
//finds the sum of each row and column to indicate game won that there is a winner each 'X' is 1 and each 'O' is 4 so that they will not interfere with each other
void sumAllDimensions(char board[N][N], int sumR[N], int sumC[N], int* sumLD, int* sumRD) {
    int i, j;
    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) { //checks each rows and adds the value by the corresponding value in each cell
            if (board[i][j] == 'O') {
                sumR[i] = sumR[i] + 4;
            }
            else if (board[i][j] == 'X') {
                sumR[i] = sumR[i] + 1;
            }

        }
    }
    for (i = 0; i < N; i++) {//checks each columns and adds the value by the corresponding value in each cell
        for (j = 0; j < N; j++) {
            if (board[j][i] == 'O') {
                sumC[i] = sumC[i] + 4;
            }
            else if (board[j][i] == 'X') {
                sumC[i] = sumC[i] + 1;
            }
        }
    }
    for (i = 0; i < N; i++) {//checks the left diagonal and adds the value by the corresponding value in each cell
        if (board[i][i] == 'O') {
            *sumLD = *sumLD + 4;
        }
        else if (board[i][i] == 'X') {
            *sumLD = *sumLD + 1;
        }
    }
    for (i = 0; i < N; i++) {//checks the right diagonal and adds the value by the corresponding value in each cell
            if (board[i][2 - i] == 'O') {
                *sumRD = *sumRD + 4;
            }
            if (board[i][2 - i] == 'X') {
                *sumRD = *sumRD + 1;
            }
    }
}
//if computer has an opportunity to win on it's turn this function will make it win
int computerPlaysToWin(char board[N][N], int* cRow, int* cCol) {
    int sumRD = 0;
    int sumLD = 0;
    int sumR[N] = {0, 0, 0};
    int sumC[N] = {0, 0, 0};
    int i, j;
    sumAllDimensions(board, sumR, sumC, &sumLD, &sumRD);

    if (memberOf(8, sumR) == 1) {//if the sum of the rows is 8 as indicated by function of memberOf then there is a winning potential in the rows
        for (i = 0; i < N; i++) {
            if (sumR[i] == 8) {
                for (j = 0; j < N; j++) {
                    if (board[i][j] == '?') {
                        *cRow = i;
                        *cCol = j;
                        return 1;//return the coordinates of the cell of the blank
                    }
                }
            }
        }
    }
    else if (memberOf(8, sumC) == 1) {//if the sum of the columns is 8 as indicated by function of memberOf then there is a winning potential in the columns
        for (i = 0; i < N; i++) {
            if (sumC[i] == 8) {
                for (j = 0; j < N; j++) {
                    if (board[j][i] == '?') {
                        *cRow = j;
                        *cCol = i;
                        return 1;
                    }
                }
            }
        }
    }

    else if (sumLD == 8) {//if the sum of the left diagonal is 8 as indicated by function of memberOf then there is a winning potential in the left diagonal
        for (i = 0; i < N; i++) {
            if (board[i][i] == '?') {
                *cRow = i;
                *cCol = i;
                return 1;
            }
        }

    }

    else if (sumRD == 8) {//if the sum of the right diagonal is 8 as indicated by function of memberOf then there is a winning potential in the right diagonal
        for (i = 0; i < N; i++) {
            if (board[i][2 - i] == '?') {
                *cRow = i;
                *cCol = 2 - i;
                return 1;
            }
        }
    }
    return 0;
}
//computer will choose a random cell where it will place it's 'O' in the same lines as the users 'X'
void computerPlaysRandom(int* cRow, int* cCol, int uRow, int uCol) {
    int option = rand() % 4;
    int LD = rand() % 3;

    if (uCol == 1 && uRow == 0) { //if the user enters in the middle sides of the board this will execute to make sure computer is on the same lines as it
        option = rand() % 2;
    }
    else if ((uCol == 0 || uCol == 2) && uRow == 1) {
        option = rand() % 2;
    }
    else if (uCol == 1 && uRow == 2) {
        option = rand() % 2;
    }
    else {
        option = rand() % 4;
    }

    if (option == 0) {
        *cRow = uRow;
        *cCol = rand() % 3;
    }
    else if (option == 1) {
        *cRow = rand() % 3;
        *cCol = uCol;
    }
    else if (option == 2) {
        *cRow = LD;
        *cCol = *cRow;
    }

    else if (option == 3) {
        if (LD == 0) {
            *cRow = 0;
            *cCol = 2;
        }

        else if (LD == 1) {
            *cRow = 1;
            *cCol = 1;
        }
        else if (LD == 2) {
            *cRow = 2;
            *cCol = 0;
        }
    }
}
//see if the number at the array will equal the number desired
int memberOf(int aNum, int someArray[N]) {
    int i, match;

    for(i = 0; i < N; i++) { //if the numbers match then it returns 1 stating that it is true
        if (someArray[i] == aNum) {
            match = 1;
        }
    }
    return match;
}
//BONUS: computer will block player if player can win
int computerPlaysToBlock (char board[N][N], int * cRow, int * cCol) {
    int i, j;
    int sumRD = 0;
    int sumLD = 0;
    int sumR[N] = {0, 0, 0};
    int sumC[N] = {0, 0, 0};

    sumAllDimensions(board, sumR, sumC, &sumLD, &sumRD);

    if (memberOf(2, sumR) == 1) { //checks if player is about to win in the rows and if so it will find the last '?' and take the spot
        for (i = 0; i < N; i++) {
            if (sumR[i] == 2) {
                for (j = 0; j < N; j++) {
                    if (board[i][j] == '?') {
                        *cCol = j;
                        *cRow = i;
                        return 1;
                    }
                }
            }
        }
    }
    else if (memberOf(2, sumC) == 1) { //checks the rows if player is about to win
        for (i = 0; i < N; i++) {
            if (sumC[i] == 2) {
                for (j = 0; j < N; j++) {
                    if (board[j][i] == '?') {
                        *cCol = i;
                        *cRow = j;
                        return 1;
                    }
                }
            }
        }
    }
    else if (sumRD == 2) { //checks the right diagonal if plater is about to win
        for (i = 0; i < N; i++) {
            if (board[i][2 - i] == '?') {
                *cCol = 2 - i;
                *cRow = i;
                return 1;
            }
        }
    }
    else if (sumLD == 2) { //checks the left diagonal if the player is about to win
        for (i = 0; i < N; i++) {
            if (board[i][i] == '?') {
                *cCol = i;
                *cRow = i;
                return 1;
            }
        }
    }
    return 0; //returns 0 if player is not going to win
}
