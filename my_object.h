/* my_object.h */
#ifdef MY_OBJECTH
#else
#define MY_OBJECTH
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <wchar.h>

/* データの型 */
#define MY_DATATYPE  uint32_t
#define MY_EMPTY  0
#define MY_INT8   1
#define MY_INT16  2
#define MY_INT32  3
#define MY_BOOL   4
#define MY_INT64  5
#define MY_UINT8  6
#define MY_UINT16 7
#define MY_UINT32 8
#define MY_UINT64 9
#define MY_FLOAT   10
#define MY_DOUBLE  11
#define MY_LONG_DOUBLE  12
#define MY_POINTER 13
#define MY_STRING       30
#define MY_MB_STRING    31
#define MY_WIDE_STRING  32
#define MY_STRUCT  33
#define MY_SIZE    34

/* バッファサイズ */
#define MY_BUFSIZE 1024

/* ヒント用シンボル */
// データはヒープ上にあり、その所有者となることを示す。(不要になったら free() で解放する責任を負う)
#define MY_HEAP
// データはスタック上にあり、直ちに安全な場所へコピーする必要があることを示す。
#define MY_STACK

/* オブジェクトの定義 */
typedef struct tagMyObject {
    int32_t refcount;  // 参照カウント
    int32_t type;      // データの型
    int32_t size;      // 要素の長さ (バイト数)
    size_t length;     // 長さ (配列の場合の要素数、配列でない場合は 1)
    void* data;        // データへのポインタ (NULL ならデータが未定義)
} MyObject;

/* 参照カウントの操作 */
inline void my_object_addref(MyObject* myobj) { myobj->refcount++; };
void my_object_release(MyObject* obj);

/* ハッシュ値 */
uint16_t my_object_hash(MyObject* obj);

/* 文字列化 */
MY_HEAP char* my_object_string(MyObject* obj);

/* オブジェクト化 */
MY_HEAP MyObject* my_object_wrap(void* data, MY_DATATYPE type, int size, size_t length);

/* データを取り出す */
int32_t my_object_int32(MyObject*);
int64_t my_object_int64(MyObject*);
size_t my_object_size(MyObject*);
double my_object_double(MyObject*);
char* my_object_str(MyObject*);
wchar_t* my_object_wstr(MyObject*);

/* データを更新する。(型の変更は不可) */
void my_object_set_int32(MyObject*, int32_t);
void my_object_set_int64(MyObject*, int64_t);
void my_object_set_size(MyObject*, size_t);
void my_object_set_double(MyObject*, double);
void my_object_set_str(MyObject*, char*);
void my_object_set_wstr(MyObject*, wchar_t*);


/* 複製を作る */
MY_HEAP MyObject* my_object_copy(MyObject* obj);

/* 値が等しい */
bool my_object_equal(MyObject*, MyObject*);

/* 同じオブジェクト */
bool my_object_identical(MyObject*, MyObject*);

#endif


