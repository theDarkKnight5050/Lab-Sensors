package voltage_meter;

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
 * @date 6-15-2017
 * @Mentor: Jill Burnham
 */
@SuppressWarnings("serial")
public class InputWindow extends JPanel {
	// Handles communication to Arduino
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

		// creates voltage row
		voLabel = new JLabel("Voltage: ");
		add(voLabel);
		voText = new JTextField();
		PromptSupport.setPrompt("Between 0-17.5V", voText);
		add(voText);
		voButton = new JButton("Update");
		voButton.addActionListener(new VoltageListener(this));
		add(voButton);

		// creates current row
		currLabel = new JLabel("Current: ");
		add(currLabel);
		currText = new JTextField();
		PromptSupport.setPrompt("Between 0-0.5A", currText);
		add(currText);
		currButton = new JButton("Update");
		currButton.addActionListener(new CurrentListener(this));
		add(currButton);

		// create on row
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

		// Panel containing Listener's buttons
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
		 * Sends voltage data over Serial Resets label and text field
		 * 
		 * @param ae
		 *            Button Click
		 */
		@Override
		public void actionPerformed(ActionEvent ae) {
			try {
				double voltage = Double.parseDouble(voText.getText());
				if (voltage >= 0 && voltage <= 17.5) {
					comm.updateVoltage(voltage);
					voText.setText("");
					voLabel.setText("Voltage: " + voltage);
				} else {
					JOptionPane.showMessageDialog(getMyPanel(), "Number Bound Error", "Invalid Voltage",
							JOptionPane.WARNING_MESSAGE);
				}
			} catch (Exception e) {
				JOptionPane.showMessageDialog(getMyPanel(), "Number Format Error", "Invalid Voltage",
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
		 * Sends current data over Serial Resets label and text field
		 * 
		 * @param ae
		 *            Button Click
		 */
		@Override
		public void actionPerformed(ActionEvent ae) {
			try {
				double current = Double.parseDouble(currText.getText());
				if (current >= 0 && current <= 0.5) {
					comm.updateCurrent(current);
					currText.setText("");
					currLabel.setText("Current: " + current);
				} else {
					JOptionPane.showMessageDialog(getMyPanel(), "Number Bound Error", "Invalid Current",
							JOptionPane.WARNING_MESSAGE);
				}
			} catch (Exception e) {
				JOptionPane.showMessageDialog(getMyPanel(), "Number Format Error", "Invalid Current",
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
		 * Sends current data over Serial Resets label and text field
		 * 
		 * @param ae
		 *            Button Click
		 */
		@Override
		public void actionPerformed(ActionEvent ae) {
			String inString = onText.getText();
			if (inString.equalsIgnoreCase("ON")) {
				comm.updateOn(true);
				onLabel.setText("On/Off: ON");
			} else {
				if (inString.equalsIgnoreCase("OFF")) {
					comm.updateOn(false);
					onLabel.setText("On/Off: OFF");
				} else
					JOptionPane.showMessageDialog(getMyPanel(), "Input Either ON or OFF", "Invalid State",
							JOptionPane.WARNING_MESSAGE);
			}
		}
	}
}