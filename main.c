#include<stdio.h>
#include"./app-logic/contact.c"

void PrintMenu();

int main() 
{
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

