/*
 *  Functions.cpp
 *
 *  Created on: 2010-04-11
 *  
 */

#include "Functions.h"

 std::vector<std::string> &split(const std::string &s, char delim, std::vector<std::string> &elems)
{
    std::stringstream ss(s);
    std::string item;
    while (std::getline(ss, item, delim)) {
        elems.push_back(item);
    }
    return elems;
}

 std::vector<std::wstring> &split(const std::wstring &s, wchar_t delim, std::vector<std::wstring> &elems)
{
    std::wstringstream wss(s);
    std::wstring item;
    while (std::getline(wss, item, delim)) {
        elems.push_back(item);
    }
    return elems;
}

 std::vector<std::string> split(const std::string &s, char delim)
{
    std::vector<std::string> elems;
    split(s, delim, elems);
    return elems;
}

void addZeros(std::string &str)
{
    if(str.empty()) return ;

    size_t pos = str.find(',');
    if(str.size()-pos == 2 && str.size() != 1)
        str += "0";
    else if(str.size()-pos == 1)
        str += "00";
    else if(pos == std::string::npos)
    {
        pos = str.find('.');
        if(pos != std::string::npos)
            str[pos] = ',';
        else
            str += ",00";

        if(str.size()-pos == 2)
            str += "0";
        else if(str.size()-pos == 1)
            str += "00";
    }
}

bool is_number(const std::string& s, char pt)
{
    int found_point = 0;
	std::string tmp = s;
	EraseWtSpaces(tmp);
	size_t i = 0;
	if (tmp[i] == '-') i++;
    for(; i<tmp.size(); i++)
    {
        if(tmp[i] == pt)
            found_point++;
        else if(tmp[i] < 48 || tmp[i] > 57)
            return false;
    }
    if(found_point > 1)
        return false;
    else return true;
}

int getdir(std::string dir, std::vector<std::string> &files, bool recursive)
{
	int error;
	std::vector<std::string> r_files;
	DIR *dp;
	struct dirent *dirp;

	if ((dp = opendir(dir.c_str())) == NULL)
		return errno;

	while ((dirp = readdir(dp)) != NULL)
	{
		if (dirp->d_type == DT_DIR && recursive 
			&& static_cast<std::string>(dirp->d_name) != "." 
			&& static_cast<std::string>(dirp->d_name) != "..")
		{
			error = getdir(static_cast<std::string>(dirp->d_name), r_files, true);
			if (error != 0) return error;
			files.insert(files.end(), r_files.begin(), r_files.end());
		}
		else if (dirp->d_type == DT_REG)
			files.emplace_back(dirp->d_name);
	}
	closedir(dp);
	return 0;
}

 std::string GetExtFromStr(const std::string & s)
{
	auto pos = s.find_last_of('.');
	if (pos != std::string::npos)
		return s.substr(pos, s.length() - pos);
	else
		return "";
}

 std::string& to_upper(std::string &str)
 {
	 std::transform(str.begin(), str.end(), str.begin(), [](unsigned char c) { return toupper(c); });
	 return str;
 }

 std::string str_tolower(std::string s)
{
    std::transform(s.begin(), s.end(), s.begin(), [](unsigned char c){ return tolower(c); });
    return s;
}

 std::wstring str_tolower(std::wstring ws)
{
	std::transform(ws.begin(), ws.end(), ws.begin(), [](wchar_t c) { return tolower(c); });
	return ws;
}

double stringtod(std::string str)
{
	double liczba = 0.0;

	std::stringstream ss(str);
	ss >> liczba;
	if (!ss)
	{
		return 0.0;
	}
	else
		return liczba;
}

int strtoint(std::string surowa_zm)
{
	int liczba = 0;

	std::stringstream ss(surowa_zm);
	ss >> liczba;
	if (!ss)
	{
	    std::cout << surowa_zm << " to nie liczba!" << std::endl;
	    return 0;
	}
	else
	    return liczba;
}


