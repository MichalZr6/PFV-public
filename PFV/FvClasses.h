#pragma once

#include <vcclr.h>
#include <functional>
#include <string>
#include <vector>
#include <regex>
#include <unordered_set>
#include "ExcelFormat.h"
#include "Price.h"
#include <filesystem>

// column indices in xls file
enum COLS {
	DATE_COL = 0,				// = A - date column index
	COMPANY = 1,				// = B - company column index
	INVESTITION = 2,			// = C - investition column index
	DESCRIPTION = 3,			// = D - description
	FV_IDENT = 4,				// = E - FVident = invoice identification number
	NETVAL = 5,					// = F - net value
	GROSVAL = 6,				// = G - gross value
	WHO_PAYED = 7,				// = H - who payed
	PAYMENT_STATUS = 8,			// = I - payment status
	COMMENTS = 9				// = J - comments
};

using namespace ExcelFormat;

const short max_whopayed_size = 8;
const short max_payment_size = 20;

struct DateStruct
{
public:
	DateStruct();
	DateStruct(std::string d, char delim = '.');
	DateStruct(unsigned short d, unsigned short m, unsigned short y);

	unsigned short day;
	unsigned short month;
	unsigned short year;

	bool isValid() const;

	std::string GetFullDate(char delim = '.') const;

	void SetDate(std::string d, char delim = '.');
	void SetDate(unsigned short d, unsigned short m, unsigned short y);

	inline bool operator >(System::DateTime& dt) const
	{
		if (year > dt.Year)
			return true;
		else
		{
			if (year == dt.Year && month > dt.Month)
				return true;
			else
			{
				if (year == dt.Year && month == dt.Month && day > dt.Day)
					return true;
			}
		}
		return false;
	}

	inline bool operator ==(const DateStruct& date) const
	{
		return date.day == day && date.month == month && date.year == year;
	}

	DateStruct (const std::filesystem::file_time_type& ftt)
	{
		using namespace std::chrono;
		auto sctp = time_point_cast<system_clock::duration>(ftt - std::filesystem::file_time_type::clock::now()
			+ system_clock::now());
		auto tt = system_clock::to_time_t(sctp);
		std::tm t = *std::localtime(&tt);
		std::stringstream ss;
		ss << std::put_time(&t, "%d.%m.%Y");
		*this = ss.str();
	}

private:

};

class ScannedFile 
{

public:
	std::wstring old_name{ L"" };
	mutable std::wstring new_name{ L"" };
	mutable bool is_fv{ true }; 
	DateStruct last_mod;

	ScannedFile() {}

	ScannedFile(std::wstring old_n, std::wstring new_n, std::string ext) :
		old_name(old_n), new_name(new_n), extension(ext) 
	{
		if(new_n.empty())
			SetDefaultNewName();
	}

	ScannedFile(std::wstring old_n, std::wstring new_n) :
		old_name(old_n), new_name(new_n)
	{
		if (new_n.empty())
			SetDefaultNewName();
		extension = "";
	}
	
	void SetExtension(std::string s)
	{
		extension = str_tolower(s);
	}

	void SetDefaultNewName() const
	{
		new_name = L"plik" + std::to_wstring(counter++);
	}

	std::wstring GetExtension() const
	{
		return StringToWString(extension);
	}

	bool operator<(const ScannedFile &f) const 
	{
		if (old_name == f.old_name || new_name == f.new_name)
			return false;

		return old_name < f.old_name;

	}

private:
	static int counter;
	std::string extension;
};

class FvInfo
{
public:

	static std::string static_month;
	static std::string static_year;

	Price gross_value;
	Price net_value;
	DateStruct date;
	unsigned short int invquantity;
	std::wstring comments;
	std::wstring description;

	// Constructors:
	FvInfo();
	FvInfo(const FvInfo &fvdoc);
	FvInfo(FvInfo &&fvdoc);
	FvInfo(std::string company);
	FvInfo(const BasicExcelCell *ident_cell, const BasicExcelCell *comp_cell);

