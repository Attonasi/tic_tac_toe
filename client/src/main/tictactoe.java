package main;

import main.rest.GET;
import main.rest.POST;
import main.rest.RESTRequest;

import java.io.IOException;

public class tictactoe {

  public static void main(String args[]) throws IOException {

    Components c = new Components();
    RESTRequest initGET = new GET(c.client, c.URL, c.PORT, c.INIT);
    RESTRequest movePOST = new POST(c.client, c.URL, c.PORT, c.MOVE);


    c.game.setBoard(c.jProc.jsonToBoard(initGET.GET()));

    while(c.game.getBoard().checkForWinner() ? false : !(c.game.getBoard().isBoardFull())) {

      c.game.getBoard().printBoard();

      c.game.getMove();

      c.game.getBoard().printBoard();

      if(c.game.getBoard().checkForWinner() ? false : !(c.game.getBoard().isBoardFull())){

        c.game.setBoard(c.jProc.jsonToBoard(movePOST.POST(c.jProc.boardToJSON(c.game.getBoard()))));
      }
    }
    c.game.getBoard().printBoard();
    System.out.println("Game Over man! Game Over!");
  }
}
