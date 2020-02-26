#include "stdio.h"
#include "stdlib.h"
#include "math.h"


int WHOWON = 0; //0 for player 1, 1 for player2, 2 for a tie
void printBoard(char** baord, int length);
int bounds(char** board, int length, int x, int y); //0 if out of bounds 1 otherwise

int getX(char coordinates[]);
int getY(char coordinate[]);

void placeWhite(char** board, int length, int x, int y);
void placeBlack(char** board, int length, int x, int y);
int adjacent(char** board, int length, int a, int b, int x, int y);//1 if adj and 0 if not
void play(char** board, int length, int whoseTurn); //player1 is 0 and player2 is 1
int spotsFilled(char** board, int length, int x, int y); //big funtion 1 if all filled 0 otherwise
int spotEmpty(char** board, int length, int x, int y); //1 if filled 0 otherwise
int rowCheck(char** board, int length, char player);
int columnCheck(char**board, int length, char player);
int diagonalCheck(char** board, int length, char player);
void testPrintBoard(char** board, int length);



int main() {

	char** arr;
	int boardlength = 10;

	arr = malloc(boardlength * sizeof(char*));

	for (int i = 0; i < boardlength; i++) {
		arr[i] = malloc(boardlength * sizeof(char));

		for (int j = 0; j < boardlength; j++)
			arr[i][j] = ' ';
	}

	int playerBet = 0;
	printf("Please bet on either Player 1 or Player 2. Enter 0 to bet on player 1, 1 to bet on player 2, and 2 to bet for a tie: ");
	scanf("%d", &playerBet);

	printf("\n\n");

	printBoard(arr, boardlength);

	play(arr, boardlength, 0);

	if (WHOWON == playerBet){
		printf("You won your bet.\n");
	}
	else{
		printf("You lost your bet\n");
	}

/*
	testPrintBoard(arr, boardlength);

	int totalWhiteScore = rowCheck(arr, boardlength, 'W') + columnCheck(arr, boardlength, 'W') + diagonalCheck(arr, boardlength, 'W');
	int totalBlackScore = rowCheck(arr, boardlength, 'B') + columnCheck(arr, boardlength, 'B') + diagonalCheck(arr, boardlength, 'B');
	printf("%d\n", totalWhiteScore);
	printf("%d\n", totalBlackScore);
	if (totalWhiteScore > totalBlackScore) {
		printf("Player1 WON!!!\n");
	}
	else if (totalBlackScore > totalWhiteScore) {
		printf("Player2 WON!!!\n");
	}
	else {
		printf("You both tie!");
	}
*/

	int i = 0;
	scanf("%d", &i);


	return 0;


}

void printBoard(char** board, int length) {

	for (int i = length - 1; i >= 0; i--) {
		for (int j = 0; j < length; j++) {
			if (j == 0) {
				printf("%d |%c", i, board[j][i]);
			}
			else if (j == length - 1) {
				printf("|%c|", board[j][i]);
			}
			else {
				printf("|%c", board[j][i]);
			}
		}
		printf("\n");
	}
	for (int i = 0; i < length; i++) {
		if (i == 0) {
			printf("   %c ", i + 'A');
		}
		else if (i == 9) {
			printf("%c\n", i + 'A');
		}
		else {
			printf("%c ", i + 'A');
		}
	}
	printf("\n");
}

int bounds(char** board, int length, int x, int y) { //0 out of bounds
	if (x < 0 || x >= length || y < 0 || y >= length) {
		return 0;
	}
	else {
		return 1;
	}
}

int getX(char coordinate[]) {
	return coordinate[0] - 'A';
}

int getY(char coordinate[]) {
	char* i = &coordinate[1];
	int y = atoi(i);
	return y;
}

void placeWhite(char** board, int length, int x, int y) {
	board[x][y] = 'W';
}

void placeBlack(char** board, int length, int x, int y) {
	board[x][y] = 'B';
}

int adjacent(char** board, int length, int x, int y, int a, int b) { //if (a,b) is adjacent to (x,y)

	if ((abs(x - a) + (abs(y - b)) == 1)) { //vertical and horizontal
		return 1;
	}
	else if ((abs(x - a) == 1) && (abs(y - b) == 1)) { //diagonal test
		return 1;
	}
	else {
		return 0;
	}

}

