#include <cstdio>
#include "system.h"
#include "util/tinydir.h"

std::vector<std::string> getDirectoryFilenames(std::string path)
{
	std::vector<std::string> vec;

	tinydir_dir dir;

	if (tinydir_open(&dir, path.c_str()) == -1)
	{
		fputs("Couldn't read game directory contents.", stderr);
		tinydir_close(&dir);
		return vec;
	}

	while (dir.has_next)
	{
		tinydir_file file;
		if (tinydir_readfile(&dir, &file) == -1)
		{
			fputs("Error getting file", stderr);
			continue;
		}

		if (!file.is_dir)
		{
			vec.push_back(file.name);
		}

		tinydir_next(&dir);
	}

	tinydir_close(&dir);
	return vec;
}

#ifdef _MSC_VER
#include <Windows.h>
#include <io.h>
#include <fcntl.h>

void openSystemConsole()
{
	// from http://justcheckingonall.wordpress.com/2008/08/29/console-window-win32-app/
	// Redirects stdout and stderr to the opened console.
	AllocConsole();

    HANDLE handle_out = GetStdHandle(STD_OUTPUT_HANDLE);
    int hCrt = _open_osfhandle((long) handle_out, _O_TEXT);
    FILE* hf_out = _fdopen(hCrt, "w");
    setvbuf(hf_out, NULL, _IONBF, 1);
    *stdout = *hf_out;

    HANDLE handle_err = GetStdHandle(STD_ERROR_HANDLE);
	int hErrorCrt = _open_osfhandle((long) handle_err, _O_TEXT);
	FILE* hf_err = _fdopen(hErrorCrt, "w");
	setvbuf(hf_err, NULL, _IONBF, 1);
	*stderr = *hf_err;

    HANDLE handle_in = GetStdHandle(STD_INPUT_HANDLE);
    hCrt = _open_osfhandle((long) handle_in, _O_TEXT);
    FILE* hf_in = _fdopen(hCrt, "r");
    setvbuf(hf_in, NULL, _IONBF, 128);
    *stdin = *hf_in;
}
#else
// A no-op on Linux.
void openSystemConsole()
{
}
#endif

