#include <iostream>
#include <string>
#include <mysql.h>
#include <iomanip>
#include <conio.h>
#include <string.h>
#include <sstream>
#include <regex>
#include <chrono>
#pragma warning(disable : 4996)
using namespace std;

class BookStore
{
    public:

	void mainmenu();
	void booksellerlogin();
	void customerlogin();
	void booksellermenu();
	void interfaceCustomer();
	void customermenu();
	void getdetail();
	void addbook();
	void viewbookBS();
	void viewbookC();
	void searchbookBS();
	void deletebook();
	void modifybook();
	void purchasebook();
	void showreport();
	bool Email_check(string);
	bool isValid(string);
	void viewInvoice();
	bool check_number(string[]);

	string BooksellerID, BookID;
	string BooksellerUsername;
	string CustomerUsername, CustomerPhoneNumber, CustomerAddress, CustomerEmail;
	string CustomerID;
	string j, k;

	string PurchaseDate;
	double Totalprice;
	string price;
	int UpdateQuantity;
	string CurrentQuantity;
	string choose;
	string BookName, BookType;

	bool check_number(string str) {
		for (int i = 0; i < str.length(); i++)
			if (isdigit(str[i]) == false)
			{
				if (str[i] == '.')
					return true;
				else
					return false;
			}
		return true;
	}
};

int qstate;

MYSQL* conn;
MYSQL_ROW row;
MYSQL_RES* res;

class db_response
{
public:

    static void ConnectionFunction()
    {
        conn = mysql_init(0);

		if (conn)
		{
			cout << "\n\n\n\tDatabase Connected" << endl << endl;
		}
		else
		{
			cout << "\n\n\n\tFailed To Connect!" << endl << endl;
		}
        conn = mysql_real_connect(conn, "localhost", "root", "", "dbbsms", 3306, NULL, 0);

		if (conn)
		{
			cout << "\n\tDatabase Connected To MySql" << endl << endl;
		}
		else
		{
			cout << "\n\tFailed To Connect!" << endl << endl;
		}
    }
};

int main()
{
	db_response::ConnectionFunction();
	cout << "\n\n\n\tPlease wait a moment...." << endl;
	Sleep(1500);
	system("cls");
	BookStore obj;
	obj.mainmenu();
	return 0;
}

void BookStore::mainmenu() // this function to display main menu
{
	string option;
	cout << "\n\t________________________________________________________";
	cout << "\n\n\t              BOOKSTORE MANAGEMENT SYSTEM ";
	cout << "\n\t________________________________________________________";
	cout << "\n\n\n\t                     ~ Main ~";
	cout << "\n\n\n\tPlease Choose One Option";
	cout << "\n\n\n\n\t1. Customer\n\n\t2. Bookseller\n\n\t3. Close Application\n";
	cout << "\n\n\tEnter your choice : ";
	cin >> option;

	try {

		if (option == "1")
		{
			system("cls");
			interfaceCustomer();
		}
		else if (option == "2")
		{
			system("cls");
			booksellerlogin();
		}
		else if (option == "3")
		{
			system("cls");

			cout << "\n\n\n\t-----------------------------------" << endl;
			cout << "\t     EXITING SYSTEM, THANK YOU " << endl;
			cout << "\t-----------------------------------" << endl << endl;
			exit(0);
		}
		else
		{
			throw 505;
		}
	}
	catch (...)
	{
		cout << "\n\n\t--------------------------------------------------------------" << endl;
		cout << "\t      You entered the wrong option. Please enter 1,2 or 3 " << endl;
		cout << "\t--------------------------------------------------------------" << endl << endl << endl << endl;
		cout << "\t- Press ENTER to try again - ";
		_getch();
		system("cls");
		mainmenu();
	}
}

void BookStore::booksellerlogin() // this function for bookseller to login first before select other functions
{
        system("cls");

        string BooksellerPassword;
       
		cout << "\n\t________________________________________________________";
		cout << "\n\n\t              BOOKSTORE MANAGEMENT SYSTEM ";
		cout << "\n\t________________________________________________________";
		cout << "\n\n\n\t                     ~ Login ~";
		cout << "\n\n\n\tEnter '0' in username field to cancel";
        cout << "\n\n\n\tEnter username : ";
        cin >> BooksellerUsername;

		if (BooksellerUsername == "0")
		{
			system("cls");
			mainmenu();
		}

        cout << "\n\tEnter password : ";
        char ch;
        while ((ch = _getch()) != 13)
        {
            BooksellerPassword += ch;
            cout << '*';
        }

        string checkUser_query = "select BooksellerID from bookseller where BooksellerUsername = '" + BooksellerUsername + "' and BooksellerPassword = '" + BooksellerPassword + "'";
        const char* cu = checkUser_query.c_str();
        qstate = mysql_query(conn, cu);

        if (!qstate)
        {
            res = mysql_store_result(conn);

            if (res->row_count == 1)
            {
				while (row = mysql_fetch_row(res))
				{
					BooksellerID = row[0];

					cout << "\n\n\n\n\n\t-----------------------------------" << endl;
					cout << "\t          Login successful " << endl;
					cout << "\t-----------------------------------" << endl << endl << endl;

					cout << "\n\n\t - Press Enter to continue -";
					_getch();
					system("cls");
					booksellermenu();
				}
            }
            else
            {
                string c;
				cout << "\n\n\n\n\n\t-----------------------------------" << endl;
				cout << "\t    Invalid username or password " << endl;
				cout << "\t-----------------------------------" << endl;
				cout << "\n\n\n\n\tDo you want to try again ? Press [y/Y] for yes or else to go back to main.";
				cout << "\n\n\n\tYour choice : ";
                cin >> c; 
               
				if (c == "y" || c == "Y")
				{
					booksellerlogin();
				}
				else
				{
					system("cls");
					mainmenu();
				}
            }
        }
        else
        {
            cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
        }
}

void BookStore::customerlogin()
{
	system("cls");

	string CustomerPassword;

	cout << "\n\t________________________________________________________";
	cout << "\n\n\t              BOOKSTORE MANAGEMENT SYSTEM ";
	cout << "\n\t________________________________________________________";
	cout << "\n\n\n\t                     ~ Login ~";
	cout << "\n\n\n\tEnter '0' in username field to cancel";
	cout << "\n\n\n\tEnter username : ";
	cin >> CustomerUsername;

	if (CustomerUsername == "0")
	{
		system("cls");
		interfaceCustomer();
	}

	cout << "\n\tEnter password : ";
	char ch;
	while ((ch = _getch()) != 13)
	{
		CustomerPassword += ch;
		cout << '*';
	}

	string checkUser_query = "select CustomerID from customer where CustomerUsername = '" + CustomerUsername + "' and CustomerPassword = '" + CustomerPassword + "'";
	const char* cu = checkUser_query.c_str();
	qstate = mysql_query(conn, cu);

	if (!qstate)
	{
		res = mysql_store_result(conn);

		if (res->row_count == 1)
		{
			while (row = mysql_fetch_row(res))
			{
				CustomerID = row[0];

				cout << "\n\n\n\n\n\t-----------------------------------" << endl;
				cout << "\t          Login successful " << endl;
				cout << "\t-----------------------------------" << endl << endl << endl;

				cout << "\n\n\t - Press Enter to continue -";
				_getch();
				system("cls");
				customermenu();
			}
		}
		else
		{
			string c;
			cout << "\n\n\n\n\n\t-----------------------------------" << endl;
			cout << "\t    Invalid username or password " << endl;
			cout << "\t-----------------------------------" << endl;
			cout << "\n\n\n\n\tDo you want to try again ? Press [y/Y] for yes or else to go back.";
			cout << "\n\n\n\tYour choice : ";
			cin >> c;

			if (c == "y" || c == "Y")
			{
				customerlogin();
			}
			else
			{
				system("cls");
				interfaceCustomer();
			}
		}
	}
	else
	{
		cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
	}
}

