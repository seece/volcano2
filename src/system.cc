#include "system.h"

#ifdef _MSC_VER
std::vector<std::string> getDirectoryFilenames(std::string dir)
{
	std::vector<std::string> vec;

	/* FIXME Replace this placeholder function. */
	vec.push_back("map1.map");
	vec.push_back("map2.map");
	vec.push_back("map3.map");

	return vec;
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
#endif