package main.json;

import com.google.gson.Gson;
import com.google.gson.GsonBuilder;
import main.Components;
import main.game.Board;
import main.game.Game;

public class JSONProcessor {

  Components c;
  protected Gson gson;

  public JSONProcessor(Components c)  {
    this.c = c;
    this.gson = new GsonBuilder().create();

  }

  public Game jsonToGame(String json){
    return gson.fromJson(json, Game.class);
  }

  public Board jsonToBoard(String json) { return gson.fromJson(json, Board.class); }

  public String gameToJSON(Game game){
    return gson.toJson(game);
  }

  public String boardToJSON(Board board){
    return gson.toJson(board);
  }
}
