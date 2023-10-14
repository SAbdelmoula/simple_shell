#include "shell.h"

/**
 * exitShell - Exit the shell with a specified exit status
 * @info: Struct containing potential arguments
 * Return: Exit with the given exit status:
 *         (0) if info->argv[0] != "exit"
 */
int exitShell(info_t *info)
{
	int exitStatus;

	if (info->argv[1])
	{
		exitStatus = _erratoi(info->argv[1]);
		if (exitStatus == -1)
		{
			info->status = 2;
			print_error(info, "Illegal number: ");
			_eputs(info->argv[1]);
			_eputchar('\n');
			return (1);
		}
		info->err_num = exitStatus;
		return (-2);
	}
	info->err_num = -1;
	return (-2);
}
/**
 * changeDirectory - Change the current directory of the process
 * @info: Struct containing potential arguments
 * Return: Always 0
 */
int changeDirectory(info_t *info)
{
	char *currentDir, *newDir, buffer[1024];
	int chdir_ret;

	currentDir = getcwd(buffer, 1024);
	if (!currentDir)
		_puts("TODO: >>getcwd failure emsg here<<\n");
	if (!info->argv[1])
	{
		newDir = _getenv(info, "HOME=");
		if (!newDir)
			chdir_ret = chdir((newDir = _getenv(info, "PWD=")) ? newDir : "/");
		else
			chdir_ret = chdir(newDir);
	}
	else if (_strcmp(info->argv[1], "-") == 0)
	{
		if (!_getenv(info, "OLDPWD="))
		{
			_puts(currentDir);
			_putchar('\n');
			return (1);
		}
		_puts(_getenv(info, "OLDPWD="));
		_putchar('\n');
		chdir_ret = chdir((newDir = _getenv(info, "OLDPWD=")) ? newDir : "/");
	}
	else
	{
		chdir_ret = chdir(info->argv[1]);
	}
	if (chdir_ret == -1)
	{
		print_error(info, "can't cd to ");
		_eputs(info->argv[1]);
		_eputchar('\n');
	else
		_setenv(info, "OLDPWD", _getenv(info, "PWD="));
		_setenv(info, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}
/**
 * helpShell - Display the help message for the shell
 * @info: Struct containing potential arguments
 * Return: always 0
 */
int helpShell(info_t *info)
{
	char **argumentsArray;

	argumentsArray = info->argv;
	_puts("Help call works. Function not yet implemented\n");
	if (0)
		_puts(argumentsArray);

	return (0);
}
