/*

Eric Rouse
Homework 3

Card Test 4:
village

*/

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define TESTCARD "village"

int main() {
  int newCards = 1;
  int discarded = 0;
  int shuffledCards = 0;
  int handPos = 0;
  int randSeed = 1000;
  int numPlayers = 2;
  int thisPlayer = 0;
  struct gameState* game;
  struct gameState* store_game;
  int k[10] = {adventurer, embargo, village, minion, mine, cutpurse,
      sea_hag, tribute, smithy, council_room};

  printf("----------------- Testing Card: %s -----------------\n", TESTCARD);

  // initialize the game state
  game = newGame();
  initializeGame(numPlayers, k, randSeed, game);

  // copy the game state to a test case
  store_game = newGame();
  memcpy(store_game, game, sizeof(struct gameState));

  // play card in store_game
  zzzvillagecardplay(thisPlayer, handPos, store_game);
  // ----------- TEST 1: No need to shuffle deck cards --------------
  printf("TEST 1: No need to shuffle deck cards\n");
  
  // check handCount
  printf("zzzvillagecardplay() | handCount | player %d | \n\t***check for expected value:", thisPlayer);
  if (store_game->handCount[thisPlayer] != (game->handCount[thisPlayer] + newCards - discarded))  {
    printf(" FAIL\n");
    printf("\tExpected %d handCount, but was %d\n", game->handCount[thisPlayer] + newCards - discarded, store_game->handCount[thisPlayer]);
  }
  else {
    printf(" PASS\n");
  }
  // check deckCount
  printf("zzzvillagecardplay() | deckCount | player %d | \n\t***check for expected value:", thisPlayer);
  if (store_game->deckCount[thisPlayer] != (game->deckCount[thisPlayer] - newCards + shuffledCards))  {
    printf(" FAIL\n");
    printf("\tExpected %d deckCount, but was %d\n", game->deckCount[thisPlayer] - newCards + shuffledCards, store_game->deckCount[thisPlayer]);
  }
  else {
    printf(" PASS\n");
  } 
  // check playedCardCount
  printf("zzzvillagecardplay() | cardCount | player %d | \n\t***check for expected value:", thisPlayer); 
  if (store_game->playedCardCount != discarded)  {
    printf(" FAIL\n");
    printf("\tExpected %d playedCardCount, but was %d\n", discarded, store_game->playedCardCount);
  } 
  else  {
    printf(" PASS\n");
  }

  
    // ----------- TEST 2: Need to shuffle deck cards ------------------
    printf("TEST 2: Need to shuffle deck cards\n");

  shuffledCards = store_game->handCount[thisPlayer];
  endTurn(store_game);

  // copy the game state to a test case
  memcpy(game, store_game, sizeof(struct gameState));

  // play the card in store_game
  zzzvillagecardplay(thisPlayer, handPos, store_game);

  // check handCount
  printf("zzzvillagecardplay() | handCount | player %d | \n\t***check for expected value:", thisPlayer);
  if (store_game->handCount[thisPlayer] != (game->handCount[thisPlayer] + newCards - discarded))  {
    printf(" FAIL\n");
    printf("\tExpected %d handCount, but was %d\n", game->handCount[thisPlayer] + newCards - discarded, store_game->handCount[thisPlayer]);
  }
  else {
    printf(" PASS\n");
  }
  // check deckCount
  printf("zzzvillagecardplay() | deckCount | player %d | \n\t***check for expected value:", thisPlayer);
  if (store_game->deckCount[thisPlayer] != (game->deckCount[thisPlayer] - newCards + shuffledCards))  {
    printf(" FAIL\n");
    printf("\tExpected %d deckCount, but was %d\n", game->deckCount[thisPlayer] - newCards + shuffledCards, store_game->deckCount[thisPlayer]);
  }
  else {
    printf(" PASS\n");
  } 
  // check playedCardCount
  printf("zzzvillagecardplay() | cardCount | player %d | \n\t***check for expected value:", thisPlayer); 
  if (store_game->playedCardCount != discarded)  {
    printf(" FAIL\n");
    printf("\tExpected %d playedCardCount, but was %d\n", discarded, store_game->playedCardCount);
  } 
  else  {
    printf(" PASS\n");
  }


    return 0;
}
