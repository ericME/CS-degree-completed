/*

Eric Rouse
Homework 3

Card Test 3:
council room card


*/

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"
#include <stdlib.h>

#define TESTCARD "council room"

int main() {
  int newCards = 4;
  int discarded = 1;
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
  zzzcouncilroomcardplay(0, thisPlayer, handPos, store_game);
  // ----------- TEST 1: No need to shuffle deck cards --------------
  printf("TEST 1: No need to shuffle deck cards\n");
  
  // check handCount
  printf("zzzcouncilroomcardplay() | handCount | player %d | \n\t***check for expected value:", thisPlayer);
  if (store_game->handCount[thisPlayer] != (game->handCount[thisPlayer] + newCards))  {
    printf(" FAIL\n");
    printf("\tExpected %d handCount, but was %d\n", game->handCount[thisPlayer] + newCards, store_game->handCount[thisPlayer]);
  }
  else {
    printf(" PASS\n");
  }
  // check deckCount
  printf("zzzcouncilroomcardplay() | deckCount | player %d | \n\t***check for expected value:", thisPlayer);
  if (store_game->deckCount[thisPlayer] != (game->deckCount[thisPlayer]))  {
    printf(" FAIL\n");
    printf("\tExpected %d deckCount, but was %d\n", game->deckCount[thisPlayer], store_game->deckCount[thisPlayer]);
  }
  else {
    printf(" PASS\n");
  } 
  // check playedCardCount
  printf("zzzcouncilroomcardplay() | numBuys | player %d | \n\t***check for expected value:", thisPlayer); 
  if (store_game->numBuys != game->numBuys +1 )  {
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
  zzzcouncilroomcardplay(0, thisPlayer, handPos, store_game);

  /// check handCount
  printf("zzzcouncilroomcardplay() | handCount | player %d | \n\t***check for expected value:", thisPlayer);
  if (store_game->handCount[thisPlayer] != (game->handCount[thisPlayer] + newCards))  {
    printf(" FAIL\n");
    printf("\tExpected %d handCount, but was %d\n", game->handCount[thisPlayer] + newCards, store_game->handCount[thisPlayer]);
  }
  else {
    printf(" PASS\n");
  }
  // check deckCount
  printf("zzzcouncilroomcardplay() | deckCount | player %d | \n\t***check for expected value:", thisPlayer);
  if (store_game->deckCount[thisPlayer] != (game->deckCount[thisPlayer]))  {
    printf(" FAIL\n");
    printf("\tExpected %d deckCount, but was %d\n", game->deckCount[thisPlayer], store_game->deckCount[thisPlayer]);
  }
  else {
    printf(" PASS\n");
  } 
  // check playedCardCount
  printf("zzzcouncilroomcardplay() | numBuys | player %d | \n\t***check for expected value:", thisPlayer); 
  if (store_game->numBuys != game->numBuys +1 )  {
    printf(" FAIL\n");
    printf("\tExpected %d playedCardCount, but was %d\n", discarded, store_game->playedCardCount);
  } 
  else  {
    printf(" PASS\n");
  }


  return 0;
}
