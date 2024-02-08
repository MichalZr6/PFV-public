#include "FvClasses.h"

std::string FvInfo::static_month;
std::string FvInfo::static_year;

int ScannedFile::counter = 0;

using namespace System::Windows::Forms;

struct CompareFvDates
{
	inline bool operator () (const Fv_ptr & fv1, const Fv_ptr & fv2)
	{
		if (fv1->date.year > fv2->date.year)
			return true;
		if (fv1->date.year == fv2->date.year && fv1->date.month > fv2->date.month)
			return true;
		if (fv1->date.year == fv2->date.year && fv1->date.month == fv2->date.month &&
			fv1->date.day > fv2->date.day)
			return true;
		else
			return false;
	}
};

FvList::FvList(const USHORT rows_from_xls_end) : rfe(rows_from_xls_end)
{
	xls = std::make_unique<BasicExcel>();
	xls_out = std::make_unique<BasicExcel>();
}

std::string FvList::GetDataFromXlsFile(std::string fv_file_name, const short & rows_from_end)
{
	this->file_name = fv_file_name;
	this->rows_from_end = rows_from_end;

	if (!xls->Load(fv_file_name.c_str()))
	{
		MessageBox::Show(strtoustr("B³¹d wczytywania pliku: " + fv_file_name 
			+ ". SprawdŸ czy plik jest otwarty w innym programie.\nZadana iloœæ wierszy do wczytania: " 
			+ std::to_string(rows_from_end)));
		Application::Exit();
	}

	sheet = xls->GetWorksheet(0);
	xls_out->New(1);

	std::string prev_date = "", warnings = "";

	for (int i = sheet->GetTotalRows() - 1; i >= sheet->GetTotalRows() - rows_from_end; i--)
	{
		try {
			auto temp_info = std::make_unique<FvInfo>();
			temp_info->ResetWarnings();
			temp_info->SetCompanyAndIdent(sheet->Cell(i, COLS::FV_IDENT), sheet->Cell(i, COLS::COMPANY));
			temp_info->SetDescription(sheet->Cell(i, COLS::DESCRIPTION));
			if (!sheet->Cell(i, COLS::DATE_COL)->GetDate().empty())
			{
				prev_date = sheet->Cell(i, COLS::DATE_COL)->GetDate();
				temp_info->SetDate(sheet->Cell(i, COLS::DATE_COL));
			}
			else
			{
				if (prev_date.empty())
					prev_date = prev_date + "01" + FvInfo::static_month + "." + FvInfo::static_year;
				else
					temp_info->SetDate(prev_date);
			}
			temp_info->SetInvestition(sheet->Cell(i, COLS::INVESTITION));
			temp_info->net_value.SetPrice(sheet->Cell(i, COLS::NETVAL)->GetDouble());
			temp_info->gross_value.SetPrice(sheet->Cell(i, COLS::GROSVAL)->GetDouble());
			temp_info->SetPayingPerson(sheet->Cell(i, COLS::WHO_PAYED)->GetText());
			temp_info->SetPayment(sheet->Cell(i, COLS::PAYMENT_STATUS)->GetText());
			temp_info->comments = sheet->Cell(i, COLS::COMMENTS)->GetText();
			warnings += temp_info->GetWarnings();
			this->vecOldFvInfo.push_back(std::move(temp_info));
		}
		catch (std::exception& e)
		{
			std::cout << e.what() << std::endl;
		}
	}
	return warnings;
}

void FvList::SearchForCompany(std::wstring fname, std::unordered_set<std::wstring> &comp_set)
{
	for (auto const &fvFromXls : this->vecOldFvInfo)
	{
		if (wstr_tolower(fvFromXls->GetCompany()).find(wstr_tolower(fname)) != std::wstring::npos)
			comp_set.insert(fvFromXls->GetCompany());
	}
}

