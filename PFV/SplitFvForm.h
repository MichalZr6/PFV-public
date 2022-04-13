#pragma once

#include "Globals.h"
#include "FvClasses.h"
#include "Functions.h"
#include "SplitCountAskForm.h"

namespace ProjektFaktury {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for additional_form
	/// </summary>
	public ref class SplitFvForm : public System::Windows::Forms::Form
	{
	public:
		SplitCountAskForm^ split_form;
	private: System::Windows::Forms::RichTextBox^ rtxtHeadOutput;
	private: System::Windows::Forms::ComboBox^ cbTax;
	private: System::Windows::Forms::Label^ lblVat;
	private: System::Windows::Forms::Panel^ panelInputs;

	private: System::Windows::Forms::TextBox^ txtComments;
	private: System::Windows::Forms::Label^ lblComments;
	private: System::Windows::Forms::Button^ btnCancel;
	private: System::Windows::Forms::Button^ btnAdd;

	public:

	private: bool numberKeyPressed = false;
	public:
		SplitFvForm(void)
		{
			InitializeComponent();
			InitDynamicOutputBox();
		}

	private:

		void ManageForm(FormState state);

		Fv_ptr FvInfoFromInputs(const FvInfo& base);
		void InitDynamicOutputBox();
		void ClearInputs();
		bool CheckSplit();


	public:

		unsigned short splitCount;

		USTRING getCompName()
		{
			return this->txtCompany->Text;
		}

		USTRING getFvIdent()
		{
			return this->txtFvIdent->Text;
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~SplitFvForm()
		{
			if (components)
			{
				delete components;
			}
		}



	private: System::Windows::Forms::TextBox^ txtCompany;
	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::TextBox^ txtInvQuantity;
	private: System::Windows::Forms::Label^ label3;
	private: System::Windows::Forms::Label^ label4;
	private: System::Windows::Forms::TextBox^ txtInvestition;
	private: System::Windows::Forms::Label^ label5;
	private: System::Windows::Forms::TextBox^ txtDescription;
	private: System::Windows::Forms::Label^ label6;
	private: System::Windows::Forms::TextBox^ txtFvIdent;
	private: System::Windows::Forms::RichTextBox^ rtxtProgramOutput;
	private: System::Windows::Forms::RichTextBox^ rtxtDynamicOutput;
	private: System::Windows::Forms::Label^ label2;
	private: System::Windows::Forms::TextBox^ txtNetVal;
	private: System::Windows::Forms::Label^ label7;
	private: System::Windows::Forms::TextBox^ txtGrossVal;


	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container^ components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->txtCompany = (gcnew System::Windows::Forms::TextBox());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->txtInvQuantity = (gcnew System::Windows::Forms::TextBox());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->txtInvestition = (gcnew System::Windows::Forms::TextBox());
			this->label5 = (gcnew System::Windows::Forms::Label());
			this->txtDescription = (gcnew System::Windows::Forms::TextBox());
			this->label6 = (gcnew System::Windows::Forms::Label());
			this->txtFvIdent = (gcnew System::Windows::Forms::TextBox());
			this->rtxtProgramOutput = (gcnew System::Windows::Forms::RichTextBox());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->txtNetVal = (gcnew System::Windows::Forms::TextBox());
			this->label7 = (gcnew System::Windows::Forms::Label());
			this->txtGrossVal = (gcnew System::Windows::Forms::TextBox());
			this->rtxtHeadOutput = (gcnew System::Windows::Forms::RichTextBox());
			this->cbTax = (gcnew System::Windows::Forms::ComboBox());
			this->lblVat = (gcnew System::Windows::Forms::Label());
			this->panelInputs = (gcnew System::Windows::Forms::Panel());
			this->btnCancel = (gcnew System::Windows::Forms::Button());
			this->btnAdd = (gcnew System::Windows::Forms::Button());
			this->txtComments = (gcnew System::Windows::Forms::TextBox());
			this->lblComments = (gcnew System::Windows::Forms::Label());
			this->panelInputs->SuspendLayout();
			this->SuspendLayout();
			// 
			// txtCompany
			// 
			this->txtCompany->Enabled = false;
			this->txtCompany->Location = System::Drawing::Point(65, 37);
			this->txtCompany->Name = L"txtCompany";
			this->txtCompany->ReadOnly = true;
			this->txtCompany->Size = System::Drawing::Size(133, 20);
			this->txtCompany->TabIndex = 3;
			this->txtCompany->TabStop = false;
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(3, 44);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(35, 13);
			this->label1->TabIndex = 4;
			this->label1->Text = L"Firma:";
			// 
			// txtInvQuantity
			// 
			this->txtInvQuantity->Location = System::Drawing::Point(114, 11);
			this->txtInvQuantity->MaxLength = 2;
			this->txtInvQuantity->Name = L"txtInvQuantity";
			this->txtInvQuantity->ReadOnly = true;
			this->txtInvQuantity->Size = System::Drawing::Size(39, 20);
			this->txtInvQuantity->TabIndex = 1;
			this->txtInvQuantity->TabStop = false;
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Location = System::Drawing::Point(3, 14);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(89, 13);
			this->label3->TabIndex = 7;
			this->label3->Text = L"Liczba inwestycji:";
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->Location = System::Drawing::Point(3, 101);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(60, 13);
			this->label4->TabIndex = 9;
			this->label4->Text = L"Inwestycja:";
			// 
			// txtInvestition
			// 
			this->txtInvestition->Location = System::Drawing::Point(65, 95);
			this->txtInvestition->MaxLength = 40;
			this->txtInvestition->Name = L"txtInvestition";
			this->txtInvestition->Size = System::Drawing::Size(175, 20);
			this->txtInvestition->TabIndex = 2;
			this->txtInvestition->TextChanged += gcnew System::EventHandler(this, &SplitFvForm::txtInvestition_TextChanged);
			this->txtInvestition->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &SplitFvForm::txtInvestition_KeyPress);
			this->txtInvestition->PreviewKeyDown += gcnew System::Windows::Forms::PreviewKeyDownEventHandler(this, &SplitFvForm::txtInvestition_PreviewKeyDown);
			// 
			// label5
			// 
			this->label5->AutoSize = true;
			this->label5->Location = System::Drawing::Point(3, 127);
			this->label5->Name = L"label5";
			this->label5->Size = System::Drawing::Size(31, 13);
			this->label5->TabIndex = 11;
			this->label5->Text = L"Opis:";
			// 
			// txtDescription
			// 
			this->txtDescription->Location = System::Drawing::Point(65, 121);
			this->txtDescription->MaxLength = 50;
			this->txtDescription->Name = L"txtDescription";
			this->txtDescription->Size = System::Drawing::Size(175, 20);
			this->txtDescription->TabIndex = 3;
			// 
			// label6
			// 
			this->label6->AutoSize = true;
			this->label6->Location = System::Drawing::Point(3, 75);
			this->label6->Name = L"label6";
			this->label6->Size = System::Drawing::Size(56, 13);
			this->label6->TabIndex = 13;
			this->label6->Text = L"Nr faktury:";
			// 
			// txtFvIdent
			// 
			this->txtFvIdent->Enabled = false;
			this->txtFvIdent->Location = System::Drawing::Point(65, 69);
			this->txtFvIdent->Name = L"txtFvIdent";
			this->txtFvIdent->ReadOnly = true;
			this->txtFvIdent->Size = System::Drawing::Size(133, 20);
			this->txtFvIdent->TabIndex = 12;
			this->txtFvIdent->TabStop = false;
			// 
			// rtxtProgramOutput
			// 
			this->rtxtProgramOutput->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				| System::Windows::Forms::AnchorStyles::Right));
			this->rtxtProgramOutput->Location = System::Drawing::Point(268, 132);
			this->rtxtProgramOutput->Name = L"rtxtProgramOutput";
			this->rtxtProgramOutput->ReadOnly = true;
			this->rtxtProgramOutput->ScrollBars = System::Windows::Forms::RichTextBoxScrollBars::Vertical;
			this->rtxtProgramOutput->Size = System::Drawing::Size(530, 332);
			this->rtxtProgramOutput->TabIndex = 14;
			this->rtxtProgramOutput->TabStop = false;
			this->rtxtProgramOutput->Text = L"";
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(2, 153);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(63, 13);
			this->label2->TabIndex = 16;
			this->label2->Text = L"Wart. netto:";
			// 
			// txtNetVal
			// 
			this->txtNetVal->Location = System::Drawing::Point(74, 147);
			this->txtNetVal->Name = L"txtNetVal";
			this->txtNetVal->Size = System::Drawing::Size(79, 20);
			this->txtNetVal->TabIndex = 5;
			this->txtNetVal->Enter += gcnew System::EventHandler(this, &SplitFvForm::txtNetVal_Enter);
			// 
			// label7
			// 
			this->label7->AutoSize = true;
			this->label7->Location = System::Drawing::Point(2, 183);
			this->label7->Name = L"label7";
			this->label7->Size = System::Drawing::Size(66, 13);
			this->label7->TabIndex = 18;
			this->label7->Text = L"Wart. brutto:";
			// 
			// txtGrossVal
			// 
			this->txtGrossVal->Location = System::Drawing::Point(74, 173);
			this->txtGrossVal->Name = L"txtGrossVal";
			this->txtGrossVal->Size = System::Drawing::Size(79, 20);
			this->txtGrossVal->TabIndex = 7;
			this->txtGrossVal->Enter += gcnew System::EventHandler(this, &SplitFvForm::txtGrossVal_Enter);
			this->txtGrossVal->Leave += gcnew System::EventHandler(this, &SplitFvForm::txtGrossVal_Leave);
			// 
			// rtxtHeadOutput
			// 
			this->rtxtHeadOutput->Location = System::Drawing::Point(268, 6);
			this->rtxtHeadOutput->Name = L"rtxtHeadOutput";
			this->rtxtHeadOutput->ReadOnly = true;
			this->rtxtHeadOutput->ScrollBars = System::Windows::Forms::RichTextBoxScrollBars::None;
			this->rtxtHeadOutput->Size = System::Drawing::Size(530, 120);
			this->rtxtHeadOutput->TabIndex = 20;
			this->rtxtHeadOutput->TabStop = false;
			this->rtxtHeadOutput->Text = L"";
			// 
			// cbTax
			// 
			this->cbTax->FormattingEnabled = true;
			this->cbTax->Items->AddRange(gcnew cli::array< System::Object^  >(3) { L"23", L"8", L"zw" });
			this->cbTax->Location = System::Drawing::Point(195, 147);
			this->cbTax->Name = L"cbTax";
			this->cbTax->Size = System::Drawing::Size(45, 21);
			this->cbTax->TabIndex = 6;
			this->cbTax->Text = L"23";
			// 
			// lblVat
			// 
			this->lblVat->AutoSize = true;
			this->lblVat->Location = System::Drawing::Point(158, 150);
			this->lblVat->Name = L"lblVat";
			this->lblVat->Size = System::Drawing::Size(31, 13);
			this->lblVat->TabIndex = 21;
			this->lblVat->Text = L"VAT:";
			// 
			// panelInputs
			// 
			this->panelInputs->AutoSize = true;
			this->panelInputs->AutoSizeMode = System::Windows::Forms::AutoSizeMode::GrowAndShrink;
			this->panelInputs->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->panelInputs->Controls->Add(this->btnCancel);
			this->panelInputs->Controls->Add(this->btnAdd);
			this->panelInputs->Controls->Add(this->txtComments);
			this->panelInputs->Controls->Add(this->lblComments);
			this->panelInputs->Controls->Add(this->txtCompany);
			this->panelInputs->Controls->Add(this->cbTax);
			this->panelInputs->Controls->Add(this->txtGrossVal);
			this->panelInputs->Controls->Add(this->lblVat);
			this->panelInputs->Controls->Add(this->txtInvQuantity);
			this->panelInputs->Controls->Add(this->txtFvIdent);
			this->panelInputs->Controls->Add(this->txtNetVal);
			this->panelInputs->Controls->Add(this->label3);
			this->panelInputs->Controls->Add(this->label7);
			this->panelInputs->Controls->Add(this->txtDescription);
			this->panelInputs->Controls->Add(this->label1);
			this->panelInputs->Controls->Add(this->txtInvestition);
			this->panelInputs->Controls->Add(this->label4);
			this->panelInputs->Controls->Add(this->label2);
			this->panelInputs->Controls->Add(this->label5);
			this->panelInputs->Controls->Add(this->label6);
			this->panelInputs->Dock = System::Windows::Forms::DockStyle::Left;
			this->panelInputs->Location = System::Drawing::Point(0, 0);
			this->panelInputs->Margin = System::Windows::Forms::Padding(10);
			this->panelInputs->Name = L"panelInputs";
			this->panelInputs->Padding = System::Windows::Forms::Padding(10);
			this->panelInputs->Size = System::Drawing::Size(255, 462);
			this->panelInputs->TabIndex = 22;
			// 
			// btnCancel
			// 
			this->btnCancel->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Right));
			this->btnCancel->Location = System::Drawing::Point(165, 431);
			this->btnCancel->Name = L"btnCancel";
			this->btnCancel->Size = System::Drawing::Size(75, 23);
			this->btnCancel->TabIndex = 14;
			this->btnCancel->Text = L"Anuluj";
			this->btnCancel->UseVisualStyleBackColor = true;
			this->btnCancel->Click += gcnew System::EventHandler(this, &SplitFvForm::btnCancel_Click);
			// 
			// btnAdd
			// 
			this->btnAdd->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Left));
			this->btnAdd->Location = System::Drawing::Point(6, 431);
			this->btnAdd->Name = L"btnAdd";
			this->btnAdd->Size = System::Drawing::Size(75, 23);
			this->btnAdd->TabIndex = 12;
			this->btnAdd->Text = L"Dodaj";
			this->btnAdd->UseVisualStyleBackColor = true;
			this->btnAdd->Click += gcnew System::EventHandler(this, &SplitFvForm::btnAdd_Click);
			// 
			// txtComments
			// 
			this->txtComments->Location = System::Drawing::Point(65, 199);
			this->txtComments->MaxLength = 100;
			this->txtComments->Name = L"txtComments";
			this->txtComments->Size = System::Drawing::Size(175, 20);
			this->txtComments->TabIndex = 8;
			// 
			// lblComments
			// 
			this->lblComments->AutoSize = true;
			this->lblComments->Location = System::Drawing::Point(3, 205);
			this->lblComments->Name = L"lblComments";
			this->lblComments->Size = System::Drawing::Size(60, 13);
			this->lblComments->TabIndex = 23;
			this->lblComments->Text = L"Komentarz:";
			// 
			// SplitFvForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(804, 462);
			this->Controls->Add(this->panelInputs);
			this->Controls->Add(this->rtxtHeadOutput);
			this->Controls->Add(this->rtxtProgramOutput);
			this->MaximumSize = System::Drawing::Size(820, 700);
			this->MinimumSize = System::Drawing::Size(820, 300);
			this->Name = L"SplitFvForm";
			this->Text = L"Podzia³ faktury na ró¿ne inwestycje";
			this->Load += gcnew System::EventHandler(this, &SplitFvForm::SplitFvForm_Load);
			this->panelInputs->ResumeLayout(false);
			this->panelInputs->PerformLayout();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void btnAdd_Click(System::Object^ sender, System::EventArgs^ e);
	private: System::Void btnCancel_Click(System::Object^ sender, System::EventArgs^ e)
	{
		this->Close();
	}
	private: System::Void txtInvestition_TextChanged(System::Object^ sender, System::EventArgs^ e);
	private: System::Void txtInvestition_KeyPress(System::Object^ sender,
		System::Windows::Forms::KeyPressEventArgs^ e)
	{
		if (this->numberKeyPressed)
			e->Handled = true;
	}
	private: System::Void txtInvestition_PreviewKeyDown(System::Object^ sender,
		System::Windows::Forms::PreviewKeyDownEventArgs^ e);
	private: System::Void SplitFvForm_Load(System::Object^ sender, System::EventArgs^ e);
	private: System::Void txtGrossVal_Enter(System::Object^ sender, System::EventArgs^ e)
	{
		Globals::AutoFillOtherPriceTBox(txtNetVal, txtGrossVal, Globals::GetTaxFromCBox(cbTax));
	}
	private: System::Void txtNetVal_Enter(System::Object^ sender, System::EventArgs^ e)
	{
		Globals::AutoFillOtherPriceTBox(txtGrossVal, txtNetVal, Globals::GetTaxFromCBox(cbTax));
	}
	private: System::Void txtGrossVal_Leave(System::Object^ sender, System::EventArgs^ e)
	{
		Globals::AutoFillOtherPriceTBox(txtGrossVal, txtNetVal, Globals::GetTaxFromCBox(cbTax));
	}
	};
}
