#include <stdbool.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char* ansi_red = "\x1b[31m";
char* ansi_green = "\x1b[32m";
char* ansi_reset = "\x1b[0m";

#ifndef __MINIUNIT_H__
#define __MINIUNIT_H__

#define MU_SUCCESS 0
#define mu_start() int __mu_first_failure_line_number_or_0 = MU_SUCCESS
#define mu_end() return __mu_first_failure_line_number_or_0

#define mu_check(condition) \
	do { 																		\
		if (!(condition) && __mu_first_failure_line_number_or_0 == MU_SUCCESS) 	\
		{ 																		\
			__mu_first_failure_line_number_or_0 = __LINE__; 					\
		} \
	} while(false);

#define mu_check_strings_equal(s1, s2) mu_check(strcmp(s1, s2) == 0)

#define mu_run(function) \
	do { \
		if (function() == MU_SUCCESS) \
		{ \
			printf("%sTest passed: %s%s\n", ansi_green, (#function), ansi_reset); \
		} \
		else if (__LINE__ >= 1) \
		{ \
			printf("%sTest failed: %s at line %i%s\n", ansi_red, (#function), __LINE__, ansi_reset); \
		} \
	} while(false);

#endif /* end of include guard: __MINIUNIT_H__ */