void FvList::SearchInvestition(std::wstring invest, std::unordered_set <std::wstring> &inv_set)
{
	for (auto const &fvFromXls : this->vecOldFvInfo)
	{
		if (wstr_tolower(fvFromXls->GetInvestition()).find(wstr_tolower(invest)) != std::wstring::npos)
			inv_set.insert(fvFromXls->GetInvestition());
	}
}

std::string FvList::GetLatestDate() const
{
	if (this->vecOldFvInfo.empty())
		return "0";
	else
		return this->vecOldFvInfo.front()->GetFvFullDate();
}

std::string FvList::GetOldestDate() const
{
	if (this->vecOldFvInfo.empty())
		return "0";
	else
		return this->vecOldFvInfo.back()->GetFvFullDate();
}

size_t FvList::GetSize() const
{
	return this->vecOldFvInfo.size();
}

void FvList::DrawDateSeparator(USHORT row, const rFvIter &it)
{
	if (CheckDates(it))
	{
		cfmt->set_borderlines(EXCEL_LS::EXCEL_LS_NO_LINE, EXCEL_LS::EXCEL_LS_NO_LINE,
			EXCEL_LS::EXCEL_LS_THIN, EXCEL_LS::EXCEL_LS_NO_LINE, 1, 1);
		cfmt->set_alignment(EXCEL_HALIGN_CENTRED);
		for (int col = 0; col < sheet_out->GetTotalCols(); ++col)
		{
			sheet_out->Cell(row, col)->SetFormat(*cfmt);
		}
	}

	cfmt->set_borderlines(0);
}

void FvList::SetNewEntryBgColor(USHORT row, USHORT col, const rFvIter& it, bool is_new_fv)
{
	if (is_new_fv)
		cfmt->set_background(MAKE_COLOR2(ExcelFormat::EGA_CYAN, 0));
	else
		cfmt->set_background(0, 0x20C0);			// default color

	cfmt->set_alignment(EXCEL_VALIGN_CENTRED);
	sheet_out->Cell(row, col)->SetFormat(*cfmt);
	cfmt->set_alignment(EXCEL_HALIGN_LEFT);
	sheet_out->Cell(row, col)->SetFormat(*cfmt);

	cfmt->set_background(0, 0x20C0);			// default color
}