void BookStore::booksellermenu() // this function to display bookseller menu
{
	string option;
	cout << "\n\t________________________________________________________";
	cout << "\n\n\t                Welcome " << BooksellerUsername;
	cout << "\n\t________________________________________________________";
	cout << "\n\n\n\tPlease Choose One Option :\n";
	cout << "\n\n\t1. View Booklist\n\n\t2. Search Book\n\n\t3. Modify Book\n\n\t4. Add Book\n\n\t5. Delete Book\n\n\t6. Show Report\n\n\t7. Log Out\n\n\t8. Close Application\n";
	cout << "\n\n\n\tEnter your choice : ";
	cin >> option;

	if (option == "1")
	{
		system("cls");
		viewbookBS();
	}
	else if (option == "2")
	{
		system("cls");
		searchbookBS();
	}
	else if (option == "3")
	{
		system("cls");
		modifybook();
	}
	else if (option == "4")
	{
		system("cls");
		addbook();
	}
	else if (option == "5")
	{
		system("cls");
		deletebook();
	}
	else if (option == "6")
	{
		system("cls");
		showreport();
	}
	else if (option == "7")
	{
		system("cls");
		char c;
		cout << "\n\n\n\n\tAre you sure that you want to log out ? press [y] for yes or else to go back to menu :  ";
		cin >> c;

		if (c == 'y' || c == 'Y')
		{
			cout << "\n\n\n\t-----------------------------------" << endl;
			cout << "               SUCCESFULLY LOGGED OUT      " << endl;
			cout << "\t-----------------------------------" << endl << endl << endl;
			cout << "\t";
			system("pause");
			system("cls");
			mainmenu();
		}
		else
		{
			system("cls");
			booksellermenu();
		}
	}
	else if (option == "8")
	{
		system("cls");

		cout << "\n\n\n\t-----------------------------------" << endl;
		cout << "\t     EXITING SYSTEM, THANK YOU " << endl;
		cout << "\t-----------------------------------" << endl << endl;
		exit(0);
	}
	else
	{
		cout << "\n\n\n\n\t------------------------------------------------------------------------" << endl;
		cout << "\t  You entered the wrong option. Please enter 1, 2, 3, 4, 5, 6, 7 or 8 " << endl;
		cout << "\t------------------------------------------------------------------------" << endl;
		cout << "\n\n\n\n\t- Press ENTER to try again - ";
		_getch();
		system("cls");
		booksellermenu();
	}
}

void BookStore::customermenu() // this function to display customer menu 
{
	string option;
	
	cout << "\n\t________________________________________________________";
	cout << "\n\n\t                Welcome " << CustomerUsername;
	cout << "\n\t________________________________________________________";
	cout << "\n\n\n\tPlease Choose One Option:\n";
	cout << "\n\n\t1. Purchase Book\n\n\t2. View Purchase History\n\n\t3. Log Out\n\n\t4. Close Application\n";
	cout << "\n\n\n\tEnter your choice : ";
	cin >> option;

	if (option == "1")
	{
		system("cls");
		viewbookC();
	}
	else if (option == "2")
	{
		system("cls");
		viewInvoice();
	}
	else if (option == "3")
	{
		system("cls");
		char c;
		cout << "\n\n\n\n\tAre you sure that you want to log out ? press [y] for yes or else to go back to menu :  ";
		cin >> c;

		if (c == 'y' || c == 'Y')
		{
			cout << "\n\n\n\t-----------------------------------" << endl;
			cout << "               SUCCESFULLY LOGGED OUT      " << endl;
			cout << "\t-----------------------------------" << endl << endl << endl;
			cout << "\t";
			system("pause");
			system("cls");
			mainmenu();
		}
		else
		{
			system("cls");
			customermenu();
		}
	}
	else if (option == "4")
	{
		system("cls");

		cout << "\n\n\n\t-----------------------------------" << endl;
		cout << "\t     EXITING SYSTEM, THANK YOU " << endl;
		cout << "\t-----------------------------------" << endl << endl;
		exit(0);
	}
	else
	{
		cout << "\n\n\n\n\t---------------------------------------------------------" << endl;
		cout << "\t  You entered the wrong option. Please enter 1,2,3 or 4  " << endl;
		cout << "\t---------------------------------------------------------" << endl;
		cout << "\n\n\t- Press ENTER to try again - ";
		_getch();
		system("cls");
		customermenu();
	}
}

void BookStore::interfaceCustomer()
{
	system("cls");

	string pilih;
	string username, password;

	cout << endl << endl << endl << "           Please choose one option : " << endl << endl << endl;
	cout << "           1. Login " << endl << endl;
	cout << "           2. Register " << endl << endl;
	cout << "           3. Forgot Password " << endl << endl;
	cout << "           4. Cancel " << endl << endl << endl;
	cout << "           Enter your choice : ";
	cin >> pilih;

	if (pilih == "1")
	{
		system("cls");
		customerlogin();
	}
	else if (pilih == "2")
	{
		system("cls");
		getdetail();
	}
	else if (pilih == "3")
	{
		system("cls");

		cout << endl << endl << "                        ~ Change Password ~ ";
		cout << endl << endl << endl << "           Enter '0' in username field to cancel";
	
		cout << endl << endl << endl << "           Enter your registered username : ";
		cin >> username;

		if (username == "0")
		{
			system("cls");
			interfaceCustomer();
		}

		string checkUser_query = "select CustomerUsername from customer where CustomerUsername = '" + username + "'";
		const char* cu = checkUser_query.c_str();
		qstate = mysql_query(conn, cu);
		res = mysql_store_result(conn);
		row = mysql_fetch_row(res);
		if (res->row_count == 0)
		{
			cout << "\n\n\n\n          --------------------------------------------------------" << endl;
			cout << "                You have never registered using this username " << endl;
			cout << "           --------------------------------------------------------";
			cout << "\n\n\n\n           - Press ENTER to try again - ";
			_getch();
			interfaceCustomer();
		}

		cout << endl <<"           Enter new password : ";
		cin >> password;

		string update_query = "update customer set CustomerPassword = '" + password + "' where CustomerUsername = '" + username + "'";
		const char* q = update_query.c_str();
		qstate = mysql_query(conn, q);

		cout << "\n\n\n           --------------------------" << endl;
		cout << "               Password updated " << endl;
		cout << "           --------------------------";
		cout << "\n\n\n           - Press ENTER to continue -";
		_getch();

		system("cls");
		interfaceCustomer();
	}
	else if (pilih == "4")
	{
		system("cls");
		mainmenu();
	}
	else
	{
		cout << "\n\n\n\n           ---------------------------------------------------------" << endl;
		cout << "             You entered the wrong option. Please enter 1,2,3 or 4  " << endl;
		cout << "           ---------------------------------------------------------" << endl;
		cout << "\n\n           - Press ENTER to try again - ";
		_getch();
		system("cls");
		interfaceCustomer();
	}
}

