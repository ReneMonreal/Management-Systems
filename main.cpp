#include <iostream>
#include <queue>
#include <map>
#include <vector>
#include <fstream>
#include <list>

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
        void newbook(string title, string author, string ISBN) {
            this->title = title;
            this->author = author;
            this->ISBN = ISBN;
            this->avalibility = true; //assume avalibility
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
        string hasBorrowed();
        string getName();
        void borrow();
        void returnBook();
        void printBorrowed();
        void getBorrowedBooks();
};

class Libary{
    private:
        vector<book> books;//store books
        map<string, user> users;
        book* findBookByISBN(const string& isbn);
    public:

        Libary(){

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
            string bookDataIbsn, line, title, author, availability;
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


        
int main(){
    int choice;
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
    //case 8
    string searchISBN;
    
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
        cout << "9. Sort Books\n";
        cout << "10. Exit\n";

        while (true){
            cout << "Enter your choice (1 ,2 , 3... 10): ";
            cin>>choice;
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
                book1.newbook(bookname, authorname, ISBN);
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
                        if (specificAvailability == "0"){
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
            case 5:{

                //Barrowing book
                /* 1.) Ask for user
                 
                2.) Ask for isbn
                3.)Check if book is aviable
                    book1.getAvalibility(ISBN)
                4.) if avalibale set user to barrowing the book
                */

                
                break;
            }
            case 6:{
                break;
            }
            case 7:{
                break;
            }
            case 8:{
                break;
            }
            case 9:{
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