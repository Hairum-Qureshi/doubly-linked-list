#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dll_functions.h"

#define BUFFER_SIZE 128

node_t* addStudentData(node_t* head, char* first_name, char* last_name, char* studentYear, char* gradYear, long studentID) {
    // This function makes sure to include data at the end of the DLL
    node_t* newNode = malloc(sizeof(node_t));
    if(!newNode) {
        printf("Memory allocation failed \n");
        return head;
    }

    newNode->studentData.first_name = strdup(first_name);
    newNode->studentData.last_name = strdup(last_name);
    newNode->studentData.studentYear = strdup(studentYear);
    newNode->studentData.gradYear = strdup(gradYear);
    newNode->studentData.studentID = studentID;

    newNode->next = NULL;
    newNode->prev = NULL;

    if(!head) {
        return newNode;
    }

    node_t* lastNode = head;
    while(lastNode->next) {
        lastNode = lastNode->next;
    }

    lastNode->next = newNode;
    newNode->prev = lastNode;
    return head;
}

void printList(node_t* head) {
   if(!head) {
      printf("The list is currently empty \n");
   }
   else {
      printf("Here are the list of students: \n");
      node_t* temp = head;
      while(temp) {
        printf("--------------------------------------------- \n");
        printf("First Name: %s", temp->studentData.first_name);
        printf("Last Name: %s", temp->studentData.last_name);
        printf("Student Year: %s", temp->studentData.studentYear);
        printf("Expected Grad Year: %s \n", temp->studentData.gradYear);
        printf("Student ID: %ld \n", temp->studentData.studentID);
	temp = temp->next;
      }
     printf("--------------------------------------------- \n");
   }
}

void printListInReverse(node_t* head) {
   if(!head) {
      printf("The list is currently empty \n");
   }
   else {
     printf("Here is the list printed in reverse: \n");
     node_t* tail = head;
     while(tail->next != NULL) {
        tail = tail->next;
     }

     node_t* curr = tail;
     while(curr) {
        printf("--------------------------------------------- \n");
        printf("* First Name: %s", curr->studentData.first_name);
        printf("* Last Name: %s", curr->studentData.last_name);
        printf("* Student Year: %s", curr->studentData.studentYear);
        printf("* Expected Grad Year: %s \n", curr->studentData.gradYear);
        printf("* Student ID: %ld \n", curr->studentData.studentID);
        curr = curr->prev;
     }
     printf("--------------------------------------------- \n");
   }
}

node_t* removeByLastName(node_t* head, char* last_name) {
   if(!head) {
     printf("The list is currently empty \n");
   }
   else {
     node_t* temp = head;
     int foundLastName = 0;

     while(temp) {
       if(strcmp(temp->studentData.last_name, last_name) == 0) {
          foundLastName = 1;
       }
       temp = temp->next;
     }

     if(foundLastName == 1) {
     	printf("** Deleting students with last name: %s", last_name);
     	while(temp) {
       	   if(strcmp(temp->studentData.last_name, last_name) == 0) {
             if(temp == head) {
               head = head->next;
             }
             node_t* nextNode = temp->next;
             node_t* prevNode = temp->prev;
             if(nextNode) {
               nextNode->prev = prevNode;
             }
	     if(prevNode) {
               prevNode->next = nextNode;
             }
	     node_t* next = temp->next;
             free(temp->studentData.first_name);
             free(temp->studentData.last_name);
             free(temp->studentData.studentYear);
             free(temp->studentData.gradYear);
             free(temp);
             temp = next;
            }
           else {
             temp = temp->next;
           }
        }
        printf("Deletion complete! \n");
     }
     else {
	printf("** Could not find any students with the last name: %s", last_name);
     }
     return head;
   }
}

void freeDLLMemory(node_t* head) {
   if(!head) {
     return;
   }
   else {
     node_t* current = head;
     while(current) {
       node_t* next = current->next;
       free(current->studentData.first_name);
       free(current->studentData.last_name);
       free(current->studentData.studentYear);
       free(current->studentData.gradYear);
       free(current);
       current = next;
     }
   }
}

int main() {

  int num;
  node_t* head = NULL;

  while(1) {
      printf("===================================================== \n");
      printf("Enter a number for the action you would like to do: \n");
      printf("[1] - Add student data \n");
      printf("[2] - Remove students by last name \n");
      printf("[3] - Print list \n");
      printf("[4] - Print list (reversed) \n");
      printf("[5] - Exit \n");
      printf("===================================================== \n");
      printf("> ");

      int result = scanf("%d", &num);
      while(getchar() != '\n');

      if(num == 5) break;

      switch(num) {
        case 1: {
           char first_name[BUFFER_SIZE];
           char last_name[BUFFER_SIZE];
	   char studentYear[BUFFER_SIZE];
           char gradYear[5];
           long studentID;

           printf("Enter student first name > ");
           fgets(first_name, sizeof(first_name), stdin);

           printf("Enter student last name > ");
           fgets(last_name, sizeof(last_name), stdin);

           printf("Enter student year (freshman, sophomore, junior, or senior > ");
           fgets(studentYear, sizeof(studentYear), stdin);

           printf("Enter student expected graduation year > ");
           fgets(gradYear, sizeof(gradYear), stdin);

           printf("Enter student ID number > ");
           scanf("%ld", &studentID);

           while(getchar() != '\n');

           head = addStudentData(head, first_name, last_name, studentYear, gradYear, studentID);
	   break;
       }
       case 2: {
           char lastNameToDelete[BUFFER_SIZE];
	   printf("Please enter the LAST NAME of the student(s) you would like to remove > ");
           fgets(lastNameToDelete, sizeof(lastNameToDelete), stdin);
	   head = removeByLastName(head, lastNameToDelete);
           break;
       }
       case 3:
          printList(head);
          break;
       case 4:
          printListInReverse(head);
          break;
     }
  }
  freeDLLMemory(head); 
  return 0;
}