void BookStore::getdetail() // this function for customer to register their details
{
	system("cls");

	string CustomerUsername2;
	string CustomerPassword2;
	string CustomerPhoneNumber2;
	string CustomerAddress2;
	string CustomerEmail2;

	cout << endl << endl << "                        ~ Customer Details ~" << endl << endl << endl;
	cout << "           Please fill in your details for delivery purposes. ";

	cin.ignore(1, '\n');
	cout << endl << endl << endl << "           Enter '0' in username field to cancel" << endl << endl << endl;
	cout << endl <<"           Enter username : ";
	getline(cin, CustomerUsername2);

	if (CustomerUsername2 == "0")
	{
		system("cls");
		interfaceCustomer();
	}

	cout << endl << "           Enter password : ";
	getline(cin, CustomerPassword2);

	cout << endl << "           Enter phone number ( start with 0 and must be 10 digits ) : ";
	getline(cin, CustomerPhoneNumber2);
	
	if (isValid(CustomerPhoneNumber2))
	{}
	else
	{
		cout << endl << endl << endl << "           --------------------------------------------" << endl;
		cout << "               Your phone number entered is invalid " << endl;
		cout << "           --------------------------------------------" << endl;
		cout << endl << endl << endl << "           - Press ENTER twice to try again - " ;
		_getch();
		system("cls");
		getdetail();
	}
	
	cout << endl << "           Enter address : ";
	getline(cin, CustomerAddress2);
	cout << endl << "           Enter email ( eg: zhr@gmail.com ) : ";
	getline(cin, CustomerEmail2);

	if (Email_check(CustomerEmail2))
	{}
	else
	{
		cout << endl << endl << endl << "           --------------------------------------------" << endl;
		cout << "                   Your email entered is invalid " << endl;
		cout << "           --------------------------------------------" << endl;


		cout << endl << endl << endl << "           - Press ENTER twice to try again - ";
		_getch();
		system("cls");
		getdetail();
	}

	string insert_query = "insert into customer (CustomerUsername, CustomerPassword, CustomerPhoneNumber, CustomerAddress, CustomerEmail) values ('" + CustomerUsername2 + "', '" + CustomerPassword2 + "', '" + CustomerPhoneNumber2 + "', '" + CustomerAddress2 + "', '" + CustomerEmail2 + "')";
	const char* q = insert_query.c_str();
	qstate = mysql_query(conn, q);

	if (!qstate)
	{
		cout << "\n\n\n\n           ------------------------------" << endl;
		cout << "             Details added successfully " << endl;
		cout << "           ------------------------------";
		cout << "\n\n\n           - Press ENTER to continue -";
	}
	else
	{
		cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
	}

	_getch();
	system("cls");
	interfaceCustomer();
}

void BookStore::addbook() // this function to add book and only for bookseller
{
	system("cls");

	stringstream ss;

	string confirm;
	string BookType[2] = { "tutorial" , "lab" };
	string Type;
	string BookType2;
	string BookName, BookAuthorName, BookPublicationName;
	string choose;

	cout << "\n\n\n\t    ~ Add Book ~";
	cout << "\n\n\n\tEnter '0' in book name field to cancel";

	cin.ignore(1, '\n');
	cout << endl << "\n\n\n\tEnter book name : ";
	getline(cin, BookName);

	if (BookName == "0")
	{
		system("cls");
		booksellermenu();
	}

	cout  <<"\n\tEnter author name : ";
	getline(cin, BookAuthorName);

	if (BookAuthorName == "0")
	{
		system("cls");
		booksellermenu();
	}

	cout  <<"\n\tEnter publication name : ";
	getline(cin, BookPublicationName);

	if (BookPublicationName == "0")
	{
		system("cls");
		booksellermenu();
	}

	cout  << "\n\tPlease choose the book type  ";
	cout << "\n\n\t1. Tutorial ";
	cout << "\n\n\t2. Lab ";
	cout << endl << "\n\n\tInsert the number : ";
	cin >> Type;
	
	if (Type == "1")
	{
		BookType2 = BookType[0];
	}
	else if (Type == "2")
	{
		BookType2 = BookType[1];
	}
	else if (Type == "0")
	{
		system("cls");
		booksellermenu();
	}
	else
	{
		cout << endl << endl << "\n\t-------------------" << endl;
		cout << "\t    Wrong input " << endl;
		cout << "\t-------------------" ;
		cout << "\n\n\n\t- Press ENTER to try again - ";
		_getch();
		system("cls");
		addbook();
	}

	cin.ignore(1, '\n');
	cout << endl <<"\n\tEnter book price : ";

	std::string line;
	double Price;
	while (std::getline(std::cin, line))
	{
		std::stringstream ss(line);
		if (ss >> Price)
		{
			if (ss.eof())
			{   // Success
				break;
			}
		}
		std::cout << endl << endl << "\n\t ------------------------------ " << endl;
		std::cout << "\t    Only numbers are allowed " << endl;
		std::cout << "\t ------------------------------ " ;
		cout << "\n\n\n\t- Press ENTER twice to try again - ";
		_getch();
		system("cls");
		addbook();
	}

	cout  <<"\n\tEnter book quantity : ";

	std::string line2;
	int Quantity;
	while (std::getline(std::cin, line2))
	{
		std::stringstream ss(line2);
		if (ss >> Quantity)
		{
			if (ss.eof())
			{   // Success
				break;
			}
		}
		std::cout << endl << endl << "\n\t ------------------------------ " << endl;
		std::cout << "\t    Only numbers are allowed " << endl;
		std::cout << "\t ------------------------------ ";
		cout << "\n\n\n\t- Press ENTER twice to try again - ";
		_getch();
		system("cls");
		addbook();
	}

	string BookPrice = to_string(Price);
	string BookQuantity = to_string(Quantity);

	cout << "\n\n\n\tDo you confirm to add this book ? Enter [y/Y] for yes or else to cancel ";
	cout << "\n\n\n\tYour choice : ";
	cin >> confirm;
	
	if (confirm == "y" || confirm == "Y")
	{
		string insert_query = "insert into book (BookName, BookAuthorName, BookPublicationName, BookType, BookPrice, BookQuantity) values ('" + BookName + "', '" + BookAuthorName + "', '" + BookPublicationName + "', '" + BookType2 + "', '" + BookPrice + "', '" + BookQuantity + "')";
		const char* q = insert_query.c_str();
		qstate = mysql_query(conn, q);

		if (!qstate)
		{
			cout << "\n\n\n\n\t------------------------------" << endl;
			cout << "\t   Book added successfully " << endl;
			cout << "\t------------------------------";
			cout << "\n\n\n\t- Press ENTER to continue -";
		}
		else
		{
			cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
		}

		do
		{
			_getch();
			system("cls");

			cout << "\n\n\n\n\tDo you want add another book? press [y/Y] for yes or else to go back to menu : ";
			cin >> choose;

			if (choose == "y" || choose == "Y")
			{
				system("cls");
				addbook();
			}
			else
			{
				system("cls");
				booksellermenu();
			}
		} while (choose == "y" || choose == "Y");
	}
	else
	{
		system("cls");
		addbook();
	}
}

