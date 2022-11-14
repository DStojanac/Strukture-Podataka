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
position top=NULL;


int readFromFile(char* fileName,char *line);
position createNew(float number);
int push(float number);
float pop();
int printStack();
int readFromBuffer(char *line);
int operations(char operand);
int Delete();

int main(void)
{

    char fileName[MAX_FILE_NAME] = { 0 };
    char line[MAX_LINE]={0};
    float result=0;

    printf("Type in file name: ");
    scanf(" %s", fileName);

    readFromFile(fileName,line);

    
    printf("Postfix from file: %s",line); 

  
    result=top->next->number;
    printf("Result: %.2f\n",result);

    printf("==================================\n");
    
    if(Delete()==0){
      printf("Successful memory cleaning p1!");
      printf("\n");
    }
    
    return EXIT_SUCCESS;
}

int readFromFile(char* fileName,char *line)
{
    char buffer[MAX_LINE] = { 0 };
    FILE* fp = NULL;
    fp = fopen(fileName, "r");

  
    if (fp == NULL) {
        printf("Dear customer, the file %s didn't open! \r\n", fileName);
        return FILE_DIDNT_OPEN_ERROR;
    }

    while(!feof(fp)){
        fgets(buffer,MAX_LINE,fp);
        readFromBuffer(buffer);
    }

    strcpy(line,buffer);
    
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
    
    return new;
}

int push(float number)
{
    position new = NULL;
    new = createNew(number);

    if (new == NULL) {
        printf("Memory not allocated correctly!");
        return MEMORY_NOT_ALLOCATED_CORRECT;
    }
    
    
    new->next = top;
    top=new;
    
    return EXIT_SUCCESS;
}

int printStack(){
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

float pop(){
  position temp;
  float number=0;
  if (top == NULL) {
      printf("Stack is empty!");
      return MEMORY_NOT_ALLOCATED_CORRECT;
  }
    
    number=top->number;  
    temp=top;
    top=top->next;
    free(temp);

  return number;
}

int readFromBuffer(char *line){

  float number=0;
  char operand=0;
  int n=0;
  int rez=0;
 

  while (strlen(line) > 0)
  {
      rez = sscanf(line, " %f %n", &number, &n);

      if (rez == 1) 
      {
          push(number);
          line += n;

      }
      else 
      {
          sscanf(line, " %c %n", &operand, &n);
          operations(operand);
          line += n;
      }
  }

    
    return EXIT_SUCCESS;
  }

 

int operations(char operand){
  float number1=0;
  float number2=0;
  float rez=0;

  number1=pop();
  number2=pop();

  switch(operand){
    case '+':
      rez=number2+number1;
      push(rez);
      break;
    case '-':
      rez=number2-number1;
      push(rez);
      break;
    case '*':
      rez=number1*number2;
      push(rez);
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
            push(rez);
        }
        break;
    default:
		printf("Wrong postfix expression!");
		return POSTFIX_ERROR;
  }


  return EXIT_SUCCESS;
}

int Delete(){
  position head=top->next;
  position temp;

  while(head!=NULL){
    temp=head->next;
    free(head);
    head=temp;
  }

  return EXIT_SUCCESS;
}