#ifndef FINAL_H
#define FINAL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <netdb.h>
#include <sys/socket.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <jansson.h>
#include <ulfius.h>
#include <time.h>

/* ENDPOINTS:

http://localhost:8080/init --> The client calls this endpoint to start a new game.

http://localhost:8080/move --> The client calls this endpoint to get a move from
                               the computer in a game.

http://localhost:8080/shutdown --> Usually called by a curl call. Shuts the server
                                   down.
*/

/*
This program will create a server to play the game of Tic Tac Toe and
a client user interface that will facilitate the players moves. The server
and the client will be stateless/RESTful. This means the server and the
client will pass abd receive an entire game in progress, develop a response,
and pass it back. THe game is formatted to JSOn when passed from client
to server.
*/

#define BUFFER 1000
#define BOARDSIZE 9
#define PORT 8080

// typedef!

typedef struct _u_instance Instance_t;
typedef const struct _u_request U_Request_t;
typedef const char Key_t;

// STRUCTS

/*
JSOnPtrs holds pointers to the json_t objects used by the server to help decode and
encode the JSON strings used to communicate with clients.

json_t*  root_json a pointer to the root object that is sent and received from a client.

json_t* playerName_json json_t pointer to the players name.

json_t* board_json json_t pointer to board_json the jsont_t* object set to the board

return JSOnPtrs* pointer to a struct holding pointers the above values.
*/

typedef struct {

  json_t* root_json;
  json_t* playerName_json;
  json_t* board_json;
} JSOnPtrs;

JSOnPtrs* createJSOnPointers(json_t *root_json, json_t *playerName_json, json_t *board_json);

/*
JSOnKeys* holds pointers to the keys of the key value pairs in the json objects
passed from server and client.

Key_t (const char*) board_j holds a pointer to "board"

Key_t (const char*) player_j holds a pointer to "playerName"

return JSOnKeys* pointer to a struct holding pointers to the above values
*/
typedef struct {

  Key_t* board_j;
  Key_t* player_j;
} JSOnKeys;

JSOnKeys* createJSOnKeys(Key_t* board_j, Key_t* player_j);

/*
JSOnData is a struct holding pointers to JSOnKeys and JSOPtrs. It is just a further
abstraction to sepereate date into groups.

JSOnPtrs* jp a pointer to the struct jp that holds json_t pointers.

JSOnKeys* jk a pointer to the struct jk that holds the string key values in JSOnKeys.

json_error_t error_json a struct the jansson library uses to hold errors thrown in
jansson library functions.

return JSONData* a pointer to a struct holding the JSOnPtrs and JSOnKeys struct and
the error json struct.
*/
typedef struct {

  JSOnPtrs* jp;
  JSOnKeys* jk;
  json_error_t error_json;

} JSOnData;

JSOnData* createJSOnData(JSOnPtrs* jp, JSOnKeys* jk, json_error_t error_json);

/*
ServerData holds information for server operations

int port The port number the server will be opened on.

int serverStatus int that keeps the while loop holding the server going and
turned off when the shurdown command is given.

struct _u_instance instance the core instance struct ulfius needs to run.

return Serverdata* a struct that holds pointers to the above items.
*/

typedef struct {

  int port;
  int serverStatus;
  struct _u_instance instance;

} ServerData;

ServerData* createServer(int port, int serverStatus, struct _u_instance instance);

/*
GameComm short for game communications is a struct holding the input and output strings
and their lengths used by the server and client to communicate.

char input[] char array designated for holding the input from the client.

int inputLen the length of the input;

char output[] char array designated for holding the output from the client.

int inputLen the length of the output;

return GameComm* pointer to the GameComm object holding the above pointers.
*/
typedef struct {

  char input[BUFFER];
  int inputLen;
  char output[BUFFER];
  int outputLen;

} GameComm;

GameComm* createGameComm(char* input, int inputLen, char* output, int outputLen);

/*
GameData holds the information needed to handle the game the server makes and or receivess
and sends.

int numEmpty used to document the number of empty squares on a board passed in from a client.

char playerName[] char array holding the players name

int board[] array holding the values for the 9 squares of the board in a tictactoe game.

return gd pointer to a GameData struct.
*/
typedef struct {

  int numEmpty;
  char playerName[100];
  int board[9];

} GameData;

GameData* createGameData(char* playerName, int board[9], int numEmpty);

