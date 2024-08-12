#include <stdio.h>
#include"./testUtils.c"
#include"../app-data-persistence-logic/files.c"

void TestReadFirstLine(char* path)
{
  char* content = ReturnSpecificLineFromFile(path, 1); 
  char temp[1];
 
  temp[0] = content[0];

  assertEquals("These texts are the same", "1", temp);
}

void TestPrintAllFileStartingAt(char* path, int lineToStartPrinting)
{
  PrintContentFromFileStartingAt(path, lineToStartPrinting);
}

void TestReadAllFile(char* path) 
{
  PrintContentFromFile(path);   
}

void TestGetNumberOfLinesFromFile(char* path, int numOfLines)
{
 int result = getTotalOfLinesFromFile(path);
 assertTrue("Number of Lines match", result == numOfLines); 
}

void TestCheckIfFileExist(char* path)
{
 int result = CheckIfFileExists(path);

 assertTrue("File exists!", result == FILE_EXIST);
}

void TestWriteOnFile(char* path, char* content)
{
  WriteNewLineOnFile(path, content);
}

int main()
{
 TestReadFirstLine("./testContactFile.txt");
 TestGetNumberOfLinesFromFile("./testReadEntireFile.txt", 5);
 TestCheckIfFileExist("./contacts.txt");

 TestWriteOnFile("./contacts.txt", "Oscarito oscarito el alma de la fiesta");

 return 0;
}
