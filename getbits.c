/*************************************
* Tanner Wagner
* Professor Haugh
* CS 241
* Group 3RW
*
* This file is used to store all the code
* for getbits.c as well as the helper functions
* getbits() and readUnsignedLong().
* To use it, simply compile the program using the
* ansi, Wall, pedantic flags. You can then
* run the executable and use the standard 
* redirection operators <> to pass an input file
* and then output the code to a desired output file.
*
*************************************/

#include <stdio.h>
#include <stdlib.h>
#define ON 1
#define OFF 0

int readOverflow;

/*************************************
* Each parameter’s type and name:
*   input: None
*   output: None
*   readOverflow: Flag indicating overflow
*   myNum: Accumulator for the number read
*   myChar: Character read from input
*   stopRun: Flag to stop reading input
*   Return: Unsigned long representing the number read
* Description of what the function does:
*   Reads an unsigned long number from input,
*   handling overflow and non-numeric characters.
* Function’s algorithm:
*   Initialize variables.
*   Loop until stopRun is ON.
*     Read character from input.
*     If end of file is reached, exit.
*     If character is a digit, update myNum accordingly.
*     If myNum exceeds the range, set readOverflow flag.
*     If character is not a digit, set stopRun to ON.
*   Return myNum.
*************************************/

unsigned long readUnsignedLong(void)
{
  double myNum = 0;
  char myChar;
  int stopRun = OFF;
  
  while (stopRun != ON)
  {
    myChar = getchar();

    if (myChar == EOF)
    {
      exit(0);
    }

    else if (myChar >= '0' && myChar <= '9')
    {
      myNum *= 10;
      myNum += myChar - '0';

      if (myNum > 0xffffffff)
      {
	readOverflow = ON;
      }
    }
    
    else
    {
      stopRun = ON;
    }
  }

  return myNum;
}

/*************************************
* Each parameter’s type and name:
*   input: Unsigned integer x, position p, number of bits n
*   Output: None
*   Return: Unsigned integer representing the extracted bits
* Description of what the function does:
*   Extracts n bits from x starting at position p.
* Function’s algorithm:
*   Right shift x to align the desired bits.
*   Use a mask to extract the desired bits.
*   Return the extracted bits.
*************************************/

unsigned int getbits(unsigned int x, int p, int n)
{
  return (x >> (p + 1 - n)) & ~(~0 << n);
}

/*************************************
* Each parameter’s type and name:
*   Input: None
*   Output: None
*   x: Unsigned integer representing the number from which bits are extracted
*   p: Integer representing the starting position for bit extraction
*   n: Integer representing the number of bits to extract
*   Return: Integer representing the program exit status
* Description of what the function does:
*   Reads unsigned integers x, p, and n from input and prints the result of extracting n bits from x starting at position p. 
*   Handles various error conditions including value out of range, position out of range, number of bits out of range, and too many bits requested from position.
* Function’s algorithm:
*   Initialize variables x, p, and n.
*   Loop indefinitely.
*     Reset the readOverflow flag.
*     Read x, p, and n using readUnsignedLong().
*     Check for various error conditions and print corresponding error messages.
*     If no error, call getbits() with x, p, and n, and print the result.
*   Return 0.
*************************************/

int main(void)
{
  unsigned int x;
  int p;
  int n;

  while (ON)
  {
    readOverflow = OFF;
    x = readUnsignedLong();
    p = (int) readUnsignedLong();
    n = (int) readUnsignedLong();

    if (readOverflow)
    {
      printf("Error: value out of range\n");
    }

    else if (p > 31)
    {
      printf("Error: position out of range\n");
    }

    else if (n > 31)
    {
      printf("Error: number of bits out of range\n");
    }

    else if (n > (p + 1))
    {
      printf("Error: too many bits requested from position\n");
    }

    else
    {
      printf("getbits(x=%u, p=%d, n=%d) = %u\n", x, p, n, getbits(x, p, n));
    }
  }

  return 0;
}
