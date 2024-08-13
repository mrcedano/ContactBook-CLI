#include <stdio.h>  
#include <string.h>  

//definimos las constantes que se utilizaran
#define NULL_LINE -1
#define FILE_EXIST 0
#define FILE_NOT_EXIST 1

// Modos de apertura de archivos
char* bunchOfModes[] = {"r", "a", "w", "rb", "w+"};

// aqui la funcion enum es para los modos de los archivos
enum FileMode
{
  READ = 0,
  WRITE = 1,
  WRITE_AND_CREATES = 2,
  WRITE_AND_READ = 4
};

// Retorna el modo de archivo como una cadena según el enum
char* getModeIdentifier(enum FileMode mode)
{
  return bunchOfModes[mode];
}

// Crea un puntero a un archivo con un modo específico
FILE* createFilePointer(char* path, enum FileMode mode)
{
  char *modeChar = getModeIdentifier(mode);
  return fopen(path, modeChar);
}

// Crea un archivo vacío
void createEmptyFile(char* path)
{
  FILE* file = createFilePointer(path, WRITE_AND_CREATES);
  fclose(file);
}

// Verifica si un archivo existe
int CheckIfFileExists(char* path)
{ 
  FILE* file = fopen(path, getModeIdentifier(READ));
  if (file == NULL)  // si el puntero no apunta a nada entonces el archivo no existe
  {
    return FILE_NOT_EXIST;
  }
  fclose(file);
  return FILE_EXIST;  // Archivo encontrado
}

// Imprime el contenido de un archivo a partir de una línea específica
void PrintContentFromFileStartingAt(char* path, int lineToStartPrinting)
{
  FILE* file = createFilePointer(path, READ);
  
  if (CheckIfFileExists(path) == FILE_NOT_EXIST)
  {
    return;  
  }

  size_t len = 0;
  char* content = NULL;
  int lineNumber = 0;

  // Lee el archivo línea por línea
  while (getline(&content, &len, file) != NULL_LINE) 
  {
    if (lineNumber >= lineToStartPrinting)
    {
      printf("%s", content);  // Imprime el contenido a partir de la línea especificada
    }
    lineNumber++;
  }

  fclose(file);
}

// Imprime todo el contenido del archivo
void PrintContentFromFile(char* path)
{
  FILE* file = createFilePointer(path, READ);
  
  if (CheckIfFileExists(path) == FILE_NOT_EXIST)
  {
    return;  //si el archivo no existe
  }

  size_t len = 0;
  char* content = NULL;

  // Lee el archivo línea por línea e imprime el contenido
  while ((getline(&content, &len, file)) != NULL_LINE) 
  {
    printf("%s", content);
  }

  fclose(file);
}

// Imprime un número específico de líneas del archivo
void PrintSpecificNumberOfLinesFromFile(char* path)
{
  FILE* file = createFilePointer(path, READ);
  
  if (CheckIfFileExists(path) == FILE_NOT_EXIST)
  {
    return;  // Archivo no existe
  }

  // Funcionalidad pendiente
}

// Retorna una línea específica del archivo
char* ReturnSpecificLineFromFile(char* path, int linesToPrint)
{
  FILE* file = createFilePointer(path, READ);

  if (CheckIfFileExists(path) == FILE_NOT_EXIST)
  {
    return NULL;  // Archivo no existe
  }

  char* content = NULL;
  size_t len = 0;
  ssize_t read;

  // Lee el archivo línea por línea hasta encontrar la línea deseada
  while ((getline(&content, &len, file)) != NULL_LINE && linesToPrint > 0) {
    linesToPrint--;
  }
  
  fclose(file);

  return content;  // Retorna la línea encontrada
}

// Obtiene el número total de líneas en un archivo
int getTotalOfLinesFromFile(char* path) 
{
  int total = 0;
  FILE* file = createFilePointer(path, READ);
  char* content = NULL; 
  size_t len = 0;

  // Cuenta el número de líneas en el archivo
  while (getline(&content, &len, file) != NULL_LINE)
  {
    total++;
  }

  fclose(file);

  return total;
}

// Escribe una nueva línea en el archivo
void WriteNewLineOnFile(char* filepath, char* message)
{
  FILE* file = createFilePointer(filepath, WRITE);
  
  if (CheckIfFileExists(filepath) == FILE_NOT_EXIST)
  {
    return;  
  }

  fwrite(message, 1, strlen(message), file);  // Escribe el mensaje en el archivo

  fclose(file);//cierra el archivo
}
