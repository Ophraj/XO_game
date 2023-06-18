/*-------------------------------------------------------------------------
  Include files:
--------------------------------------------------------------------------*/

#include <stdio.h>
#include <stdlib.h>


/*=========================================================================
  Constants and definitions:
==========================================================================*/

/*  #defines and typedefs here*/
#define N 12
#define S 11
#define PLAYER_ONE_SIGN 'X'
#define PLAYER_TWO_SIGN 'O'
#define N_PLAY 2
#define DIFF_PLAYERS 3
#define INDEX_P_TWO 2
#define INDEX_P_ONE 1
#define EVEN 2
/*-------------------------------------------------------------------------
  The main program. (describe what your program does here)
     XO game in the board size of the players' choice.
 -------------------------------------------------------------------------*/
void print_welcome_phrase ();
void print_enter_board_size();
void print_player_turn(int current_player);
void print_error();
void print_player_turn (int current_player);
void print_board (int n, int matrix[N][N]);
void ask_and_take_values (int *row_choice, int *column_choice, int current_player);
void take_values (int *row_choice, int *column_choice);
void check_win (int count, int board_matrix[N][N], int *pcheck, int board_size, int player, int *pcount);
void keep_record_of_game (int count, int row, int column, int keep_record [N_PLAY][N*N]);
int check_of_scan (int n, int matrix[N][N], int keep_record [N_PLAY][N*N], int row, int column, int count, int player, int* pcount);
int normal_turn (int row, int column, int board_size,int keep_record[N_PLAY][N*N], int board_matrix[N][N], int player, int count);
int row_or_column_out_of_board (int row, int column, int board_size);
int row_is_negative (int row, int board_size, int board_matrix [N][N], int keep_record [N_PLAY][N*N], int count, int *pcount);
void undo_game (int row, int board_matrix[N][N], int keep_record [N_PLAY][N*N], int count,int* pcount);
int keep_board_player (int matrix [N][N], int row, int column, int player, int board_size);
int checking_winner (int matrix[N][N], int board_size, int player, int count);
int checking_win_diagonal1 (int board_size, int matrix [N][N]);
int checking_win_diagonal2 (int board_size, int matrix [N][N]);
int checking_win_row (int board_size, int matrix [N][N]);
int checking_win_column (int board_size, int matrix [N][N]);
int check_tie (int count, int board_size);
void print_tie ();
void print_winner(int current_player);

//main function
//13 lines
int main()
{
    int board_size,row_choice,column_choice, current_player=1, count=0, check=1;
    int *pcheck=&check, *pcount=&count;
    int board_matrix[N][N]={{0}}, keep_record [N_PLAY][N*N]={{0}};

    print_welcome_phrase ();
    scanf ("%d", &board_size);
    print_board (board_size,board_matrix);

   while (check)
   {
       ask_and_take_values (&row_choice,&column_choice,current_player);

       while (check_of_scan(board_size,board_matrix,keep_record,row_choice,column_choice,count,current_player, pcount)==0)
       {
           take_values(&row_choice,&column_choice);
       }

       current_player=DIFF_PLAYERS-current_player;
       check_win (count, board_matrix, pcheck, board_size, current_player, pcount);
   }
  return 0;
}

//print welcome message
//3 lines
void print_welcome_phrase ()
{
    printf ("*** Welcome to AVOIDANCE TIC-TAC-TOE game ***\n");
    printf ("\n");
    print_enter_board_size();
}

//print message to enter board size
//1 lines
void print_enter_board_size()
{
    printf("Please enter board size (1 to %d):\n", S);
}

//print player turn
//1 line
void print_player_turn (int current_player)
{
    printf ("\nPlayer ** %d **, enter next move:\n", current_player);
}


//Take row value and column value if row positive from the player.
//5 lines
void take_values (int *row_choice, int *column_choice)
{
   scanf ("%d", row_choice);
       if (*row_choice>=0)
       {
            scanf ("%d", column_choice);
       }
       else
       {
           *column_choice=1;
       }
}

//ask the current player row and column values and update them
//6 lines
void ask_and_take_values (int *row_choice, int *column_choice, int current_player)
{
    print_player_turn(current_player);
    scanf ("%d", row_choice);
       if (*row_choice>=0)
       {
            scanf ("%d", column_choice);
       }
       else
       {
           *column_choice=1;
       }
}

//update check if there's a winner to stop the game
//2 lines
 void check_win (int count, int board_matrix[N][N], int *pcheck, int board_size, int player, int *pcount)
{
    if (count>=(N_PLAY*board_size-N_PLAY))
    {
        *pcheck =checking_winner(board_matrix, board_size,player,count);
    }

    *pcount=*pcount+1;
}
//update the array in case an undo is performed
// 2 lines
void keep_record_of_game (int count, int row, int column, int keep_record[N_PLAY][N*N])
{
    keep_record[0][count]=row;
    keep_record[1][count]=column;
}


//check the values of row and column and perform in correspondence.
//9 lines
 int check_of_scan (int board_size, int board_matrix[N][N], int keep_record [N_PLAY][N*N], int row, int column, int count, int player, int* pcount)
 {
     if (1)
     {
        if (normal_turn (row, column, board_size, keep_record, board_matrix,player,count))
        {
            return 1;
        }

        if ((row_is_negative(row, board_size, board_matrix,keep_record,count,pcount))==1)
        {
            return 1;
        }
        if (row_or_column_out_of_board (row, column, board_size))
        {
          return 0;
        }
     }
    return 0;
 }


