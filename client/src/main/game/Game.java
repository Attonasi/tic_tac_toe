package main.game;

import main.sysin.InputProcessor;

import java.io.IOException;

public class Game implements iGame{


  private Board board;
  private String playerName;
  private InputProcessor playerInput;

  public Game(InputProcessor playerInput) throws IOException {
    this.playerInput = playerInput;
    initializeGame(playerInput);
    this.board = new Board();
  }

  public void setBoard(Board newBoard) { this.board = newBoard; }

  public Board getBoard(){ return this.board; }

  /**
   * This method takes the board initialized by the server and takes input from the player to choose
   * X or O and .
   */
  public void initializeGame(InputProcessor playerInput) throws IOException {

    System.out.println("Please enter your name:");
    playerName = playerInput.readLine();

  }

  /**
   * This method attempts to place the players mark in a square.
   *
   * @param row    row number for the potential play.
   * @param column column number for the potential play.
   * @return false if it was a legal move and a mark was placed, True if the player needs
   * to enter valic input.
   */
  @Override
  public Boolean playerMove(int row, int column) {


    if (row > 2 || row < 0 || column > 2 || column < 0){
      System.out.println("Please enter 1, 2, or 3 for the row and column.");
      return true;
    }
    if(board.getBoard()[((row+1) * 3 - 3) + column] == 0){
      board.getBoard()[((row+1) * 3 - 3) + column] = 2;
      return false;
    }
    System.out.println("That square is already marked. Try again.");
    return true;
  }

  public void getMove() throws IOException {

    int row = -1;
    int column = -1;

    while (playerMove(row, column)){

      System.out.print(playerName + ", please enter the row number:");
      row = Character.getNumericValue(playerInput.readChar()) - 1;
      System.out.print(playerName + ", please enter the column number:");
      column = Character.getNumericValue(playerInput.readChar()) - 1;
    }

    System.out.println("\n" + playerName + " has marked square " + (row+1) + ", " + (column+1) + "!\n");
  }

}
