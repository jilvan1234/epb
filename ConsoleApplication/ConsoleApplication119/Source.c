#include <stdio.h> 
#include <stdlib.h>
#include "Student.h" 

int main(int argc, char* argv[]) 
{
	char ch1[] = "C:\\c++\\epbgit\\ConsoleApplication\\Debug\\out\\data.txt";
    FILE *file = fopen(ch1, "wb"); 
	
    int count; 
    struct Student student = {0, "", 0.0}; 
    int i;
	/*
    if(argc != 2) { 
        puts("���O: create <filename>"); 
        return 1; 
    } */

    if(!file) { 
        puts("�ɮ׿�X����"); 
        return 1; 
    } 

    printf("�n�إߴX����ơH "); 
    scanf("%d", &count); 

    for(i = 0; i < count; i++) { 
        fwrite((char*) &student, sizeof(student), 1, file); 
    } 

    fclose(file);
        
	system("pause");
    return 0; 
}