void FvList::PrepareXLSData(const VecFv_ptr &vecNewFvs)
{
	// Merge UI data with already loaded .xls records
	std::copy(vecNewFvs.begin(), vecNewFvs.end(), std::back_inserter(vecOldFvInfo));

	// Sort by date in Excel-style
	std::sort(vecOldFvInfo.begin(), vecOldFvInfo.end(), CompareFvDates());

	// below is no good, the duplicates can be not adjacent which is required with std::unique
	// 
	//int s = vecOldFvInfo.size();

	//VecFv_ptr unique_fv_vec(vecOldFvInfo.begin(), std::unique(vecOldFvInfo.begin(), vecOldFvInfo.end(), [](const Fv_ptr& fv1, const Fv_ptr& fv2) {
	//	return fv1->date == fv2->date && fv1->GetInvoiceNumber() == fv2->GetInvoiceNumber() && fv1->GetInvestition() == fv2->GetInvestition();
	//	}));

	//vecOldFvInfo = std::move(unique_fv_vec);

	//MessageBox::Show(strtoustr("Got rid of "+ std::to_string(s - vecOldFvInfo.size()) + " duplicates."));

	sheet_out = xls_out->GetWorksheet(0);
	xfmg = std::make_unique<XLSFormatManager>(*xls_out);
	ExcelFont ft;
	ft.set_height(200);			// do sprawdzenia !!!!
	ft.set_font_name(L"Calibri");
	cfmt = std::make_unique<CellFormat>(*xfmg, ft);
	CellFormat cf(*xfmg);
	cf.set_font(ft);
	cf.set_alignment(EXCEL_ALIGNMENT::EXCEL_HALIGN_CENTRED | EXCEL_ALIGNMENT::EXCEL_VALIGN_CENTRED);
	CellFormat date_fmt(*xfmg);
	date_fmt.set_format_string("DD.MM.YYYY");

	USHORT row = 0;

	for (auto &it = vecOldFvInfo.rbegin()+1; it != vecOldFvInfo.rend(); ++it)
	{
		if ((*it)->GetMonthNumber() && it >= vecOldFvInfo.rend()-rfe)
		{
			//sheet_out->Cell(row, DATE_COL)->SetFormat(date_fmt);
			sheet_out->Cell(row, DATE_COL)->SetString((*it)->GetFvFullDate().c_str());
			sheet_out->Cell(row, INVESTITION)->SetFormat(cf);
			sheet_out->Cell(row, DESCRIPTION)->SetFormat(cf);
			sheet_out->Cell(row, FV_IDENT)->SetFormat(cf);
			sheet_out->Cell(row, NETVAL)->SetFormat(cf);
			sheet_out->Cell(row, GROSVAL)->SetFormat(cf);
			sheet_out->Cell(row, WHO_PAYED)->SetFormat(cf);
			//DrawDateSeparator(row, it);			<-- works but causes formatting issues in xls file
			sheet_out->Cell(row, COMPANY)->Set((*it)->GetCompany().c_str());
			sheet_out->Cell(row, INVESTITION)->Set((*it)->GetInvestition().c_str());
			sheet_out->Cell(row, DESCRIPTION)->Set((*it)->description.c_str());
			sheet_out->Cell(row, FV_IDENT)->Set((*it)->GetInvoiceNumber().c_str());
			sheet_out->Cell(row, NETVAL)->Set((*it)->net_value.GetPrice());
			sheet_out->Cell(row, GROSVAL)->Set((*it)->gross_value.GetPrice());
			sheet_out->Cell(row, WHO_PAYED)->Set((*it)->GetPayingPerson().c_str());
			sheet_out->Cell(row, PAYMENT_STATUS)->Set((*it)->GetPayment().c_str());
			sheet_out->Cell(row, COMMENTS)->Set((*it)->comments.c_str());
			bool is_new = std::find(vecNewFvs.rbegin(), vecNewFvs.rend(), *it) != vecNewFvs.rend();
			if (is_new) 
				sheet_out->Cell(row, COMMENTS+1)->Set("<---- NEW");

			row++;

			//System::Diagnostics::Debug::WriteLine("row: " + row);
		}
	}
}

bool FvList::CheckDates(const rFvIter &it)
// returns true if >it - 1< is the last entry in the given month
{
	if ((*it)->GetMonthNumber() != (*(it - 1))->GetMonthNumber())
		return true;
	else
		return false;
}

bool FvList::SaveToXLSFile(std::string fn, VecFv_ptr &vecNewFvs)
{
	PrepareXLSData(vecNewFvs);

	if(!xls_out->SaveAs(fn.c_str()))
		return false;

	return true;
}

////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////  END OF FvList Section //////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////  BEGIN OF FvInfo Section ////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////

FvInfo::FvInfo(const BasicExcelCell *ident_cell, const BasicExcelCell *comp_cell)
{
	this->err_msg = "";
	this->SetCompanyAndIdent(ident_cell, comp_cell);
}

FvInfo::FvInfo()
{
	this->invquantity = 1;
	this->err_msg = "";
}

FvInfo::FvInfo(const FvInfo & fvdoc)
{
	//MessageBox::Show(wstrtoustr(L"Copy constructor for [" + fvdoc.GetCompany() + L" + " + fvdoc.FVident));
	*this = fvdoc;
}

FvInfo::FvInfo(FvInfo && fvdoc)
{
	//MessageBox::Show(wstrtoustr(L"Move constructor for [" + fvdoc.GetCompany() + L" + " + fvdoc.FVident));
	*this = std::move(fvdoc);
}

