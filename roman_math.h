#ifndef ROMAN_MATH_H
#define ROMAN_MATH_H

int convert_to_integer(const char *numeral);
char *convert_to_numeral(int integer);

char *add(const char *num_one, const char *num_two);
char *subtract(const char *num_one, const char *num_two);

#endif /* ROMAN_MATH_H */