#include <stdio.h> 
#include <stdlib.h>
                                                                                
int main(int argc, char* argv[]) {
	
	errno_t err;	// �^�ǿ��~���ƭ�
	
	char ch1[] = "C:\\c++\\epbgit\\ConsoleApplication\\Debug\\out\\data.txt";
	

    FILE *file;// = fopen("C:\\c++\\epbgit\\ConsoleApplication\\Debug\\out\\data.txt", "r");
    char name[30]; 
    int request, account, score; 
     
	if (( err = fopen_s(&file,ch1, "r")) != 0)
	{
	 printf("cant open the file");
	 exit(1);
	}


    puts("��J�ﶵ:");
    puts("1) ��ܩҦ��ǥͻP����");
    puts("2) ��ܤή�ǥͻP����");
    puts("3) ��ܤ��ή�ǥͻP����");
    puts("4) ���}");

    while(1) { 
        printf("\n�ﶵ? "); 
        scanf_s("%d", &request); 
        if(request == 4) {
            break; 
        }

        switch(request) { 
            case 1: 
                puts("\n�Ҧ��ǥͻP����:");
                break; 
            case 2: 
                puts("\n�ή�ǥͻP����:");
                break; 
            case 3: 
                puts("\n���ή�ǥͻP����:");
                break; 
        } 

        fscanf_s(file, "%d\t%s\t%d", &account, name, &score); 
        while(!feof(file)) { 
            if((request == 1) || (request == 2 && score >= 60) || 
               (request == 3 && score < 60)) {
                printf("%d\t%s\t%d\n", account, name, score);     
            }

            fscanf_s(file, "%d\t%s\t%d", &account, name, &score); 
        } 

        rewind(file);  // ���m��СA�]�i�ϥ� fseek(file, 0, SEEK_SET);
    } 

    fclose(file); 
    
	system("pause");
    return 0; 
}