int spotsFilled(char** board, int length, int x, int y) { // 1 if all spots are filled 0 otherwise

	if (x != 0 && y != 0 && x != length - 1 && y != length - 1) {
		if (board[x + 1][y] != ' ' && board[x - 1][y] != ' ' && board[x][y + 1] != ' ' && board[x][y - 1] != ' ' &&
			board[x + 1][y + 1] != ' ' && board[x - 1][y - 1] != ' ' && board[x - 1][y + 1] && board[x + 1][y - 1] != ' ') {
			return 1;
		}
		else {
			return 0;
		}
	}
	else if (x == 0 || y == 0 || x == length - 1 || y == length - 1) {
		if (x == 0 && y == 0) {
			if (board[x + 1][y] != ' '  && board[x][y + 1] != ' ' && board[x + 1][y + 1] != ' ') {
				return 1;
			}
			else {
				return 0;
			}
		}
		else if (x == length - 1 && y == length - 1) {
			if (board[x - 1][y] != ' '  && board[x][y - 1] != ' '  && board[x - 1][y - 1] != ' ') {
				return 1;
			}
			else {
				return 0;
			}
		}
		else if (x == 0 && y == length - 1) {
			if (board[x + 1][y] != ' '   && board[x][y - 1] != ' ' && board[x + 1][y - 1] != ' ') {
				return 1;
			}
			else {
				return 0;
			}
		}
		else if (x == length - 1 && y == 0) {
			if (board[x - 1][y] != ' ' && board[x][y + 1] != ' ' && board[x - 1][y + 1] != ' ') {
				return 1;
			}
			else {
				return 0;
			}
		}
		if (x == 0 && y != 0 && y != length - 1) {
			if (board[x + 1][y] != ' ' &&  board[x][y + 1] != ' ' && board[x][y - 1] != ' ' &&
				board[x + 1][y + 1] != ' ' && board[x + 1][y - 1] != ' ') {
				return 1;
			}
			else {
				return 0;
			}
		}
		else if (x == length - 1 && y != length - 1 && y != 0) {
			if (board[x - 1][y] != ' ' && board[x][y + 1] != ' ' && board[x][y - 1] != ' '  && board[x - 1][y - 1] != ' '&&
				board[x - 1][y + 1]) {
				return 1;
			}
			else {
				return 0;
			}
		}
		else if (x != 0 && x != length - 1 && y == length - 1) {
			if (board[x + 1][y] != ' ' && board[x - 1][y] != ' '  && board[x][y - 1] != ' ' &&
				board[x - 1][y - 1] != ' '  && board[x + 1][y - 1] != ' ') {
				return 1;
			}
			else {
				return 0;
			}
		}
		else if (x != length - 1 && x != 0 && y == 0) {
			if (board[x + 1][y] != ' ' && board[x - 1][y] != ' ' && board[x][y + 1] != ' ' &&
				board[x + 1][y + 1] != ' '  && board[x - 1][y + 1]) {
				return 1;
			}
			else {
				return 0;
			}
		}

	}
	else {
		return 0;
	}
}

int spotEmpty(char** board, int length, int x, int y) { //0 if spot is empty 1 if it's filled
	if (board[x][y] == ' ') {
		return 0;
	}
	else {
		return 1;
	}
}

int columnCheck(char** board, int length, char player) {
	int counter;
	int score = 0;
	for (int x = 0; x < length; x++) {
		counter = 0;
		for (int y = 0; y < length; y++) {
			if (board[x][y] == player) {
				counter++;
			}
			else {
				if (counter == 4) {
					score++;
				}
				counter = 0;
			}
			if (counter == 4) {
				if (board[x][y + 1] == player) {
					counter = 0;
				}
				else {
					score++;
					counter = 0;
				}
			}
			if (counter == 4 &&  x == length - 1) {
				score++;
			}
		}
	}
	return score;
}

int rowCheck(char** board, int length, char player) {

	int counter;
	int score = 0;
	for (int y = 0; y < length; y++) {
		counter = 0;
		for (int x = 0; x < length; x++) {
			if (board[x][y] == player) {
				counter++;
			}
			else {
				if (counter == 4) {
					score++;
				}
				counter = 0;
			}
			if (counter == 4 && x == length - 1) {
				score++;
			}
		}
	}
	return score;
}


int diagonalCheck(char** board, int length, char player) {

	int score = 0;
	for (int i = 0; i < length; i++) {
		int counter = 0;
		for (int j = 0; j < length; j++) {
			if (i + j < length && i <= length - 4 && board[i + j][j] == player) {
				counter++;
			}
			else {
				counter = 0;
			}
			if (counter == 4) {
				if (i + j == length - 1 || board[i + j + 1][j + 1] != player) {
					score++;
				}
			}
		}
	}

	for (int i = 0; i < length; i++) {
		int counter = 0;
		for (int j = 0; j < length; j++) {
			if (i + j < length && i + j != j && i <= length - 4 && board[j][i + j] == player) {
				counter++;
			}
			else {
				counter = 0;
			}
			if (counter == 4) {
				if (i + j == length - 1 || board[j + 1][i + j + 1] != player) {
					score++;
				}
			}
		}

	}

	for (int i = length - 1; i > 0; i--) {
		int counter = 0;
		for (int j = 0; j < length; j++) {
			if (i - j >= 0 && i >= 3 && board[i - j][j] == player) {
				counter++;
			}
			else {
				counter = 0;
			}if (counter == 4) {
				if (i - j == 0 || board[i -j - 1][j + 1] != player) {
					score++;
				}
			}
		}

	}

	int a = length - 1;
	for (int i = 0; i <length; i++) {
		int counter = 0;
		for (int j = 0; j <length; j++) {
			if (i < length - 4 && i + j + 1 < length && board[a - j][i + j + 1] == player) {
				counter++;
			}
			else {
				counter = 0;
			}
			if (counter == 4) {
				if (i + j + 1 == length - 1 || board[a - j - 1][i + j + 2] != player) {
					score++;
				}
			}
		}
	}

	return score;

}


