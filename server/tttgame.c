#include "final.h"

void getEmptyCount_ttt(GameObject* game)
{
  game->gd->numEmpty = 0;

  for (int i = 0; i < BOARDSIZE; i++)
  {
    if(game->gd->board[i] == 0)
    {
      game->gd->numEmpty++;
    }
  }
  printf("numEmpty is %d\n", game->gd->numEmpty);
}


void initGame_ttt(GameObject* game)
{
  for (int i = 0; i < BOARDSIZE; i++)
  {
    game->gd->board[i] = 0;
  }

  int first = rand() % 2;

  if(first > 0)
  {
   game->gd->board[4] = 1;
  }
}

int computerMove(GameObject* game)
{
  printf("Start computer move\n");
  int one[4] = {0, 2, 6, 8};
  int two[4] = {8, 6, 2, 0};

  getEmptyCount_ttt(game);
  // Begin by checking for a naughty client sending a full board.
  if(game->gd->numEmpty == 0)
  {
    printf("Board is full. Game is a tie, This should not have happened.\n");
    return 1;
  }
  // If empty or one square marked try to go center else corner.
  if(game->gd->numEmpty > 7)
  {
    if(game->gd->board[4] == 0)
    {
      game->gd->board[4] = 1;
    }
    else
    {
      game->gd->board[0] = 1;
    }
    printf("line 57 return\n");
    return 0;
  }
  // Two squares marked hit first open corner
  if(game->gd->numEmpty > 6)
  {
    for (int i = 0; i < 4; i++)
    {
      if(game->gd->board[one[i]] == 0)
      {
        game->gd->board[one[i]] = 1;
        printf("line 69 return index: %d\n", one[i]);
        return 0;
      }
    }
  }
  // Detect cross corner strategy
  if(game->gd->numEmpty == 6 && ((game->gd->board[0] == game->gd->board[8] &&  game->gd->board[0] != 0) || (game->gd->board[2] == game->gd->board[6] && game->gd->board[2] != 0)))
  {
    game->gd->board[1] = 1;
    printf("Line 78 return index 1\n");
    return 0;
  }
  for (int i = 0; i < 3; ++i)
  {
    // back column
    if(game->gd->board[i+3] == game->gd->board[i+6] && game->gd->board[i] == 0 && game->gd->board[i+3] != 0)
    {
      game->gd->board[i] = 1;
      printf("line 86 return\n");
      return 0;
    }
    //back row
    if(game->gd->board[i*3+1] == game->gd->board[i*3+2] && game->gd->board[i*3] == 0 && game->gd->board[i*3+1] != 0)
    {
      game->gd->board[i*3] = 1;
      printf("line 93 return index: %d\n", i*3);
      return 0;
    }
    for (int j = 1; j < 3; j++)
    {
      // Columns
      if(game->gd->board[i] == game->gd->board[i+3*j]  && game->gd->board[i] != 0)
      {
        if(j == 1 && game->gd->board[i+6] == 0)
        {
          game->gd->board[i+6] = 1;
          printf("line 104 return index: %d\n", i+6);
          return 0;
        }
        else if(j == 2 && game->gd->board[i+3] == 0)
        {
          game->gd->board[i+3] = 1;
          printf("line 110 return index: %d\n", i+3);
          return 0;
        }
      }
      // Rows
      if(game->gd->board[i*3] == game->gd->board[i*3+j]  && game->gd->board[i*3] != 0)
      {
        if(j == 1 && game->gd->board[i*3+2] == 0)
        {
          game->gd->board[i*3+2] = 1;
          printf("line 120 return index: %d\n", i*3+2);
          return 0;
        }
        else if(j == 2 && game->gd->board[i*3+1] == 0)
        {
          game->gd->board[i*3+1] = 1;
          printf("line 126 return index: %d\n", i*3+1);
          return 0;
        }
      }
    }
  }
  //Diagonals
  for (int i = 0; i < 4; ++i)
  {
    if(game->gd->board[4] == game->gd->board[one[i]] && game->gd->board[two[i]] == 0)
    {
      game->gd->board[two[i]] = 1;
      printf("line 138 return index: %d \n", two[i]);
      return 0;
    }
  }
  // If nobody can win
  int three[9] = { 0, 2, 6, 8, 4, 1, 3, 5, 7};
  for (int i = 0; i < BOARDSIZE; i++)
  {
    if(game->gd->board[three[i]] == 0)
    {
      game->gd->board[three[i]] = 1;
      printf("line 149 return index: %d \n", three[i]);
      return 0;
    }
  }
  printf("line 153 return, not good.\n");
  return 1;
}

