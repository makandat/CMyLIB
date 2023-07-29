/* my_collections.c */
#include "my_collections.h"
#include <stdbool.h>
#pragma GCC diagnostic ignored "-Wincompatible-pointer-types"
#pragma GCC diagnostic ignored "-Wint-conversion"

/*
  単純な一方向リスト
*/

/* ListRoot を作成する。*/
MY_HEAP ListRoot* my_list_new() {
    ListRoot* root = (ListRoot*)malloc(sizeof(ListRoot));
    root->count = 0;
    root->current = NULL;
    root->first = NULL;
    root->last = NULL;
    return root;
}

/* リストのすべてのリソースを解放する。*/
void my_list_free(ListRoot* list) {
    ListCell* p = list->first;
    ListCell* q = NULL;
    while (p != NULL) {
        free(p->payload);
        q = p;
        p = p->next;
        free(q);
    }
    free(list);
    return;
}

/* ListRoot.current を先頭のセルにする。 */
const ListCell* my_list_first(ListRoot* list) {
    list->current = list->first;
    return list->current;
}

/* ListRoot.current を次のセルにする。 */
const ListCell* my_list_next(ListRoot* list) {
    if (list->current == NULL)
        return NULL;
    ListCell* cell = list->current;
    list->current = cell->next;
    return list->current;
}

/* ペイロードを追加する。 */
void my_list_append(ListRoot* list, void* value, size_t size) {
    ListCell* new = (ListCell*)malloc(sizeof(ListCell));
    new->payload = malloc(size);
    new->size = size;
    memcpy(new->payload, value, size);
    new->next = NULL;
    if (list->count == 0) {
        list->first = new;
        list->last = new;
        list->current = new;
    }
    else {
        ListCell* p = list->last;
        list->last = new;
        p->next = new;
    }
    list->count++;
    return;
}

/* 現在の値を得る。(pvalの領域は呼び出し側で用意すること) */
void my_list_value(ListRoot* list, void* pval) {
    memcpy(pval, list->current->payload, list->current->size);
    return;
}

/* コールバック関数にリストのすべての要素を適用する。 */
void my_list_foreach(ListRoot* list, Callback func) {
    ListCell* p = list->first;
    while (p != NULL) {
        func(p->payload, p->size);
        p = p->next;
    }
}


/*
 インデックス付きリスト
*/

/* リストを初期化する。 */
MY_HEAP IxRoot* my_ixlist_new() {
    IxRoot* root = (IxRoot*)malloc(sizeof(IxRoot));
    root->first = NULL;
    root->last = NULL;
    root->index = 0;
    root->count = 0;
    return root;
}

/* リストにペイロードを追加する。*/
void my_ixlist_setval(IxRoot* root, void* value, size_t size) {
    IxCell* cell = (IxCell*)malloc(sizeof(IxCell));
    cell->payload = malloc(size);
    memcpy(cell->payload, value, size);
    cell->size = size;
    my_ixlist_append(root, cell);
}

