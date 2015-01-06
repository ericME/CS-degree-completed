/*

Eric Rouse
Homework 3

Unit Test 4:
updateCoins()
 
*/

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

int main() {
  int i;
  int seed = 1000;
  int numPlayer = 2;
  int maxBonus = 10; 
  int maxHandCount = 8;
  int bonus;
  int handCount;
  int player;
  int returnVal;
  int k[10] = {adventurer, council_room, feast, gardens, mine
               , remodel, smithy, village, baron, great_hall};
  struct gameState* game;


  for (player = 0; player < numPlayer; player++)
  {
    for (bonus = 0; bonus <= maxBonus; bonus++)
    {
      for (handCount = 1; handCount <= maxHandCount; handCount++)
      {
        // initialize a new game
        game = newGame();
        assert(initializeGame(numPlayer, k, seed, game) == 0);

        // test for a hand of all coppers
        game->handCount[player] = handCount;
        for(i = 0; i < handCount; i++){
          game->hand[player][i] = copper;
        }
        returnVal = updateCoins(player, game, bonus);
        // check for proper return value
        printf ("updateCoins() | method return | player %d | bonus %d | handCount %d | \n\t***check for expected value:", player, bonus, handCount);
        if (returnVal != 0){
          printf (" FAIL\n");
          printf ("\texpected return value of %d, but was %d", 0, returnVal);
        }
        else{
          printf (" PASS\n");
        }

        assert(returnVal == 0); 

        // check for right number of coins
        printf ("updateCoins() | copper count  | player %d | bonus %d | handCount %d | \n\t***check for expected value:", player, bonus, handCount);
        if (game->coins != (handCount * 1 + bonus)){ 
          printf (" FAIL\n");
          printf ("\texpected coin value of %d * %d + %d = %d, but was %d\n", handCount, 1, bonus, handCount * 1 + bonus, game->coins);
        } 
        else{
          printf (" PASS\n");
        }
        

        // test for a hand of all silvers
        printf ("updateCoins() | silver count  | player %d | bonus %d | handCount %d | \n\t***check for expected value:", player, bonus, handCount);
        game->handCount[player] = handCount;
        for(i = 0; i < handCount; i++){
          game->hand[player][i] = silver;
        }
        updateCoins(player, game, bonus);
        
        // check for right number of coins
        if (game->coins != (handCount * 2 + bonus)){ 
          printf (" FAIL\n");
          printf ("\texpected coin value of %d * %d + %d = %d, but was %d\n", handCount, 2, bonus, handCount * 2 + bonus, game->coins);
        } 
        else{
          printf (" PASS\n", player, bonus, handCount);
        }

        // test for a hand of all golds
        printf ("updateCoins() |  gold  count  | player %d | bonus %d | handCount %d | \n\t***check for expected value:", player, bonus, handCount);
        game->handCount[player] = handCount;
        for(i = 0; i < handCount; i++){
          game->hand[player][i] = gold;
        }
        updateCoins(player, game, bonus);
        // check for proper return value
        assert(returnVal == 0); 
        // check for right number of coins
        if (game->coins != (handCount * 3 + bonus)){ 
          printf (" FAIL\n", player, bonus, handCount);
          printf ("\texpected coin value of %d * %d + %d = %d, but was %d\n", handCount, 3, bonus, handCount * 3 + bonus, game->coins);
        } 
        else{
          printf (" PASS\n");
        }
      }
    }
  }

  return 0;
}
