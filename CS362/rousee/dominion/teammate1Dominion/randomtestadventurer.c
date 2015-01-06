#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

void checkAdventurerCard(int drawnTreasure, int cardDrawn, int player, struct gameState *post){
	struct gameState pre;
	memcpy(&pre, post, sizeof(struct gameState));
	int r, i;
	int testdrawntreasure = 0;
	int z = 0;
	int temphand[MAX_HAND];
	int deckTreasure = 0;
	
	zzzadventurercardplay(drawnTreasure, player, cardDrawn, temphand, z, post);
	if (pre.deckCount[player] > 0) {
	    pre.handCount[player] = pre.handCount[player]+2;
	    pre.hand[player][pre.handCount[player]-1] = pre.deck[player][pre.deckCount[player]-1];
	    pre.deckCount[player]--;
	 
	    for (i = 0; i < MAX_HAND; i++)
		{
			if (post->hand[player][i] == copper || post->hand[player][i] == silver || post->hand[player][i] == gold)
			{
				testdrawntreasure++;
			}
		}

		for (i = 0; i < MAX_HAND; i++)
		{
			if (pre.hand[player][i] == copper || pre.hand[player][i] == silver || pre.hand[player][i] == gold)
			{
				drawnTreasure++;
			}
		}


  	} else if (pre.discardCount[player] > 0) {
	    memcpy(pre.deck[player], post->deck[player], sizeof(int) * pre.discardCount[player]);
	    memcpy(pre.discard[player], post->discard[player], sizeof(int)*pre.discardCount[player]);
	    pre.handCount[player] = pre.handCount[player]+2;
	    pre.hand[player][post->handCount[player]-1] = post->hand[player][post->handCount[player]-1];
	    pre.deckCount[player] = pre.discardCount[player]-1;
	   	pre.discardCount[player] = 0;
	   
	    for (i = 0; i < MAX_HAND; i++)
		{
			if (post->hand[player][i] == copper || post->hand[player][i] == silver || post->hand[player][i] == gold)
			{
				testdrawntreasure++;
				
			}
		}

		for (i = 0; i < MAX_DECK; i ++)
		{
			if (post->deck[player][i] == copper || post->deck[player][i] == silver || post->deck[player][i] == gold)
			{
				deckTreasure++;
				
			}
		}
		

  	}
  	if (deckTreasure >= 2)
	{
		drawnTreasure += 2;
	}
	else if (deckTreasure == 1)
	{
		drawnTreasure++;
	}

	//assert(testdrawntreasure == drawnTreasure);
	//assert(post->handCount[player] == pre.handCount[player]);
	//printf("Treasure count = %d, expected = %d\n", testdrawntreasure, drawnTreasure);
	if (testdrawntreasure == drawnTreasure)
	{
		printf("Treasure test passed.\n");
	}
	else
		printf("Treasure test failed. \n");

//  	printf("Hand count = %d, expected = %d\n", post->handCount[player], pre.handCount[player]);
  
  	if (pre.handCount[player] == post->handCount[player])
  		printf("Passed handcount\n");
  	else
  		printf("Failed handcount\n");
 	
}
int main()
{
	int i, n, r, player, j,  handPos, deckCount, discardCount, handCount, cardDrawn;
	int drawnTreasure = 0;
	

	int k[10] = {adventurer, council_room, feast, gardens, mine,
	       remodel, smithy, village, baron, great_hall};

	struct gameState G;

	printf ("Testing adventurer card.\n");

	printf ("RANDOM TESTS.\n");

	SelectStream(2);
	PutSeed(3);

	for (n = 0; n < 2000; n++) {
		for (i = 0; i < sizeof(struct gameState); i++) {
	  		((char*)&G)[i] = floor(Random() * 256);
		}

		player = floor(Random() * 2);
		G.deckCount[player] = floor(Random() * MAX_DECK);
		G.discardCount[player] = floor(Random() * MAX_DECK);
		G.handCount[player] = floor(Random() * MAX_HAND);
		cardDrawn = floor(Random() *10);
		handPos = floor(Random() * G.handCount[player]);
		G.playedCardCount = floor(Random() * MAX_DECK);
		for (i = 0; i < MAX_PLAYERS; i++){
			for (j = 0 ; j< MAX_HAND; j++){
					G.hand[i][j] = floor(Random() *27);
			}
		}
		for (i = 0; i < MAX_PLAYERS; i++){
			for (j = 0 ; j< MAX_HAND; j++){
					G.deck[i][j] = floor(Random() *27);
			}
		}
		for (i = 0; i < MAX_PLAYERS; i++){
			for (j = 0 ; j< MAX_HAND; j++){
					G.discard[i][j] = floor(Random() *27);
			}
		}
		checkAdventurerCard(drawnTreasure, cardDrawn, player, &G);
		
	}

	printf ("ALL TESTS OK\n");

	exit(0);

	return 0;
}