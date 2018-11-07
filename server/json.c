#include "final.h"

int parseJSON(GameObject* game)
{
  printf("Parse JSON: %s\n", game->gc->input);
  game->jd->jp->root_json = json_loads(game->gc->input, 0, &game->jd->error_json);
  if(!game->jd->jp->root_json)
  {
    fprintf(stderr, "error on line %d: %s server\n", game->jd->error_json.line, game->jd->error_json.text);
    return 1;
  }

  game->jd->jp->playerName_json = json_object_get(game->jd->jp->root_json, game->jd->jk->player_j);
  strcpy(game->gd->playerName, json_string_value(game->jd->jp->playerName_json));
  printf("parseJSON: %s name\n", game->gd->playerName);

  game->jd->jp->board_json = json_object_get(game->jd->jp->root_json, game->jd->jk->board_j);

  if(json_is_array(game->jd->jp->board_json))
  {
    for (int i = 0; i < json_array_size(game->jd->jp->board_json); i++)
    {
      game->gd->board[i] = json_integer_value(json_array_get(game->jd->jp->board_json, i));
      printf("%d board[%d]\n", game->gd->board[i], i);
    }
  }
  return 0;
}

int parseBoardJSON(GameObject* game){

  printf("Parse Board JSON: %s\n", game->gc->input);
  game->jd->jp->root_json = json_loads(game->gc->input, 0, &game->jd->error_json);
  if(!game->jd->jp->root_json)
  {
    fprintf(stderr, "error on line %d: %s server\n", game->jd->error_json.line, game->jd->error_json.text);
    return 1;
  }

  game->jd->jp->board_json = json_object_get(game->jd->jp->root_json, game->jd->jk->board_j);

  if(json_is_array(game->jd->jp->board_json))
  {
    for (int i = 0; i < json_array_size(game->jd->jp->board_json); i++)
    {
      game->gd->board[i] = json_integer_value(json_array_get(game->jd->jp->board_json, i));
    }
  }
  return 0;
}


void encodeJSON(GameObject* game)
{
  printf("Start Encode JSON\n");
  game->jd->jp->playerName_json = json_string(game->gd->playerName);
  game->jd->jp->board_json = json_array();

  for (int i = 0; i < BOARDSIZE; i++)
  {
    json_array_append_new(game->jd->jp->board_json, json_integer(game->gd->board[i]));
  }

  printf("Set Pointers\n");

  json_object_set(game->jd->jp->root_json, game->jd->jk->player_j, game->jd->jp->playerName_json);
  json_object_set(game->jd->jp->root_json, game->jd->jk->board_j, game->jd->jp->board_json);

  printf("Set Objects\n");

  char* json_dump = json_dumps(game->jd->jp->root_json, JSON_ENCODE_ANY);
  int dump_len = strlen(json_dump);

  printf("dump: %s %d length\n", json_dump, dump_len);

  for (int i = 0; i < dump_len; i++)
  {
    game->gc->output[i] = json_dump[i];
  }
  game->gc->output[dump_len] = 0;

  printf("EncodeJSON out:%s\n", game->gc->output);
}

void initEncodeJSON(GameObject* game){

  printf("Start Init Encode\n");
  game->jd->jp->board_json = json_array();

  for (int i = 0; i < BOARDSIZE; i++)
  {
    json_array_append_new(game->jd->jp->board_json, json_integer(game->gd->board[i]));
  }

  json_object_set(game->jd->jp->root_json, game->jd->jk->board_j, game->jd->jp->board_json);

  char* json_dump = json_dumps(game->jd->jp->root_json, JSON_ENCODE_ANY);
  int dump_len = strlen(json_dump);

  printf("dump: %s  %d length\n", json_dump, dump_len);

  for (int i = 0; i < dump_len; i++)
  {
    game->gc->output[i] = json_dump[i];
  }
  game->gc->output[dump_len] = 0;
}