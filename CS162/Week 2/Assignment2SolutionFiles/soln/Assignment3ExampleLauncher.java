import java.awt.BorderLayout;
import java.awt.Color;
import java.awt.GridLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.beans.PropertyVetoException;
import java.io.FileNotFoundException;

import javax.swing.BorderFactory;
import javax.swing.JApplet;
import javax.swing.JButton;
import javax.swing.JDesktopPane;
import javax.swing.JOptionPane;
import javax.swing.JPanel;

/**
 * Assignment3ExampleLauncher is a JApplet, which allows the modified BattleshipBoardGUI to be previewed.
 * @author javidrichman
 *
 */
public class Assignment3ExampleLauncher extends JApplet{
	JButton[] buttons = new JButton[2];
	JDesktopPane jdp;
	ActionListener buttonListener = new ActionListener(){
		@Override
		public void actionPerformed(ActionEvent e) {
			try {
				BattleshipBoardGUIJInternalFrame gui;
				if(e.getSource().equals(buttons[0])){
					gui = new BattleshipBoardGUIJInternalFrame(true,true, 'r');
					gui.setTitle("Random: Battleship Board GUI With Both Color And Titled Border");
					attach(gui);
				} else if(e.getSource().equals(buttons[1])){
					gui = new BattleshipBoardGUIJInternalFrame(true,true, 's');
					gui.setTitle("Systematic: Battleship Board GUI With Both Color And Titled Border");
					attach(gui);
				}
				
				/*if(e.getSource().equals(buttons[0])){
					gui= new BattleshipBoardGUIJInternalFrame(false, false, 'r');
					gui.setTitle("Random: Battleship Board GUI");
					attach(gui);

				} else if(e.getSource().equals(buttons[1])){
					gui = new BattleshipBoardGUIJInternalFrame(true, false, 'r');
					gui.setTitle("Random: Battleship Board GUI - With Color");
					attach(gui);
				} else if(e.getSource().equals(buttons[2])){
					gui = new BattleshipBoardGUIJInternalFrame(false, true, 'r');
					gui.setTitle("Random: Battleship Board GUI - With Titled Border");
					attach(gui);
				} else if(e.getSource().equals(buttons[3])){
					gui = new BattleshipBoardGUIJInternalFrame(true,true, 'r');
					gui.setTitle("Random: Battleship Board GUI With Both Color And Titled Border");
					attach(gui);
				} else if(e.getSource().equals(buttons[4])){
					gui= new BattleshipBoardGUIJInternalFrame(false, false, 's');
					gui.setTitle("Systematic: Battleship Board GUI");
					attach(gui);

				} else if(e.getSource().equals(buttons[5])){
					gui = new BattleshipBoardGUIJInternalFrame(true, false, 's');
					gui.setTitle("Systematic: Battleship Board GUI - With Color");
					attach(gui);
				} else if(e.getSource().equals(buttons[6])){
					gui = new BattleshipBoardGUIJInternalFrame(false, true, 's');
					gui.setTitle("Systematic: Battleship Board GUI - With Titled Border");
					attach(gui);
				} else if(e.getSource().equals(buttons[7])){
					gui = new BattleshipBoardGUIJInternalFrame(true,true, 's');
					gui.setTitle("Systematic: Battleship Board GUI With Both Color And Titled Border");
					attach(gui);
				} */

			} catch (Exception exception){
				JOptionPane.showMessageDialog(null, "Error: "+exception.getMessage());
			}
		}
		private void attach(BattleshipBoardGUIJInternalFrame gui) throws PropertyVetoException{
			gui.setClosable(true);
			gui.setVisible(true);
			gui.setLocation(30*jdp.getComponentCount()+10, 30*jdp.getComponentCount()+10);
			jdp.add(gui);
			gui.setSelected(true);
		}

	};
	public Assignment3ExampleLauncher() throws FileNotFoundException, BattleshipException{
		jdp = new JDesktopPane();
		JPanel panel = new JPanel();
		panel.setLayout(new GridLayout(1,2));
		/*buttons[0] = new JButton("Random");
		buttons[1] = new JButton("Random: With Color");
		buttons[2] = new JButton("Random: With Titled Border");
		buttons[3] = new JButton("Random: With Color AND Border");
		buttons[4] = new JButton("Systematic");
		buttons[5] = new JButton("Systematic: With Color");
		buttons[6] = new JButton("Systematic: With Titled Border");
		buttons[7] = new JButton("Systematic: With Color AND Border");*/

		buttons[0] = new JButton("Random");
		buttons[1] = new JButton("Systematic");
		
		for(JButton b: buttons){
				b.addActionListener(buttonListener);
				panel.add(b);
		}

		panel.setBorder(BorderFactory.createTitledBorder("Choose A BattlshipBoardGUI To View: (Note: You can open multiple BattleshipBoardGUI windows, if you like!)"));
		panel.setBackground(Color.WHITE);
		setLayout(new BorderLayout());
		add(panel, BorderLayout.NORTH);
		add(jdp, BorderLayout.CENTER);
	}


}
