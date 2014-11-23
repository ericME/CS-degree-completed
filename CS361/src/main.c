#include <stdio.h>
#include <stdlib.h>
#include "addDonor.h"
#include "removeDonor.h"
#include "unit_tests.h"
#include <string.h>
//int strcmp( const char *str1, const char *str2 ); 

int main(void) {
    //add donor unit_tests
    struct donor_info *test_di;
    //All items fail
    printf("***ALL ITEMS SHOULD FAIL***\n");
    test_di = addDonor(22, "Fake", "Fakerson", "AAAAA");
    test_donor_info(test_di, 25, "Test", "McTester", "GATTC");
    //All items pass
    printf("***ALL ITEMS SHOULD PASS***\n");
    test_di = addDonor(24, "Test", "McTester", "GATTC");
    test_donor_info(test_di, 25, "Test", "McTester", "GATTC");

    createDonor(30);

    return 0;
}