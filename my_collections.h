/* my_collections.h v1.1 */
#ifndef MY_COLLECTIONS_H
#define MY_COLLECTIONS_H
#include "my_object.h"

#define INDEX_CELLGROUP 1024
#define DICT_ENTRY 4096

// foreach コールバック関数
typedef void (*Callback)(void* payload, size_t plsize);
// 辞書のコールバック関数
typedef void (*EachPair)(char* key, void* value, size_t sz);

/*
  単純な一方向リスト
*/
/* セルの定義 */
typedef struct tagListCell {
  struct tagListCell* next;  // 次のセル
  void* payload;  // ペイロード（値）
  size_t size;  // ペイロードのバイト数
} ListCell;

/* ルートの定義 */
typedef struct tagListRoot {
  struct tagListCell* current;  // 現在のセル (list_first(), list_next() で使う。)
  struct tagListCell* first;  // 先頭のセル
  struct tagListCell* last;  // 最後のセル
  int count;  // セルの数
} ListRoot;

/* 関数のプロトタイプ */
MY_HEAP ListRoot* my_list_new();  // ListRoot を初期化する。
void my_list_free(ListRoot*); // すべてのリソースを解放する。
const ListCell* my_list_first(ListRoot* root);  // ListRoot.current を先頭のセルにする。
const ListCell* my_list_next(ListRoot* root);  // ListRoot.current を次のセルにする。
void my_list_append(ListRoot* root, void* value, size_t size);  // ペイロードを追加する。
void my_list_value(ListRoot* root, void* pval);  // 現在の値を得る。(pvalの領域は呼び出し側で用意すること)
void my_list_foreach(ListRoot*, Callback); // コールバック関数にリストのすべての要素を適用する。

/*
 インデックス付きリスト
*/
/* セルの定義 */
typedef struct tagIxListCell {
  struct tagIxListCell* next;  // 次のセル
  void* payload;  // ペイロード（値）
  size_t size;  // ペイロードのバイト数
} IxCell;

/* ルートの定義 */
typedef struct tagIxListRoot {
  IxCell* first;  // 先頭のセル
  IxCell* last;  // 最後のセル
  IxCell* current;  // 現在のセル
  struct tagIndexList* index;  // インデックス
  int count;  // セルの数
} IxRoot;

/* インデックスリストのセル */
typedef struct tagIndexCell {
  int code;  // インデックスの値
  IxCell* cell;  // セルへのポインタ
} IndexCell;

/* インデックスリスト */
typedef struct tagIndexList {
  IndexCell* indexes[INDEX_CELLGROUP];  // インデックスの配列
  struct tagIndexList* next;  // 次のインデックスリストへのポインタ
} IndexList;


/* 関数定義 */
MY_HEAP IxRoot* my_ixlist_new(); // リストを初期化する。
void my_ixlist_setval(IxRoot* root, void* value, size_t size);  // リストにペイロードを追加する。
void my_ixlist_append(IxRoot*, IxCell*);  // リストにセルを追加する。
void* my_ixlist_getval(IxRoot*, int);  // インデックスに対応するペイロードを得る。
size_t my_ixlist_getsize(IxRoot*, int);  // インデックスに対応するペイロードのサイズ得る。v1.1
IndexCell* my_ixlist_get_indexcell(IxRoot*, int);  // インデックスに対応するセルを得る。
IxCell* my_ixlist_first(IxRoot* list);  // リストセルの先頭を返す。
IxCell* my_ixlist_next(IxRoot* list);  // 次のリストセルを返す。
int my_ixlist_count(IxRoot*);  // 要素の数を得る。
void my_ixlist_foreach(IxRoot*, Callback);  // リスト内のすべての要素（値）に関数を適用する。
void my_ixlist_free(IxRoot*);  // リストを解放する。
void my_ixlist_dump_indexes(IxRoot*);  // インデックスリストをダンプ表示する。

/*
    辞書
*/

/* セル */
typedef struct tagDictCell {
  struct tagDictCell* next;  // 次のセルへのポインタ
  char* key;  // キー
  void* payload; // ペイロード
  size_t size;  // ペイロードのバイト数
} DictCell;

/* ハッシュテーブル */
typedef struct tagDictEntry {
  struct tagDictCell* first;  // 辞書の先頭
  int count;  // 要素の数
} DictEntry;

