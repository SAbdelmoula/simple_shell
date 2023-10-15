#include "shell.h"

/**
 * _myexitShell - Exit the shell with a specified exit status
 * @info: Struct containing potential arguments
 * Return: Exit with the given exit status:
 *         (0) if info->argv[0] != "exit"
 */
int _myexitShell(info_t *info)
{
	int exitstatus;

	if (info->argv[1])
	{
		exitstatus = SHellerratoi(info->argv[1]);
		if (exitstatus == -1)
		{
			info->status = 2;
			PrintShellerror(info, "Illegal number: ");
			_eputs(info->argv[1]);
			_eputchar('\n');
			return (1);
		}
		info->err_num = PrintShellerror(info->argv[1]);
		return (-2);
	}
	info->err_num = -1;
	return (-2);
}

/**
 * _changeDirectory - changes the current directory of the process
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: Always 0
 */
int _changeDirectory(info_t *info)
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
			chdir_ret = /* TODO: What ought to this be? */
				chdir((newDir = _getenv(info, "PWD=")) ? newDir : "/");
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
		_puts(_getenv(info, "OLDPWD=")), _putchar('\n');
		chdir_ret = /* TODO: What ought to this be? */
			chdir((newDir = _getenv(info, "OLDPWD=")) ? newDir : "/");
	}
	else
		chdir_ret = chdir(info->argv[1]);
	if (chdir_ret == -1)
	{
		print_error(info, "can't change directory to ");
		_eputs(info->argv[1]), _eputchar('\n');
	}
	else
	{
		_setenv(info, "OLDPWD", _getenv(info, "PWD="));
		_setenv(info, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}

/**
 * _myshellhelp - changes the current directory of the process
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 *  Return: Always 0
 */
int _myshellhelp(info_t *info)
{
	char **argumentsArray;

	argumentsArray = info->argv;
	_puts("Help call works. Function not yet implemented \n");
	if (0)
		_puts(*argumentsArray); /* att_unused temporary workaround */
	return (0);
}