FvInfo::FvInfo(std::string company)
{
	this->invquantity = 1;
	this->err_msg = "";
	this->company = StringToWString(company);
}

FvInfo &FvInfo::operator=(const FvInfo &fvdoc)
{
	this->company = fvdoc.GetCompany();
	this->FVident = fvdoc.FVident;
	this->file = fvdoc.file;
	this->investition = fvdoc.GetInvestition();
	this->invquantity = fvdoc.invquantity;
	this->description = fvdoc.description;
	this->date = fvdoc.date;
	this->net_value.SetPrice(fvdoc.net_value.GetPrice());
	this->gross_value.SetPrice(fvdoc.gross_value.GetPrice());
	this->whoPayed = fvdoc.whoPayed;
	this->payment = fvdoc.payment;
	this->comments = fvdoc.comments;
	this->err_msg = fvdoc.GetWarnings();
	this->corrective = fvdoc.isCorrective();
	return *this;
}

FvInfo & FvInfo::operator=(FvInfo && fvdoc)
{
	this->company = std::move(fvdoc.GetCompany());
	this->FVident = std::move(fvdoc.FVident);
	this->file = std::move(fvdoc.file);
	this->investition = std::move(fvdoc.GetInvestition());
	this->invquantity = std::move(fvdoc.invquantity);
	this->description = std::move(fvdoc.description);
	this->date = std::move(fvdoc.date);
	this->net_value.SetPrice(fvdoc.net_value.GetPrice());
	this->gross_value.SetPrice(fvdoc.gross_value.GetPrice());
	this->whoPayed = std::move(fvdoc.whoPayed);
	this->payment = std::move(fvdoc.payment);
	this->comments = std::move(fvdoc.comments);
	this->err_msg = std::move(fvdoc.GetWarnings());
	this->corrective = fvdoc.isCorrective();
	return *this;
}

bool FvInfo::operator<(FvInfo & fvdoc)
{
	return this->GetDayNumber() < fvdoc.GetDayNumber();
}

bool FvInfo::operator==(const FvInfo & fvdoc) const
{
	return (wstr_tolower(this->company + this->FVident) == wstr_tolower(fvdoc.company + fvdoc.FVident));
}

void FvInfo::SetCompanyAndIdent(const BasicExcelCell * ident_cell, const BasicExcelCell * comp_cell)
{
	this->invquantity = 0;
	auto val = ident_cell->GetText();
	if (val.empty())
		this->err_msg += "Komórka numeru faktury: " + ident_cell->GetRowCol() + " - pusta wartoœæ.\n";
	else
		this->FVident = val;

	val = comp_cell->GetText();
	if (val.empty())
		this->err_msg += "Komórka nazwy firmy: " + ident_cell->GetRowCol() + " - pusta wartoœæ.\n";
	else
		this->company = val;
}

FvInfo &FvInfo::operator-=(const FvInfo &fvdoc)
{
	this->net_value.SetPrice(this->net_value.GetPrice() - fvdoc.net_value.GetPrice());

	this->gross_value.SetPrice(this->gross_value.GetPrice() - fvdoc.gross_value.GetPrice());

	return *this;
}

void FvInfo::SetFile(const ScannedFile *f)
{
	if (f->old_name.empty())
		MessageBox::Show("FvInfo::SetFile(f) -> [f.old_name] is empty");

	this->file = f;
}

void FvInfo::SetDescription(const BasicExcelCell *cell)
{
	this->description = cell->GetText();
}

void FvInfo::SetDescription(std::wstring descr)
{
	this->description = descr;
}

void FvInfo::SetInvestition(const BasicExcelCell *cell)
{
	auto val = cell->GetText();
	if (val.empty())
		this->err_msg += "Komórka inwestycji: " + cell->GetRowCol() + " - pusta wartoœæ komórki.\n";
	else
		this->investition = val;
}