/* リストにセルを追加する。 */
void my_ixlist_append(IxRoot* root, IxCell* cell) {
  if (root->count == 0) {
    // 何も要素がないとき
    IndexList* ixlist = (IndexList*)malloc(sizeof(IndexList));
    if (ixlist == NULL)
      return;
    for (int j = 0; j < INDEX_CELLGROUP; j++) {
      ixlist->indexes[j] = NULL;
    }
    ixlist->next = NULL;
    root->index = ixlist;
    root->first = cell;
    root->last = cell;
    root->count = 1;
    ixlist->indexes[0] = (IndexCell*)malloc(sizeof(IndexCell));
    if (ixlist->indexes[0] == NULL)
      return;
    ixlist->indexes[0]->cell = cell;
    ixlist->indexes[0]->code = 0;
  }
  else {
    // すでに要素があるとき
    int indexof = root->count % INDEX_CELLGROUP; // インデックスグループ内の位置
    int indexn = (int)(root->count / INDEX_CELLGROUP) + 1;  // インデックスグループ番号
    // 最後のセルの後にパラメータで指定されたセルを追加する。
    IxCell* p = root->last;
    p->next = cell;
    root->last = cell;
    // インデックスリストの最後のグループを決める。
    IndexList* ix = root->index;
    for (int i = 0; i < (indexn - 1); i++) {
      ix = ix->next;
    }
    // インデックスグループの内の最後の位置
    // 最後のセルかチェックする。
    if (indexof == INDEX_CELLGROUP - 1 && ix->indexes[0] != NULL) {
      // グループ内で最後のインデックスセルの場合
      // リストセルをそのインデックスセルにリンクする。
      ix->indexes[indexof] = (IndexCell*)malloc(sizeof(IndexCell));
      if (ix->indexes[indexof] == NULL)
        return;
      ix->indexes[indexof]->cell = cell;
      ix->indexes[indexof]->code = root->count;
      root->count++;
      // 次のインデックスグループを作成して現在のリストグループにリンクする。
      IndexList* ixlist = (IndexList*)malloc(sizeof(IndexList));
      if (ixlist == NULL)
        return;
      for (int j = 0; j < INDEX_CELLGROUP; j++) {
        ixlist->indexes[j] = NULL;
      }
      ixlist->next = NULL;
      ix->next = ixlist;  // 今までのインデックスグループの next にリンクする。
    }
    else {
      // 最後のセル以外ならリストセルをリンクする。
      ix->indexes[indexof] = (IndexCell*)malloc(sizeof(IndexCell));
      if (ix->indexes[indexof] == NULL)
        return;
      ix->indexes[indexof]->cell = cell;
      ix->indexes[indexof]->code = root->count;
      root->count++;
    }
  }
}


/* インデックスに対応するセルを得る。 */
IndexCell* my_ixlist_get_indexcell(IxRoot* list, int idx) {
    int indexof = idx % INDEX_CELLGROUP; // インデックスグループ内の位置
    int indexn = (int)(idx / INDEX_CELLGROUP);  // インデックスグループ番号
    // インデックスグループへのポインタを得る。
    IndexList* pidx = list->index;
    for (int i = 0; i < indexn; i++) {
        pidx = pidx->next;
    }
    // インデックスグループでの目的位置のインデックスオフセットを得る。
    IndexCell* ixc = pidx->indexes[indexof];
    return ixc;
}

/* インデックスに対応するペイロードを得る。 */
void* my_ixlist_getval(IxRoot* list, int idx) {
    IndexCell* ixcell = my_ixlist_get_indexcell(list, idx);
    return ixcell->cell->payload;
}

/* リストセルの先頭を返す。*/
IxCell* my_ixlist_first(IxRoot* list) {
    list->current = list->first;
    return list->current;
}

/* 次のリストセルを返す。*/
IxCell* my_ixlist_next(IxRoot* list) {
    list->current = list->current->next;
    return list->current;
}

/* 要素の数を得る。*/
int my_ixlist_count(IxRoot* list) {
    return list->count;
}


/* リスト内のすべての要素（値）に関数を適用する。 */
void my_ixlist_foreach(IxRoot* list, Callback func) {
    IxCell* p = list->first;
    while (p != NULL) {
        func(p->payload, p->size);
        p = p->next;
    }
}

/* リストを解放する。 */
void my_ixlist_free(IxRoot* list) {

}

/* インデックスリストをダンプ表示する。 */
void my_ixlist_dump_indexes(IxRoot* root) {
  if (root->index == NULL) {
    puts("Error: root->index = NULL");
    return;
  }
  if (root->count == 0) {
    puts("Error: root->count = 0");
    return;
  }

  IndexList* ixlist = root->index;

  for (int i = 0; i < root->count; i++) {
    printf("l=%d index[%d]\n", i, ixlist->indexes[i % INDEX_CELLGROUP]->code);
    if ((i + 1) % INDEX_CELLGROUP == 0) {
      ixlist = ixlist->next;
    }
  }
}


