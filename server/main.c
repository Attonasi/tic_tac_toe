/*This is the main function. It really doesn't do that
  much. It sets values and starts the server. Everything
  you want to read in the header file final.h.
*/
#include "final.h"

int main(int argc, char const *argv[])
{
  srand(time(NULL));

  // Server Variables
  int port = PORT;
  Instance_t instance;
  int serverStatus = 1;

  // Game Comm variables
  char input[BUFFER] = "\0";
  int inputLen = 0;
  char output[BUFFER] = "\0";
  int outputLen = 0;

  // Game Variables
  int numEmpty = 0;
  int board[9];
  char playerName[100];

  // JSON Things
  json_t *root_json = json_object();
  json_t *playerName_json = json_object();
  json_t *board_json = json_object();
  json_error_t error_json;

  Key_t* board_j = "board";
  Key_t* player_j = "playerName";

  //Data Struct Initiation
  GameComm* gc = createGameComm(input, inputLen, output, outputLen);
  GameData* gd = createGameData(playerName, board, numEmpty);
  JSOnPtrs* jp = createJSOnPointers(root_json, playerName_json, board_json);
  JSOnKeys* jk = createJSOnKeys(board_j, player_j);
  JSOnData* jd = createJSOnData(jp, jk, error_json);
  ServerData* sv = createServer(port, serverStatus, instance);
  GameObject* game = createGameObj(gc, gd, sv, jd);

  //Turn on the Server
  INITIATE_R(game);

  free(gc);
  free(gd);
  free(jp);
  free(jk);
  free(jd);
  free(sv);
  free(game);

  return 0;
}