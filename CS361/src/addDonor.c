#include "addDonor.h"
#include "unit_tests.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct donor_info *addDonor(int exp_id, char* exp_fname, char* exp_lname, char* exp_geneseq) {

    struct donor_info *di = (struct donor_info*)malloc(sizeof(struct donor_info));

    strcpy(di->first_name,exp_fname);
    strcpy(di->last_name, exp_lname);
    strcpy(di->gene_sequence, exp_geneseq);
    di->id = exp_id+1;
    
    return di;
}

struct donor_info *createDonor(int last_id) {

    int i;
    char first_name[256];
    char last_name[256];
    char gene_sequence[GENESEQUENCE_SIZE + 1];
    struct donor_info *di;

    gene_sequence[GENESEQUENCE_SIZE] = '\0';
    printf("Donor first name?\n");
    scanf("%s", first_name);

    printf("Donor last name?\n");
    scanf("%s", last_name);

    for(i = 0; i < GENESEQUENCE_SIZE; i++) {
        printf("What is entry %d in the gene sequence?\n", i + 1);
        scanf(" %c", &gene_sequence[i]);
        //verify input?
    }

    di = addDonor(last_id, first_name, last_name, gene_sequence);

    printf("Donor added!\n");
    printf("ID: %d\n", di->id);
    printf("First name: %s\n", di->first_name);
    printf("Last name: %s\n", di->last_name);
    printf("Gene sequence: %s\n", di->gene_sequence);
    
    return di;
}