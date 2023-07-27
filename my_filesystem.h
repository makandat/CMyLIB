/* my_filesystem.h */
#ifndef MY_FILESYSTEM_H
#define MY_FILESYSTEM_H

#include "my_string.h"
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <time.h>
#include <grp.h>
#include <pwd.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/types.h>
#include <locale.h>
#include <dirent.h>

#define MAX_PATH 512
#define MAX_EXTLEN 10

char *realpath(const char *__restrict__file_name, char *__restrict__resolved_name);
int lstat(const char *__restrict__ pathname, struct stat *__restrict__ buf);

/* ディレクトリエントリのセル */
typedef struct tagDirEntryCell {
  struct dirent* dir_entry;  // dirent 構造体へのポインタ
  struct stat* stat;  // stat 構造体へのポインタ
  struct tagDirEntry* next;  // 次のエントリへのポインタ
} DirEntryCell;

/* ディレクトリエントリのリスト */
typedef struct tagDirentList {
  struct tagDirEntryCell* first;  // 最初のエントリへのポインタ
  struct tagDirEntryCell* last;  // 最後のエントリへのポインタ
  int count;  // リストに含まれるエントリの数
} DirentList;

/*
struct dirent {
        __uint32_t d_fileno;            // エントリのファイル番号
        __uint16_t d_reclen;            // このレコードの長さ
        __uint8_t  d_type;              // ファイルタイプ、以下参照
        __uint8_t  d_namlen;            // d_name の文字列長
        char    d_name[255 + 1];        // 名前はこの長さを越えてはならない
} */

// ファイル属性
bool my_exists(const char* path);  // ファイルまたはディレクトリが存在するかチェックする。
bool my_isfile(const char* path);  // ファイルが存在するかチェックする。
bool my_isdir(const char* path);   // ディレクトリが存在するかチェックする。
bool my_issymlink(const char* path); // シンボリックリンクかチェックする。
bool my_file_readable(const char* path); // ファイルが読み込めるかチェックする。
bool my_file_executable(const char* path); // ファイルが実行できるかチェックする。
bool my_file_writable(const char* path); // ファイルが書き込めるかチェックする。
time_t my_file_time(const char* path); // ファイルの更新日付時刻
MY_HEAP char* my_file_strtime(const char* path); // ファイルの更新日付時刻を文字列として得る。
size_t my_file_length(const char* path);  // ファイルの長さを得る。
uid_t my_file_owner(const char* path);  // ファイル/ディレクトリの所有者を得る。
gid_t my_file_group(const char* path);  // ファイル/ディレクトリのグループを得る。
MY_HEAP const char* my_getname(int id, bool group); // 所有者またはグループコードからユーザ名を得る。

// ファイルシステム情報
MY_HEAP const char* my_pwd();  // カレントディレクトリを得る。
MY_HEAP const char* my_home(); // ホームディレクトリを得る。

// パス
MY_HEAP const char* my_file_ext(const char* path);  // ファイル拡張子を得る。
MY_HEAP const char* my_file_dir(const char* path);  // パスのディレクトリ部分を得る
MY_HEAP const char* my_file_filename(const char* path); // パスのファイル名部分を得る。
MY_HEAP const char* my_file_append(const char* path, const char* p);  // パスに文字列を追加する。
MY_HEAP const char* my_file_absolute(const char* relpath);  // 相対パスから絶対パスに変換する。

// ファイル入出力
MY_HEAP char* my_file_read(const char* path, size_t maxsize);  // ファイルを読んでバッファを返す。
ssize_t my_file_write(const char* path, char* buf);  // ファイルにバッファ内容を書く。

// ディレクトリの内容一覧
void my_dir_entries(DirentList* entlist, const char* directory);  // ディレクトリ内容を返す。
void my_dir_recursive(DirentList* entlist, const char* directory);  // ディレクトリを再帰的に検索して内容を返す。
bool my_dir_append(DirentList* entries, struct dirent* ent, struct stat* status, char* fullpath);  // (ワーク用) ディレクトリ・エントリリストに指定したエントリを追加する。
void my_dir_foreach(DirentList* entlist, void (*callback)(struct dirent* entry));  // 取得済みのディレクトリの全エントリに対して関数 callback を適用する。
int my_dir_toarray(DirentList* entlist, DirEntryCell* entries[], size_t size);  // リストを配列に変換する。

// ファイル操作
bool my_rename(const char* src, const char* dest);  // ファイルやディレクトリをリネームする。
bool my_copy(const char* src, const char* dest, bool overwrite);  // ファイルをコピーする。
bool my_delete(const char* src);      // ファイルを削除する。
bool my_chmod(const char* path, int mode);  // ファイルモードを変更する。

// ディレクトリ操作
bool my_mkdir(const char* dir);  // ディレクトリを作成する。
bool my_rmdir(const char* dir);  // 空のディレクトリを削除する。
bool my_chdir(const char* dir);  // カレントディレクトリを変更する。

// 一時ファイル
FILE* my_write_temp(char* buf);  // 一時ファイルに書き込む。
bool my_read_temp(FILE* fp, char* buf, size_t size, bool close); // 一時ファイルから読む。

#endif
