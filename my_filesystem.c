/* my_filesystem.c */
#include "my_filesystem.h"

// ファイル属性
/* ファイルまたはディレクトリが存在し、かつアクセスできるかチェックする。*/
bool my_exists(const char* path) {
    return access(path, F_OK) == 0 ? true : false;
}

/* 指定したパスがファイルかチェックする。 */
bool my_isfile(const char* path) {
    struct stat status;
    if (stat(path, &status) < 0)
        return false;
    return S_ISREG(status.st_mode);
}

/* 指定したパスがディレクトリかチェックする。*/
bool my_isdir(const char* path) {
    struct stat status;
    if (stat(path, &status) < 0)
      return false;
    return S_ISDIR(status.st_mode);
}

/* 指定したパスがシンボリックリンクかチェックする。 */
bool my_issymlink(const char* path) {
    struct stat status;
    if (lstat(path, &status) < 0)
        return false;
    else
        return S_ISLNK(status.st_mode);
}


/* ファイルが読み込めるかチェックする。*/
bool my_file_readable(const char* path) {
    return access(path, R_OK) == 0 ? true : false;
}

/* ファイルが実行できるかチェックする。*/
bool my_file_executable(const char* path) {
    return access(path, X_OK) == 0 ? true : false;
}

/* ファイルが書き込めるかチェックする。*/
bool my_file_writable(const char* path) {
    return access(path, W_OK) == 0 ? true : false;
}

/* ファイルの更新日付時刻 */
time_t my_file_time(const char* path) {
    struct stat status;
    if (stat(path, &status) < 0)
        return -1L;
    else
        return status.st_mtime;
}


/* ファイルの更新日付時刻を文字列として得る。 */
MY_HEAP char* my_file_strtime(const char* path) {
    char buff[100];
    struct stat status;
    if (stat(path, &status) < 0)
      return NULL;
    struct tm* t = localtime(&(status.st_mtime));
    setlocale(LC_TIME, "ja-JP");
    strftime(buff, 100, "%Y-%m-%d %H:%M:%S", t);
    char* result = (char*)malloc(strlen(buff) + 1);
    strcpy(result, buff);
    return result;
}

/* ファイルの長さを得る。*/
size_t my_file_length(const char* path) {
    struct stat status;
    if (stat(path, &status) < 0)
        return 0L;
    else
        return status.st_size;
}

/* ファイル/ディレクトリの所有者を得る。 */
uid_t my_file_owner(const char* path) {
   struct stat status;
   if (stat(path, &status) < 0)
       return 0L;
   else
       return (status.st_uid);
}

/* ファイル/ディレクトリのグループを得る。*/
gid_t my_file_group(const char* path) {
    struct stat status;
    if (stat(path, &status) < 0)
        return 0L;
    else
        return (status.st_gid);
}

/* 所有者またはグループコードからユーザ名を得る。*/
MY_HEAP const char* my_getname(int id, bool group) {
    struct passwd* pwd;
    struct group* grp;
    int n;
    char* result;
    if (group) {
      grp = getgrgid(id);
      n = strlen(grp->gr_name);
      result = (char*)malloc(n + 1);
      strcpy(result, grp->gr_name);
    }
    else {
      pwd = getpwuid(id);
      n = strlen(pwd->pw_name);
      result = (char*)malloc(n + 1);
      strcpy(result, pwd->pw_name);
    }
    return result;
}


// ファイルシステム情報
/* カレントディレクトリを得る。 */
MY_HEAP const char* my_pwd() {
    char buff[512];
    getcwd(buff, sizeof(buff));
    char* ret = (char*)malloc(strlen(buff) + 1);
    strcpy(ret, buff);
    return ret;
}

/* ホームディレクトリを得る。*/
MY_HEAP const char* my_home() {
    return getenv("HOME");
}

