package main.sysin;

public interface InputProcessorI {


  /**
   * @return String The first line of text from the bufferReader.
   * @throws Exception
   */
  String readLine() throws Exception;

  /**
   * @return Char the first character off the bufferReader.
   * @throws Exception
   */

  Character readChar() throws Exception;
}
