#include <stdlib.h>
#include <stdio.h>
#define MAX_STATES 8

typedef struct state { 

  char name; 
  struct state *next0; 
  struct state *next1;
  int del;
 
}

state_t;
state_t fsm[MAX_STATES]; 

void initialize_states(state_t fsm[]){ 

  char arr[] = {'A','B','C','D','E','F','G','H'};
  int n0[] = {2,4,7,5,6,1,0,3};
  int n1[] = {6,0,1,4,5,2,7,7};
  int k;

  for(k = 0; k < 8; k++){ 
   fsm[k].name = arr[k]; 
   fsm[k].next0 = fsm + n0[k];
   fsm[k].next1 = fsm + n1[k]; 
   fsm[k].del = 0; 
  } 

} 

void change_states(state_t *current, char input[]){ 

  int stateNum = 0; 

  switch(input[2]) { 

   case '0': stateNum = input[4] - current[0].name; 
   if(current[stateNum].del == 0) { 
    current -> next0 = &current[stateNum]; 
   } else { 
    printf("ERROR: State %c HAS BEEN DELETED.\n", input[4]); 
    break; 
   } 
   break; 

   case '1': stateNum = input[4] - current[0].name;
    if(current[stateNum].del == 0){ 
     current -> next1 = &current[stateNum]; 
    } else { 
     printf("ERROR: STATE %c HAS BEEN DELETED.\n", input[4]); 
     break; 
    }    
   break; 
  } 

} 

void print_states(state_t fsm[]){ 

  int i = 0; 
  state_t * next0; 
  state_t * next1; 
  next0 = &fsm[0]; 
  next1 = &fsm[0]; 

  for(i = 0; i < MAX_STATES; i++){ 

   if(fsm[i].del == 0){ 
    printf("%c ", fsm[i].name);
    next0 = &fsm[i]; 
    next1 = &fsm[i]; 
    next0 = next0 -> next0; 
    next1 = next1 -> next1; 
    printf("%c %c \n", next0 -> name, next1 -> name); 
   } 

  } 

} 

void garbage_identify(state_t fsm[]){ 

  char state = 65; 
  int stateNum, i,j,count=0; 

  for(i = 0; i < MAX_STATES; i++){ 

   count=0; 

   for(j = 0;j < MAX_STATES; j++){ 

    if(state == (fsm[j].next0 -> name) || state == (fsm[j].next1 -> name)){ 
     count++; 
    } 
   }
 
   stateNum = state; 

   if(count == 0){ 
    fsm[stateNum - 65].del = 1; 
   } 
   
   state++;
  } 
} 

void print_garbage(state_t fsm[]){ 

  int i,j = 0;
 
  for(i = 0;i < MAX_STATES; i++){

   if(fsm[i].del == 1){ 
    printf("Garbage: %c\n",fsm[i].name); 
    j++; 
   } 
  }
 
  if(j == 0){ 
   printf("No garbage.\n"); 
  } 

} 

void delete_states(state_t fsm[]){ 

  int i,j = 0; 

  for(i = 0;i < MAX_STATES; ++i){ 

   if(fsm[i].del==1){ 
   printf("Deleted: %c", fsm[i].name); 
   fsm[i].name='/'; 
   j++; 
   } 
  }
 
  if(j == 0){ 
   printf("No states to be deleted.\n"); 
  } 

} 

int main(int argc, char * argv[]){
 
  state_t *current; 
  int loop = 0; 
  char input[5]; 
  initialize_states(fsm); 
  current = &fsm[2]; 
  printf("Initial State: %c\n",current->name); 
  printf("Please do not press spacebar, program only records first input ! \n"); 

  while(loop == 0){  

   gets(input);
 
   switch(input[0]){ 

    case '0': current = current -> next0; 
    printf("%c\n", current->name); 
    break;
 
    case '1': current = current -> next1;
    printf("%c\n",current->name); 
    break;
 
    case 'p': print_states(fsm); 
    break;
 
    case 'g': garbage_identify(fsm); 
    print_garbage(fsm); 
    break;
 
    case 'd': delete_states(fsm); 
    break;
 
    case 'c': change_states(current,input); 
    garbage_identify(fsm); 
    break;
 
    case 'e': exit(0); 
    break;
 
    default: printf("Unknown command, please enter another command \n"); 

   } 
  }
 
  exit(0); 

}




