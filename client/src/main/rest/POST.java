package main.rest;

import org.apache.http.client.HttpClient;

public class POST extends AbsRESTRequest {

  /** The only purpose of this class is to force the user to understand they are
   * making a new POST.
   *
   * @param client HTTPClient used in every RESTRequest.
   * @param host String representing the domain name. "http://[something]"
   * @param port String representing the port number of the server.
   * @param flag String matching the REST endpoint on the server the instance of this
   *             class targets.
   */
  public POST(HttpClient client, String host, String port, String flag) {
    super(client, host, port, flag);
  }
}
