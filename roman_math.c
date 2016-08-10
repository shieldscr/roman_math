#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "roman_math.h"

const int NUMERAL_BUFFER_SIZE = 16;
const int OPERAND_MAX=3999;
const char *RANGE_ERROR_MESSAGE = "Operand must be between 1 and 3999";
const char *NULL_ERROR_MESSAGE = "Operand must not be NULL";
const char *OPERAND_ORDER_MESSAGE = "Operand two cannot be greater than operand one";

char numerals[7] = {'I', 'V', 'X', 'L', 'C', 'D', 'M'};
int integers[7] = {1, 5, 10, 50, 100, 500, 1000};

int to_roman_integers[13] = {1000, 900, 500, 400, 100, 90, 50, 40, 10, 9, 5, 4, 1};
char *to_roman_characters[13] = {"M", "CM", "D", "CD", "C", "XC", "L", "XL", "X", "IX", "V", "IV", "I"};

static int index_of(const char *value, const char find) {
	const char *first = strchr(value, find);
	if(first) {
		return first - value;
	} else {
		return -1;
	}
}

static int is_valid_range(const int *number_one, const int *number_two) {
	if(*number_one >= OPERAND_MAX || *number_two >= OPERAND_MAX
		|| number_one == NULL || number_two == NULL) {
		return -1;
	} else {
		return 0;
	}
}

int convert_to_integer(const char *numeral) {

	int previousValue = 0;
	int returnInteger = 0;
	for(int i = (strlen(numeral) - 1); i >= 0; i--) {
		int numeralIndex = index_of(numerals, numeral[i]);
		int integerIndexValue = integers[numeralIndex];

		if(integerIndexValue < previousValue) {
			returnInteger -= integerIndexValue;
		} else {
			returnInteger += integerIndexValue;
		}

		previousValue = integerIndexValue;
	}

	return returnInteger;
}

char *convert_to_numeral(int integer) {
	char *return_buffer = calloc(NUMERAL_BUFFER_SIZE, sizeof(char));

	for(int i = 0; i < (sizeof(to_roman_integers)/sizeof(to_roman_integers[0])); i++) {
	 	while (to_roman_integers[i] <= integer) {
	     	integer -= to_roman_integers[i];
	     	strcat(return_buffer, to_roman_characters[i]);
	    }
	}
	char *return_copy = calloc(NUMERAL_BUFFER_SIZE, sizeof(return_buffer));
	strcpy(return_copy, return_buffer);
	free(return_buffer);

	return return_copy;
}

char *add(const char *num_one, const char *num_two) {
	if(num_one == NULL || num_two == NULL) {
		return (char *)NULL_ERROR_MESSAGE;
	}

	const int integer_value_one = convert_to_integer(num_one);
	const int integer_value_two = convert_to_integer(num_two);

	if(is_valid_range(&integer_value_one, &integer_value_two) != 0) {
		return (char *)RANGE_ERROR_MESSAGE;
	}

	int total = integer_value_one + integer_value_two;

	char *final_numeral = convert_to_numeral(total);

	return final_numeral;
}

char *subtract(const char *num_one, const char *num_two) {
	if(num_one == NULL || num_two == NULL) {
		return (char *)NULL_ERROR_MESSAGE;
	}
	int integer_value_one = convert_to_integer(num_one);
	int integer_value_two = convert_to_integer(num_two);

	if(is_valid_range(&integer_value_one, &integer_value_two) != 0) {
		return (char *)RANGE_ERROR_MESSAGE;
	} else if(integer_value_two > integer_value_one) {
		return (char *)OPERAND_ORDER_MESSAGE;
	}

	int total = integer_value_one - integer_value_two;

	char *final_numeral = convert_to_numeral(total);

	return final_numeral;
}