std::string FvInfo::GetFvFullDate() const
{
	return this->date.GetFullDate();
}

USHORT FvInfo::GetDayNumber() const
{
	if (this->date.isValid())
		return this->date.day;
	else
	{
		//MessageBox::Show(wstrtoustr(L"W funkcji [GetDayNumber] -> firma [numer faktury] = "
			//+ this->company +L"["+ this->FVident +L"] nie posiada prawid³owej daty."));
		return 0;
	}
}

USHORT FvInfo::GetMonthNumber() const
{
	if (this->date.isValid())
		return this->date.month;
	else
	{
		//MessageBox::Show(wstrtoustr(L"W funkcji [GetDayNumber] -> firma [numer faktury] = " + 
			//this->company + L"[" + this->FVident + L"] nie posiada prawid³owej daty, tj:\n") 
			//+ System::Convert::ToString(this->date.month));
		return 0;
	}
}

const ScannedFile* FvInfo::GetFile() const
{
	return this->file;
}

std::wstring FvInfo::GetCompany() const
{
	return this->company;
}

std::wstring FvInfo::GetFvIdent() const
{
	return this->FVident;
}

std::wstring FvInfo::GetInvestition() const
{
	return this->investition;
}

std::string FvInfo::GetPayment() const
{
	return this->payment;
}

std::string FvInfo::GetPayingPerson() const
{
	return this->whoPayed;
}

std::wstring FvInfo::GetInvoiceNumber() const
{
	return this->FVident;
}

std::string FvInfo::GetWarnings() const
{
	return this->err_msg;
}

bool FvInfo::isCorrective() const
{
	return corrective;
}

void FvInfo::ResetWarnings()
{
	this->err_msg = "";
}

bool FvInfo::ValidatePaymentFormat(std::string pay)
{
	str_toupper(pay);
	
	if (pay[0] == 'G' || pay[0] == 'P' || pay[0] == 'T' || pay == "KARTA")
		return true;
	else
		return false;
}

void FvInfo::IndicateFVisCorrective()
{
	if (gross_value < Price(0) && net_value < Price(0))
		corrective = true;
	else
		corrective = false;
}

void FvInfo::SetDate(BasicExcelCell *cell)
{
	if (!cell->GetDate().empty())
		this->date.SetDate(cell->GetDate());
	else
	{
		MessageBox::Show("Komórka cell[row, col] = ["+ cell->GetRow() +", "+ cell->GetCol() 
			+"]\nw funkcji FvInfo::SetDate(BasicExcelCell)\nnie zawiera poprawnej daty");
		return;
	}
}

void FvInfo::SetDate(std::string date)
{
	this->date.SetDate(date);
}

void FvInfo::SetPayingPerson(std::wstring person)
{
	SetPayingPerson(WStringToString(person));
}

void FvInfo::SetPayingPerson(std::string person)
{
	if (person.size() > max_whopayed_size)
		return;

	this->whoPayed = person;
	str_toupper(this->whoPayed);
}

void FvInfo::SetPayment(std::wstring pay)
{
	SetPayment(WStringToString(pay));
}

void FvInfo::SetPayment(std::string pay)
{
	if (pay.length() > max_payment_size)
	{
		this->err_msg += "Pominiêto status p³atnoœci. Napis zbyt d³ugi ["+ pay +"].\n";
		return;
	}
	else if (pay.empty())
		return;
	else if (!this->ValidatePaymentFormat(pay))
	{
		this->err_msg += "Nieprawid³owy format statusu p³atnoœci: ["+ pay +"].\n";
		return;
	}
	else
		this->payment = pay;
}

void FvInfo::SetTax(std::string tax)
{
	if (tax == "mix")
	{
		this->tax = 0;
		return;
	}

	try
	{
		this->tax = convert::numeric_cast<short>(tax.c_str());
	}
	catch (...)
	{
		this->err_msg += "B³¹d konwersji ci¹gu znaków podatku VAT do liczby";
		return;
	}
}

