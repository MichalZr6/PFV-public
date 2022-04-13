#pragma once

#include <locale.h>
#include <algorithm>
#include <iterator>
#include <filesystem>
#include "Functions.h"
#include "BasicExcel.hpp"
#include "Price.h"
#include "Fv-func.h"
#include "Globals.h"
#include "SplitFvForm.h"

namespace PFV
{
	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Podsumowanie informacji o MainForm
	/// </summary>
	public ref class MainForm : public System::Windows::Forms::Form
	{
	public:
		MainForm(void)
		{
			InitializeComponent();
			InitDynamicOutputBox();
		}

	private:
		void InitDynamicOutputBox();
		void StringsToOutput(const std::wstring& search,
			const std::unordered_set<std::wstring>& sset);
		void PrevCompInvKeyDown(System::Object^ sender,
			System::Windows::Forms::PreviewKeyDownEventArgs^ e);
		std::wstring GetFvDirText();

		void LoadRawFiles(void);
		void AskForPath(void);
		void LoadXLSRecords(void);
		void SetCurrYearMon(void);

		void ManageForm(FormState state);
		void CheckActFile(void);
		void SetFvInfoFromInputs(Fv_ptr& fv);
		void ClearAllInputs(void);
		void HideFvComponents(void);
		void ShowFvComponents(void);
		bool CanSplitBtnBeEnabled(std::set<ScannedFile>::const_iterator curr);

		void UpdateProgramOutput(FormState state);
		void RawFilenames_ToOutput(void);
		void SummaryFromXLS_ToOutput(void);
		void FvFiles_ToOutput(void);

		bool NewFvAdd(void);
		void CheckForDuplicates(const Fv_ptr& fv);
		//throws if there are duplicates: in program input or in data loaded from xls file
		bool NewNonFvAdd(void);
		void AnotherPagePrepare(void);
		bool AnotherPageAdd(void);

		bool PromptForSaving(void);
		void SaveToFile(void);
		void RenameAllFiles(void);
		void CreateFoldersAndMoveFiles(void);

		void ResetFilenameLabel(void);
		void InitOnMouseHoverTextBox(void);
		std::wstring TrimLongFileName(const std::wstring& fname);

		// Debugging
		void FillInForTests(void);

		// Variables
		bool numberKeyPressed = false;
		System::String^ warnings;
		System::Drawing::Size cached_panel_size;
		System::Drawing::Size cached_programOutput_size;

	private: System::Windows::Forms::MenuStrip^ menuStrip1;
	private: System::Windows::Forms::ToolStripMenuItem^ miProperties;
	private: System::Windows::Forms::ToolStripMenuItem^ wykonajAkcjêToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^ dodajToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^ usuñOstatniWpisToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^ podzielOstatniaFakturêToolStripMenuItem;
	private: System::Windows::Forms::ToolStripSeparator^ toolStripSeparator3;
	private: System::Windows::Forms::ToolStripMenuItem^ toolStripMenuItem1;
	private: System::Windows::Forms::ToolStripMenuItem^ zapiszDotychczasoweDaneDoPlikuxlsToolStripMenuItem;
	private: System::Windows::Forms::ToolStripSeparator^ toolStripSeparator2;
	private: System::Windows::Forms::ToolStripMenuItem^ generujTekstDoSaldeoToolStripMenuItem;
	private: System::Windows::Forms::ToolStripSeparator^ toolStripSeparator1;
	private: System::Windows::Forms::ToolStripMenuItem^ zamknijProgramToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^ ukryjPanelGórnyToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^ ukryjKomunikatyProgramuToolStripMenuItem;
	private: System::Windows::Forms::Label^ lblTax;

	private: System::Windows::Forms::Panel^ panelInputs;
	private: System::Windows::Forms::ComboBox^ cbTax;

	private: System::Windows::Forms::ToolStripMenuItem^ miHelp;

	protected:
		/// <summary>
		/// Wyczyœæ wszystkie u¿ywane zasoby.
		/// </summary>
		~MainForm()
		{
			if (components)
			{
				delete components;
			}
		}
		//////////////////////////////////////////////////
		////////   CONTROLS DECLARATIONS   ///////////////
		//////////////////////////////////////////////////
	private: System::Windows::Forms::Label^ lblComments;
	private: System::Windows::Forms::TextBox^ txtComments;
	private: System::Windows::Forms::CheckBox^ chbAnotherPage;
	private: System::Windows::Forms::RichTextBox^ rtxtDynamicOutput;
	private: System::Windows::Forms::Panel^ panelFilename;
	private: System::Windows::Forms::Label^ label12;
	private: System::Windows::Forms::TextBox^ txtDescr;
	private: System::Windows::Forms::RichTextBox^ rtxtOnMouseHover;
	private: System::Windows::Forms::Form^ split_fv_form;
	private: System::Windows::Forms::Button^ btnDeleteLast;
	private: System::Windows::Forms::Button^ btnExit;
	private: System::Windows::Forms::CheckBox^ chbIsFv;
	private: System::Windows::Forms::Label^ lblCurrFileStatic;

	private: System::Windows::Forms::Label^ lblCurrentFile;
	private: System::Windows::Forms::TextBox^ txtNewNotFvFilename;
	private: System::Windows::Forms::Label^ label14;
	private: System::Windows::Forms::TextBox^ txtPayment;
	private: System::Windows::Forms::Label^ label15;
	private: System::Windows::Forms::TextBox^ txtWhoPayed;
	private: System::Windows::Forms::Button^ btnSaldeo;
	private: System::Windows::Forms::FolderBrowserDialog^ folderBrowser;

	private: System::Windows::Forms::Button^ btnAdd;
	private: System::Windows::Forms::Label^ label1;
	private: System::Windows::Forms::TextBox^ txtCompany;
	private: System::Windows::Forms::TextBox^ txtFvIdent;
	private: System::Windows::Forms::Label^ label2;
	private: System::Windows::Forms::Label^ label3;
	private: System::Windows::Forms::TextBox^ txtDay;
	private: System::Windows::Forms::TextBox^ txtMonth;
	private: System::Windows::Forms::TextBox^ txtYear;
	private: System::Windows::Forms::Label^ label4;
	private: System::Windows::Forms::TextBox^ txtInvest;
	private: System::Windows::Forms::RichTextBox^ rtxtProgramOutput;


	private: System::Windows::Forms::Button^ btnSplit;
	private: System::Windows::Forms::Label^ label5;
	private: System::Windows::Forms::TextBox^ txtNetVal;
	private: System::Windows::Forms::Label^ label6;
	private: System::Windows::Forms::TextBox^ txtGrossVal;
	private: System::Windows::Forms::Panel^ panelTop;

	private: System::Windows::Forms::TextBox^ txtFvListOutFilename;
	private: System::Windows::Forms::Label^ label8;
	private: System::Windows::Forms::TextBox^ txtFvListFilename;
	private: System::Windows::Forms::Label^ label7;
	private: System::Windows::Forms::TextBox^ txtFvDir;
	private: System::Windows::Forms::Label^ label9;
	private: System::Windows::Forms::Label^ label10;
	private: System::Windows::Forms::Label^ label11;

	protected:

	private:
		/// <summary>
		/// Wymagana zmienna projektanta.
		/// </summary>
		System::ComponentModel::Container^ components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Metoda wymagana do obs³ugi projektanta — nie nale¿y modyfikowaæ
		/// jej zawartoœci w edytorze kodu.
		/// </summary>
		void InitializeComponent(void)
		{
			this->btnAdd = (gcnew System::Windows::Forms::Button());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->txtCompany = (gcnew System::Windows::Forms::TextBox());
			this->txtFvIdent = (gcnew System::Windows::Forms::TextBox());
			this->label2 = (gcnew System::Windows::Forms::Label());
			this->label3 = (gcnew System::Windows::Forms::Label());
			this->txtDay = (gcnew System::Windows::Forms::TextBox());
			this->txtMonth = (gcnew System::Windows::Forms::TextBox());
			this->txtYear = (gcnew System::Windows::Forms::TextBox());
			this->label4 = (gcnew System::Windows::Forms::Label());
			this->txtInvest = (gcnew System::Windows::Forms::TextBox());
			this->rtxtProgramOutput = (gcnew System::Windows::Forms::RichTextBox());
			this->btnSplit = (gcnew System::Windows::Forms::Button());
			this->label5 = (gcnew System::Windows::Forms::Label());
			this->txtNetVal = (gcnew System::Windows::Forms::TextBox());
			this->label6 = (gcnew System::Windows::Forms::Label());
			this->txtGrossVal = (gcnew System::Windows::Forms::TextBox());
			this->panelTop = (gcnew System::Windows::Forms::Panel());
			this->txtFvDir = (gcnew System::Windows::Forms::TextBox());
			this->label9 = (gcnew System::Windows::Forms::Label());
			this->txtFvListOutFilename = (gcnew System::Windows::Forms::TextBox());
			this->label8 = (gcnew System::Windows::Forms::Label());
			this->txtFvListFilename = (gcnew System::Windows::Forms::TextBox());
			this->label7 = (gcnew System::Windows::Forms::Label());
			this->label10 = (gcnew System::Windows::Forms::Label());
			this->label11 = (gcnew System::Windows::Forms::Label());
			this->label12 = (gcnew System::Windows::Forms::Label());
			this->txtDescr = (gcnew System::Windows::Forms::TextBox());
			this->btnDeleteLast = (gcnew System::Windows::Forms::Button());
			this->btnExit = (gcnew System::Windows::Forms::Button());
			this->chbIsFv = (gcnew System::Windows::Forms::CheckBox());
			this->lblCurrFileStatic = (gcnew System::Windows::Forms::Label());
			this->lblCurrentFile = (gcnew System::Windows::Forms::Label());
			this->txtNewNotFvFilename = (gcnew System::Windows::Forms::TextBox());
			this->label14 = (gcnew System::Windows::Forms::Label());
			this->txtPayment = (gcnew System::Windows::Forms::TextBox());
			this->label15 = (gcnew System::Windows::Forms::Label());
			this->txtWhoPayed = (gcnew System::Windows::Forms::TextBox());
			this->btnSaldeo = (gcnew System::Windows::Forms::Button());
			this->folderBrowser = (gcnew System::Windows::Forms::FolderBrowserDialog());
			this->panelFilename = (gcnew System::Windows::Forms::Panel());
			this->chbAnotherPage = (gcnew System::Windows::Forms::CheckBox());
			this->lblComments = (gcnew System::Windows::Forms::Label());
			this->txtComments = (gcnew System::Windows::Forms::TextBox());
			this->menuStrip1 = (gcnew System::Windows::Forms::MenuStrip());
			this->wykonajAkcjêToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->dodajToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->usuñOstatniWpisToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->podzielOstatniaFakturêToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->toolStripSeparator3 = (gcnew System::Windows::Forms::ToolStripSeparator());
			this->toolStripMenuItem1 = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->zapiszDotychczasoweDaneDoPlikuxlsToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->toolStripSeparator2 = (gcnew System::Windows::Forms::ToolStripSeparator());
			this->generujTekstDoSaldeoToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->toolStripSeparator1 = (gcnew System::Windows::Forms::ToolStripSeparator());
			this->zamknijProgramToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->miProperties = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->ukryjPanelGórnyToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->ukryjKomunikatyProgramuToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->miHelp = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->lblTax = (gcnew System::Windows::Forms::Label());
			this->panelInputs = (gcnew System::Windows::Forms::Panel());
			this->cbTax = (gcnew System::Windows::Forms::ComboBox());
			this->panelTop->SuspendLayout();
			this->panelFilename->SuspendLayout();
			this->menuStrip1->SuspendLayout();
			this->panelInputs->SuspendLayout();
			this->SuspendLayout();
			// 
			// btnAdd
			// 
			this->btnAdd->Location = System::Drawing::Point(8, 274);
			this->btnAdd->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->btnAdd->Name = L"btnAdd";
			this->btnAdd->Size = System::Drawing::Size(141, 28);
			this->btnAdd->TabIndex = 15;
			this->btnAdd->Text = L"Do&daj";
			this->btnAdd->UseVisualStyleBackColor = true;
			this->btnAdd->Click += gcnew System::EventHandler(this, &MainForm::btnAdd_Click);
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(4, 11);
			this->label1->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(41, 16);
			this->label1->TabIndex = 1;
			this->label1->Text = L"Firma";
			// 
			// txtCompany
			// 
			this->txtCompany->Location = System::Drawing::Point(89, 7);
			this->txtCompany->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->txtCompany->MaxLength = 40;
			this->txtCompany->Name = L"txtCompany";
			this->txtCompany->Size = System::Drawing::Size(367, 22);
			this->txtCompany->TabIndex = 2;
			this->txtCompany->TextChanged += gcnew System::EventHandler(this, &MainForm::txtCompany_TextChanged);
			this->txtCompany->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &MainForm::txtCompany_KeyPress);
			this->txtCompany->Leave += gcnew System::EventHandler(this, &MainForm::txtCompany_Leave);
			this->txtCompany->PreviewKeyDown += gcnew System::Windows::Forms::PreviewKeyDownEventHandler(this, &MainForm::txtCompany_PreviewKeyDown);
			// 
			// txtFvIdent
			// 
			this->txtFvIdent->Location = System::Drawing::Point(89, 39);
			this->txtFvIdent->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->txtFvIdent->MaxLength = 30;
			this->txtFvIdent->Name = L"txtFvIdent";
			this->txtFvIdent->Size = System::Drawing::Size(367, 22);
			this->txtFvIdent->TabIndex = 3;
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(4, 48);
			this->label2->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(63, 16);
			this->label2->TabIndex = 4;
			this->label2->Text = L"Nr faktury";
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Location = System::Drawing::Point(4, 143);
			this->label3->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(36, 16);
			this->label3->TabIndex = 6;
			this->label3->Text = L"Data";
			// 
			// txtDay
			// 
			this->txtDay->Location = System::Drawing::Point(89, 134);
			this->txtDay->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->txtDay->MaxLength = 2;
			this->txtDay->Name = L"txtDay";
			this->txtDay->Size = System::Drawing::Size(32, 22);
			this->txtDay->TabIndex = 6;
			// 
			// txtMonth
			// 
			this->txtMonth->Location = System::Drawing::Point(155, 133);
			this->txtMonth->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->txtMonth->MaxLength = 2;
			this->txtMonth->Name = L"txtMonth";
			this->txtMonth->Size = System::Drawing::Size(32, 22);
			this->txtMonth->TabIndex = 7;
			// 
			// txtYear
			// 
			this->txtYear->Location = System::Drawing::Point(220, 134);
			this->txtYear->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->txtYear->MaxLength = 4;
			this->txtYear->Name = L"txtYear";
			this->txtYear->Size = System::Drawing::Size(68, 22);
			this->txtYear->TabIndex = 8;
			this->txtYear->TabStop = false;
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->Location = System::Drawing::Point(4, 80);
			this->label4->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(69, 16);
			this->label4->TabIndex = 10;
			this->label4->Text = L"Inwestycja";
			// 
			// txtInvest
			// 
			this->txtInvest->Location = System::Drawing::Point(89, 70);
			this->txtInvest->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->txtInvest->MaxLength = 50;
			this->txtInvest->Name = L"txtInvest";
			this->txtInvest->Size = System::Drawing::Size(367, 22);
			this->txtInvest->TabIndex = 4;
			this->txtInvest->TextChanged += gcnew System::EventHandler(this, &MainForm::txtInvest_TextChanged);
			this->txtInvest->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &MainForm::txtInvest_KeyPress);
			this->txtInvest->Leave += gcnew System::EventHandler(this, &MainForm::txtInvest_Leave);
			this->txtInvest->PreviewKeyDown += gcnew System::Windows::Forms::PreviewKeyDownEventHandler(this, &MainForm::txtInvest_PreviewKeyDown);
			// 
			// rtxtProgramOutput
			// 
			this->rtxtProgramOutput->Location = System::Drawing::Point(509, 107);
			this->rtxtProgramOutput->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->rtxtProgramOutput->Name = L"rtxtProgramOutput";
			this->rtxtProgramOutput->ReadOnly = true;
			this->rtxtProgramOutput->Size = System::Drawing::Size(596, 405);
			this->rtxtProgramOutput->TabIndex = 11;
			this->rtxtProgramOutput->TabStop = false;
			this->rtxtProgramOutput->Text = L"";
			// 
			// btnSplit
			// 
			this->btnSplit->Enabled = false;
			this->btnSplit->Location = System::Drawing::Point(157, 274);
			this->btnSplit->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->btnSplit->Name = L"btnSplit";
			this->btnSplit->Size = System::Drawing::Size(300, 28);
			this->btnSplit->TabIndex = 16;
			this->btnSplit->Text = L"Podziel ostatni¹ dodan¹ fakturê na czêœci";
			this->btnSplit->UseVisualStyleBackColor = true;
			this->btnSplit->Click += gcnew System::EventHandler(this, &MainForm::btnSplit_Click);
			// 
			// label5
			// 
			this->label5->AutoSize = true;
			this->label5->Location = System::Drawing::Point(4, 175);
			this->label5->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->label5->Name = L"label5";
			this->label5->Size = System::Drawing::Size(70, 16);
			this->label5->TabIndex = 16;
			this->label5->Text = L"Wart. netto";
			// 
			// txtNetVal
			// 
			this->txtNetVal->Location = System::Drawing::Point(89, 166);
			this->txtNetVal->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->txtNetVal->MaxLength = 30;
			this->txtNetVal->Name = L"txtNetVal";
			this->txtNetVal->Size = System::Drawing::Size(79, 22);
			this->txtNetVal->TabIndex = 9;
			this->txtNetVal->Enter += gcnew System::EventHandler(this, &MainForm::txtNetVal_Enter);
			this->txtNetVal->Leave += gcnew System::EventHandler(this, &MainForm::txtNetVal_Leave);
			// 
			// label6
			// 
			this->label6->AutoSize = true;
			this->label6->Location = System::Drawing::Point(295, 170);
			this->label6->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->label6->Name = L"label6";
			this->label6->Size = System::Drawing::Size(41, 16);
			this->label6->TabIndex = 18;
			this->label6->Text = L"Brutto";
			// 
			// txtGrossVal
			// 
			this->txtGrossVal->Location = System::Drawing::Point(349, 164);
			this->txtGrossVal->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->txtGrossVal->MaxLength = 30;
			this->txtGrossVal->Name = L"txtGrossVal";
			this->txtGrossVal->Size = System::Drawing::Size(107, 22);
			this->txtGrossVal->TabIndex = 11;
			this->txtGrossVal->Enter += gcnew System::EventHandler(this, &MainForm::txtGrossVal_Enter);
			this->txtGrossVal->Leave += gcnew System::EventHandler(this, &MainForm::txtGrossVal_Leave);
			// 
			// panelTop
			// 
			this->panelTop->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->panelTop->Controls->Add(this->txtFvDir);
			this->panelTop->Controls->Add(this->label9);
			this->panelTop->Controls->Add(this->txtFvListOutFilename);
			this->panelTop->Controls->Add(this->label8);
			this->panelTop->Controls->Add(this->txtFvListFilename);
			this->panelTop->Controls->Add(this->label7);
			this->panelTop->Location = System::Drawing::Point(23, 46);
			this->panelTop->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->panelTop->Name = L"panelTop";
			this->panelTop->Size = System::Drawing::Size(1083, 49);
			this->panelTop->TabIndex = 19;
			// 
			// txtFvDir
			// 
			this->txtFvDir->Location = System::Drawing::Point(865, 11);
			this->txtFvDir->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->txtFvDir->Name = L"txtFvDir";
			this->txtFvDir->Size = System::Drawing::Size(188, 22);
			this->txtFvDir->TabIndex = 25;
			this->txtFvDir->TabStop = false;
			this->txtFvDir->Text = L"Fv/";
			// 
			// label9
			// 
			this->label9->AutoSize = true;
			this->label9->Location = System::Drawing::Point(711, 15);
			this->label9->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->label9->Name = L"label9";
			this->label9->Size = System::Drawing::Size(134, 16);
			this->label9->TabIndex = 24;
			this->label9->Text = L"Œcie¿ka folderu faktur";
			// 
			// txtFvListOutFilename
			// 
			this->txtFvListOutFilename->Location = System::Drawing::Point(513, 11);
			this->txtFvListOutFilename->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->txtFvListOutFilename->Name = L"txtFvListOutFilename";
			this->txtFvListOutFilename->Size = System::Drawing::Size(188, 22);
			this->txtFvListOutFilename->TabIndex = 23;
			this->txtFvListOutFilename->TabStop = false;
			this->txtFvListOutFilename->Text = L"Zestawienie Faktur_out.xls";
			// 
			// label8
			// 
			this->label8->AutoSize = true;
			this->label8->Location = System::Drawing::Point(313, 15);
			this->label8->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->label8->Name = L"label8";
			this->label8->Size = System::Drawing::Size(179, 16);
			this->label8->TabIndex = 22;
			this->label8->Text = L"Plik zestawienia wynikowego";
			// 
			// txtFvListFilename
			// 
			this->txtFvListFilename->Location = System::Drawing::Point(121, 11);
			this->txtFvListFilename->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->txtFvListFilename->Name = L"txtFvListFilename";
			this->txtFvListFilename->Size = System::Drawing::Size(183, 22);
			this->txtFvListFilename->TabIndex = 21;
			this->txtFvListFilename->TabStop = false;
			this->txtFvListFilename->Text = L"Zestawienie Faktur.xls";
			// 
			// label7
			// 
			this->label7->AutoSize = true;
			this->label7->Location = System::Drawing::Point(4, 15);
			this->label7->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->label7->Name = L"label7";
			this->label7->Size = System::Drawing::Size(102, 16);
			this->label7->TabIndex = 20;
			this->label7->Text = L"Plik zestawienia";
			// 
			// label10
			// 
			this->label10->AutoSize = true;
			this->label10->Location = System::Drawing::Point(131, 138);
			this->label10->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->label10->Name = L"label10";
			this->label10->Size = System::Drawing::Size(11, 16);
			this->label10->TabIndex = 20;
			this->label10->Text = L"/";
			// 
			// label11
			// 
			this->label11->AutoSize = true;
			this->label11->Location = System::Drawing::Point(196, 138);
			this->label11->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->label11->Name = L"label11";
			this->label11->Size = System::Drawing::Size(11, 16);
			this->label11->TabIndex = 21;
			this->label11->Text = L"/";
			// 
			// label12
			// 
			this->label12->AutoSize = true;
			this->label12->Location = System::Drawing::Point(4, 111);
			this->label12->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->label12->Name = L"label12";
			this->label12->Size = System::Drawing::Size(35, 16);
			this->label12->TabIndex = 28;
			this->label12->Text = L"Opis";
			// 
			// txtDescr
			// 
			this->txtDescr->Location = System::Drawing::Point(89, 102);
			this->txtDescr->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->txtDescr->MaxLength = 50;
			this->txtDescr->Name = L"txtDescr";
			this->txtDescr->Size = System::Drawing::Size(367, 22);
			this->txtDescr->TabIndex = 5;
			// 
			// btnDeleteLast
			// 
			this->btnDeleteLast->Location = System::Drawing::Point(8, 310);
			this->btnDeleteLast->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->btnDeleteLast->Name = L"btnDeleteLast";
			this->btnDeleteLast->Size = System::Drawing::Size(141, 28);
			this->btnDeleteLast->TabIndex = 17;
			this->btnDeleteLast->Text = L"Usuñ ostatni wpis";
			this->btnDeleteLast->UseVisualStyleBackColor = true;
			this->btnDeleteLast->Click += gcnew System::EventHandler(this, &MainForm::btnDeleteLast_Click);
			// 
			// btnExit
			// 
			this->btnExit->Location = System::Drawing::Point(347, 310);
			this->btnExit->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->btnExit->Name = L"btnExit";
			this->btnExit->Size = System::Drawing::Size(111, 28);
			this->btnExit->TabIndex = 19;
			this->btnExit->Text = L"&WyjdŸ";
			this->btnExit->UseVisualStyleBackColor = true;
			this->btnExit->Click += gcnew System::EventHandler(this, &MainForm::btnExit_Click);
			// 
			// chbIsFv
			// 
			this->chbIsFv->AutoSize = true;
			this->chbIsFv->Checked = true;
			this->chbIsFv->CheckState = System::Windows::Forms::CheckState::Checked;
			this->chbIsFv->Location = System::Drawing::Point(8, 26);
			this->chbIsFv->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->chbIsFv->Name = L"chbIsFv";
			this->chbIsFv->Size = System::Drawing::Size(96, 20);
			this->chbIsFv->TabIndex = 1;
			this->chbIsFv->Text = L"faktura VAT";
			this->chbIsFv->UseVisualStyleBackColor = true;
			this->chbIsFv->CheckedChanged += gcnew System::EventHandler(this, &MainForm::chbIsFv_CheckedChanged);
			this->chbIsFv->Enter += gcnew System::EventHandler(this, &MainForm::chbIsFv_Enter);
			this->chbIsFv->Leave += gcnew System::EventHandler(this, &MainForm::chbIsFv_Leave);
			// 
			// lblCurrFileStatic
			// 
			this->lblCurrFileStatic->AutoSize = true;
			this->lblCurrFileStatic->Location = System::Drawing::Point(4, 4);
			this->lblCurrFileStatic->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->lblCurrFileStatic->Name = L"lblCurrFileStatic";
			this->lblCurrFileStatic->Size = System::Drawing::Size(85, 16);
			this->lblCurrFileStatic->TabIndex = 32;
			this->lblCurrFileStatic->Text = L"Aktualny plik:";
			// 
			// lblCurrentFile
			// 
			this->lblCurrentFile->AutoSize = true;
			this->lblCurrentFile->Location = System::Drawing::Point(119, 4);
			this->lblCurrentFile->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->lblCurrentFile->Name = L"lblCurrentFile";
			this->lblCurrentFile->Size = System::Drawing::Size(0, 16);
			this->lblCurrentFile->TabIndex = 33;
			this->lblCurrentFile->MouseLeave += gcnew System::EventHandler(this, &MainForm::lblCurrentFile_MouseLeave);
			this->lblCurrentFile->MouseHover += gcnew System::EventHandler(this, &MainForm::lblCurrentFile_MouseHover);
			// 
			// txtNewNotFvFilename
			// 
			this->txtNewNotFvFilename->Location = System::Drawing::Point(167, 7);
			this->txtNewNotFvFilename->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->txtNewNotFvFilename->Name = L"txtNewNotFvFilename";
			this->txtNewNotFvFilename->Size = System::Drawing::Size(289, 22);
			this->txtNewNotFvFilename->TabIndex = 2;
			this->txtNewNotFvFilename->Visible = false;
			// 
			// label14
			// 
			this->label14->AutoSize = true;
			this->label14->Location = System::Drawing::Point(220, 204);
			this->label14->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->label14->Name = L"label14";
			this->label14->Size = System::Drawing::Size(108, 16);
			this->label14->TabIndex = 37;
			this->label14->Text = L"P³atnoœæ/Termin";
			// 
			// txtPayment
			// 
			this->txtPayment->Location = System::Drawing::Point(344, 196);
			this->txtPayment->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->txtPayment->MaxLength = 20;
			this->txtPayment->Name = L"txtPayment";
			this->txtPayment->Size = System::Drawing::Size(112, 22);
			this->txtPayment->TabIndex = 13;
			// 
			// label15
			// 
			this->label15->AutoSize = true;
			this->label15->Location = System::Drawing::Point(4, 207);
			this->label15->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->label15->Name = L"label15";
			this->label15->Size = System::Drawing::Size(46, 16);
			this->label15->TabIndex = 36;
			this->label15->Text = L"P³aci³";
			// 
			// txtWhoPayed
			// 
			this->txtWhoPayed->Location = System::Drawing::Point(89, 201);
			this->txtWhoPayed->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->txtWhoPayed->MaxLength = 2;
			this->txtWhoPayed->Name = L"txtWhoPayed";
			this->txtWhoPayed->Size = System::Drawing::Size(79, 22);
			this->txtWhoPayed->TabIndex = 12;
			// 
			// btnSaldeo
			// 
			this->btnSaldeo->Location = System::Drawing::Point(157, 310);
			this->btnSaldeo->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->btnSaldeo->Name = L"btnSaldeo";
			this->btnSaldeo->Size = System::Drawing::Size(100, 28);
			this->btnSaldeo->TabIndex = 18;
			this->btnSaldeo->Text = L"Saldeo Text";
			this->btnSaldeo->UseVisualStyleBackColor = true;
			this->btnSaldeo->Click += gcnew System::EventHandler(this, &MainForm::btnSaldeo_Click);
			// 
			// folderBrowser
			// 
			this->folderBrowser->RootFolder = System::Environment::SpecialFolder::MyComputer;
			this->folderBrowser->ShowNewFolderButton = false;
			// 
			// panelFilename
			// 
			this->panelFilename->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->panelFilename->Controls->Add(this->chbAnotherPage);
			this->panelFilename->Controls->Add(this->lblCurrFileStatic);
			this->panelFilename->Controls->Add(this->chbIsFv);
			this->panelFilename->Controls->Add(this->lblCurrentFile);
			this->panelFilename->Location = System::Drawing::Point(23, 94);
			this->panelFilename->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->panelFilename->Name = L"panelFilename";
			this->panelFilename->RightToLeft = System::Windows::Forms::RightToLeft::No;
			this->panelFilename->Size = System::Drawing::Size(478, 60);
			this->panelFilename->TabIndex = 39;
			// 
			// chbAnotherPage
			// 
			this->chbAnotherPage->AutoSize = true;
			this->chbAnotherPage->Location = System::Drawing::Point(148, 26);
			this->chbAnotherPage->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->chbAnotherPage->Name = L"chbAnotherPage";
			this->chbAnotherPage->Size = System::Drawing::Size(181, 20);
			this->chbAnotherPage->TabIndex = 34;
			this->chbAnotherPage->Text = L"kolejna strona poprz. pliku";
			this->chbAnotherPage->UseVisualStyleBackColor = true;
			this->chbAnotherPage->CheckedChanged += gcnew System::EventHandler(this, &MainForm::chbAnotherPage_CheckedChanged);
			// 
			// lblComments
			// 
			this->lblComments->AutoSize = true;
			this->lblComments->Location = System::Drawing::Point(4, 240);
			this->lblComments->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->lblComments->Name = L"lblComments";
			this->lblComments->Size = System::Drawing::Size(70, 16);
			this->lblComments->TabIndex = 40;
			this->lblComments->Text = L"Komentarz";
			// 
			// txtComments
			// 
			this->txtComments->Location = System::Drawing::Point(89, 231);
			this->txtComments->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->txtComments->MaxLength = 100;
			this->txtComments->Name = L"txtComments";
			this->txtComments->Size = System::Drawing::Size(367, 22);
			this->txtComments->TabIndex = 14;
			// 
			// menuStrip1
			// 
			this->menuStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(3) {
				this->wykonajAkcjêToolStripMenuItem,
					this->miProperties, this->miHelp
			});
			this->menuStrip1->Location = System::Drawing::Point(0, 0);
			this->menuStrip1->Name = L"menuStrip1";
			this->menuStrip1->Padding = System::Windows::Forms::Padding(8, 2, 0, 2);
			this->menuStrip1->Size = System::Drawing::Size(1107, 24);
			this->menuStrip1->TabIndex = 41;
			this->menuStrip1->Text = L"menuStrip1";
			// 
			// wykonajAkcjêToolStripMenuItem
			// 
			this->wykonajAkcjêToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(10) {
				this->dodajToolStripMenuItem,
					this->usuñOstatniWpisToolStripMenuItem, this->podzielOstatniaFakturêToolStripMenuItem, this->toolStripSeparator3, this->toolStripMenuItem1,
					this->zapiszDotychczasoweDaneDoPlikuxlsToolStripMenuItem, this->toolStripSeparator2, this->generujTekstDoSaldeoToolStripMenuItem,
					this->toolStripSeparator1, this->zamknijProgramToolStripMenuItem
			});
			this->wykonajAkcjêToolStripMenuItem->Name = L"wykonajAkcjêToolStripMenuItem";
			this->wykonajAkcjêToolStripMenuItem->Size = System::Drawing::Size(95, 20);
			this->wykonajAkcjêToolStripMenuItem->Text = L"Wykonaj akcjê";
			// 
			// dodajToolStripMenuItem
			// 
			this->dodajToolStripMenuItem->Name = L"dodajToolStripMenuItem";
			this->dodajToolStripMenuItem->Size = System::Drawing::Size(286, 22);
			this->dodajToolStripMenuItem->Text = L"Dodaj";
			// 
			// usuñOstatniWpisToolStripMenuItem
			// 
			this->usuñOstatniWpisToolStripMenuItem->Name = L"usuñOstatniWpisToolStripMenuItem";
			this->usuñOstatniWpisToolStripMenuItem->Size = System::Drawing::Size(286, 22);
			this->usuñOstatniWpisToolStripMenuItem->Text = L"Usuñ ostatni wpis";
			// 
			// podzielOstatniaFakturêToolStripMenuItem
			// 
			this->podzielOstatniaFakturêToolStripMenuItem->Name = L"podzielOstatniaFakturêToolStripMenuItem";
			this->podzielOstatniaFakturêToolStripMenuItem->Size = System::Drawing::Size(286, 22);
			this->podzielOstatniaFakturêToolStripMenuItem->Text = L"Podziel ostatni¹ fakturê";
			// 
			// toolStripSeparator3
			// 
			this->toolStripSeparator3->Name = L"toolStripSeparator3";
			this->toolStripSeparator3->Size = System::Drawing::Size(283, 6);
			// 
			// toolStripMenuItem1
			// 
			this->toolStripMenuItem1->Name = L"toolStripMenuItem1";
			this->toolStripMenuItem1->Size = System::Drawing::Size(286, 22);
			this->toolStripMenuItem1->Text = L"Ukryj komunikaty programu";
			// 
			// zapiszDotychczasoweDaneDoPlikuxlsToolStripMenuItem
			// 
			this->zapiszDotychczasoweDaneDoPlikuxlsToolStripMenuItem->Name = L"zapiszDotychczasoweDaneDoPlikuxlsToolStripMenuItem";
			this->zapiszDotychczasoweDaneDoPlikuxlsToolStripMenuItem->Size = System::Drawing::Size(286, 22);
			this->zapiszDotychczasoweDaneDoPlikuxlsToolStripMenuItem->Text = L"Zapisz dotychczasowe dane do pliku .xls";
			// 
			// toolStripSeparator2
			// 
			this->toolStripSeparator2->Name = L"toolStripSeparator2";
			this->toolStripSeparator2->Size = System::Drawing::Size(283, 6);
			// 
			// generujTekstDoSaldeoToolStripMenuItem
			// 
			this->generujTekstDoSaldeoToolStripMenuItem->Name = L"generujTekstDoSaldeoToolStripMenuItem";
			this->generujTekstDoSaldeoToolStripMenuItem->Size = System::Drawing::Size(286, 22);
			this->generujTekstDoSaldeoToolStripMenuItem->Text = L"Generuj tekst do Saldeo";
			// 
			// toolStripSeparator1
			// 
			this->toolStripSeparator1->Name = L"toolStripSeparator1";
			this->toolStripSeparator1->Size = System::Drawing::Size(283, 6);
			// 
			// zamknijProgramToolStripMenuItem
			// 
			this->zamknijProgramToolStripMenuItem->Name = L"zamknijProgramToolStripMenuItem";
			this->zamknijProgramToolStripMenuItem->Size = System::Drawing::Size(286, 22);
			this->zamknijProgramToolStripMenuItem->Text = L"Zamknij program";
			// 
			// miProperties
			// 
			this->miProperties->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {
				this->ukryjPanelGórnyToolStripMenuItem,
					this->ukryjKomunikatyProgramuToolStripMenuItem
			});
			this->miProperties->Name = L"miProperties";
			this->miProperties->Size = System::Drawing::Size(50, 20);
			this->miProperties->Text = L"Opcje";
			// 
			// ukryjPanelGórnyToolStripMenuItem
			// 
			this->ukryjPanelGórnyToolStripMenuItem->CheckOnClick = true;
			this->ukryjPanelGórnyToolStripMenuItem->Name = L"ukryjPanelGórnyToolStripMenuItem";
			this->ukryjPanelGórnyToolStripMenuItem->Size = System::Drawing::Size(223, 22);
			this->ukryjPanelGórnyToolStripMenuItem->Text = L"Ukryj panel górny";
			this->ukryjPanelGórnyToolStripMenuItem->CheckedChanged += gcnew System::EventHandler(this, &MainForm::ukryjPanelGórnyToolStripMenuItem_CheckedChanged);
			// 
			// ukryjKomunikatyProgramuToolStripMenuItem
			// 
			this->ukryjKomunikatyProgramuToolStripMenuItem->CheckOnClick = true;
			this->ukryjKomunikatyProgramuToolStripMenuItem->Name = L"ukryjKomunikatyProgramuToolStripMenuItem";
			this->ukryjKomunikatyProgramuToolStripMenuItem->Size = System::Drawing::Size(223, 22);
			this->ukryjKomunikatyProgramuToolStripMenuItem->Text = L"Ukryj komunikaty programu";
			this->ukryjKomunikatyProgramuToolStripMenuItem->CheckedChanged += gcnew System::EventHandler(this, &MainForm::ukryjKomunikatyProgramuToolStripMenuItem_CheckedChanged);
			// 
			// miHelp
			// 
			this->miHelp->Name = L"miHelp";
			this->miHelp->Size = System::Drawing::Size(57, 20);
			this->miHelp->Text = L"Pomoc";
			// 
			// lblTax
			// 
			this->lblTax->AutoSize = true;
			this->lblTax->Location = System::Drawing::Point(177, 170);
			this->lblTax->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			this->lblTax->Name = L"lblTax";
			this->lblTax->Size = System::Drawing::Size(34, 16);
			this->lblTax->TabIndex = 42;
			this->lblTax->Text = L"VAT";
			// 
			// panelInputs
			// 
			this->panelInputs->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->panelInputs->Controls->Add(this->cbTax);
			this->panelInputs->Controls->Add(this->label1);
			this->panelInputs->Controls->Add(this->btnAdd);
			this->panelInputs->Controls->Add(this->lblTax);
			this->panelInputs->Controls->Add(this->txtCompany);
			this->panelInputs->Controls->Add(this->txtComments);
			this->panelInputs->Controls->Add(this->txtFvIdent);
			this->panelInputs->Controls->Add(this->lblComments);
			this->panelInputs->Controls->Add(this->label2);
			this->panelInputs->Controls->Add(this->txtDay);
			this->panelInputs->Controls->Add(this->btnSaldeo);
			this->panelInputs->Controls->Add(this->label3);
			this->panelInputs->Controls->Add(this->label14);
			this->panelInputs->Controls->Add(this->txtMonth);
			this->panelInputs->Controls->Add(this->txtPayment);
			this->panelInputs->Controls->Add(this->txtYear);
			this->panelInputs->Controls->Add(this->label15);
			this->panelInputs->Controls->Add(this->txtInvest);
			this->panelInputs->Controls->Add(this->txtWhoPayed);
			this->panelInputs->Controls->Add(this->label4);
			this->panelInputs->Controls->Add(this->txtNewNotFvFilename);
			this->panelInputs->Controls->Add(this->btnSplit);
			this->panelInputs->Controls->Add(this->btnExit);
			this->panelInputs->Controls->Add(this->txtNetVal);
			this->panelInputs->Controls->Add(this->btnDeleteLast);
			this->panelInputs->Controls->Add(this->label5);
			this->panelInputs->Controls->Add(this->label12);
			this->panelInputs->Controls->Add(this->txtGrossVal);
			this->panelInputs->Controls->Add(this->txtDescr);
			this->panelInputs->Controls->Add(this->label6);
			this->panelInputs->Controls->Add(this->label11);
			this->panelInputs->Controls->Add(this->label10);
			this->panelInputs->Location = System::Drawing::Point(23, 149);
			this->panelInputs->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->panelInputs->Name = L"panelInputs";
			this->panelInputs->Size = System::Drawing::Size(478, 364);
			this->panelInputs->TabIndex = 43;
			// 
			// cbTax
			// 
			this->cbTax->FormattingEnabled = true;
			this->cbTax->Items->AddRange(gcnew cli::array< System::Object^  >(4) { L"23", L"8", L"oo", L"mix" });
			this->cbTax->Location = System::Drawing::Point(220, 166);
			this->cbTax->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->cbTax->Name = L"cbTax";
			this->cbTax->Size = System::Drawing::Size(59, 24);
			this->cbTax->TabIndex = 10;
			this->cbTax->Text = L"23";
			// 
			// MainForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->AutoSize = true;
			this->AutoSizeMode = System::Windows::Forms::AutoSizeMode::GrowAndShrink;
			this->BackColor = System::Drawing::SystemColors::InactiveCaption;
			this->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Center;
			this->ClientSize = System::Drawing::Size(1107, 528);
			this->Controls->Add(this->panelInputs);
			this->Controls->Add(this->panelFilename);
			this->Controls->Add(this->panelTop);
			this->Controls->Add(this->rtxtProgramOutput);
			this->Controls->Add(this->menuStrip1);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::Fixed3D;
			this->MainMenuStrip = this->menuStrip1;
			this->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			this->Name = L"MainForm";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterParent;
			this->Text = L"Projekt: Faktury";
			this->Load += gcnew System::EventHandler(this, &MainForm::MainForm_Load);
			this->panelTop->ResumeLayout(false);
			this->panelTop->PerformLayout();
			this->panelFilename->ResumeLayout(false);
			this->panelFilename->PerformLayout();
			this->menuStrip1->ResumeLayout(false);
			this->menuStrip1->PerformLayout();
			this->panelInputs->ResumeLayout(false);
			this->panelInputs->PerformLayout();
			this->ResumeLayout(false);
			this->PerformLayout();

		}
