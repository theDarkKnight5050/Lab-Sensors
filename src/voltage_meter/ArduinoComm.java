package voltage_meter;

import processing.core.PApplet;

/**
 * Extends processing sketch to communicate with Arduino through Serial
 * 
 * @author Ahmed Abdalla
 * @version 6-15-2017
 * @Mentor: Jill Burnham
 */
public class ArduinoComm extends PApplet {
	// Communication channel to Arduino
	private Serial myPort;
	// Output String
	String outString;
	// Stores whether contact established
	boolean firstContact = false;
	// Check digit
	String val;

	/**
	 * Creates instance of ArduinoComm
	 */
	public ArduinoComm() {
		setup();
	}

	/**
	 * Sets myPort
	 */
	public void setup() {
		String portName = Serial.list()[1];
		myPort = new Serial(this, portName, 9600);
		myPort.bufferUntil('A');
	}

	public void serialEvent(Serial myPort) {
		val = myPort.readStringUntil('A');
		if (firstContact == false && val.equals("A")) {
			myPort.clear();
			firstContact = true;
			myPort.write('A');
			System.out.println("contact");
		}
	}

	/**
	 * Writes newVoltage to Serial
	 * 
	 * @param newVoltage
	 */
	public void updateVoltage(double newVoltage) {
		outString = "V" + newVoltage + '\r';
		myPort.write(outString);
		myPort.write('\n');
		System.out.println(outString);
	}

	/**
	 * Writes newCurrent to Serial
	 * 
	 * @param newCurrent
	 */
	public void updateCurrent(double newCurrent) {
		outString = "C" + newCurrent + '\r';
		myPort.write(outString);
		System.out.println(outString);
	}

	/**
	 * Writes whether On/Off to Serial
	 * 
	 * @param on
	 */
	public void updateOn(boolean on) {
		outString = "O" + on + '\r';
		myPort.write(outString);
		System.out.println(outString);
	}

	// public void output(String s) {
	// try {
	// byte[] bytes;
	// bytes = s.getBytes("US-ASCII");
	// for(byte b : bytes)
	// myPort.write(b);
	// } catch (UnsupportedEncodingException e) {
	// // TODO Auto-generated catch block
	// e.printStackTrace();
	// }
	// }

	// public void draw(){
	// background(0, 0, 0);
	// fill(0, 200, 250);
	//
	// text(outString, 10, 50);
	// text(outCurrent, 10, 50);
	// text(outOn, 10, 50);
	// }
}