// パス
/* ファイル拡張子を得る。 */
MY_HEAP const char* my_file_ext(const char* path) {
  int8_t* p1 = strrchr(path, '.');
  int8_t* p2 = strrchr(path, '/');
  int8_t* ext = (int8_t*)calloc(MAX_EXTLEN + 1, sizeof(int8_t));
  if (p1 == NULL)
    return emptystring;
  int8_t* p = p1;
  if (p2 == NULL || (int64_t)p2 < (int64_t)p1) {
    for (int i = 0; i < MAX_EXTLEN; i++) {
      if (*p == 0)
        break;
      ext[i] = *p++;
    }
  }
  return ext;
}

/* パスのディレクトリ部分を得る */
MY_HEAP const char* my_file_dir(const char* path) {
  int8_t* p1 = strrchr(path, '/');
  if (p1 == NULL || (int64_t)p1 == (int64_t)path)
    return emptystring;
  int64_t n = (int64_t)p1 - (int64_t)path;
  int8_t* dir = (int8_t*)calloc(n + 1, sizeof(int8_t));
  strncpy(dir, path, n);
  return dir;
}


/* パスのファイル名部分を得る。*/
MY_HEAP const char* my_file_filename(const char* path) {
  int8_t* p1 = strrchr(path, '/');
  if (p1 == NULL || (int64_t)p1 == (int64_t)path)
    return path;
  int64_t n = (int64_t)strlen(path) - ((int64_t)p1 - (int64_t)path);
  int8_t* filename = (int8_t*)calloc(n + 1, sizeof(int8_t));
  strncpy(filename, p1 + 1, n);
  return filename;
}

/* パスに文字列を追加する。 */
MY_HEAP const char* my_file_append(const char* path, const char* p) {
  int8_t sep[2];
  sep[0] = separator;
  sep[1] = '\0';
  int8_t* newpath = (int8_t*)malloc(strlen(dir) + strlen(p) + 2);
  strcpy(newpath, dir);
  strcat(newpath, sep);
  strcat(newpath, p);
  return newpath;
}

/* 相対パスから絶対パスに変換する。*/
MY_HEAP const char* my_file_absolute(const char* relpath) {
  char abspath[512];
  realpath(relpath, abspath);
  size_t size = strlen(abspath) + 1;
  int8_t* result = (int8_t*)malloc(size);
  strcpy(result, abspath);
  return result;
}

// ファイル入出力
/* ファイルを読んでバッファを返す。 */
MY_HEAP char* my_file_read(const char* path, size_t maxsize) {
  char* buff = (char*)malloc(maxsize);
  memset(buff, 0, sizeof(buff));
  const char* path = argv[1];
  int fd = open(path, O_RDONLY);  // 読み込み専用で開く。
  ssize_t size = read(fd, buff, sizeof(buff));  // 最大バッファサイズまで読み込む。
  char* p = strchr(buff, 255);  // ファイル全体でなく途中まで読み込んだ場合は終端が 255 になる。
  if (p != NULL)  // 255 があった場合、改行に置き換える。
    *p = '\n';
  close(fd);
  return buff;
}

/* ファイルにバッファ内容を書く。*/
ssize_t my_file_write(const char* path, char* buf) {
  int flags = O_CREAT|O_WRONLY;
  if (access(path, F_OK) == 0)  // 書き込むファイルが存在するか？
    flags = O_WRONLY; // 存在する場合、O_CREAT は不要。
  int fd = open(path, flags, 0744);  // 書き込み専用で開く。
  ssize_t size = write(fd, buff, strlen(buff));  // buff 内容を書く。
  close(fd);
  return size;
}

// ディレクトリの内容一覧
/* ディレクトリ内容を文字列配列として返す。 */
void my_dir_entries(DirentList* entlist, const char* directory) {
  struct dirent* ent;
  struct stat* status = (struct stat*)malloc(sizeof(struct stat));
  char path[MAX_PATH];
  entlist->first = NULL;
  entlist->last = NULL;
  entlist->count = 0;
  DIR* dp = opendir(directory);
  while ((ent = readdir(dp)) != NULL) {
    if (strcmp(ent->d_name, ".") == 0 || strcmp(ent->d_name, "..") == 0)
      continue;
    path[0] = '\0';
    strcpy(path, directory);
    strcat(path, "/");
    strcat(path, ent->d_name);
    if (stat(path, status) == 0) {
      my_dir_append(entlist, ent, status, NULL);
    }
  }
  closedir(dp);
}

