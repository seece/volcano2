#include "system.h"

#ifdef _MSC_VER
#include <Windows.h>
#include <io.h>
#include <fcntl.h>

std::vector<std::string> getDirectoryFilenames(std::string dir)
{
	std::vector<std::string> vec;

	/* FIXME Replace this placeholder function. */
	vec.push_back("map1.map");
	vec.push_back("map2.map");
	vec.push_back("map3.map");

	return vec;
}

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
// TODO fix this Linux implementation
#include <unistd.h>
#include <dirent.h>

std::vector<std::string> getDirectoryFilenames(std::string dir)
{
	std::vector<std::string> filenames;

    DIR* dirStream = opendir(".");
    struct dirent* entry = new dirent;
    struct dirent* next;

    readdir_r(dirStream, entry, &next);
    while (next) {
        std::string filename(next->d_name);
        std::string extension(".map");

        bool isMapFile = false;
        if(filename.length() > extension.length()) {
            size_t extPos = filename.length() - extension.length();
            std::string end = filename.substr(extPos);
            for(size_t i = 0; i < end.length(); i++) {
                end[i] = tolower(end[i]);
            }

            isMapFile = (end == extension);
        }

        if(isMapFile) {
            filenames.push_back(filename);
        }

        readdir_r(dirStream, entry, &next);
    }
    
    closedir(dirStream);
    delete entry;

	return filenames;
}

// A no-op on Linux.
void openSystemConsole()
{
}
#endif

