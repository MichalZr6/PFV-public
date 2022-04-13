#include "Globals.h"

FvList Globals::fv_list(NEW_XLS_ENTRIES_COUNT);
std::vector<std::unique_ptr<FvInfo>> Globals::vecFvFromImg;
std::set<ScannedFile> Globals::files;
std::set<ScannedFile>::const_iterator Globals::curr_file;
std::map<unsigned short int, std::wstring> Globals::currShown;
std::vector<std::unique_ptr<FvInfo>> Globals::vecSplittedFvs;
std::unique_ptr<FvSplit> Globals::fvSplitter;

void Globals::SearchCompany(const std::wstring &name, 
	std::unordered_set<std::wstring> &comp_set)
{
	for (auto it = Globals::vecFvFromImg.cbegin(); 
		it != Globals::vecFvFromImg.cend(); ++it)
	{
		if (str_tolower((*it)->GetCompany()).find(str_tolower(name)) != std::wstring::npos)
			comp_set.insert((*it)->GetCompany());
	}
}
void Globals::SearchInvestition(const std::wstring &name,
	std::unordered_set<std::wstring>& inv_set)
{
	for (auto it = Globals::vecFvFromImg.cbegin(); 
		it != Globals::vecFvFromImg.cend(); ++it)
	{
		if (str_tolower((*it)->GetInvestition()).find(str_tolower(name)) != std::wstring::npos)
			inv_set.insert((*it)->GetInvestition());
	}
}
