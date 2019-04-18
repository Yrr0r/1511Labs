// Author Steve & Abigail
// Date created: 16.01.2019
// Compute student WAM and grade

#include <stdio.h>
#define HD_MARK 85
#define D_MARK 75

int main (void) {
  int course1, course2, course3, course4;
  double average;

  printf("Enter marks for 4 courses enrolled in past semester:\n");

  scanf("%d %d %d %d", &course1, &course2, &course3, &course4);
  
  average = (course1 + course2 + course3 + course4)/4.00;

  // %.2f -- the .2 makes sure only two decimal points are printed
  printf("Your WAM  is: %.2f \n", average);

  if (average >= HD_MARK) {
     printf("Your grade is HD\n");
  }
  else if (average >= D_MARK) {
     printf("Your grade is D\n");
  }
  else if (average >= 65) {
     printf("Your grade is CR\n");
  }
  else if (average >= 50){
     printf("Your grade is PS\n");
  }
  else {
     printf("Your grade is FL\n");
  }
  return 0;
}
