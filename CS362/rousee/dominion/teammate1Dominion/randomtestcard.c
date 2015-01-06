#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

void checkVillageCard(int player, int handPos, struct gameState *post){
	struct gameState pre;
	memcpy(&pre, post, sizeof(struct gameState));
	int r;

	zzzvilliagecardplay(player, handPos, post);
	//r = cardEffect(village, 0, 0, 0, post, handPos, 0 );
	
	if (pre.deckCount[player] > 0) {
    pre.handCount[player]++;
    pre.hand[player][pre.handCount[player]-1] = pre.deck[player][pre.deckCount[player]-1];
    pre.deckCount[player]--;
    pre.numActions = pre.numActions + 2;
  	} else if (pre.discardCount[player] > 0) {
    memcpy(pre.deck[player], post->deck[player], sizeof(int) * pre.discardCount[player]);
    memcpy(pre.discard[player], post->discard[player], sizeof(int)*pre.discardCount[player]);
    pre.hand[player][post->handCount[player]-1] = post->hand[player][post->handCount[player]-1];
    pre.handCount[player]++;
    pre.deckCount[player] = pre.discardCount[player]-1;
   	pre.discardCount[player] = 0;
    pre.numActions = pre.numActions + 2;
  	}
	assert (r == 0);
  /*if (r == 0)
  {
  	printf("r == 0\n");

  }
  else
  	printf("r != 0\n");*/
  	/*
	assert(pre.deckCount[player] == post->deckCount[player]);
	assert(pre.numActions == post->numActions);
	assert(pre.discard[player] == post->discard[player]);
	assert(pre.handCount[player] == post->handCount[player]);
	*/

  	if (pre.deckCount[player] == post->deckCount[player])
  		printf("passed deckcount\n");
  	else
  		printf("failed deckcount\n");
  	if (pre.handCount[player] == post->handCount[player])
  		printf("passed handcount\n");
  	else
  		printf("failed handcount\n");
  	if (pre.numActions == post->numActions)
  		printf("passed numactions\n");
  	else
  		printf("failed numactions\n");
  	if (pre.discard[player] == post->discard[player])
  		printf("passed discard\n");
  	else
  		printf("failed discard\n");

  	
  	

 

}
int main()
{
	int i, n, r, player, j,  handPos, deckCount, discardCount, handCount, numActions;

	int k[10] = {adventurer, council_room, feast, gardens, mine,
	       remodel, smithy, village, baron, great_hall};

	struct gameState G;

	printf ("Testing village card.\n");

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
		G.numActions = floor(Random() *MAX_HAND);
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
		checkVillageCard(player, handPos, &G);
	}


	printf ("ALL TESTS OK\n");

	exit(0);

	return 0;
}