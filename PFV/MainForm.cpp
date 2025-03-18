	#include "MainForm.h"

#include <regex>

using namespace System;
using namespace System::Windows::Forms;

[STAThreadAttribute]
int main(array < String^ > ^ args)
{
	Application::EnableVisualStyles();
	Application::SetCompatibleTextRenderingDefault(false);
	PFV::MainForm form;
	Application::Run(%form);

	return 0;
}

//////////////////////////////////// FORM CONTROLS FUNCTIONS ///////////////////////////////////////
//////////////////////////////////// SECTION				 /////////////////////////////////////// 
//////////////////////////////////// BEGIN  				 ///////////////////////////////////////

void PFV::MainForm::btnAdd_Click(System::Object ^ sender, System::EventArgs ^ e)
{
	if (Globals::files.empty())
	{
		AskForPath();
		return;
	}

	if (Globals::curr_file == Globals::files.cend())
	{
		CheckActFile();
		return;
	}

	if (chbAnotherPage->Checked && Globals::curr_file != Globals::files.begin())				// the file is another page of previously added one
		AnotherPageAdd();
	else
	{
		bool is_valid;

		if (chbIsFv->Checked)
			is_valid = NewFvAdd();
		else
			is_valid = NewNonFvAdd();

		if (!is_valid)
			return;
	}
	auto ptr = Globals::curr_file;
	Globals::curr_file++;
	ptr = Globals::curr_file;
	CheckActFile();
	chbIsFv_CheckedChanged(sender, e);
}
void PFV::MainForm::btnSplit_Click(System::Object^  sender, System::EventArgs^  e)
{
	if (Globals::vecFvFromImg.size() > 0)
	{
		split_fv_form = gcnew ProjektFaktury::SplitFvForm();
		Hide();
		split_fv_form->ShowDialog();
		Show();
		ManageForm(FormState::ADDING_DELETING);
	}
	else
		MessageBox::Show("Brak dodanych faktur");
}

void PFV::MainForm::MainForm_Load(System::Object^ sender, System::EventArgs^ e)
{

	LoadRawFiles();
	SetCurrYearMon();

	if(Globals::files.empty())
		ManageForm(FormState::NO_FILES_LOADED);
	else
	{
		Globals::curr_file = Globals::files.cbegin();
		LoadXLSRecords();
		TryRecognizeCurrFile();
		ManageForm(FormState::STARTING);
	}

#ifdef TEST_RUN			// defined in Globals.h

	FillInForTests();

#endif // TEST_RUN
}
void PFV::MainForm::txtCompany_TextChanged(System::Object ^ sender, System::EventArgs ^ e)
{
	rtxtDynamicOutput->Clear();
	Globals::currShown.clear();	

	if (txtCompany->Text->Length > TEXT_LEN_SHOW_ACTIVATE)
	{
		std::unordered_set<std::wstring> companies_set;
		auto const search_string{ ustrtowstr(txtCompany->Text->ToString()) };

		Globals::fv_list.SearchForCompany(search_string, companies_set);		// search in records from XLS file
		Globals::SearchCompany(search_string, companies_set);					// search in already added invoices

		if (companies_set.size() > 0)
		{
			rtxtDynamicOutput->Visible = true;
			rtxtDynamicOutput->Text = "Wybierz z klawiatury nr firmy:\n";
			StringsToOutput(search_string, companies_set);
		} else rtxtDynamicOutput->Visible = false;
	} else rtxtDynamicOutput->Visible = false;
}
void PFV::MainForm::txtCompany_PreviewKeyDown(System::Object ^ sender, System::Windows::Forms::PreviewKeyDownEventArgs ^ e)
{
	PrevCompInvKeyDown(sender, e);
}
void PFV::MainForm::txtInvest_TextChanged(System::Object ^ sender, System::EventArgs ^ e)
{
	rtxtDynamicOutput->Clear();
	Globals::currShown.clear();

	if (txtInvest->Text->Length > TEXT_LEN_SHOW_ACTIVATE)
	{
		std::unordered_set<std::wstring> searchResult;
		auto const search_string{ ustrtowstr(txtInvest->Text->ToString()) };

		Globals::fv_list.SearchInvestition(search_string, searchResult);		// search in records from XLS file
		Globals::SearchInvestition(search_string, searchResult);				// search in already added invoices
																		// function appends any matching records
		if (searchResult.size() > 0)
		{
			rtxtDynamicOutput->Visible = true;
			rtxtDynamicOutput->Text = "Wybierz z klawiatury nr inwestycji:\n";
			StringsToOutput(search_string, searchResult);
		}
		else rtxtDynamicOutput->Visible = false;
	}
	else rtxtDynamicOutput->Visible = false;
}
void PFV::MainForm::txtInvest_PreviewKeyDown(System::Object^  sender, System::Windows::Forms::PreviewKeyDownEventArgs^  e)
{
	PrevCompInvKeyDown(sender, e);
}
void PFV::MainForm::btnDeleteLast_Click(System::Object^  sender, System::EventArgs^  e)
{
	Globals::curr_file--;

	if (Globals::curr_file->is_fv)
	{
		auto inv_quant = Globals::vecFvFromImg.back()->invquantity;
		for(; inv_quant > 0; inv_quant--)
			Globals::vecFvFromImg.pop_back();
	}
	else
	{
		Globals::curr_file->is_fv = true;			// mark the file to default value
		Globals::curr_file->SetDefaultNewName();
	}

	ManageForm(FormState::ADDING_DELETING);
	ResetFilenameLabel();
	CheckActFile();
}
void PFV::MainForm::btnSaldeo_Click(System::Object^  sender, System::EventArgs^  e)
{
	for (auto &fv : Globals::fv_list.vecOldFvInfo)
	{
		if (fv->date.month == System::Convert::ToInt16(txtMonth->Text)
			&& fv->date.year == System::Convert::ToInt16(txtYear->Text))
		{
			rtxtProgramOutput->Text += "new FvInfo(\""
				+ wstrtoustr(erase_strange_chars(fv->GetCompany() + fv->GetInvoiceNumber()) + L"\", "
					+ L"\"" + fv->GetCompany() + L"\", ");
			rtxtProgramOutput->Text += strtoustr("\"" + fv->GetFvFullDate() + "\", ");
			rtxtProgramOutput->Text += wstrtoustr(L"\"" + fv->GetInvoiceNumber() + L"\", ");
			rtxtProgramOutput->Text += wstrtoustr(L"\"" + fv->GetInvestition() + L"\", ");
			rtxtProgramOutput->Text += wstrtoustr(L"\"" + fv->description + L"\", ");
			rtxtProgramOutput->Text += strtoustr("\"" + fv->net_value.GetPriceStr() + "\", ");
			rtxtProgramOutput->Text += strtoustr("\"" + fv->gross_value.GetPriceStr() + "\", ");
			rtxtProgramOutput->Text += strtoustr("\"" + fv->GetPayingPerson() + "\", ");
			rtxtProgramOutput->Text += strtoustr("\"" + fv->GetPayment() + "\"),");


			rtxtProgramOutput->Text += "\n";
		}
	}
}
void PFV::MainForm::lblCurrentFile_MouseHover(System::Object^  sender, System::EventArgs^  e)
{
	if (Globals::curr_file == Globals::files.cend()) return ;
	
	InitOnMouseHoverTextBox();
	size_t s{ Globals::curr_file->old_name.size() };
	System::Drawing::Point ^p = System::Windows::Forms::Control::MousePosition;
	rtxtOnMouseHover->Location = 
		panelFilename->PointToClient(System::Drawing::Point(p->X+20, p->Y+100));
	rtxtOnMouseHover->Size = System::Drawing::Size(
		static_cast<int>(s*5.5), 15);
	rtxtOnMouseHover->Text = wstrtoustr(Globals::curr_file->old_name);
	rtxtOnMouseHover->Visible = true;
	rtxtOnMouseHover->BringToFront();
}

