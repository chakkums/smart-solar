package server;

import java.io.IOException;
import java.net.ServerSocket;
import java.net.Socket;

public class ServerMain {
	private static int port = 6100;
	
	public static void main(String[] args) throws IOException{
		ServerSocket sock = new ServerSocket(port);
		Socket client;
		
		// now listen for connections
				while (true) {
					System.out.println("Server listening for more connections on port " + port + "...\n");
					client = sock.accept();

					System.out.println("Just connected to client on port " + port  + " on " + new java.util.Date().toString() + ".");
					
					//No limit on number of threads that can be created - could use a thread pool.
					new Thread(new ServiceRequest(client)).start();	
				}
				

	}

}
