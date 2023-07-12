/* my_string.c */
#include "my_string.h"

/* MyString オブジェクトの参照カウントを増やす。*/
inline void my_addref_str(MyString* str) {
    str->refcount++;
}

/* MyStringArray オブジェクトの参照カウントを増やす。 */
inline void my_addref_strarray(MyStringArray* str) {
    str->refcount++;
}

/* MyString オブジェクトの参照カウントを減らす。 */
void my_release_str(MyString* str) {
    if (str->refcount > 0)
        str->refcount--;
    if (str->refcount == 0) {
        str->type = MY_EMPTY;
        str->size = 0;
        str->length = 0;
        free(str->data);
        str->data = NULL;
        free(str);
    }
}

/* MyStringArray オブジェクトの参照カウントを減らす。*/
void my_release_strarray(MyStringArray* str) {
    if (str->refcount > 0)
        str->refcount--;
    if (str->refcount == 0) {
        str->type = MY_EMPTY;
        str->size = 0;
        char** p = str->data;
        for (int i = 0; i < str->length; i++) {
            free(*p);
            p++;
        }
        str->data = NULL;
        free(str);
    }
}

/* 文字列をラップしてMyStringオブジェクトを作成する。 */
MY_HEAP MyString* my_string_wrap(char* s) {
    MyString* obj = (MyString*)malloc(sizeof(MyString));
    obj->refcount = 1;
    obj->type = MY_STRING;
    obj->size = strlen(s);
    obj->length = 1;
    obj->data = (char*)malloc(obj->size + 1);
    strcpy(obj->data, s);
    return obj;
}

/* 内部の文字列 (char*) を返す。 */
inline const char* my_string_get(MyString* str) {
    return str->data;
}

/* 内部の文字列を更新する。 */
void my_string_set(MyString* str, const char* s) {
    size_t sz = strlen(s) + 1;
    char* buf = (char*)malloc(sz);
    strcpy(buf, s);
    free(str->data);
    str->data = buf;
    str->size = strlen(s);
    return;
}

/* 文字列オブジェクトを複製する。 */
MY_HEAP MyString* my_string_dup(MyString* str) {
    MyString* dup = (MyString*)malloc(sizeof(MyString));
    dup->refcount = str->refcount;
    dup->type = str->type;
    dup->size = str->size;
    dup->length = str->length;
    dup->data = (char*)malloc(dup->size + 1);
    strcpy(dup->data, str->data);
    return dup;
}

/* 文字列を追加する。 */
void my_string_append(MyString* str, const char* s) {
    size_t sz = str->size + strlen(s) + 1;
    char* buf = (char*)malloc(sz);
    strcpy(buf, str->data);
    strcat(buf, s);
    str->size = sz - 1;
    return;
}

/*  文字列を検索する。*/
int my_string_indexof(MyString* str, const char* s, int start) {

}

/* 文字列を検索する。 */
int my_string_last_indexof(MyString* str, const char* s, int start) {

}

/* 開始位置 start から終了位置 end までの部分文字列を得る。 */
MY_HEAP MyString* my_string_slice(MyString* str, int start, int end) {

}

/* 開始位置 start から長さ length の部分文字列を得る。 */
MY_HEAP MyString* my_string_substring(MyString* str, int start, int length) {

}

/* 文字列を分割する。 */
MY_HEAP char** my_string_split(MyString* str, char separator) {

}

/*  文字列を結合する。*/
MY_HEAP MyString* my_string_join(char** strarray, char separator) {

}

/* 文字列内に部分文字列を置換する。 */
MY_HEAP MyString* my_string_replace(MyString* str, char* target, char* repstr) {

}

/* 文字列の前後の空白文字を削除する。 */
MY_HEAP MyString* my_string_trim(MyString* str) {

}

/* 文字列の前の空白文字を削除する。 */
MY_HEAP MyString* my_string_trim_begin(MyString* str) {

}

/* 文字列の後の空白文字を削除する。 */
MY_HEAP MyString* my_string_trim_end(MyString* str, char c, size_t length) {

}

/* 文字列の前に指定した文字を追加して指定の長さの文字列にする。 */
MY_HEAP MyString* my_string_pad_left(MyString* str, char c, size_t length) {

}

/* 文字列の後に指定した文字を追加して指定の長さの文字列にする。 */
MY_HEAP MyString* my_string_pad_right(MyString* str) {

}

/* 文字列の最後が LF なら削除する。 */
MY_HEAP MyString* my_string_chomp(MyString* str) {

}

/* 文字列内の英小文字を大文字に変換する。 */
MY_HEAP MyString* my_string_toupper(MyString* str) {

}

/* 文字列内の英大文字を小文字に変換する。 */
MY_HEAP MyString* my_string_tolower(MyString* str) {

}

/* 文字列の開始が指定した文字列なら true を返す。 */
bool my_string_startswith(MyString* str, char* str) {

}

/* 文字列の終了が指定した文字列なら true を返す。 */
bool my_string_endswith(MyString* str, char* str) {

}
