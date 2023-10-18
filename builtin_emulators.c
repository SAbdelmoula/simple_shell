#include "shell.h"

/**
 * _myexit - Exit the shell with a specified exit status
 * @info: Arrangement with possible arguments
 * Return: exits that display the specified exit status
 *         (0) if info.argv[0] != "exit"
 */
int _myexit(info_t *info)
{
	int exitstatus;

	if (info->argv[1])
	{
		exitstatus = _erratoi(info->argv[1]);
		if (exitstatus == -1)
		{
			info->status = 2;
			print_error(info, "Illegal number: ");
			_eputs(info->argv[1]);
			_eputchar('\n');
			return (1);
		}
		info->err_num = _erratoi(info->argv[1]);
		return (-2);
	}
	info->err_num = -1;
	return (-2);
}

/**
 * _mycd - modifies the process's current directory
 * @info: Arrangement with possible arguments
 * Return: Always 0
 */
int _mycd(info_t *info)
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
			chdir_ret = /* TODO: what should this be? */
				chdir((newDir = _getenv(info, "PWD=")) ? newDir : "/");
		else
			chdir_ret = chdir((newDir = _getenv(info, "PWD=")) ?
			 newDir : "/");
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
		chdir_ret = /* TODO: what should this be? */
			chdir((newDir = _getenv(info, "OLDPWD=")) ? newDir : "/");
	}
	else
		chdir_ret = chdir(info->argv[1]);
	if (chdir_ret == -1)
	{
		print_error(info, "can't cd to ");
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
 * _myhelp - modifies the process's current directory
 * @info: Arrangement with possible arguments
 *  Return: Always 0
 */
int _myhelp(info_t *info)
{
	char **arg_array;

	arg_array = info->argv;
	_puts("help call works. Function not yet implemented \n");
	if (0)
		_puts(*arg_array); /* temp att_unused workaround */
	return (0);
}