void BookStore::viewbookBS() // this function is to display booklist for bookseller
{
	system("cls");
	
	cout << endl << endl << endl << "\t\t\t\t\t\t\t\t      ~ BookList ~" << endl << endl;

	qstate = mysql_query(conn, "select BookId, BookName, BookAuthorName, BookPublicationName, BookType, BookPrice, BookQuantity from book");

	if (!qstate)
	{
		cout << "\t\t=============================================================================================================================" << endl;
		cout << setw(20) << "Id" << setw(20) << "Name" << setw(20) << "Author Name" << setw(20) << "Publication Name" << setw(20) << "Type" << setw(20) << "Price" << setw(20) << "Quantity " << endl;
		cout << "\t\t=============================================================================================================================" << endl;

		res = mysql_store_result(conn);
		while (row = mysql_fetch_row(res))
		{
			cout << setw(20) << row[0] << setw(20) << row[1] << setw(17) << row[2] << setw(19) << row[3] << setw(25) << row[4] << setw(18) << row[5] << setw(17) << row[6] << endl << endl;
		}
	}
	else
	{
		cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
	}
	cout << "\t\t=============================================================================================================================" << endl;


	cout << "\n\n\n\n\n\t\t\t\t\t\t\t\t- Press ENTER to continue -";
	_getch();
	system("cls");
	booksellermenu();
}

void BookStore::viewbookC() // this function is to display booklist for customer
{
	system("cls");

	string option;

	
	cout << endl << endl << endl << "\t\t\t\t\t\t\t\t      ~ BookList ~" << endl << endl;

	qstate = mysql_query(conn, "select BookId, BookName, BookAuthorName, BookPublicationName, BookType, BookPrice, BookQuantity from book");

	if (!qstate)
	{
		cout << "\t\t=============================================================================================================================" << endl;
		cout << setw(20) << "Id" << setw(20) << "Name" << setw(20) << "Author Name" << setw(20) << "Publication Name" << setw(20) << "Type" << setw(20) << "Price" << setw(20) << "Quantity " << endl;
		cout << "\t\t=============================================================================================================================" << endl;

		res = mysql_store_result(conn);
		while (row = mysql_fetch_row(res))
		{
			cout << setw(20) << row[0] << setw(20) << row[1] << setw(17) << row[2] << setw(19) << row[3] << setw(25) << row[4] << setw(18) << row[5] << setw(17) << row[6] << endl << endl;
		}

		cout << "\t\t=============================================================================================================================" << endl;


		cout << "\n\n\t\tInterested to purchase ? Enter [Y/y] for yes to proceed or else to go back to menu.";
		cout << "\n\n\n\t\tEnter your choice : ";
		cin >> option;

		if (option == "Y" || option == "y")
		{
			system("cls");
			purchasebook();
		}
		else
		{
			system("cls");
			customermenu();
		}

	}
	else
	{
		cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
	}

	cout << "\n\n\n\t\t\t\t\t\t\t\t- Press ENTER to continue -";
	_getch();
	system("cls");
	customermenu();
}

void BookStore::searchbookBS()
{
	system("cls");
	string choose;
	string BookType;

	cout << "\n\n\n\t                ~ Search book by type ~";
	cout << "\n\n\n\tEnter '0' to cancel";
	cout << "\n\n\t*The book type must be in use lower case letters only.";
	cin.ignore(1, '\n');
	cout << endl << "\n\n\n\tEnter book type : ";
	getline(cin, BookType);

	if (BookType == "0")
	{
		system("cls");
		booksellermenu();
	}

	string checkUser_query = "select BookType from book where BookType like '%" + BookType + "%'";
	const char* cu = checkUser_query.c_str();
	qstate = mysql_query(conn, cu);
	res = mysql_store_result(conn);
	row = mysql_fetch_row(res);
	if (res->row_count == 0)
	{
		cout << "\n\n\n\n\t--------------------------------------------------------" << endl;
		cout << "\t   The book you are looking for is not available here " << endl;
		cout << "\t--------------------------------------------------------";
		cout << "\n\n\n\n\t- Press ENTER twice to try again - ";
		_getch();
		searchbookBS();
	}

	system("cls");

	cout << endl << endl << endl << "\t\t\t\t\t\t\t\t~ BookList ~" << endl << endl;

	string search_query = "select BookID, BookName, BookAuthorName, BookPublicationName, BookType, BookPrice, BookQuantity from book where BookType like '%" + BookType + "%'";
	const char* q = search_query.c_str();
	qstate = mysql_query(conn, q);

	if (!qstate)
	{
		cout << "\t\t=============================================================================================================================" << endl;
		cout << setw(20) << "Id" << setw(20) << "Name" << setw(20) << "Author Name" << setw(20) << "Publication Name" << setw(20) << "Type" << setw(20) << "Price" << setw(20) << "Quantity " << endl;
		cout << "\t\t=============================================================================================================================" << endl;

		res = mysql_store_result(conn);
		while (row = mysql_fetch_row(res))
		{
			cout << setw(20) << row[0] << setw(20) << row[1] << setw(17) << row[2] << setw(19) << row[3] << setw(25) << row[4] << setw(18) << row[5] << setw(17) << row[6] << endl << endl;
		}

		cout << "\t\t=============================================================================================================================" << endl;


		cout << endl  << endl << "\n\t\tDo you want to search other type ? press [y/Y] for yes or else to go back to menu : ";
		cin >> choose;

		if (choose == "y" || choose == "Y")
		{
			system("cls");
			searchbookBS();
		}
		else 
		{
			system("cls");
			booksellermenu();
		}
		
	}
	else
	{
		cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
	}
}

void BookStore::deletebook()
{
	system("cls");

	string choose;
	string confirm;

	cout << endl << endl  << "\t\t\t\t\t\t\t\t  ~ Delete book ~" << endl << endl;

	qstate = mysql_query(conn, "select BookID, BookName, BookAuthorName, BookPublicationName, BookType, BookPrice, BookQuantity from book");

	if (!qstate)
	{
		cout << "\t\t=============================================================================================================================" << endl;
		cout << setw(20) << "Id" << setw(20) << "Name" << setw(20) << "Author Name" << setw(20) << "Publication Name" << setw(20) << "Type" << setw(20) << "Price" << setw(20) << "Quantity " << endl;
		cout << "\t\t=============================================================================================================================" << endl;

		res = mysql_store_result(conn);
		while (row = mysql_fetch_row(res))
		{
			cout << setw(20) << row[0] << setw(20) << row[1] << setw(17) << row[2] << setw(19) << row[3] << setw(25) << row[4] << setw(18) << row[5] << setw(17) << row[6] << endl << endl;
		}

		cout << "\t\t=============================================================================================================================" << endl;


		cout << "\n\n\t\tEnter '0' to cancel";
		cout << "\n\n\n\n\t\tPlease choose Id that want to delete : ";
		cin >> BookID;

		if (BookID == "0")
		{
			system("cls");
			booksellermenu();
		}

		string checkUser_query = "select BookID from book where BookID = '" + BookID + "'";
		const char* cu = checkUser_query.c_str();
		qstate = mysql_query(conn, cu);
		res = mysql_store_result(conn);
		row = mysql_fetch_row(res);
		if (res->row_count == 0)
		{
			cout << "\n\n\n\n\t\t-------------------------------------" << endl;
			cout << "\t\t    Book ID entered does not exist " << endl;
			cout << "\t\t-------------------------------------" ;

			cout << "\n\n\n\t\t- Press ENTER to try again -";
			_getch();
			deletebook();
		}
		
		cout << "\n\n\n\n\t\tDo you confirm to delete this book ? Enter [y/Y] for yes or else to cancel ";
		cout << "\n\n\n\t\tYour choice : ";
		cin >> confirm;

		if (confirm == "y" || confirm == "Y")
		{
			string delete_query = "\n\t\tdelete from book where BookID = '" + BookID + "'";
			const char* q = delete_query.c_str();
			qstate = mysql_query(conn, q);

			cout << "\n\n\n\t\t-------------------------" << endl;
			cout << "\t\t   Deletion successful " << endl;
			cout << "\t\t-------------------------" << endl << endl;
			cout << "\n\n\n\t\t- Press ENTER to continue -";

			_getch();
			system("cls");

			cout << "\n\n\t\tDo you want to delete other book? press [y/Y] for yes or else to go back to menu : ";
			cin >> choose;

			if (choose == "y" || choose == "Y")
			{
				system("cls");
				deletebook();
			}
			else
			{
				system("cls");
				booksellermenu();
			}
		}
		else
		{
			system("cls");
			deletebook();
		}
	}
	else
	{
		cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
	}
}

