/* my_object.c */
#include "my_object.h"


/* 参照カウントの操作: カウントを減らす。 */
void my_object_release(MyObject* myobj) {
    if (myobj->refcount > 0)
        myobj->refcount--;
    if (myobj->refcount == 0) {
        free(myobj->data);
    }
}


/* ハッシュ値 */
uint16_t my_object_hash(MyObject* myobj) {
    uint16_t hash = 0;
    hash += myobj->type;
    hash += myobj->size;
    hash += myobj->length;
    int n = myobj->size * myobj->length;
    char* p = (char*)myobj->data;
    for (int i = 0; i < n; i++) {
        hash += *p;
        hash &= 0xffff;
        p++;
    }
    return hash;
}

/* 文字列化 */
MY_HEAP char* my_object_string(MyObject* myobj) {
    char buf[MY_BUFSIZE];
    sprintf(buf, "refcount=%d; type=%d; size=%d; length=%ld; data=%p", myobj->refcount, myobj->type, myobj->size, myobj->length, myobj->data);
    size_t sz = strlen(buf) + 1;
    char* ret = (char*)malloc(sz);
    strcpy(ret, buf);
    return ret;
}

/* オブジェクト化 */
MY_HEAP MyObject* my_object_wrap(void* data, MY_DATATYPE type, int32_t size, size_t length) {
    MyObject* obj = (MyObject*)malloc(sizeof(MyObject));
    obj->refcount = 1;
    obj->type = type;
    obj->size = size;
    obj->length = length;
    size_t sz = size * length;
    obj->data = malloc(sz);
    memcpy(obj->data, data, sz);
    return obj;
}

/* 複製を作る */
MY_HEAP MyObject* my_object_copy(MyObject* obj) {
    MyObject* cobj = (MyObject*)malloc(sizeof(MyObject));
    cobj->refcount = obj->refcount;
    cobj->type = obj->type;
    cobj->size = obj->size;
    cobj->length = obj->length;
    size_t sz = obj->size * obj->length;
    cobj->data = malloc(sz);
    memcpy(cobj->data, obj->data, sz);
    return cobj;
}

/* 解放 */
void my_object_free(MyObject* obj) {
    free(obj->data);
    free(obj);
}

/* 整数を取り出す。 */
int32_t my_object_int32(MyObject* obj) {
    int32_t n = 0;
    if (obj->type == MY_INT32) {
        n = *(int32_t*)(obj->data);
    }
    return n;
}

/* 長整数を取り出す。 */
int64_t my_object_int64(MyObject* obj) {
    int64_t n = 0;
    if (obj->type == MY_INT64) {
        n = *(int64_t*)(obj->data);
    }
    return n;
}

/* size_t (unsigned int) を取り出す。 */
size_t my_object_size(MyObject* obj) {
    size_t n = 0;
    if (obj->type == MY_SIZE) {
        n = *(size_t*)(obj->data);
    }
    return n;
}

/* 倍精度浮動小点数を取り出す。 */
double my_object_double(MyObject* obj) {
    double x = 0.0;
    if (obj->type == MY_DOUBLE) {
        x = *(double*)(obj->data);
    }
    return x;
}

/* 文字列を取り出す。 */
char* my_object_string(MyObject* obj) {
    char* p = NULL;
    if (obj->type == MY_STRING) {
        p = *(char**)(obj->data);
    }
    return p;
}

/* ワイド文字列を取り出す。 */
wchar_t* my_object_wstring(MyObject* obj) {
    wchar_t* p = NULL;
    if (obj->type == MY_WIDE_STRING) {
        p = *(wchar_t**)(obj->data);
    }
    return p;
}
