
import java.util.ArrayList;
import java.util.Random;

/**
 * RandomPlayer implements the Player interface, and randomly chooses a cell as its strategy.  
 * @author Javid Richman
 *
 */
public class RandomPlayer extends Player {
	private Random rand;
	private ArrayList<Cell> cells = new ArrayList<Cell>();
	public RandomPlayer(BattleshipBoard board) {
		super(board);
		rand = new Random();
		for(int c=0; c < board.getNumCols(); c++){
			for(int r=0; r < board.getNumRows(); r++){
				cells.add(new Cell(c,r));
			}
		}
		
	}

	@Override
	public Cell getNextShot() {
		return cells.remove(rand.nextInt(cells.size()));
	}

}