/*
    辞書
*/

/* 辞書のを作成する。 */
MY_HEAP DictEntry** my_dict_new() {
    DictEntry** dict = malloc(sizeof(void*) * DICT_ENTRY);
    for (int i = 0; i < DICT_ENTRY; i++) {
        dict[i] = (DictEntry*)malloc(sizeof(DictEntry));
        memset(dict[i], 0, sizeof(DictEntry));
    }
    return dict;
}

/* キーに対するハッシュ値を得る。 */
int my_gethash(const char* key) {
  const char* p = key;
  int sum = 0;
  int mask = 0xff;
  while (*p != 0) {
    sum += (int)*p;
    sum &= mask;
    p++;
  }
  return sum;
}

/* キーに対する値を更新する。 */
void my_dict_setval(DictEntry** dict, const char* key, void* value, size_t size) {
  DictEntry* entry = my_getentry(dict, key);
  if (entry->first == NULL) {
    // セルがないので追加
    DictCell* cell = my_dictcell_new(key, value, size);
    entry->first = cell;
    entry->count = 1;
  }
  else {
    // 同じキーのセルがあるか
    if (my_dictkey_exists(dict, key)) {
      // 同じキーのセルがある場合はセル上書き
      DictCell* cell = my_get_dictcell(dict, key);
      // そのセルを上書きする。
      memcpy(cell->payload, value, size);
      cell->size = size;
    }
    else {
      // 同じキーのセルがない場合はセル追加
      DictCell* p = entry->first;
      while (p->next != NULL) {
        // 終端のセルまで繰り返す。
        p = p->next;
      }
      // 新しいセルを追加する。
      DictCell* cell = my_dictcell_new(key, value, size);
      p->next = cell;
      entry->count++;
    }
  }
}

/* キーに対するエントリ―を得る。 */
MY_HEAP DictEntry* my_getentry(DictEntry** dict, const char* key) {
    int hash = my_gethash(key);
    return dict[hash];
}

/* セルを作成する。 */
MY_HEAP DictCell* my_dictcell_new(const char* key, void* value, size_t size) {
    DictCell* cell = (DictCell*)malloc(sizeof(DictCell));
    if (cell == NULL)
        return NULL;
    int keyleng = (int)strlen(key) + 1;
    cell->key = (char*)malloc(keyleng);
    if (cell->key == NULL)
      return NULL;
    strcpy(cell->key, key);
    cell->payload = value;
    cell->size = size;
    cell->next = NULL;
    return cell;
}

/* キーが存在するかチェックする。 */
bool my_dictkey_exists(DictEntry* dict[], const char* key) {
    int hash = my_gethash(key);
    if (dict[hash]->count > 0) {
        if (strcmp(dict[hash]->first->key, key) == 0)
          return true;
        else {
           DictCell* p = dict[hash]->first->next;
           while (p != NULL) {
              if (strcmp(p->key, key) == 0)
                return true;
              else
                p = p->next;
          }
          return false;
        }
    }
    else
        return false;
}

/* キー一覧を得る。 */
MY_HEAP ListRoot* my_get_keys(DictEntry** dict) {
  ListRoot* keys = my_list_new();
  DictCell* cell = NULL;
  for (int i = 0; i < DICT_ENTRY; i++) {
    DictEntry* entry = dict[i];
    for (int i = 0; i < entry->count; i++) {
      if (i == 0) {
        cell = entry->first;
      }
      else {
        if (cell != NULL)
          cell = cell->next;
      }
      my_list_append(keys, cell->key, strlen(cell->key) + 1);
    }
  }
  return keys;
}

