// To compile, run and view the finished product type 
 
// dcc -o black black.c

// ./black

// display black.bmp


// An example of creating a bitmap file with code. 
// We generate the bytes using a while loop. 
// The bitmap is 512 x 512.
// The bitmap file has a header, with data that includes 
// the size of the file and other things we do not need to worry about. 
// After the header, there are data bytes that represent the pixels.
// Each pixel is represented by 3 bytes. 
// One for blue, one for green and one for red. 
// The first 3 bytes in the pixel data represent
// the bottom left corner of the file.

//  Created by Richard Buckland on 14/04/11, edited 5/4/14
  
 

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
 
#define BYTES_PER_PIXEL 3
#define BITS_PER_PIXEL (BYTES_PER_PIXEL*8)
#define NUMBER_PLANES 1
#define PIX_PER_METRE 2835
#define MAGIC_NUMBER 0x4d42
#define NO_COMPRESSION 0
#define OFFSET 54
#define DIB_HEADER_SIZE 40
#define NUM_COLORS 0
 
#define SIZE 512
#define BMP_FILE "black.bmp"
 
void writeHeader (FILE *file);
void generateData(FILE *file);
void writePixel(unsigned char b, unsigned char r, unsigned char g, FILE * f); 

int main (void) {
 
   FILE *outputFile;
   
 
   outputFile = fopen(BMP_FILE, "wb");

   if ( outputFile == NULL ){
       fprintf(stderr,"Could not open file\n");
       return EXIT_FAILURE;
   }

   writeHeader(outputFile);   
   generateData(outputFile);
     
   fclose(outputFile); 
   return EXIT_SUCCESS;
}


// Change this function to create different images!
void generateData(FILE * f){
   unsigned char blue = 0;
   unsigned char green = 0;
   unsigned char red = 0;
  
   int row = 0;
   int col = 0;
   while (row < SIZE) {
      col = 0;
      while(col < SIZE){        
          writePixel(blue,green,red,f);          
          col++;
      }
      row++;
   }
}

// The colour of each pixel is determined by its 
// blue, green and red values. 
// So each pixel needs 3 bytes of data written to the file
void writePixel(unsigned char b, unsigned char g, unsigned char r, FILE * f){
          fwrite (&b, sizeof (unsigned char), 1, f);
          fwrite (&g, sizeof (unsigned char), 1, f);
          fwrite (&r, sizeof (unsigned char), 1, f);
}
 
// Do not worry if you do not understand this code and what all the 
// values are for. It is just writing a header in the bmp and follows 
// the standard format For more info if you are interested see 
// https://en.wikipedia.org/wiki/BMP_file_format

void writeHeader (FILE *file) {
 
 
   unsigned short magicNumber = MAGIC_NUMBER;
   fwrite (&magicNumber, sizeof magicNumber, 1, file);
 
   unsigned int fileSize = OFFSET + (SIZE * SIZE * BYTES_PER_PIXEL);
   fwrite (&fileSize, sizeof fileSize, 1, file);
 
   unsigned int reserved = 0;
   fwrite (&reserved, sizeof reserved, 1, file);
 
   unsigned int offset = OFFSET;
   fwrite (&offset, sizeof offset, 1, file);
 
   unsigned int dibHeaderSize = DIB_HEADER_SIZE;
   fwrite (&dibHeaderSize, sizeof dibHeaderSize, 1, file);
 
   unsigned int width = SIZE;
   fwrite (&width, sizeof width, 1, file);
 
   unsigned int height = SIZE;
   fwrite (&height, sizeof height, 1, file);
 
   unsigned short planes = NUMBER_PLANES;
   fwrite (&planes, sizeof planes, 1, file);
 
   unsigned short bitsPerPixel = BITS_PER_PIXEL;
   fwrite (&bitsPerPixel, sizeof bitsPerPixel, 1, file);
 
   unsigned int compression = NO_COMPRESSION;
   fwrite (&compression, sizeof compression, 1, file);
 
   unsigned int imageSize = (SIZE * SIZE * BYTES_PER_PIXEL);
   fwrite (&imageSize, sizeof imageSize, 1, file);
 
   unsigned int hResolution = PIX_PER_METRE;
   fwrite (&hResolution, sizeof hResolution, 1, file);
 
   unsigned int vResolution = PIX_PER_METRE;
   fwrite (&vResolution, sizeof vResolution, 1, file);
 
   unsigned int numColors = NUM_COLORS;
   fwrite (&numColors, sizeof numColors, 1, file);
 
   unsigned int importantColors = NUM_COLORS;
   fwrite (&importantColors, sizeof importantColors, 1, file);
 
}
