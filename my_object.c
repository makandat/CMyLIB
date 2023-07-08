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
MY_HEAP MyObject* my_wrap(void* data, MY_DATATYPE type, int32_t size, size_t length) {
    MyObject* obj = (MyObject*)malloc(sizeof(MyObject));
    obj->refcount = 1;
    obj->type = type;
    obj->size = size;
    obj->length = length;
    obj->data = data;
    return obj;
}
