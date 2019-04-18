// Steve's edited black.c 
// Renamed as chessboard.c
// Generate a file named chessboard.c
  
 

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
#define BMP_FILE "chessboard.bmp"
 
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

// 3 SPACE INDENT DRIVES ME NUTS
// STYLE GUIDE IS IMPORTANT PLEASE FOLLOW

   unsigned char blue = 0;
   unsigned char green = 0;
   unsigned char red = 0;
   // CALL writePixel(blue, green, red, filepointer);
   
   // Destination this time is 512x512 in size and 16x16 pixel per cell.
   // Each cell is 32x32 px, first cell is white.
   
   int cside = 16; // cell side length in px
   int cellps = SIZE/cside; // cells per side
   
   // begin with a big count
   for(int h=0; h<cellps; h++){
      for(int hc=0; hc<cside; hc++){
         //Now do each line:
         for(int r=0; r<cellps; r++){
         	for(int rc=0; rc<cside; rc++){
         		if((h%2==0 && r%2==0) || (h%2!=0 && r%2!=0)){
         			writePixel(0,0,0,f);
         		}else{
         			writePixel(255,255,255,f);
         		}
         	 }
         }
      }
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
