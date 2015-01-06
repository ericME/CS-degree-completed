/* inputChar and inputString by Robert Kety - CS362 */
#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<time.h>
#include<assert.h>

#define MAX_ASCII 256

char inputChar(void);
char* inputString(void);
void testme(void);

int main(int argc, char *argv[])
{
    srand(time(NULL));
    testme();
    return 0;
}

char inputChar(void){
	int randRangeMax = 9;
	int randChar = rand() % randRangeMax;	//Increase this variable to allow for additional random ASCII-valid values (0 - 127)
	
	assert(randRangeMax >= 9); //Must be >= 9 to provide the likely domain of valid characters
	
	switch (randChar){
		case 0:
			return '[';
		case 1:
			return ']';
		case 2:
			return '(';
		case 3:
			return ')';
		case 4:
			return '{';
		case 5:
			return '}';
		case 6:
			return 'a';
		case 7:
			return 'x';
		case 8:
			return ' ';
		default:
			return rand() % MAX_ASCII;
	}
}

char *inputString(void){
    int strLen = 5, i, randChar;
	char* randString = malloc(strLen);
	int randRangeMax = 4;	//Increase this variable to allow for additional random ASCII-valid values (0 - 127)
	
	assert(randRangeMax >= 4); //Must be >= 4 to provide the likely domain of valid characters
	assert(strLen >= 5); //All strings < 5 are invalid
	
	for(i = 0; i < strLen; i++){
		randChar = rand() % randRangeMax;
		switch (randChar){
			case 0:
				randString[i] = 'r';
				break;
			case 1:
				randString[i] = 's';
				break;
			case 2:
				randString[i] = 't';
				break;
			case 3:
				randString[i] = 'e';
				break;	
			default:
				randString[i] = rand() % MAX_ASCII;
				break;
		}
	}
    
	randString[strLen] = '\0';
	
	return randString; 
}

void testme(void)
{
  int tcCount = 0;
  char *s;
  char c;
  int state = 0;
  while (1)
  {
    tcCount++;
    c = inputChar();
    s = inputString();
    printf("Iteration %d: c = %c, s = %s, state = %d\n", tcCount, c, s, state);

    if (c == '[' && state == 0) state = 1;
    if (c == '(' && state == 1) state = 2;
    if (c == '{' && state == 2) state = 3;
    if (c == ' ' && state == 3) state = 4;
    if (c == 'a' && state == 4) state = 5;
    if (c == 'x' && state == 5) state = 6;
    if (c == '}' && state == 6) state = 7;
    if (c == ')' && state == 7) state = 8;
    if (c == ']' && state == 8) state = 9;
    if (s[0] == 'r' && s[1] == 'e'
       && s[2] == 's' && s[3] == 'e'
       && s[4] == 't' && s[5] == '\0'
       && state == 9)
    {
      printf("error ");
      exit(200);
    }
  }
}