/* 関数のプロトタイプ */
MY_HEAP DictEntry** my_dict_new();  // 辞書を作成する。
int my_gethash(const char* key);  // キーに対するハッシュ値を得る。
MY_HEAP DictEntry* my_getentry(DictEntry** dict, const char* key);  // キーに対するエントリ―を得る。
MY_HEAP DictCell* my_dictcell_new(const char* key, void* value, size_t size);  // セルを作成する。
bool my_dictkey_exists(DictEntry** dict, const char* key);  // キーが存在するかチェックする。
MY_HEAP ListRoot* my_get_keys(DictEntry** dict);  // キー一覧を得る。
void my_dict_foreach(DictEntry** dict, EachPair f);  // 辞書のすべてのキー値ペアに対して関数を適用する。
MY_HEAP DictCell* my_get_dictcell(DictEntry** entry, const char* key);  // 指定したキーのセルを得る。
void my_dict_setval(DictEntry** dict, const char* key, void* value, size_t size);  // キーに対する値を更新する。(キーが存在しないときは追加)
void* my_dict_getval(DictEntry** dict, const char* key);  // キーに対する値を得る。
size_t my_dict_getsize(DictEntry** dict, const char* key);  // 指定したキーに対するペイロードのサイズを得る。
void my_dict_free(DictEntry** dict, bool);  // 辞書のリソースを解放する。
void my_dict_remove(DictEntry** dict, const char* key);  // キーを削除する。
void my_dump_hashtable(DictEntry** dict, bool all);  // 辞書をダンプ表示する。

/*
 *   Stack
 */
/* セルの定義 */
typedef struct tagBidiCell {
  struct tagListCell* next;  // 次のセル
  struct tagListCell* prev;  // 前のセル
  void* payload;  // ペイロード（値）
  size_t size;  // ペイロードのバイト数
} BidiCell;

#define StackCell BidiCell

/* ルートの定義 */
typedef struct tagStackRoot {
  int count;  // セルの数
  struct tagBidiCell* current;  // 現在のセル
  struct tagBidiCell* first;  // 先頭のセル
  struct tagBidiCell* last;  // 最後のセル
} StackRoot;

/* スタック関数 */
MY_HEAP StackRoot* my_stack_new();  // スタックを作成する。
void my_stack_push(StackRoot* stack, void* value, size_t size);  // 値をプッシュする。
bool my_stack_pop(StackRoot* stack, void* pval, size_t* np);  // 値をポップする。(pval は呼び出し側で領域を確保する)
bool my_stack_peek(StackRoot* stack, void* pval, size_t* np); // スタックトップの値を読む。(ポップしない)
bool my_stack_empty(StackRoot* stack);  // スタックが空かどうかを返す。
void my_stack_free(StackRoot* stack);  // スタックのリソースを解放する。
void my_stack_first(StackRoot* stack, void* pval, size_t* np);  // 最初の要素 (bottom) へ移動 v1.1
void my_stack_last(StackRoot* stack, void* pval, size_t* np);  // 最後の要素 (top) へ移動 v1.1
bool my_stack_next(StackRoot* stack, void* pval, size_t* np);  // 次の要素へ移動 v1.1
bool my_stack_prev(StackRoot* stack, void* pval, size_t* np);  // 前の要素へ移動 v1.1

/*
 *  Queue
 */
#define QueueRoot StackRoot
#define QueueCell BidiCell

/* キュー関数 */
MY_HEAP QueueRoot* my_queue_new();  // キューを作成する。
void my_queue_push(QueueRoot* queue, void* value, size_t size);  // 値をプッシュする。
bool my_queue_deque(QueueRoot* queue, void* pval, size_t* np);  // 先頭を取り出す。
void my_queue_peek(QueueRoot* queue, void* pval, size_t* np);  // 先頭の値を読む。
bool my_queue_empty(QueueRoot* queue);  // キューが空かどうかを返す。
void my_queue_free(QueueRoot* queue);  // キューのリソースを解放する。

/*
 *  Set
*/
#define SET_ENTRY 256

/* セル */
typedef struct tagSetCell {
  struct tagSetCell* next;
  char* item;
} SetCell;

/* ハッシュテーブル */
typedef struct tagSetEntry {
  struct tagSetCell* first;
  int count;
} SetEntry;

/* 関数のプロトタイプ */
MY_HEAP SetEntry** my_set_new();// 空のセットを作成する。
MY_HEAP SetCell* my_set_cellnew(const char* item); // 空のセルを作成する。
void my_set_setitem(SetEntry** set, const char* item); // 要素をセットに追加する。
bool my_set_exists(SetEntry** set, const char* item); // 要素がすでにセットに含まれているか判別する。
MY_HEAP ListRoot* my_get_items(SetEntry** set); // セットの要素一覧をリストとして取得する。
void my_set_foreach(SetEntry** set, void(*callback)(const char* item)); // セットのすべての要素に対してコールバック関数を適用する。
SetCell* my_set_getcell(SetEntry** set, const char* item); // 指定した要素のセルを得る。
bool my_set_empty(SetEntry** set);// セットが空か判別する。
int my_set_count(SetEntry** set);// セットに含まれる要素数を得る。
void my_set_remove(SetEntry** set, const char* item); // セットから要素を削除する。

#endif
