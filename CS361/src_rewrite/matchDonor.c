#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

//#include "unit_tests.h"

#define MAXDONOR 20

struct donor
{
     int id;
     char firstName[40];
     char lastName[40];
     char genSequence[40];
     int matches[40];
} donorRecords[MAXDONOR];

int countDonor = 0;

//Removes \n from char * input from fgets
char *removeNewLine(char *input) {
    int j;
    j = strlen(input)-1;
    if(input[j] == '\n') {
        input[j] = '\0';
    }
    return input;
}

//Adds donor to specified location in the donor array
void addDonor(int i, char *fName, char *lName, char *genes) {
    fName = removeNewLine(fName);
    lName = removeNewLine(lName);
    genes = removeNewLine(genes);
    donorRecords[i].id = i;
    strcpy(donorRecords[i].firstName, fName);
    strcpy(donorRecords[i].lastName , lName);
    strcpy(donorRecords[i].genSequence , genes);
    return;
}

//Removes donor from array, string fields replaced with 'empty' string.
void removeDonor(int i, int test) {
    int m;
    char *empt = "empty";
    char *input;
    char RawInput[10];
    if (test == 0){
        printf("Are you sure you want to delete records for %s %s? <y/n> ", donorRecords[i].firstName, donorRecords[i].lastName);
        fgets(RawInput, 10, stdin);
        //Conversion workaround, fgets wants a char array, removeNewLine input doesn't.
        input = RawInput;
        input = removeNewLine(input);
    }

    if(strcmp(input, "y")==0 || test == 1) {
        countDonor--;
        printf("Removing donor.\n");
        strcpy(donorRecords[i].firstName, empt);
        strcpy(donorRecords[i].lastName , empt);
        strcpy(donorRecords[i].genSequence , empt);
        for(m = i; m<MAXDONOR; m++) {
            if(m<MAXDONOR) {
                strcpy(donorRecords[m].firstName, donorRecords[m+1].firstName);
                strcpy(donorRecords[m].lastName , donorRecords[m+1].lastName);
                strcpy(donorRecords[m].genSequence , donorRecords[m+1].genSequence);
            }
            else if(m == MAXDONOR) {
                strcpy(donorRecords[m].firstName, empt);
                strcpy(donorRecords[m].lastName , empt);
                strcpy(donorRecords[m].genSequence , empt);
            }
        }
    }
    else if(strcmp(input, "n")==0) {
        printf("Remove cancelled.\n");
    }
    else {
        printf("Command unrecognized.\n");
    }
    return;
}

//Finds all matches for a specific Donor and stores information to array.
void matchDonor(int i) {
    int j;
    for(j=0; j<MAXDONOR; j++) {
        if(strcmp(donorRecords[i].genSequence, donorRecords[j].genSequence)==0) {
            donorRecords[i].matches[j] = 1;
        }
        else {
            donorRecords[i].matches[j] = 0;
        }
    }
    return;
}

//Displays matches found by 'matchDonor' method, if i>0, a specific ID number was specified, and only look to that ID, else, all was specified.
void displayMatches(int i) {
    int m, j;
    int foundMatches;

    if(i>0) {
        foundMatches = 0;
        //Generate list of matches before printing results.
        matchDonor(i);
        printf("Donors matching %s %s.\n", donorRecords[i].firstName, donorRecords[i].lastName);
        for(j=0; j<MAXDONOR; j++) {
            if(donorRecords[i].matches[j]==1 && i!=j) {
                foundMatches++;
                printf("\tMatch %d: %s %s\n", foundMatches, donorRecords[j].firstName, donorRecords[j].lastName);
            }
        }
        if(foundMatches == 0) {
            printf("\tNo matches found.\n");
        }
    }
    else {
    //Iterates through every donor in the array.
    for(m=1; m<=MAXDONOR; m++) {
        //If specific integer provided, find matches to that donor.
        //Else, if all specified, print all donor matches.
            foundMatches = 0;
            matchDonor(m);
            if(strcmp(donorRecords[m].firstName, "empty")!=0) {
                printf("Donors matching %s %s.\n", donorRecords[m].firstName, donorRecords[m].lastName);
            }
            else {
               foundMatches++;
            }
            for(j=0; j<MAXDONOR; j++) {
                //Special case to avoid printing matches for empty spots in the donor array.
                if(donorRecords[m].matches[j]==1 && m!=j && (strcmp(donorRecords[m].firstName, "empty")!=0)) {
                    foundMatches++;
                    printf("\tMatch %d: %s %s\n", foundMatches, donorRecords[j].firstName, donorRecords[j].lastName);
                }
            }
            if(foundMatches == 0) {
                printf("\tNo matches found.\n");
            }
    }
    }
    return;
}

