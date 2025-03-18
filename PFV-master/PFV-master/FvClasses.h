#pragma once

#include <vcclr.h>
#include <functional>
#include <string>
#include <vector>
#include <unordered_set>
#include "../../myIncludes/ExcelFormat.h"
#include "../../myIncludes/Price.h"
#include "Fv-func.h"

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
const short max_payment_size = 15;

class ScannedFile 
{

public:
	std::wstring old_name{ L"" };
	mutable std::wstring new_name{ L"" };
	mutable bool is_fv{ true };

	ScannedFile() {}

	ScannedFile(const std::wstring &old_n, const std::wstring &new_n, const std::string &ext) :
		old_name(old_n), new_name(new_n), extension(ext) 
	{
		if(new_n.empty())
			this->SetDefaultNewName();
	}

	ScannedFile(const std::wstring &old_n, const std::wstring &new_n) :
		old_name(old_n), new_name(new_n)
	{
		if (new_n.empty())
			this->SetDefaultNewName();
		this->extension = "";
	}
	
	void SetExtension(const std::string &s)
	{
		this->extension = str_tolower(s);
	}

	void SetDefaultNewName() const
	{
		this->new_name = L"plik" + std::to_wstring(counter++);
	}

	std::wstring GetExtension() const
	{
		return StringToWString(extension);
	}

	bool operator<(const ScannedFile &f) const 
	{
		if (this->old_name == f.old_name || this->new_name == f.new_name)
			return false;

		return this->old_name < f.old_name;

	}

private:
	static int counter;
	std::string extension;
};

struct DateStruct
{
public:
	DateStruct();
	DateStruct(const std::string& d, char delim = '.');
	DateStruct(unsigned short d, unsigned short m, unsigned short y);

	unsigned short day;
	unsigned short month;
	unsigned short year;

	bool isValid() const;

	std::string GetFullDate(char delim = '.') const;

	void SetDate(const std::string& d, char delim = '.');
	void SetDate(unsigned short d, unsigned short m, unsigned short y);

private:

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
	FvInfo(const std::string &company);
	FvInfo(const BasicExcelCell *ident_cell, const BasicExcelCell *comp_cell);

	// Operators:
	FvInfo &operator -= (const FvInfo &fvdoc);
	FvInfo &operator = (const FvInfo &fvdoc);
	FvInfo &operator = (FvInfo &&fvdoc);
	bool operator < (FvInfo &fvdoc);
	bool operator == (const FvInfo &fvdoc) const;
	
	// Setters:
	void SetCompanyAndIdent(const BasicExcelCell *ident_cell, const BasicExcelCell *comp_cell);
	void SetNetValue(const std::string &price_str);
	void SetGrossValue(const std::string &price_str);
	void SetInvestition(const std::wstring &inv);
	void SetInvestition(const BasicExcelCell *cell);
	void SetDescription(const std::wstring &descr);
	void SetDescription(const BasicExcelCell *cell);
	void SetFile(const ScannedFile &f);
	void SetCompany(const std::wstring &comp_name);
	void FvInfo::SetFvIdent(const std::wstring &fv_nr);
	void SetDate(BasicExcelCell *cell);
	void SetDate(const std::string &date);
	void SetPayingPerson(const std::string &person);
	void SetPayment(const std::string &pay);
	void SetTax(const std::string &tax);

	// Getters:
	std::string GetFvFullDate() const;
	USHORT GetDayNumber() const;
	USHORT GetMonthNumber() const;
	std::wstring GetCompany() const;
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
	ScannedFile file;
	std::wstring FVident;
	std::wstring investition;
	std::vector<std::wstring> investitions;
	std::string whoPayed;
	std::string payment;
	std::string err_msg;

	bool ValidatePaymentFormat(std::string pay);
	void IndicateFVisCorrective();
};

typedef std::reverse_iterator<std::vector<std::unique_ptr<FvInfo>>::iterator> rFvIter;

class FvList
{
public:

	std::string file_name;
	short rows_from_end;
	std::vector<std::unique_ptr<FvInfo>> vecOldFvInfo;
	
	FvList() = delete;
	FvList(const USHORT rows_from_xls_end);

	std::string GetDataFromXlsFile(const std::string &fv_file_name, const short &rows_from_end);		// returns warnings string
	bool SaveToXLSFile(const std::string &, std::vector<std::unique_ptr<FvInfo>> &vecNewFvs);
	void SearchForCompany(const std::wstring &fname, std::unordered_set<std::wstring> &comp_set);
	void SearchInvestition(const std::wstring &invest, std::unordered_set<std::wstring> &inv_set);
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
	void PrepareXLSData(std::vector<std::unique_ptr<FvInfo>> &vecNewFvs);
	inline bool CheckDates(const rFvIter &it);
};