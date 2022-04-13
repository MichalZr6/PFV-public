#include "FvClasses.h"

std::string FvInfo::static_month;
std::string FvInfo::static_year;

int ScannedFile::counter = 0;

using namespace System::Windows::Forms;

struct CompareFvDates
{
	inline bool operator () (const std::unique_ptr<FvInfo> & fv1, const std::unique_ptr<FvInfo> & fv2)
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

std::string FvList::GetDataFromXlsFile(const std::string & fv_file_name, const short & rows_from_end)
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
	xls_out->New(*xls);

	std::string prev_date = "", warnings = "";

	for (int i = sheet->GetTotalRows() - 1; i >= sheet->GetTotalRows() - rows_from_end; i--)
	{
		auto temp_info = std::make_unique<FvInfo>();
		temp_info->ResetWarnings();
		temp_info->SetCompanyAndIdent(sheet->Cell(i, COLS::FV_IDENT), sheet->Cell(i, COLS::COMPANY));
		temp_info->SetDescription(sheet->Cell(i, COLS::DESCRIPTION));
		if (sheet->Cell(i, COLS::DATE_COL)->GetString())
		{
			prev_date = sheet->Cell(i, COLS::DATE_COL)->GetString();
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
		temp_info->SetPayingPerson(sheet->Cell(i, COLS::WHO_PAYED)->GetString() ? sheet->Cell(i, COLS::WHO_PAYED)->GetString() : "");
		temp_info->SetPayment(sheet->Cell(i, COLS::PAYMENT_STATUS)->GetString() ? sheet->Cell(i, COLS::PAYMENT_STATUS)->GetString() : "");
		temp_info->comments = sheet->Cell(i, COLS::COMMENTS)->GetWString() ? sheet->Cell(i, COLS::COMMENTS)->GetWString() : L"";
		warnings += temp_info->GetWarnings();

		this->vecOldFvInfo.push_back(std::move(temp_info));
	}
	return warnings;
}

void FvList::SearchForCompany(const std::wstring &fname, std::unordered_set<std::wstring> &comp_set)
{
	for (auto const &fvFromXls : this->vecOldFvInfo)
	{
		if (str_tolower(fvFromXls->GetCompany()).find(str_tolower(fname)) != std::wstring::npos)
			comp_set.insert(fvFromXls->GetCompany());
	}
}

void FvList::SearchInvestition(const std::wstring &invest, std::unordered_set <std::wstring> &inv_set)
{
	for (auto const &fvFromXls : this->vecOldFvInfo)
	{
		if (str_tolower(fvFromXls->GetInvestition()).find(str_tolower(invest)) != std::wstring::npos)
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

void FvList::SetPaymentBgColor(USHORT row, const rFvIter &it)
{
	std::string pstat{ (*it)->GetPayment() };
	if (pstat[0] == 'T' ||									// np. T: 11.10.2018     (termin p³atnoœci = nierozliczona faktura)
			pstat == "G" || pstat == "g")					// np. G lub g			(nierozliczona gotówka)
		cfmt->set_background(MAKE_COLOR2(EGA_YELLOW, 0));
	else
		cfmt->set_background(0, 0x20C0);			// default color
	
	cfmt->set_alignment(EXCEL_VALIGN_CENTRED);
	sheet_out->Cell(row, PAYMENT_STATUS)->SetFormat(*cfmt);
	cfmt->set_alignment(EXCEL_HALIGN_CENTRED);
	sheet_out->Cell(row, PAYMENT_STATUS)->SetFormat(*cfmt);
	
	cfmt->set_background(0, 0x20C0);			// default color
}

void FvList::PrepareXLSData(std::vector<std::unique_ptr<FvInfo>> &vecNewFvs)
{
	// Merge UI data with already loaded .xls records
	std::move(vecNewFvs.begin(), vecNewFvs.end(), std::back_inserter(vecOldFvInfo));
	// Sort by date in Excel-style
	std::sort(vecOldFvInfo.begin(), vecOldFvInfo.end(), CompareFvDates());

	sheet_out = xls_out->GetWorksheet(0);
	xfmg = std::make_unique<XLSFormatManager>(*xls_out);
	cfmt = std::make_unique<CellFormat>(*xfmg);

	USHORT row = 0;

	for (auto &it = vecOldFvInfo.rbegin()+1; it != vecOldFvInfo.rend(); ++it)
	{
		if ((*it)->GetMonthNumber() && it >= vecOldFvInfo.rend()-rfe)
		{
			sheet_out->Cell(row, DATE_COL)->SetString((*it)->GetFvFullDate().c_str());
			//DrawDateSeparator(row, it);			<-- works but causes formatting issues in xls file
			sheet_out->Cell(row, COMPANY)->Set((*it)->GetCompany().c_str());
			sheet_out->Cell(row, INVESTITION)->Set((*it)->GetInvestition().c_str());
			sheet_out->Cell(row, DESCRIPTION)->Set((*it)->description.c_str());
			sheet_out->Cell(row, FV_IDENT)->Set((*it)->GetInvoiceNumber().c_str());
			sheet_out->Cell(row, NETVAL)->Set((*it)->net_value.GetPrice());
			sheet_out->Cell(row, GROSVAL)->Set((*it)->gross_value.GetPrice());
			sheet_out->Cell(row, WHO_PAYED)->Set((*it)->GetPayingPerson().c_str());
			sheet_out->Cell(row, PAYMENT_STATUS)->Set((*it)->GetPayment().c_str());
			SetPaymentBgColor(row, it);
			sheet_out->Cell(row, COMMENTS)->Set((*it)->comments.c_str());

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

bool FvList::SaveToXLSFile(const std::string &fn, std::vector<std::unique_ptr<FvInfo>> &vecNewFvs)
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

FvInfo::FvInfo(const std::string &company)
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
	return (str_tolower(this->company + this->FVident) == str_tolower(fvdoc.company + fvdoc.FVident));
}

void FvInfo::SetCompanyAndIdent(const BasicExcelCell * ident_cell, const BasicExcelCell * comp_cell)
{
	this->invquantity = 0;

	if (ident_cell->Type() == BasicExcelCell::STRING) this->FVident = StringToWString(ident_cell->GetString());
	else if (ident_cell->Type() == BasicExcelCell::WSTRING) this->FVident = ident_cell->GetWString();
	else if (ident_cell->Type() == BasicExcelCell::INT) this->FVident = std::to_wstring(ident_cell->GetInteger());
	else if (ident_cell->Type() == BasicExcelCell::DOUBLE) this->FVident = std::to_wstring(ident_cell->GetDouble());
	else if (ident_cell->Type() == BasicExcelCell::UNDEFINED) this->err_msg += "Komórka " + ident_cell->GetRowCol() 
																				+ " numeru faktury jest pusta.\n";
	else this->err_msg += "Komórka "+ ident_cell->GetRowCol() + " nie zawiera prawid³owego numeru faktury.\n";

	if (comp_cell->Type() == BasicExcelCell::STRING) this->company = StringToWString(comp_cell->GetString());
	else if (comp_cell->Type() == BasicExcelCell::WSTRING) this->company = comp_cell->GetWString();
	else if (comp_cell->Type() == BasicExcelCell::UNDEFINED) this->err_msg += "Komórka " + ident_cell->GetRowCol() 
																			+ " nazwy firmy jest pusta.\n";
	else this->err_msg += "Komórka "+ ident_cell->GetRowCol() + " nie zawiera prawid³owej nazwy firmy.\n";
}

FvInfo &FvInfo::operator-=(const FvInfo &fvdoc)
{
	this->net_value.SetPrice(this->net_value.GetPrice() - fvdoc.net_value.GetPrice());

	this->gross_value.SetPrice(this->gross_value.GetPrice() - fvdoc.gross_value.GetPrice());

	return *this;
}

void FvInfo::SetFile(const ScannedFile &f)
{
	if (f.old_name.empty())
		MessageBox::Show("In FvInfo::SetFile(f) - [f.old_name] is empty");

	this->file = f;
}

void FvInfo::SetDescription(const BasicExcelCell *cell)
{
	if (cell->Type() == BasicExcelCell::STRING) this->description = StringToWString(cell->GetString());
	else if (cell->Type() == BasicExcelCell::WSTRING) this->description = cell->GetWString();
	else if (cell->Type() == BasicExcelCell::UNDEFINED) this->description = L"";
	else MessageBox::Show(strtoustr("[row: " + std::to_string(cell->GetRow()+1) + "][col: " 
					+ std::to_string(cell->GetCol()+1) + "] = is not valid description"));
}

void FvInfo::SetDescription(const std::wstring &descr)
{
	if (descr.empty())
		MessageBox::Show("FvInfo::SetDescription val passed is empty");
	
	this->description = descr;
}

void FvInfo::SetInvestition(const BasicExcelCell *cell)
{
	if (cell->Type() == BasicExcelCell::STRING) this->investition = StringToWString(cell->GetString());
	else if (cell->Type() == BasicExcelCell::WSTRING) this->investition = cell->GetWString();
	else if (cell->Type() == BasicExcelCell::UNDEFINED) this->investition = L"";
	else MessageBox::Show(strtoustr("[row: " + std::to_string(cell->GetRow() + 1) + "][col: " 
					+ std::to_string(cell->GetCol() + 1) + "] = is not valid ivestition name"));
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

std::wstring FvInfo::GetCompany() const
{
	return this->company;
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
	to_upper(pay);
	
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
	if (cell->GetString())
		this->date.SetDate(cell->GetString());
	else
	{
		MessageBox::Show("Komórka cell[row, col] = ["+ cell->GetRow() +", "+ cell->GetCol() 
			+"]\nw funkcji FvInfo::SetDate(BasicExcelCell)\nnie zawiera poprawnej daty");
		return;
	}
}

void FvInfo::SetDate(const std::string &date)
{
	this->date.SetDate(date);
}

void FvInfo::SetPayingPerson(const std::string & person)
{
	if (person.size() > max_whopayed_size)
		return;

	std::string p = person;
	this->whoPayed = to_upper(p);
}

void FvInfo::SetPayment(const std::string & pay)
{
	if (pay.size() > max_payment_size)
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

void FvInfo::SetTax(const std::string & tax)
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

void FvInfo::SetNetValue(const std::string &price_str)
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

void FvInfo::SetGrossValue(const std::string &price_str)
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

void FvInfo::SetFvIdent(const std::wstring &fv_nr)
{
	if (fv_nr.empty())
		MessageBox::Show("FvInfo::SetFvIdent val passed is empty");

	this->FVident = fv_nr;
}

void FvInfo::SetCompany(const std::wstring &comp_name)
{
	if (comp_name.empty())
		MessageBox::Show("FvInfo::SetCompany val passed is empty");

	this->company = comp_name;
}

void FvInfo::SetInvestition(const std::wstring &inv)
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

DateStruct::DateStruct(const std::string & d, char delim)
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

void DateStruct::SetDate(const std::string & d, char delim)
{
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