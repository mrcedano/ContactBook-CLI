#include <stdio.h>
#include <stdlib.h>
#include"../app-data-persistence-logic/files.c"


struct Contact
{
  char* name; 
  char* address;
  char* cellphone;
};

struct ContactBook
{
  char* pathToFile;
  struct Contact* bunchOfContacts;
  int quantityOfContacts;
};

// Prototypes 

void RecoverContactBookInformation(struct ContactBook* sourceBook, char* filename);

void GenerateEmptyContactBook(struct ContactBook* sourceBook, char* filename);

struct ContactBook GenerateOrRecoverContactBookFromCurrentDirectory(char* path);

struct Contact* getContactsFromContactBookFile(char* path);

struct Contact* CreateAndReturnBunchOfContactsPointerInHeap(int size);

int getTotalOfContactsFromContactBookFile(char* path);

// Implementation

void RecoverContactBookInformation(struct ContactBook* sourceBook, char* filename)
{
 sourceBook->file = createFilePointer(filename, WRITE);
 sourceBook->bunchOfContacts = getContactsFromContactBookFile(filename);
 sourceBook->quantityOfContacts = 0;
}

struct Contact* getContactsFromContactBookFile(char* path)
{ 
  int totalOfContacts = getTotalOfContactsFromContactBookFile(path);
  struct Contact* bunchOfContacts = CreateAndReturnBunchOfContactsPointerInHeap(totalOfContacts);

  return bunchOfContacts;
}

struct Contact* CreateAndReturnBunchOfContactsPointerInHeap(int size)
{
 return (struct Contact*)malloc(size*sizeof(struct Contact));
}

int getTotalOfContactsFromContactBookFile(char* path)
{
  int lineNumber = getTotalOfLinesFromFile(path); // 8
  int totalOfPropertiesOfContact= 4;

  int totalOfContacts = lineNumber / totalOfPropertiesOfContact;

  return totalOfContacts;
}



void GenerateEmptyContactBook(struct ContactBook* sourceBook, char* filename)
{
 sourceBook->file = getFilePointer(filename, WRITE_AND_CREATES);
 sourceBook->quantityOfContacts = 0; 
}

struct ContactBook GenerateOrRecoverContactBookFromCurrentDirectory(char* path)
{
 struct ContactBook contactbook;

 int verification = CheckIfFileExists(path); 
 
 if(verification == FILE_NOT_EXIST)
 {
   GenerateEmptyContactBook(&contactbook, path);
 }

 if(verification == FILE_EXIST)
 {
   RecoverContactBookInformation(&contactbook, path);
 }
 
 return contactbook;
}