//Replace original empty array, with empty strings replacing null values.
static void initilizeDonors() {
    int i;
    for(i = 0; i<=MAXDONOR; i++) {
        addDonor(i, "empty", "empty", "empty");
    }
}

static void listDonors(int maxDonors) {
    int i;
    for(i=0; i < maxDonors; i++) {
        //Weird way of handling what gets displayed, couldn't get the first array segment to
        if(strcmp(donorRecords[i].firstName, "empty")!=0) {
            printf("Donor ID: %d\n", donorRecords[i].id);
            printf("First Name: %s\n", donorRecords[i].firstName);
            printf("Last Name: %s\n", donorRecords[i].lastName);
            printf("Gene Sequence: %s\n", donorRecords[i].genSequence);
            printf("\n");
        }
    }
    return;
}

//unit test 1, test donor info
//verifies donor was created and correct data was initiated
int test_donor_info(struct donor *di, int exp_id, char* exp_fname, char* exp_lname, char* exp_geneseq) {

    int error = 0;
    int pass = 0;
    
    if(di->id != exp_id) {
        printf("Test failed! ID was: %d, expected: %d\n", di->id, exp_id);  
        error = 1;
    }

    if(strcmp(di->firstName, exp_fname) != 0) {
        printf("Test failed! First names do not match.\n");
        error = 1;
    }

    if(strcmp(di->lastName, exp_lname) != 0) {
        printf("Test failed! Last names do not match.\n");
        error = 1;
    }

    if(strcmp(di->genSequence, exp_geneseq) != 0) {
        printf("Test failed! Gene sequences do not match.\n");
        error = 1;
    }

    if(error == 0) {
        printf("Donor Info tests passed.\n");
        pass = 1;
    }

    return pass;
}

//unit test 2, test listing
//Verifies all donors are listed.
int test_donor_list(int maxDonors){
    char match[5];
    int pass = 0;

    printf("Verify the following two lists match (press enter when ready):\n");getchar();
    printf("\tList 1\n");
    listDonors(maxDonors);
    printf("\tList 2\n");
    printf("Donor ID: 1\nFirst Name: Darth\nLast Name: Vader\nGene Sequence: GATTACA\n\nDonor ID: 2\nFirst Name: Hans\nLast Name: Moleman\nGene Sequence: ACCACCT\n\nDonor ID: 3\nFirst Name: Eric\nLast Name: Idle\nGene Sequence: TACAGCT\n\nDonor ID: 4\nFirst Name: Stephen\nLast Name: Hawking\nGene Sequence: GATTACA\n\nDonor ID: 5\nFirst Name: Turd\nLast Name: Ferguson\nGene Sequence: AACCTGC\n\nDonor ID: 6\nFirst Name: Tom\nLast Name: Brokaw\nGene Sequence: GATTACA\n\nDonor ID: 7\nFirst Name: Norm\nLast Name: MacDonald\nGene Sequence: AACCTGC\n\nDonor ID: 8\nFirst Name: Super\nLast Name: Mario\nGene Sequence: TACAGCT\n");

    printf("Do they match (y/n)?\n");
    scanf("%s", match);
    if (strcmp(match,"y")==0 || strcmp(match, "Y") == 0){
        printf("Donor List test passed!\n");
        pass = 1;
    }
    else printf("Test failed!\n");
    return pass;
}

