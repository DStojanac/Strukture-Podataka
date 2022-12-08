#pragma warning (disable: 4047)
#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define FILE_DIDNT_OPEN_ERROR (-1)
#define MAX_LINE (1024)
#define MAX_FILE_NAME (256)
#define MEMORY_NOT_ALLOCATED_CORRECT (-1)
#define POSTFIX_ERROR (-1)
#define DIVIDING_BY_ZERO (-1)

struct _stack;
typedef struct _stack* position;
typedef struct _stack {
	float number;
	position next;
}stack;


int readFromFile(position top,char* fileName,char *line);
position createNew(float number);
int push(position top,float number);
float pop(position top);
int printStack(position top);
int operations(position top,char operation);
int Delete(position top);



int main(void)
{
    stack head={.number=0,.next=NULL};
    position top=&head;
    

    char fileName[MAX_FILE_NAME] = { 0 };
    char line[MAX_LINE]={0};
    float result=0;

    printf("Type in file name: ");
    scanf(" %s", fileName);
    
    readFromFile(top,fileName,line);
    
    // Provjera jel cita iz filea
    printf("Postfix from file: %s",line); 


    result= top->next->number;
    printf("Result: %.2f\n",result);

    printf("==================================\n");
    
    if(Delete(top)==0){
      printf("Successful memory cleaning p1!");
      printf("\n");
    }
    
    return EXIT_SUCCESS;
}



int readFromFile(position top,char* fileName,char *line){
  float number=0;
  char operation=0;
  int n=0;
  char buffer[MAX_LINE] = { 0 };
  char *ptr=buffer;
    FILE* fp = NULL;
    fp = fopen(fileName, "r");

  
    if (fp == NULL) {
        printf("Dear customer, the file %s didn't open! \r\n", fileName);
        return FILE_DIDNT_OPEN_ERROR;
    }

    while(!feof(fp)){
      fgets(buffer,MAX_LINE,fp);
      strcpy(line,buffer);
      while(strlen(ptr)>0){

        if(sscanf(ptr, " %f %n", &number, &n)==1){
          push(top,number);
          ptr += n;
        }
        else if(sscanf(ptr, " %c %n", &operation, &n)==1){
          operations(top,operation);
          ptr += n;
        }
        else{
          printf("Wrong postfix! ");
         }

        }
    }
    fclose(fp);

    return EXIT_SUCCESS;
}


position createNew(float number)
{
    position new = NULL;
    new = (position)malloc(sizeof(stack));

    if (new == NULL) {
        printf("Memory not allocated correctly!");
        return MEMORY_NOT_ALLOCATED_CORRECT;
    }

    new->number = number;
    new->next=NULL;

    return new;
}

int push(position top,float number)
{
    position new = NULL;
    new = createNew(number);

    if (new == NULL) {
        printf("Memory not allocated correctly!");
        return MEMORY_NOT_ALLOCATED_CORRECT;
    }
    
    
    new->next = top->next;
    top->next=new;
    
    return EXIT_SUCCESS;
}

float pop(position top){
  position temp=top->next;
  float number=0.0;

  if (top == NULL) {
        printf("Stack is empty!");
        return MEMORY_NOT_ALLOCATED_CORRECT;
  }
  
  number=temp->number; 

  top->next=temp->next;
  free(temp);

  
  return number;
}


int printStack(position top){
  position temp=top;

  if(temp==NULL){
    printf("Stack empty");
    return FILE_DIDNT_OPEN_ERROR;
  }

  while(temp!=NULL){
    printf("%.2f\n",temp->number);

    temp=temp->next;
  }

  return EXIT_SUCCESS;
}



int operations(position top,char operation){
  float number1=0;
  float number2=0;
  float rez=0;

  number1=pop(top);
  number2=pop(top);

  switch(operation){
    case '+':
      rez=number2+number1;
      push(top,rez);
      break;
    case '-':
      rez=number2-number1;
      push(top,rez);
      break;
    case '*':
      rez=number1*number2;
      push(top,rez);
      break;
    case '/':    
      if (number1 == 0)
        {
            printf("Dividing by zero isn't possible!\n");
            return DIVIDING_BY_ZERO;
        }
        else
        {
            rez = number2 / number1;
            push(top,rez);
        }
        break;
    default:
		  printf("Wrong postfix expression!");
      break;
		return POSTFIX_ERROR;
  }


  return EXIT_SUCCESS;
}

int Delete(position top){
  position head=top->next;
  position temp;

  while(head!=NULL){
    temp=head->next;
    free(head);
    head=temp;
  }

  return EXIT_SUCCESS;
}
