#include <stdio.h>
#include <stdlib.h>

#include "../utils.c"  // aqui se incluyen las funciones auxiliares
#include "../app-data-persistence-logic/files-for-contactbooks.c"  // se incluyen las funciones para los archivos de contactos

#define CONTACT_EXIST 0 //se definen con un valor el contacto si existe 
#define CONTACT_NOT_EXIST 1// tambien se define pero ahora si no existe



// Inicializa/recupera un libro de contactos
struct ContactBook InitContactBookSystem()
{
    struct ContactBook contactbook = GenerateOrRecoverContactBookFromCurrentDirectory("./.contacts");
    return contactbook;
}

// se usa la funcion para agregar un nuevo contacto a la lista o mejor dicho al libro
void AddNewContact(struct ContactBook* contactbook)
{
    struct Contact contact = {"", "", ""};  // Contacto vacío
    char name[35];
    char address[50];
    char cellphone[20];

    system("clear");  // Limpia la pantalla

    puts("| Adding a new contact |");

    // Solicita y lee el nombre del contacto
    puts("Type the name: ");
    ClearBuffer();  // Limpia el buffer de entrada
    fgets(name, 35, stdin);
   
    // Solicita y lee la dirección del contacto
    puts("Type the address: ");
    fgets(address, 50, stdin);

    // Solicita y lee el número de teléfono del contacto
    puts("Type the cellphone: ");
    fgets(cellphone, 20, stdin);
 
    system("clear");  // Limpia la pantalla

    puts("Contact Added to the Book!");
  
    // Copia la información del contacto en la estructura de contacto
    strcpy(contact.name, name);
    strcpy(contact.address, address);
    strcpy(contact.cellphone, cellphone);

    // aqui se crea un nuevo libro y se actualiza el que ya existe
    createNewContactOnFile(contactbook->pathToFile, contact);

    contactbook->quantityOfContacts++;  // va incrementando la lista de los contactos
    contactbook->bunchOfContacts = getContactsFromContactBookFile(contactbook->pathToFile);  // actualiza la lista de contactos
}

// Actualiza la lista de contactos pero ahora en el libro de contactos
void updateBunchOfContacts(struct ContactBook contactbook)
{
    contactbook.bunchOfContacts = getContactsFromContactBookFile(contactbook.pathToFile);
}

// Imprime todos los contactos del libro
void PrintAllContacts(struct ContactBook contactbook)
{
    char* path = contactbook.pathToFile;
    PrintContentFromFile(path);  // Imprime el contenido del archivo de contactos
}

// // la funcion busca el contacto por el nombre dado por el usuario
void SearchContact(struct ContactBook contactbook)
{
    char name[35];

    puts("Type the name:");
    ClearBuffer();  // Limpia el buffer de entrada
    fgets(name, 35, stdin);

    struct Contact contact = findContactByName(contactbook, name);

    // Verifica si el contacto existe
    if (CheckIfContactExist(contact) == CONTACT_NOT_EXIST)
    {
        puts("Contact doesn't exist");
        return;
    }

    // Imprime la información que se encuentra en el contacto
    PrintInformationOfContact(contact);
}

// Verifica si un contacto existe
int CheckIfContactExist(struct Contact contact)
{
    char* name = contact.name;

    // Un contacto con nombre vacío se considera inexistente
    if (strcmp(name, "") == 0)
    {
        return CONTACT_NOT_EXIST;
    }

    return CONTACT_EXIST;
}

// Imprime la información de un contacto
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
