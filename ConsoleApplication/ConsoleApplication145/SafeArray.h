//#include "ArrayIndexOutOfBoundsException.h"

template <typename CType>
class SafeArray { 
public: 
    // �غc�禡 
    SafeArray(int); 
    // �Ѻc�禡 
    ~SafeArray();
 
    CType get(int); 
    void set(int, CType);
 
    int length;
private:
    CType *_array; 

    bool isSafe(int i); 
};

// �ʺA�t�m�}�C
template <typename CType>
SafeArray<CType>::SafeArray(int len) {
    length = len;
    _array = new CType[length];
}

// ���լO�_�W�X�}�C����
template <typename CType>
bool SafeArray<CType>::isSafe(int i) {
    // 
    if(i >= length || i < 0) {
        return false;
    } 
    else {
        return true;
    }
}

// ���o�}�C������
template <typename CType>
CType SafeArray<CType>::get(int i) {
    if(isSafe(i)) {
        return _array[i]; 
    }
    else {
        // �s���W�L�}�C���סA��X�ҥ~ 
        throw ArrayIndexOutOfBoundsException(i); 
    }
}

// �]�w�}�C������
template <typename CType>
void SafeArray<CType>::set(int i, CType value) {
    if(isSafe(i)) {
        _array[i] = value;
    }
    else {
        // �s���W�L�}�C���סA��X�ҥ~
        throw ArrayIndexOutOfBoundsException(i); 
    }
}

// �R���ʺA�t�m���귽
template <typename CType>
SafeArray<CType>::~SafeArray() {
    delete [] _array;
}