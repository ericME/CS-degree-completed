/**
 * This class represents a board in the classic game of Battleship.
 */

public class BattleshipBoard {

	/**
	 * Constructor for the Battleship Board. It allows for boards of arbitrary
	 * rows and columns to be created
	 * 
	 * @param numRows
	 *            The number of rows
	 * @param numCols
	 *            The number of columns
	 */
	public BattleshipBoard(int numRows, int numCols) {
		// To be filled in
	}

	/**
	 * Getter for the number of rows in the board
	 * 
	 * @return The number of rows in the Battleship board
	 */
	public int getNumRows() {
		// To be filled in
		return 0;
	}

	/**
	 * Getter for the number of columns in the board
	 * 
	 * @return The number of columns in the Battleship board
	 */
	public int getNumCols() {
		// To be filled in
		return 0;
	}

	/**
	 * Places the battleship at the starting coordinates (startCol,startRow) and the
	 * end coordinates (endCol,endRow) inclusive.
	 * 
	 * @param startCol
	 *            The starting Col coordinate
	 * @param startRow
	 *            The starting Row coordinate
	 * @param endCol
	 *            The ending Col coordinate
	 * @param endRow
	 *            The ending Row coordinate
	 * @throws Exception
	 *             If ship is placed diagonally
	 *             If the coordinates are out of bounds. A coordinate is in bounds if 0 <= col < (number of columns - 1) and 0 <= row < (number of rows - 1).  
	 *             If it overlaps with another battleship  
	 *             If startCol > endCol or startRow > endRow. 
	 */
	public void placeShip(int startCol, int startRow, int endCol, int endRow)
			throws Exception {
		// To be filled in
	}

	/**
	 * Fires a shot at a battleship
	 * 
	 * @param col
	 *            The col coordinate of the shot
	 * @param row
	 *            The row coordinate of the shot
	 * @return true if an enemy battleship is hit, false otherwise
	 * @throws Exception
	 *             if col or row are out of bounds
	 */
	public boolean fireShot(int col, int row) throws Exception {
		// To be filled in
		return false;
	}

	/**
	 * Main function
	 * 
	 * @param args
	 *            Command line arguments
	 */
	public static void main(String args[]) {
	    // You may leave this empty
	}
	
	
	/*****************************************
	 * Everything below is FOR BONUS ONLY
	 *****************************************/

	/**
	 * FOR BONUS ONLY: Gets the number of Battleships left
	 * 
	 * @return The number of battleships left
	 */
	public int getNumBattleshipsLeft() {
		// To be filled in
		return 0;
	}
	
	/**
	 * FOR BONUS ONLY: Returns true if game is over, false otherwise
	 * @return true if game is over, false otherwise
	 */
	public boolean isGameOver() {
		return false;
	}
	

}