//case when row and column are normal values, check if the case is already taken, update everything needed and print the new board.
//8 lines
int normal_turn (int row, int column, int board_size,int keep_record[N_PLAY][N*N], int board_matrix[N][N], int player, int count)
{
    if ((row>0)&&(row<=board_size)&&(column>0)&&(column<=board_size))
    {
        if (keep_board_player(board_matrix,row,column,player,board_size))
        {
            keep_record_of_game (count,row,column,keep_record);
            return 1;
        }
        else
        {
            print_error();
            return 0;
        }
    }
    return 0;
}

//case when row or column are too big or equal to zero, ask again.
//7 lines
int row_or_column_out_of_board (int row, int column, int board_size)
{
    if ((row>board_size)||(column>board_size))
    {
        print_error ();
        return 1;
    }
    if ((row==0)||(column==0))
    {
        print_error ();
        return 1;
    }
    return 0;
}

//case when row is negative, perform undo.
//10 lines
int row_is_negative (int row, int board_size, int board_matrix [N][N], int keep_record [N_PLAY][N*N], int count, int *pcount)
{
    if (row<0)
    {
        int tempr=(-1)*row;
        if ((tempr%EVEN==1)&&(tempr<=count))
        {
        undo_game (row,board_matrix,keep_record, count, pcount);
        print_board (board_size, board_matrix);
        return 1;
        }
        else
        {
            print_error();
            return 0;
        }
    }
    return 0;
}

 // undo function.
 //10 lines
 void undo_game (int row, int board_matrix[N][N], int keep_record [N_PLAY][N*N], int count, int* pcount)
 {
     int row_temp=row;
     int count_temp=count;
     while (row!=0)
     {
         int c=keep_record[0][count-1];
         int d= keep_record[1][count-1];
         board_matrix[c][d]=0;
         row++;
         count--;
     }
     *pcount= count_temp+row_temp-1;
 }

//update the array of the board or return 0 if place is already taken.
//8 lines
 int keep_board_player (int board_matrix [N][N], int row, int column, int player, int board_size)
 {
   if (board_matrix[row][column]!=0)
   {
       return 0;
   }

   if (player==INDEX_P_ONE)
   {
        board_matrix[row][column]=INDEX_P_ONE;
   }

    if (player==INDEX_P_TWO)
    {
        board_matrix[row][column]=INDEX_P_TWO;
    }

    print_board (board_size, board_matrix);
    return 1;
 }

 // print board of the game.
 //11 lines
void print_board (int n, int board_matrix[N][N])
 {
     printf ("\nCurrent board:\n");

     for (int i=1; i<n+1; i++)
     {
         for (int j=1; j<n+1; j++)
         {
             if (board_matrix [i][j]==0)
                printf ("|_");
             if (board_matrix [i][j]==INDEX_P_ONE)
                printf ("|%c", PLAYER_ONE_SIGN);
             if (board_matrix [i][j]==INDEX_P_TWO)
                printf ("|%c", PLAYER_TWO_SIGN);
         }
         printf ("|\n");
     }
     printf ("\n");

 }

// print error when needed.
//1 line
void print_error ()
{
    printf ("Illegal move!!!, please try again:\n");
}

//print tie if needed
//1 line
void print_tie ()
{
    printf  ("It's a tie!\n");
}

//print the winner if needed
//1 line
void print_winner(int current_player)
{
    printf("Player %d Wins! Hooray!\n", current_player);
}

//check if there's a winner in all the board and print in correspondence.
//10 lines
int checking_winner(int matrix[N][N], int board_size, int player, int count)
{

     if (((checking_win_row (board_size, matrix))==1)||((checking_win_column (board_size, matrix))==1))
      {
        print_winner(player);
        return 0;
      }

    if (((checking_win_diagonal1 (board_size, matrix))==1)||((checking_win_diagonal2 (board_size, matrix))==1))
     {
        print_winner(player);
        return 0;
     }

     if (check_tie (count, board_size))
     {
         print_tie();
         return 0;
     }

    return 1;
}


//check if there's a winner in each column.
//8 lines
int checking_win_column (int board_size, int matrix [N][N])
{

    for (int j=1; j<=board_size; j++)
    {
        int column_count=0;
        for (int i=1; i<board_size; i++)
        {
            if ((matrix[i][j]!=0) && (matrix[i][j]==matrix[i+1][j]))
            column_count++;
        }
        if (column_count==board_size-1)
        {
            return 1;
        }
    }
    return 0;
}

//check if there's a winner in each row.
//8 lines
int checking_win_row (int board_size, int matrix[N][N])
{
    for (int i=1; i<=board_size; i++)
    {
        int row_count=0;
        for (int j=1; j<board_size; j++)
        {
            if ((matrix[i][j]!=0)&&(matrix [i][j]==matrix[i][j+1])  )
            row_count++;
        }
        if(row_count==board_size-1)
            return 1;
    }
    return 0;

}

//check if there's a winner in the first diagonal.
//7 lines
int checking_win_diagonal1 (int board_size, int matrix [N][N])
{
    int count_1=0;

    for (int i=1; i<board_size; i++)
    {
        if ((matrix [i][i]==matrix[i+1][i+1])&&(matrix[i][i]!=0))
            count_1++;

        if (count_1==board_size-1)
            return 1;
    }
    return 0;
}

//check if there's a winner in the second diagonal.
//7 lines
int checking_win_diagonal2 (int board_size, int matrix [N][N])
{
    int count_2=0;

    for (int j=board_size,i=1; (j>1)&&(i<board_size); j--,i++)
        {
           if ((matrix [i][j]!=0)&&(matrix[i][j]==matrix[i+1][j-1]))
           {
            count_2++;
           }
           if (count_2==board_size-1)
           {
            return 1;
           }
        }
    return 0;
}

//check if there's a tie.
//4 lines.
int check_tie (int count, int board_size)
{
    if (count==board_size*board_size-1)
        return 1;
    else
        return 0;
}
