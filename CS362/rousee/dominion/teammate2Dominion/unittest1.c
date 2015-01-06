/*

Eric Rouse
Homework 3

Unit Test 1:
kingdomCards()

*/

#include "dominion.h"
#include "dominion_helpers.h"
#include <string.h>
#include <stdio.h>
#include <assert.h>
#include "rngs.h"

int main() {
  int i;
  int * kingCards;
  int k[10] = {adventurer, council_room, feast, gardens, mine
               , remodel, smithy, village, baron, great_hall};

  kingCards = kingdomCards(adventurer, council_room, feast, gardens, mine
               , remodel, smithy, village, baron, great_hall);

  // test for correct cards added to deck
  for (i = 0; i < 10; i++)
  {
    printf ("kingdomCards() | return array eval | card %d | \n\t***check for expected value:", k[i]);
    if (k[i] == kingCards[i]){
      printf(" PASS\n");
    }
    else{
      printf(" FAIL\n");
      printf("\tExpected %d card, but was %d\n", k[i], kingCards[i]);
    }
  }
  return 0;
}
