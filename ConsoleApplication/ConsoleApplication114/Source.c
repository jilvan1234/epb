#include <stdio.h> 
                                                                                
int main(int argc, char* argv[]) {

	char name[10]; 
    int score; 
	//
	
	errno_t err;
    FILE *file;    
	char ch1[] = "C:\\c++\\epbgit\\ConsoleApplication\\Debug\\out\\test.txt";
	char ch2[] = "C:\\c++\\epbgit\\ConsoleApplication\\Debug\\out\\test.txt";
	                        
	
    if(err = fopen_s(&file,ch1, "w")) { 
        puts("�ӷ��ɮ׶}�ҥ���"); 
        return 1; 
    }

    fprintf(file, "%s\t%d\r\n", "Justin", 90);
    fprintf(file, "%s\t%d\r\n", "momor", 80);
    fprintf(file, "%s\t%d\r\n", "bush", 75);    

    fclose(file);

	
    if(err = fopen_s(&file,ch2, "r")) { 
        puts("�ӷ��ɮ׶}�ҥ���"); 
        return 1; 
    }
    
    
    puts("Name\tScore"); 
	
    
    while(fscanf_s(file,"%s\t%d", name, &score) != EOF) { 
        // �g��зǿ�X
        fprintf(stdout, "%s\t%d\n", name, score); 
    } 

    fclose(file);

    return 0; 
}