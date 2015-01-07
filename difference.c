#include <stdio.h>
#include <stdlib.h>
#include <time.h>

/*
 Author: Shovik Shyamsundar
 Filename: difference.c
 Description: Your implementation of a program that reads in the
 contents of two files. It will then compare the contents and every 
 bite that i s different in file one will be written to a third file 
 and every bite that is different in f ile two will be written to a fourth. 
 Every large array in this program will be dynamically all ocated.. */
int main(int argc, char *argv[])
{
    clock_t start1, end1, start2, end2;
    float cpu_time_used1, cpu_time_used2;
    int ch1, ch2;
    int size1, size2;
    FILE *fh1, *fh2, *diffone, *difftwo;
    
    if( argc<3 ) {
        printf("need two file names\n"); return(1);
    }
    if(!(fh1 = fopen(argv[1], "r"))) {
        printf("cannot open %s\n",argv[1]); return(2);
    }
    if(!(fh2 = fopen(argv[2], "r"))) {
        printf("cannot open %s\n",argv[2]); return(3);
    }
    if(!(diffone = fopen("diffone.txt", "w+"))) {
      printf("cannot open %s\n",diffone); return(4);
    }
    if(!(difftwo = fopen("difftwo.txt", "w+"))){
      printf("cannot open %s\n",difftwo); return(4);
    }

    fseek(fh1, 0, SEEK_END);
    size1 = ftell(fh1);//gets size of fh1
    fseek(fh1, 0, SEEK_SET);
   
    fseek(fh2, 0, SEEK_END);
    size2 = ftell(fh2);//gets size of fh2
    fseek(fh2, 0, SEEK_SET);

    start1 = clock();
    while((!feof(fh1)) || (!feof(fh2)))
    {
        ch1=ch2='-';
        if(!feof(fh1)) ch1 = fgetc(fh1);
        if(!feof(fh2)) ch2 = fgetc(fh2);
	if (ch1 != ch2 && (!feof(fh1)))
	  fprintf(diffone,"%c", ch1);
    }
    //    fclose(diffone);
    end1 = clock();
    cpu_time_used1 = (float)(end1 - start1)/CLOCKS_PER_SEC;
    cpu_time_used1 *= 1000;
    printf("Time taken to compare one to two: %f ms\n", cpu_time_used1);

    fseek(fh1, 0, SEEK_SET);//reset position of fh1
    fseek(fh2, 0, SEEK_SET);//reset position of fh2

    char* readText(int, FILE*);
    char *text1 = readText(size1, fh1);
    char *text2 = readText(size2, fh2);
    char *cmp2to1;
    // int i;
    // for (i=0; i<size1; i++)
    // printf("text1[%d] = %c\n", i, text1[i]);
    int i;
    int j;
    int k = 0;
    int l;
    int count = 0;
   
    //counts number of differences between file1 and file2, determining size of difftwo
    
    
    start2 = clock();
    if (size2 > size1)
      {
	for (l=0; l < size1; l++)
	  {
	    if(text1[l]!=text2[l])
	      count++;
	  }
	count+=(size2-size1);
	cmp2to1 = malloc(count * sizeof(char));
	for (i=0; i < size1; i++)
	  {
	    if(text1[i]!=text2[i])
	      {
		cmp2to1[k]=text2[i];
		k++;
	      }
	  }
	for (j=i; j<size2; j++)
	  {
	    cmp2to1[k] = text2[j];
	    k++;
	  }
      }
    else if(size1>size2)
      {
	for (l=0; l < size2; l++)
	  {
	    if(text1[l]!=text2[l])
	      count++;
	  }
	count+=(size1-size2);
	cmp2to1 = malloc(count * sizeof(char));
	for (i=0; i < size2; i++)
	  {
	    if(text1[i]!=text2[i])
	      {
		cmp2to1[k]=text2[i];
		k++;
	      }
	  }
	for (j=i; j<size1; j++)
	  {
	    cmp2to1[k] = text2[j];
	    k++;
	  }
      } 
    else 
      {
	for (l=0; l < size2; l++)
	  {
	    if(text1[l]!=text2[l])
	      count++;
	  }
	cmp2to1 = malloc(count * sizeof(char));
	for (i=0; i < size2; i++)
	  {
	    if(text1[i]!=text2[i])
	      {
		cmp2to1[k]=text2[i];
		k++;
	      }
	  }
      }
    end2 = clock();
    cpu_time_used2 = ((float) (end2 - start2))/CLOCKS_PER_SEC;
    cpu_time_used2*=1000;
    printf("Time taken to compare two to one: %f ms\n", cpu_time_used2);
    
    //fprintf(difftwo, "%s", cmp2to1);
    fprintf(difftwo, cmp2to1);
    fclose(fh1);
    fclose(fh2);
    fclose(diffone);
    fclose(difftwo);
    free(text1);
    free(text2);
    free(cmp2to1);
    return 0;
}
char *readText(int size, FILE *fh){
  char * text = malloc(size * sizeof(char));
  int i=0;
  while(!(feof(fh)))
    {
      fgets(text, size+1, fh);
      ++i;
    }
  return text;
}

