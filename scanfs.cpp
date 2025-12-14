/* scanf example */
#include <stdio.h>

int main ()
{
  char str_0 [80];
  int i_0;

  printf ("Enter your family name: ");
  scanf ("%79s",str_0);  
  printf ("Enter your age: ");
  scanf ("%d",&i_0);
  printf ("Mr. %s , %d years old.\n",str_0,i_0);
  printf ("Enter a hexadecimal number: ");
  scanf ("%x",&i_0);
  printf ("You have entered %#x (%d).\n",i_0,i_0);
  



  char sentence []="Rudolph is 12 years old";
  char str_1 [20];
  int i_1;

  sscanf (sentence,"%s %*s %d",str_1,&i_1);
  printf ("%s -> %d\n",str_1,i_1);
  
  return 0;

}
