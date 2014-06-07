

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
import javax.swing.JOptionPane;
import javax.swing.JPanel;

/**
 * 
 * @author Angela Billings
 * @author Javid Richman
 *
 */
public class BattleshipBoardGUI extends JFrame{
	//I added these so I could easily turn on and off the color and/or titled borders.
	public static final boolean COLOR = true;  //Turn Color On
	public static final boolean BORDER = true; //Turn Color Off
	
	
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

	public BattleshipBoardGUI(File opponentFile, File playerFile, char playerType) throws FileNotFoundException{

		//Initialize instance fields
		opponentButtons = new FireButton[COLS][ROWS];
		playerButtons = new FireButton[COLS][ROWS];
		opponentBoard = new BattleshipBoard(opponentFile);
		opponentBoard.print();
		playerBoard  = new BattleshipBoard(playerFile);
		
		opponentGrid = new JPanel(new GridLayout(COLS, ROWS));
		playerGrid = new JPanel(new GridLayout(COLS, ROWS));

		//Set the title to "Battleship GUI"
		this.setTitle("Battleship GUI");

		//Set the default close operator to EXIT_ON_CLOSE
		this.setDefaultCloseOperation(EXIT_ON_CLOSE);

		//Set the size of the JFrame using the defined constants (GUI_WIDTH AND GUI_HEIGHT)
		this.setSize(BattleshipBoardGUI.GUI_WIDTH, BattleshipBoardGUI.GUI_HEIGHT);

		//Set the location of the JFrame to the center of the screen
		this.setLocationRelativeTo(null);

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
					if(COLOR) pb.setBackground(new Color(139,69,19));
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
		if(BORDER) opponentGrid.setBorder(BorderFactory.createTitledBorder("Opponent Battleship Board"));
		if(BORDER) playerGrid.setBorder(BorderFactory.createTitledBorder("Player Battleship Board"));

		//Add Grids to JFrame
		this.add(opponentGrid, BorderLayout.EAST);
		this.add(playerGrid, BorderLayout.WEST);
		
		//Initialize Player Type
		player = (playerType=='r') ? new RandomPlayer(playerBoard) : new SystematicPlayer(playerBoard);

	}
	public class FireListener implements ActionListener{

		@Override
		public void actionPerformed(ActionEvent arg0) {
			//Player Fire Shot On Opponent
			FireButton fb = (FireButton) arg0.getSource();
			fb.setEnabled(false);
			if(opponentBoard.fireShot(fb.getCell().getColumn(), fb.getCell().getRow())){
				fb.setText(Character.toString(HIT));
				if(COLOR) fb.setBackground(Color.YELLOW);
			} else{
				fb.setText(Character.toString(MISS));
				if(COLOR) fb.setBackground(Color.BLUE);
			}	
			
			//Check if player is winner
			if(opponentBoard.isGameOver()){
				JOptionPane.showMessageDialog(null, "The Player Has Won The Game!\nClick OK to exit the program.", "You WON!", JOptionPane.INFORMATION_MESSAGE);
				System.exit(0);
			}

			//Computer Fires Shot On Player
			Cell nextShot = player.getNextShot();
			FireButton pfb = playerButtons[nextShot.getColumn()][nextShot.getRow()];
			if(playerBoard.fireShot(nextShot.getColumn(), nextShot.getRow())){
				pfb.setText(Character.toString(HIT));
				if(COLOR) pfb.setBackground(Color.YELLOW);
			} else{
				pfb.setText(Character.toString(MISS));
				if(COLOR) pfb.setBackground(Color.BLUE);
			}
			
			//Check if computer is winner
			if(playerBoard.isGameOver()){
				JOptionPane.showMessageDialog(null, "The Computer Has Won The Game!\nClick OK to exit the program.", "You LOST!", JOptionPane.ERROR_MESSAGE);
				System.exit(0);
			}
		}
	}
	public static void main(String[] args){
		if(args.length!=3){
			System.out.println("Usage: java BattleshipBoardGUI <path_to_opponent_board_file> <path_to_player_board_file> <s_or_r>");
			System.out.println("Example Usage: java BattleshipBoardGUI /home/user/opponentBoard.txt /home/user/playerBoard.txt s");
			System.exit(-1);
		}
		try {
			BattleshipBoardGUI gui = new BattleshipBoardGUI(new File(args[0]), new File(args[1]), args[2].charAt(0));
			gui.setVisible(true);
		} catch (FileNotFoundException e) {
			e.printStackTrace();
		}

	}
}