void BookStore::modifybook() //this function to modify book details
{
	system("cls");

	string data;
	string choose;
	string confirm;
	string option;
	string datas;
	string BookType1 = { "tutorial"};
	string BookType2 = { "lab" };
	
	string* ip;
	string* ip2;
	ip = &BookType1;
	ip2 = &BookType2;

	cout << "\n\n\n\t                                                           ~ Modify Book Details ~" << endl << endl;

	qstate = mysql_query(conn, "select BookID, BookName, BookAuthorName, BookPublicationName, BookType, BookPrice, BookQuantity from book");

	if (!qstate)
	{
		cout << "\t\t=============================================================================================================================" << endl;
		cout << setw(20) << "Id" << setw(20) << "Name" << setw(20) << "Author Name" << setw(20) << "Publication Name" << setw(20) << "Type" << setw(20) << "Price" << setw(20) << "Quantity " << endl;
		cout << "\t\t=============================================================================================================================" << endl;

		res = mysql_store_result(conn);
		while (row = mysql_fetch_row(res))
		{
			cout << setw(20) << row[0] << setw(20) << row[1] << setw(17) << row[2] << setw(19) << row[3] << setw(25) << row[4] << setw(18) << row[5] << setw(17) << row[6] << endl << endl;
		}

		cout << "\t\t=============================================================================================================================" << endl;


		cout << "\n\n\t\tEnter '0' in Id field to cancel";
		cout << "\n\n\n\t\tPlease choose Id that want to modify : ";
		cin >> BookID;

		if (BookID == "0")
		{
			system("cls");
			booksellermenu();
		}

		string checkUser_query = "select BookID from book where BookID = '" + BookID + "'";
		const char* cu = checkUser_query.c_str();
		qstate = mysql_query(conn, cu);
		res = mysql_store_result(conn);
		row = mysql_fetch_row(res);
		if (res->row_count == 0)
		{
			cout << "\n\n\n\t\t--------------------------------------" << endl;
			cout << "\t\t    Book ID entered does not exist " << endl;
			cout << "\t\t--------------------------------------";
			cout << "\n\n\n\t\t- Press ENTER to try again - ";
			_getch();
			modifybook();
		}

		cout << endl << "\n\n\t\t~ Category ~" << endl << endl << endl;
		cout << "\t\t1. Name" << endl << endl;
		cout << "\t\t2. Author Name" << endl << endl;
		cout << "\t\t3. Publication Name" << endl << endl;
		cout << "\t\t4. Type" << endl << endl;
		cout << "\t\t5. Price" << endl << endl;
		cout << "\t\t6. Quantity" << endl << endl << endl;
		cout << "\t\tPlease choose one category to modify  : ";
		cin >> choose;
		

		cin.ignore(1, '\n');
		if (choose == "1")
		{
			cout << "\n\n\n\t\tEnter New Name : ";
			getline(cin, data);

			cout << "\n\n\n\n\t\tDo you confirm to update this detail ? Enter [y/Y] for yes or else to cancel ";
			cout << "\n\n\n\t\tYour choice : " ;
			cin >> confirm;

			if (confirm == "y" || confirm == "Y")
			{
				string update_query = "update book set BookName = '" + data + "' where BookID = '" + BookID + "'";
				const char* q = update_query.c_str();
				qstate = mysql_query(conn, q);
			}
			else
			{
				system("cls");
				modifybook();
			}
		}
		else if (choose == "2")
		{
			cout << "\n\n\t\tEnter New Author Name : ";
			getline(cin, data);

			cout << "\n\n\n\n\t\tDo you confirm to update this detail ? Enter [y/Y] for yes or else to cancel ";
			cout << "\n\n\n\t\tYour choice : ";
			cin >> confirm;

			if (confirm == "y" || confirm == "Y")
			{
				string update_query = "update book set BookAuthorName = '" + data + "' where BookID = '" + BookID + "'";
				const char* q = update_query.c_str();
				qstate = mysql_query(conn, q);
			}
			else
			{
				system("cls");
				modifybook();
			}
		}
		else if (choose == "3")
		{
			cout << "\n\n\t\tEnter New Publication Name : ";
			getline(cin, data);

			cout << "\n\n\n\n\t\tDo you confirm to update this detail ? Enter [y/Y] for yes or else to cancel ";
			cout << "\n\n\n\t\tYour choice : ";
			cin >> confirm;

			if (confirm == "y" || confirm == "Y")
			{
				string update_query = "update book set BookPublicationName = '" + data + "' where BookID = '" + BookID + "'";
				const char* q = update_query.c_str();
				qstate = mysql_query(conn, q);
			}
			else
			{
				system("cls");
				modifybook();
			}
		}
		else if (choose == "4")
		{
			cout << "\n\n\t\tPlease choose new book type ";
			cout << "\n\n\n\t\t1. Tutorial ";
			cout << "\n\n\t\t2. Lab ";
			cout << "\n\n\n\t\tInsert the number : ";
			cin >> datas;

			if (datas == "1")
			{
				cout << "\n\n\n\n\t\tDo you confirm to update this detail ? Enter [y/Y] for yes or else to cancel ";
				cout << "\n\n\n\t\tYour choice : ";
				cin >> confirm;

				if (confirm == "y" || confirm == "Y")
				{
					data = *ip;
				}
				else
				{
					system("cls");
					modifybook();
				}
			}
			else if (datas == "2")
			{
				cout << "\n\n\n\n\t\tDo you confirm to update this detail ? Enter [y/Y] for yes or else to cancel ";
				cout << "\n\n\n\t\tYour choice : ";
				cin >> confirm;

				if (confirm == "y" || confirm == "Y")
				{
					data = *ip2;
				}
				else
				{
					system("cls");
					modifybook();
				}
			}
			else
			{
				cout << "\n\n\n\t\t----------------------------------------------------------" << endl;
				cout << "\t\t    You entered the wrong option. Please enter 1 or 2 " << endl;
				cout << "\t\t----------------------------------------------------------";
				cout << "\n\n\n\t\t- Press ENTER to try again - ";
				_getch();
				system("cls");
				modifybook();
			}
			string update_query = "update book set BookType = '" + data + "' where BookID = '" + BookID + "'";
			const char* q = update_query.c_str();
			qstate = mysql_query(conn, q);
		}
		else if (choose == "5")
		{
			cout << "\n\n\t\tEnter New Price : ";

			std::string line3;
			double Price;
			while (std::getline(std::cin, line3))
			{
				std::stringstream ss(line3);
				if (ss >> Price)
				{
					if (ss.eof())
					{   // Success
						break;
					}
				}
				std::cout << "\n\n\n\t\t ------------------------------ " << endl;
				std::cout << "\t\t    Only numbers are allowed " << endl;
				std::cout << "\t\t ------------------------------ ";
				cout << "\n\n\n\t\t- Press ENTER to try again - ";
				_getch();
				system("cls");
				modifybook();
			}

			string data = to_string(Price);

			cout << "\n\n\n\n\t\tDo you confirm to update this detail ? Enter [y/Y] for yes or else to cancel ";
			cout << "\n\n\n\t\tYour choice : ";
			cin >> confirm;

			if (confirm == "y" || confirm == "Y")
			{
				string update_query = "update book set BookPrice = '" + data + "' where BookID = '" + BookID + "'";
				const char* q = update_query.c_str();
				qstate = mysql_query(conn, q);
			}
			else
			{
				system("cls");
				modifybook();
			}
		}
		else if (choose == "6")
		{
			cout << "\n\n\t\tEnter New Quantity : ";

			std::string line4;
			int Quantity;
			while (std::getline(std::cin, line4))
			{
				std::stringstream ss(line4);
				if (ss >> Quantity)
				{
					if (ss.eof())
					{   // Success
						break;
					}
				}
				std::cout << "\n\n\n\t\t ------------------------------ " << endl;
				std::cout << "\t\t    Only numbers are allowed " << endl;
				std::cout << "\t\t ------------------------------ ";
				cout << "\n\n\n\t\t- Press ENTER to try again - ";
				_getch();
				system("cls");
				modifybook();
			}

			string data = to_string(Quantity);

			cout << "\n\n\n\n\t\tDo you confirm to update this detail ? Enter [y/Y] for yes or else to cancel ";
			cout << "\n\n\n\t\tYour choice : ";
			cin >> confirm;

			if (confirm == "y" || confirm == "Y")
			{
				string update_query = "update book set BookQuantity = '" + data + "' where BookID = '" + BookID + "'";
				const char* q = update_query.c_str();
				qstate = mysql_query(conn, q);
			}
			else
			{
				system("cls");
				modifybook();
			}
		}
		else if (choose == "0")
		{
		  system("cls");
		  booksellermenu();
        }
		else
		{
		cout << "\n\n\n\n\t\t--------------------------------------------------------------------" << endl;
		cout << "\t\t   You entered the wrong option. Please enter 1, 2, 3, 4, 5 or 6 " << endl;
		cout << "\t\t--------------------------------------------------------------------";
		cout << "\n\n\n\n\t\t- Press ENTER to try again - ";
		  _getch();
		  system("cls");
		  modifybook();
        }

		cout << "\n\n\n\t\t--------------------------" << endl;
		cout << "\t\t   Book details updated " << endl;
		cout << "\t\t--------------------------" ;
		cout << "\n\n\n\t\t- Press ENTER to continue -";
		_getch();
		
		system("cls");

		cout << "\n\n\n\n\t\tDo you want to edit other detail? press [y/Y] for yes or else to go back to menu : ";
		cin >> option;

		if (option == "y" || option == "Y")
		{
			system("cls");
			modifybook();
		}
		else
		{
			system("cls");
			booksellermenu();
		}
	}
	else
	{
		cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
	}
}

