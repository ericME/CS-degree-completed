/*UNIT TEST 1*/
/*legal move (no hopping), without capturing*/
#instantiate chess object
Chessobject chessboard[][]
Chessobject oracleboard[][]
Discardobject discardpile[32]
Discardobject oraclepile[32]
#clear the board
for x in range(8):
	for y in range(8):
		chessboard[x][y] = null
#set whiterook1 on appropriate spot
chessboard[2][7] = whiterook1
#copy the game state into the oracle
memcopy(oracleboard, chessboard)
memcopy(oraclepile, discardpile)
#call the move, must return true
assertTrue("valid move", RookMove(chessboard, discardpile, whiterook1, 2, 7, 2, 3))
#verify chessboard and discard states:
assertTrue("board must change", chessboard != oracleboard)
assertTrue("discardpile must not change", discardpile == oraclepile)
#verify the move completed accurately
assertTrue("rook must move to 2, 3", chessboard[2][3] == whiterook1)
#verify the discard pile
assertTrue("discard pile should be empty", discard[0] == null)

/*UNIT TEST 2*/
/*legal move (no hopping), with capturing*/
#instantiate objects
Chessobject chessboard[][]
Chessobject oracleboard[][]
Discardobject discardpile[32]
Discardobject oraclepile[32]
#clear the board
for x in range(8):
	for y in range(8):
		chessboard[x][y] = null
#set whiterook1 on appropriate spot, give it a target to capture
chessboard[2][7] = whiterook1
chessboard[2][3] = blackpawn1
#copy the game state into the oracle
memcopy(oracleboard, chessboard)
memcopy(oraclepile, discardpile)
#call the move, must return true
assertTrue("valid move", RookMove(chessboard, discardpile, whiterook1, 2, 7, 2, 3))
#verify chessboard and discard states:
assertTrue("board must change", chessboard != oracleboard)
assertTrue("discardpile must change", discardpile != oraclepile)
#verify the move completed accurately
assertTrue("rook must move to 2, 3", chessboard[2][3] == whiterook1)
#verify the discard pile
assertTrue("discard pile should have a pawn", discard[0] == blackpawn1)

/*UNIT TEST 3*/
/*illegal move (piece hopping), with capturing*/
#instantiate objects
Chessobject chessboard[][]
Chessobject oracleboard[][]
Discardobject discardpile[32]
Discardobject oraclepile[32]
#clear the board
for x in range(8):
	for y in range(8):
		chessboard[x][y] = null
#set whiterook1 on appropriate spot, give it a target to capture
chessboard[2][7] = whiterook1
chessboard[2][3] = blackpawn1
chessboard[2][4] = whitepawn1
#copy the game state into the oracle
memcopy(oracleboard, chessboard)
memcopy(oraclepile, discardpile)
#call the move, must return false
assertFalse("invalid move", RookMove(chessboard, discardpile, whiterook1, 2, 7, 2, 3))
#verify chessboard and discard states:
assertTrue("board must not change", chessboard == oracleboard)
assertTrue("discardpile must not change", discardpile == oraclepile)
#verify the move did not execute
assertTrue("rook must be left on 2, 7", chessboard[2][7] == whiterook1)
assertTrue("blackpawn1 should be on 2, 3", chessboard[2][3] == blackpawn1)
assertTrue("whitepawn1 should be on 2, 4", chessboard[2][4] == whitepawn1)
#verify the discard pile
assertTrue("discard pile should be empty", discard[0] == null)
#change the blocking piece
chessboard[2][4] = blackpawn2
#call the move, must return false
assertFalse("invalid move", RookMove(chessboard, discardpile, whiterook1, 2, 7, 2, 3))
#verify chessboard and discard states:
assertTrue("board must not change", chessboard == oracleboard)
assertTrue("discardpile must not change", discardpile == oraclepile)
#verify the move did not execute
assertTrue("rook must be left on 2, 7", chessboard[2][7] == whiterook1)
assertTrue("blackpawn1 should be on 2, 3", chessboard[2][3] == blackpawn1)
assertTrue("blackpawn2 should be on 2, 4", chessboard[2][4] == blackpawn2)
#verify the discard pile
assertTrue("discard pile should be empty", discard[0] == null)

