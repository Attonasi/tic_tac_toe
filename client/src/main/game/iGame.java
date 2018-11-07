package main.game;

import main.sysin.InputProcessor;

import java.io.IOException;

public interface iGame {

  /**
   * main.game.Game contains thefields board, Player, and XoO. The methods below control a main.game of
   * main.tictactoe
   */

  /**
   * This method takes the board initialized by the server and takes input from the player to choose
   * X or O and .
   */
  void initializeGame(InputProcessor playerInput) throws IOException;


  /**This method attempts to place the players mark in a square.
   *
   * @param row row number for the potential play.
   * @param column column number for hte potential play.
   * @return true if it was a legal move and a mark was placed, false otherwise.
   */
  Boolean playerMove(int row, int column);
}
