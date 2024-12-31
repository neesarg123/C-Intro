#include <stdio.h>

// maximum buffer length for directive
#define MAX_LENGTH_DIRECTIVE 10

// number of directives
#define NUM_OF_DIRECTIVES 9

// maximum buffer length for brackets/parenthesis/etc.
#define MAX_LENGTH_BUFF_OPEN_CLOSE 1000


// array of derictives
const char *DIRECTIVES[] = {"define", "undef", "include", "ifdef", "ifndef", "if", "else", "elif", "endif"};

// boolean to check if we are processing a directive
int IN_DIRECTIVE = 0;

// buffer for directive
char DIRECTIVE_BUFFER[MAX_LENGTH_DIRECTIVE];

// boolean to check if we are in single line comment or multi-line comment
int IN_SINGLE_LINE_COMMENT = 0;
int IN_MULTI_LINE_COMMENT = 0; 

// buffer for brackets
char OPEN_CLOSE_BUFFER[MAX_LENGTH_BUFF_OPEN_CLOSE]; 

// index for brackets
int OC_BUFF_IDX = 0;

// SUCCESS
int SUCCESS = 0;
// ERROR
int ERROR = 1;

// clear/empty DIRECTIVE_BUFFER
void clear_directive_buffer();

// routine for handling directives
int handle_directives();

// checking valid DIRECTIVE_BUFFER
int check_directive_buffer(const char* c);

// handle opening comment
int handle_opening_comment();

// handle closing comment
int handle_closing_comment();

// clear/empty OPEN_CLOSE_BUFFER
void clear_open_close_buffer();

// pop char
int pop_char_open_close_buffer();

// handle opening bracket
int handle_opening_bracket();

// handle closing bracket
int handle_closing_bracket();

// handle new line
int handle_new_line();

void clear_directive_buffer() {
	for (int i = 0; i < MAX_LENGTH_DIRECTIVE; i++) {
		DIRECTIVE_BUFFER[i] = '\0';
	}
}

int check_directive_buffer(const char* c) {
	int i = 0;

	for (i = 0; c[i] != '\0'; i++) {
		if (DIRECTIVE_BUFFER[i] != c[i]) {
			return ERROR;	
		}
	}

	if (DIRECTIVE_BUFFER[i] != '\0') {
		return ERROR;	
	}

	return SUCCESS;
}

int handle_directives() {
	int c;
	int l = 0;

	while ((c = getchar()) != ' ' && c != '\t' && c != '\n') {
		if (l >= MAX_LENGTH_DIRECTIVE) {
			return 1;	
		}
		DIRECTIVE_BUFFER[l] = c;
		++l;
	} 

	for (int i = 0; i < NUM_OF_DIRECTIVES; i++) { 
		if (check_directive_buffer(DIRECTIVES[i]) == SUCCESS)
			return SUCCESS;
	}
	
	return 2;
}

int handle_opening_comment() {
	int c;

	if ((c = getchar()) == '/') {
		if (IN_MULTI_LINE_COMMENT == 0) {
			IN_SINGLE_LINE_COMMENT = 1;	
		}
	} else if (c == '*') {
		if (IN_MULTI_LINE_COMMENT == 1) {
			return 1;
		}
		if (IN_SINGLE_LINE_COMMENT == 0) {
			IN_MULTI_LINE_COMMENT = 1;	
		}
	} else {
		if (IN_MULTI_LINE_COMMENT == 0) {
			return 2;
		}
	}

	return SUCCESS;
}

int handle_closing_comment() {
	int c;

	if ((c = getchar()) == '/') {
		if (IN_MULTI_LINE_COMMENT == 1)	{
			IN_MULTI_LINE_COMMENT = 0;	
		} else {
			return 1;
		}
	}
	else {
		if (IN_MULTI_LINE_COMMENT == 0 && IN_SINGLE_LINE_COMMENT == 0) {
			return 2;
		}
	}

	return SUCCESS;
}

void clear_open_close_buffer() {
	for (int i = 0; i < MAX_LENGTH_BUFF_OPEN_CLOSE; i++) {
		OPEN_CLOSE_BUFFER[i] = '\0';		
	}
}

int pop_char_open_close_buffer() {
	if (OC_BUFF_IDX == 0) {
		return ERROR;
	} else {
		return OPEN_CLOSE_BUFFER[--OC_BUFF_IDX];	
	}
}

int handle_opening_bracket() {
	if (OC_BUFF_IDX >= MAX_LENGTH_BUFF_OPEN_CLOSE) {
		return 1;
	}

	OPEN_CLOSE_BUFFER[OC_BUFF_IDX] = '[';
	++OC_BUFF_IDX;

	return SUCCESS;
}

int handle_closing_bracket() {
	int ch;

	if ((ch = pop_char_open_close_buffer()) != '[')	{
		return 1;
	}

	return SUCCESS;
}

int handle_new_line() {
	IN_SINGLE_LINE_COMMENT = 0;

	if (OC_BUFF_IDX != 0) {
		return 1;
	}

	return 0;
}

int main() {	
	int c, r;

	clear_open_close_buffer();

	while ((c = getchar()) != EOF) {
		IN_DIRECTIVE = 0;

		if (c == '#' && IN_SINGLE_LINE_COMMENT == 0 && IN_MULTI_LINE_COMMENT == 0) {
			IN_DIRECTIVE = 1;	
			clear_directive_buffer();
			if ((r = handle_directives()) == 1) {
				printf("ran out of space to allocate for directive. It must be invalid\n");
				return ERROR;
			} else if (r == 2) {
				printf("Directive Validation failure\n");	
				return ERROR;
			}
		}

		if (c == '/') {
			if ((r = handle_opening_comment()) == 1) {
				printf("Syntax error while creating multi-line comment\n");
				return ERROR;
			} else if (r == 2) {
				printf("Syntax error while creating comment\n");
				return ERROR;	
			}
		}
		
		if (c == '*') {
			if ((r = handle_closing_comment()) == 1) {
				printf("Syntax error near * -- comment never started\n");	
				return ERROR;	
			} else if (r == 2) {
				printf("Syntax error near * -- not in a comment\n");	
				return ERROR;	
			}
		}

		if (c == '[') {
			if ((r = handle_opening_bracket()) == 1) {
				printf("Maximum buffer length reach for open and close\n");	
				return ERROR;
			}
		}

		if (c == ']') {
			if ((r = handle_closing_bracket()) == 1) {
				printf("No opening bracket found\n");	
				return ERROR;
			}
		}

		if (c == '\n') {
			if ((r = handle_new_line()) == 1) {
				printf("Unclosed bracket/parenthesis/etc.\n");	
				return ERROR;
			}
		}
	}

	return SUCCESS;
}