//unit test 3, test matching
//verifies donors match appropriately
int test_donor_match(){
    char match[5];
    int pass = 0;

    printf("Verify the following two lists match (press enter when ready):\n");
    getchar();

    printf("\tList 1\n");
    displayMatches(0);
    printf("\tList 2\n");
    printf("Donors matching Darth Vader.\n\tMatch 1: Stephen Hawking\n\tMatch 2: Tom Brokaw\nDonors matching Hans Moleman.\n\tNo matches found.\nDonors matching Eric Idle.\n\tMatch 1: Super Mario\nDonors matching Stephen Hawking.\n\tMatch 1: Darth Vader\n\tMatch 2: Tom Brokaw\nDonors matching Turd Ferguson.\n\tMatch 1: Norm MacDonald\nDonors matching Tom Brokaw.\n\tMatch 1: Darth Vader\n\tMatch 2: Stephen Hawking\nDonors matching Norm MacDonald.\n\tMatch 1: Turd Ferguson\nDonors matching Super Mario.\n\tMatch 1: Eric Idle\n");

    printf("Do they match (y/n)?\n");
    scanf("%s", match);
    if (strcmp(match,"y")==0 || strcmp(match, "Y") == 0){
        printf("Donor Match test passed!\n");
        pass = 1;
    }
    else printf("Test failed!\n");


    return pass;
}

//unit test 4, test removal
//verifies donors are removed

int test_donor_remove(struct donor *di){
    int pass = 0;
    int error = 0;
    int id = di->id;
    char fname[40];
    char lname[40];
    char genes[40];
    strcpy(fname, di->firstName);
    strcpy(lname, di->lastName);
    strcpy(genes, di->genSequence);
    removeDonor(id,1);


    printf("Attemtping to remove Donor: %s %s.\n", di->firstName, di->lastName);
    if(strcmp(di->firstName, fname) == 0) {
        printf("%s\n", di->firstName);
        printf("Test failed! First name not removed.\n");
        error = 1;
    }

    if(strcmp(di->lastName, lname) == 0) {
        printf("Test failed! Last name not removed.\n");
        error = 1;
    }

    if(strcmp(di->genSequence, genes) == 0) {
        printf("Test failed! Gene sequence not removed.\n");
        error = 1;
    }

    if(error == 0) {
        printf("Remove donor tests passed.\n");
        pass = 1;
    }

    return pass;
}


