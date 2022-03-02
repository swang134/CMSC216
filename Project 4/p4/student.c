#include "student.h"
#include <string.h>

Student new_student(const char name[], unsigned int id, float shoe_size){
  char namecopy[39];
  Student student;
  if(name != NULL)
    strcpy(namecopy, name);
  else
    strcpy(namecopy, "");
  strcpy(student.name , namecopy);
  student.id = id;
  student.shoe_size = shoe_size;
  
  return student;  
}

void init_student(Student *const student, const char name[], unsigned int id,
                  float shoe_size){
  if(student!=NULL){
    char namecopy[39];
    if(name != NULL)
      strcpy(namecopy, name);
    else
      strcpy(namecopy, "");
    strcpy(student->name , namecopy);
    student->id = id;
    student->shoe_size = shoe_size;
  }
}

unsigned int has_id(Student student, unsigned int id){
  return student.id == id;
}

unsigned int has_name(Student student, const char name[]){
  if(name == NULL)
    return 0;
  return strcmp(student.name , name)==0;
}

unsigned int get_id(Student student){
  return student.id;
}

float get_shoe_size(Student student){
  return student.shoe_size;
}

Student change_shoe_size(Student student, float new_shoe_size){
  student.shoe_size = new_shoe_size;
  return student;
}

void change_name(Student *const student, const char new_name[]){
  if(student != NULL)
    init_student(student, new_name, student->id, student->shoe_size);
}
