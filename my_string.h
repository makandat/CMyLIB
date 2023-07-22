/* my_string.h */
#ifndef MY_STRING_H
#define MY_STRING_H
#include "my_object.h"
#include <ctype.h>

/* 文字列オブジェクト */
typedef struct tagString {
    int32_t refcount;  // 参照カウント
    int32_t type;      // データの型
    int32_t size;      // 文字列の長さ (バイト数、終端文字は含まず)
    size_t length;     // 長さ (配列の場合の要素数、配列でない場合は 1)
    char* data;        // 文字列へのポインタ (NULL ならデータが未定義)
    struct tagString* next;  // 次の文字列オブジェクトへのポインタ
} MyString;

/* 文字列配列オブジェクト */
typedef struct tagStringArray {
    int32_t refcount;  // 参照カウント
    int32_t type;      // データの型
    int32_t size;      // 使用しない。(常に 0)
    size_t length;     // リストの長さ
    struct tagString* first;  // 文字列リストの先頭へのポインタ (NULL ならデータが未定義)
    struct tagString* last;   // 文字列リストの最後へのポインタ (NULL ならデータが未定義)
} MyStringArray;


void my_addref_str(MyString*); // MyString オブジェクトの参照カウントを増やす。
void my_addref_strarray(MyStringArray*); // MyStringArray オブジェクトの参照カウントを増やす。
void my_release_str(MyString*); // MyString オブジェクトの参照カウントを減らす。
void my_release_strarray(MyStringArray*); // MyStringArray オブジェクトの参照カウントを減らす。
MY_HEAP MyString* my_string_wrap(char* str); // 文字列をラップしてMyStringオブジェクトを作成する。
const char* my_string_get(MyString* str); // 内部の文字列 (char*) を返す。
void my_string_set(MyString* str, const char* s);  // 内部の文字列を更新する。
MY_HEAP MyString* my_string_dup(MyString* str);  // 文字列オブジェクトを複製する。
void my_string_append(MyString* str, const char* s);  // 文字列を追加する。
int my_string_indexof(MyString* str, const char* s, int start);  // 文字列を検索する。
bool my_string_equal(MyString* str, const char* s);  // 文字列が同じか判別する。
int my_string_compare(MyString* str, const char* s);  // 文字列を比較する。
MY_HEAP MyString* my_string_slice(MyString* str, int start, int end);  // 開始位置 start から終了位置 end までの部分文字列を得る。
MY_HEAP MyString* my_string_substring(MyString* str, int start, int length);  // 開始位置 start から長さ length の部分文字列を得る。
MY_HEAP MyStringArray* my_string_split(MyString* str, char separator);  // 文字列を分割する。
MY_HEAP MyString* my_string_join(MyStringArray* strarray, char separator);  // 文字列を結合する。
MY_HEAP MyString* my_string_replace(MyString* str, char* target, char* repstr);  // 文字列内の部分文字列を置換する。
MY_HEAP MyString* my_string_trim(MyString* str);  // 文字列の前後の空白文字を削除する。
MY_HEAP MyString* my_string_trim_begin(MyString* str);  // 文字列の前の空白文字を削除する。
MY_HEAP MyString* my_string_trim_end(MyString* str);  // 文字列の後の空白文字を削除する。
MY_HEAP MyString* my_string_pad_left(MyString* str, char c, size_t len);  // 文字列の前に指定した文字を追加して指定の長さの文字列にする。
MY_HEAP MyString* my_string_pad_right(MyString* str, char c, size_t len);  // 文字列の後に指定した文字を追加して指定の長さの文字列にする。
MY_HEAP MyString* my_string_chomp(MyString* str);  // 文字列の最後が LF なら削除する。
MY_HEAP MyString* my_string_strip(MyString* str, char paren);  // カッコで囲まれた文字列の中身を取り出す。
MY_HEAP MyString* my_string_toupper(MyString* str); // 文字列内の英小文字を大文字に変換する。
MY_HEAP MyString* my_string_tolower(MyString* str); // 文字列内の英大文字を小文字に変換する。
bool my_string_startswith(MyString* str, char* s); // 文字列の開始が指定した文字列なら true を返す。
bool my_string_endswith(MyString* str, char* s); // 文字列の終了が指定した文字列なら true を返す。
MY_HEAP MyString* my_string_new();  // 文字列オブジェクトを作成する。
MY_HEAP MyStringArray* my_stringarray_new();  // 文字列配列を作成する。
void my_stringarray_append(MyStringArray* array, MyString* str);  // 文字列配列オブジェクトに文字列オブジェクトを追加する。
void my_stringarray_append2(MyStringArray* array, char* s);  // 文字列配列オブジェクトに文字列を追加する。
MY_HEAP char* my_stringarray_tostr(MyStringArray* array, char* c);  // 文字列配列オブジェクトの要素を結合した C 文字列を返す。
MY_HEAP char* my_bytes_new(int size);  // 0 クリアされたバイトバッファを作成する。
void my_string_times(char* buf, char c, size_t n); // n 個の文字からなる文字列を指定されたバッファにコピーする。
void my_string_print(MyString* str);  // 文字列オブジェクトを表示する。
void my_stringarray_print(MyStringArray* array);  // 文字列配列オブジェクトを表示する。
char *strrstr(char *haystack, char *needle);  // strstr()関数の後ろから検索バージョン

#endif
