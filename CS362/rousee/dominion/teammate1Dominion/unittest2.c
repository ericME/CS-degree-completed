/*

Eric Rouse
Homework 3

Unit Test 2:
playCard()

*/

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

int main() {
  int i;
  int randSeed = 1000;
  int players = 2;
  int returnVal;
  int k[10] = {adventurer, council_room, feast, gardens, mine
               , remodel, smithy, village, baron, great_hall};
  struct gameState* game;
  int currentPlayer;
  int store_numActions;

  game = newGame();
  initializeGame(players, k, randSeed, game); 

  //check phase
  game->phase = 0;
  assert(game->phase == 0);
  printf ("playCard() |  phase fail  | phase %d | \n\t***check for expected value:", 0);
  returnVal = playCard(0, 0, 0, 0, game); 
  if (returnVal != -1){ 
    printf (" FAIL\n");
    printf ("\texpected return value of %d, but was %d\n", -1, returnVal);
  } 
  else{
    printf (" PASS\n");
  }

  //check actions
  game->numActions = 0;
  assert(game->numActions == 0);
  printf ("playCard() | actions fail | actions %d | \n\t***check for expected value:", 0);
  returnVal = playCard(0, 0, 0, 0, game);
  if (returnVal != -1){ 
    printf (" FAIL\n");
    printf ("\texpected return value of %d, but was %d\n", -1, returnVal);
  } 
  else{
    printf (" PASS\n");
  }

  //check card is an action
  currentPlayer = whoseTurn(game);
  game->hand[currentPlayer][0] = -99;
  assert(game->hand[currentPlayer][0] == -99);
  printf ("playCard() | actions fail | card %d | \n\t***check for expected value:", -99);
  returnVal = playCard(0, 0, 0, 0, game);
  if (returnVal != -1){ 
    printf (" FAIL\n");
    printf ("\texpected return value of %d, but was %d\n", -1, returnVal);
  } 
  else{
    printf (" PASS\n");
  }

  //play to check num actions, cycle through all cards
  initializeGame(players, k, randSeed, game); 
  i = adventurer;
  //{
    printf ("playCard() | valid cards | card %d | \n\t***check for expected value:", i);
    store_numActions = game->numActions;
    currentPlayer = whoseTurn(game);
    game->hand[currentPlayer][0] = i;
    playCard(0, 1, 2, 3, game);
    if (store_numActions - 1 != game->numActions){
      printf(" FAIL\n");
      printf("\texpected actions value of %d, but was %d\n", store_numActions - 1, game->numActions);
    }
    else{
      printf(" PASS\n");
    }
  //}
  return 0;
}