void BookStore::purchasebook() //this function for customer to purchase book
{
	time_t currTime;
	tm* currTm;
	char dateString[100];
	time(&currTime);
	currTm = localtime(&currTime);
	strftime(dateString, 50, "%Y-%m-%d", currTm);

	stringstream ss;

	cout << endl << endl << "                                   ~ Search Book By Name ~" << endl << endl << endl << endl;
	cout << "\t\tEnter '0' in book name field to cancel" << endl << endl << endl;
	cout << "\t\t*The book name must be in use lower case letters only." << endl << endl;
	cout << "\t\t*Press ENTER without entering any book name if you want to view all the books.";

	cin.ignore(1, '\n');
	cout << endl << endl << endl << endl << "\t\tEnter book name : ";
	getline(cin, BookName);

	if (BookName == "0")
	{
		system("cls");
		customermenu();
	}

	string checkUser_query = "select BookName from book where BookName like '%" + BookName + "%'";
	const char* cu = checkUser_query.c_str();
	qstate = mysql_query(conn, cu);
	res = mysql_store_result(conn);
	row = mysql_fetch_row(res);

	if (res->row_count == 0)
	{
		cout << "\n\n\n\n\t\t--------------------------------------------------------" << endl;
		cout << "\t\t   The book you are looking for is not available here " << endl;
		cout << "\t\t--------------------------------------------------------";
		cout << "\n\n\n\t\t- Press ENTER twice to try again - ";
		_getch();
		system("cls");
		purchasebook();
	}

	string select_query = "select BookID, BookName, BookAuthorName, BookPublicationName, BookType, BookPrice, BookQuantity from book where BookName like '%" + BookName + "%'";
	const char* q = select_query.c_str();
	qstate = mysql_query(conn, q);

	if (!qstate)
	{
		cout << endl << endl << "\t\t=============================================================================================================================" << endl;
		cout << setw(20) << "Id" << setw(20) << "Name" << setw(20) << "Author Name" << setw(20) << "Publication Name" << setw(20) << "Type" << setw(20) << "Price" << setw(20) << "Quantity " << endl;
		cout << "\t\t=============================================================================================================================" << endl;

		res = mysql_store_result(conn);
		while (row = mysql_fetch_row(res))
		{
			cout << setw(20) << row[0] << setw(20) << row[1] << setw(17) << row[2] << setw(19) << row[3] << setw(25) << row[4] << setw(18) << row[5] << setw(17) << row[6] << endl << endl;
			cout << "\t\t=============================================================================================================================" << endl;
		}
	}

	if (!qstate)
	{
		cout << endl << endl << endl << endl << "                                   ~ Purchase Book ~" << endl << endl << endl;
		cout << "\t\tEnter '0' in Id field to go back to search" << endl << endl << endl << endl;
		cout << "\t\tPlease enter Id that you want to purchase : ";
		getline(cin, BookID);

		if (BookID == "0")
		{
			system("cls");
			purchasebook();
		}


		string checkUser_query = "select BookID from book where BookID like '%" + BookID + "%'";
		const char* cu = checkUser_query.c_str();
		qstate = mysql_query(conn, cu);
		res = mysql_store_result(conn);
		row = mysql_fetch_row(res);

		if (res->row_count == 0)
		{
			cout << endl << endl << "\n\n\t\t-------------------------------------" << endl;
			cout << "\t\t   Book ID entered does not exist " << endl;
			cout << "\t\t-------------------------------------" ;
			cout << endl << "\n\n\t\t- Press ENTER twice to try again - ";
			_getch();
			system("cls");
			purchasebook();
		}

		string selectQuantity_query = "select BookQuantity from book where BookID = '" + BookID + "'";
		const char* sq = selectQuantity_query.c_str();
		qstate = mysql_query(conn, sq);
		if (!qstate)
		{
			res = mysql_store_result(conn);
			while (row = mysql_fetch_row(res))
			{
				CurrentQuantity = row[0];
			}
		}
		else
		{
			cout << "\n -- Query execution error! -- " << endl << endl;
		}

		cout << "\n\t\tEnter Quantity that you want to purchase : ";

		std::string line3;
		int Purchasequantity;
		while (std::getline(std::cin, line3))
		{
			std::stringstream ss(line3);
			if (ss >> Purchasequantity)
			{
				if (ss.eof())
				{   // Success
					break;
				}
			}
			std::cout << "\n\n\n\t\t ------------------------------ " << endl;
			std::cout << "\t\t    Only numbers are allowed " << endl;
			std::cout << "\t\t ------------------------------ ";
			cout << "\n\n\n\t\t- Press ENTER to try again - ";
			_getch();
			system("cls");
			purchasebook();
		}

		if (Purchasequantity > stoi(CurrentQuantity))
		{
			cout << endl << endl << "\n\n\t\t-------------------------------------" << endl;
			cout << "\t\t    Item quantity is out of range " << endl;
			cout << "\t\t------------------------------------- ";

			cout << "\n\n\n\t\t- Press ENTER twice to try again - ";
			_getch();
			system("cls");
			purchasebook();
		}

		UpdateQuantity = (stoi(CurrentQuantity) - Purchasequantity);

		ss << UpdateQuantity;
		string p;
		ss >> p;

		string selectPrice_query = "select BookPrice from book where BookID = '" + BookID + "'";
		const char* sP = selectPrice_query.c_str();
		qstate = mysql_query(conn, sP);
		if (!qstate)
		{
			res = mysql_store_result(conn);
			while (row = mysql_fetch_row(res))
			{
				price = row[0];
			}
		}
		else
		{
			cout << "\n -- Query execution error! -- " << endl << endl;
		}

		Totalprice = (stod(price) * Purchasequantity);

		cout << endl << endl << "\n\n\t\t----------------------------------------------------" << endl;
		cout << "\t\t       The amount you have to pay is RM " << Totalprice << endl;
		cout << "\t\t---------------------------------------------------- ";

		cout << "\n\n\n\n\t\tConfirm this order ? Enter [y/Y] or else to cancel " ;
		string confirm;
		cout << endl << "\n\n\t\tYour choice : ";
		cin >> confirm;

		if (confirm == "y" || confirm == "Y")
		{
		}
		else
		{
			cout << endl << "\n\n\t\t-------------------------------------" << endl;
			cout << "\t\t     You cancelled this process " << endl;
			cout << "\t\t------------------------------------- ";
			cout << "\n\n\n\t\t- Press ENTER to try again - ";
			_getch();
			system("cls");
			purchasebook();
		}

		string k = to_string(Totalprice);

		string j = to_string(Purchasequantity);

		string update_query = "update book set BookQuantity = '" + p + "' where BookID = '" + BookID + "'";
		const char* q = update_query.c_str();
		qstate = mysql_query(conn, q);

		string checkCust_query2 = "select CustomerID from customer where CustomerUsername = '" + CustomerUsername + "'";
		const char* cu2 = checkCust_query2.c_str();
		qstate = mysql_query(conn, cu2);
		if (!qstate)
		{
			res = mysql_store_result(conn);
			row = mysql_fetch_row(res);
			CustomerID = row[0];
		}
		else
		{
			cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
		}
		
		string insert_query = "insert into purchase (PurchaseQuantity, PurchaseTotalPrice, PurchaseDate, BookID, CustomerID) values ('" + j + "', '" + k + "', '" + dateString + "' , '" + BookID + "' , '" + CustomerID + "')";
		const char* Q = insert_query.c_str();
		qstate = mysql_query(conn, Q);

		if (!qstate)
		{
			cout << endl << "\n\n\n\t\t-------------------------------------" << endl;
			cout << "\t\t   Your order is successfully made " << endl;
			cout << "\t\t------------------------------------- ";
			cout << "\n\n\n\n\n\t\t- Press ENTER to continue - ";
			_getch();
		}
		else
		{
			cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
		}

		string selecttypename_query = "select BookType, BookName from book where BookID = '" + BookID + "'";
		const char* spt = selecttypename_query.c_str();
		qstate = mysql_query(conn, spt);
		if (!qstate)
		{
			res = mysql_store_result(conn);
			while (row = mysql_fetch_row(res))
			{
				BookType = row[0];
				BookName = row[1];
			}
		}
		else
		{
			cout << "\n -- Query execution error! -- " << endl << endl;
		}

		system("cls");

		cout << "\n\n\n\t\t                            ======================================================================" << endl;
		cout << "\t\t                                                     CUSTOMER DETAILS  " << endl;
		cout << "\t\t                            ======================================================================" << endl << endl;
		cout << "\t\t                                                 Name : " << CustomerUsername << endl << endl;
		cout << "\t\t                                                 Phone Number : 0" << CustomerPhoneNumber << endl << endl;
		cout << "\t\t                                                 Address : " << CustomerAddress << endl << endl;
		cout << "\t\t                                                 Email : " << CustomerEmail << endl << endl;
		cout << "\t\t                            ======================================================================" << endl;
		cout << "\t\t                                                          INVOICE  " << endl;
		cout << "\t\t                            ======================================================================" << endl;
		cout << setw(56) << "Book Name" << setw(15) << "Quantity" << setw(23) << "Total Price (RM)" << setw(20) << "Date Purchased " << endl;
		cout << "\t\t                            ======================================================================" << endl;
		cout << setw(56) << BookName << setw(11) << j << setw(20) << k << setw(24) << dateString << endl << endl;
		cout << "\t\t                            ======================================================================" << endl;
		cout << "\n\t\t                                                THANK YOU FOR PURCHASING WITH US" << endl << endl;
		cout << "\t\t                            ======================================================================" << endl;

		cout << "\n\n\t\t                                                - Press ENTER to continue -";
		_getch();
		system("cls");

		cout << "\n\n\n\n\n\n\t\tDo you want to purchase another book ? Enter [y/Y] for yes or else to go to menu.";
		cout << "\n\n\n\t\tYour choice : ";
		cin >> choose;

		if (choose == "y" || choose == "Y")
		{
			system("cls");
			purchasebook();
		}
		else
		{
			system("cls");
			customermenu();
		}
	}
	else
	{
		cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
	}
}

