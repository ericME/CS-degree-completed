#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "addDonor.h"
#include "unit_tests.h"

void removeData(struct donor_info *di) {

    printf("Removing Data.../n");

    if (di->first_name != 0)
    {
        free(di->first_name);
    }

    if (di->last_name != 0)
    {
        free(di->last_name);
    }

    if (di->gene_sequence != 0)
    {
        free(di->gene_sequence);
    }
}

void removeDonor(struct donor_info *di) {

    if ((di->first_name != 0) || (di->last_name != 0) || (di->gene_sequence != 0))
    {

        free(di);

    }
}