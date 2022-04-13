#include "Globals.h"

FvList Globals::fv_list(NEW_XLS_ENTRIES_COUNT);
VecFv_ptr Globals::vecFvFromImg;
std::set<ScannedFile> Globals::files;
std::set<ScannedFile>::const_iterator Globals::curr_file;
std::map<unsigned short int, std::wstring> Globals::currShown;
VecFv_ptr Globals::vecSplittedFvs;
std::unique_ptr<FvSplit> Globals::fvSplitter;

void Globals::SearchCompany(std::wstring name, std::unordered_set<std::wstring> &comp_set)
{
	for (auto it = Globals::vecFvFromImg.cbegin(); 
		it != Globals::vecFvFromImg.cend(); ++it)
	{
		if (wstr_tolower((*it)->GetCompany()).find(wstr_tolower(name)) != std::wstring::npos)
			comp_set.insert((*it)->GetCompany());
	}
}
void Globals::SearchInvestition(std::wstring name, std::unordered_set<std::wstring>& inv_set)
{
	for (auto it = Globals::vecFvFromImg.cbegin(); 
		it != Globals::vecFvFromImg.cend(); ++it)
	{
		if (wstr_tolower((*it)->GetInvestition()).find(wstr_tolower(name)) != std::wstring::npos)
			inv_set.insert((*it)->GetInvestition());
	}
}

void Globals::AutoFillOtherPriceTBox(System::Windows::Forms::TextBox^ from_tb,
	System::Windows::Forms::TextBox^ into_tb, short tax)
{
	if (System::String::IsNullOrWhiteSpace(from_tb->Text))
		return;
	auto p = std::make_unique<Price>();

	try
	{
		p->SetPrice(ustrtostr(from_tb->Text));

		if (from_tb->Name->Contains("Gross"))
			p->SetPrice(p->GetPrice() / Price(tax / 100.0 + 1.0));
		else if (from_tb->Name->Contains("Net"))
			p->SetPrice(p->GetPrice() * Price(tax / 100.0 + 1.0));
		else
			assert("The function " + __FUNCTION__ + " cannot distinguish Gross or Net value");
	}
	catch (const std::domain_error& err)
	{
		System::Windows::Forms::MessageBox::Show(strtoustr(err.what()));
	}
	into_tb->Text = strtoustr(p->GetPriceStr());
	into_tb->SelectAll();
}

short Globals::GetTaxFromCBox(System::Windows::Forms::ComboBox^ cbox)
{
	short tax;

	try
	{
		if (cbox->Text == "oo")
			tax = 0;
		else
			tax = convert::numeric_cast<short>(ustrtostr(cbox->Text).c_str());
	}
	catch (std::exception& e)
	{
		System::Windows::Forms::MessageBox::Show("Nieprawid³owy format liczby podatku VAT");
		return 23;			// return default
	}
	return tax;
}