/* Calculate a grade from a mark. */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <stdbool.h>
#include <assert.h>

// Integer constants representing grades.
enum { G1, G21, G22, G3, Fail, Invalid };


// Convert a mark string into an integer.
int convert(int n, const char mark[]) {
    return atoi(mark);
}

// Check whether a mark string is properly formatted and in range.
bool valid(int n, const char mark[]) {
    if (n > 3) return false;
    
    else if (n == 1) {
        if (isdigit(mark[0]) == false) return false;
        else return true;
    }
    else if (n == 2) {
        if (mark[0] == '0') return false;
        else if (isdigit(mark[0]) == false) return false;
        else if (isdigit(mark[1]) == false) return false;
        else return true;
    }

    else if (n == 3) {
        if (mark[0] == '0') return false;
        else if ((mark[0] == '0') && (mark[1] == '0')) return false;
        else if (isdigit(mark[0]) == false) return false;
        else if (isdigit(mark[1]) == false) return false;
        else if (isdigit(mark[2]) == false) return false;
        else if (convert(n, mark) > 100) return false;
        else return true;

    }
    else return true;
    
}
// Convert a mark string into a grade.
int grade(int n, const char mark[]) {
    
    int grade = convert(n, mark);

    if (valid(n, mark) == false) 
        return Invalid;
    else
        if (grade >= 70) return G1;
        if (grade >= 60) return G21;
        if (grade >= 50) return G22;
        if (grade >= 40) return G3;
        else return Fail;

}

// -----------------------------------------------------------------------------
// User interface and testing.

// Print out a grade.
void print(int grade) {
    if (grade == G1) printf("First\n");
    else if (grade == G21) printf("Upper second\n");
    else if (grade == G22) printf("Lower second\n");
    else if (grade == G3) printf("Third\n");
    else if (grade == Fail) printf("Fail\n");
    else if (grade == Invalid) printf("Invalid mark\n");
}

// Check that you haven't changed the grade constants.  (If you do, it spoils
// automatic marking, when your program is linked with a test program.)
void checkConstants() {
    assert(G1==0 && G21==1 && G22==2 && G3==3 && Fail==4 && Invalid==5);
}

// Test each grade (tests 1 to 5)
void testGrades() {
    assert(grade(2, "35") == Fail);
    assert(grade(2, "45") == G3);
    assert(grade(2, "55") == G22);
    assert(grade(2, "65") == G21);
    assert(grade(2, "75") == G1);
}

// Test the boundary points of the grades (tests 6 to 15)
void testBoundaries() {
    assert(grade(1, "0") == Fail);
    assert(grade(2, "39") == Fail);
    assert(grade(2, "40") == G3);
    assert(grade(2, "49") == G3);
    assert(grade(2, "50") == G22);
    assert(grade(2, "59") == G22);
    assert(grade(2, "60") == G21);
    assert(grade(2, "69") == G21);
    assert(grade(2, "70") == G1);
    assert(grade(3, "100") == G1);
}

// Test that grade only accepts valid marks, and rejects non-digits, numbers
// outside the range 0..100, and unnecessary leading zeros (tests 16 to 25)
void testValidity() {
    assert(grade(4, "40.5") == Invalid);
    assert(grade(1, "x") == Invalid);
    assert(grade(2, "-1") == Invalid);
    assert(grade(4, "40x5") == Invalid);
    assert(grade(3, " 40") == Invalid);
    assert(grade(3, "40 ") == Invalid);
    assert(grade(3, "101") == Invalid);
    assert(grade(3, "547") == Invalid);
    assert(grade(2, "01") == Invalid);
    assert(grade(3, "040") == Invalid);
}

// Run the tests.
void test() {
    checkConstants();
    testGrades();
    testBoundaries();
    testValidity();
    printf("All tests pass\n");
}

// Deal with input and output. If there are no arguments call test. If there is
// one argument, calculate and print the grade.
int main(int n, char *args[n]) {
    if (n == 1) test();
    else if (n == 2) print(grade(strlen(args[1]), args[1]));
    else {
        fprintf(stderr, "Use:   ./grade   or   ./grade m\n");
        fprintf(stderr, "where m is an integer mark from 0 to 100\n");
        return 1;
    }
    return 0;
}
