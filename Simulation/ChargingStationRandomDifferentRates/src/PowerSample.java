import java.sql.Timestamp;

public class PowerSample {

private Timestamp timeSampled;
private double usbCurrentDraw;
private double lightingCurrentDraw;

public PowerSample(Timestamp timeSampled, double usbCurrentDraw,
		double lightingCurrentDraw) {
	super();
	this.timeSampled = timeSampled;
	this.usbCurrentDraw = usbCurrentDraw;
	this.lightingCurrentDraw = lightingCurrentDraw;
}

public Timestamp getTimeSampled() {
	return timeSampled;
}

public double getUsbCurrentDraw() {
	return usbCurrentDraw;
}

public double getLightingCurrentDraw() {
	return lightingCurrentDraw;
}

}
