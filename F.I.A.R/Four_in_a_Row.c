/*Program: Game- Four in a row written in C. wrriten by dolev hindy
*Game: Connect_Four.
*Size:6-rows 7-column
*Rules:2 Players, you can put wherever you want, the first who have 4 connect wins.
*
*0 means -undo-cancel enemy's turn.
*/
#include <stdio.h>
#include <ctype.h>
#include "header.h"
#include <stdbool.h>
#include <stdlib.h>/*Program: Game- Four in a row written in C. wrriten by dolev hindy
*Game: Connect_Four.
*Size:6-rows 7-column
*Rules:2 Players, you can put wherever you want, the first who have 4 connect wins.
*
*0 means -undo-cancel enemy's turn.
*/
//if the column is full , if letters
#include <stdio.h>
#include <ctype.h>
#include "header.h"
#include <stdbool.h>
#include <stdlib.h>

static int Stack[STACK_MAX];
static int top = -1;
//STACK
int Isempty()
{
    if (top == -1)
        return 1;
    else
        return 0;
}
int Isfull()
{
    if (top == STACK_MAX)
        return 1;
    else
        return 0;
}
int Peek()
{
    return Stack[top];
}
int Pop()
{
    int data;
    if (!Isempty())
    {
        data = Stack[top];
        top = top - 1;
        return data;
    }
}
int Push(int data)
{
    if (!Isfull())
    {
        top = top + 1;
        Stack[top] = data;
    }
    else
    {
        printf(" Stack is full.\n");
    }
}
//Print our Board:
void Print_Board(char board[MAX_ROW][MAX_COLUMN])
{
    for (int i = 0; i < MAX_ROW; i++)
    {
        for (int j = 0; j < MAX_COLUMN; j++)
        {
            printf("|%c", board[i][j]);
        }
        printf("|\n");
    }
    printf(" 1 2 3 4 5 6 7 \n");
}
// check if column is full
int Full_Column(char board[MAX_ROW][MAX_COLUMN], int n)
{
    int i = 0;
    if (board[i][n] != Space)
    {
        return 0;
    }
}
//check if four in a row
int Row(char board[MAX_ROW][MAX_COLUMN], char User[], int player)
{
    for (int row = 5; row >= 0; row--)
    {
        for (int i = 0; i < 4; i++)
        {
            if (board[row][i] == User[player] && board[row][i + 1] == User[player] && board[row][i + 2] == User[player] && board[row][i + 3] == User[player])
            {
                return 1;
            }
        }
    }
}
//check if four in a column
int Column(char board[MAX_ROW][MAX_COLUMN], char User[], int player)
{
    for (int column = 6; column >= 0; column--)
    {
        for (int i = 0; i < 3; i++)
        {
            if (board[i][column] == User[player] && board[i + 1][column] == User[player] && board[i + 2][column] == User[player] && board[i + 3][column] == User[player])
            {
                return 1;
            }
        }
    }
}
//trace  [i][j]->[i+1][j+1] ->[i+2][j+2]->[i+3][j+3] - check if four in a trace
int Trace1(char board[MAX_ROW][MAX_COLUMN], char User[], int player)
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            if (board[i][j] == User[player] && board[i + 1][j + 1] == User[player] && board[i + 2][j + 2] == User[player] && board[i + 3][j + 3] == User[player])
            {
                return 1;
            }
        }
    }
}
//trace [i][j]->[i-1][j+1]->[i-2][j+2]->[i-3][j+3] -check if four in a trace
int Trace2(char board[MAX_ROW][MAX_COLUMN], char User[], int player)
{
    for (int i = 3; i < MAX_ROW; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            if (board[i][j] == User[player] && board[i - 1][j + 1] == User[player] && board[i - 2][j + 2] == User[player] && board[i - 3][j + 3] == User[player])
            {
                return 1;
            }
        }
    }
}
//check if board is full
int draw(char board[MAX_ROW][MAX_COLUMN])
{
    for (int i = 0; i < MAX_COLUMN; i++)
    {
        if (board[0][i] == Space)
        {
            return 0;
        }
    }
    printf("It's a tie! \n");
}
//add a disk in a column
void add(char board[MAX_ROW][MAX_COLUMN], int col, char User[], int place)
{
    for (int index = 5; index >= 0;)
    {
        if (board[index][col - 1] == Space)
        {
            Push(col - 1); //we add every turn to the stack.
            board[index][col - 1] = User[place];

            break;
        }
        else
            index--;
    }
    Print_Board(board);
}
//delete the last turn
void del(char board[MAX_ROW][MAX_COLUMN])
{
    int delete = Pop();
    for (int i = 0; i < MAX_ROW; i++)
    {
        if (board[i][delete] != Space)
        {
            board[i][delete] = Space;
            break;
        }
    }
    Print_Board(board);
}
// MAIN
int main()
{
    char User[] = {'X', 'O'};
    printf("Welcome !\n");
    char board[MAX_ROW][MAX_COLUMN];
    for (int i = 0; i < MAX_ROW; i++)
    {
        for (int j = 0; j < MAX_COLUMN; j++)
        {
            board[i][j] = Space;
        }
    }
    int place = 0;
    Print_Board(board);
    while (draw(board) == 0)
    {
        //player 1 +player 2
        float column; //column
        printf("Player %c, please enter column number : (or - 0 to undo) :\n ", User[place]);
        scanf("%f", &column);
        int col = (int)column;
        while (col > 7 || col < 0)
        {
            printf("Invalid input, the number must be between 1 to 7:\n");
            printf("Player %c, please enter column number : (or - 0 to undo) :\n ", User[place]);
            scanf("%f", &column);
            col = (int)column;
        }
        if (col == 0) // undo
        {
            if (Isempty() != 1)
            {
                del(board);
            }
            else
            {
                while (col == 0)
                {
                    printf("Board is empty - can't undo!\n");
                    printf("Player %c, please enter column number : (or - 0 to undo) :\n ", User[place]);
                    scanf("%f", &column);
                    col = (int)column;
                }
                add(board, col, User, place);
            }
        }
        else if (col < 8 && col >= 1)
        {
            while (Full_Column(board, col - 1) == 0)
            {
                printf("Invalid input, this column %d is full. Please choose another one:\n", col);
                printf("Player %c, please enter column number : (or - 0 to undo) :\n ", User[place]);
                scanf("%f", &column);
                col = (int)column;
            }
            add(board, col, User, place);
            if ((col - column) < 0)
            {
                printf("Invalid input, bye-bye!\n");
                exit(0);
            }
        }
        if (Row(board, User, 0) == 1 || Column(board, User, 0) == 1 || Trace1(board, User, 0) == 1 || Trace2(board, User, 0) == 1)
        {
            Print_Board(board);
            printf("Player %c wins:\n ", User[0]);
            printf("Game is Over! \n");
            break;
        }
        if (Row(board, User, 1) == 1 || Column(board, User, 1) == 1 || Trace1(board, User, 1) == 1 || Trace2(board, User, 1) == 1)
        {
            Print_Board(board);
            printf("Player %c wins:\n ", User[1]);
            printf("Game is Over! \n ");
            break;
        }
        //changing the player
        if (place == 0)
        {
            place = 1;
        }
        else
        {
            place = 0;
        }
    }
    return 0;
}

