/* my_object.c */
#include "my_object.h"


/* 参照カウントの操作: カウントを減らす。 */
void my_object_release(MyObject* myobj) {
    if (myobj->refcount > 0)
        myobj->refcount--;
    if (myobj->refcount == 0 && myobj->type != MY_EMPTY) {
        free(myobj->data);
        myobj->type = MY_EMPTY;
        myobj->data = NULL;
        free(myobj);
    }
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
char* my_object_str(MyObject* obj) {
    char* p = NULL;
    if (obj->type == MY_STRING) {
        p = (char*)(obj->data);
    }
    return p;
}

/* ワイド文字列を取り出す。 */
wchar_t* my_object_wstr(MyObject* obj) {
    wchar_t* p = NULL;
    if (obj->type == MY_WIDE_STRING) {
        p = (wchar_t*)(obj->data);
    }
    return p;
}

/* 32ビット整数を更新する。(型の変更は不可) */
void my_object_set_int32(MyObject* obj, int32_t n) {
    if (obj->type == MY_INT32)
        *(int32_t*)(obj->data) = n;
}

/* 64ビット整数を更新する。(型の変更は不可) */
void my_object_set_int64(MyObject* obj, int64_t n) {
    if (obj->type == MY_INT64)
        *(int64_t*)(obj->data) = n;
}

/* size_t を更新する。 */
void my_object_set_size(MyObject* obj, size_t n) {
    if (obj->type == MY_SIZE)
        *(size_t*)(obj->data) = n;
}

/* 倍精度浮動小数点数を更新する。 */
void my_object_set_double(MyObject* obj, double x) {
    if (obj->type == MY_DOUBLE)
        *(double*)(obj->data) = x;
}

/* 文字列を更新する。 */
void my_object_set_str(MyObject* obj, char* str) {
    if (obj->type == MY_STRING) {
        size_t sz = strlen(str) + sizeof(char);
        free((char*)obj->data);
        obj->data = malloc(sz);
        strcpy((char*)(obj->data), str);
    }
}

/* ワイド文字列を更新する。 */
void my_object_set_wstr(MyObject* obj, wchar_t* str) {
    if (obj->type == MY_WIDE_STRING) {
        size_t sz = wcslen(str) + sizeof(wchar_t);
        free(obj->data);
        obj->data = malloc(sz);
        wcscpy((wchar_t*)(obj->data), str);
    }
}


/* 値が等しい */
bool my_object_equal(MyObject* a, MyObject* b) {
    if (a->type != b->type)
        return false;
    if (a->size != b->size)
        return false;
    if (a->length != b->length)
        return false;
    size_t sz = a->size * a->length;
    char* p = a->data;
    char* q = b->data;
    for (int i = 0; i < (int)sz; i++) {
        if (memcmp(p, q, 1) == 0) {
            continue;
        }
        else {
            return false;
        }
        p++;
        q++;
    }
    return true;
}

/* 同じオブジェクト */
bool my_object_identical(MyObject* a, MyObject* b) {
    if (a->type != b->type)
        return false;
    if (a->size != b->size)
        return false;
    if (a->length != b->length)
        return false;
    if (a->data != b->data)
        return false;
    return true;
}
