#include <string.h>
#include <stdio.h>
#include <stdlib.h>

  
#define BUFSIZE 1000
int main(int argc, char* argv[])
  {
  /* declare local variables */
   
   int ErrorCode = 0;               /* Application error code - 0 is OK */

   FILE *DataFile;                  /* Pointer to Data file name (from cmd line) */

   char *print;

   char menu[10] ={'m','e','n','u','e','n','t','r','y',0};
   char sub[8] ={'s','u','b','m','e','n','u',0};

   int menuFlag = 0;
   int subFlag = 0;

   int start;
   int tabLevel;

   /* Try to open the Data file for input (read mode)     */
   if(1 == argc)
      DataFile = fopen("/boot/grub/grub.cfg", "r");
   else
      DataFile = fopen(argv[1], "r");   
   /* Verify that file was opened correctly */
   if (NULL == DataFile)
   {
      fprintf (stderr, "File Cannot be opened");
      ErrorCode = -1;
      return ErrorCode;
   }
   
   char *buffer = (char*) malloc(BUFSIZE); /* allocate buffer */ 

   printf("-------------------------------------------------\n");
   printf("Grub Menu Breakdown:\n");
   printf("-------------------------------------------------\n");

   while ( fgets(buffer, BUFSIZE, DataFile) != NULL )
   {

      menuFlag = subFlag = 0;

      for(start = 0; buffer[start] == 9; start++);
      tabLevel = start;
      for(int i = 0; buffer[start+i] == menu[i];i++)
      {
         if(8 == i)
         {
            menuFlag = 1;
            break;
         }
      }

      for(int i = 0; buffer[start+i] == sub[i];i++)
      {  
         if(6 == i)
         {  
            subFlag = 1;
            break;
         }
      }

      if(menuFlag | subFlag)
      {
         for(; 39 != buffer[start]; start++);
         print = &buffer[++start];
         for(; 39 != buffer[start]; start++);
         buffer[start] = 0;
         for(int i = 0; i < tabLevel ; i++)
            printf("\t");
         printf("%s\n", print);
      }

   }

   printf("-------------------------------------------------\n");

   free(buffer);
   fclose(DataFile);
   return ErrorCode;
} /* main() */

