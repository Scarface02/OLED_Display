#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>


int buff;
int prev_buff;
int n;
int comma;
FILE *fRead;
FILE *fWrite;
    
int main(int argc, char **argv)
{
    if ((fRead = fopen("from.txt","r")) == NULL){
       printf("Error! opening file");


       // Program exits if the file pointer returns NULL.
       exit(1);
   }
   
   if ((fWrite = fopen("to.txt","w")) == NULL){
       printf("Error! opening file");


       // Program exits if the file pointer returns NULL.
       exit(2);
   }
    
     while ((buff = fgetc(fRead)) != EOF){
        if(buff=='\n'){
			comma = 1;
		}else{
			if(isdigit(buff)){
				if(!isdigit(prev_buff)){
					n++;
				}
			}
			if(comma){
			fputc(',', fWrite);
			comma = 0;
			}
			fputc(buff, fWrite);
		}
		prev_buff = buff;
    }
    fputc('\n', fWrite);
    fprintf(fWrite,"Array size: ");
    fprintf(fWrite,"%d",n);
    
    fclose(fRead);
    fclose(fWrite);
    
    
    return 0;
}

