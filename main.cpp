#include <iostream>
#include <fstream>

using namespace std;

class Registering{
    public:
        void setAccount(string username, string password, string email){
            this-> username = username;
            this->password = password;
            this->email = email;
        }

        bool UnqiueUsername(const string& username){
            string datauser;
            ifstream MyReadFile;
            MyReadFile.open("data.txt", ios:: in);

            while(getline(MyReadFile,datauser,',')){
                if (datauser == username){
                    MyReadFile.close();
                    return false;
                }
            }
            MyReadFile.close();
            return true;
                        
        }

        void SaveAccountData(){

            //std::ios::app - “append”; moves the write pointer to the end of the file
            ofstream MyFile("data.txt", std::ios::app);
            //run if file is create/found
            if (MyFile){
                MyFile << username <<","<<password<<","<<email<<endl;
                return;
            }
            else{cout<<"Trouble Saving Account Data to Database"<<endl;}
            MyFile.close();
        }
    private:
        string username, password, email;
};

class LogingIn{
    public:
        void setCredentials(string username, string password){
            this-> username = username;
            this-> password = username;
        }
        bool checkLoginCredentials(string username, string password){
            string datauser, datapassword;
            ifstream MyReadFile;
            MyReadFile.open("data.txt", ios::in);
            getline(MyReadFile, datauser, ',');
            getline(MyReadFile, datapassword, ',');
            if (datauser == username){
                if (datapassword == password){
                    cout<<"Login Successfull"<<endl;
                    return true;
                }
                else{
                    cout<<"Password is incorrect...";
                    return false;
                }
            }
            else{
                cout<<"Username is incorrect...";
                return false;
            }
        }
    private:
        string username, password;
};

int main(){
    //Variables
    int choice;
    string username, password, email;
    bool quit = false;
    bool UnqiueUsername = true;
    bool accessGranted = false;

    Registering temp;
    LogingIn logInTemp;


    do{
        cout<<"\n__________________________________________"<<endl;
        cout<<"|    What would you like to do today?    |"<<endl;
        cout<<"|    1.) Register                        |"<<endl;
        cout<<"|    2.) Login                           |"<<endl;
        cout<<"|    3.) Quit Program                    |"<<endl;
        cout<<"------------------------------------------"<<endl;
        //add this
        
        while (true) {
            std::cout << "Enter 1, 2, or 3: ";
            if (std::cin >> choice && (choice == 1 || choice == 2 || choice == 3)) {
                break;                       // valid int received
            }
            std::cout << "Invalid input. Please enter a number.\n";
            std::cin.clear();                // clear failbit
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // discard rest of line
        }


        switch(choice){

            case 1:
                cin.ignore();
                cout<<"\nEnter a Username: ";
                getline(cin, username);
                cout<<"Enter a Password: ";
                getline(cin, password);
                cout<<"Enter an Email: ";
                getline(cin, email);

                //Action
                temp.setAccount(username, password, email);
                UnqiueUsername = temp.UnqiueUsername(username);
                if (UnqiueUsername){
                    temp.SaveAccountData();
                    cout<<"Account has been created"<<endl;
                }
                else{cout<<"\nUsername is taken, try again...";}

                break;;
            case 2:
                cin.ignore();
                cout<<"\nEnter your Username; ";
                getline(cin, username);
                cout<<"Enter your password; ";
                getline(cin, password);

                //action
                logInTemp.setCredentials(username, password);
                accessGranted = logInTemp.checkLoginCredentials(username, password);
                if (accessGranted){
                    cout<<"Logged in Succesfully"<<endl;
                }
                else {cout<<"\nFailed to log in...";}


                break;
            case 3://finished
                cout<<"\n ****** Quiting Program ****** "<<endl;
                quit = true;
                break;
            default:
                cout<<"Please enter a valid input"<<endl;
                break;; //might neet to change
        }
    } while (!quit);

    



    return 0;
}