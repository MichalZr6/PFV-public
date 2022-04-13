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

#include "conversion.hpp"
#include "dirent.h"
#include "Price.h"

#define _SILENCE_CXX17_CODECVT_HEADER_DEPRECATION_WARNING
// for std::wstring_convert from <codecvt> deprecated in C++17

class FvInfo;

typedef System::String^ USTRING;

std::vector<std::string> &split(const std::string &s, char delim, std::vector<std::string> &elems);    
std::vector<std::string> split(const std::string &s, char delim);                                       

void addZeros(std::string &str);
bool is_number(const std::string& s, char pt = ',');
int getdir(std::string dir, std::vector<std::string> &files, bool recursive = false);
std::string GetExtFromStr(const std::string &s);		// returns string after last '.' - 
														// must be checked if its the extension

std::string& to_upper(std::string &str);
std::string str_tolower(std::string s);
std::wstring str_tolower(std::wstring ws);

std::wstring erase_strangers(const std::wstring &str);
bool ComparePathStrings(std::wstring path, std::wstring other);
                    
std::string & EraseWtSpaces(std::string &str);
std::wstring StringToWString(const std::string& s);
std::string WStringToString(const std::wstring& s);


//// Funkcje dla Visual Studio ///////////

 _NODISCARD std::string ustrtostr(const USTRING &u_str);
 _NODISCARD std::wstring ustrtowstr(const USTRING &u_wstr);
 _NODISCARD USTRING strtoustr(const std::string &std_str);
 _NODISCARD USTRING wstrtoustr(const std::wstring &std_wstr);

 void AutoFillOtherPriceTBox(System::Windows::Forms::TextBox ^ from_tb,
	 System::Windows::Forms::TextBox ^into_tb, short tax);
 short GetTaxFromCBox(System::Windows::Forms::ComboBox ^cbox);
