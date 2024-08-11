#include<stdio.h>
#include<string.h>

void assertTrue(char* message, int booleanValue)
{
 if(booleanValue == 1)
 {
   printf("✅ ");
 }
 else 
 {
   printf("❌ ");
 }
 
 printf("%s", message);
 puts("");

}

void assertFalse(char* message, int booleanValue)
{
 if(booleanValue == 0) 
 {
  printf("✅ ");
 }
 else
 {
  printf("❌ ");
 }

 printf("%s", message);
 puts("");
}

void assertEquals(char* message, char* expected_response, char* response)
{
 int booleanValue = strcmp(expected_response, response);

 assertTrue(message, booleanValue == 0);
}
