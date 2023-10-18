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
 * struct liststr - individual linked list
 * @num: the numerical field
 * @str: a string
 * @next: indicates the following node
 */
typedef struct liststr
{
	int num;
	char *str;
	struct liststr *next;
} list_t;

/**
 *struct passinfo - includes fictitious arguments to pass to a function,
 *					enabling uniform function pointer structure prototype
 *@arg: a string produced by getline that contains arguments
 *@argv: a string array created from arg
 *@path: an array path for the active command
 *@argc: the number of arguments
 *@line_count: the number of errors
 *@err_num: the exit() error code
 *@linecount_flag: If this input line is counted
 *@fname: software's filename
 *@env: local copy of linked list enviroment
 *@environ: LL env environment updated specifically
 *@history: historical node
 *@alias: alias node
 *@env_changed: if the environment changed
 *@status: the last executed command's return status
 *@cmd_buf: address of the cmd_buf pointer, if chaining
 *@cmd_buf_type: CMD_type ||, &&, ;
 *@readfd: reading line input from the fd
 *@histcount: the amount of historical lines
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
 *struct builtin - includes an integrated string and related functions
 *@type: the internal cmd flag
 *@func: function
 */
typedef struct builtin
{
	char *type;
	int (*func)(info_t *);
} builtin_table;

/* path.c */
int is_cmd(info_t *info, char *path);
char *dup_chars(char *pathstring, int start, int stop);
char *find_path(info_t *info, char *pathstring, char *command);

/* memory_functions */
char *_memset(char *s, char buf, unsigned int num);
void ffree(char **pp);
void *_realloc(void *parameter, unsigned int old_size,
	 unsigned int current_size);

/* memory_functions2.c */
int bfree(void **parameter);

/* more_functions.c */
int interactive(info_t *info);
int is_delim(char c, char *delimeter);
int _isalpha(int c);
int _atoi(char *s);

/* more_functions2.c */
int _erratoi(char *s);
void print_error(info_t *info, char *str);
int print_d(int input, int fd);
char *convert_number(long int number, int base, int flags);
void remove_comments(char *buffer);

/* hsh.c */
int hsh(info_t *info, char **av);
int find_builtin(info_t *info);
void find_cmd(info_t *info);
void fork_cmd(info_t *info);

/* loophsh.c */
int loophsh(char **);

/* err_string_functions.c */
void _eputs(char *str);
int _eputchar(char c);
int _putfd(char c, int fd);
int _putsfd(char *str, int fd);

/* string_functions.c */
int _strlen(char *st);
int _strcmp(char *st1, char *st2);
char *starts_with(const char *haystack, const char *needle);
char *_strcat(char *destination, char *source);

/* string_functions2.c */
char *_strcpy(char *destination, char *source);
char *_strdup(const char *str);
void _puts(char *str);
int _putchar(char c);

/* string_functions3.c */
char *_strncpy(char *destination, char *source, int num);
char *_strncat(char *destination, char *source, int num);
char *_strchr(char *st, char c);

/* string_functions4.c */
char **strtow(char *str, char *delimeter);
char **strtow2(char *str, char delimeter);


/* builtin_emulators.c */
int _myexit(info_t *info);
int _mycd(info_t *info);
int _myhelp(info_t *info);

/* builtin_emulators2.c */
int _myhistory(info_t *info);
int unset_alias(info_t *info, char *str);
int set_alias(info_t *info, char *str);
int print_alias(list_t *node);
int _myalias(info_t *info);

/* getline.c */

ssize_t input_buf(info_t *info, char **buffer, size_t *Len);
ssize_t get_input(info_t *info);
ssize_t read_buf(info_t *info, char *buffer, size_t *i);
int _getline(info_t *info, char **ptr, size_t *length);
void sigintHandler(__attribute__((unused))int sig_number);

/* getinfo.c */
void clear_info(info_t *info);
void set_info(info_t *info, char **av);
void free_info(info_t *info, int all);

/* shell_envir.c */
int _myenv(info_t *info);
char *_getenv(info_t *info, const char *name);
int _mysetenv(info_t *info);
int _myunsetenv(info_t *info);
int populate_env_list(info_t *info);

/* shell_envir2.c */
char **get_environment(info_t *info);
int _unsetenv(info_t *info, char *varName);
int _setenv(info_t *info, char *varName, char *value);

/* file_io_functions.c */
char *get_history_file(info_t *info);
int write_history(info_t *info);
int read_history(info_t *info);
int build_history_list(info_t *info, char *buffer, int linecount);
int renumber_history(info_t *info);

/* liststr.c */
list_t *add_node(list_t **head, const char *str, int number);
list_t *add_node_end(list_t **head, const char *str, int number);
size_t print_list_str(const list_t *head);
int delete_node_at_index(list_t **head, unsigned int index);
void free_list(list_t **head_parameter);

/* liststr2.c */
size_t list_len(const list_t *head);
char **list_to_strings(list_t *head);
size_t print_list(const list_t *head);
list_t *node_starts_with(list_t *node, char *prefix, char c);
ssize_t get_node_index(list_t *head, list_t *node);

/* chain.c */
int is_chain(info_t *info, char *buffer, size_t *position);
void check_chain(info_t *info, char *buffer, size_t *position,
size_t startIndex, size_t length);
int replace_alias(info_t *info);
int replace_vars(info_t *info);
int replace_string(char **oldString, char *newString);

#endif
