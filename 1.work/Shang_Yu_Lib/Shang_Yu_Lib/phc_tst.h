char *test_serect();
char* LockVarR(char *A,int size);
void LockVarW(char *A,int size);
void loadtable();
void SDCARD_LOCK_IO_TST(int startbit,int size,char* buff,char* buff2);
void SDCARD_READ_tst(int startbit,int size,char* buff);




//��ڨϥ�
void SDCARD_READ(int startbit,int size,char* buff);  //SDCARD �a���r�J
void SDCARD_WRITE(int startbit,int size,char* buff); //SDCARD �[�K��X
void loadtable();