import java.io.IOException;
import java.net.MalformedURLException;
import java.net.URL;

import javax.imageio.ImageIO;
import javax.swing.JFrame;

/**
 * Creates Frame
 * 
 * @author Ahmed Abdalla
 * @version 6-14-2017
 * @Mentor: Jill Burnham
 */
public class Controller {
	/**
	 * Creates JFrame and places an InputWindow within
	 * 
	 * @param args
	 * @throws IOException 
	 * @throws MalformedURLException 
	 */
	public static void main(String[] args) throws MalformedURLException, IOException {
		JFrame frame = new JFrame("PMC35-1A Controller");
		frame.setSize(475, 125);
		frame.setLocation(100, 50);
		frame.setDefaultCloseOperation(JFrame.EXIT_ON_CLOSE);
		frame.setIconImage(ImageIO.read(new URL("https://cdn4.iconfinder.com/data/icons/electricity/500/Energy_lightning_power_electric_electricity-512.png")));
		frame.setContentPane(new InputWindow());
		frame.setVisible(true);
	}
}