int main(int argc, char**argv) {
    char str[80];
    int maxDonors = MAXDONOR;
    int go = 1;
    int input;
    int i;
    const int NUMTESTS = 4;
    int passTotal;
    int pass[NUMTESTS];
    const char * testname[] = {"Donor Add and Info Verification, ", "Donor Listing, ", "Donor Matching, ", "Donor Removal, "};
    const char * passfail[] = {"failed.\n", "passed.\n"};
    char *inChar;
    char charInput[40] = "empty";
    char fName[40] = "empty";
    char lName[40] = "empty";
    char genSeq[40] = "empty";

    initilizeDonors();

    printf("Program accepts commands: add, remove, list, quit.\n**Or for unit tests, type test!\n");

	while(go == 1) {
        printf("Input command, type 'help' to list commands: ");
        fgets(str, 10, stdin);
        inChar = str;
        inChar = removeNewLine(inChar);

        if(strcmp(inChar, "add") == 0) {
            //Get donor information from user
            countDonor++;
            printf("Enter a first name: ");
            fgets(fName, 40, stdin);
            printf("Enter a last name: ");
            fgets(lName, 40, stdin);
            printf("Enter a gene sequence: ");
            fgets(genSeq, 40, stdin);
            addDonor(countDonor, fName, lName, genSeq);
            if(strcmp(fName, donorRecords[countDonor].firstName)==0 && strcmp(lName, donorRecords[countDonor].lastName)==0 && strcmp(genSeq, donorRecords[countDonor].genSequence)==0){
                printf("\n%s %s added successfully.\n", donorRecords[countDonor].firstName, donorRecords[countDonor].lastName);
            }
            else {
                printf("\nFailed to add donor.\n");
            }
        }

        else if(strcmp(inChar, "remove") == 0) {
            printf("Enter the ID for the donor to remove: ");
            fgets(charInput, 10, stdin);
            input = atoi(charInput);
            if(input<=countDonor || input>0) {
                removeDonor(input, 0);
            }
            else {
                printf("Specified ID does not exist in array.\n");
            }
        }
        else if(strcmp(inChar, "list") == 0) {
            printf("Listing all donor information: \n\n");
            listDonors(maxDonors);
        }
        else if(strcmp(inChar, "match") == 0) {
            printf("Enter 'all', or enter the ID of the specific donor to match: ");
            fgets(charInput, 10, stdin);
            inChar = charInput;
            inChar = removeNewLine(inChar);

            if(strcmp(inChar, "all")==0) {
                displayMatches(-1);
            }
            else {
                input = atoi(inChar);
                if(input<countDonor || input>0) {
                    displayMatches(input);
                }
                else {
                    printf("Specified ID does not exist in array.\n");
                }
            }
        }
        else if(strcmp(inChar, "test") == 0) {
            printf("Adding test donors to list.\n");
            srand ( time(NULL) );
            
            countDonor++;
            printf("Adding Darth Vader, expect all to pass: ");
            addDonor(countDonor, "Darth", "Vader", "GATTACA");
            pass[0] = test_donor_info(&donorRecords[countDonor], countDonor, "Darth", "Vader", "GATTACA");
            
            countDonor++;
            printf("Adding Hans Moleman, expect gene sequence to fail: ");
            addDonor(countDonor, "Hans", "Moleman", "ACCACCT");
            test_donor_info(&donorRecords[countDonor], countDonor, "Hans", "Moleman", "GATTACA");
            
            countDonor++;
            printf("Adding Eric Idle, expect last name to fail: ");
            addDonor(countDonor, "Eric", "Idle", "TACAGCT");
            test_donor_info(&donorRecords[countDonor], countDonor, "Eric", "Rouse", "TACAGCT");
            
            countDonor++;
            printf("Adding Stephen Hawking, expect first name to fail: ");
            addDonor(countDonor, "Stephen", "Hawking", "GATTACA");
            test_donor_info(&donorRecords[countDonor], countDonor, "Steven", "Hawking", "GATTACA");
            
            countDonor++;
            printf("Adding Turd Ferguson, expect all to fail: ");
            addDonor(countDonor, "Turd", "Ferguson", "AACCTGC");
            test_donor_info(&donorRecords[countDonor], countDonor+1, "turd", "ferguson", "aacctgc");
            
            countDonor++;
            printf("Adding Tom Brokaw, expect first and last name to fail: ");
            addDonor(countDonor, "Tom", "Brokaw", "GATTACA");
            test_donor_info(&donorRecords[countDonor], countDonor, "tom", "brokaw", "GATTACA");
            
            countDonor++;
            printf("Adding Norm MacDonald, expect ID to fail: ");
            addDonor(countDonor, "Norm", "MacDonald", "AACCTGC");
            test_donor_info(&donorRecords[countDonor], countDonor + 1, "Norm", "MacDonald", "AACCTGC");

            
            countDonor++;
            printf("Adding Super Mario, no test performed\n");
            addDonor(countDonor, "Super", "Mario", "TACAGCT");

            printf("Press enter to continue...");
            getchar();
            pass[1] = test_donor_list(maxDonors);
            pass[2] = test_donor_match();
            pass[3] = test_donor_remove(&donorRecords[rand()%countDonor]);
            printf("Test suite summary:\n");
            for(i = 0; i < NUMTESTS; i++){
                printf("\tTest %d, ", i+1);
                printf(testname[i]);
                printf(passfail[pass[i]]);
                passTotal += pass[i];
            }
            printf("pass rating of: %'.2f\n%%", (float)passTotal/NUMTESTS); 
            exit(0);
        }
        else if(strcmp(inChar, "help") == 0) {
            printf("Commands are: \nadd: Adds a specified number to the dynamic array.\nremove: Removes a specified number from the dynamic array.\nlist: Lists all numbers currently in dynamic array.\nmatch: Finds all donors matching specified donor.\n");
        }
        else if(strcmp(inChar, "quit") == 0) {
            go = 0;
        }
        else {
            printf("Command not recognized, please enter 'add, 'remove', 'list', match, test, or 'quit'\n");
        }
    }
    return 0;
}
