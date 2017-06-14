import java.io.UnsupportedEncodingException;

import processing.core.PApplet;

/**
 * Extends processing sketch to communicate with Arduino through
 * Serial
 * 
 * @author Ahmed Abdalla
 * @version 6-14-2017
 * @Mentor: Jill Burnham
 */
public class ArduinoComm extends PApplet {
	//Communication channel to Arduino
	private Serial myPort;
	//Output String
	String outString;
	boolean firstContact = false;
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
		myPort.bufferUntil('\n');
	}

	public void serialEvent( Serial myPort)	{
		val = myPort.readStringUntil('\n');
		if(firstContact == false && val.equals("A")) {
			myPort.clear();
			firstContact = true;
			myPort.write("A");
			System.out.println("contact");
		}
	}
	
	/**
	 * Writes newVoltage to Serial
	 * 
	 * @param newVoltage
	 */
	public void updateVoltage(double newVoltage) {
		outString = "V" + newVoltage + "\n";
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
		outString = "C" + newCurrent + "\n";
		myPort.write(outString);
		System.out.println(outString);
	}

	/**
	 * Writes whether On/Off to Serial
	 * 
	 * @param on
	 */
	public void updateOn(boolean on) {
		outString = "O" + on + "\n";
		myPort.write(outString);
		System.out.println(outString);
	}	
	
//	public void output(String s) {
//		try {
//			byte[] bytes;
//			bytes = s.getBytes("US-ASCII");
//			for(byte b : bytes)
//				myPort.write(b);
//		} catch (UnsupportedEncodingException e) {
//			// TODO Auto-generated catch block
//			e.printStackTrace();
//		}
//	}

//	public void settings() {
//		size(200, 200);
//	}
}