#pragma once

#include "dirent.h"
#include <errno.h>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include "FvClasses.h"

typedef System::String^ USTRING;

class ScannedFile;

int getdir(std::string dir, std::vector<ScannedFile> &files, bool recursive = false);
USTRING FvToOutput(const FvInfo & fv_info);
bool CheckPayment(const FvInfo &fv);