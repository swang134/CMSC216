
#include "functions.h"

/* Write your implementations of the functions in this source file.
 * Skeleton versions of the functions already appear below.
 */

int sum_of_cubes(int n) {
  int sum = 0;
  int x=1;
  if(n<0)
    return -1;
  while(x<=n){
    sum+=x*x*x;
    x++;
  }
  return sum;
}

int quadrant(int x, int y) {
  int quad=-1;
  if(x>0&&y>0)
    quad=1;
  if(x<0&&y>0)
    quad=2;
  if(x<0&&y<0)
    quad=3;
  if(x>0&&y<0)
    quad=4;
  return quad;
}

int num_occurrences_of_digit(long num, int digit) {
  int times,check;
    times=0;
    if(digit<0||digit>9)
      return -1;
    if(num<0)
      num=0-num;
    while(num!=0){
      check=num%10;
      num=num/10;
      if(check==digit){
	times++;
      }
    }
  return times;
}
