#include "WordCount.h"
#include <iostream>
#include <sstream>
using namespace std;

void check(const string& actual, const string& expected, const string& testName) {
    if (actual == expected) {
        cout << "PASSED: " << testName << endl;
    } else {
        cout << "FAILED: " << testName
             << " (actual: \"" << actual
             << "\", expected: \"" << expected << "\")" << endl;
    }
}

void check(int actual, int expected, const string& testName) {
    if (actual == expected) {
        cout << "PASSED: " << testName << endl;
    } else {
        cout << "FAILED: " << testName
             << " (actual: " << actual
             << ", expected: " << expected << ")" << endl;
    }
}

int main() {

    cout << "===== TESTING addAllWords =====" << endl;

    {
        WordCount wc;
        wc.addAllWords("Hello world! Hello again.");

        // Words: "hello", "world", "hello", "again"
        check(wc.getWordCount("hello"), 2, "addAllWords: hello count");
        check(wc.getWordCount("world"), 1, "addAllWords: world count");
        check(wc.getWordCount("again"), 1, "addAllWords: again count");
        check(wc.getTotalWords(), 4, "addAllWords: total words");
        check(wc.getNumUniqueWords(), 3, "addAllWords: unique words");
    }

    {
        WordCount wc;
        wc.addAllWords("Repeat repeat repeat");

        // All become "repeat"
        check(wc.getWordCount("repeat"), 3, "addAllWords: repeat count");
    }


    cout << "===== TESTING dumpWordsSortedByWord =====" << endl;

    {
        WordCount wc;
        wc.addAllWords("banana apple cherry apple");

        stringstream ss;
        wc.dumpWordsSortedByWord(ss);

        string actual = ss.str();

        string expected =
            "cherry,1\n"
            "banana,1\n"
            "apple,2\n";

        check(actual, expected, "dumpWordsSortedByWord");
    }


    cout << "===== TESTING dumpWordsSortedByOccurence =====" << endl;

    {
        WordCount wc;
        wc.addAllWords("a a b c c c");

      

        stringstream ss;
        wc.dumpWordsSortedByOccurence(ss);

        string actual = ss.str();

        string expected =
            "b,1\n"
            "a,2\n"
            "c,3\n";

        check(actual, expected, "dumpWordsSortedByOccurence");
    }

    cout << "===== ALL TESTS COMPLETE =====" << endl;

    return 0;
}

