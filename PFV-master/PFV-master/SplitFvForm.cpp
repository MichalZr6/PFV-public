#include "SplitFvForm.h"

void ProjektFaktury::SplitFvForm::ManageForm(FormState state)
{
	switch (state)
	{
	case STARTING:
		break;
	case NO_MORE_LEFT:
		rtxtProgramOutput->AppendText
		("\nWyczerpano iloœæ dalszych podzia³ów faktury");
		ClearInputs();
		btnAdd->Text = "Zapisz";
		btnAdd->Focus();
		break;
	case ADDING_DELETING:
		ClearInputs();
		txtInvestition->Focus();
		break;
	default:
		assert("No state with code: [" 
			+ System::Convert::ToString(state) + "] was specified.");
		break;
	}
}

void ProjektFaktury::SplitFvForm::InitDynamicOutputBox()
{
	if (this->Controls->Find(L"rtxtDynamicOutput", true)->Length)
		return;
	this->rtxtDynamicOutput = (gcnew System::Windows::Forms::RichTextBox());
	this->rtxtDynamicOutput->Name = L"rtxtDynamicOutput";
	this->rtxtDynamicOutput->ReadOnly = true;
	this->rtxtDynamicOutput->ScrollBars =
		System::Windows::Forms::RichTextBoxScrollBars::None;
	this->rtxtDynamicOutput->Size =
		System::Drawing::Size(txtInvestition->Width, (MAX_DYNAMIC_SHOW + 1) * 15);
	this->rtxtDynamicOutput->TabStop = false;
	this->rtxtDynamicOutput->Text = L"";
	this->rtxtDynamicOutput->Visible = false;
	this->Controls->Add(this->rtxtDynamicOutput);

}

void ProjektFaktury::SplitFvForm::ClearInputs()
{
	txtNetVal->Clear();
	txtGrossVal->Clear();
	txtInvestition->Clear();
	txtDescription->Clear();
	txtComments->Clear();
}

bool ProjektFaktury::SplitFvForm::CheckSplit()
{
	if (!Globals::fvSplitter->isValidSplit())
	{
		MessageBox::Show("Nieprawid³owe dane.\nWartoœæ netto i/lub brutto"
			+ " faktur jest b³êdna. Problem mo¿e wystêpowaæ w przypadku podania ujemnych"
			+ " i dodatnich wartoœci jednoczeœnie dla faktury bazowej i faktury czêœciowej.");
		txtNetVal->Clear();
		txtGrossVal->Clear();
		txtNetVal->Focus();
		this->splitCount++;
		return false;
	}
	else
		return true;
}

std::unique_ptr<FvInfo> ProjektFaktury::SplitFvForm::FvInfoFromInputs(const FvInfo &base)
{
	std::string errmsg{ "" };
	auto fv = std::make_unique<FvInfo>(base);

	System::String::IsNullOrWhiteSpace(txtInvestition->Text) ?
		errmsg += "Wymagane jest podanie nazwy inwestycji.\n" :
		fv->SetInvestition(ustrtowstr(txtInvestition->Text));

	System::String::IsNullOrWhiteSpace(txtDescription->Text) ?
		errmsg += "Wymagane jest podanie opisu inwestycji.\n" :
		fv->SetDescription(ustrtowstr(txtDescription->Text));

	if (!errmsg.empty())
	{
		System::Exception ^e = gcnew System::Exception(strtoustr(errmsg));
		e->Source = "Pola tekstowe";
		throw e;
	}

	fv->SetNetValue(ustrtostr(txtNetVal->Text));
	fv->SetGrossValue(ustrtostr(txtGrossVal->Text));
	fv->comments = ustrtowstr(txtComments->Text);

	return fv;
}

void ProjektFaktury::SplitFvForm::btnAdd_Click
		(System::Object ^ sender, System::EventArgs ^ e)
{
	this->splitCount--;

	FvInfo partFv;

	if (splitCount >= 1)
	{
		try
		{
			partFv = *this->FvInfoFromInputs(*Globals::vecFvFromImg.back());
			Globals::fvSplitter->SetPartFv(partFv);
		}
		catch (System::Exception ^e)
		{
			MessageBox::Show("B³¹d spowodowany przez: " + e->Source 
				+ "\nOpis: " + e->Message);
			return;
		}

		if(CheckSplit())
		{
			rtxtProgramOutput->AppendText(FvToOutput(partFv));
			ManageForm(FormState::ADDING_DELETING);

			if (this->splitCount == 1)
			{
				rtxtProgramOutput->AppendText(FvToOutput(*Globals::vecFvFromImg.back()));
				ManageForm(FormState::NO_MORE_LEFT);
			}
		}
	}
	else
		this->Hide();
}

