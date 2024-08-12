#include<stdio.h>
#include"./testUtils.c"
#include"../app-data-persistence-logic/files-for-contactbooks.c"

void TestRetrieveBunchOfContactsFromFile(char* path, int quantityOfContacts)
{
  struct Contact* bunchOfContacts = RetrieveBunchOfContactsFromFile(path, quantityOfContacts);
  
  assertTrue("Bunch of Contacts returned sucessfully", bunchOfContacts[0].name != NULL);
}

void TestCorrectNameFromBunchOfContacts(char* path, int contactid, char* nameToCompare, int quantityOfContacts)
{
  struct Contact* bunchOfContacts = RetrieveBunchOfContactsFromFile(path, quantityOfContacts);

   assertTrue("Name Correct",
    strlen(nameToCompare) == strlen(bunchOfContacts[contactid].name) - 1
    &&
    strcmp(bunchOfContacts[contactid].name, nameToCompare) == 10);
}

void TestCreateNewContactOnFile(char* path, struct Contact contactToBeAdded) 
{
  createNewContactOnFile(path, contactToBeAdded);
}

int main()
{
  TestRetrieveBunchOfContactsFromFile("./TestBunchOfContacts.txt", 2);
  TestCorrectNameFromBunchOfContacts("./TestBunchOfContacts.txt", 0, "Oscar Noel Cedano Beltran", 2);
  return 0;
}
