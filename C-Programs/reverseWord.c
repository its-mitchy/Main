#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>
#include <string.h>

#define TRUE 1
#define FALSE 0

#define BUFSIZE 80

// Reverse str, which has len characters.
// str may not have an ending NULL, but you already have len.
// suppose you have 10 chars to reverse:
// you swap 0 and 9, 1 and 8, 2 and 7 and so on.
void str_reverse(char str[], int len) 
{
    int end = len - 1;
    int start = 0; 

    while (start < end) {
        // swap str[start] and str[end]
        char c;
        c = str[end];
        str[end] = str[start];
        str[start] = c;

        start ++;
        end  --;
    }
}

int main()
{
    char ch = 0;
    char buf[BUFSIZE];
    int i = 0;
    int inWord = FALSE;

    while ((ch = getchar()) != EOF) {
        // isspace() may return non-zero values that is not 1. 
        // So be careful.
        int sp = isspace(ch);

        if (sp) { // if ch is a space
            if (inWord) {
                str_reverse(buf, i);
                buf[i] = 0;   // add NULL to print
                printf("%s", buf);
                inWord = FALSE;
            }
            printf("%c", ch);
        } else { 
            if (inWord) {
                // If the word is too long, exit
                // Otherwise, append ch to the buffer
                if (i >= BUFSIZE - 2) 
                    exit(-1);
            } else {
                // start a new word
                inWord = TRUE;
                i = 0;  
            }
            buf[i++] = ch;
        }
    } 
    // What if the file does not end with a space?
    if (inWord) {
        str_reverse(buf, i);
        buf[i] = 0;   // add NULL to print
        printf("%s", buf);
    }
}
