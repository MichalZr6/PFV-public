# PFV
Invoice Manager with Excel Database

I started this project to support my company's accounting. 

In the begining I'd scanned every document and written invoice details to XLS file. The more company grew, the more work had to be done.

The PFV tasks: 
- loading scanned files from FV folder
- reading UI files' info such as company name, invoice id, date, prices, etc.
- spliting invoice if it relates to more than one investition
- generating prices in terms of given tax
- calculating prices if user types some simple math expression
- generating merged 'database' xls file with PFV records
- renaming all scanned files to a user defined name (when it's not invoice file) or to auto-generated, based on invoice id and company name.

I've used many different programming platforms before. This time wanted to try Visual Studio.
Despite pure c++ coding in VS requires some special efforts, I continued this project.


Some important notes:
- BasicExcel.hpp is rather old, but gives the project all it needs
- PFV generates new excel file for merged old and new entries (quantity is defined in Globals.h) - it could rewrite the original file, but I find it too early
- some features are not yet implemented (i.a. main menu)

Future tasks:
- saving user input as backup every entry read and reading the backup file in case of crush or major user mistake
- adding functionality to edit chosen entry (current UI only allows user to delete last entry)
- moving defined constants from code to a new UI window, available from main menu
- implementing SQL database instead of XLS file
- implementing 'Company Storage'
