#pragma once

namespace ProjektFaktury {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Summary for SplitCountAskForm
	/// </summary>
	public ref class SplitCountAskForm : public System::Windows::Forms::Form
	{
	public:
		SplitCountAskForm(void)
		{
			InitializeComponent();
		}
		
		SplitCountAskForm(System::String ^comp_name, System::String ^fv_nr)
		{
			InitializeComponent();

			this->txtCompanyName->Text = comp_name;
			this->txtFvIdent->Text = fv_nr;
		}

		unsigned short int inv_count;
		bool is_valid_data;

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~SplitCountAskForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Button^  btnAccept;
	protected:
	private: System::Windows::Forms::Button^  btnCancel;
	private: System::Windows::Forms::TextBox^  txtInvCount;
	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::Label^  label3;
	private: System::Windows::Forms::TextBox^  txtCompanyName;
	private: System::Windows::Forms::TextBox^  txtFvIdent;

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->btnAccept = (gcnew System::Windows::Forms::Button());
			this->btnCancel = (gcnew System::Windows::Forms::Button());
			this->txtInvCount = (gcnew System::Windows::Forms::TextBox());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->txtCompanyName = (gcnew System::Windows::Forms::TextBox());
			this->txtFvIdent = (gcnew System::Windows::Forms::TextBox());
			this->SuspendLayout();
			// 
			// btnAccept
			// 
			this->btnAccept->Location = System::Drawing::Point(32, 163);
			this->btnAccept->Name = L"btnAccept";
			this->btnAccept->Size = System::Drawing::Size(75, 23);
			this->btnAccept->TabIndex = 2;
			this->btnAccept->Text = L"ZatwierdŸ";
			this->btnAccept->UseVisualStyleBackColor = true;
			this->btnAccept->Click += gcnew System::EventHandler(this, &SplitCountAskForm::btnAccept_Click);
			// 
			// btnCancel
			// 
			this->btnCancel->Location = System::Drawing::Point(138, 163);
			this->btnCancel->Name = L"btnCancel";
			this->btnCancel->Size = System::Drawing::Size(75, 23);
			this->btnCancel->TabIndex = 3;
			this->btnCancel->Text = L"WyjdŸ";
			this->btnCancel->UseVisualStyleBackColor = true;
			this->btnCancel->Click += gcnew System::EventHandler(this, &SplitCountAskForm::btnCancel_Click);
			// 
			// txtInvCount
			// 
			this->txtInvCount->Location = System::Drawing::Point(208, 102);
			this->txtInvCount->MaxLength = 2;
			this->txtInvCount->Name = L"txtInvCount";
			this->txtInvCount->Size = System::Drawing::Size(43, 20);
			this->txtInvCount->TabIndex = 1;
			this->txtInvCount->PreviewKeyDown += gcnew System::Windows::Forms::PreviewKeyDownEventHandler(this, &SplitCountAskForm::txtInvCount_PreviewKeyDown);
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(29, 105);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(164, 13);
			this->label1->TabIndex = 3;
			this->label1->Text = L"Podaj liczbê inwestycji dla faktury";
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(29, 71);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(58, 13);
			this->label2->TabIndex = 4;
			this->label2->Text = L"Faktura nr:";
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Location = System::Drawing::Point(29, 41);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(35, 13);
			this->label3->TabIndex = 5;
			this->label3->Text = L"Firma:";
			// 
			// txtCompanyName
			// 
			this->txtCompanyName->Location = System::Drawing::Point(102, 41);
			this->txtCompanyName->MaxLength = 2;
			this->txtCompanyName->Name = L"txtCompanyName";
			this->txtCompanyName->ReadOnly = true;
			this->txtCompanyName->Size = System::Drawing::Size(149, 20);
			this->txtCompanyName->TabIndex = 6;
			this->txtCompanyName->TabStop = false;
			// 
			// txtFvIdent
			// 
			this->txtFvIdent->Location = System::Drawing::Point(102, 68);
			this->txtFvIdent->MaxLength = 2;
			this->txtFvIdent->Name = L"txtFvIdent";
			this->txtFvIdent->ReadOnly = true;
			this->txtFvIdent->Size = System::Drawing::Size(149, 20);
			this->txtFvIdent->TabIndex = 7;
			this->txtFvIdent->TabStop = false;
			// 
			// SplitCountAskForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(284, 220);
			this->Controls->Add(this->txtFvIdent);
			this->Controls->Add(this->txtCompanyName);
			this->Controls->Add(this->label3);
			this->Controls->Add(this->label2);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->txtInvCount);
			this->Controls->Add(this->btnCancel);
			this->Controls->Add(this->btnAccept);
			this->Name = L"SplitCountAskForm";
			this->Text = L"Podaj liczbê inwestycji";
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion
	private: System::Void btnCancel_Click(System::Object^  sender, System::EventArgs^  e) 
	{
		is_valid_data = false;
		this->Close();
	}
private: System::Void btnAccept_Click(System::Object^  sender, System::EventArgs^  e) 
	{
		try
		{
			this->inv_count = int::Parse(txtInvCount->Text);
		}
		catch (System::Exception ^e)
		{
			MessageBox::Show("B³¹d:\n" + e->Message);
			is_valid_data = false;
			return;
		}
		if (this->inv_count <= 1 || this->inv_count >= 5)
			MessageBox::Show("Iloœæ podzia³ów nie powinna przekraczaæ 5. Wartoœæ mniejsza b¹dŸ równa 1 jest bez sensu");
		
		this->Hide();
		is_valid_data = true;
	}
private: System::Void txtInvCount_PreviewKeyDown(System::Object^  sender, System::Windows::Forms::PreviewKeyDownEventArgs^  e) 
{
	if (e->KeyCode == Keys::Enter)
		this->btnAccept_Click(sender, e);
}
};
}
