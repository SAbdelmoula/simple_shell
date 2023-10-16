#include "shell.h"

/**
 * hsh - the initial  shell loop
 * @information: information struct for parameters and returns
 * @av: the main() argument vector
 * Return: 0 for success, 1 for error, or error code
 */
int hsh(info_t *information, char **av)
{
	ssize_t n = 0;
	int builtin_ret = 0;

	while (n != -1 && builtin_ret != -2)
	{
		clear_information(information);
		if (interactive(information))
			_puts("$ ");
		_eputchar(BUF_FLUSH);
		n = get_input(information);
		if (n != -1)
		{
			set_information(information, av);
			builtin_ret = find_builtin(information);
			if (builtin_ret == -1)
				find_command(information);
		}
		else if (interactive(information))
			_putchar('\n');
		free_nformation(information, 0);
	}
	write_history(information);
	free_information(information, 1);
	if (!interactive(information) && info->status)
		exit(info->status);
	if (builtin_ret == -2)
	{
		if (info->err_num == -1)
			exit(info->status);
		exit(info->err_num);
	}
	return (builtin_ret);
}

/**
 * find_builtin - identifies a built-in command
 * @information: struct for argument and return information
 * Return: -1 if builtin not appear,
 *			0 if builtin worked successfully
 *			1 if builtin found but fail,
 *			-2 if builtin signals appear()
 */
int find_builtin(info_t *information)
{
	int n, built_in_ret = -1;
	builtin_table builtintbl[] = {
		{"exit", _myexit},
		{"env", _myenv},
		{"help", _myhelp},
		{"history", _myhistory},
		{"unsetenv", _mysetenv},
		{"unsetenv", _myunsetenv},
		{"cd", _mycd},
		{"alias", _myalias},
		{NULL, NULL}
	};

	for (n = 0; builtintbl[n].type; n++)
		if (_strcmp(information->argv[0], builtintbl[n].type) == 0)
		{
			info->line_count++;
			built_in_ret = builtintbl[i].func(information);
			break;
		}
	return (built_in_ret);
}

/**
 * find_command - locates the command along the path
 * @information: the parameter and supporting info  for the struct
 * Return: void
 */
void find_command(info_t *information)
{
	char *path = NULL;
	int a, n;

	information->path = information->argv[0];
	if (info->linecount_flag == 1)
	{
		info->line_count++;
		info->linecount_flag = 0;
	}
	for (a = 0, n = 0; info->arg[a]; a++)
		if (!is_delim(info->arg[a], " \t\n"))
			n++;
	if (!n)
		return;

	path = find_path(information, _getenvironment(information, "PATH="),
			   info->argv[0]);
	if (path)
	{
		info->path = path;
		fork_command(information);
	}
	else
	{
		if ((interactive(information) || _getenvironment(information, "PATH=")
			|| info->argv[0][0] == '/') && is_cmd(information, info->argv[0]))
			fork_command(information);
		else if (*(info->arg) != '\n')
		{
			info->status = 127;
			print_error(information, "not found\n");
		}
	}
}

/**
 * fork_command - split the executive thread and execute cmd
 * @information: the parameter and supporting info  for the struct
 * Return: void
 */
void fork_command(info_t *information)
{
	pid_t child_pid;

	child_pid = fork();
	if (child_pid == -1)
	{
		/* TODO: PUT ERROR FUNCTION */
		perror("Error:");
		return;
	}
	if (child_pid == 0)
	{
		if (execve(info->path, info->argv, get_environment(information)) == -1)
		{
			free_information(information, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
		/* TODO: put error function */
	}
	else
	{
		wait(&(info->status));
		if (WIFEXITED(info->status))
		{
			info->status = WEXITSTATUS(info->status);
			if (info->status == 126)
				print_error(information, "Permission denied\n");
		}
	}
}
