#include<stdio.h>
#include"testUtils.c"
#include"../app-logic/contact.c"

void TestCreateEmptyContactBook()
{
 struct ContactBook contactbook;

 contactbook = GenerateOrRecoverContactBookFromCurrentDirectory("contactos.txt");

 assertTrue("Empty Contact Book Generated", contactbook.quantityOfContacts == 0);
}

void TestCreateAndAddContactToNewContactBook()
{
 struct ContactBook contactbook = InitContactBookSystem();

 AddNewContact(contactbook);
}

void TestRecoverInformationFromContactBook()
{
 struct ContactBook contactbook = InitContactBookSystem();
  
 char* name = contactbook.bunchOfContacts[2].name;
}

void TestSearchContactByName()
{
  struct ContactBook contactbook = InitContactBookSystem();
 
  char* name = "Fatima";

  SearchContact(contactbook, name);
}

void TestPrintAllContacts()
{
 struct ContactBook contactbook = InitContactBookSystem();

 PrintAllContacts(contactbook);
}

int main()
{
 // TestCreateAndAddContactToNewContactBook();
 
// TestRecoverInformationFromContactBook();
 
//   TestSearchContactByName();

 TestPrintAllContacts();
}