static int Stack[STACK_MAX];
static int top = -1;
//STACK
int Isempty()
{

    if (top == -1)
        return 1;
    else
        return 0;
}
int Isfull()
{

    if (top == STACK_MAX)
        return 1;
    else
        return 0;
}
int Peek()
{
    return Stack[top];
}
int Pop()
{
    int data;
    if (!Isempty())
    {
        data = Stack[top];
        top = top - 1;
        return data;
    }
}
int Push(int data)
{

    if (!Isfull())
    {
        top = top + 1;
        Stack[top] = data;
    }
    else
    {
        printf(" Stack is full.\n");
    }
}
//Print our Board:
void Print_Board(char board[MAX_ROW][MAX_COLUMN])
{

    for (int i = 0; i < MAX_ROW; i++)
    {
        for (int j = 0; j < MAX_COLUMN; j++)
        {
            printf("|%c", board[i][j]);
        }
        printf("|\n");
    }
    printf(" 1 2 3 4 5 6 7 \n");
}
// check if column is full
int Full_Column(char board[MAX_ROW][MAX_COLUMN], int n)
{
    int i = 0;
    if (board[i][n] != Space)
    {
        return 0;
    }
}
//check if four in a row
int Row(char board[MAX_ROW][MAX_COLUMN], char User[], int player)
{
    for (int row = 5; row >= 0; row--)
    {
        for (int i = 0; i < 4; i++)
        {
            if (board[row][i] == User[player] && board[row][i + 1] == User[player] && board[row][i + 2] == User[player] && board[row][i + 3] == User[player])
            {
                return 1;
            }
        }
    }
}
//check if four in a column
int Column(char board[MAX_ROW][MAX_COLUMN], char User[], int player)
{
    for (int column = 6; column >= 0; column--)
    {
        for (int i = 0; i < 3; i++)
        {
            if (board[i][column] == User[player] && board[i + 1][column] == User[player] && board[i + 2][column] == User[player] && board[i + 3][column] == User[player])
            {
                return 1;
            }
        }
    }
}
//trace  [i][j]->[i+1][j+1] ->[i+2][j+2]->[i+3][j+3] - check if four in a trace
int Trace1(char board[MAX_ROW][MAX_COLUMN], char User[], int player)
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            if (board[i][j] == User[player] && board[i + 1][j + 1] == User[player] && board[i + 2][j + 2] == User[player] && board[i + 3][j + 3] == User[player])
            {
                return 1;
            }
        }
    }
}
//trace [i][j]->[i-1][j+1]->[i-2][j+2]->[i-3][j+3] -check if four in a trace
int Trace2(char board[MAX_ROW][MAX_COLUMN], char User[], int player)
{
    for (int i = 3; i < MAX_ROW; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            if (board[i][j] == User[player] && board[i - 1][j + 1] == User[player] && board[i - 2][j + 2] == User[player] && board[i - 3][j + 3] == User[player])
            {
                return 1;
            }
        }
    }
}
//check if board is full
int draw(char board[MAX_ROW][MAX_COLUMN])
{
    for (int i = 0; i < MAX_COLUMN; i++)
    {
        if (board[0][i] == Space)
        {
            return 0;
        }
    }
    printf("It's a tie! \n");
}
//add a disk in a column
void add(char board[MAX_ROW][MAX_COLUMN], int col, char User[], int place)
{
    for (int index = 5; index >= 0;)
    {
        if (board[index][col - 1] == Space)
        {
            Push(col - 1); //we add every turn to the stack.
            board[index][col - 1] = User[place];

            break;
        }
        else
            index--;
    }
    Print_Board(board);
}
//delete the last turn
void del(char board[MAX_ROW][MAX_COLUMN])
{
    int delete = Pop();
    for (int i = 0; i < MAX_ROW; i++)
    {
        if (board[i][delete] != Space)
        {
            board[i][delete] = Space;
            break;
        }
    }
    Print_Board(board);
}
// MAIN
int main()
{
    char User[] = {'X', 'O'};
    printf("Welcome !\n");
    char board[MAX_ROW][MAX_COLUMN];
    for (int i = 0; i < MAX_ROW; i++)
    {
        for (int j = 0; j < MAX_COLUMN; j++)
        {
            board[i][j] = Space;
        }
    }
    int place = 0;
    Print_Board(board);
    while (draw(board) == 0)
    {
        //player 1 +player 2
        float column; //column
        printf("Player %c, please enter column number : (or - 0 to undo) :\n ", User[place]);
        scanf("%f", &column);
        int col = (int)column;
        while (col > 7 || col < 0)
        {
            printf("Invalid input, the number must be between 1 to 7:\n");
            printf("Player %c, please enter column number : (or - 0 to undo) :\n ", User[place]);
            scanf("%f", &column);
            col = (int)column;
        }
        if (col == 0) // undo
        {
            if (Isempty() != 1)
            {
                del(board);
            }
            else
            {
                while (col == 0)
                {
                    printf("Board is empty - can't undo!\n");
                    printf("Player %c, please enter column number : (or - 0 to undo) :\n ", User[place]);
                    scanf("%f", &column);
                    col = (int)column;
                }
                add(board, col, User, place);
            }
        }
        else if (col < 8 && col >= 1)
        {
            while (Full_Column(board, col - 1) == 0)
            {
                printf("Invalid input, this column %d is full. Please choose another one:\n", col);
                printf("Player %c, please enter column number : (or - 0 to undo) :\n ", User[place]);
                scanf("%f", &column);
                col = (int)column;
            }
            add(board, col, User, place);
            if ((col - column) < 0)
            {
                printf("Invalid input, bye-bye!\n");
                exit(0);
            }
        }

        if (Row(board, User, 0) == 1 || Column(board, User, 0) == 1 || Trace1(board, User, 0) == 1 || Trace2(board, User, 0) == 1)
        {
            Print_Board(board);
            printf("Player %c wins:\n ", User[0]);
            printf("Game is Over! \n");
            break;
        }
        if (Row(board, User, 1) == 1 || Column(board, User, 1) == 1 || Trace1(board, User, 1) == 1 || Trace2(board, User, 1) == 1)
        {
            Print_Board(board);
            printf("Player %c wins:\n ", User[1]);
            printf("Game is Over! \n ");
            break;
        }
        //changing the player
        if (place == 0)
        {
            place = 1;
        }
        else
        {
            place = 0;
        }
    }
    return 0;
}