//////////////////////////////////// FORM CONTROLS FUNCTIONS ///////////////////////////////////////
//////////////////////////////////// SECTION				 /////////////////////////////////////// 
//////////////////////////////////// END					 ///////////////////////////////////////

void PFV::MainForm::InitDynamicOutputBox()
{
	if (Controls->Find(L"rtxtDynamicOutput", true)->Length)
		return;
	rtxtDynamicOutput = (gcnew System::Windows::Forms::RichTextBox());
	rtxtDynamicOutput->Name = L"rtxtDynamicOutput";
	rtxtDynamicOutput->ReadOnly = true;
	rtxtDynamicOutput->ScrollBars = 
		System::Windows::Forms::RichTextBoxScrollBars::None;
	rtxtDynamicOutput->Size = 
		System::Drawing::Size(txtCompany->Width, (MAX_DYNAMIC_SHOW+1)*15);
	rtxtDynamicOutput->TabStop = false;
	rtxtDynamicOutput->Text = L"";
	rtxtDynamicOutput->Visible = false;
	Controls->Add(rtxtDynamicOutput);

}
void PFV::MainForm::StringsToOutput(const std::wstring &search, 
	const std::unordered_set<std::wstring> &sset)
{
	unsigned short int i = 1;

	for (auto const &it : sset)
	{
		if (i > MAX_DYNAMIC_SHOW) break;

		Globals::currShown[i] = it;
		rtxtDynamicOutput->AppendText(strtoustr(std::to_string(i) + ". "));
		rtxtDynamicOutput->AppendText(wstrtoustr(it) + "\n");
		i++;
	}
}
void PFV::MainForm::PrevCompInvKeyDown(System::Object ^ sender,
	System::Windows::Forms::PreviewKeyDownEventArgs ^ e)
{
	auto tbox = dynamic_cast<System::Windows::Forms::TextBox ^>(sender);
	if(!tbox) return;

	rtxtDynamicOutput->Location = tbox->FindForm()->PointToClient(
		tbox->PointToScreen(System::Drawing::Point(0, tbox->Height)));
	rtxtDynamicOutput->BringToFront();

	// Handle backspace (reset auto-selection)
	if(e->KeyCode == Keys::Back)
	{
		userSelectionMade = false;
		rtxtDynamicOutput->Visible = false;
		return;
	}

	int number = static_cast<int>(e->KeyCode) - 48;

	if(e->KeyCode >= Keys::D1 && e->KeyCode <= Keys::D9
		&& number <= MAX_DYNAMIC_SHOW
		&& Globals::currShown.size() != 0
		&& rtxtDynamicOutput->Visible
		&& tbox->Text->Length > TEXT_LEN_SHOW_ACTIVATE)
	{
		rtxtDynamicOutput->Visible = false;
		tbox->Text = wstrtoustr(Globals::currShown[number]);
		userSelectionMade = true;
		System::Windows::Forms::Control::SelectNextControl(tbox, true, true, true, true);
	}
	else if(e->KeyCode == Keys::Tab
		&& !Globals::currShown.empty()
		&& rtxtDynamicOutput->Visible
		&& tbox->Text->Length > TEXT_LEN_SHOW_ACTIVATE
		&& !userSelectionMade) // Prevent override if invoice recognition was used
	{
		tbox->Text = wstrtoustr(Globals::currShown[1]);
		userSelectionMade = true;
		rtxtDynamicOutput->Visible = false;
	}
	else
	{
		userSelectionMade = false;
	}
}

