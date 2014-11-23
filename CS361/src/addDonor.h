#ifndef ADDDONOR_H
#define ADDDONOR_H

#define GENESEQUENCE_SIZE 5

struct donor_info {
  int id;
  char first_name[256];
  char last_name[256] ;
  char gene_sequence[GENESEQUENCE_SIZE + 1] ;
};
struct donor_info *addDonor(int exp_id, char* exp_fname, char* exp_lname, char* exp_geneseq);
struct donor_info *createDonor();

#endif