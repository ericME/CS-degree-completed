

/**
 * The Player interface defines what methods a Computer Player must implement.  
 * @author Javid Richman
 *
 */
public abstract class Player {
	protected BattleshipBoard board;
	
	/**
	 * Player constructor initializes the board instance field.
	 * @param board The board to initialize the board instance field to.
	 */
	public Player(BattleshipBoard board){
		this.board = board;
	}
	
	/**
	 * 
	 * fireNextShot() returns a new Cell object, representing a location to fire at.
	 * @return a new Cell object, representing a location to fire at.
	 *
	 */
	public abstract Cell getNextShot();
	
}
