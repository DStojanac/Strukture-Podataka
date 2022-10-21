#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define FILE_DIDNT_OPEN_ERROR (-1)
#define MAX_LINE (1024)
#define MAX_FILE_NAME (256)
#define MAX_NAME (50)
#define MAX_SURNAME (50)
#define MAX_BODOVA (70)

struct students;

typedef struct students {
  char ime[MAX_NAME];
  char prezime[MAX_SURNAME];
  float bodovi;
}student;


int countStudentsFromFile(char* filename);
int readingFromFile(char *filename, student *st, int br_stud);
void printInfo(student *st,int br_stud);

int main(void){

  int i=0;
  student *stud=NULL; 
  int br_stud=0;
  char filename[MAX_FILE_NAME]={0};
  

  printf("Insert filename: ");
  scanf(" %s",filename);

  
  printf("Broj studenata u datoteci %s je %d \r\n",filename,countStudentsFromFile(filename));

  br_stud=countStudentsFromFile(filename);

  stud=(student*)malloc(br_stud*sizeof(student));
  if(stud==NULL){
    printf("Memory not allocated correctly!");
    return FILE_DIDNT_OPEN_ERROR;
  }

  
   readingFromFile(filename,  stud,  br_stud);
   printInfo(stud, br_stud);
  

  return EXIT_SUCCESS;
}

int countStudentsFromFile(char* filename) {
    FILE* fp = NULL;
    int count = 0;
    char buffer[MAX_LINE] = { 0 };

    fp = fopen(filename, "r");
    if (fp == NULL) {
        printf("Dear customer, the file %s didn't open! \r\n", filename);
        return FILE_DIDNT_OPEN_ERROR;
    }

    while (!feof(fp)) {

      if(fgets(buffer,MAX_LINE,fp)){
        if (strcmp("\n", buffer) != 0) {
            count++;
         } 
      }
    }
        fclose(fp);
        return count;
}


int readingFromFile(char *filename, student *st,int br_stud){
  int i=0;
  FILE* fp = NULL;
  fp = fopen(filename, "r");

  if (fp == NULL) {
        printf("Dear customer, the file %s didn't open! \r\n", filename);
        return FILE_DIDNT_OPEN_ERROR;
    }

  for(i=0;i<br_stud;i++){
    fscanf(fp,"%s %s %f",st[i].ime,st[i].prezime, &st[i].bodovi);
  }
  fclose(fp);
    return EXIT_SUCCESS;
}



void printInfo(student *st,int br_stud){

  float rel_bodovi=0.0;
  int i=0;
  
  printf("IME\tPREZIME\tAPS.BODOVI\tREL.BODOVI\n");


  for(i=0;i<br_stud;i++){

    student stud= *(st+i);
    rel_bodovi=(((float)stud.bodovi/MAX_BODOVA)*100);

    
    printf("%s\t%s\t%.2lf\t\t%.2f%% ",st[i].ime,st[i].prezime,st[i].bodovi,rel_bodovi);

    printf("\n");
  }

}