std::wstring PFV::MainForm::GetFvDirText()
{
	auto main_fv_dir = ustrtowstr(txtFvDir->Text);
	if (main_fv_dir.back() == L'/' || main_fv_dir.back() == L'\\')
		main_fv_dir.pop_back();

	return main_fv_dir;
}
void PFV::MainForm::LoadRawFiles(void)
{
	std::vector<ScannedFile> vec;

	for (auto const &d : std::filesystem::directory_iterator(ustrtostr(txtFvDir->Text->ToString())))
	{
		if (!d.is_directory())
		{
			ScannedFile f(d.path().filename().wstring(), L"", d.path().extension().string());
			f.last_mod = d.last_write_time();
			vec.push_back(std::move(f));
		}
	}

	if (vec.empty())
	{
		MessageBox::Show("Brak plików w lokalizacji: "
			+ txtFvDir->Text->ToString());
		return;
	}

	for (auto const &it : vec)
	{
		if (!Globals::files.insert(it).second)
			MessageBox::Show("Zduplikowana nazwa pliku: " + wstrtoustr(it.old_name));
	}
}
void PFV::MainForm::AskForPath(void)
{
	folderBrowser->ShowDialog();
	if(!System::String::IsNullOrEmpty(folderBrowser->SelectedPath))
		MessageBox::Show("Wskazany folder to: "+ folderBrowser->SelectedPath 
			+"\n\nTa funkcja nie jest jeszcze dostêpna...");
	
	// ...
	
	return;				// show file browser dialog, user selects directory from which files are loaded
}
void PFV::MainForm::LoadXLSRecords(void)
{
	Globals::fv_list.vecOldFvInfo.reserve(XLS_ROWS_FROM_END + Globals::files.size());
	warnings = strtoustr(Globals::fv_list.GetDataFromXlsFile(ustrtostr(txtFvListFilename->Text->ToString()), XLS_ROWS_FROM_END));
}

void PFV::MainForm::ManageForm(FormState state)
{
	if(state != FormState::NO_FILES_LOADED
		&& Globals::curr_file == Globals::files.cend()
		&& state != FormState::AFTER_SAVING)
		state = FormState::NO_MORE_LEFT;

	btnSplit->Enabled = false;
	btnDeleteLast->Enabled = false;
	panelFilename->Visible = false;

	UpdateProgramOutput(state);

	switch (state)
	{
	case NO_FILES_LOADED:
		btnAdd->Text = "Wczytaj z pliku";
		HideFvComponents();
		break;
	case NO_MORE_LEFT:
		btnAdd->Text = "Zapisz";
		btnDeleteLast->Enabled = true;
		btnSplit->Enabled = CanSplitBtnBeEnabled(Globals::curr_file);
		break;
	case STARTING:
		panelFilename->Visible = true;
		chbAnotherPage->Visible = false;
		btnAdd->Text = "Dodaj";
		ResetFilenameLabel();
		break;
	case ADDING_DELETING:
		panelFilename->Visible = true;
		chbAnotherPage->Visible = true;
		btnAdd->Text = "Dodaj";
		ClearAllInputs();
		chbIsFv->Focus();
		btnSplit->Enabled = CanSplitBtnBeEnabled(Globals::curr_file);
		btnDeleteLast->Enabled = true;
		ResetFilenameLabel();
		break;
	case AFTER_SAVING:
		btnAdd->Enabled = false;
		ClearAllInputs();
		break;
	default:
		// for debugging only
		MessageBox::Show("No state with code: [" + System::Convert::ToString(state) + "] was specified.");
	}
}
void PFV::MainForm::CheckActFile(void)
{
	if (Globals::curr_file == Globals::files.cend())
	{
		ManageForm(FormState::NO_MORE_LEFT);
		if (PromptForSaving())
		{
			try 
			{
				SaveToFile();
				RenameAllFiles();
				CreateFoldersAndMoveFiles();
			}
			catch (std::string &err)
			{
				MessageBox::Show(strtoustr(err));
				ManageForm(FormState::NO_MORE_LEFT);
				return;
			}
			ManageForm(FormState::AFTER_SAVING);
		}
	}
	else if (Globals::curr_file == Globals::files.cbegin())
	{
		if (Globals::vecFvFromImg.empty())		// all entries have been deleted
		{
			ManageForm(FormState::STARTING);
			TryRecognizeCurrFile();
		}
		else
			MessageBox::Show("Error... vecFvFromImg has elements,"
				+" but curr_file == files vec begin()");
	}
	else
	{
		ManageForm(FormState::ADDING_DELETING);
		TryRecognizeCurrFile();
	}
}

// Reading data from UI inputs 

