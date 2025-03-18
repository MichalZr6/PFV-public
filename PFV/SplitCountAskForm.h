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

		SplitCountAskForm(System::String^ comp_name, System::String^ fv_nr)
		{
			InitializeComponent();

			txtCompanyName->Text = comp_name;
			txtFvIdent->Text = fv_nr;
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
	private: System::Windows::Forms::Button^ btnAccept;
	protected:
	private: System::Windows::Forms::Button^ btnCancel;
	private: System::Windows::Forms::TextBox^ txtInvCount;
	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::Label^ label2;
	private: System::Windows::Forms::Label^ label3;
	private: System::Windows::Forms::TextBox^ txtCompanyName;
	private: System::Windows::Forms::TextBox^ txtFvIdent;

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
			btnAccept = (gcnew System::Windows::Forms::Button());
			btnCancel = (gcnew System::Windows::Forms::Button());
			txtInvCount = (gcnew System::Windows::Forms::TextBox());
			label1 = (gcnew System::Windows::Forms::Label());
			label2 = (gcnew System::Windows::Forms::Label());
			label3 = (gcnew System::Windows::Forms::Label());
			txtCompanyName = (gcnew System::Windows::Forms::TextBox());
			txtFvIdent = (gcnew System::Windows::Forms::TextBox());
			SuspendLayout();
			// 
			// btnAccept
			// 
			btnAccept->Location = System::Drawing::Point(32, 163);
			btnAccept->Name = L"btnAccept";
			btnAccept->Size = System::Drawing::Size(75, 23);
			btnAccept->TabIndex = 2;
			btnAccept->Text = L"ZatwierdŸ";
			btnAccept->UseVisualStyleBackColor = true;
			btnAccept->Click += gcnew System::EventHandler(this, &SplitCountAskForm::btnAccept_Click);
			// 
			// btnCancel
			// 
			btnCancel->Location = System::Drawing::Point(138, 163);
			btnCancel->Name = L"btnCancel";
			btnCancel->Size = System::Drawing::Size(75, 23);
			btnCancel->TabIndex = 3;
			btnCancel->Text = L"WyjdŸ";
			btnCancel->UseVisualStyleBackColor = true;
			btnCancel->Click += gcnew System::EventHandler(this, &SplitCountAskForm::btnCancel_Click);
			// 
			// txtInvCount
			// 
			txtInvCount->Location = System::Drawing::Point(208, 102);
			txtInvCount->MaxLength = 2;
			txtInvCount->Name = L"txtInvCount";
			txtInvCount->Size = System::Drawing::Size(43, 20);
			txtInvCount->TabIndex = 1;
			txtInvCount->PreviewKeyDown += gcnew System::Windows::Forms::PreviewKeyDownEventHandler(this, &SplitCountAskForm::txtInvCount_PreviewKeyDown);
			// 
			// label1
			// 
			label1->AutoSize = true;
			label1->Location = System::Drawing::Point(29, 105);
			label1->Name = L"label1";
			label1->Size = System::Drawing::Size(164, 13);
			label1->TabIndex = 3;
			label1->Text = L"Podaj liczbê inwestycji dla faktury";
			// 
			// label2
			// 
			label2->AutoSize = true;
			label2->Location = System::Drawing::Point(29, 71);
			label2->Name = L"label2";
			label2->Size = System::Drawing::Size(58, 13);
			label2->TabIndex = 4;
			label2->Text = L"Faktura nr:";
			// 
			// label3
			// 
			label3->AutoSize = true;
			label3->Location = System::Drawing::Point(29, 41);
			label3->Name = L"label3";
			label3->Size = System::Drawing::Size(35, 13);
			label3->TabIndex = 5;
			label3->Text = L"Firma:";
			// 
			// txtCompanyName
			// 
			txtCompanyName->Location = System::Drawing::Point(102, 41);
			txtCompanyName->MaxLength = 2;
			txtCompanyName->Name = L"txtCompanyName";
			txtCompanyName->ReadOnly = true;
			txtCompanyName->Size = System::Drawing::Size(149, 20);
			txtCompanyName->TabIndex = 6;
			txtCompanyName->TabStop = false;
			// 
			// txtFvIdent
			// 
			txtFvIdent->Location = System::Drawing::Point(102, 68);
			txtFvIdent->MaxLength = 2;
			txtFvIdent->Name = L"txtFvIdent";
			txtFvIdent->ReadOnly = true;
			txtFvIdent->Size = System::Drawing::Size(149, 20);
			txtFvIdent->TabIndex = 7;
			txtFvIdent->TabStop = false;
			// 
			// SplitCountAskForm
			// 
			AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			ClientSize = System::Drawing::Size(284, 220);
			Controls->Add(txtFvIdent);
			Controls->Add(txtCompanyName);
			Controls->Add(label3);
			Controls->Add(label2);
			Controls->Add(label1);
			Controls->Add(txtInvCount);
			Controls->Add(btnCancel);
			Controls->Add(btnAccept);
			Name = L"SplitCountAskForm";
			Text = L"Podaj liczbê inwestycji";
			ResumeLayout(false);
			PerformLayout();

		}
#pragma endregion
	private: System::Void btnCancel_Click(System::Object^ sender, System::EventArgs^ e)
	{
		is_valid_data = false;
		Close();
	}
	private: System::Void btnAccept_Click(System::Object^ sender, System::EventArgs^ e)
	{
		try
		{
			inv_count = int::Parse(txtInvCount->Text);
		}
		catch (System::Exception^ e)
		{
			MessageBox::Show("B³¹d:\n" + e->Message);
			is_valid_data = false;
			return;
		}
		if (inv_count <= 1 || inv_count >= 5)
			MessageBox::Show("Iloœæ podzia³ów nie powinna przekraczaæ 5. Wartoœæ mniejsza b¹dŸ równa 1 jest bez sensu");

		Hide();
		is_valid_data = true;
	}
	private: System::Void txtInvCount_PreviewKeyDown(System::Object^ sender, System::Windows::Forms::PreviewKeyDownEventArgs^ e)
	{
		if (e->KeyCode == Keys::Enter)
			btnAccept_Click(sender, e);
	}
	};
}
