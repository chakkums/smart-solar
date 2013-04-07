import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.net.*;
import java.sql.*;



/**
 * Server class used to listen for connections from
 * GSM modem over a TCP connection.
 * 
 * @author Daniel Chakraverty 200906954
 */
public class Server {
	private static int port = 6100;
	
	public static void main(String[] args) throws IOException, InterruptedException, ClassNotFoundException, SQLException {
		//Creates a new ServerSocket on the port specified
		
		String	host	=	"jdbc:mysql://localhost:3306/";
		String	dbName	=	"test";
		String	username	=	"root";
		String	password	=	"";
		String	url	=	host	+	dbName	+	"?user="	+	username	+	"&password="	+	password;

		
		ServerSocket sock = new ServerSocket(port); 
		
		Socket client; //Socket of connected client
		
		while(true){
			System.out.println("Server listening for connections on port " + port + "...\n");
			client = sock.accept();

			System.out.println("Just connected to client on port " + port  + " on " + new java.util.Date().toString() + ".");
			
			InputStream in = client.getInputStream();
			BufferedReader bin = new BufferedReader(new InputStreamReader(in));
			
			String message;
			
			message = bin.readLine();
			
			System.out.println("\t*******Start of message*********");
			System.out.println("\t" +  message);
			System.out.println("\t*******End of message***********\n");
	
			client.close();
			System.out.println("Connection terminated with client.\n");
			
			Class.forName("com.mysql.jdbc.Driver");
			Connection conn = DriverManager.getConnection(url);
			
			System.out.println("Parsing received string...");
			if(message != null){
			String timeString = message.substring(7);
			System.out.println("Data: " + timeString);
			
			System.out.println("Inserting data into SQL database...");
			Statement stat = conn.createStatement();
			stat.execute("INSERT INTO time (time) VALUE (" + timeString +")");
			
			System.out.println("Done.\n");
			conn.close();
			}else{
				System.out.println("No data in message, skipping...");
			}
			
		}	
	}

}
