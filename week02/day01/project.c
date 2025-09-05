#include<stdio.h>
#include<stdlib.h>
// #include<string.h>
// #include<time.h>
//

typedef struct {
    int id;
    char name[32];
    
} Student;

int
main(int argc, char ** args)
{
    // FILE *f = fopen("Student", "wb");
    // Student student = {1, "Hello"};
    // printf("id: %d , name: %s\n", student.id, student.name);
    // fwrite(&student, sizeof(Student), 1, f);
    // fclose(f);
    

    FILE *f = fopen("Student", "rb");
    Student student;
    fread(&student, sizeof(Student), 1, f);
    printf("id: %d , name: %s\n", student.id, student.name);
    fclose(f);
    



   return 0;

}
