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
void my_release_strarray(MyStringArray* strarray) {
    if (strarray->refcount > 0)
        strarray->refcount--;
    if (strarray->refcount == 0) {
        strarray->type = MY_EMPTY;
        strarray->size = 0;
        MyString* sp = strarray->first;
        MyString* sq;
        for (int i = 0; i < strarray->length; i++) {
            sq = sp->next;
            free(sp);
            sp = sq;
        }
        strarray->first = NULL;
        strarray->last = NULL;
        free(strarray);
    }
}

/* 文字列をラップしてMyStringオブジェクトを作成する。 */
MY_HEAP MyString* my_string_wrap(char* s) {
    MyString* ret = my_string_new();
    ret->size = strlen(s);
    ret->length = 1;
    ret->data = (char*)malloc(ret->size + 1);
    strcpy(ret->data, s);
    return ret;
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
    if (start >= strlen(str->data) - strlen(s))
        return -1;
    char* p = str->data + start;
    char* q = strstr(p, s);
    if (q == NULL)
        return -1;
    else
        return q - p;
}

/* 文字列が同じか判別する。 */
bool my_string_equal(MyString* str, const char* s) {
    if (strcmp(str->data, s) == 0)
        return true;
    else
        return false;
}

/* 文字列を比較する。 */
int my_string_compare(MyString* str, const char* s) {
    return strcmp(str->data, s);
}

/* 開始位置 start から終了位置 end までの部分文字列を得る。 */
MY_HEAP MyString* my_string_slice(MyString* str, int start, int end) {
    MyString* ret = my_string_new();
    ret->length = 1;
    int len = strlen(str->data);
    if (start > len) {
      // 開始位置が文字列長を超えている場合
      ret->data = (char*)calloc(1, sizeof(char));
    }
    else if (end > len) {
      // 最終位置が文字列長を超えている場合
      ret->data = (char*)calloc(len - start + 1, sizeof(char));
      strncpy(ret->data, str->data + start, len - start);
    }
    else if (start == end) {
      // start == end の場合
      ret->data = (char*)calloc(2, sizeof(char));
      ret->data[0] = str->data[start];
    }
    else {
      // ノーマル
      ret->data = (char*)calloc(end - start + 1, sizeof(char));
      strncpy(ret->data, str->data + start, end - start);
    }
    return ret;
}

/* 開始位置 start から長さ length の部分文字列を得る。 */
MY_HEAP MyString* my_string_substring(MyString* str, int start, int length) {
    MyString* ret = my_string_new();
    ret->length = 1;
    int len = strlen(str->data);
    if (len - start < length) {
      // 指定長が文字列の最後を超えている場合は元の文字列の start から最後までを返す。
      length = len - start;
      ret->data = (char*)calloc(length + 1, sizeof(char));
      strncpy(ret->data, str->data + start, length);
    }
    else if (start < 0) {
      // start が負の場合
      start = len - length;
      if (start <= 0) {
        // length が元の文字列長以上の場合は文字列全体を返す。
        ret->data = (char*)calloc(len + 1, sizeof(char));
        strcpy(ret->data, str->data);
      }
      else {
        ret->data = (char*)calloc(length + 1, sizeof(char));
        strncpy(ret->data, str->data + start, length);
      }
    }
    else {
      // その他の場合
      ret->data = (char*)calloc(length + 1, sizeof(char));
      strncpy(ret->data, str->data + start, length);
    }
    return ret;
}

/* 文字列を分割する。 */
MY_HEAP MyStringArray* my_string_split(MyString* str, char separator) {
    char* buf[1024];
    MyStringArray* ret = my_stringarray_new();
    char* p = str->data;
    ret->length = 0;
    while (strchr(p, separator) != NULL) {
        MyString* new = my_string_new();
        new->size = p - str->data;
        new->data = my_bytes_new(new->size + 1);
        memcpy(buf, str->data, new->size);
        if (ret->first == NULL) {
            ret->first = new;
            ret->last  = new;
            ret->first->next = ret->last;
        }
        else {
            ret->last = new;
        }
        ret->length++;
    }
    return ret;
}

/*  文字列を結合する。*/
MY_HEAP MyString* my_string_join(MyStringArray* strarray, char separator) {
    MyString* ret = my_string_new();
    size_t n = 0;
    MyString* p = strarray->first;
    while (p != NULL) {
        n += strlen(p->data);
        p = p->next;
    }
    ret->data = (char*)calloc(n + 1, sizeof(char));
    MyString* q = strarray->first;
    while (q != NULL) {
        strcat(ret->data, q->data);
        q = q->next;
    }
    ret->size = n;
    ret->length = 1;
    return ret;
}

