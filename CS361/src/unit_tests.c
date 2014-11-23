#include "unit_tests.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void test_donor_info(struct donor_info *di, int exp_id, char* exp_fname, char* exp_lname, char* exp_geneseq) {

    int error = 0;
    
    if(di->id != exp_id) {
        printf("Test failed! ID was: %d, expected: %d\n", di->id, exp_id);  
        error = 1;
    }

    if(strcmp(di->first_name, exp_fname) != 0) {
        printf("Test failed! First names do not match.\n");
        error = 1;
    }

    if(strcmp(di->last_name, exp_lname) != 0) {
        printf("Test failed! Last names do not match.\n");
        error = 1;
    }

    if(strcmp(di->gene_sequence, exp_geneseq) != 0) {
        printf("Test failed! Gene sequences do not match.\n");
        error = 1;
    }

    if(error == 0) {
        printf("All tests passed.\n");
    }

    return;
}