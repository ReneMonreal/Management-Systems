#include <iostream>
#include <queue>
#include <map>
#include <vector>
#include <fstream>
#include <list>
#include <limits>
#include <stdexcept>

using namespace std;


class book{
    private:
        string title, author, ISBN;
        bool avalibility;
    public:
        book() {//CONSTRUCTOR  
            this->title = "None";
            this->author =  "None";
            this->ISBN =  "None";
            this->avalibility = true; 
        }
        void newbook(string title, string author, string ISBN, bool availability) {
            this->title = title;
            this->author = author;
            this->ISBN = ISBN;
            this->avalibility = availability;
        }

        string getTitle() const {return title;}
        string getAuthor() const {return author;}
        string getISBN() const {return ISBN;}
        bool getAvalibility() const {return avalibility;}
        void borrowBook();
        void returnBook();
        void addRequest();
        void hasRequests();
        void nextRequester();
        void print();
};

class user{
    private:
        string name;
        list<string>borrowedBooks; //Track user borrowed books
    public:
        user(){//CONSTRUCTOR
            this-> name = "None";
        }
        void NewUser(string UserFullName){
            name = UserFullName;
            ofstream MyFile("users.txt", ios::app);
            if (MyFile.is_open()){
                MyFile << name<< endl;
                MyFile << '0'<< endl;;//assume new user has no books barrowed
            }
            MyFile.close();
        }
        bool CheckValidUser(string searchname){
            ifstream inputfile("users.txt");
            if (!inputfile.is_open()){
                cout<<"Error Opening User File..."<<endl;
                return false;
            }
            while(getline(inputfile,name)){
                if (name == searchname){
                    cout<<"User exists in database... "<<endl;
                    return true;
                }
                
            }
            inputfile.close();
            cout<<"User could not be found... "<<endl;
            return false;
        }
        string hasBorrowed();
        string getName();
        void borrow();
        void returnBook();
        void AppendBarrowedBooksToUserBarrowedBooksList(string username, list<string>& UserBarrowedBooks) {
            ifstream file("users.txt");
            if(!file.is_open()){
                cout<<"Error Opening File: "<<endl;
                return;
            }
            string line;
            while (getline(file, line)) {
                if (line == username) {
                    int bookCount;
                    getline(file, line);
                    bookCount = stoi(line);
                    cout << username << " is borrowing " << bookCount << " book(s):" << endl;
                    for (int i = 0; i < bookCount; ++i) {
                        getline(file, line);
                        UserBarrowedBooks.push_back(line);
                    }
                    return;
                } else {
                    // Skip borrowed books for users not being printed
                    getline(file, line); // count
                    int skipCount = stoi(line);
                    for (int i = 0; i < skipCount; ++i) getline(file, line);
                }
            }
            cout << "User not found in file.\n";
        }
        void getBorrowedBooks();
};

class Libary{
    private:
        vector<book> books;//store books
        map<string, user> users;
        book* findBookByISBN(const string& isbn);
        string bookDataIbsn, line, title, author, availability;
    public:

        Libary(){//constructor
            this->bookDataIbsn = "none";
            this->line = "none";
            this-> title = "none";
            this-> author = "none";
            this-> availability = "none";
        }



