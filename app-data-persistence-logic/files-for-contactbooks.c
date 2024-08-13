#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "files.c"  // Incluye funciones para manejo de archivos

#define NUM_OF_CONTACT_PROPERTIES 3  // Número de propiedades por contacto
#define SEPARATOR_OF_CONTACTS "-----"  // Separador para distinguir contactos en el archivo

// es el struct para almacenar información del libro de contactos
struct ContactBook
{
  char* pathToFile;  // Ruta del archivo del libro de contactos
  struct Contact* bunchOfContacts;  // Puntero a un arreglo de contactos
  int quantityOfContacts;  // Cantidad de contactos en el libro
};

// struct para almacenar los datos del contacto osea el nombre, la direccion y el numero de telefono
struct Contact
{
  char name[35];  
  char address[50];  
  char cellphone[20]; 
};

// Recupera la información del libro de contactos desde un archivo
void RecoverContactBookInformation(struct ContactBook* sourceBook, char* filename);

// Crea un libro de contactos vacío
void GenerateEmptyContactBook(struct ContactBook* sourceBook, char* filename);

// Genera o recupera el libro de contactos desde un directorio
struct ContactBook GenerateOrRecoverContactBookFromCurrentDirectory(char* path);

// Obtiene el número de contactos desde el archivo
int getNumberOfContactsFromContactBook(char* path);

// Crea un puntero a un arreglo de contactos en el heap
struct Contact* CreateAndReturnBunchOfContactsPointerInHeap(int size);

// Recupera un arreglo de contactos desde un archivo
struct Contact* RetrieveBunchOfContactsFromFile(char* filepath, int quantityOfContacts);

// Crea un puntero para un arreglo de contactos
struct Contact* createPointerForBunchOfContacts(int size);

// Obtiene los contactos desde el archivo del libro de contactos
struct Contact* getContactsFromContactBookFile(char* path);

// Implementación

// Recupera contactos desde el archivo especificado
struct Contact* RetrieveBunchOfContactsFromFile(char* filepath, int quantityOfContacts)
{
  FILE* file = createFilePointer(filepath, READ);  // abre el archivo en modo lectura

  if (CheckIfFileExists(filepath) == FILE_NOT_EXIST)  // verifica si el archivo existe
  {
    return NULL;  // Retorna NULL si el archivo no existe
  }

  // crea un arreglo para los contactos y lee desde el archivo
  struct Contact* bunchOfContacts = createPointerForBunchOfContacts(quantityOfContacts);
  char* extractedValue = NULL;
  size_t length = 0;
  int contactID = 0, propertyNumber = 1;

  // Lee líneas del archivo y llena la estructura de contactos
  while (getline(&extractedValue, &length, file) != NULL_LINE)
  {
    if (propertyNumber > NUM_OF_CONTACT_PROPERTIES)
    {
      propertyNumber = 1;
      contactID++;
      continue;
    }

    if (propertyNumber == 1) strcpy(bunchOfContacts[contactID].name, extractedValue);
    if (propertyNumber == 2) strcpy(bunchOfContacts[contactID].address, extractedValue);
    if (propertyNumber == 3) strcpy(bunchOfContacts[contactID].cellphone, extractedValue);
    
    propertyNumber++;
  }

  return bunchOfContacts;  // Retorna el arreglo de contactos
}

// Crea un puntero a un arreglo de contactos en el heap
struct Contact* createPointerForBunchOfContacts(int size) 
{  
  return (struct Contact*)malloc(size * sizeof(struct Contact)); 
}

// Crea un nuevo contacto en el archivo
void createNewContactOnFile(char* path, struct Contact contactToBeAdded)
{
   WriteNewLineOnFile(path, contactToBeAdded.name);
   WriteNewLineOnFile(path, contactToBeAdded.address);
   WriteNewLineOnFile(path, contactToBeAdded.cellphone);
   WriteNewLineOnFile(path, SEPARATOR_OF_CONTACTS);
   WriteNewLineOnFile(path, "\n");
}

// Busca un contacto por nombre en el libro de contactos
struct Contact findContactByName(struct ContactBook contactbook, char* nameToBeSearched)
{
  struct Contact contact;
  struct Contact* bunchOfContacts = contactbook.bunchOfContacts;
  int quantityOfContacts = contactbook.quantityOfContacts;

  // Recorre los contactos para encontrar el que coincide con el nombre buscado
  for (int i = 0; i < quantityOfContacts; i++)
  {
    if (strcmp(bunchOfContacts[i].name, nameToBeSearched) == 0) 
    {
      // Copia los datos del contacto encontrado
      strcpy(contact.name, bunchOfContacts[i].name);
      strcpy(contact.address, bunchOfContacts[i].address);
      strcpy(contact.cellphone, bunchOfContacts[i].cellphone);
      return contact;
    }
  }

  // Retorna un contacto vacío si no se encuentra
  strcpy(contact.name, "");
  return contact;
}

// Recupera el libro de contactos desde un archivo
void RecoverContactBookInformation(struct ContactBook* sourceBook, char* filename)
{
  sourceBook->pathToFile = filename;
  sourceBook->bunchOfContacts = getContactsFromContactBookFile(filename);
  sourceBook->quantityOfContacts = getNumberOfContactsFromContactBook(filename);
}

// Obtiene los contactos desde el archivo del libro de contactos
struct Contact* getContactsFromContactBookFile(char* path)
{ 
  int totalOfContacts = getNumberOfContactsFromContactBook(path);
  struct Contact* bunchOfContacts = RetrieveBunchOfContactsFromFile(path, totalOfContacts);  
  return bunchOfContacts;
}

// Obtiene el número total de contactos desde el archivo
int getNumberOfContactsFromContactBook(char* path)
{
  int lines = getTotalOfLinesFromFile(path); 
  int totalOfPropertiesPerContact = NUM_OF_CONTACT_PROPERTIES;
  return lines / totalOfPropertiesPerContact;  // Calcula el número total de contactos
}

// Genera un libro de contactos vacío
void GenerateEmptyContactBook(struct ContactBook* sourceBook, char* path)
{
  sourceBook->pathToFile = path;
  sourceBook->quantityOfContacts = 0;
  createEmptyFile(path);  // Crea un archivo vacío para el libro de contactos
}

// Genera o recupera el libro de contactos desde un directorio dependiendo de la validacion dada 
//es decir si no existe entinces lo crea y si ya existe lo recupera
struct ContactBook GenerateOrRecoverContactBookFromCurrentDirectory(char* path)
{
  struct ContactBook contactbook;
  int verification = CheckIfFileExists(path); 

  if (verification == FILE_NOT_EXIST)
  {
    GenerateEmptyContactBook(&contactbook, path);  // Crea un nuevo libro si  es que este no existe
  }
  else
  {
    RecoverContactBookInformation(&contactbook, path);  // Recupera el libro existente
  }
  
  return contactbook;
}
