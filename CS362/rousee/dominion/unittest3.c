/*

Eric Rouse
Homework 3

Unit Test 3:
initializeGame()
    
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
  int players;
  int returnVal;
  int k_Pass[10] = {adventurer, council_room, feast, gardens, mine
               , remodel, smithy, village, baron, great_hall};
  //this array has the same kingdom card
  int k_Same[10] = {adventurer, adventurer, feast, gardens, mine
               , remodel, smithy, village, baron, great_hall};
  //this array has an unknown card
    int k_Unkn[10] = {-99, adventurer, feast, gardens, mine
               , remodel, smithy, village, baron, great_hall};
  struct gameState* game;

  for (players = 2; players <= MAX_PLAYERS; players++)
  {
    // force a failed game not all cards different
    game = newGame();
    returnVal = initializeGame(players, k_Same, randSeed, game); 
    printf ("initializeGame() | fail1  return | players %d | \n\t***check for expected value:", players);
    if (returnVal != -1){ 
      printf (" FAIL\n");
      printf ("\texpected return value of %d, but was %d\n", -1, returnVal);
    } 
    else{
      printf (" PASS\n");
    }
    assert(returnVal == -1);

    // force a failed game not enough players
    game = newGame();
    returnVal = initializeGame(1, k_Pass, randSeed, game); 
    printf ("initializeGame() | fail2  return | players %d | \n\t***check for expected value:", players);
    if (returnVal != -1){ 
      printf(" FAIL\n");
      printf ("\texpected return value of %d, but was %d\n", -1, returnVal);
    } 
    else{
      printf (" PASS\n");
    }
    assert(returnVal == -1);

    // force a failed game wrong card
    game = newGame();
    returnVal = initializeGame(players, k_Unkn, randSeed, game); 
    printf ("initializeGame() | fail3  return | players %d | \n\t***check for expected value:", players);
    if (returnVal != -1){ 
      printf(" FAIL\n");
      printf ("\texpected return value of %d, but was %d\n", -1, returnVal);
    } 
    else{
      printf (" PASS\n");
    }
    //assert(returnVal == -1);

    // restart with a good game
    game = newGame();
    returnVal = initializeGame(players, k_Pass, randSeed, game);
    printf ("initializeGame() | method return | players %d | \n\t***check for expected value:", players); 
    if (returnVal != 0){ 
      printf(" FAIL\n");
      printf ("\texpected return value of %d, but was %d\n", 0, returnVal);
    } 
    else{
      printf (" PASS\n");
    }

    // test to make sure coins is set in the range 2 - 5
    printf ("initializeGame() |  coin  init   | players %d | \n\t***check for expected value:", players);
    if(game->coins < 2 || game->coins > 5){
      printf(" FAIL\n");
      printf("\texpected coins of 2-5, but was %d", game->coins);
    }
    else{
      printf(" PASS\n");
    }

    // test to make sure number of players is set correctly
    printf ("initializeGame() | number plyers | players %d | \n\t***check for expected value:", players);
    if(game->numPlayers != players){
      printf(" FAIL\n");
      printf("\texpected %d players, but was %d\n", players, game->numPlayers);
    }
    else{
      printf(" PASS\n");
    }

    // check to make sure each player's hand count is set correctly (5, 0, 0, 0)
    for(i = 0; i < players; i++){
      printf ("initializeGame() |   game  hand  | players %d | \n\t***check for expected value:", players);
      if(i == 0){
        if(game->handCount[i] != 5){
          printf(" FAIL\n");
          printf("\texpected handCount of %d, but was %d\n", 5, game->handCount[i]);
        }
        else{
          printf(" PASS\n");
        }
      }
      else {
        if(game->handCount[i] != 0){
          printf(" FAIL\n");
          printf("\texpected handCount of %d, but was %d\n", 0, game->handCount[i]);
        }
        else{
          printf(" PASS\n");
        }
      }
    }

    // check to make sure supply of treasure cards is set correctly
    printf ("initializeGame() | copper cards  | players %d | \n\t***check for expected value:", players);
    if(game->supplyCount[copper] != 60 - 7 * players){
      printf(" FAIL\n");
      printf("\texpected %d copper supply, but was %d\n", 60 - 7 * players, game->supplyCount[4]);
    }
    else{
      printf(" PASS\n");
    }
    
    printf ("initializeGame() | silver cards  | players %d | \n\t***check for expected value:", players);
    if(game->supplyCount[silver] != 40){
      printf(" FAIL\n");
      printf("\texpected %d silver supply, but was %d\n", 40, game->supplyCount[4]);
    }
    else{
      printf(" PASS\n");
    }

    printf ("initializeGame() |  gold  cards  | players %d | \n\t***check for expected value:", players);
    if(game->supplyCount[gold] != 30){
      printf(" FAIL\n");
      printf("\texpected %d gold supply, but was %d\n", 30, game->supplyCount[4]);
    }
    else{
      printf(" PASS\n");
    }
  }

  return 0;
}
