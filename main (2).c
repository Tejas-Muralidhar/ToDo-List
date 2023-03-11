//Tejas(1RN21CS171) and Sanjana(1RN21CS136)... Started 6th May 2023

/*C Mini Project: To-Do List
Expectations from the project:

1. It should ask the user to create a new task. The entered task will have a default status of 'todo'.
2. Like this, new tasks can be created, old tasks can be deleted and old tasks can also have the task status changed to completed.
3. The program also provides for the tasks to be edited at any time.*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <math.h>
#include <stdbool.h>

struct node{
    unsigned int index;
    char task[100];
    unsigned int st;
    struct node * link;
};
typedef struct node nd;

char * get_status_meaning(int);
nd * add_task(nd * , unsigned int * );
nd * remove_task(nd * , unsigned int * );
void display_list(nd *);
nd * change_status(nd * , unsigned int );
nd * change_task(nd *,unsigned int);
nd * edit_task(nd * , unsigned int * );
void print_logo();

void print_logo(){
    system("clear");
    printf(R"EOF(########  #######  ########   #######     ##       ####  ######  ######## 
   ##    ##     ## ##     ## ##     ##    ##        ##  ##    ##    ##    
   ##    ##     ## ##     ## ##     ##    ##        ##  ##          ##    
   ##    ##     ## ##     ## ##     ##    ##        ##   ######     ##    
   ##    ##     ## ##     ## ##     ##    ##        ##        ##    ##    
   ##    ##     ## ##     ## ##     ##    ##        ##  ##    ##    ##    
   ##     #######  ########   #######     ######## ####  ######     ##    )EOF");
   printf("\n");
}

nd * add_task(nd * todolist, unsigned int * index_number){
   //creates a new node, sets it status to todo and makes its task as given by the input.
    nd* new_task = NULL,* l = NULL;
    while(!new_task)
        new_task = (nd*)malloc(sizeof(nd));
    printf("Enter the task: ");
    scanf(" %[^\n]s",new_task->task);
    new_task->st = 1; //set to ToDo by default
    new_task->index = ++(*index_number); 
    new_task->link = NULL;
    if(todolist == NULL)
        return new_task;
    for(l=todolist;l->link!=NULL;l=l->link);
    l->link = new_task;
    return todolist;
}

nd * remove_task(nd * todolist, unsigned int * index_number){
   /*asks for the index of node to be deleted and removes the node, decrementing the index of 
    all nodes behind it*/ 
    char ch[2];
    int delete_index =-1;
    bool flag = true;
    display_list(todolist);
    while(flag){
        printf("\nEnter the index of the task you want to delete");
        printf("\nYour Choice: ");
        scanf("%s",ch);
        delete_index = atoi(ch);
        if(delete_index < 1 || delete_index > (*index_number)){
            printf("Try Again...\n");
        }
        else{
            flag = false;
            nd *p=NULL, *l=NULL;
            if(delete_index == 1){
                l=todolist;
                todolist = todolist->link;
                free(l);
                for(l=todolist;l!=NULL;l=l->link)
                    l->index -= 1;
            }
            else if(delete_index == (*index_number)){
                for(l=todolist;l->index!=delete_index;p=l,l=l->link);
                p->link = NULL;
                free(l);
            }
            else{
                for(l=todolist;l->index!=delete_index;p=l,l=l->link);
                p->link = l->link;
                free(l);
                for(p=p->link;p!=NULL;p=p->link)
                    p->index -=1;
            }
           (*index_number)--; 
           return todolist; 
        }
    }
}

void display_list(nd * todolist){
   //used to display the complete list of all tasks and their status. 
    if(todolist == NULL){
       printf("Your ToDo list is currently empty!\n");
       return;
    }
    printf("\n");
    while(todolist!=NULL){
        printf("%u. %s =====> %s\n",todolist->index,todolist->task,get_status_meaning(todolist->st));
        todolist = todolist->link;
    }
}

nd * change_status(nd * todolist, unsigned int index_number){
   //used to change the status of a particular task. Called from edit_task() function.
   nd* l = NULL;
   unsigned int s;
   char t[100];
   unsigned int required_index;
   do{
        display_list(todolist);
        printf("\nEnter the index for which you'd like to change the status\n");
        printf("Enter your choice: ");
        scanf("%s",t);
        required_index = atoi(t);
        if(required_index < 1 || required_index > index_number)
            printf("Try Again...\n");
    }while ( required_index < 1 || required_index > index_number);
   do{
       printf("\nWhat would you like to change the status to?\n");
       printf("1.Todo\n2.In Progress\n3.Completed\n4.On Hold\n");
       printf("Enter your choice: ");
       scanf("%s",t);
       s = atoi(t);
       if(!(s>0&&s<5))
        printf("\nInvalid Choice. Try Again...\n");
   }while(!(s>0&&s<5));
   for(l=todolist;(l->index)!=required_index;l=l->link);
   l->st = s;
   return todolist;
}

nd * change_task(nd * todolist,unsigned int index_number){
    nd* l = NULL;
    unsigned int s;
    char t[2];
    char task[100];
    unsigned int required_index;
    do{
        display_list(todolist);
        printf("\nEnter the index for which you'd like to change the task\n");
        printf("Enter your choice: ");
        scanf("%s",t);
        required_index = atoi(t);
        if(required_index < 1 || required_index > index_number)
            printf("Try Again...\n");
    }while ( required_index < 1 || required_index > index_number);
    printf("\nWhat would you like to change the status to?\n");
    printf("Enter the task: ");
    scanf(" %[^\n]s",task);
    for(l=todolist;(l->index)!=required_index;l=l->link);
    strcpy(l->task,task);
    return todolist;
}

nd * edit_task(nd * todolist, unsigned int * index_number){
   //used to change the task of a node or to change the status of a node. Call change_status() function for the latter job.
    char ch[200],x[2];
    int choice;
    bool flag = false;
    do{
        printf("\nWhat would you like to edit?\n1.The Task\n2.The Status\n3.Back to Main Menu\n");
        printf("Enter your choice: ");
        scanf("%s",x);
        choice = atoi(x);
        switch(choice){
            case 1: return change_task(todolist,*(index_number));
            case 2: return change_status(todolist,*(index_number));
            case 3: return todolist;
            default: printf("Try Again...\n");
                    flag = true;
        }
    }while(flag);
}

char * get_status_meaning(int s){
   //to convert the enum values into strings to be stored and printed in the nodes.    
    switch(s){
        case 1: return "ToDo"; 
        case 2: return "In Progress";
        case 3: return "Completed";
        case 4: return "On Hold";
    }
}

int main(){
    nd * todolist = NULL;
    unsigned int index_number = 0;
    print_logo();
    printf("\nThis is a ToDo List Program\n");
    for(;;){
        printf("\n1.View my ToDo List\n2.Add a Task\n3.Delete a task\n4.Edit a task\n5.Exit the program\n");
        printf("Your Choice: ");
        char ch[2];
        scanf("%s",ch);
        int choice = atoi(ch);
        switch(choice){
            case 1: display_list(todolist); break;
            case 2: todolist = add_task(todolist,&index_number); break;
            case 3: todolist = remove_task(todolist,&index_number); break;
            case 4: todolist = edit_task(todolist,&index_number); break;
            case 5: printf("Exiting..."); return 0;
            default: printf("Try Again...\n");break;
        }
    }
    return 0;
}