void FvInfo::SetNetValue(std::string price_str)
{
	try
	{
		net_value.SetPrice(price_str);
	}
	catch (...)
	{
		MessageBox::Show("Nieprawid³owa wartoœæ netto");
	}

	IndicateFVisCorrective();

	if (gross_value != Price(0) && fabs(gross_value) < fabs(net_value))
		this->err_msg += "Brutto mniejsze od netto";
}

void FvInfo::SetGrossValue(std::string price_str)
{
	try
	{
		gross_value.SetPrice(price_str);
	}
	catch (...)
	{
		MessageBox::Show("Nieprawid³owa wartoœæ brutto");
	}

	IndicateFVisCorrective();

	if (net_value != Price(0) && fabs(gross_value) < fabs(net_value))
		this->err_msg += "Brutto mniejsze od netto";
}

void FvInfo::SetFvIdent(std::wstring fv_nr)
{
	this->FVident = fv_nr;
}

void FvInfo::SetCompany(std::wstring comp_name)
{
	if (comp_name.empty())
		MessageBox::Show("FvInfo::SetCompany val passed is empty");

	this->company = comp_name;
}

void FvInfo::SetInvestition(std::wstring inv)
{
	if (inv.empty())
		MessageBox::Show("FvInfo::SetInvestition val passed is empty");

	this->investition = inv;
}

////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////  END OF FvInfo Section //////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////  BEGIN OF DateStruct Section ////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////

DateStruct::DateStruct()
{
	this->day = 0;
	this->month = 0;
	this->year = 0;
}

DateStruct::DateStruct(std::string d, char delim)
{
	this->SetDate(d, delim);
}

DateStruct::DateStruct(unsigned short d, unsigned short m, unsigned short y)
{
	this->SetDate(d, m, y);
}

bool DateStruct::isValid() const
{
	if (this->day && this->month && this->year)
		return true;
	else
		return false;
}

std::string DateStruct::GetFullDate(char delim) const
{
	std::string ret_val = "";
	if (!isValid())
		return "";

	if (convert::string_cast(this->day).size() == 1)
		ret_val += "0";
	ret_val += convert::string_cast(this->day);
	ret_val += delim;
	if (convert::string_cast(this->month).size() == 1)
		ret_val += "0";
	ret_val += convert::string_cast(this->month);
	ret_val += delim;
	ret_val += convert::string_cast(this->year);

	return ret_val;
}

void DateStruct::SetDate(std::string d, char delim)
{
	std::regex reg("^([0-9]|0[1-9]|[12][0-9]|3[01])[.](0[1-9]|1[012])[.](20)\\d\\d$");
	if (!std::regex_match(d, reg))
	{
		this->day = 0;
		return;
	}

	if (d.empty())
	{
		this->day = 0;
		this->month = 0;
		this->year = 0;
		return;
	}

	if (!is_number(d.substr(0, 1)) && d.size() != 10 && d.find(delim) != 2 && d.find_last_of(delim) != 5)
	{
		this->day = 0;
		this->month = 0;
		this->year = 0;
		return;
	}
	else /// DD.MM.YYYY
	{
		this->day = convert::numeric_cast<USHORT>(d.substr(0, 2).c_str());
		this->month = convert::numeric_cast<USHORT>(d.substr(3, 2).c_str());
		this->year = convert::numeric_cast<USHORT>(d.substr(6, 4).c_str());
	}
}

void DateStruct::SetDate(unsigned short d, unsigned short m, unsigned short y)
{
	if (d <= 0 || d >= 32 || m <= 0 || m >= 13 || y <= 2000 || y >= 2050)
	{
		this->day = 0;
		this->month = 0;
		this->year = 0;
	}
	else
	{
		this->day = d;
		this->month = m;
		this->year = y;
	}
}

////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////  END OF DateStruct Section //////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////  BEGIN OF Other Section /////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////