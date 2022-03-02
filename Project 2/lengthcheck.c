#include <stdio.h>
#define MAX 999

/* Shuyao Wang 9/18/19
 *
 * This project will check how many characters are in a line
 * and it will print the line's length (3 digit number) and current 
 * line if it contains 80 characters or less, or a single uppercase
 * X if the line read is longer than 80 characters 
 */
int main(void) {
  char arr[MAX];
  int count = 0;
  int i;
  
  while(!feof(stdin)) { /* read data until the end of its input is seen */
    scanf("%c", &arr[count]); /* read a character and store it into array */
    
    if(arr[count] != '\n') { /* read data until the line end */  
      count++; /* count the current number of character */
    } else {
      
      if(arr[count] == '\n' && !feof(stdin)){ /* recheck whether the file is
					       * end */
        if( count <= 80 ) { /* if the number of character <= 80 in the
			     * line, print count */
	  printf("  %3d: ", count);
	} else { /* if the number of character > 80 in current line, print a
		  * single uppercase X before print count */
	  printf("X %3d: ", count);
	}
	
	for(i = 0; i < count; i++) { /* prine the line store in arr[] by print 111111111111111111111111111111111111111
				      * elements in arr[] one by one */
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


