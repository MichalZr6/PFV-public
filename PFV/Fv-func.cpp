#include "Fv-func.h"


int getdir(std::string dir, std::vector<ScannedFile> &files, bool recursive)
{
	std::vector<ScannedFile> r_files;
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
			getdir(dirp->d_name, r_files, true);
			files.insert(files.end(), r_files.begin(), r_files.end());
		}
		else if (dirp->d_type == DT_REG)
			files.emplace_back(StringToWString(dirp->d_name), L"", GetExtFromStr(dirp->d_name));
	}
	closedir(dp);
	return 0;
}

USTRING FvToOutput(const FvInfo & fv_info)
{
	std::wstring output_wstr = fv_info.file->old_name.empty() ? L"Brak pliku skanu, " : L"Skan o nazwie:\t" + fv_info.file->old_name + L"";
	output_wstr += L"\nFirma: \t\t" + fv_info.company
		+ L"\t\tNr FV:\t\t" + fv_info.FVident
		+ L"\nData:\t\t" + StringToWString(fv_info.GetFvFullDate())
		+ L"\tInwestycja:\t" + fv_info.investition
		+ L"\nOpis:\t\t" + fv_info.description
		+ L"\nKomentarz:\t" + fv_info.comments;
	std::string output_str = CheckPayment(fv_info) ? "\nKto p³aci³:\t" + fv_info.whoPayed + "\t\tStatus:\t" + fv_info.payment :
		"\nTermin p³atnoœci:\t" + fv_info.payment.substr(3, fv_info.payment.size());
	output_str += "\nWartoœæ netto:\t" + fv_info.net_value.GetPriceStrCurr()
		+ "\t\tWartoœæ brutto:\t" + fv_info.gross_value.GetPriceStrCurr() + "\n\n";

	return wstrtoustr(output_wstr) + strtoustr(output_str);
}

bool CheckPayment(const FvInfo &fv)
{
	if (!fv.GetPayment().empty() && fv.GetPayment()[0] == 'T')	// tylko faktura oznaczona jako np. "T: 21.12.2018" nie jest op³acona
		return false;
	else
		return true;
}