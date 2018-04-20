/*
 * Usage of CDK Matrix
 *
 * File:   example1.cc
 * Author: Stephen Perkins
 * Email:  stephen.perkins@utdallas.edu
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

class BinaryFileHeader{
public:
  uint32_t magicNumber; 
  uint32_t versionNumber;
  uint64_t numRecords;
};
class BinaryFileRecord{
public:
  
  uint8_t strLength;
  char stringBuffer[25];

};


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

  /* Display the Matrix */
  drawCDKMatrix(myMatrix, true);

  /*
   * Dipslay a message
   */
  setCDKMatrixCell(myMatrix, 2, 2, "Test Message");
  drawCDKMatrix(myMatrix, true);    /* required  */

  /* so we can see results */
  unsigned char x;
  cin>>x;


  // Cleanup screen
  endCDK();
}