void BookStore::showreport() //this function is to display report of purchase made by customer and only accessible for bookseller only
{
	system("cls");

	string choice;
	string totalsale;
	string totalquantity;

	string month;

	cout << endl << endl << endl << "                    ~ Show report ~" << endl << endl << endl << endl;

	cout << "                Please choose one option : " << endl << endl << endl;


	cout << "                1. All " << endl << endl;
	cout << "                2. Monthly " << endl << endl;
	cout << "                3. Cancel " << endl << endl << endl;
	cout << "                Your choice : ";
	cin >> choice;

	if (choice == "1")
	{
		system("cls");

		qstate = mysql_query(conn, "select o.BookID, e.BookName, sum(o.PurchaseTotalPrice), sum(o.PurchaseQuantity), e.BookQuantity from purchase as o inner JOIN book as e on e.BookID = o.BookID GROUP by BookID");

		if (!qstate)
		{
			cout << endl << endl << endl<< "\t\t============================================================================================================================================" << endl;
			cout << setw(30) << "Book ID" << setw(30) << "Book Name" << setw(30) << "Total Price (RM)" << setw(30) << "Purchase Quantity" << setw(30) << "Balance Quantity" << endl;
			cout << "\t\t============================================================================================================================================" << endl;

			res = mysql_store_result(conn);
			while (row = mysql_fetch_row(res))
			{
				cout << setw(28) << row[0] << setw(31) << row[1] << setw(27) << row[2] << setw(27) << row[3] << setw(30) << row[4] << endl << endl;
			}
			cout << "\t\t============================================================================================================================================" << endl;
		}
		else
		{
			cout << "Query Execution Problem!" << mysql_errno(conn) << endl;
		}

		string selecttypename_query = "select sum(PurchaseTotalPrice), sum(PurchaseQuantity) from purchase";
		const char* spt = selecttypename_query.c_str();
		qstate = mysql_query(conn, spt);
		if (!qstate)
		{
			res = mysql_store_result(conn);
			while (row = mysql_fetch_row(res))
			{
				totalsale = row[0];
				totalquantity = row[1];
			}
		}
		else
		{
			cout << "\n -- Query execution error! -- " << endl << endl;
		}

		cout << "\n\n\t\t                                                Total sales : RM " << totalsale;
		cout << "\n\n\t\t                                                The number of books sold : " << totalquantity;


		cout << "\n\n\n\n\n\n\n\t\t                                               - Press ENTER to continue -";
		_getch();
		system("cls");
		showreport();
	}
	else if (choice == "2")
	{
		system("cls");

		cout << "\n\n\n\t\tEnter Month ( 1 - 12 ) : ";
		cin >> month;

		string checkUser_query = "select MONTH(PurchaseDate) from purchase where MONTH(PurchaseDate) = '" + month + "'";
		const char* cu = checkUser_query.c_str();
		qstate = mysql_query(conn, cu);
		res = mysql_store_result(conn);
		row = mysql_fetch_row(res);


		if (check_number(month) == false || stoi(month) < 1 || stoi(month) > 12)
		{
			cout << "\n\n\n\t\t-------------------" << endl;
			cout << "\t\t   Invalid month  " << endl;
			cout << "\t\t-------------------" << endl;
			cout << "\n\n\n\t\t- Press ENTER to continue -";

			_getch();
			showreport();
		}
		else
		{
			if (res->row_count == 0)
			{
				cout << "\n\n\n\t\t---------------------------------------------------" << endl;
				cout << "\t\t   There are no purchase records for this month" << endl;
				cout << "\t\t---------------------------------------------------" << endl;
				cout << "\n\n\n\t\t- Press ENTER to continue - ";

				_getch();
				system("cls");
				showreport();
			}

			string monthly_query = "select o.BookID, e.BookName, sum(o.PurchaseTotalPrice), sum(o.PurchaseQuantity), e.BookQuantity from purchase as o RIGHT JOIN book as e on e.BookID = o.BookID WHERE MONTH(PurchaseDate) = '" + month + "' group by BookID";
			const char* m = monthly_query.c_str();
			qstate = mysql_query(conn, m);

			if (!qstate)
			{
				cout << endl << endl << endl << "\t\t============================================================================================================================================" << endl;
				cout << setw(30) << "Book ID" << setw(30) << "Book Name" << setw(30) << "Total Price (RM)" << setw(30) << "Purchase Quantity" << setw(30) << "Balance Quantity" << endl;
				cout << "\t\t============================================================================================================================================" << endl;

				res = mysql_store_result(conn);
				while (row = mysql_fetch_row(res))
				{
					cout << setw(28) << row[0] << setw(31) << row[1] << setw(27) << row[2] << setw(27) << row[3] << setw(30) << row[4] << endl << endl;
				}
				cout << "\t\t============================================================================================================================================" << endl;
			}
			else
			{
				cout << "\n -- Query execution error! -- " << endl << endl;
			}

			string selecttypename_query = "select sum(PurchaseTotalPrice), sum(PurchaseQuantity) from purchase where MONTH(PurchaseDate) = '" + month + "' ";
			const char* spt = selecttypename_query.c_str();
			qstate = mysql_query(conn, spt);
			if (!qstate)
			{
				res = mysql_store_result(conn);
				while (row = mysql_fetch_row(res))
				{
					totalsale = row[0];
					totalquantity = row[1];
				}
			}
			else
			{
				cout << "\n -- Query execution error! -- " << endl << endl;
			}

			cout << "\n\n\t\t                                                Total sales : RM " << totalsale;
			cout << "\n\n\t\t                                                The number of books sold : " << totalquantity;

			cout << "\n\n\n\n\n\n\n\t\t                                               - Press ENTER to continue -";
			_getch();
			system("cls");
			showreport();
		}
	}
	else if (choice == "3")
	{
		system("cls");
		booksellermenu();
	}
	else
	{
	    cout << "\n\n\n\n\t\t---------------------------------------------------------" << endl;
	    cout << "\t\t   You entered the wrong option. Please enter 1,2 or 3  " << endl;
	    cout << "\t\t---------------------------------------------------------" << endl;
	    cout << "\n\n\t\t- Press ENTER to try again - ";
	  
		_getch();
		showreport();
	}
}