/* 文字列内の部分文字列を置換する。 */
MY_HEAP MyString* my_string_replace(MyString* str, char* target, char* repstr) {
    static char zero = 0;
    char* buf;
    size_t sz;
    MyString* temp;
    MyString* ret = my_string_new();
    MyStringArray* strarray = my_stringarray_new();
    char* p = strstr(str->data, target);
    int i = 0;
    char* ptr[100];  // target が見つかった位置
    // ターゲットの位置を見つける。
    while (p != NULL) {
        ptr[i] = p;
        i++;
        p += strlen(target);
        // もうデータがないかチェックする。
        if (p > str->data - strlen(target))
          break;
    }
    // ターゲットの位置をもとにもとの文字列を分解する。
    int n = i;  // もとの文字列に含まれるターゲットに数
    for (int i = 0; i < n; i++) {
        // １個目の場合
        if (strarray->first == NULL) {
            if (ptr[0] == str->data) {
                // 元の文字列の先頭にターゲットが見つかった場合
                strarray->first = my_string_new();
                strarray->first->data = &zero;
                strarray->length = 1;
                strarray->last = strarray->first;
            }
            else { // 元の文字列の先頭以外でターゲットが見つかった場合
                sz = strlen(ptr[0]) + 1;
                buf = (char*)malloc(sz);
                strncpy(buf, str->data, sz - 1);
                strarray->first = my_string_new();
                strarray->first->data = buf;
                strarray->first->size = sz;
                strarray->last = strarray->first;
            }
            strarray->length = 1;  // 1 個見つかった
        }
        else {  // ２個目以降
            p = ptr[i - 1] + strlen(target);  // 中間文字列の位置
            sz = ptr[i] - p;  // 中間文字列の長さ
            buf = (char*)malloc(sz + 1);
            strncpy(buf, p, sz);
            temp = strarray->last;
            strarray->last = my_string_new();
            strarray->last->data = buf;
            temp->next = strarray->last;
            strarray->length++;
        }
        // 文字列のリストを結合して１つの文字列を作る。
        MyString* p1 = strarray->first;
        sz = 0;
        for (int i = 0; i < strarray->length; i++) {  // 結合後の文字列の長さを計算する。
            sz += strarray->length;
            sz += strlen(repstr);
        }
        // 結合後の文字列用バッファを用意する。
        buf = my_bytes_new(sz);
        p1 = strarray->first;
        // 部分文字列を置換文字列で結合する。
        for (int i = 0; i < strarray->length; i++) {
            strcat(buf, p1->data);
            if (i < strarray->length - 1)
              strcat(buf, repstr);
            p1 = p1->next;
        }
    }
    ret->size = strlen(ret->data) + 1;
    ret->data = buf;
    return ret;
}

/* 文字列の前後の空白文字を削除する。 */
MY_HEAP MyString* my_string_trim(MyString* str) {
    MyString* ret = my_string_new();
    ret->size = 0;
    ret->length = 1;
    int n2 = strlen(str->data);
    ret->data = my_bytes_new(n2 + 1);
    char* p = str->data;
    while (isblank(*p)) {
        p++;
    }
    char* q = str->data + n2 - 1;
    while (isblank(*q) || *q == '\n') {
        q--;
    }
    memcpy(ret->data, p, q - p);
    return ret;
}

/* 文字列の前の空白文字を削除する。 */
MY_HEAP MyString* my_string_trim_begin(MyString* str) {
    MyString* ret = my_string_new();
    ret->size = 0;
    ret->length = 1;
    int n2 = strlen(str->data);
    ret->data = my_bytes_new(n2 + 1);
    char* p = str->data;
    while (isblank(*p)) {
        p++;
    }
    strcpy(ret->data, p);
    return ret;
}

/* 文字列の後の空白文字を削除する。 */
MY_HEAP MyString* my_string_trim_end(MyString* str, char c, size_t len) {
    MyString* ret = my_string_new();
    ret->size = 0;
    ret->length = 1;
    int n2 = strlen(str->data);
    ret->data = my_bytes_new(n2 + 1);
    int n = strlen(str->data) - 1;
    char* p = str->data + n;
    int i = 0;
    while (i < n) {
        if (isblank(*p))
            i++;
        else
            break;
        p--;
    }
    strncpy(ret->data, str->data, n - i);
    return ret;
}

/* 文字列の前に指定した文字を追加して指定の長さの文字列にする。 */
MY_HEAP MyString* my_string_pad_left(MyString* str, char c, size_t len) {
    MyString* ret = my_string_new();
    ret->size = len;
    ret->length = str->length;
    ret->data = (char*)malloc(len + 1);
    int n = len - strlen(str->data);
    int i = 0;
    while (i < n) {
        *(ret->data + i) = c;
        i++;
    }
    strcat(ret->data + n, str->data);
    return ret;
}

/* 文字列の後に指定した文字を追加して指定の長さの文字列にする。 */
MY_HEAP MyString* my_string_pad_right(MyString* str, char c, size_t len) {
    MyString* ret = my_string_new();
    ret->size = len;
    ret->length = str->length;
    ret->data = (char*)malloc(len + 1);
    strcpy(ret->data, str->data);
    int i = strlen(ret->data);
    while (i < len) {
        *(ret->data + i) = c;
        i++;
    }
    return ret;
}

