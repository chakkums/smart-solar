import java.sql.Connection;
import java.sql.DriverManager;
import java.sql.ResultSet;
import java.sql.SQLException;
import java.sql.Statement;
import java.text.DateFormat;
import java.text.DecimalFormat;
import java.text.SimpleDateFormat;
import java.util.Calendar;


public class createString {

	/**
	 * @param args
	 * @throws ClassNotFoundException
	 * @throws SQLException
	 */
	public static void main(String[] args) throws ClassNotFoundException,
			SQLException {
		String host = "jdbc:mysql://localhost:3306/";
		String dbName = "smartsolar";
		String username = "root";
		String password = "";
		String url = host + dbName + "?user=" + username + "&password="
				+ password;

		Class.forName("com.mysql.jdbc.Driver");
		Connection conn = DriverManager.getConnection(url);

		Statement stat = conn.createStatement();

		DecimalFormat df = new DecimalFormat("00");
		DecimalFormat df3 = new DecimalFormat("000");
		DecimalFormat df4 = new DecimalFormat("0000");
		ResultSet rs = stat
				.executeQuery("SELECT batteryID from batteries WHERE location = 'Sambel Kunda'");
		int count = -1;
		do {
			count++;
		} while (rs.next());
		String sendString = "[SK020413:" + df.format(count) + "[";
		rs = stat
				.executeQuery("SELECT irradiance, temperature  from environment WHERE location = 'Sambel Kunda' AND DATE(datetime) = '2013-03-24'");
		while (rs.next()) {
			sendString += df4.format(rs.getDouble(1) * 10 + randBetween(0, 5))
					+ ":"
					+ df3.format(rs.getDouble(2) * 10 + randBetween(0, 3))
					+ ",";
		}
		sendString += "]";

		rs = stat
				.executeQuery("SELECT batteryID, numberOfCycles, withCustomer  from batteries WHERE location = 'Sambel Kunda'");
		while (rs.next()) {
			sendString += "[" + rs.getString(1) + ":04:"
					+ df4.format(rs.getInt(2)) + ":"
					+ df.format(randBetween(1, 2)) + "0413"
					+ randBetween(10, 23) + randBetween(10, 59) + ":"
					+ df3.format(randBetween(60, 700)) + ":"
					+ randBetween(0, 1);

			sendString += "[";

			DateFormat sdf = new SimpleDateFormat("ddMMYYHHmm");
			Calendar cal = Calendar.getInstance();
			cal.set(2013, 3, 1, 0, 0, 0);

			double chargeLevel = randBetween(50, 100);
			int numberOfSamples = 1;
			while (numberOfSamples <= 4) {
				// Simulate a charge cycle
				int timeOn = randBetween(10, 500); // between 10 mins and 8.3
													// hours
				String timeLoadOn = sdf.format(cal.getTime());

				double startChargeLevel = chargeLevel;

				cal.add(Calendar.MINUTE, timeOn);

				chargeLevel = chargeLevel - (double) timeOn
						/ (10 + (randBetween(0, 4)));

				double endChargeLevel = chargeLevel;

				if (endChargeLevel < 0) {
					chargeLevel = 100;
					endChargeLevel = 0;
					int timeToCharge = randBetween(500, 700);
					cal.add(Calendar.MINUTE, timeToCharge);
				}

				// Add time between load applications
				int timeOff = randBetween(50, 120);
				cal.add(Calendar.MINUTE, timeOff);
				double temperature = 25.9 + Math.random() * 3;

				chargeLevel = chargeLevel - randBetween(0, 5) / 10;// not ideal
																	// battery

				sendString += "(" + timeLoadOn + ":" + df3.format(timeOn) + ":"
						+ df3.format(startChargeLevel) + ":"
						+ df3.format(endChargeLevel) + ":"
						+ df3.format(temperature * 10) + ")";

				numberOfSamples++;
			}
			sendString += "]]";

		}

		System.out.println(sendString);

		conn.close();

	}

	public static int randBetween(int start, int end) {
		return start + (int) Math.round(Math.random() * (end - start));
	}


}
