#include <stdio.h>
#include <stdbool.h>
#include <limits.h>
#include <string.h>

//Emin Salih ACIKGOZ ID:22050111032

int Q1_for_solution(char* haystack, char* needle) {
	int haystackLen = strlen(haystack);
	int needleLen = strlen(needle);

	if (needleLen == 0) return 0; // Needle is empty, return 0

	for (int i = 0; i <= haystackLen - needleLen; i++) {
		if (haystack[i] == needle[0]) { // Found potential needle
			int j;
			for (j = 1; j < needleLen; j++) {
				if (haystack[i + j] != needle[j]) {
					break; // Break if characters don't match
				}
			}
			if (j == needleLen) {
				return i; // Found the needle
			}
		}
	}

	return -1; // Needle not found
}


int Q1_for_to_goto_solution(char* haystack, char* needle) {
	int haystackLen = strlen(haystack);
	int needleLen = strlen(needle);

	if (needleLen == 0) return 0; // Needle is empty, return 0

	int i = 0;
	int j;
	goto test_a;
loop_a:
	if (haystack[i] == needle[0]) { // Found potential needle
		j = 1;
	loop_b:
		if (j >= needleLen)
			return i; //needle found
		if (haystack[i + j] != needle[j])
			goto done_b; // Break out of inner loop if characters do not match
		j++;
		goto loop_b;
	done_b:
	}
	i++;
test_a:
	if (i <= haystackLen - needleLen)
		goto loop_a;

done_a:
	return -1; // Needle not found
}


int Q2_while_solution(char* s) {
	const char* curr = s;
	int res = 0;
	bool sign = false;

	while (*curr != '\0') {//Skips whitespaces and processes sign
		if (*curr == ' ') {
			curr++;
		}
		else if (*curr == '-') {
			sign = true;
			curr++;
			break;
		}
		else if (*curr == '+') {
			curr++;
			break;
		}
		else if (*curr >= '0' && *curr <= '9') {
			break;
		}
		else {
			return 0; // Invalid input
		}
	}

	while (*curr >= '0' && *curr <= '9') {//Parses an int until an invalid char is encountered
		int digit = *curr - '0';
		if (res > (INT_MAX - digit) / 10) {
			return (sign) ? INT_MIN : INT_MAX;
		}
		res = res * 10 + digit;
		curr++;
	}

	return (sign) ? -res : res;
}


int Q2_while_to_jm_goto_solution(char* s) {
	const char* curr = s;
	int res = 0;
	bool sign = false;

	// Skip leading whitespace and process sign
	goto test_a;
loop_a:
	if (*curr == ' ') {
		curr++;
	}
	else if (*curr == '-') {
		sign = true;
		curr++;
		goto done_a;
	}
	else if (*curr == '+') {
		curr++;
		goto done_a;
	}
	else if (*curr >= '0' && *curr <= '9') {
		goto done_a;
	}
	else {
		return 0; // Invalid input
	}
test_a:
	if (*curr != '\0')
		goto loop_a;
done_a:

	// Process digits into an integer
	goto test_b;
loop_b:
	int digit = *curr - '0';
	if (res > (INT_MAX - digit) / 10) {
		return (sign) ? INT_MIN : INT_MAX;
	}
	res = res * 10 + digit;
	curr++;
	goto test_b;
test_b:
	if (*curr >= '0' && *curr <= '9') {
		goto loop_b;
	}
done_b:
	return (sign) ? -res : res;
}


int Q2_while_to_dw_goto_solution(char* s) {
	const char* curr = s;
	int res = 0;
	bool sign = false;


	if (*curr == '\0')//Test case to ensure we do not operate on an empty string
		goto done_a;
loop_a://Skips whitespaces and proccesses sign
	if (*curr == ' ') {
		curr++;
	}
	else if (*curr == '-') {
		sign = true;
		curr++;
		goto done_a;
	}
	else if (*curr == '+') {
		curr++;
		goto done_a;
	}
	else if (*curr >= '0' && *curr <= '9') {
		goto done_a;
	}
	else {
		return 0; // Invalid input
	}
	if (*curr != '\0')
		goto loop_a;
done_a:

	if (!(*curr >= '0' && *curr <= '9')) //ensures that the do-while loop only encounters numbers
		goto done_b;
loop_b://Parse an integer from digits
	int digit = *curr - '0';
	if (res > (INT_MAX - digit) / 10) {
		return (sign) ? INT_MIN : INT_MAX;
	}
	res = res * 10 + digit;
	curr++;
	if (*curr >= '0' && *curr <= '9') {
		goto loop_b;
	}
done_b:
	return (sign) ? -res : res;
}


void testQ1() {
	// Test cases for Q1
	char haystack1[] = "example";
	char needle1[] = "exam";
	char haystack2[] = "goosebump";
	char needle2[] = "foo";

	printf("Testing Q1 methods:\n");

	// Test Q1_for_solution
	printf("Q1_for_solution:\n");
	printf("Output for needle1: %d\n", Q1_for_solution(haystack1, needle1));
	printf("Output for needle2: %d\n", Q1_for_solution(haystack1, needle2));

	// Test Q1_for_to_goto_solution
	printf("Q1_for_to_goto_solution:\n");
	printf("Output for needle1: %d\n", Q1_for_to_goto_solution(haystack1, needle1));
	printf("Output for needle2: %d\n", Q1_for_to_goto_solution(haystack1, needle2));
}


void testQ2() {
	// Test cases for Q2
	char s1[] = "  +413";
	char s2[] = "-712";
	char s3[] = " 123goosebump";

	printf("Testing Q2 methods:\n");

	// Test Q2_while_solution
	printf("Q2_while_solution:\n");
	printf("Output for s1: %d\n", Q2_while_solution(s1));
	printf("Output for s2: %d\n", Q2_while_solution(s2));
	printf("Output for s3: %d\n", Q2_while_solution(s3));

	// Test Q2_while_to_jm_goto_solution
	printf("Q2_while_to_jm_goto_solution:\n");
	printf("Output for s1: %d\n", Q2_while_to_jm_goto_solution(s1));
	printf("Output for s2: %d\n", Q2_while_to_jm_goto_solution(s2));
	printf("Output for s3: %d\n", Q2_while_to_jm_goto_solution(s3));

	// Test Q2_while_to_dw_goto_solution
	printf("Q2_while_to_dw_goto_solution:\n");
	printf("Output for s1: %d\n", Q2_while_to_dw_goto_solution(s1));
	printf("Output for s2: %d\n", Q2_while_to_dw_goto_solution(s2));
	printf("Output for s3: %d\n", Q2_while_to_dw_goto_solution(s3));
}


void runTests() {
	testQ1();
	testQ2();
}


int main() {
	runTests();
	return 0;
}