	// Operators:
	FvInfo &operator -= (const FvInfo &fvdoc);
	FvInfo &operator = (const FvInfo &fvdoc);
	FvInfo &operator = (FvInfo &&fvdoc);
	bool operator < (FvInfo &fvdoc);
	bool operator == (const FvInfo &fvdoc) const;
	
	// Setters:
	void SetCompanyAndIdent(const BasicExcelCell *ident_cell, const BasicExcelCell *comp_cell);
	void SetNetValue(std::string price_str);
	void SetGrossValue(std::string price_str);
	void SetInvestition(std::wstring inv);
	void SetInvestition(const BasicExcelCell *cell);
	void SetDescription(std::wstring descr);
	void SetDescription(const BasicExcelCell *cell);
	void SetFile(const ScannedFile *f);
	void SetCompany(std::wstring comp_name);
	void FvInfo::SetFvIdent(std::wstring fv_nr);
	void SetDate(BasicExcelCell *cell);
	void SetDate(std::string date);
	void SetPayingPerson(std::string person);
	void SetPayingPerson(std::wstring person);
	void SetPayment(std::wstring pay);
	void SetPayment(std::string pay);
	void SetTax(std::string tax);

	// Getters:
	std::string GetFvFullDate() const;
	USHORT GetDayNumber() const;
	USHORT GetMonthNumber() const;
	const ScannedFile *GetFile() const;
	std::wstring GetCompany() const;
	std::wstring GetFvIdent() const;
	std::wstring GetInvestition() const;
	std::string GetPayment() const;
	std::string GetPayingPerson() const;
	std::wstring GetInvoiceNumber() const;
	std::string GetWarnings() const;
	bool isCorrective() const;

	void ResetWarnings();

	friend USTRING FvToOutput(const FvInfo & fv_info);

private:
	short tax = -1;
	bool corrective = false;
	std::wstring company;
	const ScannedFile *file;
	std::wstring FVident;
	std::wstring investition;
	std::vector<std::wstring> investitions;
	std::string whoPayed;
	std::string payment;
	std::string err_msg;

	bool ValidatePaymentFormat(std::string pay);
	void IndicateFVisCorrective();
};

using Fv_ptr = std::shared_ptr<FvInfo>;
using VecFv_ptr = std::vector<Fv_ptr>;
typedef std::reverse_iterator<VecFv_ptr::iterator> rFvIter;

class FvList
{
public:

	std::string file_name;
	short rows_from_end;
	VecFv_ptr vecOldFvInfo;
	
	FvList() = delete;
	FvList(const USHORT rows_from_xls_end);

	std::string GetDataFromXlsFile(std::string fv_file_name, const short &rows_from_end);		// returns warnings string
	bool SaveToXLSFile(std::string , VecFv_ptr &vecNewFvs);
	void SearchForCompany(std::wstring fname, std::unordered_set<std::wstring> &comp_set);
	void SearchInvestition(std::wstring invest, std::unordered_set<std::wstring> &inv_set);
	std::string GetLatestDate() const;
	std::string GetOldestDate() const;
	size_t GetSize() const;
	~FvList() = default;

private:
	USHORT rfe;	//rows_from_xls_end
	std::vector<std::string> vDatesFromXls;
	std::unique_ptr<BasicExcel> xls, xls_out;
	std::unique_ptr<XLSFormatManager> xfmg;
	std::unique_ptr<CellFormat> cfmt;
	std::unique_ptr<ExcelFont> xfont;
	BasicExcelWorksheet *sheet, *sheet_out;

	inline void DrawDateSeparator(USHORT row, const rFvIter &it);
	inline void SetPaymentBgColor(USHORT row, const rFvIter &it);
	inline void SetNewEntryBgColor(USHORT row, USHORT col, const rFvIter& it, bool is_new_fv);
	void PrepareXLSData(const VecFv_ptr &vecNewFvs);
	inline bool CheckDates(const rFvIter &it);
};