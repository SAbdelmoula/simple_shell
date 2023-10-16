#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>

/* for write&read buffers */
#define READ_BUF_SIZE 1024
#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH -1

/* for cmd chaining */
#define CMD_NORM	0
#define CMD_OR		1
#define CMD_AND		2
#define CMD_CHAIN	3

/* for convert_number() */
#define CONVERT_LOWERCASE	1
#define CONVERT_UNSIGNED	2

/* 1 if using system getline() */
#define USE_GETLINE 0
#define USE_STRTOK 0

#define HIST_FILE	".simple_shell_history"
#define HIST_MAX	4096

extern char **environ;


/**
 * struct liststr - singly linked list
 * @number: the field number
 * @string: a string
 * @next: points to the next node
 */
typedef struct liststr
{
	int number;
	char *str;
	struct liststr *next;
} list_t;

/**
 *structure passinfo - contains pseudo-arguements to pass into a function,
 *					allowing uniform prototype for function pointer structure
 *@arg: a string generated from getline containing arguements
 *@argv: an array of strings generated from arg
 *@path: a string path for the current command
 *@argc: the argument count
 *@line_count: the error count
 *@err_num: the error code for exit()s
 *@linecount_flag: if on count this line of input
 *@fname: the program filename
 *@env: linked list local copy of environ
 *@environ: custom modified copy of environ from LL env
 *@history: the history node
 *@alias: the alias node
 *@env_changed: on if environ was changed
 *@status: the return status of the last exec'd command
 *@cmd_buf: address of pointer to cmd_buf, on if chaining
 *@cmd_buf_type: CMD_type ||, &&, ;
 *@readfd: the fd from which to read line input
 *@histcount: the history line number count
 */
typedef struct passinfo
{
	char *arg;
	char **argv;
	char *path;
	int argc;
	unsigned int line_count;
	int err_num;
	int linecount_flag;
	char *fname;
	list_t *env;
	list_t *history;
	list_t *alias;
	char **environ;
	int env_changed;
	int status;

	char **cmd_buf; /* pointer to cmd ; chain buffer, for memory mangement */
	int cmd_buf_type; /* CMD_type ||, &&, ; */
	int readfd;
	int histcount;
} info_t;

#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
	0, 0, 0}

/**
 *struct builtin - contains a builtin string and related function
 *@type: the builtin command flag
 *@func: the function
 */
typedef struct builtin
{
	char *type;
	int (*func)(info_t *);
} builtin_table;

/* path.c */
int IsShellcommand(info_t *information, char *path);
char *DuplicateShellchars(char *pathstring, int start, int stop);
char *FindStrpath(info_t *information, char *pathstring, char *command);

/* memory_functions */
char *_Memset(char *s, char buf, unsigned int num);
void Ffree(char **pp);
void *RealLocate(void *parameter, unsigned int old_size,
	 unsigned int current_size);

/* memory_functions2.c */
int Bfree(void **parameter);

/* more_functions.c */
int Shellnteractive(info_t *information);
int Isfunctiondelimeter(char c, char *delimeter);
int ISfunctionalpha(int c);
int SHellatoi(char *s);

/* more_functions2.c */
int SHellerratoi(char *s);
void PrintShellerror(info_t *information, char *str);
int Printfunction_d(int input, int fd);
char *ConvertShellnumber(long int number, int base, int flags);
void RemoveShellcomment(char *buffer);

/* hsh.c */
int hsh(info_t *information, char **av);
int FindBuiltin(info_t *information);
void FindCommand(info_t *information);
void ForkCommand(info_t *information);

/* err_string_functions.c */
void _eputs(char *str);
int _eputChar(char c);
int _putfd(char c, int fd);
int _putsfd(char *str, int fd);

/* string_functions.c */
int StringLength(char *st);
int StringComparison(char *st1, char *st2);
char *startwithHys(const char *haystack, const char *needle);
char *stringSHellConcateat(char *destination, char *source);

/* string_functions2.c */
char *_stringcopy(char *destination, char *source);
char *_stringduplicate(const char *string);
void _putstr(char *string);
int _putchars(char c);

/* string_functions3.c */
char *_stringcpy(char *destination, char *source, int num);
char *_stringcat(char *destination, char *source, int num);
char *_stringchars(char *str, char c);

/* string_functions4.c */
char *stringwords(char *string, char *delimeter);
char *string2w(char *string, char delimeter);


/* builtin_emulators.c */
int _myexit(info_t *info);
int _mycd(info_t *info);
int _myhelp(info_t *info);

/* builtin_emulators2.c */
int _myhistory(info_t *info);
int unset_alias(info_t *info, char *aliasString);
int set_alias(info_t *info, char *aliasString);
int print_alias(list_t *node);
int _myalias(info_t *info);

/* getline.c */

ssize_t Buffer_Input(info_t *information, char **buffer, size_t *Len);
ssize_t GetInput(info_t *information);
ssize_t ReadBuffer(info_t *information, char *buffer, size_t *i);
int _getline(info_t *info, char **ptr, size_t *length);
void Siginthandler(__attribute__((unused))int sig_number);

/* getinfo.c */
void ClearInformation(info_t *information);
void SetInformation(info_t *information, char **av);
void FreeInformation(info_t *information, int all);

/* shell_envir.c */
int _myenvironment(info_t *info);
char *_getenvironment(info_t *info, const char *name);
int _mysetenvironment(info_t *info);
int _myunsetenvironment(info_t *info);
int populate_environment_List(info_t *info);

/* shell_envir2.c */
char **get_environment(info_t *info);
int _unsetenvironment(info_t *info, char *varName);
int _setenvironment(info_t *info, char *varName, char *value);

/* file_io_functions.c */
char *get_history_file(info_t *information);
int write_history(info_t *information);
int read_history(info_t *information);
int build_history_list(info_t *information, char *buffer, int Linecount);
int renumber_history(info_t *information);

/* liststr.c */
list_t *AddNode(list_t **head, const char *structure, int number);
list_t *AddNode_End(list_t **head, const char *structure, int number);
size_t PrintListstructure(const list_t *head);
int DeleteNodeIndex(list_t **head, unsigned int index);
void FreeList(list_t **head_parameter);

/* liststr2.c */
size_t ListLen(const list_t *head);
char **Listtostrings(list_t *head);
size_t PrintList(const list_t *head);
list_t *Nodestartswith(list_t *node, char *prefix, char c);
ssize_t GetNodeIndex(list_t *head, list_t *node);

/* chain.c */
int is_chain(info_t *info, char *buffer, size_t *position);
void check_chain(info_t *info, char *buffer, size_t *position,
                size_t startIndex, size_t length);
int replace_alias(info_t *info);
int replace_vars(info_t *info);
int replace_string(char **oldString, char *newString);

#endif
