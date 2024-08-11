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

int main()
{
 TestReadFirstLine("./testContactFile.txt");
 TestGetNumberOfLinesFromFile("./testReadEntireFile.txt", 5);

 return 0;
}
