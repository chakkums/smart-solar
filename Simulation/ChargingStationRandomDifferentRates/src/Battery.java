
public class Battery {

private int batID;	
private int numberOfCycles;
private int lastCharged;
private int chargingLevel = 100; //assumption = no charge time
private boolean inUse;
//State of health - number between 1 and 100 indicating percentage
private double SOH;

//Manufacturer's predicted cycles
private int predictedCycles = 300;

public Battery(int batID, int numberOfCycles, boolean inUse) {
	super();
	this.batID = batID;
	this.numberOfCycles = numberOfCycles;
	this.inUse = inUse;
	SOH = (1-((double)numberOfCycles/(double)predictedCycles))*100;
}

public boolean isCharged(){
	if(this.chargingLevel > 90){
		return true;
	}else{
		return false;
	}
}

/**
 * Is with user.
 **/
public boolean isInUse() {
	return inUse;
}

public void setInUse(boolean inUse) {
	this.inUse = inUse;
}

public double getHealth() {
	SOH = (1-((double)numberOfCycles/(double)predictedCycles))*100;
	return SOH;
}

public int getBatID() {
	return batID;
}

public int getNumberOfCycles() {
	return numberOfCycles;
}

public int getLastCharged() {
	return lastCharged;
}

public void setDayHandedOut(int day) {
	lastCharged = day;
	
}

public void incrementCycles() {
	numberOfCycles++;
	
}


}
