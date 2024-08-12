#include<stdio.h>
#include"./app-logic/contact.c"

#define USER "cedano"
#define PASSWORD  "cedano"

#define LOGIN_SUCESS 0
#define LOGIN_FAILED 1

int Login()
{
 char username[20];
 char password[20];

 puts("| Login |");
 puts("Type your user: ");
 scanf("%s", username); 
 
 puts("Type your password");

 scanf("%s", password);

 if(strcmp(username, USER) == 0 && strcmp(password, PASSWORD) == 0)
 {
   return LOGIN_SUCESS;
 }

 return LOGIN_FAILED;
}

void PrintMenu();

int main() 
{

 if(Login() == LOGIN_FAILED)
 {
   puts("Login unsucessful. Check your credentials");
   return 1;
 }

 system("clear");
 int option = 0;
 
 struct ContactBook contactbook = InitContactBookSystem();

 do 
 {
   PrintMenu();
    
   puts("Type your option:");
   printf("#> ");
   scanf("%i", &option);

   switch(option)
   {
      case 1: 
       PrintAllContacts(contactbook);
      break;

      case  2:
       AddNewContact(&contactbook);
      break;
      
      case 3:
       SearchContact(contactbook);
      break;
   }

 } while(option != 4);
  

 return 0;
}

void PrintMenu() 
{
 puts("-------------");
 puts("| Menu |");
 puts("| 1.- Print all contacts");
 puts("| 2.- Add New Contact");
 puts("| 3.- Search contact by name");
 puts("| 4.- Exit");
}

