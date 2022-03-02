#include <stdio.h>
#define MAX 999
/* Shuyao Wang 9/18/19
 *
 * This program will check for tab character, and print space if it 
 * occur. There was an invisible tab stoped every 8 positions and a
 * tab character in input can occupy anywhere between 1 and 8 position 
 */
int main(void) {
  char arr[MAX];
  int count = 0;
  int tab = 0;
  int i;
  
  while(!feof(stdin)) {  /* read data until the end of its input is seen */
    scanf("%c", &arr[count]);  /* read a character and store it into array */

    if(arr[count] != '\n') {  /* read data until the line end */
      
      if(arr[count] != '\t') {  /* check whether this character is tab */
	  count++;
	  
      } else { 
	tab = 8 - (count % 8); /* calculate how many space do this tab need */
	
	for(i = count; i < count + tab; i++) { /* initialize the value in 
						* range arr[count] to
						* arr[count + tab]
						* with ' ' */
	    arr[i] = ' ';
	}
	count += tab; /* plus the space number to total number of character */
      }
      
    } else {
      
      if(arr[count] == '\n' && !feof(stdin)) { /* recheck whether the file is
						* end or not */

	for(i = 0; i < count; i++) { /* print the line store in arr[] by
				      * print elements in arr[] one by one */
	  printf("%c", arr[i]);
	}
	printf("%c", '\n'); /* print the newline after it finished print 
			     * current line */

	count = 0; /* reset the total number and arr */
      }
    }
  }
  return 0; 
}
