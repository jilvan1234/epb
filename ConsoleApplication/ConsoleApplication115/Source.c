#include <stdio.h> 
#include <stdlib.h>
                                                                                
int main(int argc, char* argv[]) {
	
    unsigned char ch; 
    int count = 0; 
	char ch1[] = "C:\\c++\\epbgit\\ConsoleApplication\\Debug\\out\\test.txt";
    FILE *file = fopen(ch1, "rb");

	/*
    if(argc != 2) { 
        puts("���O: read <filename>"); 
        return 1; 
    } */

    if(!file) { 
        puts("�L�kŪ���ɮ�"); 
        return 1; 
    } 


    while(!feof(file)) { 
        fread(&ch, sizeof(char), 1, file);
        
        printf("%2X ", ch);
        count++; 
        if(count > 16) {  // ���� 
            putchar('\n');
            count = 0; 
        } 
    } 
    putchar('\n');

    fclose(file);
        
	system("pause");
    return 0; 
}