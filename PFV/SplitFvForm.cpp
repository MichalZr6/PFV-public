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
	if (Controls->Find(L"rtxtDynamicOutput", true)->Length)
		return;
	rtxtDynamicOutput = (gcnew System::Windows::Forms::RichTextBox());
	rtxtDynamicOutput->Name = L"rtxtDynamicOutput";
	rtxtDynamicOutput->ReadOnly = true;
	rtxtDynamicOutput->ScrollBars =
		System::Windows::Forms::RichTextBoxScrollBars::None;
	rtxtDynamicOutput->Size =
		System::Drawing::Size(txtInvestition->Width, (MAX_DYNAMIC_SHOW + 1) * 15);
	rtxtDynamicOutput->TabStop = false;
	rtxtDynamicOutput->Text = L"";
	rtxtDynamicOutput->Visible = false;
	Controls->Add(rtxtDynamicOutput);

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
		splitCount++;
		return false;
	}
	else
		return true;
}

Fv_ptr ProjektFaktury::SplitFvForm::FvInfoFromInputs(const FvInfo& base)
{
	std::string errmsg{ "" };
	auto fv = std::make_unique<FvInfo>(base);

	System::String::IsNullOrWhiteSpace(txtInvestition->Text) ?
		errmsg += "Wymagane jest podanie nazwy inwestycji.\n" :
		fv->SetInvestition(ustrtowstr(txtInvestition->Text));

		fv->SetDescription(ustrtowstr(txtDescription->Text));

	if (!errmsg.empty())
	{
		System::Exception^ e = gcnew System::Exception(strtoustr(errmsg));
		e->Source = "Pola tekstowe";
		throw e;
	}

	fv->SetNetValue(ustrtostr(txtNetVal->Text));
	fv->SetGrossValue(ustrtostr(txtGrossVal->Text));
	fv->comments = ustrtowstr(txtComments->Text);

	return fv;
}

void ProjektFaktury::SplitFvForm::btnAdd_Click
(System::Object^ sender, System::EventArgs^ e)
{
	splitCount--;

	FvInfo partFv;

	if (splitCount >= 1)
	{
		try
		{
			partFv = *FvInfoFromInputs(*Globals::vecFvFromImg.back());
			Globals::fvSplitter->SetPartFv(partFv);
		}
		catch (System::Exception^ e)
		{
			MessageBox::Show("B³¹d spowodowany przez: " + e->Source
				+ "\nOpis: " + e->Message);
			return;
		}

		if (CheckSplit())
		{
			rtxtProgramOutput->AppendText(FvToOutput(partFv));
			ManageForm(FormState::ADDING_DELETING);

			if (splitCount == 1)
			{
				rtxtProgramOutput->AppendText(FvToOutput(*Globals::vecFvFromImg.back()));
				ManageForm(FormState::NO_MORE_LEFT);
			}
		}
	}
	else
		Hide();
}

void ProjektFaktury::SplitFvForm::txtInvestition_TextChanged
(System::Object^ sender, System::EventArgs^ e)
{
	std::unordered_set<std::wstring> searchResult;
	auto const search_string{ ustrtowstr(txtInvestition->Text->ToString()) };
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
		Globals::fv_list.SearchInvestition(search_string, searchResult);		// search in records from XLS file
		Globals::SearchInvestition(search_string, searchResult);			// search in already added FvInfo companies

		auto sc = search_string;

		if (searchResult.size() > 0)
		{
			rtxtDynamicOutput->Visible = true;
			rtxtDynamicOutput->Text = "Wybierz z klawiatury nr inwestycji:\n";
			for (auto const &it : searchResult)
			{
				std::wstring inv = it;
				if (i > MAX_DYNAMIC_SHOW) break;
				if (wstr_tolower(sc) == wstr_tolower(inv))
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
(System::Object^ sender, System::Windows::Forms::PreviewKeyDownEventArgs^ e)
{
	if (e->KeyCode >= Keys::D1 && e->KeyCode <= Keys::D9
		&& static_cast<int>(e->KeyCode) - 48 <= MAX_DYNAMIC_SHOW
		&& Globals::currShown.size() != 0
		&& txtInvestition->Text->Length > TEXT_LEN_SHOW_ACTIVATE)
	{
		txtInvestition->Text = wstrtoustr(Globals::currShown[static_cast<int>(e->KeyCode) - 48]);
		txtDescription->Focus();
		numberKeyPressed = true;
		rtxtDynamicOutput->Visible = false;
	}
	else if (e->KeyCode == Keys::Tab
		&& Globals::currShown.size() != 0
		&& txtInvestition->Text->Length > TEXT_LEN_SHOW_ACTIVATE)
	{
		txtInvestition->Text = wstrtoustr(Globals::currShown[1]);
		numberKeyPressed = true;
		rtxtDynamicOutput->Visible = false;
	}
	else
		numberKeyPressed = false;
}

void ProjektFaktury::SplitFvForm::SplitFvForm_Load
(System::Object^ sender, System::EventArgs^ e)
{
	FvInfo lastFv = *Globals::vecFvFromImg.back();
	rtxtHeadOutput->AppendText("Podzielona zostanie faktura:\n");

	rtxtHeadOutput->AppendText(FvToOutput(lastFv));

	txtCompany->Text = wstrtoustr(lastFv.GetCompany());
	txtFvIdent->Text = wstrtoustr(lastFv.GetInvoiceNumber());

	split_form = gcnew SplitCountAskForm(txtCompany->Text, txtFvIdent->Text);
	Hide();
	split_form->ShowDialog();
	if (split_form->is_valid_data)
	{
		splitCount = split_form->inv_count;
		txtInvQuantity->Text = System::Convert::ToString(splitCount);
	}
	else
		Close();

	Globals::fvSplitter.reset(new FvSplit(lastFv, splitCount));

	split_form->~SplitCountAskForm();
}