void PFV::MainForm::SetFvInfoFromInputs(Fv_ptr & fv)
{
	std::string errmsg{ "" };

	fv->SetFile(&*Globals::curr_file);

	System::String::IsNullOrWhiteSpace(txtCompany->Text) ?
		errmsg += "Wymagane jest podanie nazwy firmy.\n" :
		fv->SetCompany(ustrtowstr(txtCompany->Text));

	System::String::IsNullOrWhiteSpace(txtInvest->Text) ?
		errmsg += "Wymagane jest podanie nazwy inwestycji.\n" :
		fv->SetInvestition(ustrtowstr(txtInvest->Text));

	fv->SetDescription(ustrtowstr(txtDescr->Text));		// may be empty

	fv->SetFvIdent(ustrtowstr(txtFvIdent->Text));

	fv->SetPayment(str_toupper(ustrtostr(txtPayment->Text)));
	fv->SetTax(ustrtostr(cbTax->Text));
	fv->SetNetValue(ustrtostr(txtNetVal->Text));
	fv->SetGrossValue(ustrtostr(txtGrossVal->Text));
	fv->SetPayingPerson(!System::String::IsNullOrWhiteSpace(txtWhoPayed->Text) ?
		str_toupper(ustrtostr(txtWhoPayed->Text)) : "");

	fv->comments = ustrtowstr(txtComments->Text);

	errmsg += fv->GetWarnings();

	if (!errmsg.empty())
	{
		System::Exception ^e = gcnew System::Exception(strtoustr(errmsg));
		e->Source = "B³¹d wygenerowany przez pola tekstowe.";
		throw e;
	}

	fv->date.SetDate(System::Convert::ToUInt16(txtDay->Text), 
					System::Convert::ToUInt16(txtMonth->Text),
					System::Convert::ToUInt16(txtYear->Text));

	if (fv->date > System::DateTime::Now)
	{
		System::Exception^ e =
			gcnew System::Exception("Data jest z przysz³oœci.\n");
		e->Source = "B³¹d wygenerowany przez pola daty.";
		throw e;
	}
	
	if(!fv->date.isValid())
	{
		System::Exception ^e = 
			gcnew System::Exception("Nieprawid³owy format daty.\n"); 
		e->Source = "B³¹d wygenerowany przez pola daty.";
		throw e;
	}

	if (System::String::IsNullOrWhiteSpace(txtFvIdent->Text))
	{
		fv->SetFvIdent(StringToWString(fv->GetFvFullDate()));
	}
}
void PFV::MainForm::SetCurrYearMon(void)
{
	System::DateTime now = System::DateTime::Now;
	txtYear->Text = System::Convert::ToString(now.Year);
	txtMonth->Text = System::Convert::ToString(now.Month);
}
void PFV::MainForm::ClearAllInputs(void)
{
	txtCompany->Clear();
	txtFvIdent->Clear();
	txtInvest->Clear();
	txtDescr->Clear();
	txtDay->Clear();
	txtNetVal->Clear();
	txtGrossVal->Clear();
	txtNewNotFvFilename->Clear();
	txtWhoPayed->Clear();
	txtPayment->Clear();
	txtNewNotFvFilename->Clear();
	txtComments->Clear();
}
void PFV::MainForm::HideFvComponents(void)
{
	for (int i = 0; i < panelInputs->Controls->Count; ++i)
	{
		auto ctr = panelInputs->Controls[i];
		if (ctr->GetType()->FullName != "System.Windows.Forms.Button")
			ctr->Visible = false;
	}
}
void PFV::MainForm::ShowFvComponents(void)
{
	for (int i = 0; i < panelInputs->Controls->Count; ++i)
	{
		panelInputs->Controls[i]->Visible = true;
	}
}
bool PFV::MainForm::CanSplitBtnBeEnabled
	(std::set<ScannedFile>::const_iterator curr)
{
	if (curr != Globals::files.cbegin()
		&& (--curr)->is_fv
		&& Globals::vecFvFromImg.back()->invquantity == 1)
		return true;
	else
		return false;
}

void PFV::MainForm::UpdateProgramOutput(FormState state)
{
	if(state != FormState::AFTER_SAVING)
		rtxtProgramOutput->Clear();

	switch (state)
	{
	case FormState::NO_FILES_LOADED:
		rtxtProgramOutput->Text = "Brak plików w folderze: " + txtFvDir->Text;
		break;
	case FormState::STARTING:
		SummaryFromXLS_ToOutput();
		rtxtProgramOutput->AppendText("Uwagi:\n"+ warnings + "\n");
		RawFilenames_ToOutput();
		break;
	case FormState::ADDING_DELETING:
		FvFiles_ToOutput();
		break;
	case FormState::NO_MORE_LEFT:
		FvFiles_ToOutput();
		rtxtProgramOutput->AppendText("\nWczytano wszystkie dostêpne pliki z folderu: " + txtFvDir->Text);
		break;
	case FormState::AFTER_SAVING:
		rtxtProgramOutput->AppendText("\n\nZapisano do pliku i zmieniono nazwy skanów");
		break;
	default:
		break;
	}
	rtxtProgramOutput->ScrollToCaret();
}
void PFV::MainForm::RawFilenames_ToOutput(void)
{
	for (auto &file : Globals::files)
		if (file.old_name != L".." && file.old_name != L".")
			rtxtProgramOutput->AppendText(wstrtoustr(L"Wczytano: "
				+ file.old_name + L'\n'));
}
void PFV::MainForm::SummaryFromXLS_ToOutput(void)
{
	rtxtProgramOutput->AppendText("Wczytano z pliku " + txtFvListFilename->Text->ToString()
		+ System::Convert::ToString(Globals::fv_list.GetSize()) + " faktur. ");
	rtxtProgramOutput->AppendText(strtoustr("Daty wczytanych faktur: od "
		+ Globals::fv_list.GetOldestDate() + " do " + Globals::fv_list.GetLatestDate() + "\n\n"));
}
void PFV::MainForm::FvFiles_ToOutput(void)
{
	std::vector<ScannedFile> non_fv_files;

	for (auto &fv : Globals::vecFvFromImg)
		rtxtProgramOutput->AppendText(FvToOutput(*fv));

	for (auto &file : Globals::files)
	{
		if (!file.is_fv)
			non_fv_files.push_back(file);
	}

	if (non_fv_files.size() > 0)
	{
		rtxtProgramOutput->AppendText("\nPliki nie bêd¹ce fakturami:\n");
		for (auto &it : non_fv_files)
			rtxtProgramOutput->AppendText(wstrtoustr(it.old_name + L" -> " + it.new_name + L"\n"));
	}
}

