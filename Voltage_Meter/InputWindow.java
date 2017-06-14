import java.awt.GridLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import javax.swing.JButton;
import javax.swing.JLabel;
import javax.swing.JOptionPane;
import javax.swing.JPanel;
import javax.swing.JTextField;

import org.jdesktop.xswingx.PromptSupport;

/**
 * GUI Panel
 * 
 * @author Ahmed Abdalla
 * @date 6-14-2017
 * @Mentor: Jill Burnham
 */
@SuppressWarnings("serial")
public class InputWindow extends JPanel {
	//Handles communication to Arduino
	private ArduinoComm comm;
	private JLabel voLabel, currLabel, onLabel;
	private JTextField voText, currText, onText;
	private JButton voButton, currButton, onButton;

	/**
	 * Creates panel
	 */
	public InputWindow() {
		setLayout(new GridLayout(3, 3));

		comm = new ArduinoComm();

		voLabel = new JLabel("Voltage: ");
		add(voLabel);
		voText = new JTextField();
		PromptSupport.setPrompt("Enter Value Between 0-17.5", voText);
		add(voText);
		voButton = new JButton("Update");
		voButton.addActionListener(new VoltageListener(this));
		add(voButton);

		currLabel = new JLabel("Current: ");
		add(currLabel);
		currText = new JTextField();
		PromptSupport.setPrompt("Enter Value Between 0-1", currText);
		add(currText);
		currButton = new JButton("Update");
		currButton.addActionListener(new CurrentListener(this));
		add(currButton);

		onLabel = new JLabel("On/Off: ");
		add(onLabel);
		onText = new JTextField();
		PromptSupport.setPrompt("Either \"ON\" or \"OFF\"", onText);
		add(onText);
		onButton = new JButton("Update");
		onButton.addActionListener(new OnListener(this));
		add(onButton);
	}

	private class MyListener {
		//Panel containing Listener's buttons
		private JPanel myPanel;
		
		/**
		 * Sets myPanel 
		 * 
		 * @param panel
		 */
		public MyListener(JPanel panel) {
			myPanel = panel;
		}

		/**
		 * @return myPanel
		 */
		public JPanel getMyPanel() {
			return myPanel;
		}
		
		/**
		 * Sets myPanel
		 * 
		 * @param myPanel
		 */
		@SuppressWarnings("unused")
		public void setMyPanel(JPanel myPanel) {
			this.myPanel = myPanel;
		}
	}

	/**
	 * Handles clicking of Voltage "Update" button
	 * 
	 * @author Ahmed Abdalla
	 * @date 6-14-2017
	 * @Mentor: Jill Burnham
	 */
	private class VoltageListener extends MyListener implements ActionListener {

		/**
		 * Sets myPanel
		 * 
		 * @param panel
		 */
		public VoltageListener(JPanel panel) {
			super(panel);
			// TODO Auto-generated constructor stub
		}

		/**
		 * Sends voltage data over Serial
		 * 
		 * @param ae Button Click
		 */
		public void actionPerformed(ActionEvent ae) {
			try {
				String voltage = voText.getText();
				comm.updateVoltage(Double.parseDouble(voltage));
				voText.setText("");
			} catch (Exception e) {
				JOptionPane.showMessageDialog(getMyPanel(), "Invalid Voltage", "Number Format Error",
						JOptionPane.WARNING_MESSAGE);
			}
		}
	}

	/**
	 * Handles clicking of Current "Update" button
	 * 
	 * @author Ahmed Abdalla
	 * @date 6-14-2017
	 * @Mentor: Jill Burnham
	 */
	private class CurrentListener extends MyListener implements ActionListener {
		
		/**
		 * Sets myPanel
		 * 
		 * @param panel
		 */
		public CurrentListener(JPanel panel) {
			super(panel);
			// TODO Auto-generated constructor stub
		}

		/**
		 * Sends current data over Serial
		 * 
		 * @param ae Button Click
		 */
		public void actionPerformed(ActionEvent ae) {
			try {
				String current = currText.getText();
				comm.updateCurrent(Double.parseDouble(current));
				currText.setText("");
			} catch (Exception e) {
				JOptionPane.showMessageDialog(getMyPanel(), "Invalid Current", "Number Format Error",
						JOptionPane.WARNING_MESSAGE);
			}
		}
	}

	/**
	 * Handles clicking of On/Off "Update" button
	 * 
	 * @author Ahmed Abdalla
	 * @date 6-14-2017
	 * @Mentor: Jill Burnham
	 */
	private class OnListener extends MyListener implements ActionListener {
		
		/**
		 * Sets myPanel
		 * 
		 * @param panel
		 */
		public OnListener(JPanel panel) {
			super(panel);
			// TODO Auto-generated constructor stub
		}

		/**
		 * Sends current data over Serial
		 * 
		 * @param ae Button Click
		 */
		public void actionPerformed(ActionEvent ae) {
			String inString = onText.getText();
			if (inString.equalsIgnoreCase("ON")) {
				comm.updateOn(true);
			} else {
				if (inString.equalsIgnoreCase("OFF"))
					comm.updateOn(false);
				else
					JOptionPane.showMessageDialog(getMyPanel(), "Invalid State", "Input Either ON or OFF",
							JOptionPane.WARNING_MESSAGE);
			}
		}
	}
}