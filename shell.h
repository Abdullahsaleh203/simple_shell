#ifndef HEADER_H
#define HEADER_H
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <linux/limits.h>
#include <dirent.h>
/*my owne macros*/
#define INTERACTIVE 1
#define NOT_INTERACTIVE_FILE 0
#define NOT_INTERACTIVE_PIPED 2
#define ERROR -1
/*The Error status macros*/
#define NOT_FOUND 127
#define PERMISSION_DENIED 126
#define EXIT_ERROR 2
#define TOK_D " \t\r\n\a\""
extern char **environ;
/**
 * struct _list_paths - singly linked list
 * @path: string
 * @len: length of the string
 * @next: points to the next node
 *
 * Description: singly linked list node structure
 */
typedef struct _list_paths
{
	char *path;
	unsigned int len;
	struct _list_paths *next;
} _list_paths;
int _strcmp(char *s1, char *s2);
char *_get_env(char *name);
void free_list(_list_paths *head);
int _strlen(char *s);
ssize_t _getline_Helper(char **lineptr, size_t *n,
__attribute__((unused)) FILE * stream);
ssize_t _getline(char **lineptr, size_t *n, FILE *stream);
char *_strdup(char *str);
char *_str_cat(char *dest, char *src);
char *_str_cpy(char *dest, char *src);
_list_paths *add_node(_list_paths **head, char *path);
_list_paths *set_all_paths_to_list();
_list_paths *set_all_vector_to_list();
char **get_av_with_flags(char *line, int status);
unsigned int char_count(char *str, char c);
/*----------*/
void free_all(char **lines, int counter, _list_paths *env,
_list_paths *current, char *line, char **line_vector);
int _var_cmp(char *var_name, char *full_var);
void _setenv(char *name, char *value, _list_paths *env_list);
_list_paths *get_variable(char *name, _list_paths *head);
size_t print_list(const _list_paths *p);
void set_list_env(_list_paths *p);
size_t env_list_len(const _list_paths *p);
int _cd(char *line_vector[], char **argv);
unsigned int _chr_Check(char c, const char *str);
char *_strtok(char *str, const char *delim);
unsigned int char_count_piped(char *str, char c);
void print_cant_open(char *program_name, int counter, char *file_name);
void is_not_built_in(char **line_vector, char *env[], int *status,
int counter, _list_paths *current, char *argv[]);
char **text_to_vector(char *text);
char **file_not_interactive(char *file_name, char *program_shell);
char **piped_not_interactive();
char **get_commands(int o_mode, char *file_name, char *program_shell);
void free_li_vec(char *line, char **line_vector);
int is_dir(char *line, char **argv, int counter,
char **line_vector, int *status, char *old_line);
int _atoi(char *s);
void is_exit(char *line, char **line_vector, _list_paths *current,
char *program_shell, int counter, int *status, _list_paths *env, char **lines);
void print_error(char *program_shell, int counter,
char *command, int type_of_error);
void handle_comments(char *input);
/*=------------------=*/
void handle_semicolons(char *line);
void execute_command_with_waitpid(char *path, char **av, char **env);
/*-------------------*/
char *number_to_char(int num);
char *check_access(char *line_av_1, _list_paths *current);
void execute_command(char *path, char **av, char **env, int *status);
void print_env(int *status);
char *get_process_id();
char *get_status(int n);
int is_built_in(char *line, char **line_vector, _list_paths *current,
char *program_shell,
int counter, int *status, _list_paths *env, char **lines, char **argv);
void print_error(char *program_shell, int counter,
char *command, int type_of_error);
char *get_command_from_file(char *file);
char *get_command_from_user(_list_paths *current);
int checker_mode(int argc);
void free_vec(char **vec);
#endif
