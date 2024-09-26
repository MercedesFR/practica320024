#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <string.h>
int main(int argc, char *argv[])
{
 int espera;
 int escrit, tube1[2],tube2[2];
 char leido;
 
 if(argc==5)
 {/*
  struct stat c;  
      int tube1[2];
      int tube2[2];*/
      pipe(tube1);
      pipe(tube2);   
    
      if( fork() != 0)
      {
close(tube1[1]);close(tube2[1]);
close(0);
       dup(tube2[0]);
       close(tube2[0]);
   /*    close(tube2[1]);*/
       close(tube1[0]);
     /*  close(tube1[1]);*/
       wait(&espera);
       printf("\nHOLLLLL");
       execlp("grep", "grep", argv[4],NULL);
      }
      else
      {

        if( fork() != 0 )
        {
         close(tube1[1]);
         close(tube2[0]);
         escrit = creat(argv[3], 0700);
         while( read( tube1[0], &leido, sizeof(char) ) )
         {
           write(escrit, &leido, sizeof(char));
           write(tube2[1], &leido, sizeof(char));
           printf("%c", leido); 
         }
         close(tube2[1]);
         close(tube1[0]);
        }
        else
        {
         close(1);
         dup(tube1[1]);
         close(tube1[0]);
         close(tube1[1]);
         close(tube2[0]);
         close(tube2[1]);
         close(2);
         creat(argv[2], 0700);
         execlp("cat", "cat", argv[1], NULL);
        }
      }

 } 
 else 
 {
 printf("El número de argumentos es incorrecto\n");
 }
 exit(0); 
}