/* ディレクトリを再帰的に検索して内容を文字列配列として返す。*/
void my_dir_recursive(DirentList* entlist, const char* directory) {
  struct dirent* ent;
  struct stat* status = (struct stat*)malloc(sizeof(struct stat));
  char path[MAX_PATH];
  entlist->first = NULL;
  entlist->last = NULL;
  entlist->count = 0;
  DIR* dp = opendir(directory);
  if (dp == NULL)
    return;
  while ((ent = readdir(dp)) != NULL) {
    if (strcmp(ent->d_name, ".") == 0 || strcmp(ent->d_name, "..") == 0)
      continue;
    path[0] = '\0';
    strcpy(path, directory);
    strcat(path, "/");
    strcat(path, ent->d_name);
    if (stat(path, status) == 0) {
      char fullpath[MAX_PATH];
      strcpy(fullpath, directory);
      strcat(fullpath, "/");
      strcat(fullpath, ent->d_name);
      my_dir_append(entlist, ent, status, fullpath);
      if (S_ISDIR(status->st_mode)) {
        char dir[MAX_PATH];
        strcpy(dir, directory);
        strcat(dir, "/");
        strcat(dir, ent->d_name);
        my_dir_recursive(entlist, dir);
      }
    }
  }
  closedir(dp);
}

/* ディレクトリ・エントリリストに指定したエントリを追加する。*/
bool dir_append(DirentList* entries, struct dirent* ent, struct stat* status, char* fullpath) {
  DirEntryCell* cell = (DirEntryCell*)malloc(sizeof(DirEntryCell));
  cell->stat = (struct stat*)malloc(sizeof(struct stat));
  memcpy(cell->stat, status, sizeof(struct stat));
  cell->dir_entry = (struct dirent*)malloc(sizeof(struct dirent));
  cell->dir_entry->d_reclen = ent->d_reclen;
  cell->dir_entry->d_type = ent->d_type;
  if (fullpath == NULL)
    strcpy(cell->dir_entry->d_name, ent->d_name);
  else
    strcpy(cell->dir_entry->d_name, fullpath);
  cell->next = NULL;
  if (entries->count == 0) {
    entries->first = cell;
    entries->last = cell;
    entries->count = 1;
  }
  else {
    entries->last->next = cell;
    entries->last = cell;
    entries->count++;
  }
  return true;
}

/* 取得済みのディレクトリの全エントリに対して関数 callback を適用する。*/
void dir_foreach(DirentList* entlist, void (*callback)(struct dirent* entry)) {
  DirEntryCell* cell = entlist->first;
  while (cell != NULL) {
    callback(&(cell->dir_entry));
    cell = cell->next;
  }
}

/* リストを配列に変換する。*/
void dir_toarray(DirentList* entlist, DirEntryCell* entries[], size_t size) {
  DirEntryCell* cell = entlist->first;
  for (int i = 0; i < size; i++)
    entries[i] = NULL;
  int i = 0;
  while (cell != NULL) {
    if (i < size) {
      entries[i] = cell->dir_entry;
      cell = cell->next;
      i++;
    }
    else {
      break;
    }
  }
}

// ファイル操作
/* ファイルやディレクトリを移動する。(リネームする) */
bool my_move(const char* src, const char* dest) {
  return false;
}

/* ファイルをコピーする。 */
bool my_copy(const char* src, const char* dest) {
  return false;

}

/* ファイルを削除する。 */
bool my_delete(const char* src, bool force) {
  return false;

}

/* ファイルモードを変更する。 */
bool my_chmod(const char* path, int mode) {
  return false;

}

// ディレクトリ操作
/* ディレクトリを作成する。*/
bool my_mkdir(const char* dir) {
  return false;

}

/* 空のディレクトリを削除する。 */
bool my_rmdir(const char* dir) {
  return false;

}

// 一時ファイル
/* バッファ内容を一時ファイルに書く。 */
FILE* my_write_temp(char* buf) {
  return NULL;
}

/* 一時ファイルの内容を読む。*/
bool my_read_temp(FILE* fp, char* buf, bool close) {
  return false;

}