/*
GameObject holds pointers to the structs holding pointers to the various values needed
to run the game of tictactoe. Easch of these objects is an abstraction to logically
seperate out the data.

GameComm* gc pointer to a GameComm struct holding game communications inforrmation

GameData* gd pointer to a GameData struct holding hte game values.

ServerData sd pointer to a ServerData struct holding values for the server.

JSOnData js pointer to a JSOnData struct holding values for the jansson library to
encode and decode JSON.

return GameObject* a pointer to a GameObject that represents the state of a tictactoe
game and holds pointers to all of the values that maintain the server.
*/

typedef struct {

  GameComm* gc;
  GameData* gd;
  ServerData* sv;
  JSOnData* jd;

} GameObject;

GameObject* createGameObj(GameComm* gc, GameData* gd, ServerData* sv, JSOnData* jd);

// REST_SERVER.C

/*
INITIATE_R opens the server instance, definces the endpoints of the REST server, and starts
starts the instance.

GameObject* game struct holding pointers to the variables used in the game defined above.
*/
void INITIATE_R(GameObject* game);

/*
initGameGET_R is the function called by the /init endpoint. It initializes a tictactoe board
by calling intiGame_ttt.

U_Request_t* (const struct _u_request)* request is a pointer to a request object created by the
ulfius library.

struct _u_response response is a pointer to a response object created by the ulfius library.

void* user_data is a void* where the user passes their data into the endpoint functions used
in the ulfius library. GameObject is what is passed invariably.

GameObject* game struct holding pointers to the variables used in the game defined above.
*/

int initGameGET_R(U_Request_t* request, struct _u_response* response, void* user_data);
/*
processMovePOST_R is the function called by the /move endpoint. This function calles parseBoard_R,
computerMove_ttt, encodeJSON and returns the response.

U_Request_t* (const struct _u_request)* request is a pointer to a request object created by the
ulfius library.

struct _u_response response is a pointer to a response object created by the ulfius library.

void* user_data is a void* where the user passes their data into the endpoint functions used
in the ulfius library. GameObject is what is passed invariably.

GameObject* game struct holding pointers to the variables used in the game defined above.
*/
int processMovePOST_R(U_Request_t* request, struct _u_response* response, void* input);

/*
shutdownGET_R is the function called by the /shutdown GET endpoint that merely shuts down the
server gracefully.

U_Request_t* (const struct _u_request)* request is a pointer to a request object created by the
ulfius library.

struct _u_response response is a pointer to a response object created by the ulfius library.

void* user_data is a void* where the user passes their data into the endpoint functions used
in the ulfius library. GameObject is what is passed invariably.

GameObject* game struct holding pointers to the variables used in the game defined above.
*/
int shutdownGET_R(U_Request_t* request, struct _u_response* response, void* input);

// TTTGAME.C

/*
This function takes a board and sets the number of empties variable.

GameObject* game struct holding pointers to the variables used in the game defined above.
*/

void getEmptyCount_ttt(GameObject* game);

/*
This function is called by the /init endpoint to initialize and empty board and randomly
determine if the computer goes first or not.

GameObject* game struct holding pointers to the variables used in the game defined above.
*/
void initGame_ttt(GameObject* game);

/*This function is called by the /move endpoint. It takes a board and etermines where the
computer will place it's move.

GameObject* game struct holding pointers to the variables used in the game defined above.

return int 0 if the function successfully found a move and 1 if there was something wrong.
*/
int computerMove(GameObject* game);


/// JSON.C

/*
This function takes in a JSON root and sets the appropriate variables in the game object
based on the input from the client.

GameObject* game struct holding pointers to the variables used in the game defined above.

return int 0 if the parse was successful and 1 if there was an error.
*/
int parseJSON(GameObject* game);

/*
This function takes in a JSON root and sets the appropriate variables in the game object
based on the input from the client.

GameObject* game struct holding pointers to the variables used in the game defined above.

return int 0 if the parse was successful and 1 if there was an error.
*/
int parseBoardJSON(GameObject* game);

/*
This function takes the data from the game struct and encodes a json_t object that can be
sent back to the client.

GameObject* game struct holding pointers to the variables used in the game defined above.
*/
void encodeJSON(GameObject* game);

/*
This function takes the data from the game struct and encodes a json_t object that can be
sent back to the client. This one is specifically designed for hte initialization of the
game.

GameObject* game struct holding pointers to the variables used in the game defined above.
*/
void initEncodeJSON(GameObject* game);

#endif