#pragma endregion

		// some of the following methods are implemented in this file

	private:
		// BUTTONS
		void btnAdd_Click(System::Object^ sender, System::EventArgs^ e);
		void btnSplit_Click(System::Object^ sender, System::EventArgs^ e);
		void btnDeleteLast_Click(System::Object^ sender, System::EventArgs^ e);
		void btnSaldeo_Click(System::Object^ sender, System::EventArgs^ e);
		void btnExit_Click(System::Object^ sender, System::EventArgs^ e)
		{
			if (!Globals::vecFvFromImg.empty())
			{
				auto result = MessageBox::Show("Czy chcesz zachowaæ dotychczas wprowadzone dane o fakturach ?",
					"Niezapisane dane", MessageBoxButtons::YesNoCancel);
				if (result == System::Windows::Forms::DialogResult::Yes)
					// TODO: save current input
					return;
			}

			Application::Exit();
		}
		// FORM and OTHER Controls
		void MainForm_Load(System::Object^ sender, System::EventArgs^ e);
		void lblCurrentFile_MouseHover(System::Object^ sender, System::EventArgs^ e);
		void lblCurrentFile_MouseLeave(System::Object^ sender, System::EventArgs^ e)
		{
			if (this->Controls->Find(L"rtxtOnMouseHover", true)->Length)
				this->rtxtOnMouseHover->Visible = false;
		}
		// TEXT INPUTS
		void txtCompany_TextChanged(System::Object^ sender, System::EventArgs^ e);
		void txtCompany_PreviewKeyDown(System::Object^ sender, System::Windows::Forms::PreviewKeyDownEventArgs^ e);
		void txtCompany_KeyPress(System::Object^ sender, System::Windows::Forms::KeyPressEventArgs^ e)
		{
			if (this->numberKeyPressed)
				e->Handled = true;
		}
		void txtCompany_Leave(System::Object^ sender, System::EventArgs^ e)
		{
			if (rtxtDynamicOutput->Visible)
			{
				if (Globals::currShown.size() && !numberKeyPressed)
					txtCompany->Text = wstrtoustr(Globals::currShown[1]);

				rtxtDynamicOutput->Visible = false;
			}
		}
		void txtInvest_TextChanged(System::Object^ sender, System::EventArgs^ e);
		void txtInvest_PreviewKeyDown(System::Object^ sender, System::Windows::Forms::PreviewKeyDownEventArgs^ e);
		void txtInvest_KeyPress(System::Object^ sender, System::Windows::Forms::KeyPressEventArgs^ e)
		{
			if (this->numberKeyPressed)
				e->Handled = true;
		}
		void txtInvest_Leave(System::Object^ sender, System::EventArgs^ e)
		{
			if (rtxtDynamicOutput->Visible)
			{
				if (Globals::currShown.size() && !numberKeyPressed)
					txtInvest->Text = wstrtoustr(Globals::currShown[1]);

				rtxtDynamicOutput->Visible = false;
			}
		}
		void txtGrossVal_Enter(System::Object^ sender, System::EventArgs^ e)
		{
			if (cbTax->Text != "mix")
				Globals::AutoFillOtherPriceTBox(txtNetVal, txtGrossVal, Globals::GetTaxFromCBox(cbTax));
		}
		void txtNetVal_Enter(System::Object^ sender, System::EventArgs^ e)
		{
			if (cbTax->Text != "mix")
				Globals::AutoFillOtherPriceTBox(txtGrossVal, txtNetVal, Globals::GetTaxFromCBox(cbTax));
		}
		void txtNetVal_Leave(System::Object^ sender, System::EventArgs^ e)
		{
			//txtNetVal->Text = EvaluateExpr(txtNetVal->Text);
		}
		void txtGrossVal_Leave(System::Object^ sender, System::EventArgs^ e)
		{
			if (cbTax->Text != "mix")
				Globals::AutoFillOtherPriceTBox(txtGrossVal, txtNetVal, Globals::GetTaxFromCBox(cbTax));
		}
		// CHECKBOXES
		void chbIsFv_Enter(System::Object^ sender, System::EventArgs^ e)
		{
			//chbIsFv->BackColor = System::Drawing::Color::YellowGreen;
			chbIsFv->Font = gcnew System::Drawing::Font("Microsoft Sans Serif", 7.6f, FontStyle::Bold);
			lblCurrentFile->Font = gcnew System::Drawing::Font("Microsoft Sans Serif", 7.6f, FontStyle::Bold);
		}
		void chbIsFv_Leave(System::Object^ sender, System::EventArgs^ e)
		{
			//chbIsFv->ResetBackColor();
			chbIsFv->Font = gcnew System::Drawing::Font("Microsoft Sans Serif", 8.25f, FontStyle::Regular);
			lblCurrentFile->Font = gcnew System::Drawing::Font("Microsoft Sans Serif", 7.6f, FontStyle::Regular);
		}
		void chbIsFv_CheckedChanged(System::Object^ sender, System::EventArgs^ e)
		{
			if (!chbIsFv->Checked)
			{
				this->HideFvComponents();
				label1->Visible = true;
				txtNewNotFvFilename->Visible = true;
				this->ClearAllInputs();
				label1->Text = "Nowa nazwa pliku";
			}
			else
			{
				label1->Text = "Firma";
				this->ShowFvComponents();
				txtNewNotFvFilename->Visible = false;
			}
		}
		private: System::Void chbAnotherPage_CheckedChanged(System::Object^ sender, System::EventArgs^ e)
		{
			if (chbAnotherPage->Checked)
			{
				chbIsFv->Checked = false;
				chbIsFv->Visible = false;
				this->AnotherPagePrepare();
			}
			else
			{
				label1->Text = "Firma";
				chbIsFv->Visible = true;
				chbIsFv->Checked = true;
				this->ShowFvComponents();
			}
		}
		// MENU Items
		void wyjdŸToolStripMenuItem_Click(System::Object^ sender, System::EventArgs^ e)
		{
			btnExit_Click(sender, e);
		}
		void ukryjPanelGórnyToolStripMenuItem_CheckedChanged(System::Object^ sender, System::EventArgs^ e)
		{
			if (ukryjPanelGórnyToolStripMenuItem->Checked)
			{
				cached_panel_size = panelTop->Size;
				panelTop->Size = System::Drawing::Size(1, 1);
				panelInputs->Location = System::Drawing::Point
				(panelInputs->Location.X, panelInputs->Location.Y - cached_panel_size.Height);
				panelFilename->Location = System::Drawing::Point
				(panelFilename->Location.X, panelFilename->Location.Y - cached_panel_size.Height);
				rtxtProgramOutput->Location = System::Drawing::Point
				(rtxtProgramOutput->Location.X, rtxtProgramOutput->Location.Y - cached_panel_size.Height);
				panelTop->Hide();
			}
			else
			{
				panelTop->Size = cached_panel_size;
				panelInputs->Location = System::Drawing::Point
				(panelInputs->Location.X, panelInputs->Location.Y + cached_panel_size.Height);
				panelFilename->Location = System::Drawing::Point
				(panelFilename->Location.X, panelFilename->Location.Y + cached_panel_size.Height);
				rtxtProgramOutput->Location = System::Drawing::Point
				(rtxtProgramOutput->Location.X, rtxtProgramOutput->Location.Y + cached_panel_size.Height);
				panelTop->Show();
			}
		}
		void ukryjKomunikatyProgramuToolStripMenuItem_CheckedChanged(System::Object^ sender, System::EventArgs^ e)
		{
			if (ukryjKomunikatyProgramuToolStripMenuItem->Checked)
			{
				cached_programOutput_size = rtxtProgramOutput->Size;
				rtxtProgramOutput->Size = System::Drawing::Size(1, 1);
				rtxtProgramOutput->Hide();
			}
			else
			{
				rtxtProgramOutput->Size = cached_programOutput_size;
				rtxtProgramOutput->Show();
			}
		}
};
}
