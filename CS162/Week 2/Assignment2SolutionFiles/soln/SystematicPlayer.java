
/**
 * SystematicPlayer implements the Player interface, and systematically picks the next cell, as its strategy.
 * @author Javid Richman
 *
 */
public class SystematicPlayer extends Player {
	private int row = 0;
	private int col = 0;
	
	public SystematicPlayer(BattleshipBoard board) {
		super(board);
	}
	
	@Override
	public Cell getNextShot() {
		//Create Cell
		Cell temp = new Cell(col,row);
		
		//Increment Column
		col++;
		
		//Check Column Bounds
		if(col >= board.getNumCols()){
			col = 0;
			row++;
		}
		
		//Check Row Bounds
		if(row >= board.getNumRows()){
			col = 0;
			row = 0;
		}
		
		//Return Cell
		return temp;
	}


}
