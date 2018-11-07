package main.sysin;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;

public class InputProcessor implements InputProcessorI{

  public InputStream stream;
  private InputStreamReader gameReader;
  private BufferedReader bufferReader;

  public InputProcessor(InputStream info) {
    this.stream = info;
    this.gameReader = new InputStreamReader(stream);
    this.bufferReader = new BufferedReader(gameReader);
  }

  public String readLine() throws IOException {
    return bufferReader.readLine();
  }

  public Character readChar() throws IOException {
    return bufferReader.readLine().charAt(0);
  }
}
