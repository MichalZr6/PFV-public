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
			return txtCompany->Text;
		}

		USTRING getFvIdent()
		{
			return txtFvIdent->Text;
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
			txtCompany = (gcnew System::Windows::Forms::TextBox());
			label1 = (gcnew System::Windows::Forms::Label());
			txtInvQuantity = (gcnew System::Windows::Forms::TextBox());
			label3 = (gcnew System::Windows::Forms::Label());
			label4 = (gcnew System::Windows::Forms::Label());
			txtInvestition = (gcnew System::Windows::Forms::TextBox());
			label5 = (gcnew System::Windows::Forms::Label());
			txtDescription = (gcnew System::Windows::Forms::TextBox());
			label6 = (gcnew System::Windows::Forms::Label());
			txtFvIdent = (gcnew System::Windows::Forms::TextBox());
			rtxtProgramOutput = (gcnew System::Windows::Forms::RichTextBox());
			label2 = (gcnew System::Windows::Forms::Label());
			txtNetVal = (gcnew System::Windows::Forms::TextBox());
			label7 = (gcnew System::Windows::Forms::Label());
			txtGrossVal = (gcnew System::Windows::Forms::TextBox());
			rtxtHeadOutput = (gcnew System::Windows::Forms::RichTextBox());
			cbTax = (gcnew System::Windows::Forms::ComboBox());
			lblVat = (gcnew System::Windows::Forms::Label());
			panelInputs = (gcnew System::Windows::Forms::Panel());
			btnCancel = (gcnew System::Windows::Forms::Button());
			btnAdd = (gcnew System::Windows::Forms::Button());
			txtComments = (gcnew System::Windows::Forms::TextBox());
			lblComments = (gcnew System::Windows::Forms::Label());
			panelInputs->SuspendLayout();
			SuspendLayout();
			// 
			// txtCompany
			// 
			txtCompany->Enabled = false;
			txtCompany->Location = System::Drawing::Point(65, 37);
			txtCompany->Name = L"txtCompany";
			txtCompany->ReadOnly = true;
			txtCompany->Size = System::Drawing::Size(133, 20);
			txtCompany->TabIndex = 3;
			txtCompany->TabStop = false;
			// 
			// label1
			// 
			label1->AutoSize = true;
			label1->Location = System::Drawing::Point(3, 44);
			label1->Name = L"label1";
			label1->Size = System::Drawing::Size(35, 13);
			label1->TabIndex = 4;
			label1->Text = L"Firma:";
			// 
			// txtInvQuantity
			// 
			txtInvQuantity->Location = System::Drawing::Point(114, 11);
			txtInvQuantity->MaxLength = 2;
			txtInvQuantity->Name = L"txtInvQuantity";
			txtInvQuantity->ReadOnly = true;
			txtInvQuantity->Size = System::Drawing::Size(39, 20);
			txtInvQuantity->TabIndex = 1;
			txtInvQuantity->TabStop = false;
			// 
			// label3
			// 
			label3->AutoSize = true;
			label3->Location = System::Drawing::Point(3, 14);
			label3->Name = L"label3";
			label3->Size = System::Drawing::Size(89, 13);
			label3->TabIndex = 7;
			label3->Text = L"Liczba inwestycji:";
			// 
			// label4
			// 
			label4->AutoSize = true;
			label4->Location = System::Drawing::Point(3, 101);
			label4->Name = L"label4";
			label4->Size = System::Drawing::Size(60, 13);
			label4->TabIndex = 9;
			label4->Text = L"Inwestycja:";
			// 
			// txtInvestition
			// 
			txtInvestition->Location = System::Drawing::Point(65, 95);
			txtInvestition->MaxLength = 40;
			txtInvestition->Name = L"txtInvestition";
			txtInvestition->Size = System::Drawing::Size(175, 20);
			txtInvestition->TabIndex = 2;
			txtInvestition->TextChanged += gcnew System::EventHandler(this, &SplitFvForm::txtInvestition_TextChanged);
			txtInvestition->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &SplitFvForm::txtInvestition_KeyPress);
			txtInvestition->PreviewKeyDown += gcnew System::Windows::Forms::PreviewKeyDownEventHandler(this, &SplitFvForm::txtInvestition_PreviewKeyDown);
			// 
			// label5
			// 
			label5->AutoSize = true;
			label5->Location = System::Drawing::Point(3, 127);
			label5->Name = L"label5";
			label5->Size = System::Drawing::Size(31, 13);
			label5->TabIndex = 11;
			label5->Text = L"Opis:";
			// 
			// txtDescription
			// 
			txtDescription->Location = System::Drawing::Point(65, 121);
			txtDescription->MaxLength = 50;
			txtDescription->Name = L"txtDescription";
			txtDescription->Size = System::Drawing::Size(175, 20);
			txtDescription->TabIndex = 3;
			// 
			// label6
			// 
			label6->AutoSize = true;
			label6->Location = System::Drawing::Point(3, 75);
			label6->Name = L"label6";
			label6->Size = System::Drawing::Size(56, 13);
			label6->TabIndex = 13;
			label6->Text = L"Nr faktury:";
			// 
			// txtFvIdent
			// 
			txtFvIdent->Enabled = false;
			txtFvIdent->Location = System::Drawing::Point(65, 69);
			txtFvIdent->Name = L"txtFvIdent";
			txtFvIdent->ReadOnly = true;
			txtFvIdent->Size = System::Drawing::Size(133, 20);
			txtFvIdent->TabIndex = 12;
			txtFvIdent->TabStop = false;
			// 
			// rtxtProgramOutput
			// 
			rtxtProgramOutput->Anchor = static_cast<System::Windows::Forms::AnchorStyles>(((System::Windows::Forms::AnchorStyles::Top | System::Windows::Forms::AnchorStyles::Bottom)
				| System::Windows::Forms::AnchorStyles::Right));
			rtxtProgramOutput->Location = System::Drawing::Point(268, 132);
			rtxtProgramOutput->Name = L"rtxtProgramOutput";
			rtxtProgramOutput->ReadOnly = true;
			rtxtProgramOutput->ScrollBars = System::Windows::Forms::RichTextBoxScrollBars::Vertical;
			rtxtProgramOutput->Size = System::Drawing::Size(530, 332);
			rtxtProgramOutput->TabIndex = 14;
			rtxtProgramOutput->TabStop = false;
			rtxtProgramOutput->Text = L"";
			// 
			// label2
			// 
			label2->AutoSize = true;
			label2->Location = System::Drawing::Point(2, 153);
			label2->Name = L"label2";
			label2->Size = System::Drawing::Size(63, 13);
			label2->TabIndex = 16;
			label2->Text = L"Wart. netto:";
			// 
			// txtNetVal
			// 
			txtNetVal->Location = System::Drawing::Point(74, 147);
			txtNetVal->Name = L"txtNetVal";
			txtNetVal->Size = System::Drawing::Size(79, 20);
			txtNetVal->TabIndex = 5;
			txtNetVal->Enter += gcnew System::EventHandler(this, &SplitFvForm::txtNetVal_Enter);
			// 
			// label7
			// 
			label7->AutoSize = true;
			label7->Location = System::Drawing::Point(2, 183);
			label7->Name = L"label7";
			label7->Size = System::Drawing::Size(66, 13);
			label7->TabIndex = 18;
			label7->Text = L"Wart. brutto:";
			// 
			// txtGrossVal
			// 
			txtGrossVal->Location = System::Drawing::Point(74, 173);
			txtGrossVal->Name = L"txtGrossVal";
			txtGrossVal->Size = System::Drawing::Size(79, 20);
			txtGrossVal->TabIndex = 7;
			txtGrossVal->Enter += gcnew System::EventHandler(this, &SplitFvForm::txtGrossVal_Enter);
			txtGrossVal->Leave += gcnew System::EventHandler(this, &SplitFvForm::txtGrossVal_Leave);
			// 
			// rtxtHeadOutput
			// 
			rtxtHeadOutput->Location = System::Drawing::Point(268, 6);
			rtxtHeadOutput->Name = L"rtxtHeadOutput";
			rtxtHeadOutput->ReadOnly = true;
			rtxtHeadOutput->ScrollBars = System::Windows::Forms::RichTextBoxScrollBars::None;
			rtxtHeadOutput->Size = System::Drawing::Size(530, 120);
			rtxtHeadOutput->TabIndex = 20;
			rtxtHeadOutput->TabStop = false;
			rtxtHeadOutput->Text = L"";
			// 
			// cbTax
			// 
			cbTax->FormattingEnabled = true;
			cbTax->Items->AddRange(gcnew cli::array< System::Object^  >(3) { L"23", L"8", L"zw" });
			cbTax->Location = System::Drawing::Point(195, 147);
			cbTax->Name = L"cbTax";
			cbTax->Size = System::Drawing::Size(45, 21);
			cbTax->TabIndex = 6;
			cbTax->Text = L"23";
			// 
			// lblVat
			// 
			lblVat->AutoSize = true;
			lblVat->Location = System::Drawing::Point(158, 150);
			lblVat->Name = L"lblVat";
			lblVat->Size = System::Drawing::Size(31, 13);
			lblVat->TabIndex = 21;
			lblVat->Text = L"VAT:";
			// 
			// panelInputs
			// 
			panelInputs->AutoSize = true;
			panelInputs->AutoSizeMode = System::Windows::Forms::AutoSizeMode::GrowAndShrink;
			panelInputs->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			panelInputs->Controls->Add(btnCancel);
			panelInputs->Controls->Add(btnAdd);
			panelInputs->Controls->Add(txtComments);
			panelInputs->Controls->Add(lblComments);
			panelInputs->Controls->Add(txtCompany);
			panelInputs->Controls->Add(cbTax);
			panelInputs->Controls->Add(txtGrossVal);
			panelInputs->Controls->Add(lblVat);
			panelInputs->Controls->Add(txtInvQuantity);
			panelInputs->Controls->Add(txtFvIdent);
			panelInputs->Controls->Add(txtNetVal);
			panelInputs->Controls->Add(label3);
			panelInputs->Controls->Add(label7);
			panelInputs->Controls->Add(txtDescription);
			panelInputs->Controls->Add(label1);
			panelInputs->Controls->Add(txtInvestition);
			panelInputs->Controls->Add(label4);
			panelInputs->Controls->Add(label2);
			panelInputs->Controls->Add(label5);
			panelInputs->Controls->Add(label6);
			panelInputs->Dock = System::Windows::Forms::DockStyle::Left;
			panelInputs->Location = System::Drawing::Point(0, 0);
			panelInputs->Margin = System::Windows::Forms::Padding(10);
			panelInputs->Name = L"panelInputs";
			panelInputs->Padding = System::Windows::Forms::Padding(10);
			panelInputs->Size = System::Drawing::Size(255, 462);
			panelInputs->TabIndex = 22;
			// 
			// btnCancel
			// 
			btnCancel->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Right));
			btnCancel->Location = System::Drawing::Point(165, 431);
			btnCancel->Name = L"btnCancel";
			btnCancel->Size = System::Drawing::Size(75, 23);
			btnCancel->TabIndex = 14;
			btnCancel->Text = L"Anuluj";
			btnCancel->UseVisualStyleBackColor = true;
			btnCancel->Click += gcnew System::EventHandler(this, &SplitFvForm::btnCancel_Click);
			// 
			// btnAdd
			// 
			btnAdd->Anchor = static_cast<System::Windows::Forms::AnchorStyles>((System::Windows::Forms::AnchorStyles::Bottom | System::Windows::Forms::AnchorStyles::Left));
			btnAdd->Location = System::Drawing::Point(6, 431);
			btnAdd->Name = L"btnAdd";
			btnAdd->Size = System::Drawing::Size(75, 23);
			btnAdd->TabIndex = 12;
			btnAdd->Text = L"Dodaj";
			btnAdd->UseVisualStyleBackColor = true;
			btnAdd->Click += gcnew System::EventHandler(this, &SplitFvForm::btnAdd_Click);
			// 
			// txtComments
			// 
			txtComments->Location = System::Drawing::Point(65, 199);
			txtComments->MaxLength = 100;
			txtComments->Name = L"txtComments";
			txtComments->Size = System::Drawing::Size(175, 20);
			txtComments->TabIndex = 8;
			// 
			// lblComments
			// 
			lblComments->AutoSize = true;
			lblComments->Location = System::Drawing::Point(3, 205);
			lblComments->Name = L"lblComments";
			lblComments->Size = System::Drawing::Size(60, 13);
			lblComments->TabIndex = 23;
			lblComments->Text = L"Komentarz:";
			// 
			// SplitFvForm
			// 
			AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			ClientSize = System::Drawing::Size(804, 462);
			Controls->Add(panelInputs);
			Controls->Add(rtxtHeadOutput);
			Controls->Add(rtxtProgramOutput);
			MaximumSize = System::Drawing::Size(820, 700);
			MinimumSize = System::Drawing::Size(820, 300);
			Name = L"SplitFvForm";
			Text = L"Podzia³ faktury na ró¿ne inwestycje";
			Load += gcnew System::EventHandler(this, &SplitFvForm::SplitFvForm_Load);
			panelInputs->ResumeLayout(false);
			panelInputs->PerformLayout();
			ResumeLayout(false);
			PerformLayout();

		}
#pragma endregion
	private: System::Void btnAdd_Click(System::Object^ sender, System::EventArgs^ e);
	private: System::Void btnCancel_Click(System::Object^ sender, System::EventArgs^ e)
	{
		Close();
	}
	private: System::Void txtInvestition_TextChanged(System::Object^ sender, System::EventArgs^ e);
	private: System::Void txtInvestition_KeyPress(System::Object^ sender,
		System::Windows::Forms::KeyPressEventArgs^ e)
	{
		if (numberKeyPressed)
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
