

import java.awt.BorderLayout;
import java.awt.Color;
import java.awt.Dimension;
import java.awt.GridLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.io.File;
import java.io.FileNotFoundException;
import java.util.Random;

import javax.swing.BorderFactory;
import javax.swing.JFrame;
import javax.swing.JInternalFrame;
import javax.swing.JOptionPane;
import javax.swing.JPanel;
/**
 * This class is a modified version of BattleshipBoardGUI.  It is used by the Assignment3ExampleLauncher.
 * @author javidrichman
 *
 */
public class BattleshipBoardGUIJInternalFrame extends JInternalFrame{
	private JInternalFrame t;
	private boolean color;
	private boolean border;
	
	//Battleship Size Constants
	public static final int ROWS = 10;
	public static final int COLS = 10;

	//GUI Resolution
	public static final int GUI_WIDTH = 1024;
	public static final int GUI_HEIGHT = 512;

	//Label Constants
	public static final char MISS = 'M';
	public static final char HIT = 'H';
	public static final char BATTLESHIP = 'B';

	//FireButton instance fields
	private FireButton[][] opponentButtons;
	private FireButton[][] playerButtons;

	//BattleshipBoard instance fields
	private BattleshipBoard opponentBoard;
	private BattleshipBoard playerBoard;

	//Panels
	private JPanel opponentGrid;
	private JPanel playerGrid;

	//Fire Listener
	private FireListener fireListener = new FireListener();

	//Computer Player
	private Player player;

	public BattleshipBoardGUIJInternalFrame(boolean color, boolean border, char type) throws FileNotFoundException, BattleshipException{
		this.color = color;
		this.border = border;
		this.t = this;

		//Initialize instance fields
		opponentButtons = new FireButton[COLS][ROWS];
		playerButtons = new FireButton[COLS][ROWS];

		//Setup Boards
		playerBoard = new BattleshipBoard(10,10);
		opponentBoard = new BattleshipBoard(10,10);
		placeCShips(playerBoard);
		placeSShips(opponentBoard);
		
		opponentGrid = new JPanel(new GridLayout(COLS, ROWS));
		playerGrid = new JPanel(new GridLayout(COLS, ROWS));

		//Set the title to "Battleship GUI"
		this.setTitle("Battleship GUI");

		//Set the default close operator to EXIT_ON_CLOSE
		this.setDefaultCloseOperation(JInternalFrame.DISPOSE_ON_CLOSE);

		//Set the size of the JFrame using the defined constants (GUI_WIDTH AND GUI_HEIGHT)
		this.setSize(BattleshipBoardGUIJInternalFrame.GUI_WIDTH, BattleshipBoardGUIJInternalFrame.GUI_HEIGHT);

		//Set the layout manger to be BorderLayout
		this.setLayout(new BorderLayout());

		//Initialize FireButtons AND add FireButtons TO each grid
		for(int r=0; r < ROWS; r++){
			for(int c=0; c < COLS; c++){
				//Initialization
				FireButton pb = new FireButton(c, r);
				FireButton ob = new FireButton(c, r);


				//Set button attributes (for player)
				pb.setEnabled(false);
				if(playerBoard.isOccupied(c, r)){
					pb.setText(Character.toString(playerBoard.getCellContent(c, r)));
					if(color) pb.setBackground(new Color(139,69,19));
				} else{
					pb.setBackground(Color.GRAY);
				}
				//Set Preferred Size Of Buttons
				pb.setPreferredSize(new Dimension(50,50));
				ob.setPreferredSize(new Dimension(50,50));

				//Add buttons to grid
				playerGrid.add(pb);
				opponentGrid.add(ob);

				//Add Fire Listener
				ob.addActionListener(fireListener);

				//Point Array to Buttons
				playerButtons[c][r] = pb;
				opponentButtons[c][r] = ob;
			}
		}	

		//Set Labels for panels
		if(border) opponentGrid.setBorder(BorderFactory.createTitledBorder("Opponent Battleship Board"));
		if(border) playerGrid.setBorder(BorderFactory.createTitledBorder("Player Battleship Board"));

		//Add Grids to JFrame
		this.add(opponentGrid, BorderLayout.EAST);
		this.add(playerGrid, BorderLayout.WEST);
		
		//Choose Player Type
		switch(type){
		case 'r':
			player = new RandomPlayer(playerBoard);
			break;
		case 's':
			player = new SystematicPlayer(playerBoard);
			break;
		}
		
		
	}
	private void placeCShips(BattleshipBoard board) throws IndexOutOfBoundsException, BattleshipException{
		board.placeShip(2,3,2,7);
		board.placeShip(3,2,5,2);
		board.placeShip(3,3,6,3);
		board.placeShip(7,3,7,5);
		board.placeShip(7,6,7,7);
	}
	private void placeSShips(BattleshipBoard board) throws IndexOutOfBoundsException, BattleshipException{
		board.placeShip(1,3,1,6);
		board.placeShip(2,3,4,3);
		board.placeShip(4,4,4,5);
		board.placeShip(4,6,6,6);
		board.placeShip(7,2,7,6);
	}
	public class FireListener implements ActionListener{

		@Override
		public void actionPerformed(ActionEvent arg0) {
			//Player Fire Shot On Opponent
			FireButton fb = (FireButton) arg0.getSource();
			fb.setEnabled(false);
			if(opponentBoard.fireShot( fb.getCell().getColumn(), fb.getCell().getRow())){
				fb.setText(Character.toString(HIT));
				if(color) fb.setBackground(Color.YELLOW);
			} else{
				fb.setText(Character.toString(MISS));
				if(color) fb.setBackground(Color.BLUE);
			}	
			
			//Check if player is winner
			if(opponentBoard.isGameOver()){
				JOptionPane.showMessageDialog(t, "The Player Has Won The Game!\nClick OK to exit the program.", "You WON!", JOptionPane.INFORMATION_MESSAGE);
				t.dispose();
			}

			//Computer Fires Shot On Player
			Cell nextShot = player.getNextShot();
			FireButton pfb = playerButtons[nextShot.getColumn()][nextShot.getRow()];
			if(playerBoard.fireShot(nextShot.getColumn(), nextShot.getRow())){
				pfb.setText(Character.toString(HIT));
				if(color) pfb.setBackground(Color.YELLOW);
			} else{
				pfb.setText(Character.toString(MISS));
				if(color) pfb.setBackground(Color.BLUE);
			}
			
			//Check if computer is winner
			if(playerBoard.isGameOver()){
				JOptionPane.showMessageDialog(t, "The Computer Has Won The Game!\nClick OK to exit the program.", "You LOST!", JOptionPane.ERROR_MESSAGE);
				t.dispose();
			}
		}
	}

}
