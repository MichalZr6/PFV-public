#pragma once

#include <set>
#include "FvClasses.h"
#include "FvSplit.h"

#define NEW_XLS_ENTRIES_COUNT 100	// for generating new xls file purposes;
									// defines number of entries from xls database end, where 
									// the new ones will be inserted from API
#define XLS_ROWS_FROM_END 1000		// number of entries from xls database loaded;
									// TODO: user can define this in program properties
#define MAX_DYNAMIC_SHOW 5			// how many companies/investitions found are shown in dynamic RichTextBox
#define TEXT_LEN_SHOW_ACTIVATE 1	// shows dynamic RichTextBox with found entries 
									// after typing defined amount of chars
#define MAX_FILENAME_LEN 25			// max string length of current filename, 
									// that will be displayed in the label (top panel) 
									// chars after defined amount will be sliced
#define MAX_WHOPAYED_SIZE 5			// max string length for 'who_payed' input
									// ex. PS/MZ can be the max string size

#define TEST_RUN					// uncomment for autofill inputs


enum FormState {
	STARTING = 1,
	ADDING_DELETING = 2,
	NO_MORE_LEFT = 3,
	NO_FILES_LOADED = 4,
	AFTER_SAVING = 5,
};

namespace Globals
{
	extern class FvList fv_list;
	extern std::set<ScannedFile> files;
	extern std::set<ScannedFile>::const_iterator curr_file;
	extern std::vector<std::unique_ptr<FvInfo>> vecFvFromImg;
	extern std::vector<std::unique_ptr<FvInfo>> vecSplittedFvs;
	extern std::map<unsigned short int, std::wstring> currShown;
	extern std::unique_ptr<FvSplit> fvSplitter;

	void SearchCompany(const std::wstring &name, 
			std::unordered_set<std::wstring> &comp_set);
	void SearchInvestition(const std::wstring &name, 
			std::unordered_set<std::wstring> &inv_set);
}