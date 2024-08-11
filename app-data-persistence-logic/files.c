#include<stdio.h>

#define NULL_LINE -1

#define FILE_EXIST 0
#define FILE_NOT_EXIST 1

char* bunchOfModes[] = {"r", "a", "w", "rb"};

typedef enum FileMode
{
  READ = 0,
  WRITE = 1,
  WRITE_AND_CREATES = 2,
  
  READ_BINARYFILE = 3
};

char* getModeIdentifier(enum FileMode mode)
{
  return bunchOfModes[mode];
}

FILE* createFilePointer(char* path, enum FileMode mode)
{
  char *modeChar = getModeIdentifier(mode);

  return fopen(path,modeChar);  
}

void WriteNewLine(char* filepath, char* content)
{
}

int CheckIfFileExists(char* path)
{ 
 FILE* file = fopen(path, getModeIdentifier(READ));
 
 if(file == NULL)
 {
   return FILE_NOT_EXIST;
 }

 fclose(file);

 return FILE_EXIST;
}

void PrintContentFromFileStartingAt(char* path, int lineToStartPrinting)
{
  FILE* file = createFilePointer(path, READ);

  if(CheckIfFileExists(path) == FILE_NOT_EXIST)
  {
    return NULL;
  }

  size_t len = 0;
  char* content = NULL;
  
  int lineNumber = 0;

  while(getline(&content, &len, file) != NULL_LINE) 
  {
   if(lineNumber >= lineToStartPrinting)
   {
     printf("%s", content); 
   }

   lineNumber++;
  }

  fclose(file);
}

void PrintContentFromFile(char* path)
{
  FILE* file = createFilePointer(path, READ);
    
  if(CheckIfFileExists(path) == FILE_NOT_EXIST)
  {
    return NULL;
  }

  size_t len = 0;
  char* content = NULL;
   
  while((getline(&content, &len, file)) != NULL_LINE) 
  {
    printf("%s", content);
  }

  fclose(file);
}

void PrintSpecificNumberOfLinesFromFile(char* path)
{
 FILE* file = createFilePointer(path, READ);
 
 if(CheckIfFileExists(path) == FILE_NOT_EXIST)
 {
  return NULL;
 }

}

char* ReturnSpecificLineFromFile(char* path, int linesToPrint)
{
  FILE* file = createFilePointer(path, READ); 

  if(CheckIfFileExists(path) == FILE_NOT_EXIST)
  {
    return NULL;
  }

  char* content = NULL;
  size_t len = 0;
  ssize_t read;

  while ((getline(&content, &len, file)) != NULL_LINE && linesToPrint > 0) {
    linesToPrint = linesToPrint - 1;
  }
  
  fclose(file);

  return content;
}

int getTotalOfLinesFromFile(char* path) 
{
  int total = 0;

  FILE* file = createFilePointer(path, READ);
  char* content = NULL; 
  size_t len = 0;

  while(getline(&content, &len, file) != NULL_LINE)
  {
    total = total + 1;
  }

  return total;
}
