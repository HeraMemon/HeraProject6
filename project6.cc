/*
 * Hera memon
 * hxm170001@utdallas.edu
 * CS3377.002
 * 
 */

#include <iostream>
#include "cdk.h"
#include <fstream>
#include <iomanip>
#include <stdint.h>
#include <sstream>
#define MATRIX_WIDTH 3
#define MATRIX_HEIGHT 5
#define BOX_WIDTH 25
#define MATRIX_NAME_STRING "Test Matrix"

using namespace std;
//This is my binary file header
class BinaryFileHeader{
public:
  uint32_t magicNumber; 
  uint32_t versionNumber;
  uint64_t numRecords;
};
//This is my binary file record
class BinaryFileRecord{
public:
  
  uint8_t strLength;
  char stringBuffer[25];

};

//This is my main
int main()
{
  
  WINDOW	*window;
  CDKSCREEN	*cdkscreen;
  CDKMATRIX     *myMatrix;           // CDK Screen Matrix

  const char 		*rowTitles[MATRIX_HEIGHT+1] = {"R0", "R1", "R2", "R3", "R4", "R5"};
  const char 		*columnTitles[MATRIX_WIDTH+1] = {"C0", "C1", "C2", "C3"};
  int		boxWidths[MATRIX_WIDTH+1] = {BOX_WIDTH, BOX_WIDTH, BOX_WIDTH, BOX_WIDTH};
  int		boxTypes[MATRIX_WIDTH+1] = {vMIXED, vMIXED, vMIXED, vMIXED};

  /*
   * Initialize the Cdk screen.
   *
   * Make sure the putty terminal is large enough
   */
  window = initscr();
  cdkscreen = initCDKScreen(window);

  /* Start CDK Colors */
  initCDKColor();

  /*
   * Create the matrix.  Need to manually cast (const char**) to (char **)
  */
  myMatrix = newCDKMatrix(cdkscreen, CENTER, CENTER, MATRIX_HEIGHT, MATRIX_WIDTH, MATRIX_HEIGHT, MATRIX_WIDTH,
			  MATRIX_NAME_STRING, (char **) rowTitles, (char **)columnTitles, boxWidths,
				     boxTypes, 1, 1, ' ', ROW, true, true, false);

  if (myMatrix ==NULL)
    {
      printf("Error creating Matrix\n");
      _exit(1);
    }
  
  BinaryFileHeader *myRecord = new BinaryFileHeader();
  //Creating my ifstream
  ifstream binInfile("cs3377.bin", ios::in | ios::binary);
  binInfile.read((char *) myRecord, sizeof(BinaryFileHeader));
  ostringstream input;
  input<<"Magic: 0x"<< hex << uppercase<< myRecord->magicNumber;
  ostringstream input2;
  input2<<"Version: "<< myRecord->versionNumber;
  ostringstream input3;
  input3<<"NumRecords: " << myRecord->numRecords;
  //store into string
  string magicNumber = input.str();
  string versionNumber = input2.str();
  string numRecords = input3.str();
  setCDKMatrixCell(myMatrix, 1,1, magicNumber.c_str());
  setCDKMatrixCell(myMatrix, 1,2, versionNumber.c_str());
  setCDKMatrixCell(myMatrix, 1,3, numRecords.c_str());
  
  BinaryFileRecord *myOtherRecord = new BinaryFileRecord();
  
  int i=2;
  
  while(binInfile.read((char *) myOtherRecord,sizeof(BinaryFileRecord))){
    stringstream input4;
    input4.str("");//Make sure it's cleared out
    string nameOfRecord = myOtherRecord->stringBuffer;
    input4<<"strLen: "<< nameOfRecord.length();
    string nameOfRecord2 = input4.str();
    setCDKMatrixCell(myMatrix, i,1, nameOfRecord2.c_str());
    setCDKMatrixCell(myMatrix, i,2, myOtherRecord->stringBuffer);
    i++;
    if(i>5){
      break;
    }
  }
    
  /* Display the Matrix */
  drawCDKMatrix(myMatrix, true);

  /* so we can see results */
  unsigned char x;
  cin>>x;


  // Cleanup screen
  endCDK();
}
