import java.io.DataInputStream;
import java.io.IOException;
import java.text.DecimalFormat;
import java.util.ArrayList;

public class TestAlgorithms {

	static boolean normalSystemFailed = false;
	static boolean SOHSystemFailed = false;
	
	static int minimumBatteriesToServeVillage = 55;
	static int numberOfBatteries = 65;
	/**
	 * @param args
	 * @throws InterruptedException 
	 * @throws IOException 
	 */
	public static void main(String[] args) throws InterruptedException, IOException {
		ArrayList<Battery> batteries = new ArrayList<Battery>();
		// Create new batteries
		for(int i=0;i<numberOfBatteries;i++){
			batteries.add(new Battery(i+1, 0, false));
		}
		ChargingStation ChargingStationUsingSOH = new ChargingStation(batteries, minimumBatteriesToServeVillage);
		
		ArrayList<Battery> batteries2 = new ArrayList<Battery>();
		// Create 6 new batteries
		for(int i=0;i<numberOfBatteries;i++){
			batteries2.add(new Battery(i+1, 0, false));
		}
		ChargingStation ChargingStationNormal = new ChargingStation(batteries2, minimumBatteriesToServeVillage);
		
		ArrayList<Battery> batteries3 = new ArrayList<Battery>();
		// Create 6 new batteries
		for(int i=0;i<numberOfBatteries;i++){
			batteries3.add(new Battery(i+1, 0, false));
		}
		ChargingStation ChargingStationUsingRandom = new ChargingStation(batteries3, minimumBatteriesToServeVillage);
		
		System.out.println("Charging Stations created...");
		Thread.sleep(2000);
		
		// Now we have two identical charging stations to run tests on.
		simulateUse(ChargingStationNormal,ChargingStationUsingSOH,ChargingStationUsingRandom);
	}
	private static void simulateUse(ChargingStation chargingStationNormal,
			ChargingStation chargingStationUsingSOH, ChargingStation chargingStationUsingRandom) throws InterruptedException, IOException {
		DataInputStream din = new DataInputStream(System.in);
			System.out.println("Running 80% usage simulation...");
			Thread.sleep(2000);
			int normalDayFailed = chargingStationNormal.simulateUse(0);
			System.out.println("*********SYSTEM FAILED***********");
			System.out.println("Day: " + normalDayFailed);
			System.out.println("*********************************");
			din.readLine();
			System.out.println("Running random allocation simulation...");
			Thread.sleep(2000);
			int randomDayFailed = chargingStationUsingRandom.simulateUse(2);
			System.out.println("*********SYSTEM FAILED***********");
			System.out.println("Day: " + randomDayFailed);
			System.out.println("*********************************");
			din.readLine();
			System.out.println("Running state of health simulation...");
			Thread.sleep(2000);
			int SOHDayFailed = chargingStationUsingSOH.simulateUse(1);
			System.out.println("*********SYSTEM FAILED***********");
			System.out.println("Day: " + SOHDayFailed);
			System.out.println("*********************************");
			din.readLine();		
			
			System.out.println("\n*************REPORT**************");
			System.out.println("80% usage failed: " + normalDayFailed);
			System.out.println("Random allocation failed: " + randomDayFailed);
			System.out.println("SOH allocation failed: " + SOHDayFailed);
			
			int normalGain = SOHDayFailed - normalDayFailed;
			DecimalFormat df = new DecimalFormat("#.##");
			double percentageGain = ((double)normalGain/(double)normalDayFailed)*100;
			
			System.out.println("\nSOH gain over 80% usage: " + normalGain + " (" + df.format(percentageGain) + "%)");
			
			int randomGain = SOHDayFailed - randomDayFailed;
			percentageGain = ((double)randomGain/(double)randomDayFailed)*100;
			
			System.out.println("SOH gain over random allocation: " + randomGain + " (" + df.format(percentageGain) + "%)");
			
			System.out.println("\nThe simulated test systems had "+ numberOfBatteries +" identical batteries, with a minimum of " 
					+ minimumBatteriesToServeVillage+ " required to \nserve the village, the system was regarded " +
							"to have failed when it could no \nlonger meet the requirements of the village.");
			
			System.out.println("\nAssumptions:");
			System.out.println("1. Batteries can be returned and charged in the same day.");
			System.out.println("2. Number of cycles is the sole factor in state of health.");
			System.out.println("3. Batteries are returned as soon as empty, and are subjected to the same usage.");
		}
			
}
