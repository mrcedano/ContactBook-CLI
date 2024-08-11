#include<stdio.h>
#include"testUtils.c"
#include"../app-logic/contact.c"

void TestCreateEmptyContactBook()
{
 struct ContactBook contactbook;

 contactbook = GenerateOrRecoverContactBookFromCurrentDirectory("contactos.txt");

 assertTrue("Empty Contact Book Generated", contactbook.quantityOfContacts == 0);
}



int main()
{

  TestCreateEmptyContactBook();

}
