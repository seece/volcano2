/* Operating system specific functionality. */
#ifndef __system_h
#define __system_h

#include <string>
#include <vector>

std::vector<std::string> getDirectoryFilenames(std::string dir);
void openSystemConsole(); // for windows systems

#endif