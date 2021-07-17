
// C code to demonstrate practical application of
// strtok
#include <stdio.h>
#include <string.h>
  
// Driver function
int main()
{
    // Declaration of string
    // Information to be converted into CSV file
    char gfg[100] = " 1997 Ford E350 ac 3000.00";
  
    // Declaration of delimeter
    const char s[4] = " ";
    char* tok;
  
    // Use of strtok
    // get first token
    tok = strtok(gfg, s);
  
    // Checks for delimeter
    while (tok != 0) {
        printf("%s, ", tok);
  
        // Use of strtok
        // go through other tokens
        tok = strtok(0, s);
    }
  
    return (0);
}