void play(char** arr, int boardlength, int whoseTurn) { //whoseturn = 0 for player1 and 1 for player2

	int numMoves = 0;

	int xWhite = 0;
	int yWhite = 0;

	int xBlack = 0;
	int yBlack = 0;

	int iteration = 0;

	while (numMoves != boardlength * boardlength) {
		if (whoseTurn == 0) {

			char coordinate[10];
			printf("Please enter the coordinates at for the white stone: ");
			fgets(coordinate, 10, stdin);
			//printf("%s\n", coordinate);
			xWhite = getX(coordinate);
			yWhite = getY(coordinate);

			if (bounds(arr, boardlength, xWhite, yWhite) == 0) {
				printf("Please enter the valid numbers.\n");
				continue;
			}

			if (spotEmpty(arr, boardlength, xWhite, yWhite) == 1) {
				printf("The spot's taken\n");
				continue;
			}

			//check adjacency after the first move is made.

			if (iteration == 0) {
				placeWhite(arr, boardlength, xWhite, yWhite);
			}
			else {
				//if the point is not adjacent and if all the spots adjacent are not filled ask for input again so that
				if (adjacent(arr, boardlength, xWhite, yWhite, xBlack, yBlack) != 1 && spotsFilled(arr, boardlength, xBlack, yBlack) != 1) {
					printf("please enter coordinates such that the player is adjacent!\n");
					continue;
				}
				//if point is not adjacent and all the spots adjacent are taken then just place the element
				else if (adjacent(arr, boardlength, xWhite, yWhite, xBlack, yBlack) != 1 && spotsFilled(arr, boardlength, xBlack, yBlack) == 1) {
					printf("The element could be placed anywhere!\n");
					placeWhite(arr, boardlength, xWhite, yWhite);
				}
				//if the point is adjacent and the spots adjacent are not filled then just place the elemrnt
				else if (adjacent(arr, boardlength, xWhite, yWhite, xBlack, yBlack) == 1 && spotsFilled(arr, boardlength, xBlack, yBlack) != 1) {
					placeWhite(arr, boardlength, xWhite, yWhite);
				}
			}

			numMoves++;

			printBoard(arr, boardlength);

			whoseTurn = 1;

		}
		else if (whoseTurn == 1) {

			if (numMoves == boardlength * boardlength - 1) {
				int choice = 0;
				printf("Enter 0 to make the last move and 1 to exit!\n");
				scanf("%d", &choice);
				char buff[10];
				fgets(buff, 10, stdin);
				if (choice == 1) {
					printf("Game over!\n");
					break;
				}
				else if (choice == 0) {
					char coordinate[10];
					printf("Please enter the coordinates at for the black stone: ");
					fgets(coordinate, 10, stdin);
					xBlack = getX(coordinate);
					yBlack = getY(coordinate);
					if (bounds(arr, boardlength, xBlack, yBlack) == 0) {
						printf("Please enter the valid numbers.\n");
						continue;
					}
					if (spotEmpty(arr, boardlength, xBlack, yBlack) == 1) {
						printf("The spot's taken\n");
						continue;
					}
					placeBlack(arr, boardlength, xBlack, yBlack);
					printBoard(arr, boardlength);
					numMoves++;
					break;
				}
			}

			char coordinate[10];
			printf("Please enter the coordinates at for the black stone: ");
			fgets(coordinate, 10, stdin);
			xBlack = getX(coordinate);
			yBlack = getY(coordinate);

			if (bounds(arr, boardlength, xBlack, yBlack) == 0) {
				printf("Please enter the valid numbers.\n");
				continue;
			}

			if (spotEmpty(arr, boardlength, xBlack, yBlack) == 1) {
				printf("The spot's taken\n");
				continue;
			}

			if (iteration > 0) {
				//if the point is not adjacent and if all the spots adjacent are not filled ask for input again so that
				if (adjacent(arr, boardlength, xBlack, yBlack, xWhite, yWhite) != 1 && spotsFilled(arr, boardlength, xWhite, yWhite) != 1) {
					printf("please enter coordinates such that the player is adjacent!\n");
					continue;
				}
				//if point is not adjacent and all the spots adjacent are taken then just place the element
				else if (adjacent(arr, boardlength, xBlack, yBlack, xWhite, yWhite) != 1 && spotsFilled(arr, boardlength, xWhite, yWhite) == 1) {
					printf("The element could be placed anywhere!\n");
					placeBlack(arr, boardlength, xBlack, yBlack);
				}
				//if the point is adjacent and the spots adjacent are empty then just place the elemrnt
				else if (adjacent(arr, boardlength, xBlack, yBlack, xWhite, yWhite) == 1 && spotsFilled(arr, boardlength, xWhite, yWhite) != 1) {
					placeBlack(arr, boardlength, xBlack, yBlack);
				}
			}


			numMoves++;

			printBoard(arr, boardlength);

			whoseTurn = 0;
		}

		iteration++;
	}

	int totalWhiteScore = rowCheck(arr, boardlength, 'W') + columnCheck(arr, boardlength, 'W') + diagonalCheck(arr, boardlength, 'W');
	int totalBlackScore = rowCheck(arr, boardlength, 'B') + columnCheck(arr, boardlength, 'B') + diagonalCheck(arr, boardlength, 'B');
	printf("The player1's score is: %d\n", totalWhiteScore);
	printf("The player2's score is: %d\n", totalBlackScore);
	if (totalWhiteScore > totalBlackScore) {
		printf("Player1 WON!!!\n");
		WHOWON = 0;
	}
	else if (totalBlackScore > totalWhiteScore) {
		printf("Player2 WON!!!\n");
		WHOWON = 1;
	}
	else {
		printf("You both tie!");
		WHOWON = 2;
	}
}

