/* Test Driver (For Unit Testing) */

#include <common.h>
#include <words.h>

/*
 * Assertions for sanity checks
 */
void assertTrue(int a, char* msg) {
    if(!a) {
	printf("ASSERTION FAILURE: %s\n", msg);
	exit(1);
    }
}
void assertEqual(int a, int b, char* msg) {
    if(msg == NULL) {
	msg = "%d == %d";
    }
    assertTrue(a == b, msg);
}

/* 
 * It should capture the output of a single function
 * And output to stdout.
 *
 * Use assertions to verify sanity, but output the value
 * that the function returns. (Including values returned
 * through pointers)
 *
 * USAGE: test-driver FUNCTION ARGS...
 *
 * Note: When this gets larger, each will get its own function
 */
int main(int argc, char** argv) {
    assertTrue(argc >= 2, "Incorrect num of args");
    
    if(strcmp(argv[1], "readWords") == 0) {
	/*
	 * readWords
	 * INPUT: words file
	 * OUTPUT: words, line by line (should be same as input)
	 */

	assertEqual(argc, 3, "Incorrect num of args");

	int numWords;

	char** words = readWords(argv[2], &numWords);

	printf("%d\n", numWords);
	int i;
	for(i = 0; i < numWords; i++) {
	    printf("%s\n", words[i]);
	}
    }

    return 0;
}
