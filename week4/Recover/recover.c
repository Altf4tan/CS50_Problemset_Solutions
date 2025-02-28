#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

const int HEADER_SIZE = 512;

int main(int argc, char *argv[])
{
   // Check for usage, must be 2 CLA
   if (argc != 2)
   {
      printf("Usage: ./recover filename.jpeg.\n");
      return 1;
   }
   // Open the file only in read-in-binary mode
   FILE *jpeg_file = fopen(argv[1],"rb");
   if (jpeg_file == NULL)
   {
        printf("Could not open file.\n");
        return 1;
    }
   // Create a buffer for file
   uint8_t buffer[HEADER_SIZE];
   // Create a counter for giving each jpeg file a number
   int jpeg_counter = 0;
   // Create array for jpeg names
   char new_jpeg[8];
   // New jpeg file pointer
   FILE *img = NULL;
   // Loop through the entire file with fread
   while (fread(buffer, sizeof(uint8_t), HEADER_SIZE, jpeg_file) == HEADER_SIZE)
   {
        // Check if the current block starts a new JPEG file
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            // If a JPEG is already open, close it
            if (img != NULL)
            {
                fclose(img);
            }
            // Create a new JPEG file
            sprintf(new_jpeg, "%03i.jpg",jpeg_counter);
            img = fopen(new_jpeg, "wb");
            if (img == NULL)
            {
                printf("Could not create file.\n");
                fclose(jpeg_file);
                return 1;
            }
            jpeg_counter++;
        }
        // If a JPEG file is open, write the current buffer to it
        if (img != NULL)
        {
            fwrite(buffer, sizeof(uint8_t), HEADER_SIZE, img);
        }
    }
    // Close any remaining open files
    if (img != NULL)
    {
        fclose(img);
    }
   fclose(jpeg_file);
   return 0;
}