bool BookStore::Email_check(string email)
{
	const regex pattern("(\\w+)(\\.|_)?(\\w*)@(\\w+)(\\.(\\w+))+");
	return regex_match(email, pattern);
}

bool BookStore::isValid(string s)
{
	// The given argument to pattern()
	// is regular expression. With the help of
	// regular expression we can validate mobile
	// number.
	// 1) Begins with 0.
	// 2) Then contains 6,7 or 8 or 9.
	// 3) Then contains 10 digits
	const regex pattern("[0-9][0-9]{9}");

	// regex_match() is used to
	// to find match between given number
	// and regular expression
	if (regex_match(s, pattern))
	{
		return true;
	}
	else
	{
		return false;
	}
}

void BookStore::viewInvoice()
{
	time_t currTime;
	tm* currTm;
	char dateString[100];
	time(&currTime);
	currTm = localtime(&currTime);
	strftime(dateString, 50, "%Y-%m-%d", currTm);

	string selectPrice_query = "select CustomerID, CustomerPhoneNumber, CustomerAddress, CustomerEmail from customer where CustomerUsername = '" + CustomerUsername + "'";
	const char* sP = selectPrice_query.c_str();
	qstate = mysql_query(conn, sP);
	if (!qstate)
	{
		res = mysql_store_result(conn);
		while (row = mysql_fetch_row(res))
		{
			CustomerID = row[0];
			CustomerPhoneNumber = row[1];
			CustomerAddress = row[2];
			CustomerEmail = row[3];
		}
	}

	//cout << "\n\t\t                            ======================================================================" << endl;
	//cout << "\t\t                                                     CUSTOMER DETAILS  " << endl;
	//cout << "\t\t                            ======================================================================" << endl << endl;
	//cout << "\t\t                                                 Name : " << CustomerUsername << endl << endl;
	//cout << "\t\t                                                 Phone Number : 0" << CustomerPhoneNumber << endl << endl;
	//cout << "\t\t                                                 Address : " << CustomerAddress << endl << endl;
	//cout << "\t\t                                                 Email : " << CustomerEmail << endl << endl ;
	cout << "\n\n\n\t\t                            ======================================================================" << endl;
	cout << "\t\t                                                      PURCHASE HISTORY  " << endl;
	cout << "\t\t                            ======================================================================" << endl;
	cout << setw(56) << "Book Name" << setw(15) << "Quantity" << setw(23) << "Total Price (RM)" << setw(20) << "Date Purchased " << endl;
	cout << "\t\t                            ======================================================================" << endl;

	string invoice_query = "select e.BookName, o.PurchaseQuantity, o.PurchaseTotalPrice, o.PurchaseDate from purchase as o right JOIN book as e on e.BookID = o.BookID where CustomerID ='" + CustomerID + "' order by PurchaseDate DESC";
	const char* m = invoice_query.c_str();
	qstate = mysql_query(conn, m);

	if (!qstate)
	{
		res = mysql_store_result(conn);
		while (row = mysql_fetch_row(res))
		{
			cout << setw(56) << row[0] << setw(11) << row[1] << setw(20) << row[2] << setw(24) << row[3] << endl << endl;
		}
	}

	cout << "\t\t                            ======================================================================" << endl;
	//cout << "\n\t\t                                                THANK YOU FOR PURCHASING WITH US" << endl << endl;
	//cout << "\t\t                            ======================================================================" << endl;

	cout << "\n\n\t\t                                                - Press ENTER to continue -";
	_getch();
	system("cls");
	customermenu();
}

bool BookStore::check_number(string[])
{
	return false;
}

