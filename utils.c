#include<stdio.h> 

void ClearBuffer() 
{
 int ch;
while ((ch = getchar()) != '\n' && ch != EOF);
}

