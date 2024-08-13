#include <stdio.h>  /
#include "./app-logic/contact.c"  // Incluye el archivo 'contact.c' que contiene la implementación del libro de contactos

#define USER "cedano"  // Define la constante USER con el nombre de usuario permitido
#define PASSWORD "cedano"  // Define la constante PASSWORD con la contraseña permitida

#define LOGIN_SUCESS 0  // Define la constante LOGIN_SUCESS para indicar un inicio de sesión exitoso
#define LOGIN_FAILED 1  // Define la constante LOGIN_FAILED para indicar un fallo en el inicio de sesión

int Login()  // gestiona el inicio de secion del usuario
{
  char username[20];  // arreglo para que se almecene el nombre del usuario
  char password[20];  // arreglo para almacenar la contraseña

  puts("| Login |");  // Imprime el encabezado del proceso de inicio de sesión
  puts("Type your user: ");  // le pide al usuario su nombre de usuario
  scanf("%s", username);  // lee el nombre y lo almacena en la variable
 
  puts("Type your password");  // solicita la contraseña al usuario
  scanf("%s", password);  // lee la contraseña y la alamacena

  if (strcmp(username, USER) == 0 && strcmp(password, PASSWORD) == 0)  // Compara las credenciales ingresadas con las constantes definidas
  //que en este caso son cedano como usuario y contraseña
  {
    return LOGIN_SUCESS;  // retorna LOGIN_SUCESS si las credenciales son correctas
  }

  return LOGIN_FAILED;  // retorna LOGIN_FAILED si las credenciales son incorrectas
}

void PrintMenu();  // se crea la funcion para el menu

int main()  // Función principal del programa
{
  if (Login() == LOGIN_FAILED)  // manda a llamar a la funcion y ve si fallo el login
  {
    puts("Login unsuccessful. Check your credentials");  // imprime el mensaje si es que el login es fallido
    return 1;  // retorna 1 para indicar un código de error
  }

  system("clear");  // limpia la consola 
  int option = 0;  //se declara una variable para almacenar la opcion dada por el usuario
  
  struct ContactBook contactbook = InitContactBookSystem();  // Inicializa el libro de contactos llamando a InitContactBookSystem

  do  // se abre el bucle do y se repite hasta que el usuario pues decida salir
  {
    PrintMenu();  //manda a llamar a la funcion del menu
    
    puts("Type your option:");  // le pide al usuario que ingrese una de las opciones del menu
    printf("#> ");  // Imprime un prompt para la opción
    scanf("%i", &option);  // lee la opcion ingresada  y esta es guardada en la variable

    switch (option)  // se abre un swicth para elegir alguna de las opciones
    {
      case 1: 
        PrintAllContacts(contactbook);  // Llama a PrintAllContacts para imprimir todos los contactos
        break;

      case 2:
        AddNewContact(&contactbook);  // Llama a AddNewContact para agregar un nuevo contacto
        break;
        
      case 3:
        SearchContact(contactbook);  // Llama a SearchContact para buscar un contacto por nombre
        break;
    }

  } while (option != 4);  // es el fin del ciclo en donde si se elige 4 o algo diferente de 4 se sale del cliclo
  
  return 0;  // aqui acaba return 0 si se finalizo con exito
}

void PrintMenu()  // funcion para el menu de opciones
{
  puts("-------------");  // Imprime una línea de separación
  puts("| Menu |");  // Imprime el encabezado del menú
  puts("| 1.- Print all contacts");  // Imprime la opción para mostrar todos los contactos
  puts("| 2.- Add New Contact");  // Imprime la opción para agregar un nuevo contacto
  puts("| 3.- Search contact by name");  // Imprime la opción para buscar un contacto por nombre
  puts("| 4.- Exit");  // Imprime la opción para salir del programa
}
