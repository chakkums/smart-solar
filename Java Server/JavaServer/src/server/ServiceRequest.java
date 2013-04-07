package server;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;
import java.io.OutputStream;
import java.io.PrintStream;
import java.net.Socket;
import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;
import java.text.DateFormat;
import java.text.SimpleDateFormat;
import java.util.Calendar;
import java.util.Scanner;

public class ServiceRequest implements Runnable {
	InputStream in = null;
	BufferedReader bin = null;
	Socket client = null;

	 public ServiceRequest(Socket client) {
	 this.client = client;
	 }



	@Override
	public void run() {

		String host = "jdbc:mysql://localhost:3306/";
		String dbName = "smartsolar";
		String username = "root";
		String password = "";
		String url = host + dbName + "?user=" + username + "&password="
				+ password;

		try {
			Class.forName("com.mysql.jdbc.Driver");
		} catch (ClassNotFoundException e) {
			e.printStackTrace();
		}
		Connection conn = null;
		try {
			conn = DriverManager.getConnection(url);
			System.out.println("Connected to SQL database.");
		} catch (SQLException e) {
			e.printStackTrace();
		}

		Statement stat = null;
		try {
			stat = conn.createStatement();
		} catch (SQLException e) {
			e.printStackTrace();
		}

		// Reading message
		InputStream in = null;
		try {
			in = client.getInputStream();
		} catch (IOException e1) {
			e1.printStackTrace();
		}
		Scanner scan = new Scanner(new InputStreamReader(in));
		
		String message;
		
		message = scan.useDelimiter("\\;").next();


		System.out.println("*******Start of message*********");
		System.out.println("" + message);
		System.out.println("*******End of message***********\n");

		// LOCATIONS
		String chargeStationInfo = message.substring(1, 12);
		String locID = chargeStationInfo.substring(0, 2);

		String location = "";
		if (locID.equals("SK")) {
			location = "Sambel Kunda";
		} else {
			location = "Kudang";
		}
		DateFormat sdf = new SimpleDateFormat("yyyy-MM-dd HH:mm:ss");

		Calendar lastUpdated = Calendar.getInstance(); // Initialises with NOW
														// (last updated time)

		// UPDATE SQL LOCATIONS (LOCATION AND LAST UPDATED
		System.out.println("Updating location data in SQL database.");
		try {
			stat.executeUpdate("UPDATE `locations` SET `lastUpdated`='"
					+ sdf.format(lastUpdated.getTime()) + "' WHERE `name` ="
					+ "'" + location + "'");
		} catch (SQLException e) {
			e.printStackTrace();
		}

		int numberOfBatteries = Integer.parseInt(chargeStationInfo.substring(9,
				11));

		// ENVIRONMENT
		int year = 2000 + Integer.parseInt(chargeStationInfo.substring(6, 8));
		int month = Integer.parseInt(chargeStationInfo.substring(4, 6));
		int day = Integer.parseInt(chargeStationInfo.substring(2, 4));

		Calendar environment = Calendar.getInstance();
		environment.set(year, month - 1, day, 0, 0, 0); // Set to midnight on
														// the day that data is
														// for

		String environmentData = message.substring(12, 229); // Start at 12, 24
																// samples of 9
																// bytes
		
		System.out.println("Updating environment data in SQL database.");

		int sampleCount = 0;// Counts which sample we are at, add this
							// multiplied by 9 to each index
		for (int i = 0; i < 24; i++) {// 24 hours worth of data (24 samples)
			double irradiance = Double.parseDouble(environmentData.substring(
					1 + 9 * sampleCount, 5 + 9 * sampleCount)) / 10;
			double temp = Double.parseDouble(environmentData.substring(
					6 + 9 * sampleCount, 9 + 9 * sampleCount)) / 10;
			// UPDATE SQL ENVIRONMENT DATA HERE

			 try {
			 stat.execute("INSERT INTO environment (`index`,`location`,`datetime`,`temperature`,`irradiance`) VALUES "
			 +
			 "(NULL,'" + location +"','" + sdf.format(environment.getTime()) +
			 "','" + temp + "','" + irradiance + "')");
			 } catch (SQLException e) {
			 e.printStackTrace();
			 }

			environment.add(Calendar.HOUR, 1); // Add an hour to the sample, as
												// samples taken on the hour
			sampleCount++;
		}

		// BATTERIES
		int startOfBatteryInfo = 229; // end of environment data
		for (int i = 0; i < numberOfBatteries; i++) {
			int endOfBatteryInfo = message.indexOf(']', startOfBatteryInfo) + 2;// +2
																				// include
																				// that
																				// char
			String batteryInfo = message.substring(startOfBatteryInfo,
					endOfBatteryInfo);

			String batteryID = batteryInfo.substring(1, 12);

			String batLocation = "";
			if (batteryID.substring(0, 2).equals("SK")) {
				batLocation = "Sambel Kunda";
			} else if (batteryID.substring(0, 2).equals("KD")) {
				batLocation = "Kudang";
			}

			String numberString = batteryID.substring(2, 4);
			int number = Integer.parseInt(numberString);

			String type = "";
			if (batteryID.substring(4, 6).equals("PB")) {
				type = "Lead Acid";
			} else if (batteryID.substring(4, 6).equals("LI")) {
				type = "Lithium Ion";
			}

			int recommendedCycles = 0;
			String recString = batteryID.substring(6, 10);
			recommendedCycles = Integer.parseInt(recString);

			int initialCapacity = 0;
			char initString = batteryID.charAt(10);
			initialCapacity = Integer.parseInt(Character.toString(initString));

			int numberOfCycles = Integer
					.parseInt(batteryInfo.substring(16, 20));

			// CALCULATING STATE OF HEALTH AND AVAILABLE CAPACITY
			double stateOfHealth = (1 - ((double) numberOfCycles / (double) recommendedCycles)) * 100;

			// AUTOMATIC DISABLING
			int disabled = 0;
			if (stateOfHealth < 10) {
				disabled = 1;
			}

			double availableCapacity = initialCapacity * (stateOfHealth / 100);

			int chgedYear = 2000 + Integer.parseInt(batteryInfo.substring(25,
					27));
			int chgedMonth = Integer.parseInt(batteryInfo.substring(23, 25));
			int chgedDay = Integer.parseInt(batteryInfo.substring(21, 23));
			int chgedHour = Integer.parseInt(batteryInfo.substring(27, 29));
			int chgedMin = Integer.parseInt(batteryInfo.substring(29, 31));

			Calendar lastCharged = Calendar.getInstance();

			lastCharged.set(chgedYear, chgedMonth - 1, chgedDay, chgedHour,
					chgedMin, 0);


			String timeToCharge = batteryInfo.substring(32, 35);

			char withCustomer = batteryInfo.charAt(36);

			// UPDATE BATTERYID WITH CURRENT DATA IN SQL
			System.out.println("Updating battery data in SQL database for battery: " +batteryID);

			try {
				stat.executeUpdate("UPDATE `batteries` SET `batteryID`='"
						+ batteryID + "', " + "`location`='" + location + "', "
						+ "`number`='" + number + "', " + "`type`='" + type
						+ "', " + "`recommendedCycles`='" + recommendedCycles
						+ "', " + "`numberOfCycles`='" + numberOfCycles + "', "
						+ "`initialCapacity`='" + initialCapacity + "', "
						+ "`timeCharged`='" + sdf.format(lastCharged.getTime())
						+ "', " + "`timeTakenToCharge`='" + timeToCharge
						+ "', " + "`stateOfHealth`='" + stateOfHealth + "', "
						+ "`availableCapacity`='" + availableCapacity + "', "
						+ "`withCustomer`='" + withCustomer + "', "
						+ "`disabled`='" + disabled + "' "
						+ "WHERE `batteryID` ='" + batteryID + "'");
			} catch (SQLException e) {
				e.printStackTrace();
			}

			System.out.println("Updating load data in SQL database for battery: " +batteryID);

			// LOAD DATA
			int numberOfSamples = Integer.parseInt(batteryInfo
					.substring(13, 15));

			int startOfSamples = 37; // Always will be [
			int endOfSamples = batteryInfo.indexOf(']') + 1;// Marks end of
															// samples
			String samples = batteryInfo
					.substring(startOfSamples, endOfSamples);

			int sampleStart = 1;
			for (int j = 0; j < numberOfSamples; j++) {
				int sampleEnd = samples.indexOf(')', sampleStart) + 1;// End of
																		// sample
				String currentSample = samples
						.substring(sampleStart, sampleEnd);

				int ldYear = 2000 + Integer.parseInt(currentSample.substring(5,
						7));
				int ldMonth = Integer.parseInt(currentSample.substring(3, 5));
				int ldDay = Integer.parseInt(currentSample.substring(1, 3));
				int ldHour = Integer.parseInt(currentSample.substring(7, 9));
				int ldMin = Integer.parseInt(currentSample.substring(9, 11));

				Calendar time = Calendar.getInstance();

				time.set(ldYear, ldMonth - 1, ldDay, ldHour, ldMin, 0);
				String startTime = sdf.format(time.getTime());

				int timeOn = Integer.parseInt(currentSample.substring(12, 15));

				time.add(Calendar.MINUTE, timeOn);

				String endTime = sdf.format(time.getTime());

				int startChargeLevel = Integer.parseInt(currentSample
						.substring(16, 19));
				int endChargeLevel = Integer.parseInt(currentSample.substring(
						20, 23));

				double temperature = Double.parseDouble(currentSample
						.substring(24, 27)) / 10;

				double chargeDepleted = startChargeLevel - endChargeLevel;

				double averageLoad = ((chargeDepleted / 100) * availableCapacity)
						/ ((double) timeOn / 60); // hours

				// UPDATE LOAD DATA SAMPLE USING BATTERY ID
				try {
					stat.execute("INSERT INTO loaddata (`index`,`batteryID`,`location`,`timeLoadOn`,`startChargeLevel`"
							+ ",`timeLoadOff`,`timeOn`,`endChargeLevel`,`temperature`,`averageLoad`) VALUES "
							+ "(NULL,'"
							+ batteryID
							+ "','"
							+ location
							+ "','"
							+ startTime
							+ "','"
							+ startChargeLevel
							+ "','"
							+ endTime
							+ "',"
							+ "'"
							+ timeOn
							+ "','"
							+ endChargeLevel
							+ "','"
							+ temperature
							+ "','"
							+ averageLoad + "')");
				} catch (SQLException e) {
					e.printStackTrace();
				}

				sampleStart = sampleEnd;// Get next one
			}
			startOfBatteryInfo = endOfBatteryInfo; // get next one
		}

		// READ SOH AND DISABLED STATUS INTO A STRING,
		// [(batteryID,SOH,Disabled)(etc and send back)]

		try {
			Thread.sleep(3000);
		} catch (InterruptedException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		OutputStream os = null;
		try {
			os = client.getOutputStream();
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}
		PrintStream oos = new PrintStream(os);
		
		System.out.println("\nGenerating return message, reading SOH and disabled status");
		
		//return message needs to be sent as strings of length 55, terminated with \n.  The last string should end with ;\n
		 String stringToSend = "";
				 ResultSet rs = null;
				try {
					rs = stat.executeQuery("SELECT number, stateOfHealth, disabled  from `batteries` WHERE location = 'Sambel Kunda'");
				} catch (SQLException e1) {
					// TODO Auto-generated catch block
					e1.printStackTrace();
				}
				 try {
					while(rs.next()){
						 stringToSend += "[" + rs.getString(1) + "," + rs.getString(2) + "," +
					 rs.getString(3) + "]";
					 }
				} catch (SQLException e1) {
					// TODO Auto-generated catch block
					e1.printStackTrace();
				}
		
		  System.out.println("\nSending message object back to client...\n");
		 
		  String remainingString = stringToSend;
		  boolean allSent = false;
		  while(!allSent){
			  if(remainingString.length() > 50){  //55 largest string that can be sent at once, 5 bytes redundancy
				  stringToSend = remainingString.substring(0, 50) + "\n";
				  remainingString = remainingString.substring(50);
				  //SEND stringToSend
				  oos.print(stringToSend);
				  System.out.println("Message "+ stringToSend + " sent on " + new java.util.Date().toString());
				  try {
					Thread.sleep(2000);
				} catch (InterruptedException e) {
					// TODO Auto-generated catch block
					e.printStackTrace();
				}
			  }else{
				  stringToSend = remainingString += ";\n";
				  //SEND stringToSend += ";\n";
				  oos.print(stringToSend);
				  System.out.println("Message "+ stringToSend + " sent on " + new java.util.Date().toString());
				  try {
					Thread.sleep(2000);
				} catch (InterruptedException e) {
					// TODO Auto-generated catch block
					e.printStackTrace();
				}
				  allSent=true;
				  System.out.println(stringToSend);
			  }
		  }
		
		oos.close();
		try {
			os.close();
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}

		try {
			client.close();
		} catch (IOException e) {
			// TODO Auto-generated catch block
			e.printStackTrace();
		}

		System.out.println("Connection terminated with client \n");

	}
}
