#include "shell.h"

/**
 * hsh - the main shell loop
 * @information: the parameter & backing the structure information
 * @av: the argument vector from main()
 * Return: 0 on success, 1 on error, or error code
 */
int hsh(info_t *information, char **av)
{
	ssize_t n = 0;
	int builtin_ret = 0;

	while (n != -1 && builtin_ret != -2)
	{
		clearenv(information);
		if (Shellnteractive(information))
			_puts("$ ");
		_eputchar(BUF_FLUSH);
		n = GetInput(information);
		if (n != -1)
		{
			SetInformation(information, av);
			builtin_ret = FindBuiltin(information);
			if (builtin_ret == -1)
				findcommand(information);
		}
		else if (Shellnteractive(information))
			_putchar('\n');
		FreeInformation(information, 0);
	}
	WriteHistory(information);
	FreeInformation(information, 1);
	if (!Shellnteractive(information) && info->status)
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
 * FindBuiltin - Find the builtin cmd
 * @information: the parameter & backing to the structure information
 * Return: -1 if builtin not found
 *			0 if builtin executed successfully
 *			1 if builtin found but not successful,
 *			-2 if builtin signals exit()
 */
int FindBuiltin(info_t *information)
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
 * FindCommand - Find the cmd in the  path
 * @information: the parameter & backing to the structure information
 * Return: void
 */
void FindCommand(info_t *information)
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
		if (!isChainDelimiter(info->arg[a], " \t\n"))
			n++;
	if (!n)
		return;

	path = FindStrpath(information, getEnvironment(information, "PATH="),
			   info->argv[0]);
	if (path)
	{
		info->path = path;
		ForkCommand(information);
	}
	else
	{
		if ((Shellnteractive(information) || _getenv(information, "PATH=")
			|| info->argv[0][0] == '/') && IsShellcommand(information, info->argv[0]))
			ForkCommand(information);
		else if (*(info->arg) != '\n')
		{
			info->status = 127;
			PrintShellerror(information, "not found\n");
		}
	}
}

/**
 * ForkCommand - fork the executive thread to run cmd
 * @information: the parameter & backing to the structure information
 * Return: void
 */
void ForkCommand(info_t *information)
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
		if (executive(info->path, info->argv, getEnvironment(information)) == -1)
		{
			FreeInformation(information, 1);
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
