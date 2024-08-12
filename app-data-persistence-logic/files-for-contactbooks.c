#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"files.c"

#define NUM_OF_CONTACT_PROPERTIES 3
#define SEPARATOR_OF_CONTACTS "-----"

// Structs

struct ContactBook
{
  char* pathToFile;
  struct Contact* bunchOfContacts;
  int quantityOfContacts;
};

struct Contact
{
  char name[35]; 
  char address[50];
  char cellphone[20];
};



// Prototypes

void RecoverContactBookInformation(struct ContactBook* sourceBook, char* filename);

void GenerateEmptyContactBook(struct ContactBook* sourceBook, char* filename);

struct ContactBook GenerateOrRecoverContactBookFromCurrentDirectory(char* path);

int getNumberOfContactsFromContactBook(char* path);

struct Contact* CreateAndReturnBunchOfContactsPointerInHeap(int size);

struct Contact* RetrieveBunchOfContactsFromFile(char* filepath, int quantityOfContacts);

struct Contact* createPointerForBunchOfContacts(int size);

struct Contact* getContactsFromContactBookFile(char* path);


// Implementation

struct Contact* RetrieveBunchOfContactsFromFile(char* filepath, int quantityOfContacts)
{
 FILE* file = createFilePointer(filepath, READ);

 if(CheckIfFileExists(filepath) == FILE_NOT_EXIST)
 {
    return NULL; 
 }

 struct Contact* bunchOfContacts = createPointerForBunchOfContacts(quantityOfContacts);
 char* extractedValue = NULL; 
 size_t length = 0;
  
 int contactID = 0, propertyNumber = 1; 

 while(getline(&extractedValue, &length, file) != NULL_LINE)
 {
  if(propertyNumber > NUM_OF_CONTACT_PROPERTIES)
  {
     propertyNumber = 1;
     contactID++;

     continue;
  }

  if(propertyNumber == 1) strcpy(bunchOfContacts[contactID].name, extractedValue);

  if(propertyNumber == 2) strcpy(bunchOfContacts[contactID].address, extractedValue);

  if(propertyNumber == 3) strcpy(bunchOfContacts[contactID].cellphone, extractedValue);
  
  propertyNumber++;
 }

 return bunchOfContacts;
}

struct Contact* createPointerForBunchOfContacts(int size) 
{  
 return (struct Contact*)malloc(size*sizeof(struct Contact)); 
}

void createNewContactOnFile(char* path, struct Contact contactToBeAdded)
{
   WriteNewLineOnFile(path, contactToBeAdded.name);
   WriteNewLineOnFile(path, contactToBeAdded.address);
   WriteNewLineOnFile(path, contactToBeAdded.cellphone);
   WriteNewLineOnFile(path, SEPARATOR_OF_CONTACTS);
   WriteNewLineOnFile(path, "\n");
}

struct Contact findContactByName(struct ContactBook contactbook, char* nameToBeSearched)
{
  struct Contact contact;
  
  struct Contact* bunchOfContacts = contactbook.bunchOfContacts;
  int quantityOfContacts = contactbook.quantityOfContacts;

  for(int i = 0; i < quantityOfContacts; i++)
  {
      char* name = bunchOfContacts[i].name;

      if(strcmp(name, nameToBeSearched) == 0) 
      {

       char* address = bunchOfContacts[i].address;
       char* cellphone = bunchOfContacts[i].cellphone;

       strcpy(contact.name, name);
       strcpy(contact.address, address);
       strcpy(contact.cellphone, cellphone);

       return contact;
      }
  }

  strcpy(contact.name, "");
  
  return contact;
}

// Implementation

void RecoverContactBookInformation(struct ContactBook* sourceBook, char* filename)
{
 sourceBook->pathToFile = filename;
 sourceBook->bunchOfContacts = getContactsFromContactBookFile(filename);
 sourceBook->quantityOfContacts = getNumberOfContactsFromContactBook(filename);
}

struct Contact* getContactsFromContactBookFile(char* path)
{ 
  int totalOfContacts = getNumberOfContactsFromContactBook(path);
  struct Contact* bunchOfContacts = RetrieveBunchOfContactsFromFile(path, totalOfContacts);  

  return bunchOfContacts;
}

int getNumberOfContactsFromContactBook(char* path)
{
  int lines = getTotalOfLinesFromFile(path); 
  int totalOfPropertiesPerContact = 3;

  int totalOfContacts = lines / totalOfPropertiesPerContact;

  return totalOfContacts;
}

void GenerateEmptyContactBook(struct ContactBook* sourceBook, char* path)
{
 sourceBook->pathToFile = path;
 sourceBook->quantityOfContacts = 0;
 
 createEmptyFile(path); 
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