void testPrintBoard(char** board, int length) {

	board[0][0]='W';
	board[0][1]='B';
	board[0][2]='W';
	board[0][3]='W';
	board[0][4]='B';
	board[0][5]='W';
	board[0][6]='B';
	board[0][7]='W';
	board[0][8]='B';
	board[0][9]='B';

	board[1][0]='B';
	board[1][1]='B';
	board[1][2]='W';
	board[1][3]='W';
	board[1][4]='B';
	board[1][5]='W';
	board[1][6]='B';
	board[1][7]='W';
	board[1][8]='W';
	board[1][9]='W';

	board[2][0]='W';
	board[2][1]='B';
	board[2][2]='B';
	board[2][3]='B';
	board[2][4]='W';
	board[2][5]='B';
	board[2][6]='W';
	board[2][7]='B';
	board[2][8]='B';
	board[2][9]='B';

	board[3][0]='W';
	board[3][1]='B';
	board[3][2]='W';
	board[3][3]='W';
	board[3][4]='B';
	board[3][5]='W';
	board[3][6]='B';
	board[3][7]='W';
	board[3][8]='B';
	board[3][9]='W';

	board[4][0]='B';
	board[4][1]='W';
	board[4][2]='W';
	board[4][3]='W';
	board[4][4]='B';
	board[4][5]='W';
	board[4][6]='B';
	board[4][7]='B';
	board[4][8]='W';
	board[4][9]='B';

	board[5][0]='B';
	board[5][1]='W';
	board[5][2]='B';
	board[5][3]='B';
	board[5][4]='W';
	board[5][5] = 'W';
	board[5][6] = 'W';
	board[5][7] = 'W';
	board[5][8] = 'W';
	board[5][9] = 'B';

	board[6][0]='W';
	board[6][1]='B';
	board[6][2]='W';
	board[6][3]='B';
	board[6][4]='W';
	board[6][5] = 'B';
	board[6][6] = 'B';
	board[6][7] = 'B';
	board[6][8] = 'B';
	board[6][9]='W';

	board[7][0]='W';
	board[7][1]='B';
	board[7][2]='W';
	board[7][3]='W';
	board[7][4]='B';
	board[7][5]='B';
	board[7][6]='W';
	board[7][7]='W';
	board[7][8]='B';
	board[7][9]='W';

	board[8][0]='W';
	board[8][1]='B';
	board[8][2]='W';
	board[8][3]='B';
	board[8][4]='B';
	board[8][5]='W';
	board[8][6]='W';
	board[8][7]='B';
	board[8][8]='B';
	board[8][9]='B';

	board[9][0]='B';
	board[9][1]='B';
	board[9][2]='W';
	board[9][3]='B';
	board[9][4]='W';
	board[9][5]='B';
	board[9][6]='W';
	board[9][7]='B';
	board[9][8]='W';
	board[9][9]='W';
	printBoard(board, length);
}
