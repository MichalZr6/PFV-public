/*
 * Functions.h
 *
 *  Created on: 2010-04-11
 * 
 */

#pragma once

#include <msclr\marshal_cppstd.h>

#include <cassert>
#include <algorithm>
#include <codecvt>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>

#include "dirent.h"

std::vector<std::string> &split(const std::string &s, char delim, std::vector<std::string> &elems);    
std::vector<std::string> split(const std::string &s, char delim);                                       

void addZeros(std::string &str);
bool is_number(const std::string& s, char pt = ',');
int getdir(std::string dir, std::vector<std::string> &files, bool recursive = false);
std::string GetExtFromStr(std::string s);		// returns string after last '.' - 
														// must be checked if its the extension

std::string & str_toupper(std::string &str);
std::wstring & wstr_toupper(std::wstring &wstr);
std::string & str_tolower(std::string &s);
std::wstring & wstr_tolower(std::wstring &ws);

std::wstring erase_strange_chars(const std::wstring &str);
bool ComparePathStrings(std::wstring path, std::wstring other);
                    
std::string & EraseWtSpaces(std::string &str);
std::wstring StringToWString(const std::string& s);
std::string WStringToString(const std::wstring& s);


//// Funkcje dla Visual Studio ///////////

typedef System::String^ USTRING;
 _NODISCARD std::string ustrtostr(const USTRING &u_str);
 _NODISCARD std::wstring ustrtowstr(const USTRING &u_wstr);
 _NODISCARD USTRING strtoustr(const std::string &std_str);
 _NODISCARD USTRING wstrtoustr(const std::wstring &std_wstr);
