package main;

import main.game.Game;
import main.json.JSONProcessor;
import main.sysin.InputProcessor;
import org.apache.http.client.HttpClient;
import org.apache.http.impl.client.DefaultHttpClient;

import java.io.IOException;

public class Components {

  protected static final String URL = "http://localhost:8080";
  protected static final String PORT = ":8080";
  protected static final String INIT = "/init";
  protected static final String MOVE = "/move";

  protected InputProcessor playerInput = new InputProcessor(System.in);

  protected HttpClient client = new DefaultHttpClient();

  protected Game game = new Game(playerInput);

  protected JSONProcessor jProc = new JSONProcessor(this);

  public Components() throws IOException {}

  public Game getGame() { return game; }
}

