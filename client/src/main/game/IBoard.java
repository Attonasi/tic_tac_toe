package main.game;

public interface IBoard {

  /**
   * This method prints a board.
   */
  void printBoard();


  /**
   * @return true if the board is full false otherwise.
   */
  Boolean isBoardFull();

  /**
   * @return true if there is a winner and false otherwise.
   */
  Boolean checkForWinner();
}