bool PFV::MainForm::NewFvAdd(void)
{
	auto newFvDoc = std::make_shared<FvInfo>();
		
	try
	{
		SetFvInfoFromInputs(newFvDoc);
		CheckForDuplicates(newFvDoc);
	}
	catch (System::Exception ^e)
	{
		MessageBox::Show("B³¹d spowodowany przez: " + e->Source + "\nOpis: " + e->Message);
		return false;
	}

	Globals::curr_file->new_name = newFvDoc->GetCompany() + L" " + newFvDoc->GetInvoiceNumber();
	Globals::vecFvFromImg.push_back(std::move(newFvDoc));

	return true;
}
void PFV::MainForm::CheckForDuplicates(const Fv_ptr &fv)
{
	System::Exception ^e = gcnew System::Exception();
	e->Source = "Wykryto duplikaty faktury";
	auto prog_s = std::find(Globals::vecFvFromImg.begin(), Globals::vecFvFromImg.end(), fv);
	auto base_s = std::find(Globals::fv_list.vecOldFvInfo.begin(), Globals::fv_list.vecOldFvInfo.end(), fv);
	if (prog_s != Globals::vecFvFromImg.end())
	{
		e = gcnew System::Exception(wstrtoustr(L"Faktura firmy [" 
			+ (*prog_s)->GetCompany() + L"] o numerze [" 
			+ (*prog_s)->GetInvoiceNumber()
			+ L"] zosta³a ju¿ dodana w tej sesji programu."));
		throw e;
	}
	else if (base_s != Globals::fv_list.vecOldFvInfo.end())
	{
		e = gcnew System::Exception(wstrtoustr(L"Faktura firmy [" 
			+ (*base_s)->GetCompany() + L"] o numerze [" 
			+ (*base_s)->GetInvoiceNumber()
			+ L"] zosta³a ju¿ wczytana z pliku .xls."));
		throw e;
	}
}
void PFV::MainForm::TryRecognizeCurrFile()
{
	// TODO: iterate these functions in a loop... through map<company, regex>
	// provide no duplicates
	userSelectionMade = false;
	userSelectionMade |= TryRecoAutopayInvoice(L".*([0-9])+(202[0-9])(APT).*");
	userSelectionMade |= TryRecoVTSInvoice(L".*(CP([0-9]{3})([0-9]{2}).*).*");		// ex. CP02302I0494, CP02303I0286
	userSelectionMade |= TryRecoOrangeInvoice(L".*(FAKTURA-P-[0-9]*-[0-9]*-[0-9]*).*");		// ex. FAKTURA-P-16899138-2669260577-00001763
	userSelectionMade |= TryRecoIglotechInvoice(L".*FS-KAT_([0-9]+)_([0-9]{2})_([0-9]{4})_[0-9]{6}([0-9]{2}).*");	// ex. (S)FS-KAT_175_09_2023_20230918_1201 Strzelecka
	userSelectionMade |= TryRecoNaviInvoice(L".*NAVI-([0-9]+)-([0-9]{2})-([0-9]{4}).*");
	userSelectionMade |= TryRecoTCHWInvoice(L".*FV_([0-9]+)_([0-9]{2})_([0-9]{4}).*");
	userSelectionMade |= TryRecoWienkraInvoice(L".*Dok_FV-([0-9]+)-([0-9]+).*");
	userSelectionMade |= TryRecoSGKlimaInvoice(L".*dokument_FS_([0-9]+)_([0-9]{2})_([0-9]{4}).*");
	userSelectionMade |= TryRecoHerbudInvoice(L".*FS_([0-9]+)_([A-Z][0-9])_([0-9]{2})_([0-9]{4}).*");
	userSelectionMade |= TryRecoWimarInvoice(L".*FVS_([0-9]+)_([0-9]{2})_([0-9]{4}).*(Wzór_standard).*");
	userSelectionMade |= TryRecoOpenAIInvoice(L".*Invoice-(40DD5268-[0-9]{4}).*");
	userSelectionMade |= TryRecoSzydloInvoice(L".*faktura_([0-9]{2})_([0-9]{2})_([0-9]{4}).*");

	if(userSelectionMade)
		rtxtDynamicOutput->Visible = false;
}
void PFV::MainForm::txtDateSameAsFileLastModDate()
{
	txtDay->Text = strtoustr(std::to_string(Globals::curr_file->last_mod.day));
	txtMonth->Text = strtoustr(std::to_string(Globals::curr_file->last_mod.month));
	txtYear->Text = strtoustr(std::to_string(Globals::curr_file->last_mod.year));
}
bool PFV::MainForm::TryRecoAutopayInvoice(std::wstring rx_pattern)
{
	const std::wregex reg(rx_pattern);
	auto const& f = Globals::curr_file;
	std::wsmatch sm;

	if (std::regex_match(f->old_name, sm, reg))
	{
		txtCompany->Text = "Autopay";
		txtInvest->Text = "";
		txtFvIdent->Text = wstrtoustr(f->old_name.substr(0, 4)
			+ L"/" + std::to_wstring(f->last_mod.month)
			+ L"/" + std::to_wstring(f->last_mod.year)
			+ L"/APT");
		txtNetVal->Text = "10,57";
		txtGrossVal->Text = "13,00";
		txtDescr->Text = "A4";
		txtWhoPayed->Text = "MZ";
		txtPayment->Text = "G";
		txtDateSameAsFileLastModDate();
		txtFvIdent->Focus();
		return true;
	}
	return false;
}

