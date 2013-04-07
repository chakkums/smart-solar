import java.text.DecimalFormat;
import java.util.ArrayList;
import java.util.Random;

public class ChargingStation {

public ArrayList<Battery> batteries;
private int minimumBatteries;

public ChargingStation(ArrayList<Battery> batteries, int minimumBatteriesToServeVillage) {
	super();
	this.batteries = batteries;
	this.minimumBatteries = minimumBatteriesToServeVillage;
}

public int addBattery(Battery b){
	if(batteries.add(b)){
		return 1;
	}else{
		return 0;
	}
}

/**
 * Recommends the battery ID that should be handed out
 * first from charging station using the state of health field.
 * @return ID of battery to be handed out
*/
public int recommendBatteryUsingSOH(){
	/*
	 * First step is find all batteries
	 * that are not handed out, that are 
	 * charged.
	 */
	ArrayList<Battery> availableBatteries = new ArrayList<Battery>();
	for(int i=0; i<batteries.size(); i++){
		if(!batteries.get(i).isInUse()){
			if(batteries.get(i).isCharged()){
				if(batteries.get(i).getHealth() > 0){
					availableBatteries.add(batteries.get(i));
				}
			}
		}
	}
	
	/*
	 * Now need to see which of those batteries
	 * is in the best health (i.e. should be handed
	 * out to average out wear).
	 */
	if(availableBatteries.size() != 0){
		Battery recommendedBattery = availableBatteries.get(0);
		for(int i=1; i<availableBatteries.size(); i++){
			if(availableBatteries.get(i).getHealth() >= recommendedBattery.getHealth()){
				recommendedBattery = availableBatteries.get(i);
			}
		}
		return recommendedBattery.getBatID();
	}else{
		return -1; //no battery available that meets criteria
	}
}

/**
 * This method will return the battery ID using
 * a system that best models the use of charging
 * stations without the knowledge of the SOH.
 * 
 * This is based on only 80% usage of system i.e.
 * operator keeps 20% of batteries as 'spares'.
 * @return ID of battery to be handed out.
 */
public int recommendBatteryNormal(){
	/*
	 * First step is find all batteries
	 * that are not handed out, that are 
	 * charged.
	 */
	ArrayList<Battery> availableBatteries = new ArrayList<Battery>();
	for(int i=0; i<batteries.size(); i++){
		if(!batteries.get(i).isInUse()){
			if(batteries.get(i).isCharged()){
				if(batteries.get(i).getHealth() > 0){
					availableBatteries.add(batteries.get(i));
				}
			}
		}
	}
	
	if(availableBatteries.size() == 0){
		return -1;
	}else{
		for(int i=0; i<availableBatteries.size(); i++){
			if(availableBatteries.get(i).getBatID() <= minimumBatteries){
				return availableBatteries.get(i).getBatID();
			}
		}
	}
	return -1;

}

/**
 * This method will return the battery ID using
 * a system that best models the use of charging
 * stations with random allocation of batteries
 * when available.
 * @return ID of battery to be handed out.
 */
public int recommendBatteryRandom(){
	/*
	 * First step is find all batteries
	 * that are not handed out, that are 
	 * charged.
	 */
	ArrayList<Battery> availableBatteries = new ArrayList<Battery>();
	for(int i=0; i<batteries.size(); i++){
		if(!batteries.get(i).isInUse()){
			if(batteries.get(i).isCharged()){
				if(batteries.get(i).getHealth() > 0){
					availableBatteries.add(batteries.get(i));
				}
			}
		}
	}
	
	Random randomGenerator = new Random(System.currentTimeMillis());
	
	if(availableBatteries.size() == 0){
		return -1;
	}else{
		int batIndex = randomGenerator.nextInt(availableBatteries.size());
		
		return availableBatteries.get(batIndex).getBatID();
	}

}

/**
 * 
 * @param algorithmType
 * 0 for normal
 * 1 for SOH
 * @return
 * @throws InterruptedException 
 */
public int simulateUse(int algorithmType) throws InterruptedException {
	boolean failed = false;
	int day = 1;
	
	while(!failed){
	//	Random randomDay = new Random(System.currentTimeMillis());
		
		//check battery list for any that are due to be handed back and hand back
		for(int i=0; i<batteries.size(); i++){
			if(batteries.get(i).isInUse()){
//				int dayIndex = randomDay.nextInt(5)+1;
				if(batteries.get(i).getLastCharged() + 2 >= day){ 
					batteries.get(i).setInUse(false);
					batteries.get(i).incrementCycles();
				}
			}
					
		}
		
		//hand out 25 batteries per day
		for(int i=0; i<25;i++){
			int recommendedBatteryID = -1;
			if(algorithmType == 0){
				recommendedBatteryID = recommendBatteryNormal();
			}else if (algorithmType == 1){
				recommendedBatteryID = recommendBatteryUsingSOH();
			}else{
				recommendedBatteryID = recommendBatteryRandom();
			}
			if(recommendedBatteryID == -1){
				failed = true;
			}else{
				for(int j=0; j< batteries.size(); j++){
					if(batteries.get(j).getBatID() == recommendedBatteryID){
						batteries.get(j).setInUse(true);
						batteries.get(j).setDayHandedOut(day);
					}
				}
			}
		}
		System.out.println("******************************************");
		System.out.println("\t\tDay: " + day + "\n");
		for(int i=0; i<batteries.size(); i++){
			DecimalFormat df = new DecimalFormat("#.##");
			System.out.println("ID: " + batteries.get(i).getBatID() + "  Out: " + batteries.get(i).isInUse());
			System.out.println("\tSOH: " + df.format(batteries.get(i).getHealth()) + "%");
		}
		
		
		day++;
	}
	return day;

	
}

}
