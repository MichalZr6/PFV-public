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
		
		void TryRecognizeCurrFile();

		void txtDateSameAsFileLastModDate();

		bool TryRecoAutopayInvoice(std::wstring rx_pattern);	// Autopay
		bool TryRecoVTSInvoice(std::wstring rx_pattern);		// VTS Polska
		bool TryRecoOrangeInvoice(std::wstring rx_pattern);		// Orange		
		bool TryRecoIglotechInvoice(std::wstring rx_pattern);	// Iglotech
		bool TryRecoNaviInvoice(std::wstring rx_pattern);		// NaviFleet
		bool TryRecoTCHWInvoice(std::wstring rx_pattern);		// TCHW
		bool TryRecoWienkraInvoice(std::wstring rx_pattern);	// Wienkra
		bool TryRecoSGKlimaInvoice(std::wstring rx_pattern);	// SGKlima
		bool TryRecoWimarInvoice(std::wstring rx_pattern);		// Wimar
		bool TryRecoHerbudInvoice(std::wstring rx_pattern);		// Herbud
		bool TryRecoOpenAIInvoice(std::wstring rx_pattern);		// OpenAI
		bool TryRecoSzydloInvoice(std::wstring rx_pattern);		// Biuro Rachunkowe

		bool NewNonFvAdd(void);
		void WriteToTextBoxNextPageName(void);
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
		bool userSelectionMade = false;
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
			btnAdd = (gcnew System::Windows::Forms::Button());
			label1 = (gcnew System::Windows::Forms::Label());
			txtCompany = (gcnew System::Windows::Forms::TextBox());
			txtFvIdent = (gcnew System::Windows::Forms::TextBox());
			label2 = (gcnew System::Windows::Forms::Label());
			label3 = (gcnew System::Windows::Forms::Label());
			txtDay = (gcnew System::Windows::Forms::TextBox());
			txtMonth = (gcnew System::Windows::Forms::TextBox());
			txtYear = (gcnew System::Windows::Forms::TextBox());
			label4 = (gcnew System::Windows::Forms::Label());
			txtInvest = (gcnew System::Windows::Forms::TextBox());
			rtxtProgramOutput = (gcnew System::Windows::Forms::RichTextBox());
			btnSplit = (gcnew System::Windows::Forms::Button());
			label5 = (gcnew System::Windows::Forms::Label());
			txtNetVal = (gcnew System::Windows::Forms::TextBox());
			label6 = (gcnew System::Windows::Forms::Label());
			txtGrossVal = (gcnew System::Windows::Forms::TextBox());
			panelTop = (gcnew System::Windows::Forms::Panel());
			txtFvDir = (gcnew System::Windows::Forms::TextBox());
			label9 = (gcnew System::Windows::Forms::Label());
			txtFvListOutFilename = (gcnew System::Windows::Forms::TextBox());
			label8 = (gcnew System::Windows::Forms::Label());
			txtFvListFilename = (gcnew System::Windows::Forms::TextBox());
			label7 = (gcnew System::Windows::Forms::Label());
			label10 = (gcnew System::Windows::Forms::Label());
			label11 = (gcnew System::Windows::Forms::Label());
			label12 = (gcnew System::Windows::Forms::Label());
			txtDescr = (gcnew System::Windows::Forms::TextBox());
			btnDeleteLast = (gcnew System::Windows::Forms::Button());
			btnExit = (gcnew System::Windows::Forms::Button());
			chbIsFv = (gcnew System::Windows::Forms::CheckBox());
			lblCurrFileStatic = (gcnew System::Windows::Forms::Label());
			lblCurrentFile = (gcnew System::Windows::Forms::Label());
			txtNewNotFvFilename = (gcnew System::Windows::Forms::TextBox());
			label14 = (gcnew System::Windows::Forms::Label());
			txtPayment = (gcnew System::Windows::Forms::TextBox());
			label15 = (gcnew System::Windows::Forms::Label());
			txtWhoPayed = (gcnew System::Windows::Forms::TextBox());
			btnSaldeo = (gcnew System::Windows::Forms::Button());
			folderBrowser = (gcnew System::Windows::Forms::FolderBrowserDialog());
			panelFilename = (gcnew System::Windows::Forms::Panel());
			chbAnotherPage = (gcnew System::Windows::Forms::CheckBox());
			lblComments = (gcnew System::Windows::Forms::Label());
			txtComments = (gcnew System::Windows::Forms::TextBox());
			menuStrip1 = (gcnew System::Windows::Forms::MenuStrip());
			wykonajAkcjêToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			dodajToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			usuñOstatniWpisToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			podzielOstatniaFakturêToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			toolStripSeparator3 = (gcnew System::Windows::Forms::ToolStripSeparator());
			toolStripMenuItem1 = (gcnew System::Windows::Forms::ToolStripMenuItem());
			zapiszDotychczasoweDaneDoPlikuxlsToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			toolStripSeparator2 = (gcnew System::Windows::Forms::ToolStripSeparator());
			generujTekstDoSaldeoToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			toolStripSeparator1 = (gcnew System::Windows::Forms::ToolStripSeparator());
			zamknijProgramToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			miProperties = (gcnew System::Windows::Forms::ToolStripMenuItem());
			ukryjPanelGórnyToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			ukryjKomunikatyProgramuToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			miHelp = (gcnew System::Windows::Forms::ToolStripMenuItem());
			lblTax = (gcnew System::Windows::Forms::Label());
			panelInputs = (gcnew System::Windows::Forms::Panel());
			cbTax = (gcnew System::Windows::Forms::ComboBox());
			panelTop->SuspendLayout();
			panelFilename->SuspendLayout();
			menuStrip1->SuspendLayout();
			panelInputs->SuspendLayout();
			SuspendLayout();
			// 
			// btnAdd
			// 
			btnAdd->Location = System::Drawing::Point(8, 274);
			btnAdd->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			btnAdd->Name = L"btnAdd";
			btnAdd->Size = System::Drawing::Size(141, 28);
			btnAdd->TabIndex = 15;
			btnAdd->Text = L"Do&daj";
			btnAdd->UseVisualStyleBackColor = true;
			btnAdd->Click += gcnew System::EventHandler(this, &MainForm::btnAdd_Click);
			// 
			// label1
			// 
			label1->AutoSize = true;
			label1->Location = System::Drawing::Point(4, 11);
			label1->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			label1->Name = L"label1";
			label1->Size = System::Drawing::Size(41, 16);
			label1->TabIndex = 1;
			label1->Text = L"Firma";
			// 
			// txtCompany
			// 
			txtCompany->Location = System::Drawing::Point(89, 7);
			txtCompany->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			txtCompany->MaxLength = 40;
			txtCompany->Name = L"txtCompany";
			txtCompany->Size = System::Drawing::Size(367, 22);
			txtCompany->TabIndex = 2;
			txtCompany->TextChanged += gcnew System::EventHandler(this, &MainForm::txtCompany_TextChanged);
			txtCompany->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &MainForm::txtCompany_KeyPress);
			txtCompany->Leave += gcnew System::EventHandler(this, &MainForm::txtCompany_Leave);
			txtCompany->PreviewKeyDown += gcnew System::Windows::Forms::PreviewKeyDownEventHandler(this, &MainForm::txtCompany_PreviewKeyDown);
			// 
			// txtFvIdent
			// 
			txtFvIdent->Location = System::Drawing::Point(89, 39);
			txtFvIdent->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			txtFvIdent->MaxLength = 30;
			txtFvIdent->Name = L"txtFvIdent";
			txtFvIdent->Size = System::Drawing::Size(367, 22);
			txtFvIdent->TabIndex = 3;
			// 
			// label2
			// 
			label2->AutoSize = true;
			label2->Location = System::Drawing::Point(4, 48);
			label2->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			label2->Name = L"label2";
			label2->Size = System::Drawing::Size(63, 16);
			label2->TabIndex = 4;
			label2->Text = L"Nr faktury";
			// 
			// label3
			// 
			label3->AutoSize = true;
			label3->Location = System::Drawing::Point(4, 143);
			label3->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			label3->Name = L"label3";
			label3->Size = System::Drawing::Size(36, 16);
			label3->TabIndex = 6;
			label3->Text = L"Data";
			// 
			// txtDay
			// 
			txtDay->Location = System::Drawing::Point(89, 134);
			txtDay->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			txtDay->MaxLength = 2;
			txtDay->Name = L"txtDay";
			txtDay->Size = System::Drawing::Size(32, 22);
			txtDay->TabIndex = 6;
			// 
			// txtMonth
			// 
			txtMonth->Location = System::Drawing::Point(155, 133);
			txtMonth->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			txtMonth->MaxLength = 2;
			txtMonth->Name = L"txtMonth";
			txtMonth->Size = System::Drawing::Size(32, 22);
			txtMonth->TabIndex = 7;
			// 
			// txtYear
			// 
			txtYear->Location = System::Drawing::Point(220, 134);
			txtYear->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			txtYear->MaxLength = 4;
			txtYear->Name = L"txtYear";
			txtYear->Size = System::Drawing::Size(68, 22);
			txtYear->TabIndex = 8;
			txtYear->TabStop = false;
			// 
			// label4
			// 
			label4->AutoSize = true;
			label4->Location = System::Drawing::Point(4, 80);
			label4->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			label4->Name = L"label4";
			label4->Size = System::Drawing::Size(69, 16);
			label4->TabIndex = 10;
			label4->Text = L"Inwestycja";
			// 
			// txtInvest
			// 
			txtInvest->Location = System::Drawing::Point(89, 70);
			txtInvest->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			txtInvest->MaxLength = 50;
			txtInvest->Name = L"txtInvest";
			txtInvest->Size = System::Drawing::Size(367, 22);
			txtInvest->TabIndex = 4;
			txtInvest->TextChanged += gcnew System::EventHandler(this, &MainForm::txtInvest_TextChanged);
			txtInvest->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &MainForm::txtInvest_KeyPress);
			txtInvest->Leave += gcnew System::EventHandler(this, &MainForm::txtInvest_Leave);
			txtInvest->PreviewKeyDown += gcnew System::Windows::Forms::PreviewKeyDownEventHandler(this, &MainForm::txtInvest_PreviewKeyDown);
			// 
			// rtxtProgramOutput
			// 
			rtxtProgramOutput->Location = System::Drawing::Point(509, 107);
			rtxtProgramOutput->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			rtxtProgramOutput->Name = L"rtxtProgramOutput";
			rtxtProgramOutput->ReadOnly = true;
			rtxtProgramOutput->Size = System::Drawing::Size(596, 405);
			rtxtProgramOutput->TabIndex = 11;
			rtxtProgramOutput->TabStop = false;
			rtxtProgramOutput->Text = L"";
			// 
			// btnSplit
			// 
			btnSplit->Enabled = false;
			btnSplit->Location = System::Drawing::Point(157, 274);
			btnSplit->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			btnSplit->Name = L"btnSplit";
			btnSplit->Size = System::Drawing::Size(300, 28);
			btnSplit->TabIndex = 16;
			btnSplit->Text = L"Podziel ostatni¹ dodan¹ fakturê na czêœci";
			btnSplit->UseVisualStyleBackColor = true;
			btnSplit->Click += gcnew System::EventHandler(this, &MainForm::btnSplit_Click);
			// 
			// label5
			// 
			label5->AutoSize = true;
			label5->Location = System::Drawing::Point(4, 175);
			label5->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			label5->Name = L"label5";
			label5->Size = System::Drawing::Size(70, 16);
			label5->TabIndex = 16;
			label5->Text = L"Wart. netto";
			// 
			// txtNetVal
			// 
			txtNetVal->Location = System::Drawing::Point(89, 166);
			txtNetVal->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			txtNetVal->MaxLength = 30;
			txtNetVal->Name = L"txtNetVal";
			txtNetVal->Size = System::Drawing::Size(79, 22);
			txtNetVal->TabIndex = 9;
			txtNetVal->Enter += gcnew System::EventHandler(this, &MainForm::txtNetVal_Enter);
			txtNetVal->Leave += gcnew System::EventHandler(this, &MainForm::txtNetVal_Leave);
			// 
			// label6
			// 
			label6->AutoSize = true;
			label6->Location = System::Drawing::Point(295, 170);
			label6->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			label6->Name = L"label6";
			label6->Size = System::Drawing::Size(41, 16);
			label6->TabIndex = 18;
			label6->Text = L"Brutto";
			// 
			// txtGrossVal
			// 
			txtGrossVal->Location = System::Drawing::Point(349, 164);
			txtGrossVal->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			txtGrossVal->MaxLength = 30;
			txtGrossVal->Name = L"txtGrossVal";
			txtGrossVal->Size = System::Drawing::Size(107, 22);
			txtGrossVal->TabIndex = 11;
			txtGrossVal->Enter += gcnew System::EventHandler(this, &MainForm::txtGrossVal_Enter);
			txtGrossVal->Leave += gcnew System::EventHandler(this, &MainForm::txtGrossVal_Leave);
			// 
			// panelTop
			// 
			panelTop->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			panelTop->Controls->Add(txtFvDir);
			panelTop->Controls->Add(label9);
			panelTop->Controls->Add(txtFvListOutFilename);
			panelTop->Controls->Add(label8);
			panelTop->Controls->Add(txtFvListFilename);
			panelTop->Controls->Add(label7);
			panelTop->Location = System::Drawing::Point(23, 46);
			panelTop->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			panelTop->Name = L"panelTop";
			panelTop->Size = System::Drawing::Size(1083, 49);
			panelTop->TabIndex = 19;
			// 
			// txtFvDir
			// 
			txtFvDir->Location = System::Drawing::Point(865, 11);
			txtFvDir->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			txtFvDir->Name = L"txtFvDir";
			txtFvDir->Size = System::Drawing::Size(188, 22);
			txtFvDir->TabIndex = 25;
			txtFvDir->TabStop = false;
			txtFvDir->Text = L"Fv/";
			// 
			// label9
			// 
			label9->AutoSize = true;
			label9->Location = System::Drawing::Point(711, 15);
			label9->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			label9->Name = L"label9";
			label9->Size = System::Drawing::Size(134, 16);
			label9->TabIndex = 24;
			label9->Text = L"Œcie¿ka folderu faktur";
			// 
			// txtFvListOutFilename
			// 
			txtFvListOutFilename->Location = System::Drawing::Point(513, 11);
			txtFvListOutFilename->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			txtFvListOutFilename->Name = L"txtFvListOutFilename";
			txtFvListOutFilename->Size = System::Drawing::Size(188, 22);
			txtFvListOutFilename->TabIndex = 23;
			txtFvListOutFilename->TabStop = false;
			txtFvListOutFilename->Text = L"Zestawienie Faktur_out.xls";
			// 
			// label8
			// 
			label8->AutoSize = true;
			label8->Location = System::Drawing::Point(313, 15);
			label8->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			label8->Name = L"label8";
			label8->Size = System::Drawing::Size(179, 16);
			label8->TabIndex = 22;
			label8->Text = L"Plik zestawienia wynikowego";
			// 
			// txtFvListFilename
			// 
			txtFvListFilename->Location = System::Drawing::Point(121, 11);
			txtFvListFilename->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			txtFvListFilename->Name = L"txtFvListFilename";
			txtFvListFilename->Size = System::Drawing::Size(183, 22);
			txtFvListFilename->TabIndex = 21;
			txtFvListFilename->TabStop = false;
			txtFvListFilename->Text = L"Zestawienie Faktur.xls";
			// 
			// label7
			// 
			label7->AutoSize = true;
			label7->Location = System::Drawing::Point(4, 15);
			label7->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			label7->Name = L"label7";
			label7->Size = System::Drawing::Size(102, 16);
			label7->TabIndex = 20;
			label7->Text = L"Plik zestawienia";
			// 
			// label10
			// 
			label10->AutoSize = true;
			label10->Location = System::Drawing::Point(131, 138);
			label10->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			label10->Name = L"label10";
			label10->Size = System::Drawing::Size(11, 16);
			label10->TabIndex = 20;
			label10->Text = L"/";
			// 
			// label11
			// 
			label11->AutoSize = true;
			label11->Location = System::Drawing::Point(196, 138);
			label11->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			label11->Name = L"label11";
			label11->Size = System::Drawing::Size(11, 16);
			label11->TabIndex = 21;
			label11->Text = L"/";
			// 
			// label12
			// 
			label12->AutoSize = true;
			label12->Location = System::Drawing::Point(4, 111);
			label12->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			label12->Name = L"label12";
			label12->Size = System::Drawing::Size(35, 16);
			label12->TabIndex = 28;
			label12->Text = L"Opis";
			// 
			// txtDescr
			// 
			txtDescr->Location = System::Drawing::Point(89, 102);
			txtDescr->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			txtDescr->MaxLength = 50;
			txtDescr->Name = L"txtDescr";
			txtDescr->Size = System::Drawing::Size(367, 22);
			txtDescr->TabIndex = 5;
			// 
			// btnDeleteLast
			// 
			btnDeleteLast->Location = System::Drawing::Point(8, 310);
			btnDeleteLast->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			btnDeleteLast->Name = L"btnDeleteLast";
			btnDeleteLast->Size = System::Drawing::Size(141, 28);
			btnDeleteLast->TabIndex = 17;
			btnDeleteLast->Text = L"Usuñ ostatni wpis";
			btnDeleteLast->UseVisualStyleBackColor = true;
			btnDeleteLast->Click += gcnew System::EventHandler(this, &MainForm::btnDeleteLast_Click);
			// 
			// btnExit
			// 
			btnExit->Location = System::Drawing::Point(347, 310);
			btnExit->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			btnExit->Name = L"btnExit";
			btnExit->Size = System::Drawing::Size(111, 28);
			btnExit->TabIndex = 19;
			btnExit->Text = L"&WyjdŸ";
			btnExit->UseVisualStyleBackColor = true;
			btnExit->Click += gcnew System::EventHandler(this, &MainForm::btnExit_Click);
			// 
			// chbIsFv
			// 
			chbIsFv->AutoSize = true;
			chbIsFv->Checked = true;
			chbIsFv->CheckState = System::Windows::Forms::CheckState::Checked;
			chbIsFv->Location = System::Drawing::Point(8, 26);
			chbIsFv->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			chbIsFv->Name = L"chbIsFv";
			chbIsFv->Size = System::Drawing::Size(96, 20);
			chbIsFv->TabIndex = 1;
			chbIsFv->Text = L"faktura VAT";
			chbIsFv->UseVisualStyleBackColor = true;
			chbIsFv->CheckedChanged += gcnew System::EventHandler(this, &MainForm::chbIsFv_CheckedChanged);
			chbIsFv->Enter += gcnew System::EventHandler(this, &MainForm::chbIsFv_Enter);
			chbIsFv->Leave += gcnew System::EventHandler(this, &MainForm::chbIsFv_Leave);
			// 
			// lblCurrFileStatic
			// 
			lblCurrFileStatic->AutoSize = true;
			lblCurrFileStatic->Location = System::Drawing::Point(4, 4);
			lblCurrFileStatic->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			lblCurrFileStatic->Name = L"lblCurrFileStatic";
			lblCurrFileStatic->Size = System::Drawing::Size(85, 16);
			lblCurrFileStatic->TabIndex = 32;
			lblCurrFileStatic->Text = L"Aktualny plik:";
			// 
			// lblCurrentFile
			// 
			lblCurrentFile->AutoSize = true;
			lblCurrentFile->Location = System::Drawing::Point(119, 4);
			lblCurrentFile->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			lblCurrentFile->Name = L"lblCurrentFile";
			lblCurrentFile->Size = System::Drawing::Size(0, 16);
			lblCurrentFile->TabIndex = 33;
			lblCurrentFile->MouseLeave += gcnew System::EventHandler(this, &MainForm::lblCurrentFile_MouseLeave);
			lblCurrentFile->MouseHover += gcnew System::EventHandler(this, &MainForm::lblCurrentFile_MouseHover);
			// 
			// txtNewNotFvFilename
			// 
			txtNewNotFvFilename->Location = System::Drawing::Point(167, 7);
			txtNewNotFvFilename->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			txtNewNotFvFilename->Name = L"txtNewNotFvFilename";
			txtNewNotFvFilename->Size = System::Drawing::Size(289, 22);
			txtNewNotFvFilename->TabIndex = 2;
			txtNewNotFvFilename->Visible = false;
			// 
			// label14
			// 
			label14->AutoSize = true;
			label14->Location = System::Drawing::Point(220, 204);
			label14->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			label14->Name = L"label14";
			label14->Size = System::Drawing::Size(108, 16);
			label14->TabIndex = 37;
			label14->Text = L"P³atnoœæ/Termin";
			// 
			// txtPayment
			// 
			txtPayment->Location = System::Drawing::Point(344, 196);
			txtPayment->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			txtPayment->MaxLength = 20;
			txtPayment->Name = L"txtPayment";
			txtPayment->Size = System::Drawing::Size(112, 22);
			txtPayment->TabIndex = 13;
			// 
			// label15
			// 
			label15->AutoSize = true;
			label15->Location = System::Drawing::Point(4, 207);
			label15->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			label15->Name = L"label15";
			label15->Size = System::Drawing::Size(46, 16);
			label15->TabIndex = 36;
			label15->Text = L"P³aci³";
			// 
			// txtWhoPayed
			// 
			txtWhoPayed->Location = System::Drawing::Point(89, 201);
			txtWhoPayed->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			txtWhoPayed->MaxLength = 2;
			txtWhoPayed->Name = L"txtWhoPayed";
			txtWhoPayed->Size = System::Drawing::Size(79, 22);
			txtWhoPayed->TabIndex = 12;
			// 
			// btnSaldeo
			// 
			btnSaldeo->Location = System::Drawing::Point(157, 310);
			btnSaldeo->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			btnSaldeo->Name = L"btnSaldeo";
			btnSaldeo->Size = System::Drawing::Size(100, 28);
			btnSaldeo->TabIndex = 18;
			btnSaldeo->Text = L"Saldeo Text";
			btnSaldeo->UseVisualStyleBackColor = true;
			btnSaldeo->Click += gcnew System::EventHandler(this, &MainForm::btnSaldeo_Click);
			// 
			// folderBrowser
			// 
			folderBrowser->RootFolder = System::Environment::SpecialFolder::MyComputer;
			folderBrowser->ShowNewFolderButton = false;
			// 
			// panelFilename
			// 
			panelFilename->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			panelFilename->Controls->Add(chbAnotherPage);
			panelFilename->Controls->Add(lblCurrFileStatic);
			panelFilename->Controls->Add(chbIsFv);
			panelFilename->Controls->Add(lblCurrentFile);
			panelFilename->Location = System::Drawing::Point(23, 94);
			panelFilename->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			panelFilename->Name = L"panelFilename";
			panelFilename->RightToLeft = System::Windows::Forms::RightToLeft::No;
			panelFilename->Size = System::Drawing::Size(478, 60);
			panelFilename->TabIndex = 39;
			// 
			// chbAnotherPage
			// 
			chbAnotherPage->AutoSize = true;
			chbAnotherPage->Location = System::Drawing::Point(148, 26);
			chbAnotherPage->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			chbAnotherPage->Name = L"chbAnotherPage";
			chbAnotherPage->Size = System::Drawing::Size(181, 20);
			chbAnotherPage->TabIndex = 34;
			chbAnotherPage->Text = L"kolejna strona poprz. pliku";
			chbAnotherPage->UseVisualStyleBackColor = true;
			chbAnotherPage->CheckedChanged += gcnew System::EventHandler(this, &MainForm::chbAnotherPage_CheckedChanged);
			// 
			// lblComments
			// 
			lblComments->AutoSize = true;
			lblComments->Location = System::Drawing::Point(4, 240);
			lblComments->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			lblComments->Name = L"lblComments";
			lblComments->Size = System::Drawing::Size(70, 16);
			lblComments->TabIndex = 40;
			lblComments->Text = L"Komentarz";
			// 
			// txtComments
			// 
			txtComments->Location = System::Drawing::Point(89, 231);
			txtComments->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			txtComments->MaxLength = 100;
			txtComments->Name = L"txtComments";
			txtComments->Size = System::Drawing::Size(367, 22);
			txtComments->TabIndex = 14;
			// 
			// menuStrip1
			// 
			menuStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(3) {
				wykonajAkcjêToolStripMenuItem,
					miProperties, miHelp
			});
			menuStrip1->Location = System::Drawing::Point(0, 0);
			menuStrip1->Name = L"menuStrip1";
			menuStrip1->Padding = System::Windows::Forms::Padding(8, 2, 0, 2);
			menuStrip1->Size = System::Drawing::Size(1107, 24);
			menuStrip1->TabIndex = 41;
			menuStrip1->Text = L"menuStrip1";
			// 
			// wykonajAkcjêToolStripMenuItem
			// 
			wykonajAkcjêToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(10) {
				dodajToolStripMenuItem,
					usuñOstatniWpisToolStripMenuItem, podzielOstatniaFakturêToolStripMenuItem, toolStripSeparator3, toolStripMenuItem1,
					zapiszDotychczasoweDaneDoPlikuxlsToolStripMenuItem, toolStripSeparator2, generujTekstDoSaldeoToolStripMenuItem,
					toolStripSeparator1, zamknijProgramToolStripMenuItem
			});
			wykonajAkcjêToolStripMenuItem->Name = L"wykonajAkcjêToolStripMenuItem";
			wykonajAkcjêToolStripMenuItem->Size = System::Drawing::Size(95, 20);
			wykonajAkcjêToolStripMenuItem->Text = L"Wykonaj akcjê";
			// 
			// dodajToolStripMenuItem
			// 
			dodajToolStripMenuItem->Name = L"dodajToolStripMenuItem";
			dodajToolStripMenuItem->Size = System::Drawing::Size(286, 22);
			dodajToolStripMenuItem->Text = L"Dodaj";
			// 
			// usuñOstatniWpisToolStripMenuItem
			// 
			usuñOstatniWpisToolStripMenuItem->Name = L"usuñOstatniWpisToolStripMenuItem";
			usuñOstatniWpisToolStripMenuItem->Size = System::Drawing::Size(286, 22);
			usuñOstatniWpisToolStripMenuItem->Text = L"Usuñ ostatni wpis";
			// 
			// podzielOstatniaFakturêToolStripMenuItem
			// 
			podzielOstatniaFakturêToolStripMenuItem->Name = L"podzielOstatniaFakturêToolStripMenuItem";
			podzielOstatniaFakturêToolStripMenuItem->Size = System::Drawing::Size(286, 22);
			podzielOstatniaFakturêToolStripMenuItem->Text = L"Podziel ostatni¹ fakturê";
			// 
			// toolStripSeparator3
			// 
			toolStripSeparator3->Name = L"toolStripSeparator3";
			toolStripSeparator3->Size = System::Drawing::Size(283, 6);
			// 
			// toolStripMenuItem1
			// 
			toolStripMenuItem1->Name = L"toolStripMenuItem1";
			toolStripMenuItem1->Size = System::Drawing::Size(286, 22);
			toolStripMenuItem1->Text = L"Ukryj komunikaty programu";
			// 
			// zapiszDotychczasoweDaneDoPlikuxlsToolStripMenuItem
			// 
			zapiszDotychczasoweDaneDoPlikuxlsToolStripMenuItem->Name = L"zapiszDotychczasoweDaneDoPlikuxlsToolStripMenuItem";
			zapiszDotychczasoweDaneDoPlikuxlsToolStripMenuItem->Size = System::Drawing::Size(286, 22);
			zapiszDotychczasoweDaneDoPlikuxlsToolStripMenuItem->Text = L"Zapisz dotychczasowe dane do pliku .xls";
			// 
			// toolStripSeparator2
			// 
			toolStripSeparator2->Name = L"toolStripSeparator2";
			toolStripSeparator2->Size = System::Drawing::Size(283, 6);
			// 
			// generujTekstDoSaldeoToolStripMenuItem
			// 
			generujTekstDoSaldeoToolStripMenuItem->Name = L"generujTekstDoSaldeoToolStripMenuItem";
			generujTekstDoSaldeoToolStripMenuItem->Size = System::Drawing::Size(286, 22);
			generujTekstDoSaldeoToolStripMenuItem->Text = L"Generuj tekst do Saldeo";
			// 
			// toolStripSeparator1
			// 
			toolStripSeparator1->Name = L"toolStripSeparator1";
			toolStripSeparator1->Size = System::Drawing::Size(283, 6);
			// 
			// zamknijProgramToolStripMenuItem
			// 
			zamknijProgramToolStripMenuItem->Name = L"zamknijProgramToolStripMenuItem";
			zamknijProgramToolStripMenuItem->Size = System::Drawing::Size(286, 22);
			zamknijProgramToolStripMenuItem->Text = L"Zamknij program";
			// 
			// miProperties
			// 
			miProperties->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {
				ukryjPanelGórnyToolStripMenuItem,
					ukryjKomunikatyProgramuToolStripMenuItem
			});
			miProperties->Name = L"miProperties";
			miProperties->Size = System::Drawing::Size(50, 20);
			miProperties->Text = L"Opcje";
			// 
			// ukryjPanelGórnyToolStripMenuItem
			// 
			ukryjPanelGórnyToolStripMenuItem->CheckOnClick = true;
			ukryjPanelGórnyToolStripMenuItem->Name = L"ukryjPanelGórnyToolStripMenuItem";
			ukryjPanelGórnyToolStripMenuItem->Size = System::Drawing::Size(223, 22);
			ukryjPanelGórnyToolStripMenuItem->Text = L"Ukryj panel górny";
			ukryjPanelGórnyToolStripMenuItem->CheckedChanged += gcnew System::EventHandler(this, &MainForm::ukryjPanelGórnyToolStripMenuItem_CheckedChanged);
			// 
			// ukryjKomunikatyProgramuToolStripMenuItem
			// 
			ukryjKomunikatyProgramuToolStripMenuItem->CheckOnClick = true;
			ukryjKomunikatyProgramuToolStripMenuItem->Name = L"ukryjKomunikatyProgramuToolStripMenuItem";
			ukryjKomunikatyProgramuToolStripMenuItem->Size = System::Drawing::Size(223, 22);
			ukryjKomunikatyProgramuToolStripMenuItem->Text = L"Ukryj komunikaty programu";
			ukryjKomunikatyProgramuToolStripMenuItem->CheckedChanged += gcnew System::EventHandler(this, &MainForm::ukryjKomunikatyProgramuToolStripMenuItem_CheckedChanged);
			// 
			// miHelp
			// 
			miHelp->Name = L"miHelp";
			miHelp->Size = System::Drawing::Size(57, 20);
			miHelp->Text = L"Pomoc";
			// 
			// lblTax
			// 
			lblTax->AutoSize = true;
			lblTax->Location = System::Drawing::Point(177, 170);
			lblTax->Margin = System::Windows::Forms::Padding(4, 0, 4, 0);
			lblTax->Name = L"lblTax";
			lblTax->Size = System::Drawing::Size(34, 16);
			lblTax->TabIndex = 42;
			lblTax->Text = L"VAT";
			// 
			// panelInputs
			// 
			panelInputs->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			panelInputs->Controls->Add(cbTax);
			panelInputs->Controls->Add(label1);
			panelInputs->Controls->Add(btnAdd);
			panelInputs->Controls->Add(lblTax);
			panelInputs->Controls->Add(txtCompany);
			panelInputs->Controls->Add(txtComments);
			panelInputs->Controls->Add(txtFvIdent);
			panelInputs->Controls->Add(lblComments);
			panelInputs->Controls->Add(label2);
			panelInputs->Controls->Add(txtDay);
			panelInputs->Controls->Add(btnSaldeo);
			panelInputs->Controls->Add(label3);
			panelInputs->Controls->Add(label14);
			panelInputs->Controls->Add(txtMonth);
			panelInputs->Controls->Add(txtPayment);
			panelInputs->Controls->Add(txtYear);
			panelInputs->Controls->Add(label15);
			panelInputs->Controls->Add(txtInvest);
			panelInputs->Controls->Add(txtWhoPayed);
			panelInputs->Controls->Add(label4);
			panelInputs->Controls->Add(txtNewNotFvFilename);
			panelInputs->Controls->Add(btnSplit);
			panelInputs->Controls->Add(btnExit);
			panelInputs->Controls->Add(txtNetVal);
			panelInputs->Controls->Add(btnDeleteLast);
			panelInputs->Controls->Add(label5);
			panelInputs->Controls->Add(label12);
			panelInputs->Controls->Add(txtGrossVal);
			panelInputs->Controls->Add(txtDescr);
			panelInputs->Controls->Add(label6);
			panelInputs->Controls->Add(label11);
			panelInputs->Controls->Add(label10);
			panelInputs->Location = System::Drawing::Point(23, 149);
			panelInputs->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			panelInputs->Name = L"panelInputs";
			panelInputs->Size = System::Drawing::Size(478, 364);
			panelInputs->TabIndex = 43;
			// 
			// cbTax
			// 
			cbTax->FormattingEnabled = true;
			cbTax->Items->AddRange(gcnew cli::array< System::Object^  >(4) { L"23", L"8", L"oo", L"mix" });
			cbTax->Location = System::Drawing::Point(220, 166);
			cbTax->Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			cbTax->Name = L"cbTax";
			cbTax->Size = System::Drawing::Size(59, 24);
			cbTax->TabIndex = 10;
			cbTax->Text = L"23";
			// 
			// MainForm
			// 
			AutoScaleDimensions = System::Drawing::SizeF(8, 16);
			AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			AutoSize = true;
			AutoSizeMode = System::Windows::Forms::AutoSizeMode::GrowAndShrink;
			BackColor = System::Drawing::SystemColors::InactiveCaption;
			BackgroundImageLayout = System::Windows::Forms::ImageLayout::Center;
			ClientSize = System::Drawing::Size(1107, 528);
			Controls->Add(panelInputs);
			Controls->Add(panelFilename);
			Controls->Add(panelTop);
			Controls->Add(rtxtProgramOutput);
			Controls->Add(menuStrip1);
			FormBorderStyle = System::Windows::Forms::FormBorderStyle::Fixed3D;
			MainMenuStrip = menuStrip1;
			Margin = System::Windows::Forms::Padding(4, 4, 4, 4);
			Name = L"MainForm";
			StartPosition = System::Windows::Forms::FormStartPosition::CenterParent;
			Text = L"Projekt: Faktury";
			Load += gcnew System::EventHandler(this, &MainForm::MainForm_Load);
			panelTop->ResumeLayout(false);
			panelTop->PerformLayout();
			panelFilename->ResumeLayout(false);
			panelFilename->PerformLayout();
			menuStrip1->ResumeLayout(false);
			menuStrip1->PerformLayout();
			panelInputs->ResumeLayout(false);
			panelInputs->PerformLayout();
			ResumeLayout(false);
			PerformLayout();

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
			if (Controls->Find(L"rtxtOnMouseHover", true)->Length)
				rtxtOnMouseHover->Visible = false;
		}
		// TEXT INPUTS
		void txtCompany_TextChanged(System::Object^ sender, System::EventArgs^ e);
		void txtCompany_PreviewKeyDown(System::Object^ sender, System::Windows::Forms::PreviewKeyDownEventArgs^ e);
		void txtCompany_KeyPress(System::Object^ sender, System::Windows::Forms::KeyPressEventArgs^ e)
		{
			if (userSelectionMade)
				e->Handled = true;
		}
		void txtCompany_Leave(System::Object^ sender, System::EventArgs^ e)
		{
			if (rtxtDynamicOutput->Visible)
			{
				if (Globals::currShown.size() && !userSelectionMade)
					txtCompany->Text = wstrtoustr(Globals::currShown[1]);

				rtxtDynamicOutput->Visible = false;
			}
		}
		void txtInvest_TextChanged(System::Object^ sender, System::EventArgs^ e);
		void txtInvest_PreviewKeyDown(System::Object^ sender, System::Windows::Forms::PreviewKeyDownEventArgs^ e);
		void txtInvest_KeyPress(System::Object^ sender, System::Windows::Forms::KeyPressEventArgs^ e)
		{
			if (userSelectionMade)
				e->Handled = true;
		}
		void txtInvest_Leave(System::Object^ sender, System::EventArgs^ e)
		{
			if (rtxtDynamicOutput->Visible)
			{
				if (Globals::currShown.size() && !userSelectionMade)
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
				HideFvComponents();
				label1->Visible = true;
				txtNewNotFvFilename->Visible = true;
				ClearAllInputs();
				label1->Text = "Nowa nazwa pliku";
				if (chbAnotherPage->Checked)
					WriteToTextBoxNextPageName();
			}
			else
			{
				label1->Text = "Firma";
				ShowFvComponents();
				txtNewNotFvFilename->Visible = false;
			}
		}
		private: System::Void chbAnotherPage_CheckedChanged(System::Object^ sender, System::EventArgs^ e)
		{
			if (chbAnotherPage->Checked)
			{
				chbIsFv->Checked = false;
				chbIsFv->Visible = false;
				WriteToTextBoxNextPageName();
			}
			else
			{
				label1->Text = "Firma";
				chbIsFv->Visible = true;
				chbIsFv->Checked = true;
				ShowFvComponents();
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
