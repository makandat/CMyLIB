/* my_collections.h */
#ifndef MY_COLLECTIONS_H
#define MY_COLLECTIONS_H
#include "my_object.h"

#define INDEX_CELLGROUP 1024

// foreach コールバック関数
typedef void (*Callback)(void*, size_t);

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
MY_HEAP const ListCell* my_list_first(ListRoot* root);  // ListRoot.current を先頭のセルにする。
MY_HEAP const ListCell* my_list_next(ListRoot* root);  // ListRoot.current を次のセルにする。
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
  struct tagIxListRoot* first;  // 先頭のセル
  struct tagIxListRoot* last;  // 最後のセル
  struct tagIndexList* index;  // インデックス
  int count;  // セルの数
} IxRoot;

/* インデックスリストのセル */
typedef struct tagIndexCell {
  int code;  // インデックスの値
  struct tagIxListCell* cell;  // セルへのポインタ
} IndexCell;

/* インデックスリスト */
typedef struct tagIndexList {
  struct tagIndexCell* indexes[INDEX_CELLGROUP];  // インデックスの配列
  struct tagIndexList* next;  // 次のインデックスリストへのポインタ
} IndexList;


/* 関数定義 */
MY_HEAP IxRoot* my_ixlist_new(); // リストを初期化する。
void my_ixlist_append(IxRoot*, IxCell*);  // リストにセルを追加する。
MY_HEAP IndexCell* my_ixlist_get_indexcell(IxRoot*, int);  // インデックスに対応するセルを得る。
int my_ixlist_get_count(IxRoot*);  // 要素の数を得る。
void my_ixlist_foreach(IxRoot*, Callback);  // リスト内のすべての要素（値）に関数を適用する。
void my_ixlist_free(IxRoot*);  // リストを解放する。
void my_ixlist_dump_indexes(IxRoot*);  // インデックスリストをダンプ表示する。

/*
    辞書
*/
#define DICT_ENTRY 4096

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
MY_HEAP DictEntry* my_dict_new();  // 辞書を作成する。
int my_gethash(const char* key);  // キーに対するハッシュ値を得る。
void my_set_dictcell(DictEntry* dict, const char* key, void* value, size_t size);  // キーに対する値を更新する。(キーが存在しないときは追加)
MY_HEAP DictEntry* my_get_hashentry(DictEntry* dict, const char* key);  // キーに対するエントリ―を得る。
MY_HEAP DictCell* my_dictcell_new(const char* key, void* value, size_t size);  // セルを作成する。
bool my_dictkey_exists(DictEntry* dict, const char* key);  // キーが存在するかチェックする。
MY_HEAP ListRoot* my_get_keys(DictEntry* dict);  // キー一覧を得る。
MY_HEAP DictCell* my_get_dictcell(DictEntry* entry, const char* key);  // 指定したキーのセルを得る。
void my_dict_free(DictEntry* dict, bool);  // 辞書のリソースを解放する。
void my_dict_removeitem(DictEntry* dict, const char* key);  // キーを削除する。
void my_dump_hashtable(DictEntry* hashtable, bool all);  // 辞書をダンプ表示する。

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
bool my_stack_pop(StackRoot* stack, void* pval);  // 値をポップする。(pval は呼び出し側で領域を確保する)
bool my_stack_peek(StackRoot* stack, void* pval); // スタックトップの値を読む。(ポップしない)
bool my_stack_empty(StackRoot* stack);  // スタックが空かどうかを返す。
void my_stack_free(StackRoot* stack);  // スタックのリソースを解放する。

/*
 *  Queue
 */
#define QueueRoot StackRoot
#define QueueCell BidiCell

/* キュー関数 */
MY_HEAP QueueRoot* my_queque_new();  // キューを作成する。
void my_queue_push(QueueRoot* queue, void* value, size_t size);  // 値をプッシュする。
void my_queue_deque(QueueRoot* queue, void* pval);  // 先頭を取り出す。
void my_queue_peek(QueueRoot* queue, void* pval);  // 先頭の値を読む。
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
MY_HEAP SetEntry* my_set_new();
int my_set_gethash(const char* item);
SetEntry* my_set_getentry(SetEntry* set, const char* item);
SetCell* my_set_cellnew(const char* item);
void my_set_setcell(SetEntry* set, const char* item);
bool my_set_exists(SetEntry* set, const char* item);
int my_get_items(SetEntry* set, char* items[], int leng);
void my_set_foreach(SetEntry* set, void(*callback)(const char* item));
SetCell* my_set_getcell(SetEntry* set, const char* item);

#endif
