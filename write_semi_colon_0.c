#include "shell.h"
/**
 * the print_error - 
 * @program_shell: 
 * @counter_s: 
 * @command_line: 
 * @type_of_error: 
 * Return: void
 */
void print_error(char *program_shell, int counter,
		char *command_line, int type_of_error)
{
	char *counter_s;

	counter_s = num_to_char(counter);
	write(STDERR_FILENO, program_shell, _strlen(program_shell));
	write(STDERR_FILENO, ": ", 2);
	write(STDERR_FILENO, counter_s, _strlen(counter_s));
	write(STDERR_FILENO, ": ", 2);
	if (type_of_error == EXIT_ERROR)
		write(STDERR_FILENO, "exit", 4);
	else
		write(STDERR_FILENO, command_line, _strlen(command_line));
	write(STDERR_FILENO, ": ", 2);
	if (type_of_error == NOT_FOUND)
		write(STDERR_FILENO, "not found\n", 10);
	else if (type_of_error == PERMISSION_DENIED)
		write(STDERR_FILENO, "Permission denied\n", 18);
	else if (type_of_error == EXIT_ERROR)
	{
		write(STDERR_FILENO, "Illegal number: ", 16);
		write(STDERR_FILENO, command_line, _strlen(command_line));
		write(STDERR_FILENO, "\n", 1);
	}
	/* free the memory allocated for the converted command counter_s */
	free(counter_s);
}
/**
 * print_cant_open : print  can't be opened
 * @program_shell: shell program
 * @counter_s:  counter 
 * @file_name: the file name
 * Return: void() 
 * free counter_s
 */
void print_cant_open(char *program_shell, int counter, char *file_name)
{

	char *counter_s;
	counter_s = num_to_char(counter);
	write(STDERR_FILENO, program_shell, _strlen(program_shell));
	write(STDERR_FILENO, ": ", 2);
	write(STDERR_FILENO, counter_s, _strlen(counter_s));
	write(STDERR_FILENO, ": ", 2);
	write(STDERR_FILENO, "Can't open ", 11);
	write(STDERR_FILENO, file_name, _strlen(file_name));
	write(STDERR_FILENO, "\n", 1);
	free(counter_s);
}