/* 文字列の最後が LF なら削除する。 */
MY_HEAP MyString* my_string_chomp(MyString* str) {
    MyString* ret = my_string_new();
    ret->size = str->size;
    ret->length = str->length;
    ret->data = (char*)malloc(ret->size + 1);
    strcpy(ret->data, str->data);
    char* p = ret->data + strlen(ret->data - 1);
    if (*p == '\n')
        *p = 0;
    return ret;
}

/* 文字列内の英小文字を大文字に変換する。 */
MY_HEAP MyString* my_string_toupper(MyString* str) {
    if (str->data == NULL)
        return NULL;
    MyString* ret = my_string_new();
    ret->size = str->size;
    ret->length = str->length;
    ret->data = (char*)malloc(ret->size + 1);
    char* p = str->data;
    char *q = ret->data;
    while (*p != 0) {
        if (*p >= 'a' && *p <= 'z')
            *q = *p - (int)'a' + (int)'A';
        else
            *q = *p;
        p++;
        q++;
    }
    *q = 0;
    return ret;
}

/* 文字列内の英大文字を小文字に変換する。 */
MY_HEAP MyString* my_string_tolower(MyString* str) {
    if (str->data == NULL)
        return NULL;
    MyString* ret = my_string_new();
    ret->size = str->size;
    ret->length = str->length;
    ret->data = (char*)malloc(ret->size + 1);
    char* p = str->data;
    char *q = ret->data;
    while (*p != 0) {
        if (*p >= 'A' && *p <= 'Z')
            *q = *p + (int)'a' - (int)'A';
        else
            *q = *p;
        p++;
        q++;
    }
    *q = 0;
    return ret;
}

/* 文字列の開始が指定した文字列なら true を返す。 */
bool my_string_startswith(MyString* str, char* s) {
    char* p = strstr(str->data, s);
    if (p == str->data)
        return true;
    else
        return false;
}

/* 文字列の終了が指定した文字列なら true を返す。 */
bool my_string_endswith(MyString* str, char* s) {
    int n = strlen(s);
    char* p = strstr(str->data, s);
    if (p == str->data - n)
        return true;
    else
        return false;
}

/* 文字列オブジェクトを作成する。 */
MY_HEAP MyString* my_string_new() {
    MyString* ret = (MyString*)malloc(sizeof(MyString));
    ret->refcount = 1;
    ret->type = MY_STRING_OBJECT;
    ret->size = 0;
    ret->length = 1;
    ret->data = NULL;
    return ret;
}

/* 文字列配列を作成する。 */
MY_HEAP MyStringArray* my_stringarray_new() {
    MyStringArray* ret = (MyStringArray*)malloc(sizeof(MyStringArray));
    ret->refcount = 1;
    ret->type = MY_STRING_ARRAY;
    ret->size = 0;
    ret->length = 0;
    ret->first = NULL;
    ret->last  = NULL;
    return ret;
}

/* 文字列配列オブジェクトに文字列オブジェクトを追加する。*/
void my_stringarray_append(MyStringArray* array, MyString* str) {
    MyString* str2 = my_string_dup(str);
    str2->next = NULL;
    if (array->length == 0) {
        array->first = str2;
        array->last = str2;
        array->length = 1;
    }
    else {
        array->last->next = str2;
        array->last = str2;
        array->length += 1;
    }
}

/* 文字列配列オブジェクトに文字列を追加する。 */
void my_stringarray_append2(MyStringArray* array, char* s) {
    MY_HEAP MyString* str = my_string_wrap(s);
    my_stringarray_append(array, str);
}


/* n 個の文字からなる文字列を指定されたバッファにコピーする。 */
void my_string_times(char* buf, char c, size_t n) {
    char* p = buf;
    for (int i = 0; i < n; i++) {
        *p++ = c;
    }
    *p = 0;
}

// 0 クリアされたバイトバッファを作成する。
MY_HEAP inline char* my_bytes_new(int size) {
    return (char*)calloc(size + 1, 1);
}

/* 文字列オブジェクトを表示する。 */
void my_string_print(MyString* str) {
    printf("refcount=%d; type=%d; size=%d; length=%lu; data='%s'\n", str->refcount, str->type, str->size, str->length, str->data == NULL ? "" : str->data);
}

/* 文字列配列オブジェクトを表示する。 */
void my_stringarray_print(MyStringArray* array) {
    printf("refcount=%d; type=%d; size=%d; length=%lu\n", array->refcount, array->type, array->size, array->length);
    MyString* p = array->first;
    for (int i = 0; i < array->length; i++) {
        printf("\t%d: '%s'\n", i, p->data);
        p = p->next;
    }
}
