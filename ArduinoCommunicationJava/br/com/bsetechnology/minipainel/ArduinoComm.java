/**
 * @author Wesley Egberto de Brito
 * @date 11/01/2014
 * 
 * Class for communication with the Arduino through Serial Port
 */

package br.com.bsetechnology.minipainel;

import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.Closeable;
import java.io.File;
import java.io.FileNotFoundException;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;

public class ArduinoComm implements Closeable {
	BufferedReader input;
	BufferedWriter output;
	
	private final String SERIAL_PORT;
	
	public ArduinoComm() throws FileNotFoundException, IOException {
		this("/dev/ttyACM0");
	}
	
	public ArduinoComm(String serialPort) throws FileNotFoundException, IOException {
		SERIAL_PORT = serialPort;
		File file = new File(SERIAL_PORT);
		
		input = new BufferedReader(new FileReader(file));
		output = new BufferedWriter(new FileWriter(file));
	}
	
	public String readData() throws IOException {
		return input.readLine();
	}
	
	public void sendData(String data) throws IOException {
		output.write(data);
		output.flush();
		try {
			Thread.sleep(500);
		} catch(InterruptedException e) {
			e.printStackTrace();
		}
	}
	
	@Override
	public void close() {
		try {
			input.close();
		} catch(IOException e) {
			e.printStackTrace();
		}
		try {
			output.close();
		} catch(IOException e) {
			e.printStackTrace();
		}
	}
}
