#include <stdio.h>
#include <string.h>

typedef struct {
int product_num;
char product_name[80];
char product_type[80];
double product_price;
} product_t;



int
main()
{
FILE *inventoryp;
FILE *binaryp;
int input_status;
    product_t x;

inventoryp = fopen("catalog.txt", "r");
binaryp = fopen("product_list.bin", "wb");
//
// �W���o�@��,�A���e�⥦��bwhile �̭�, �o�˨C��loop���|�M���W�@�������
// 
while (input_status != EOF) {

memset(&x,0,sizeof(product_t));
//
// �����o�Ӱʧ@����, �A��data�̷|���ܦh�ýX
//

input_status = fscanf(inventoryp, "%d", &x.product_num);
input_status = fscanf(inventoryp, "%s", x.product_name);
input_status = fscanf(inventoryp, "%s", x.product_type);
input_status = fscanf(inventoryp, "%lf", &x.product_price);

fwrite(&x, sizeof(product_t), 1, binaryp);
//
// �o�Ӥ��e���L�F, �o�˷|���O�ܦh���ɮתŶ�, ��M�Y�Ǯɭ� �o�˰��O���n��
// �p�G���Q�o��, ��ĳ�A�� product_t ���C��member��write���ʧ@
//

}

fclose(inventoryp);
fclose(binaryp);
    
return 0;
}