/* コールバック関数に辞書の全キー値ペアを適用する。 */
void my_dict_foreach(DictEntry** dict, EachPair func) {
    for (int i = 0; i < DICT_ENTRY; i++) {
        if (dict[i] == NULL)
            continue; 
        if (dict[i]->count == 1) {
            func(dict[i]->first->key, dict[i]->first->payload, dict[i]->first->size);
        }
        else {
            DictCell* cell = dict[i]->first;
            while (cell != NULL) {
                 func(cell->key, cell->payload, cell->size);
                 cell = cell->next;
            }
        }
    }
}

/* 指定したキーのセルを得る。 */
MY_HEAP DictCell* my_get_dictcell(DictEntry** dict, const char* key) {
    DictCell* cell = NULL;
    int hash = my_gethash(key);
    if (dict[hash]->count == 0)
        return NULL;
    else if (dict[hash]->count == 1)
        return dict[hash]->first;
    else {
        cell = dict[hash]->first;
        while (cell->next != NULL) {
            if (strcmp(cell->key, key) == 0) {
                return cell;
            }
            cell = cell->next;
        }
        return NULL;
    }
    return cell;
}

/* 指定したキーに対する値を得る。 */
void* my_dict_getval(DictEntry** dict, const char* key) {
    DictCell* cell = my_get_dictcell(dict, key);
    if (cell == NULL)
        return NULL;
    return cell->payload;
}

/* 指定したキーに対するサイズを得る。 */
size_t my_dict_getsize(DictEntry** dict, const char* key) {
    DictCell* cell = my_get_dictcell(dict, key);
    return cell->size;
}

/* 辞書のリソースを解放する。 */
void my_dict_free(DictEntry** dict, bool b) {

}

/* キーを削除する。 */
void my_dict_remove(DictEntry** dict, const char* key) {
  DictEntry* entry = my_getentry(dict, key);
  if (entry->count == 0) {
    // キーに対するデータが存在しない場合
    return;
  }
  if (entry->count == 1) {
    // エントリに対しセルが1つだけの場合
    free(entry->first->payload);
    entry->count = 0;
    entry->first = NULL;
  }
  else {
    // エントリに対しセルが2つ以上の場合
    DictCell* cell = entry->first;
    DictCell* prev = NULL;
    while (true) {
      if (strcmp(cell->key, key) == 0) {
        if (prev == NULL) {
          // エントリ最初のセルの場合
          entry->first = cell->next;
          entry->count--;
          //free(cell->value);
        }
        else {
          // エントリ途中または最後のセルの場合
          prev->next = cell->next;
          entry->count--;
          //free(cell->value);
        }
        break;
      }
      else if (cell->next == NULL) {
        break;
      }
      else {
        prev = cell;
        cell = cell->next;
      }
    }
  }
}

/* 辞書をダンプ表示する。 */
void my_dump_hashtable(DictEntry** hashtable, bool all) {
  DictCell* cell = NULL;
  for (int i = 0; i < DICT_ENTRY; i++) {
    DictEntry* entry = hashtable[i];
    if (entry->count > 0) {
      printf("Entry[%d] .count = %d\n", i, entry->count);
      for (int i = 0; i < entry->count; i++) {
        if (i == 0) {
          cell = entry->first;
        }
        else {
          if (cell != NULL)
            cell = cell->next;
        }
      }
    }
    else {
      if (all) {
        printf("Entry[%d] NULL¥n", i);
      }
    }
  }
}

/*
 *   スタック
 */
/* スタックを作成する。 */
MY_HEAP StackRoot* my_stack_new() {
    StackRoot* new = (StackRoot*)malloc(sizeof(StackRoot));
    new->count = 0;
    new->first = NULL;
    new->last = NULL;
    new->current = NULL;
    return new;
}

/* 値をプッシュする。 */
void my_stack_push(StackRoot* stack, void* value, size_t size) {
    StackCell* cell = (StackCell*)malloc(sizeof(StackCell));
    cell->payload = malloc(size);
    memcpy(cell->payload, value, size);
    cell->size = size;
    if (stack->count == 0) {
        stack->first = cell;
        stack->last = cell;
        cell->next = NULL;
        cell->prev = NULL;
    }
    else {
        StackCell* p = stack->last;
        stack->last = cell;
        p->next = cell;
        cell->next = NULL;
        cell->prev = p;
    }
    stack->count++;
}

