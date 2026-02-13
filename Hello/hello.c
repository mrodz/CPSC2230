#include <stdio.h>

/*
 * Assignment
 *
 * Write a program in a single file called hello.c (case-sensitive)
 * that prints Hello, world! as the first line of output. Note that
 * the first line contains a single space to delimit the words and a
 * newline character at the end. It is also case- and punctuation-sensitive.
 * You may output anything or nothing after the first line; this would be
 * a good place to tell us something interesting about yourself
 * (and if there's nothing interesting about you, then that's...interesting!).
 */

int main()
{
    char message[] = "Hello, world!\n"
                     "\n"
                     "I am from Los Angeles and I taught myself how to code in middle school.\n"
                     "I love my family and my dog. I like going to the gym and grilling.\n"
                     "I want to live in California when I get older. I also want to travel.\n";

    printf("%s", message);
    
    return 0;
}
