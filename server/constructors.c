

#include "final.h"

ServerData* createServer(int port, int serverStatus, struct _u_instance instance)
{
  ServerData* sv = malloc(sizeof(ServerData));

  sv->port = port;
  sv->serverStatus = serverStatus;
  sv->instance = instance;

  return sv;
}

GameComm* createGameComm(char* input, int inputLen, char* output, int outputLen)
{
  GameComm* gc = malloc(sizeof(GameData));

  strcpy(gc->input, input);
  gc->inputLen = inputLen;
  strcpy(gc->output, output);
  gc->outputLen = outputLen;

  return gc;
}

GameData* createGameData(char* playerName,/* char XoO,*/ int board[9], int numEmpty)
{
  GameData* gd = malloc(sizeof(GameData));

  gd->numEmpty = numEmpty;
  strcpy(gd->playerName, playerName);
  // gd->XoO = XoO;
  for (int i = 0; i < BOARDSIZE; i++)
  {
    gd->board[i] = board[i];
  }

  return gd;
}

JSOnPtrs* createJSOnPointers(json_t *root_json, json_t *playerName_json,/* json_t *playerXoO_json,*/ json_t *board_json)
{
  JSOnPtrs* jp = malloc(sizeof(JSOnPtrs));

  jp->root_json = root_json;
  jp->playerName_json = playerName_json;
  // jp->playerXoO_json = playerXoO_json;
  jp->board_json = board_json;

  return jp;
}

JSOnKeys* createJSOnKeys(const char* board_j, /*const char* XoO_j,*/ const char* player_j)
{
  JSOnKeys* jk = malloc(sizeof(JSOnKeys));

  jk->board_j = strdup(board_j);
  // jk->XoO_j = strdup(XoO_j);
  jk->player_j = strdup(player_j);

  return jk;
}


JSOnData* createJSOnData(JSOnPtrs* jp, JSOnKeys* jk, json_error_t error_json)
{
  JSOnData* jd = malloc(sizeof(JSOnData));

  jd->jp = jp;
  jd->jk = jk;
  jd->error_json = error_json;

  return jd;
}

GameObject* createGameObj(GameComm* gc, GameData* gd, ServerData* sv, JSOnData* jd)
{
  GameObject* game = malloc(sizeof(GameObject));

  game->gc = gc;
  game->gd = gd;
  game->sv = sv;
  game->jd = jd;

  return game;
}