void ProjektFaktury::SplitFvForm::txtInvestition_TextChanged
			(System::Object ^ sender, System::EventArgs ^ e)
{
	std::unordered_set<std::wstring> inv_set;
	std::wstring search_string = ustrtowstr(txtInvestition->Text->ToString());
	unsigned short int i = 1;

	rtxtDynamicOutput->Clear();
	Globals::currShown.clear();

	rtxtDynamicOutput->Location =
		txtInvestition->FindForm()->PointToClient(txtInvestition->Parent->PointToScreen(
			System::Drawing::Point(
				txtInvestition->Location.X, txtInvestition->Location.Y + txtInvestition->Height)));
	rtxtDynamicOutput->BringToFront();

	if (txtInvestition->Text->Length > TEXT_LEN_SHOW_ACTIVATE)
	{
		Globals::fv_list.SearchInvestition(search_string, inv_set);		// search in records from XLS file
		Globals::SearchInvestition(search_string, inv_set);			// search in already added FvInfo companies

		if (inv_set.size() > 0)
		{
			rtxtDynamicOutput->Visible = true;
			rtxtDynamicOutput->Text = "Wybierz z klawiatury nr inwestycji:\n";
			for (auto &it : inv_set)
			{
				if (i > MAX_DYNAMIC_SHOW) break;
				if (str_tolower(search_string) == str_tolower(it))
				{
					txtInvestition->Text = wstrtoustr(it);
					txtDescription->Focus();
					rtxtDynamicOutput->Visible = false;
					break;
				}

				Globals::currShown[i] = it;
				rtxtDynamicOutput->AppendText(strtoustr(std::to_string(i) + ". "));
				rtxtDynamicOutput->AppendText(wstrtoustr(it) + "\n");
				i++;
			}
		}
		else rtxtDynamicOutput->Visible = false;
	}
	else rtxtDynamicOutput->Visible = false;
}

void ProjektFaktury::SplitFvForm::txtInvestition_PreviewKeyDown
		(System::Object ^ sender, System::Windows::Forms::PreviewKeyDownEventArgs ^ e)
{
	if (e->KeyCode >= Keys::D1 && e->KeyCode <= Keys::D9
		&& static_cast<int>(e->KeyCode) - 48 <= MAX_DYNAMIC_SHOW
		&& Globals::currShown.size() != 0
		&& txtInvestition->Text->Length > TEXT_LEN_SHOW_ACTIVATE)
	{
		txtInvestition->Text = wstrtoustr(Globals::currShown[static_cast<int>(e->KeyCode) - 48]);
		txtDescription->Focus();
		this->numberKeyPressed = true;
		rtxtDynamicOutput->Visible = false;
	}
	else if (e->KeyCode == Keys::Tab
		&& Globals::currShown.size() != 0
		&& txtInvestition->Text->Length > TEXT_LEN_SHOW_ACTIVATE)
	{
		txtInvestition->Text = wstrtoustr(Globals::currShown[1]);
		this->numberKeyPressed = true;
		rtxtDynamicOutput->Visible = false;
	}
	else
		this->numberKeyPressed = false;
}

void ProjektFaktury::SplitFvForm::SplitFvForm_Load
		(System::Object ^ sender, System::EventArgs ^ e)
{
	FvInfo lastFv = *Globals::vecFvFromImg.back();
	rtxtHeadOutput->AppendText("Podzielona zostanie faktura:\n");

	rtxtHeadOutput->AppendText(FvToOutput(lastFv));

	this->txtCompany->Text = wstrtoustr(lastFv.GetCompany());
	this->txtFvIdent->Text = wstrtoustr(lastFv.GetInvoiceNumber());

	split_form = gcnew SplitCountAskForm(txtCompany->Text, txtFvIdent->Text);
	this->Hide();
	split_form->ShowDialog();
	if (split_form->is_valid_data)
	{
		this->splitCount = split_form->inv_count;
		txtInvQuantity->Text = System::Convert::ToString(this->splitCount);
	}
	else
		this->Close();

	Globals::fvSplitter.reset(new FvSplit(lastFv, this->splitCount));
	
	split_form->~SplitCountAskForm();
}
