//
// Lexer for .A language
//==================================================================================
//
//	Written by Yuré Vanderbruggen
//	last edit: 19/7/2018
//	------------------------------
//	TODO: Add identifier, keyword, operator arrays or enums for iteration;
//	!Notice:  
//
//=================================================================================

#include <stdio.h>
#include <string.h>
#include <stdbool.h>

const char *SEPERATORS[] = {";", "(", ")", "{", "}", " ", "."};
const int SIZEOF_SEPERATORS = sizeof(SEPERATORS)/sizeof(SEPERATORS[0]);
const char *KEYWORDS[] = {"let", "print"};
const int SIZEOF_KEYWORDS = sizeof(KEYWORDS)/sizeof(KEYWORDS[0]);
const char *OPERATORS[] = {"=", "+"};
const int SIZEOF_OPERATORS = sizeof(OPERATORS)/sizeof(OPERATORS[0]);

typedef enum {
	identifier,
	keyword,
	seperator,
	operator,
	literal,
	comment
} name_t;

typedef struct{
	name_t type;
	char value[50];
} token_t;

typedef struct {
	token_t* token;
} logical_link;

token_t CreateToken(name_t Type, const char *Value){
	token_t t;
	t.type = Type;
	strcpy(t.value, Value);
	return t;
}

bool ArrayContains(const char * Array[], const int Elements, const char Value){
	for(int i = 0; i < Elements; i++){
		if ((int)*Array[i] == (int)Value){
			return true;
		}
	}
	return false;
}

void ClearArray(char * Array){
	for(int i = 0; i < (sizeof(Array)/sizeof(Array[0])); i++){
		Array[i] = '\0';
	}
}

token_t Tokenize(const char * input){
	token_t t;
	t.type = literal;

	for (int i = 0; i < SIZEOF_KEYWORDS; i++){
		if (strcmp(KEYWORDS[i], input)==0){
			t.type = keyword;
			strcpy(t.value, input);
		}
	}

	for (int i = 0; i < SIZEOF_OPERATORS; i++){
		if (strcmp(OPERATORS[i], input)==0){
			t.type = operator;
			strcpy(t.value, input);
		}
	}

	if (t.type == literal){
		strcpy(t.value, input);
	}
	
	return t;
}

token_t* Lex(char * input){
	static token_t Tokens[50]; // array of all tokens
	int tokenCount = 0; // tokencount to add new tokens to the array
	int bufferCount = 0; // count for the buffer to place a new character in it
	char buffer[50]; // the buffer for the input
	bool eoi = false; // end of input boolean value

	for(int i = 0; i < strlen(input); i++)
	{
		// determine if end of input is reached
		eoi = (i == ((int)strlen(input)-1)) ? true : false;

		// if the character equals a seperator
		if (!ArrayContains(SEPERATORS, SIZEOF_SEPERATORS, input[i]) && !eoi)
		{
			buffer[bufferCount] = input[i];
			bufferCount++;
		}
		// Seperator found
		else if ((buffer[0] != *"\0") || (input[i] != *"\0")) {
			// end of input reached, check if there was something in the buffer and if so...
			// add the last char from the input to the buffer
			if (i == ((int)strlen(input)-1)) {
				buffer[bufferCount] = input[i];
			}

			// Tokenize
			Tokens[tokenCount] = Tokenize(buffer);
			tokenCount++;

			// Clear variables
			bufferCount = 0;
			ClearArray(buffer);
		}
	}

	return Tokens;
}