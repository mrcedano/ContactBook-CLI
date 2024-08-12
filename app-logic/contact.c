#include <stdio.h>
#include <stdlib.h>

#include "../utils.c"
#include"../app-data-persistence-logic/files-for-contactbooks.c"

#define CONTACT_EXIST 0
#define CONTACT_NOT_EXIST 1


void updateBunchOfContacts(struct ContactBook contactbook);
void PrintInformationOfContact(struct Contact contact);
void SearchContact(struct ContactBook contactbook);
int CheckIfContactExist(struct Contact contact);

struct ContactBook InitContactBookSystem()
{
 struct ContactBook contactbook = GenerateOrRecoverContactBookFromCurrentDirectory("./.contacts"); 
 
 return contactbook;
}

void AddNewContact(struct ContactBook* contactbook)
{
 struct Contact contact = {"", "", ""};
 char name[35];
 char address[50];
 char cellphone[20];

 system("clear");

 puts("| Adding a new contact |");
 
 puts("Type the name: ");

 ClearBuffer();
 fgets(name, 35, stdin);
   
 puts("Type the address: ");
 fgets(address, 50, stdin);

 puts("Type the cellphone: ");
 fgets(cellphone, 20, stdin);
 
 system("clear");

 puts("Contact Added to the Book!");
  
 strcpy(contact.name, name);
 strcpy(contact.address, address);
 strcpy(contact.cellphone, cellphone);

 createNewContactOnFile(contactbook->pathToFile, contact);

 contactbook->quantityOfContacts++;
 contactbook->bunchOfContacts = getContactsFromContactBookFile(contactbook->pathToFile); 
}

void updateBunchOfContacts(struct ContactBook contactbook)
{
  contactbook.bunchOfContacts = getContactsFromContactBookFile(contactbook.pathToFile);
}

void PrintAllContacts(struct ContactBook contactbook)
{
 char* path = contactbook.pathToFile;

 PrintContentFromFile(path);
}

void SearchContact(struct ContactBook contactbook)
{
 char name[35];

 puts("Type the name:");

 ClearBuffer();

 fgets(name, 35, stdin);

 
 struct Contact contact = findContactByName(contactbook, name);

 if(CheckIfContactExist(contact) == CONTACT_NOT_EXIST)
 {
   puts("Contact doesn't exist");
   return;
 }

 PrintInformationOfContact(contact);
}

int CheckIfContactExist(struct Contact contact)
{
  char* name = contact.name;

  if(strcmp(name, "") == 0)
  {

    return CONTACT_NOT_EXIST;
  }

  return CONTACT_EXIST;
}

void PrintInformationOfContact(struct Contact contact)
{
   char* name = contact.name;
   char* address = contact.address;
   char* cellphone = contact.cellphone;

   puts("| Contact | ");
   printf("| Name: %s", name);
   printf("| Address: %s", address);
   printf("| Cellphone: %s", cellphone);
}
