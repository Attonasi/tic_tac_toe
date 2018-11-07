package main.rest;

import java.io.IOException;

public interface RESTRequest {

  /**
   * @return String the JSON response from the server. A board with a 50/50 shot at
   * the center square being marked.
   * @throws IOException
   */
  String GET() throws IOException;

  /**
   * @param json String formatted to JSON that is sent in the POST request as the
   *             entity to the server.
   * @return String the JSON response from the server. The server will take the board
   * mark the appropriate square for it's play.
   * @throws IOException
   */
  String POST(String json) throws IOException;
}
