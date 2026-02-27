#ifndef DLLFUNCTIONS_H
#define DLLFUNCTIONS_H

typedef struct student {
  char *first_name;
  char *last_name;
  char *studentYear;
  char *gradYear;
  long studentID;
} student_t;

typedef struct node {
  student_t studentData;
  struct node *prev;
  struct node *next;
} node_t;

node_t* addStudentData(node_t* head, char* first_name, char* last_name, char* studentYear, char* gradYear, long studentID);

void printList(node_t* head);

void printListInReverse(node_t* head);

node_t* removeByLastName(node_t* head, char* last_name);

void freeDLLMemory(node_t* head);

#endif