bool PFV::MainForm::TryRecoVTSInvoice(std::wstring rx_pattern)
{
	const std::wregex reg(rx_pattern);
	auto const& f = Globals::curr_file;
	std::wsmatch sm;

	if (std::regex_match(f->old_name, sm, reg))
	{
		txtCompany->Text = "VTS Polska";
		txtInvest->Text = "";
		txtFvIdent->Text = wstrtoustr(sm[1]);
		txtDay->Text = strtoustr(std::to_string(f->last_mod.day));
		txtMonth->Text = wstrtoustr(sm[3]);
		txtYear->Text = L"2"+ wstrtoustr(sm[2]);
		cbTax->Text = "23";
		txtPayment->Text = "T: ";

		txtInvest->Focus();
		return true;
	}
	return false;
}

bool PFV::MainForm::TryRecoOrangeInvoice(std::wstring rx_pattern)
{
	const std::wregex reg(rx_pattern);
	auto const& f = Globals::curr_file;
	std::wsmatch sm;

	if (std::regex_match(f->old_name, sm, reg))
	{
		txtCompany->Text = "Orange";
		txtInvest->Text = "miesiêczne koszty firmy";
		txtDescr->Text = "abon. tel.";
		txtFvIdent->Text = wstrtoustr(sm[1]);
		cbTax->Text = "23";
		txtPayment->Text = "T: ";
		txtDateSameAsFileLastModDate();

		return true;
	}
	return false;
}

bool PFV::MainForm::TryRecoIglotechInvoice(std::wstring rx_pattern)
{
	const std::wregex reg(rx_pattern);
	auto const& f = Globals::curr_file;
	std::wsmatch sm;

	if (std::regex_match(f->old_name, sm, reg))
	{
		txtCompany->Text = "Iglotech";
		txtFvIdent->Text = wstrtoustr(L"SFS-KAT/"+ sm[1].str() +L"/"+ sm[2].str() +L"/"+ 
											sm[3].str());
		txtDay->Text = wstrtoustr(sm[4]);
		txtMonth->Text = wstrtoustr(sm[2]);
		txtYear->Text = wstrtoustr(sm[3]);
		cbTax->Text = "23";
		txtPayment->Text = "T: ";

		return true;
	}
	return false;
}

bool PFV::MainForm::TryRecoNaviInvoice(std::wstring rx_pattern)
{
	const std::wregex reg(rx_pattern);
	auto const& f = Globals::curr_file;
	std::wsmatch sm;

	if (std::regex_match(f->old_name, sm, reg))
	{
		txtCompany->Text = "Navifleet";
		txtFvIdent->Text = wstrtoustr(L"NAVI-" + sm[1].str() + L"-" + sm[2].str() + L"-" +
			sm[3].str());
		txtDay->Text = strtoustr(std::to_string(f->last_mod.day));
		txtMonth->Text = wstrtoustr(sm[2]);
		txtYear->Text = wstrtoustr(sm[3]);

		txtInvest->Text = strtoustr("miesiêczne koszty firmy");
		txtDescr->Text = strtoustr("gps");
		txtNetVal->Text = strtoustr("66,00");
		txtGrossVal->Text = strtoustr("81,18");
		cbTax->Text = "23";
		txtPayment->Text = "T: ";

		return true;
	}
	return false;
}

bool PFV::MainForm::TryRecoTCHWInvoice(std::wstring rx_pattern)
{
	const std::wregex reg(rx_pattern);
	auto const& f = Globals::curr_file;
	std::wsmatch sm;

	if (std::regex_match(f->old_name, sm, reg))
	{
		txtCompany->Text = "TCHW";
		txtFvIdent->Text = wstrtoustr(L"FV/" + sm[1].str() + L"/" + sm[2].str() + L"/" +
			sm[3].str());
		txtDay->Text = strtoustr(std::to_string(f->last_mod.day));
		txtMonth->Text = wstrtoustr(sm[2]);
		txtYear->Text = wstrtoustr(sm[3]);
		cbTax->Text = "23";
		txtPayment->Text = "T: ";

		return true;
	}
	return false;
}

bool PFV::MainForm::TryRecoWienkraInvoice(std::wstring rx_pattern)
{
	const std::wregex reg(rx_pattern);
	auto const& f = Globals::curr_file;
	std::wsmatch sm;

	if (std::regex_match(f->old_name, sm, reg))
	{
		txtCompany->Text = "Wienkra";
		txtFvIdent->Text = wstrtoustr(L"FV/"+ sm[1].str() + L"/" + sm[2].str());
		txtDay->Text = strtoustr(std::to_string(f->last_mod.day));
		txtMonth->Text = strtoustr(std::to_string(f->last_mod.month));
		txtYear->Text = wstrtoustr(L"20"+ sm[2].str());

		return true;
	}
	return false;
}

bool PFV::MainForm::TryRecoSGKlimaInvoice(std::wstring rx_pattern)
{
	const std::wregex reg(rx_pattern);
	auto const& f = Globals::curr_file;
	std::wsmatch sm;

	if (std::regex_match(f->old_name, sm, reg))
	{
		txtCompany->Text = "SGKlima";
		txtFvIdent->Text = wstrtoustr(L"FS/" + sm[1].str() + L"/" + sm[2].str() + L"/" +
			sm[3].str());
		txtDay->Text = strtoustr(std::to_string(f->last_mod.day));
		txtMonth->Text = wstrtoustr(sm[2]);
		txtYear->Text = wstrtoustr(sm[3]);

		cbTax->Text = "23";
		txtPayment->Text = "T: ";

		return true;
	}
	return false;
}

