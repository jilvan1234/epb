#include <stdio.h> 
#include <stdlib.h>
#include "Student.h" 

int main(int argc, char* argv[]) {
    struct Student student; 
    int count = 0; 
	errno_t err;	// �^�ǿ��~���ƭ�
	char ch1[] = "C:\\c++\\epbgit\\ConsoleApplication\\Debug\\out\\data.txt";
    FILE *file ;//= fopen(ch1, "r+b"); 
	

	if (( err = fopen_s(&file,ch1, "r+b")) != 0)
	{
	 printf("cant open the file");
	 exit(1);
	}

    while(1) { 
        fread((char*) &student, sizeof(student), 1, file); 
        if(!feof(file)) {
            count++; 
        }
        else {
            break; 
        }
    } 

    rewind(file); 

    printf("��J�Ǹ�(1-%d)\n", count);
    puts("��J0���}"); 

    while(1) { 
        printf("\n�Ǹ�? "); 
        scanf_s("%d", &(student.studyNumber)); 
        if(student.studyNumber == 0) {
            break; 
        }
        
        printf("��J�m�W ����\n? ");
        scanf_s("%s %lf", student.name, &(student.score)); 

        fseek(file, (student.studyNumber - 1) * sizeof(student), SEEK_SET); 
        fwrite((char*) &student, sizeof(student), 1, file); 
    } 

    fclose(file); 
    
	system("pause");
    return 0; 
}