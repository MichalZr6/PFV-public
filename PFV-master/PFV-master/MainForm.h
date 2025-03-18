#pragma once

#include <locale.h>
#include <algorithm>
#include <iterator>
#include "../../myIncludes/Functions.h"
#include "../../myIncludes/BasicExcel.hpp"
#include "../../myIncludes/Price.h"
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
		void StringsToOutput(const std::wstring &search, 
						const std::unordered_set<std::wstring> &sset);
		void PrevCompInvKeyDown(System::Object^  sender, 
			System::Windows::Forms::PreviewKeyDownEventArgs^  e);

		void LoadRawFiles(void);
		void AskForPath(void);
		void LoadXLSRecords(void);
		void SetCurrYearMon(void);

		void ManageForm(FormState state);
		void CheckActFile(void);
		void SetFvInfoFromInputs(std::unique_ptr<FvInfo> &fv);
		void ClearAllInputs(void);
		void HideFvComponents(void);
		void ShowFvComponents(void);
		bool CanSplitBtnBeEnabled(std::set<ScannedFile>::const_iterator curr);

		void UpdateProgramOutput(FormState state);
		void RawFilenames_ToOutput(void);
		void SummaryFromXLS_ToOutput(void);
		void FvFiles_ToOutput(void);
		
		bool NewFvAdd(void);
		void CheckForDuplicates(const std::unique_ptr<FvInfo> &fv);	
		//throws if there are duplicates: in program input or in data loaded from xls file
		bool NewNonFvAdd(void);
		bool AnotherPageAdd(void);

		bool PromptForSaving(void);
		void SaveToFile(void);
		void RenameAllFiles(void);

		void ResetFilenameLabel(void);
		void InitOnMouseHoverTextBox(void);
		std::wstring TrimLongFileName(const std::wstring &fname);

		// Debugging
		void FillInForTests(void);

		// Variables
		bool numberKeyPressed = false;
		System::String ^warnings;
		System::Drawing::Size cached_panel_size;
		System::Drawing::Size cached_programOutput_size;

	private: System::Windows::Forms::MenuStrip^  menuStrip1;
	private: System::Windows::Forms::ToolStripMenuItem^  miProperties;
	private: System::Windows::Forms::ToolStripMenuItem^  wykonajAkcj�ToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  dodajToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  usu�OstatniWpisToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  podzielOstatniaFaktur�ToolStripMenuItem;
	private: System::Windows::Forms::ToolStripSeparator^  toolStripSeparator3;
	private: System::Windows::Forms::ToolStripMenuItem^  toolStripMenuItem1;
	private: System::Windows::Forms::ToolStripMenuItem^  zapiszDotychczasoweDaneDoPlikuxlsToolStripMenuItem;
	private: System::Windows::Forms::ToolStripSeparator^  toolStripSeparator2;
	private: System::Windows::Forms::ToolStripMenuItem^  generujTekstDoSaldeoToolStripMenuItem;
	private: System::Windows::Forms::ToolStripSeparator^  toolStripSeparator1;
	private: System::Windows::Forms::ToolStripMenuItem^  zamknijProgramToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  ukryjPanelG�rnyToolStripMenuItem;
	private: System::Windows::Forms::ToolStripMenuItem^  ukryjKomunikatyProgramuToolStripMenuItem;
	private: System::Windows::Forms::Label^  lblTax;

	private: System::Windows::Forms::Panel^  panelInputs;
	private: System::Windows::Forms::ComboBox^  cbTax;

	private: System::Windows::Forms::ToolStripMenuItem^  miHelp;

	protected:
		/// <summary>
		/// Wyczy�� wszystkie u�ywane zasoby.
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
	private: System::Windows::Forms::Label^  lblComments;
	private: System::Windows::Forms::TextBox^  txtComments;
	private: System::Windows::Forms::CheckBox^  chbAnotherPage;
	private: System::Windows::Forms::RichTextBox^ rtxtDynamicOutput;
	private: System::Windows::Forms::Panel^  panelFilename;
	private: System::Windows::Forms::Label^  label12;
	private: System::Windows::Forms::TextBox^  txtDescr;
	private: System::Windows::Forms::RichTextBox^ rtxtOnMouseHover;
	private: System::Windows::Forms::Form ^split_fv_form;
	private: System::Windows::Forms::Button^  btnDeleteLast;
	private: System::Windows::Forms::Button^  btnExit;
	private: System::Windows::Forms::CheckBox^  chbIsFv;
	private: System::Windows::Forms::Label^  lblCurrFileStatic;

	private: System::Windows::Forms::Label^  lblCurrentFile;
	private: System::Windows::Forms::TextBox^  txtNewNotFvFilename;
	private: System::Windows::Forms::Label^  label14;
	private: System::Windows::Forms::TextBox^  txtPayment;
	private: System::Windows::Forms::Label^  label15;
	private: System::Windows::Forms::TextBox^  txtWhoPayed;
	private: System::Windows::Forms::Button^  btnSaldeo;
	private: System::Windows::Forms::FolderBrowserDialog^  folderBrowser;

	private: System::Windows::Forms::Button^  btnAdd;
	private: System::Windows::Forms::Label^  label1;
	private: System::Windows::Forms::TextBox^  txtCompany;
	private: System::Windows::Forms::TextBox^  txtFvIdent;
	private: System::Windows::Forms::Label^  label2;
	private: System::Windows::Forms::Label^  label3;
	private: System::Windows::Forms::TextBox^  txtDay;
	private: System::Windows::Forms::TextBox^  txtMonth;
	private: System::Windows::Forms::TextBox^  txtYear;
	private: System::Windows::Forms::Label^  label4;
	private: System::Windows::Forms::TextBox^  txtInvest;
	private: System::Windows::Forms::RichTextBox^  rtxtProgramOutput;


	private: System::Windows::Forms::Button^  btnSplit;
	private: System::Windows::Forms::Label^  label5;
	private: System::Windows::Forms::TextBox^  txtNetVal;
	private: System::Windows::Forms::Label^  label6;
	private: System::Windows::Forms::TextBox^  txtGrossVal;
	private: System::Windows::Forms::Panel^  panelTop;

	private: System::Windows::Forms::TextBox^  txtFvListOutFilename;
	private: System::Windows::Forms::Label^  label8;
	private: System::Windows::Forms::TextBox^  txtFvListFilename;
	private: System::Windows::Forms::Label^  label7;
	private: System::Windows::Forms::TextBox^  txtFvDir;
	private: System::Windows::Forms::Label^  label9;
	private: System::Windows::Forms::Label^  label10;
	private: System::Windows::Forms::Label^  label11;

	protected:

	private:
		/// <summary>
		/// Wymagana zmienna projektanta.
		/// </summary>
		System::ComponentModel::Container ^components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Metoda wymagana do obs�ugi projektanta � nie nale�y modyfikowa�
		/// jej zawarto�ci w edytorze kodu.
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
			this->wykonajAkcj�ToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->dodajToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->usu�OstatniWpisToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->podzielOstatniaFaktur�ToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->toolStripSeparator3 = (gcnew System::Windows::Forms::ToolStripSeparator());
			this->toolStripMenuItem1 = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->zapiszDotychczasoweDaneDoPlikuxlsToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->toolStripSeparator2 = (gcnew System::Windows::Forms::ToolStripSeparator());
			this->generujTekstDoSaldeoToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->toolStripSeparator1 = (gcnew System::Windows::Forms::ToolStripSeparator());
			this->zamknijProgramToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->miProperties = (gcnew System::Windows::Forms::ToolStripMenuItem());
			this->ukryjPanelG�rnyToolStripMenuItem = (gcnew System::Windows::Forms::ToolStripMenuItem());
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
			this->btnAdd->Location = System::Drawing::Point(6, 223);
			this->btnAdd->Name = L"btnAdd";
			this->btnAdd->Size = System::Drawing::Size(106, 23);
			this->btnAdd->TabIndex = 15;
			this->btnAdd->Text = L"Do&daj";
			this->btnAdd->UseVisualStyleBackColor = true;
			this->btnAdd->Click += gcnew System::EventHandler(this, &MainForm::btnAdd_Click);
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(3, 9);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(32, 13);
			this->label1->TabIndex = 1;
			this->label1->Text = L"Firma";
			// 
			// txtCompany
			// 
			this->txtCompany->Location = System::Drawing::Point(67, 6);
			this->txtCompany->MaxLength = 40;
			this->txtCompany->Name = L"txtCompany";
			this->txtCompany->Size = System::Drawing::Size(276, 20);
			this->txtCompany->TabIndex = 2;
			this->txtCompany->TextChanged += gcnew System::EventHandler(this, &MainForm::txtCompany_TextChanged);
			this->txtCompany->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &MainForm::txtCompany_KeyPress);
			this->txtCompany->Leave += gcnew System::EventHandler(this, &MainForm::txtCompany_Leave);
			this->txtCompany->PreviewKeyDown += gcnew System::Windows::Forms::PreviewKeyDownEventHandler(this, &MainForm::txtCompany_PreviewKeyDown);
			// 
			// txtFvIdent
			// 
			this->txtFvIdent->Location = System::Drawing::Point(67, 32);
			this->txtFvIdent->MaxLength = 30;
			this->txtFvIdent->Name = L"txtFvIdent";
			this->txtFvIdent->Size = System::Drawing::Size(276, 20);
			this->txtFvIdent->TabIndex = 3;
			// 
			// label2
			// 
			this->label2->AutoSize = true;
			this->label2->Location = System::Drawing::Point(3, 39);
			this->label2->Name = L"label2";
			this->label2->Size = System::Drawing::Size(53, 13);
			this->label2->TabIndex = 4;
			this->label2->Text = L"Nr faktury";
			// 
			// label3
			// 
			this->label3->AutoSize = true;
			this->label3->Location = System::Drawing::Point(3, 116);
			this->label3->Name = L"label3";
			this->label3->Size = System::Drawing::Size(30, 13);
			this->label3->TabIndex = 6;
			this->label3->Text = L"Data";
			// 
			// txtDay
			// 
			this->txtDay->Location = System::Drawing::Point(67, 109);
			this->txtDay->MaxLength = 2;
			this->txtDay->Name = L"txtDay";
			this->txtDay->Size = System::Drawing::Size(25, 20);
			this->txtDay->TabIndex = 6;
			// 
			// txtMonth
			// 
			this->txtMonth->Location = System::Drawing::Point(116, 108);
			this->txtMonth->MaxLength = 2;
			this->txtMonth->Name = L"txtMonth";
			this->txtMonth->Size = System::Drawing::Size(25, 20);
			this->txtMonth->TabIndex = 7;
			// 
			// txtYear
			// 
			this->txtYear->Location = System::Drawing::Point(165, 109);
			this->txtYear->MaxLength = 4;
			this->txtYear->Name = L"txtYear";
			this->txtYear->Size = System::Drawing::Size(52, 20);
			this->txtYear->TabIndex = 8;
			this->txtYear->TabStop = false;
			// 
			// label4
			// 
			this->label4->AutoSize = true;
			this->label4->Location = System::Drawing::Point(3, 65);
			this->label4->Name = L"label4";
			this->label4->Size = System::Drawing::Size(57, 13);
			this->label4->TabIndex = 10;
			this->label4->Text = L"Inwestycja";
			// 
			// txtInvest
			// 
			this->txtInvest->Location = System::Drawing::Point(67, 57);
			this->txtInvest->MaxLength = 30;
			this->txtInvest->Name = L"txtInvest";
			this->txtInvest->Size = System::Drawing::Size(276, 20);
			this->txtInvest->TabIndex = 4;
			this->txtInvest->TextChanged += gcnew System::EventHandler(this, &MainForm::txtInvest_TextChanged);
			this->txtInvest->KeyPress += gcnew System::Windows::Forms::KeyPressEventHandler(this, &MainForm::txtInvest_KeyPress);
			this->txtInvest->Leave += gcnew System::EventHandler(this, &MainForm::txtInvest_Leave);
			this->txtInvest->PreviewKeyDown += gcnew System::Windows::Forms::PreviewKeyDownEventHandler(this, &MainForm::txtInvest_PreviewKeyDown);
			// 
			// rtxtProgramOutput
			// 
			this->rtxtProgramOutput->Location = System::Drawing::Point(382, 87);
			this->rtxtProgramOutput->Name = L"rtxtProgramOutput";
			this->rtxtProgramOutput->ReadOnly = true;
			this->rtxtProgramOutput->Size = System::Drawing::Size(448, 330);
			this->rtxtProgramOutput->TabIndex = 11;
			this->rtxtProgramOutput->TabStop = false;
			this->rtxtProgramOutput->Text = L"";
			// 
			// btnSplit
			// 
			this->btnSplit->Enabled = false;
			this->btnSplit->Location = System::Drawing::Point(118, 223);
			this->btnSplit->Name = L"btnSplit";
			this->btnSplit->Size = System::Drawing::Size(225, 23);
			this->btnSplit->TabIndex = 16;
			this->btnSplit->Text = L"Podziel ostatni� dodan� faktur� na cz�ci";
			this->btnSplit->UseVisualStyleBackColor = true;
			this->btnSplit->Click += gcnew System::EventHandler(this, &MainForm::btnSplit_Click);
			// 
			// label5
			// 
			this->label5->AutoSize = true;
			this->label5->Location = System::Drawing::Point(3, 142);
			this->label5->Name = L"label5";
			this->label5->Size = System::Drawing::Size(60, 13);
			this->label5->TabIndex = 16;
			this->label5->Text = L"Wart. netto";
			// 
			// txtNetVal
			// 
			this->txtNetVal->Location = System::Drawing::Point(67, 135);
			this->txtNetVal->MaxLength = 30;
			this->txtNetVal->Name = L"txtNetVal";
			this->txtNetVal->Size = System::Drawing::Size(60, 20);
			this->txtNetVal->TabIndex = 9;
			this->txtNetVal->Enter += gcnew System::EventHandler(this, &MainForm::txtNetVal_Enter);
			this->txtNetVal->Leave += gcnew System::EventHandler(this, &MainForm::txtNetVal_Leave);
			// 
			// label6
			// 
			this->label6->AutoSize = true;
			this->label6->Location = System::Drawing::Point(221, 138);
			this->label6->Name = L"label6";
			this->label6->Size = System::Drawing::Size(35, 13);
			this->label6->TabIndex = 18;
			this->label6->Text = L"Brutto";
			// 
			// txtGrossVal
			// 
			this->txtGrossVal->Location = System::Drawing::Point(262, 133);
			this->txtGrossVal->MaxLength = 30;
			this->txtGrossVal->Name = L"txtGrossVal";
			this->txtGrossVal->Size = System::Drawing::Size(81, 20);
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
			this->panelTop->Location = System::Drawing::Point(17, 37);
			this->panelTop->Name = L"panelTop";
			this->panelTop->Size = System::Drawing::Size(813, 40);
			this->panelTop->TabIndex = 19;
			// 
			// txtFvDir
			// 
			this->txtFvDir->Location = System::Drawing::Point(649, 9);
			this->txtFvDir->Name = L"txtFvDir";
			this->txtFvDir->Size = System::Drawing::Size(142, 20);
			this->txtFvDir->TabIndex = 25;
			this->txtFvDir->TabStop = false;
			this->txtFvDir->Text = L"Fv/";
			// 
			// label9
			// 
			this->label9->AutoSize = true;
			this->label9->Location = System::Drawing::Point(533, 12);
			this->label9->Name = L"label9";
			this->label9->Size = System::Drawing::Size(110, 13);
			this->label9->TabIndex = 24;
			this->label9->Text = L"�cie�ka folderu faktur";
			// 
			// txtFvListOutFilename
			// 
			this->txtFvListOutFilename->Location = System::Drawing::Point(385, 9);
			this->txtFvListOutFilename->Name = L"txtFvListOutFilename";
			this->txtFvListOutFilename->Size = System::Drawing::Size(142, 20);
			this->txtFvListOutFilename->TabIndex = 23;
			this->txtFvListOutFilename->TabStop = false;
			this->txtFvListOutFilename->Text = L"Zestawienie Faktur_out.xls";
			// 
			// label8
			// 
			this->label8->AutoSize = true;
			this->label8->Location = System::Drawing::Point(235, 12);
			this->label8->Name = L"label8";
			this->label8->Size = System::Drawing::Size(144, 13);
			this->label8->TabIndex = 22;
			this->label8->Text = L"Plik zestawienia wynikowego";
			// 
			// txtFvListFilename
			// 
			this->txtFvListFilename->Location = System::Drawing::Point(91, 9);
			this->txtFvListFilename->Name = L"txtFvListFilename";
			this->txtFvListFilename->Size = System::Drawing::Size(138, 20);
			this->txtFvListFilename->TabIndex = 21;
			this->txtFvListFilename->TabStop = false;
			this->txtFvListFilename->Text = L"Zestawienie Faktur.xls";
			// 
			// label7
			// 
			this->label7->AutoSize = true;
			this->label7->Location = System::Drawing::Point(3, 12);
			this->label7->Name = L"label7";
			this->label7->Size = System::Drawing::Size(82, 13);
			this->label7->TabIndex = 20;
			this->label7->Text = L"Plik zestawienia";
			// 
			// label10
			// 
			this->label10->AutoSize = true;
			this->label10->Location = System::Drawing::Point(98, 112);
			this->label10->Name = L"label10";
			this->label10->Size = System::Drawing::Size(12, 13);
			this->label10->TabIndex = 20;
			this->label10->Text = L"/";
			// 
			// label11
			// 
			this->label11->AutoSize = true;
			this->label11->Location = System::Drawing::Point(147, 112);
			this->label11->Name = L"label11";
			this->label11->Size = System::Drawing::Size(12, 13);
			this->label11->TabIndex = 21;
			this->label11->Text = L"/";
			// 
			// label12
			// 
			this->label12->AutoSize = true;
			this->label12->Location = System::Drawing::Point(3, 90);
			this->label12->Name = L"label12";
			this->label12->Size = System::Drawing::Size(28, 13);
			this->label12->TabIndex = 28;
			this->label12->Text = L"Opis";
			// 
			// txtDescr
			// 
			this->txtDescr->Location = System::Drawing::Point(67, 83);
			this->txtDescr->MaxLength = 40;
			this->txtDescr->Name = L"txtDescr";
			this->txtDescr->Size = System::Drawing::Size(276, 20);
			this->txtDescr->TabIndex = 5;
			// 
			// btnDeleteLast
			// 
			this->btnDeleteLast->Location = System::Drawing::Point(6, 252);
			this->btnDeleteLast->Name = L"btnDeleteLast";
			this->btnDeleteLast->Size = System::Drawing::Size(106, 23);
			this->btnDeleteLast->TabIndex = 17;
			this->btnDeleteLast->Text = L"Usu� ostatni wpis";
			this->btnDeleteLast->UseVisualStyleBackColor = true;
			this->btnDeleteLast->Click += gcnew System::EventHandler(this, &MainForm::btnDeleteLast_Click);
			// 
			// btnExit
			// 
			this->btnExit->Location = System::Drawing::Point(260, 252);
			this->btnExit->Name = L"btnExit";
			this->btnExit->Size = System::Drawing::Size(83, 23);
			this->btnExit->TabIndex = 19;
			this->btnExit->Text = L"&Wyjd�";
			this->btnExit->UseVisualStyleBackColor = true;
			this->btnExit->Click += gcnew System::EventHandler(this, &MainForm::btnExit_Click);
			// 
			// chbIsFv
			// 
			this->chbIsFv->AutoSize = true;
			this->chbIsFv->Checked = true;
			this->chbIsFv->CheckState = System::Windows::Forms::CheckState::Checked;
			this->chbIsFv->Location = System::Drawing::Point(6, 21);
			this->chbIsFv->Name = L"chbIsFv";
			this->chbIsFv->Size = System::Drawing::Size(83, 17);
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
			this->lblCurrFileStatic->Location = System::Drawing::Point(3, 3);
			this->lblCurrFileStatic->Name = L"lblCurrFileStatic";
			this->lblCurrFileStatic->Size = System::Drawing::Size(70, 13);
			this->lblCurrFileStatic->TabIndex = 32;
			this->lblCurrFileStatic->Text = L"Aktualny plik:";
			// 
			// lblCurrentFile
			// 
			this->lblCurrentFile->AutoSize = true;
			this->lblCurrentFile->Location = System::Drawing::Point(89, 3);
			this->lblCurrentFile->Name = L"lblCurrentFile";
			this->lblCurrentFile->Size = System::Drawing::Size(0, 13);
			this->lblCurrentFile->TabIndex = 33;
			this->lblCurrentFile->MouseLeave += gcnew System::EventHandler(this, &MainForm::lblCurrentFile_MouseLeave);
			this->lblCurrentFile->MouseHover += gcnew System::EventHandler(this, &MainForm::lblCurrentFile_MouseHover);
			// 
			// txtNewNotFvFilename
			// 
			this->txtNewNotFvFilename->Location = System::Drawing::Point(125, 6);
			this->txtNewNotFvFilename->Name = L"txtNewNotFvFilename";
			this->txtNewNotFvFilename->Size = System::Drawing::Size(218, 20);
			this->txtNewNotFvFilename->TabIndex = 2;
			this->txtNewNotFvFilename->Visible = false;
			// 
			// label14
			// 
			this->label14->AutoSize = true;
			this->label14->Location = System::Drawing::Point(165, 166);
			this->label14->Name = L"label14";
			this->label14->Size = System::Drawing::Size(87, 13);
			this->label14->TabIndex = 37;
			this->label14->Text = L"P�atno��/Termin";
			// 
			// txtPayment
			// 
			this->txtPayment->Location = System::Drawing::Point(258, 159);
			this->txtPayment->MaxLength = 20;
			this->txtPayment->Name = L"txtPayment";
			this->txtPayment->Size = System::Drawing::Size(85, 20);
			this->txtPayment->TabIndex = 13;
			// 
			// label15
			// 
			this->label15->AutoSize = true;
			this->label15->Location = System::Drawing::Point(3, 168);
			this->label15->Name = L"label15";
			this->label15->Size = System::Drawing::Size(36, 13);
			this->label15->TabIndex = 36;
			this->label15->Text = L"P�aci�";
			// 
			// txtWhoPayed
			// 
			this->txtWhoPayed->Location = System::Drawing::Point(67, 163);
			this->txtWhoPayed->MaxLength = 10;
			this->txtWhoPayed->Name = L"txtWhoPayed";
			this->txtWhoPayed->Size = System::Drawing::Size(60, 20);
			this->txtWhoPayed->TabIndex = 12;
			// 
			// btnSaldeo
			// 
			this->btnSaldeo->Location = System::Drawing::Point(118, 252);
			this->btnSaldeo->Name = L"btnSaldeo";
			this->btnSaldeo->Size = System::Drawing::Size(75, 23);
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
			this->panelFilename->Location = System::Drawing::Point(17, 76);
			this->panelFilename->Name = L"panelFilename";
			this->panelFilename->RightToLeft = System::Windows::Forms::RightToLeft::No;
			this->panelFilename->Size = System::Drawing::Size(359, 49);
			this->panelFilename->TabIndex = 39;
			// 
			// chbAnotherPage
			// 
			this->chbAnotherPage->AutoSize = true;
			this->chbAnotherPage->Location = System::Drawing::Point(111, 21);
			this->chbAnotherPage->Name = L"chbAnotherPage";
			this->chbAnotherPage->Size = System::Drawing::Size(149, 17);
			this->chbAnotherPage->TabIndex = 34;
			this->chbAnotherPage->Text = L"kolejna strona poprz. pliku";
			this->chbAnotherPage->UseVisualStyleBackColor = true;
			// 
			// lblComments
			// 
			this->lblComments->AutoSize = true;
			this->lblComments->Location = System::Drawing::Point(3, 195);
			this->lblComments->Name = L"lblComments";
			this->lblComments->Size = System::Drawing::Size(57, 13);
			this->lblComments->TabIndex = 40;
			this->lblComments->Text = L"Komentarz";
			// 
			// txtComments
			// 
			this->txtComments->Location = System::Drawing::Point(67, 188);
			this->txtComments->MaxLength = 40;
			this->txtComments->Name = L"txtComments";
			this->txtComments->Size = System::Drawing::Size(276, 20);
			this->txtComments->TabIndex = 14;
			// 
			// menuStrip1
			// 
			this->menuStrip1->Items->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(3) {
				this->wykonajAkcj�ToolStripMenuItem,
					this->miProperties, this->miHelp
			});
			this->menuStrip1->Location = System::Drawing::Point(0, 0);
			this->menuStrip1->Name = L"menuStrip1";
			this->menuStrip1->Size = System::Drawing::Size(830, 24);
			this->menuStrip1->TabIndex = 41;
			this->menuStrip1->Text = L"menuStrip1";
			// 
			// wykonajAkcj�ToolStripMenuItem
			// 
			this->wykonajAkcj�ToolStripMenuItem->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(10) {
				this->dodajToolStripMenuItem,
					this->usu�OstatniWpisToolStripMenuItem, this->podzielOstatniaFaktur�ToolStripMenuItem, this->toolStripSeparator3, this->toolStripMenuItem1,
					this->zapiszDotychczasoweDaneDoPlikuxlsToolStripMenuItem, this->toolStripSeparator2, this->generujTekstDoSaldeoToolStripMenuItem,
					this->toolStripSeparator1, this->zamknijProgramToolStripMenuItem
			});
			this->wykonajAkcj�ToolStripMenuItem->Name = L"wykonajAkcj�ToolStripMenuItem";
			this->wykonajAkcj�ToolStripMenuItem->Size = System::Drawing::Size(95, 20);
			this->wykonajAkcj�ToolStripMenuItem->Text = L"Wykonaj akcj�";
			// 
			// dodajToolStripMenuItem
			// 
			this->dodajToolStripMenuItem->Name = L"dodajToolStripMenuItem";
			this->dodajToolStripMenuItem->Size = System::Drawing::Size(285, 22);
			this->dodajToolStripMenuItem->Text = L"Dodaj";
			// 
			// usu�OstatniWpisToolStripMenuItem
			// 
			this->usu�OstatniWpisToolStripMenuItem->Name = L"usu�OstatniWpisToolStripMenuItem";
			this->usu�OstatniWpisToolStripMenuItem->Size = System::Drawing::Size(285, 22);
			this->usu�OstatniWpisToolStripMenuItem->Text = L"Usu� ostatni wpis";
			// 
			// podzielOstatniaFaktur�ToolStripMenuItem
			// 
			this->podzielOstatniaFaktur�ToolStripMenuItem->Name = L"podzielOstatniaFaktur�ToolStripMenuItem";
			this->podzielOstatniaFaktur�ToolStripMenuItem->Size = System::Drawing::Size(285, 22);
			this->podzielOstatniaFaktur�ToolStripMenuItem->Text = L"Podziel ostatni� faktur�";
			// 
			// toolStripSeparator3
			// 
			this->toolStripSeparator3->Name = L"toolStripSeparator3";
			this->toolStripSeparator3->Size = System::Drawing::Size(282, 6);
			// 
			// toolStripMenuItem1
			// 
			this->toolStripMenuItem1->Name = L"toolStripMenuItem1";
			this->toolStripMenuItem1->Size = System::Drawing::Size(285, 22);
			this->toolStripMenuItem1->Text = L"Ukryj komunikaty programu";
			// 
			// zapiszDotychczasoweDaneDoPlikuxlsToolStripMenuItem
			// 
			this->zapiszDotychczasoweDaneDoPlikuxlsToolStripMenuItem->Name = L"zapiszDotychczasoweDaneDoPlikuxlsToolStripMenuItem";
			this->zapiszDotychczasoweDaneDoPlikuxlsToolStripMenuItem->Size = System::Drawing::Size(285, 22);
			this->zapiszDotychczasoweDaneDoPlikuxlsToolStripMenuItem->Text = L"Zapisz dotychczasowe dane do pliku .xls";
			// 
			// toolStripSeparator2
			// 
			this->toolStripSeparator2->Name = L"toolStripSeparator2";
			this->toolStripSeparator2->Size = System::Drawing::Size(282, 6);
			// 
			// generujTekstDoSaldeoToolStripMenuItem
			// 
			this->generujTekstDoSaldeoToolStripMenuItem->Name = L"generujTekstDoSaldeoToolStripMenuItem";
			this->generujTekstDoSaldeoToolStripMenuItem->Size = System::Drawing::Size(285, 22);
			this->generujTekstDoSaldeoToolStripMenuItem->Text = L"Generuj tekst do Saldeo";
			// 
			// toolStripSeparator1
			// 
			this->toolStripSeparator1->Name = L"toolStripSeparator1";
			this->toolStripSeparator1->Size = System::Drawing::Size(282, 6);
			// 
			// zamknijProgramToolStripMenuItem
			// 
			this->zamknijProgramToolStripMenuItem->Name = L"zamknijProgramToolStripMenuItem";
			this->zamknijProgramToolStripMenuItem->Size = System::Drawing::Size(285, 22);
			this->zamknijProgramToolStripMenuItem->Text = L"Zamknij program";
			// 
			// miProperties
			// 
			this->miProperties->DropDownItems->AddRange(gcnew cli::array< System::Windows::Forms::ToolStripItem^  >(2) {
				this->ukryjPanelG�rnyToolStripMenuItem,
					this->ukryjKomunikatyProgramuToolStripMenuItem
			});
			this->miProperties->Name = L"miProperties";
			this->miProperties->Size = System::Drawing::Size(50, 20);
			this->miProperties->Text = L"Opcje";
			// 
			// ukryjPanelG�rnyToolStripMenuItem
			// 
			this->ukryjPanelG�rnyToolStripMenuItem->CheckOnClick = true;
			this->ukryjPanelG�rnyToolStripMenuItem->Name = L"ukryjPanelG�rnyToolStripMenuItem";
			this->ukryjPanelG�rnyToolStripMenuItem->Size = System::Drawing::Size(223, 22);
			this->ukryjPanelG�rnyToolStripMenuItem->Text = L"Ukryj panel g�rny";
			this->ukryjPanelG�rnyToolStripMenuItem->CheckedChanged += gcnew System::EventHandler(this, &MainForm::ukryjPanelG�rnyToolStripMenuItem_CheckedChanged);
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
			this->lblTax->Location = System::Drawing::Point(133, 138);
			this->lblTax->Name = L"lblTax";
			this->lblTax->Size = System::Drawing::Size(28, 13);
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
			this->panelInputs->Location = System::Drawing::Point(17, 121);
			this->panelInputs->Name = L"panelInputs";
			this->panelInputs->Size = System::Drawing::Size(359, 296);
			this->panelInputs->TabIndex = 43;
			// 
			// cbTax
			// 
			this->cbTax->FormattingEnabled = true;
			this->cbTax->Items->AddRange(gcnew cli::array< System::Object^  >(4) { L"23", L"8", L"oo", L"mix" });
			this->cbTax->Location = System::Drawing::Point(165, 135);
			this->cbTax->Name = L"cbTax";
			this->cbTax->Size = System::Drawing::Size(45, 21);
			this->cbTax->TabIndex = 10;
			this->cbTax->Text = L"23";
			// 
			// MainForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->AutoSize = true;
			this->AutoSizeMode = System::Windows::Forms::AutoSizeMode::GrowAndShrink;
			this->BackColor = System::Drawing::SystemColors::InactiveCaption;
			this->BackgroundImageLayout = System::Windows::Forms::ImageLayout::Center;
			this->ClientSize = System::Drawing::Size(830, 429);
			this->Controls->Add(this->panelInputs);
			this->Controls->Add(this->panelFilename);
			this->Controls->Add(this->panelTop);
			this->Controls->Add(this->rtxtProgramOutput);
			this->Controls->Add(this->menuStrip1);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::Fixed3D;
			this->MainMenuStrip = this->menuStrip1;
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
	void btnAdd_Click(System::Object^  sender, System::EventArgs^  e);
	void btnSplit_Click(System::Object^  sender, System::EventArgs^  e);
	void btnDeleteLast_Click(System::Object^  sender, System::EventArgs^  e);
	void btnSaldeo_Click(System::Object^  sender, System::EventArgs^  e);
	void btnExit_Click(System::Object^  sender, System::EventArgs^  e)
	{
		if (!Globals::vecFvFromImg.empty())
		{
			auto result = MessageBox::Show("Czy chcesz zachowa� dotychczas wprowadzone dane o fakturach ?",
				"Niezapisane dane", MessageBoxButtons::YesNoCancel);
			if (result == System::Windows::Forms::DialogResult::Yes)
				// TODO: save current input
				return;
		}
		
		Application::Exit();
	}
		// FORM and OTHER Controls
	void MainForm_Load(System::Object^  sender, System::EventArgs^  e);
	void lblCurrentFile_MouseHover(System::Object^  sender, System::EventArgs^  e);
	void lblCurrentFile_MouseLeave(System::Object^  sender, System::EventArgs^  e)
	{
		if (this->Controls->Find(L"rtxtOnMouseHover", true)->Length)
			this->rtxtOnMouseHover->Visible = false;
	}
		// TEXT INPUTS
	void txtCompany_TextChanged(System::Object^  sender, System::EventArgs^  e);
	void txtCompany_PreviewKeyDown(System::Object^  sender, System::Windows::Forms::PreviewKeyDownEventArgs^  e);
	void txtCompany_KeyPress(System::Object^  sender, System::Windows::Forms::KeyPressEventArgs^  e) 
	{
		if (this->numberKeyPressed)
			e->Handled = true;
	}
	void txtCompany_Leave(System::Object^  sender, System::EventArgs^  e) 
	{
		if (rtxtDynamicOutput->Visible)
		{
			if (Globals::currShown.size() && !numberKeyPressed)
				txtCompany->Text = wstrtoustr(Globals::currShown[1]);

			rtxtDynamicOutput->Visible = false;
		}
	}
	void txtInvest_TextChanged(System::Object^  sender, System::EventArgs^  e);
	void txtInvest_PreviewKeyDown(System::Object^  sender, System::Windows::Forms::PreviewKeyDownEventArgs^  e);
	void txtInvest_KeyPress(System::Object^  sender, System::Windows::Forms::KeyPressEventArgs^  e) 
	{
		if (this->numberKeyPressed)
			e->Handled = true;
	}
	void txtInvest_Leave(System::Object^  sender, System::EventArgs^  e) 
	{
		if (rtxtDynamicOutput->Visible)
		{
			if (Globals::currShown.size() && !numberKeyPressed)
				txtInvest->Text = wstrtoustr(Globals::currShown[1]);

			rtxtDynamicOutput->Visible = false;
		}
	}
	void txtGrossVal_Enter(System::Object^  sender, System::EventArgs^  e)
	{
		if (cbTax->Text != "mix")
			AutoFillOtherPriceTBox(txtNetVal, txtGrossVal, GetTaxFromCBox(cbTax));
	}
	void txtNetVal_Enter(System::Object^  sender, System::EventArgs^  e)
	{
		if (cbTax->Text != "mix")
			AutoFillOtherPriceTBox(txtGrossVal, txtNetVal, GetTaxFromCBox(cbTax));
	}
	void txtNetVal_Leave(System::Object^  sender, System::EventArgs^  e)
	{
		//txtNetVal->Text = EvaluateExpr(txtNetVal->Text);
	}
	void txtGrossVal_Leave(System::Object^  sender, System::EventArgs^  e)
	{
		if (cbTax->Text != "mix")
			AutoFillOtherPriceTBox(txtGrossVal, txtNetVal, GetTaxFromCBox(cbTax));
	}
		// CHECKBOXES
	void chbIsFv_Enter(System::Object^  sender, System::EventArgs^  e) 
	{
		//chbIsFv->BackColor = System::Drawing::Color::YellowGreen;
		chbIsFv->Font = gcnew System::Drawing::Font("Microsoft Sans Serif", 7.6f, FontStyle::Bold);
		lblCurrentFile->Font = gcnew System::Drawing::Font("Microsoft Sans Serif", 7.6f, FontStyle::Bold);
	}
	void chbIsFv_Leave(System::Object^  sender, System::EventArgs^  e) 
	{
		//chbIsFv->ResetBackColor();
		chbIsFv->Font = gcnew System::Drawing::Font("Microsoft Sans Serif", 8.25f, FontStyle::Regular);
		lblCurrentFile->Font = gcnew System::Drawing::Font("Microsoft Sans Serif", 7.6f, FontStyle::Regular);
	}
	void chbIsFv_CheckedChanged(System::Object^  sender, System::EventArgs^  e) 
	{
		if (!chbIsFv->Checked)
		{
			this->ClearAllInputs();
			label1->Text = "Nowa nazwa pliku";
			txtNewNotFvFilename->Visible = true;
			this->HideFvComponents();
		}
		else
		{
			label1->Text = "Firma";
			txtNewNotFvFilename->Visible = false;
			this->ShowFvComponents();
		}
	}
		// MENU Items
	void wyjd�ToolStripMenuItem_Click(System::Object^  sender, System::EventArgs^  e) 
	{
		btnExit_Click(sender, e);
	}
	void ukryjPanelG�rnyToolStripMenuItem_CheckedChanged(System::Object^  sender, System::EventArgs^  e) 
	{
		if (ukryjPanelG�rnyToolStripMenuItem->Checked)
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
	void ukryjKomunikatyProgramuToolStripMenuItem_CheckedChanged(System::Object^  sender, System::EventArgs^  e) 
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
