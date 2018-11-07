package main.game;

public class Board  implements IBoard{

  public static final int BOARDSIZE = 9;

  private Integer[] board = new Integer[BOARDSIZE];


  public Board() { }

  public Integer[] getBoard() { return board; }

  /**
   * This method prints a board.
   */
  @Override
  public void printBoard() {
    System.out.println("\n\n|-1-----2-----3-|");
    for (int i = 0; i < BOARDSIZE; i++){
      if(i % 3 == 0 &&  i > 0) {
        System.out.println((i+1)/3 + "\n|---------------|");
      }
      System.out.print("| ");
      if(board[i] == 0)
        System.out.print( "- | ");
      else if (board[i] == 1)
        System.out.print("O | ");
      else
        System.out.print("X | ");
    }
    System.out.println( "3\n|---------------|\n");
  }

  /**
   * @return true if the board is full false otherwise.
   */
  @Override
  public Boolean isBoardFull() {
    for (int i = 0; i < BOARDSIZE; i++){
      if (board[i] == 0){
        return false;
      }
    }
    System.out.println("The game is a tie!");
    return true;
  }

  /**
   * @return true if there is a winner and false otherwise.
   */
  public Boolean checkForWinner() {
    return (rowMatcher() || columnMatcher() || diagMatcher());
  }

  private Boolean rowMatcher(){
    for(int i = 0; i < BOARDSIZE/3; i++){
      if(checker(board[i*3], board[i*3+1], board[i*3+2])){
        if(board[i*3] == 2) {
          System.out.println("Player Won! row matcher");
        } else {
          System.out.println("Computer Won!");
        }
        return true;
      }
    }
    return false;
  }

  private Boolean columnMatcher(){
    for(int i = 1; i < BOARDSIZE/3; i++){
      if(checker(board[2-i], board[5-i], board[8-i])){
        if(board[2-i] == 2) {
          System.out.println("Player Won!");
        } else {
          System.out.println("Computer Won!");
        }
        return true;
      }
    }
    return false;
  }

  private Boolean diagMatcher(){
    if (checker(board[0], board[4], board[8]) ||
        checker(board[2],board[4], board[6])){
      if(board[4] == 2) {
        System.out.println("Player Won!");
      } else {
        System.out.println("Computer Won!");
      }
      return true;
    }
    return false;
  }

  private Boolean checker(Integer a, Integer b, Integer c){
    return ((a != 0) && (a.equals(b)) && (b.equals(c)));
  }

}