/* 値をポップする。(pval は呼び出し側で領域を確保する) */
bool my_stack_pop(StackRoot* stack, void* pval) {
    if (stack->count == 0)
        return false;
    memcpy(pval, stack->last->payload, stack->last->size);
    StackCell* last = stack->last;
    stack->last = stack->last->prev;
    stack->last->next = NULL;
    free(last->payload);
    free(last);
    return true;
}

/* スタックトップの値を読む。(ポップしない) */
bool my_stack_peek(StackRoot* stack, void* pval) {
    if (stack->count == 0)
        return false;
    memcpy(pval, stack->last->payload, stack->last->size);
    return true;
}

/* スタックが空かどうかを返す。 */
bool my_stack_empty(StackRoot* stack) {
    return stack->count == 0 ? true : false;
}

/* スタックのリソースを解放する。*/
void my_stack_free(StackRoot* stack) {
    StackCell* cell = stack->first;
    StackCell* p;
    while (cell != NULL) {
        free(cell->payload);
        p = cell;
        cell = cell->next;
        free(p);
    }
}


/*
 *   キュー
 */

/* キューを作成する。 */
MY_HEAP QueueRoot* my_queque_new() {
    return my_stack_new();
}

/* 値をプッシュする。 */
void my_queue_push(QueueRoot* queue, void* value, size_t size) {
    my_stack_push(queue, value, size);
}

/* 先頭を取り出す。 */
void my_queue_deque(QueueRoot* queue, void* pval) {
    memset((uint8_t*)pval, (uint8_t*)(queue->first->payload), queue->first->size);
    QueueCell* p = queue->first;
    queue->first = p->next;
    free(p->payload);
    free(p);
    return;
}

/* 先頭の値を読む。 */
void my_queue_peek(QueueRoot* queue, void* pval) {
    memset((uint8_t*)pval, (uint8_t*)(queue->first->payload), queue->first->size);
    return;
}

/* キューが空かどうかを返す。 */
bool my_queue_empty(QueueRoot* queue) {
    return queue->count == 0 ? true : false;
}

/* キューのリソースを解放する。 */
void my_queue_free(QueueRoot* queue) {
    my_stack_free(queue); 
    return;
}


/*
 *   セット
*/

/* セットを作成する。 */
MY_HEAP SetEntry* my_set_new() {
    SetEntry* ent = (SetEntry*)malloc(sizeof(SetEntry));
    ent->count = 0;
    ent->first = NULL;
    return ent;
}

/* ハッシュ値を得る。 */
int my_set_gethash(const char* item) {
    const char* p = item;
    int sum = 0;
    int mask = 0xff;
    while (*p != 0) {
        sum += (int)*p;
        sum &= mask;
        p++;
    }
    return sum;
}

/* エントリーを得る */
SetEntry* my_set_getentry(SetEntry* set, const char* item) {
    return NULL;
}

/* 新規セルを作成する。 */
SetCell* my_set_cellnew(const char* item) {
    return NULL;  
}

/* アイテムをセットにセットする。*/
void my_set_setcell(SetEntry* set, const char* item) {
    return;
}

/* アイテムがセットに含まれるかチェックする。 */
bool my_set_exists(SetEntry* set, const char* item) {
    return false;
}

/* セットに含まれるアイテムをすべて取得する。 */
int my_get_items(SetEntry* set, char* items[], int leng) {
    return 0;
}

/* セットに含まれるアイテムに関数を適用する。 */
void my_set_foreach(SetEntry* set, void(*callback)(const char* item)) {
    return;
}

/* アイテムのセルを取得する。 */
SetCell* my_set_getcell(SetEntry* set, const char* item) {
    return NULL;
}


