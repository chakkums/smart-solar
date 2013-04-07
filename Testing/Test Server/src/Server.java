
import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.ObjectOutputStream;
import java.io.OutputStream;
import java.io.PrintStream;
import java.net.*;
import java.util.Scanner;

/**
 * Server class used to listen for connections from
 * GSM modem over a TCP connection.
 * 
 * @author Daniel Chakraverty 200906954
 */
public class Server {
	private static int port = 6100;
	
	public static void main(String[] args) throws IOException, InterruptedException {
		//Creates a new ServerSocket on the port specified
		ServerSocket sock = new ServerSocket(port); 
		
		Socket client; //Socket of connected client
		
		while(true){
			System.out.println("Server listening for connections on port " + port + "...\n");
			client = sock.accept();

			System.out.println("Just connected to client on port " + port  + " on " + new java.util.Date().toString() + ".");
			
			InputStream in = client.getInputStream();
			Scanner scan = new Scanner(new InputStreamReader(in));
			
			String message;
			
			message = scan.useDelimiter("\\;").next();

			//scan.close();
			
			System.out.println("\t*******Start of message*********");
			System.out.println("\t" +  message);
			System.out.println("\t*******End of message***********\n");
			
			Thread.sleep(3000);
			System.out.println("Sending message object back to client...\n");
			OutputStream os = client.getOutputStream();
			PrintStream oos = new PrintStream(os);
			
			//return message needs to be sent as strings of length 55, terminated with \n.  The last string should end with ;\n
			String stringToSend = "[1,81.8421,0][2,83.3333,0][3,73.1053,0][4,62.6667,0][5,96,0][6,25.5789,0][7,5.75,1][8,38.75,0][9,59.4167,0][10,15.0833,0][11,63.5789,0][12,64.3158,0][13,82.3684,0][14,59.5833,0][15,76.0833,0][16,87.8421,0][17,15.0526,0][18,32.9474,0][19,5.05263,1][20,47.1667,0][21,48.4737,0][22,66.8333,0][23,79,0][24,39,0][25,42.75,0][26,9.57895,1][27,60.8333,0][28,4.31579,1][29,70.5789,0][30,17.4167,0][31,65.9474,0][32,17.4737,0][33,92.1667,0][34,55.4211,0][35,63.5833,0][36,17.8947,0][37,83.1667,0][38,81.1667,0][39,73.5263,0][40,45.8333,0][41,86.0833,0][42,49.9167,0][43,24.0526,0][44,61.75,0][45,67.1667,0][46,10.75,0][47,43.1667,0][48,35.3333,0][49,62.2105,0][50,31.6842,0][51,92.2632,0][52,10.3333,0][53,56.8333,0][54,25.8333,0][55,22.7368,0][56,96,0][57,63.2105,0][58,58.4211,0][59,25.5789,0][60,48.25,0][61,13.6842,0][62,35,0][63,3.84211,1][64,99.5833,0][65,98,0][66,6.47368,1][67,15.7895,0][68,12.9167,0][69,85.0833,0][70,83.9167,0][71,75.1667,0][72,45.3684,0][73,64.4167,0][74,99.5,0][75,52.9167,0][76,16.5,0][77,3.91667,1][78,84.2105,0][79,97.5,0][80,69.4737,0]";

			  String remainingString = stringToSend;
			  boolean allSent = false;
			  while(!allSent){
				  if(remainingString.length() > 50){  //55 largest string that can be sent at once, 5 bytes redundancy
					  stringToSend = remainingString.substring(0, 50) + "\n";
					  remainingString = remainingString.substring(50);
					  //SEND stringToSend
					  oos.print(stringToSend);
					  System.out.println("Message "+ stringToSend + " sent on " + new java.util.Date().toString());
					  Thread.sleep(2000);
				  }else{
					  stringToSend = remainingString += ";\n";
					  //SEND stringToSend += ";\n";
					  oos.print(stringToSend);
					  System.out.println("Message "+ stringToSend + " sent on " + new java.util.Date().toString());
					  Thread.sleep(2000);
					  allSent=true;
					  System.out.println(stringToSend);
				  }
			  }
			
			oos.close();
			os.close();
	
			client.close();


			
			System.out.println("Connection terminated with client.\n");
		}	
	}

}