bool PFV::MainForm::TryRecoWimarInvoice(std::wstring rx_pattern)
{
	const std::wregex reg(rx_pattern);
	auto const& f = Globals::curr_file;
	std::wsmatch sm;

	if (std::regex_match(f->old_name, sm, reg))
	{
		txtCompany->Text = "Wimar";
		txtFvIdent->Text = wstrtoustr(L"FVS-" + sm[1].str() + L"-" + sm[2].str() + L"-" +
			sm[3].str());
		txtDay->Text = strtoustr(std::to_string(f->last_mod.day));
		txtMonth->Text = wstrtoustr(sm[2]);
		txtYear->Text = wstrtoustr(sm[3]);

		cbTax->Text = "23";
		txtPayment->Text = "T: ";

		return true;
	}
	return false;
}

bool PFV::MainForm::TryRecoHerbudInvoice(std::wstring rx_pattern)
{
	const std::wregex reg(rx_pattern);
	auto const& f = Globals::curr_file;
	std::wsmatch sm;

	if (std::regex_match(f->old_name, sm, reg))
	{
		txtCompany->Text = "Herbud";
		txtFvIdent->Text = wstrtoustr(L"FS " + sm[1].str() + L"/" + sm[2].str() + L"/" +
			sm[3].str() + L"/" + sm[4].str());
		txtDay->Text = strtoustr(std::to_string(f->last_mod.day));
		txtMonth->Text = wstrtoustr(sm[3]);
		txtYear->Text = wstrtoustr(sm[4]);

		cbTax->Text = "23";
		txtPayment->Text = "T: ";

		return true;
	}
	return false;
}

bool PFV::MainForm::TryRecoOpenAIInvoice(std::wstring rx_pattern)
{
	const std::wregex reg(rx_pattern);
	auto const& f = Globals::curr_file;
	std::wsmatch sm;

	if (std::regex_match(f->old_name, sm, reg))
	{
		txtCompany->Text = "OpenAI";
		txtDescr->Text = "chat GPT";
		txtFvIdent->Text = wstrtoustr(sm[1].str());
		txtDay->Text = strtoustr(std::to_string(f->last_mod.day));
		txtMonth->Text = strtoustr(std::to_string(f->last_mod.month));
		txtYear->Text = strtoustr(std::to_string(f->last_mod.year));
		txtGrossVal->Text = "82,69";
		txtInvest->Text = "miesiêczne koszty firmy";
		txtWhoPayed->Text = "MZ";
		cbTax->Text = "23";
		txtPayment->Text = "karta";

		return true;
	}
	return false;
}

bool PFV::MainForm::TryRecoSzydloInvoice(std::wstring rx_pattern)
{
	const std::wregex reg(rx_pattern);
	auto const& f = Globals::curr_file;
	std::wsmatch sm;

	if (std::regex_match(f->old_name, sm, reg))
	{
		txtCompany->Text = "Ksiêgowoœæ";
		txtDescr->Text = "ksiêgowoœæ";
		txtInvest->Text = "miesiêczne koszty firmy";
		txtNetVal->Text = "680,00";
		txtGrossVal->Text = "836,40";
		txtFvIdent->Text = wstrtoustr(sm[1].str() + L"/" + sm[2].str() + L"/" + sm[3].str());
		txtDay->Text = wstrtoustr(sm[1]);
		txtMonth->Text = wstrtoustr(sm[2]);
		txtYear->Text = wstrtoustr(sm[3]);

		cbTax->Text = "23";
		txtPayment->Text = "T: ";

		return true;
	}
	return false;
}

bool PFV::MainForm::NewNonFvAdd(void)
{
	System::String ^text = txtNewNotFvFilename->Text;
	if (!System::String::IsNullOrWhiteSpace(text))
	{
		ScannedFile f(L"", ustrtowstr(text));

		if (Globals::files.count(f) != 0)
		{
			MessageBox::Show("Plik o nazwie [" + text + "] zosta³ ju¿ dodany.");
			return false;
		}
		else
		{
			Globals::curr_file->is_fv = false;
			Globals::curr_file->new_name = ustrtowstr(text);
			return true;
		}
	}
	else
	{
		MessageBox::Show("Podaj now¹ nazwê pliku");
		return false;
	}
}
void PFV::MainForm::WriteToTextBoxNextPageName(void)
{
	auto file_ptr = *std::prev(Globals::curr_file);
	std::wstring num_page;
	size_t pos = file_ptr.new_name.find(L"str.");
	if (pos != std::wstring::npos)
	{
		num_page = file_ptr.new_name.substr(pos + 5);
		auto num_page_int = convert::numeric_cast<int>(num_page);
		num_page_int++;
		file_ptr.new_name.erase(pos - 1);
		num_page = L" str. " + std::to_wstring(num_page_int);
	}
	else
		num_page = L" str. 2";

	file_ptr.new_name += num_page;
	txtNewNotFvFilename->Text = wstrtoustr(file_ptr.new_name);
}
bool PFV::MainForm::AnotherPageAdd(void)
{
	bool check;
	//another page might be fv...
	//if(Globals::curr_file->is_fv)
	//	blabla
	//else
		check = NewNonFvAdd();
	
	txtNewNotFvFilename->Clear();
	return check;
}

