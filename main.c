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

token_t* Lex(char * input);


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

		token_t *toks = Lex(expr);

		logical_link link;
		link.token = NULL;
		
		for (int i = 0; i < 50; i++){
			if (toks[i].type) {
				printf("Type: %d | Value: %s\n", toks[i].type, toks[i].value);
			}
		}

		printf("> ");
	}

	return 0;	
}

