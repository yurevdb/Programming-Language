//
// Cli interface for .A language
//==================================================================================
//
//	Written by Yuré Vanderbruggen
//	last edit: 19/7/2018
//	------------------------------
//	TODO:
//	!Notice:
//
//=================================================================================

// Includes
#include "lexer.h"

instruction_t* Lex(char * input);


// The main function
int main(int argc, char** argv)
{
	char expr[100];

	printf("> Type Some Code in .A\n  Or if you want to quit type !quit\n");
	printf("> ");

	while(1){
		scanf("%[^\n]%*c", &expr);

		// command to exit the environment
		if (strcmp(expr, "!quit")==0){
			break;
		}
		// other commands to add

		instruction_t *instructions = Lex(expr);
		
		int instructCount = 0;
		for (int i = 0; i < 50; i++){
			if (instructions[i].Number){
				instructCount++;
			}
		}
		printf("%d instruction(s) found\n", instructCount);

		printf("> ");
	}

	return 0;	
}

