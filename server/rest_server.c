#include "final.h"

int shutdownGET_R(U_Request_t* request, struct _u_response* response, void* input)
{
  GameObject* game = (GameObject*) input;
  game->sv->serverStatus = 0;
  printf("SHUTTING DOWN THE SERVER\n");
  return U_CALLBACK_COMPLETE;
}

void INITIATE_R(GameObject* game)
{
  if(ulfius_init_instance(&game->sv->instance, game->sv->port, NULL, NULL) != U_OK)
  {
    printf("Error initializing server of port %d line 8 rest_server.c\n", PORT);
  } else {
    printf("Instance initiated on port: %d\n", game->sv->instance.port);
  }

  ulfius_add_endpoint_by_val(&game->sv->instance, "GET", "/init", NULL, 0, &initGameGET_R, game);

  ulfius_add_endpoint_by_val(&game->sv->instance, "POST", "/move", NULL, 0, &processMovePOST_R, game);

  ulfius_add_endpoint_by_val(&game->sv->instance, "GET", "/shutdown", NULL, 0, &shutdownGET_R, game);

  if(ulfius_start_framework(&game->sv->instance) == U_OK)
  {
    printf("Start Server port: %d\n", game->sv->instance.port);

    while(game->sv->serverStatus == 1)
    {
      sleep(10);
      printf("curl -XGET localhost:8080/shutdown to close server\n");
    }
  } else {
    printf("Error starting Instance line 36 rest_server.c\n");
  }

  printf("The server has closed and stuff is going to be freed\n");

  ulfius_stop_framework(&game->sv->instance);
  ulfius_clean_instance(&game->sv->instance);
}

int initGameGET_R(U_Request_t* request, struct _u_response* response, void* input)
{

  GameObject* game = (GameObject*) input;

  printf("called initGameGET_r! stuff: %s\n", game->gc->input);

  initGame_ttt(game);
  printf("Ran Init Game\n");
  initEncodeJSON(game);
  printf("Encoded JSON\n");

  ulfius_set_string_body_response(response, 200, game->gc->output);

  return U_CALLBACK_CONTINUE;
}

int processMovePOST_R(U_Request_t* request, struct _u_response* response, void* input)
{
  GameObject* game = (GameObject*) input;

  strcpy(game->gc->input, request->binary_body);
  game->gc->input[request->binary_body_length] = 0;

  printf("Called process move! input: %s\n", game->gc->input);

  game->jd->jp->root_json = ulfius_get_json_body_request(request, &game->jd->error_json);
  if(game->jd->jp->root_json == NULL)
  {
    printf("problem with setting root line 59 rest_server\n");
    printf("json error: %s\n", game->jd->error_json.text);
  }

  parseBoardJSON(game);

  printf("Parsed JSON\n");

  int moveResult = computerMove(game);

  printf("%d move result computer move\n", moveResult);

  initEncodeJSON(game);

  printf("Encoded JSON\n");


  ulfius_set_string_body_response(response, 200, game->gc->output);

  return U_CALLBACK_CONTINUE;
}