        void addBook(const book& b){
            books.push_back(b);
            ofstream MyFile("books.txt", ios::app);  // ios::app Append mode
            if (MyFile.is_open()){
                MyFile << b.getTitle() << endl;
                MyFile << b.getAuthor() << endl;
                MyFile << b.getISBN() << endl;
                MyFile<< '1' <<endl;
                MyFile.close();
                cout << "Book added and saved to file.\n";
            }
            else{
                cout<<"error opening file"<< endl;
    
            }
        };
        void removeBook();
        void listBooks();
        void registerUser();
        void borrowBook();
        void returnBook();
        void viewUserBooks();
        bool searchBook(string ibsn){
            ifstream inputFile("books.txt");//open file via reading
            bool bookfound = false;
            if (!inputFile.is_open()){
                cout<<"File could not be open 1"<< endl;
                return false;
            }
            while (getline(inputFile, title)&& getline(inputFile, author) && getline(inputFile, bookDataIbsn) && getline(inputFile, availability)){
                if (bookDataIbsn == ibsn){
                    return true;
                }
            }
            inputFile.close();
            return false;

        };
        void PrintSearchReturnBookInfo(string isbn){//print sinlge books using ibsn search
            ifstream inputfile("books.txt");
            string LocaclAvalibility;
            if (!inputfile.is_open()){
                cout<<"Error Opening File";
                return;
            }
            while(getline(inputfile, title)&& getline(inputfile, author)&& getline(inputfile,bookDataIbsn)&& getline(inputfile,LocaclAvalibility)){
                if (bookDataIbsn == isbn){
                    //cout<<"\nBook is in our Libary!"<<endl;
                    if(LocaclAvalibility == "1"){LocaclAvalibility = "Book is Avalible";}
                    else if (LocaclAvalibility == "0"){LocaclAvalibility = "Book is being barrowed";}
                    else{LocaclAvalibility = "Error Reading Avalibility";}
                    cout<<"Book title: "<< title<< " - Book Author: "<< author<< " - Book IBSN: "<< bookDataIbsn<<" - Book Avaliability: "<< LocaclAvalibility<<endl;
                    return;
                }
            }
            cout<<"Book is not in our Libary..."<<endl;
            return;

        }
        void sortBooks();
        void loadFromFiles();
        void saveToFiles();
        void printBooks(){
            ifstream inputFile("books.txt");
            string FunspecificTitle, FunspecificIBSN, FunspecificAuthor, FunspecificAvailability, FunAvalibilityStr;
            cout<<"\n========== Libary Selection =========="<< endl;
            while (getline(inputFile,  FunspecificTitle)&& getline(inputFile, FunspecificAuthor) && getline(inputFile, FunspecificIBSN) && getline(inputFile, FunspecificAvailability)){
                if (FunspecificAvailability == "1") {FunAvalibilityStr = " - Book is Avalible.";}
                else if (FunspecificAvailability == "0") {FunAvalibilityStr = " - Book is being barrowed.";}
                else {FunAvalibilityStr = " - Error reading avalibility";}


                cout<<"Book Name: "<< FunspecificTitle << " - Book Author: " << FunspecificAuthor << " - Book ISBN: " << FunspecificIBSN << FunAvalibilityStr << endl;
            }
            inputFile.close();
        }

};
bool compareByTitle(const book& a, const book& b){
    return a.getTitle() < b.getTitle();
}


        
int main(){
    int choice = 0;
    //case 1
    bool bookFoundInDatabase = false, globalAvlibility = true; //assume not found. assume avliable
    string bookname, authorname, ISBN;
    Libary libary1;
    book book1;
    //case 2
    string specificTitle, specificIBSN, specificAuthor, specificAvailability, caseAvalibility;
    bool removed = false;
    //case 3
    string FullNameUser;
    user user1;
    //Case 4
    string scearchUser, searchBook;
    bool bookAvalibility = false;
    //case 5
    string userWantingBarrow, BarrowISBN;
    //case 6
    string userWantingReturn, ReturnISBN;
    //case 7
    string searchUsersSpecificBooks;
    bool userexists;
    //case 8
    string searchISBN;
    //case 9
    bool SpecificAvailbilityBool;

    do {
        cout << "\n======= Library Menu =======\n";
        cout << "1. Add Book\n";
        cout << "2. Remove Book\n";
        cout << "3. List All Books\n";
        cout << "4. Register User\n";
        cout << "5. Borrow Book\n";
        cout << "6. Return Book\n";
        cout << "7. View User Borrowed Books\n";
        cout << "8. Search Book\n";
        cout << "9. Sort Books by Title\n";
        cout << "10. Exit\n";

        while (true){
            cout << "Enter your choice (1 ,2 , 3... 10): ";
            try{
                cin>>choice;
                if(cin.peek() != '\n'{
                    throw invalid_argument("Non-Integer Value");
            } catch(ios::failure& excpt){
                    cout<<"Non-integer Value. Please enter a number. " << endl;
                    cout<<excpt.what() <<endl;
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    choice = 0;
            } catch(invalid_argument& excpt){
                    cout<<excpt.what()<< endl;
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>:: max(), '\n\);
                    choice = 0;
            }        
            if((choice >= 1) ||(choice <= 10)){
                break;
            }
            else{
                cout<< "Invalid Input Try Again, Enter a number...\n";
                cin.clear();
                cin.ignore(1000, '\n');
            }
        }

        switch (choice) {
            case 1:{
                cin.ignore();
                cout<<"Enter the name of the book: ";
                getline(cin, bookname);
                cout<<"Enter the author of the book: ";
                getline(cin, authorname);
                cout<<"Enter the ISBN of the book: ";
                getline(cin, ISBN);
                book1 = book(); //Error Fix, Resets the book1
                book1.newbook(bookname, authorname, ISBN, true);//true automatically set the book to avalible
                libary1.addBook(book1);
                break;
            }
            case 2:{
                cout<<"Enter the ISBN number of the book you wish to remove: ";
                cin>> ISBN;
                //find book
                bookFoundInDatabase = libary1.searchBook(ISBN);
                if (bookFoundInDatabase == false){
                    cout<<"Book is not found"<<endl;
                    break;
                }

                //if book is avaliable then remove it, if not it must be removed first 
                /*create a temp file append book by book, if book != ISBN then append onto new file, new file replaces old*/
                ifstream inputFile("books.txt");//open readable
                ofstream tempFile("temp.txt");//create tempfile

                if (!inputFile.is_open() || !tempFile.is_open()){
                    cout<<"File could not be open"<< endl;
                    break;
                }
                while (getline(inputFile, specificTitle)&& getline(inputFile, specificAuthor) && getline(inputFile, specificIBSN) && getline(inputFile, specificAvailability)){
                    if (specificIBSN == ISBN){//do not append onto temp
                        if (specificAvailability == "1"){
                            cout<<"Book has been removed "<<endl;
                            removed = true;
                        }
                        else {
                            cout<<"Book is being barrowed"<< endl;
                            break;
                        }
                    }
                    else{//if not being removed append to temp file
                        tempFile << specificTitle << endl << specificAuthor << endl << specificIBSN << endl << specificAvailability << endl;
                    }
                }
                if (removed == false){
                    cout<<"Book was not removed"<<endl;
                    break;
                }
                inputFile.close();
                tempFile.close();
                remove("books.txt");
                rename("temp.txt", "books.txt");
                break;
            }
            case 3:{
                libary1.printBooks();
                break;
            }
            case 4:{ 
                cin.ignore();
                //ask for input varibales, Full Name; assume no books have been barrowed
                user1 = user();
                cout<<"Enter the name of the user: ";
                getline(cin, FullNameUser);
                user1.NewUser(FullNameUser);
                break;
            }
            case 5:{//Barrow a book
                cin.ignore();
                //Enter Which USer wants to barrow the book... aswell as whihc book they want to barrow
                cout<<"Enter the user whom wants to barrow the book: "<<endl;
                getline(cin, userWantingBarrow);
                bool userExists =false; 
                user1 = user();
                userExists = user1.CheckValidUser(userWantingBarrow);
                if(userExists==true){
                    cout<<"Enter the book you wish to barrow: "<<endl;
                    getline(cin,BarrowISBN);
                    //check if exists then check if book is avalibale "1"
                    bool BookFound = false;//assume not existant
                    libary1 = Libary();
                    BookFound = libary1.searchBook(BarrowISBN);
                    if (BookFound == true){
                        ifstream inputFile("books.txt");
                        ofstream tempFile("temp.txt");
                        bool isAvailable = false;

                        while (getline(inputFile, specificTitle) && getline(inputFile, specificAuthor) && getline(inputFile, specificIBSN) && getline(inputFile, specificAvailability)) {
                            if (specificIBSN == BarrowISBN) {
                                bool availableBool = (specificAvailability == "1");
                                book1.newbook(specificTitle, specificAuthor, specificIBSN, availableBool);
                                isAvailable = book1.getAvalibility();
                                
                                if (isAvailable){//if book is avliable to be barrowed
                                    specificAvailability = "0";//make book barrowed
                                    tempFile<<specificTitle<< endl;
                                    tempFile<<specificAuthor<<endl;
                                    tempFile<<specificIBSN<<endl;
                                    tempFile<<specificAvailability<<endl;
                                    //update the users file to resemble changes
                                    ifstream UserInputFile("users.txt");
                                    ofstream UserTempFile("Utemp.txt");
                                    string userPlaceHolder, bookPlaceholder;
                                    int BarrowingNumBooks;
                                    bool userFound = false;
                                    while(getline(UserInputFile, userPlaceHolder)){
                                        if (userPlaceHolder == userWantingBarrow){
                                            UserTempFile << userWantingBarrow <<endl;
                                            string line;
                                            getline(UserInputFile, line);
                                            BarrowingNumBooks = stoi(line);//stoi converts string into integer
                                            UserTempFile <<(BarrowingNumBooks + 1)<<endl;
                                            UserTempFile<< BarrowISBN;
                                            for(int i = 0; i <= BarrowingNumBooks; ++i){
                                                getline(UserInputFile, bookPlaceholder);
                                                UserTempFile << bookPlaceholder<<endl;
                                            }
                                        }
                                        else{
                                            UserTempFile<<userPlaceHolder<<endl;
                                        }
                                    }
                                    cout<<userWantingBarrow<< " is now barrowing the said book"<<endl;
                                    UserInputFile.close();
                                    UserTempFile.close();
                                    remove("users.txt");
                                    rename("Utemp.txt", "users.txt");

                                }
                            }
                            else{
                                tempFile<<specificTitle<<endl;
                                tempFile<<specificAuthor<<endl;
                                tempFile<<specificIBSN<<endl;
                                tempFile<<specificAvailability<<endl;
                            }

                        }

                        inputFile.close();
                        tempFile.close();
                        remove("books.txt");
                        rename("temp.txt", "books.txt");

                    }
                    else{
                        cout<<"Book does not exist"<<endl;
                        break;
                    }
                }
                else{
                    cout<<"User does not exist..."<<endl;
                    break;
                }
                    

                    //turn aval;ibale into not avliable "0"
                    
                    //access users.txt read each line

                    //if line == uservaribale

                        //getline count

                        //for x varibale count getline: for each book they've barrowed

                        ///Paste the info into temp file, past count +1 and book they wabnt to barrow 


                //else< out bnook is already being barrowed

                break;
            }
            case 6:{
                cin.ignore();
                cout<<"Enter the name of the user who wishes to return a book: "<< endl;
                getline(cin, userWantingReturn);
                cout<<"Enter the ISBN of the book you wish to return: "<<endl;
                getline(cin, ReturnISBN);
                ifstream readFile("users.txt");
                ofstream tempFile("temp.file");
                string userPlaceHolder, bookPlaceholder;
                int BarrowingNumBooks;
                bool userFound = false;
                //Update the users.txt file, remove x book
                while(getline(readFile, userPlaceHolder)){
                    if (userPlaceHolder == userWantingReturn){
                        userFound = true;
                        tempFile << userWantingReturn << endl;
                        string line;
                        getline(readFile, line);
                        BarrowingNumBooks = stoi(line);//stoi convert string into integer
                        tempFile << (BarrowingNumBooks - 1) << endl;
                        for (int i = 0; i < BarrowingNumBooks; ++i){
                            getline(readFile, bookPlaceholder);
                            if (bookPlaceholder == ReturnISBN)
                            {
                                continue;
                            }
                            else{
                                tempFile << bookPlaceholder << endl;
                            }
                        }
                    }
                    else{
                        tempFile << userPlaceHolder << endl;
                    }
                    
                }
                if (userFound == false){
                    cout<<"User was not found, try again..."<<endl;
                }
                readFile.close();
                tempFile.close();
                remove("users.txt");
                rename("temp.file", "users.txt");

                //NEXT swap the "0" into a "1" meaning it is avaiblie from x book
                ifstream inputFile("books.txt");
                ofstream temp2File("temp.txt");
                while(getline(inputFile, specificTitle) && getline(inputFile, specificAuthor) && getline(inputFile, specificIBSN) && getline(inputFile, specificAvailability)){
                    if (specificIBSN == ReturnISBN){
                        specificAvailability = "1";
                        temp2File << specificTitle<<endl;
                        temp2File << specificAuthor<<endl;
                        temp2File << specificIBSN <<endl;
                        temp2File << specificAvailability<< endl;
                    }
                    else{
                        temp2File<<specificTitle<<endl;
                        temp2File<<specificAuthor<<endl;
                        temp2File<<specificIBSN<<endl;
                        temp2File<<specificAvailability<<endl;
                    }
                }
                inputFile.close();
                temp2File.close();
                remove("books.txt");
                rename("temp.txt", "books.txt");
                break;
            }

            case 7:{
                list<string> UserBorrowedBooks;
                cin.ignore();
                cout<<"Enter the User you wish to see what books they've barrorwed: ";
                getline(cin, searchUsersSpecificBooks);
                userexists = user1.CheckValidUser(searchUsersSpecificBooks);
                if (userexists == true){
                    user1.AppendBarrowedBooksToUserBarrowedBooksList(searchUsersSpecificBooks, UserBorrowedBooks);
                }
                list<string>::iterator it;
                for(it = UserBorrowedBooks.begin();it != UserBorrowedBooks.end(); ++it){
                    libary1.PrintSearchReturnBookInfo(*it);
                }

                


                break;
            }
            case 8:{
                libary1 = Libary();
                cin.ignore();
                cout<<"Enter the ISBN of the book you wish to find: ";
                getline(cin, searchISBN);
                libary1.PrintSearchReturnBookInfo(searchISBN);
            

                break;
            }
            case 9:{
                ifstream inputFile("books.txt");
                ofstream tempfile("temp.txt");
                list<book> unsortedBookList;
                if (!inputFile.is_open() || !tempfile.is_open()){
                    cout<<"Trouble opening file or files"<<endl;
                    break;
                }
                //each books put into a list
                while(getline(inputFile, specificTitle)&&getline(inputFile, specificAuthor)&&getline(inputFile, specificIBSN)&& getline(inputFile, specificAvailability)){
                    book tempBook;
                    SpecificAvailbilityBool = (specificAvailability == "1");
                    tempBook.newbook(specificTitle, specificAuthor, specificIBSN, SpecificAvailbilityBool);
                    unsortedBookList.push_back(tempBook);
                }

                // sort by title
                unsortedBookList.sort(compareByTitle);

                list<book>::iterator it;
                for(it = unsortedBookList.begin(); it != unsortedBookList.end(); ++it){
                    tempfile << it->getTitle() << endl;
                    tempfile << it->getAuthor() << endl;
                    tempfile << it->getISBN() << endl;
                    tempfile << (it->getAvalibility() ? "1" : "0") << endl;
                }

                cout<<"Books Have been sorted by Title... "<<endl;
                inputFile.close();
                tempfile.close();
                remove("books.txt");
                rename("temp.txt","books.txt");
                break;
            }
            case 10:{
                cout << "Exiting program. Changes saved.\n";
                break;
            }
            default:{
                cout << "Invalid choice. Try again.\n";
                
            }
        }
    } while (choice != 10);


    return 0;
}