std::wstring erase_strangers(const std::wstring &str)
{
	std::wstring s{ L"" };
	const std::wstring pl_chars{ L"QWERTYUIOPLKJHGFDSAZXCVBNMŻŹĆŃŁÓŚĄĘqwertyuioplkjhgfdsazxcvbnmąęśćżźńłóę" };

	for (size_t i = 0; i < str.size(); ++i)
	{
		if ((str[i] >= 48 && str[i] <= 57) || pl_chars.find(str[i]) != std::wstring::npos)
			s += str[i];
	}
	return s;
}

bool ComparePathStrings(std::wstring path, std::wstring other)
{
	int result{ 0 };

	if (path.size() == 0 || other.size() == 0)
		return false;

	// get rid of extension
	auto pos = path.find_last_of(L'.');
	if (pos != std::string::npos)
		path.erase(pos, path.size() - pos);

	erase_strangers(path);
	erase_strangers(other);

	if (path == other)
		return true;
	else
		return false;
}

std::string & EraseWtSpaces(std::string & str)
{
	str.erase(remove_if(str.begin(), str.end(), isspace), str.end());
	return str;
}

 std::wstring StringToWString(const std::string& s)
{
	 std::locale loc(".1250");
	auto &cctv = std::use_facet<std::codecvt<wchar_t, char, std::mbstate_t>>(loc);
	std::wstring_convert<std::codecvt<wchar_t, char, std::mbstate_t>> converter(&cctv);
	return converter.from_bytes(s);
}

 std::string WStringToString(const std::wstring& s)
{
	 std::locale loc(".1250");
	auto &cctv = std::use_facet<std::codecvt<wchar_t, char, std::mbstate_t>>(loc);
	std::wstring_convert<std::codecvt<wchar_t, char, std::mbstate_t>> converter(&cctv);
	return converter.to_bytes(s);
}

//////// Visual Studio Functions //////////

 USTRING strtoustr(const std::string &std_str)
{
	return gcnew System::String(std_str.c_str());
}

 USTRING wstrtoustr(const std::wstring &std_wstr)
{
	return gcnew System::String(std_wstr.c_str());
}

 void AutoFillOtherPriceTBox(System::Windows::Forms::TextBox ^ from_tb, 
			System::Windows::Forms::TextBox ^ into_tb, short tax)
 {
	 if (System::String::IsNullOrWhiteSpace(from_tb->Text))
		 return;
	 auto p = std::make_unique<Price>();

	 try
	 {
		 p->SetPrice(ustrtostr(from_tb->Text));

		 if (from_tb->Name->Contains("Gross"))
			 p->SetPrice(p->GetPrice() / Price(tax/100.0+1.0));
		 else if (from_tb->Name->Contains("Net"))
			 p->SetPrice(p->GetPrice() * Price(tax/100.0+1.0));
		 else
			 assert("The function " + __FUNCTION__ + " cannot distinguish Gross or Net value");
	 }
	 catch (const std::domain_error &err)
	 {
		 System::Windows::Forms::MessageBox::Show(strtoustr(err.what()));
	 }
	 into_tb->Text = strtoustr(p->GetPriceStr());
	 into_tb->SelectAll();
 }

 short GetTaxFromCBox(System::Windows::Forms::ComboBox ^ cbox)
 {
	 short tax;

	 try
	 {
		 if (cbox->Text == "oo")
			 tax = 0;
		 else
			 tax = convert::numeric_cast<short>(ustrtostr(cbox->Text).c_str());
	 }
	 catch (std::exception &e)
	 {
		 System::Windows::Forms::MessageBox::Show("Nieprawidłowy format liczby podatku VAT");
		 return 23;			// return default
	 }
	 return tax;
 }

 std::string ustrtostr(const USTRING &u_str)
{
	return msclr::interop::marshal_as<std::string>(u_str);
}

 std::wstring ustrtowstr(const USTRING &u_wstr)
{
	return msclr::interop::marshal_as<std::wstring>(u_wstr);
}