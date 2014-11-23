#ifndef UNIT_TESTS_H
#define UNIT_TESTS_H

#include "addDonor.h"
#include "removeDonor.h"


void test_donor_info(struct donor_info *di, int exp_id, char* exp_fname, char* exp_lname, char* exp_geneseq);
//remove info test here

#endif