bool PFV::MainForm::PromptForSaving(void)
{
	return MessageBox::Show(
		"Ostatni plik zosta³ dodany do listy.\n"
		+ "Zamknij wszystkie otwarte pliki faktur.\n" +
		"Zapisaæ do " + txtFvListOutFilename->Text + " ?\n" +
		"Pliki z nowymi nazwami zostan¹ przeniesione do folderu [tu nazwa folderu]",
		"Zapytanie", MessageBoxButtons::YesNo,
		MessageBoxIcon::Question) == System::Windows::Forms::DialogResult::Yes;
}
void PFV::MainForm::SaveToFile(void)
{
	if (Globals::vecFvFromImg.empty())
		return;

	if (!System::String::IsNullOrWhiteSpace(txtFvListOutFilename->Text))
	{
		std::string fn = ustrtostr(txtFvListOutFilename->Text);
		if (!Globals::fv_list.SaveToXLSFile(fn, Globals::vecFvFromImg))
		{
			throw std::string("Nie uda³o siê zapisaæ danych do pliku " + fn + ".\n"
				+ "Mo¿liwe, ¿e jest on otwarty w innym programie.");
		}
	}
	else
		throw std::string("B³¹d!\nSprawdŸ czy pole z nazw¹ pliku wyjœciowego jest poprawnie uzupe³nione.");
}
void PFV::MainForm::RenameAllFiles(void)
{
	rtxtProgramOutput->Clear();
	auto main_fv_dir = GetFvDirText();
	std::error_code ec;

	for (auto &f : Globals::files)
	{
		for (size_t i = 0; i < f.new_name.size(); i++)
		{
			if (f.new_name[i] == '/' || f.new_name[i] == '\\')
				f.new_name[i] = '-';
		}

		int counter = 2;

		// add (2), (3), (4)... if file already exists
		while(std::filesystem::exists(main_fv_dir + L"\\"+ f.new_name + f.GetExtension()))
			f.new_name += L" (" + std::to_wstring(counter++) + L")";

		std::filesystem::rename(main_fv_dir + L"\\" + f.old_name, main_fv_dir + L"\\" + f.new_name + f.GetExtension(), ec);

		if(ec)
			rtxtProgramOutput->AppendText(wstrtoustr(L"Nie uda³o siê zmieniæ nazwy pliku z [" 
				+ f.old_name + L"] na [" + f.new_name + f.GetExtension()
				+ L"] -> kod b³êdu: "+ std::to_wstring(ec.value()) +L": ")
				+ strtoustr(ec.message() + "\n"));
		else
			rtxtProgramOutput->AppendText(wstrtoustr(L"Zmiana nazwy pliku z ["
				+ f.old_name + L"] na [" + f.new_name + f.GetExtension() +L"]\n"));
	}
}

void PFV::MainForm::CreateFoldersAndMoveFiles(void)
{
	std::wstring dir_name;
	auto main_fv_dir = GetFvDirText();
	std::error_code ec;

	for (const auto& fv : Globals::vecFvFromImg)
	{
		if(fv->date.month / 10 >= 1.0)
			dir_name = std::to_wstring(fv->date.month)+L"-"+std::to_wstring(fv->date.year);
		else
			dir_name = L"0"+std::to_wstring(fv->date.month) + L"-" + std::to_wstring(fv->date.year);

		std::filesystem::create_directory(main_fv_dir +L"\\"+ dir_name);
		auto f = fv->GetFile();
		auto from = main_fv_dir + L"\\" + f->new_name + f->GetExtension();
		auto into = main_fv_dir + L"\\" + dir_name + L"\\" + f->new_name + f->GetExtension();

		std::filesystem::rename(from, into, ec);

		if(ec)
			rtxtProgramOutput->AppendText(wstrtoustr(L"Nie uda³o siê przenieœæ pliku z ["
				+ from +L"] do ["+ into +L"] ->kod b³êdu : " + std::to_wstring(ec.value()) + L": ") 
				+ strtoustr(ec.message() + "\n"));
	}
}

void PFV::MainForm::ResetFilenameLabel(void)
{
	if (Globals::curr_file != Globals::files.end())
		lblCurrentFile->Text = wstrtoustr(TrimLongFileName(Globals::curr_file->old_name));
	else
		lblCurrentFile->Text = " - ";
}
void PFV::MainForm::InitOnMouseHoverTextBox(void)
{
	if (Controls->Find(L"rtxtOnMouseHover", true)->Length)
		return;		// already initialised
	rtxtOnMouseHover = (gcnew System::Windows::Forms::RichTextBox());
	rtxtOnMouseHover->Name = L"rtxtOnMouseHover";
	rtxtOnMouseHover->BorderStyle = System::Windows::Forms::BorderStyle::None;
	rtxtOnMouseHover->ScrollBars = System::Windows::Forms::RichTextBoxScrollBars::None;
	rtxtOnMouseHover->ReadOnly = true;
	rtxtOnMouseHover->Visible = false;
	rtxtOnMouseHover->BringToFront();
	Controls->Add(rtxtOnMouseHover);
}
std::wstring PFV::MainForm::TrimLongFileName(const std::wstring & fname)
{
	std::wstring filename = fname;

	if (filename.empty())
		return filename;

	int len = filename.size() - MAX_FILENAME_LEN;	// has to be int !

	if (len < 3 && len > 0)
		filename.replace(filename.begin() + filename.size() - 4, filename.end() - 3, 3, '.');
	else if (len > 0)
		filename.replace(filename.begin() + MAX_FILENAME_LEN, filename.end(), 3, '.');

	return filename;
}

void PFV::MainForm::FillInForTests()
{
	txtCompany->Text = "Caldo";
	txtInvest->Text = "investition-test";
	txtFvIdent->Text = wstrtoustr(L"Fv-123-test"+ Globals::curr_file->old_name);
	txtNetVal->Text = "12+6/2";
	txtGrossVal->Text = "14,76";
	txtDescr->Text = "opis-test";
	txtWhoPayed->Text = "MZ";
	txtPayment->Text = "G";
	txtDay->Text = "21";
	txtMonth->Text = "11";
}
