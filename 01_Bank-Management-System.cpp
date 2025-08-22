// Header Files
#include <iostream>
#include <fstream>
#include <cctype>
#include <iomanip>
using namespace std;

// Class used
class account{
    int acno;
    char name[50];
    int deposit;
    char type;
    public:
    void create_account(); // Function to get user data
    void show_account() const; // Function to show data on screen
    void modify(); // Function to add new data
    void dep(int); // Function to accept amt and add to balance amt
    void draw(int); // Function to accept amt and subtract to balance amt
    void report() const; // Function to show data in tabular format
    int retacno() const; // Function to return account number
    int retdeposit() const; // Function to return balance amount
    char rettype() const; // Function to return type of account
};

void account::create_account(){
    cout << "\nEnter the Account No.: ";
    cin >> acno;
    cout << "\nEnter the Name of the Account Holder: ";
    cin.ignore();
    cin.getline(name,50);
    cout << "\nEnter Type of Account (C/S): ";
    cin >> type;
    type = toupper(type);
    cout << "\nEnter the Initial Amount (>=500 for Saving and >= 1000 for Current): ";
    cin >> deposit;
    cout << "\n\nAccount Created";
}

void account::show_account() const{
    cout << "\nAccount No.: " << acno;
    cout << "\nAccount Holder Name: ";
    cout << name;
    cout << "\nType of Account: " << type;
    cout << "\nBalance Amount: " << deposit;
}

void account::modify(){
    cout << "\nAccount No.: " << acno;
    cout << "\nModify Account Holder Name: ";
    cin.ignore();
    cin.getline(name,50);
    cout << "\nModify Type of Account: ";
    cin >> type;
    type = toupper(type);
    cout << "\nModify Balance Amount: ";
    cin >> deposit;
}

void account::dep(int x){
    deposit += x;
}

void account::draw(int x){
    deposit -= x;
}

void account::report() const{
    cout << acno << setw(10) << "" << name << setw(10) << "" << type << setw(6) << deposit << endl;
}

int account::retacno() const{
    return acno;
}

int account::retdeposit() const{
    return deposit;
}

char account::rettype() const{
    return type;
}

// Function Declaration
void write_account(); // Function to write records in Binary File.
void display_sp(int); // Function to Display Account details given by user.
void modify_account(int); // Function to Modify record of file.
void delete_account(int); // Function to Delete record of file.
void display_all(); // Function to Display all Account Details.
void deposit_withdraw(int, int); // Function to Deposit/Withdraw Amount of given account.
void intro(); // Introductory screen function

// Main Function of Program
int main(){
    char ch;
    int num;
    intro();
    do{
        system("cls");
        cout << "\n\n\n\tMAIN MENU";
        cout << "\n\n\t01. NEW ACCOUNT";
        cout << "\n\n\t02. DEPOSIT AMOUNT";
        cout << "\n\n\t03. WITHDRAW AMOUNT";
        cout << "\n\n\t04. BALANCE ENQUIRY";
        cout << "\n\n\t05. ALL ACOUNT HOLDER LIST";
        cout << "\n\n\t06. CLOSE AN ACCOUNT";
        cout << "\n\n\t07. MODIFY AN ACCOUNT";
        cout << "\n\n\t08. EXIT";
        cout << "\n\n\tSelect Your Option (1-8)";
        cin >> ch;
        system("cls");
        switch (ch){
            case 1:
            write_account();
            break;

            case 2:
            cout << "\n\n\tEnter the Account Number: ";
            cin >> num;
            deposit_withdraw(num, 1);
            break;

            case 3:
            cout << "\n\n\tEnter the Account Number: ";
            cin >> num;
            display_sp(num);
            break;

            case 5:
            display_all();
            break;

            case 6:
            cout << "\n\n\tEnter the Account Number: ";
            cin >> num;
            delete_account(num);
            break;

            case 7:
            cout << "\n\n\tEnter the Account Number: ";
            cin >> num;
            modify_account(num);
            break;

            case 8:
            cout << "\n\n\tThanks for using Bank Management System";
            break;
        
            default:
            cout <<"\a";
        }
        cin.ignore();
        cin.get();
    }
    while (ch!=8);
    return 0;
}

// Function to write in File
void write_function(){
    account ac;
    ofstream outFile;
    outFile.open("account.dat",ios::binary|ios::app);
    ac.create_account();
    outFile.write(reinterpret_cast<char*>(&ac), sizeof(account));
    outFile.close();
}

// Function to read specific records from file
void display_sp(int n){
    account ac;
    bool flag=false;
    ifstream inFile;
    inFile.open("account.dat",ios::binary);
    if(!inFile){
        cout << "File could not be open !! Press any Key...";
        return;
    }
    cout << "\nBALANCE DETAILS\n";
    while (inFile.read(reinterpret_cast<char*>(&ac),sizeof(account)))
    {
        if(ac.retacno()==n){
            ac.show_account();
            flag=true;
        }
    }
    inFile.close();
    if(flag==false)
    cout << "\n\nAccount Number does not Exist";
}

// Function to Modify Record of File
void modify_account(int n){
    bool found=false;
    account ac;
    fstream File;
    File.open("account.dat",ios::binary|ios::in|ios::out);
    if (!File){
        cout << "File couldn't be open!! Press any Key...";
        return;
    } while (!File.eof() && found == false){
        File.read(reinterpret_cast<char*>(&ac), sizeof(account));
        if (ac.retacno() == n){
            ac.show_account();
            cout << "\n\nEnter the New Details of Account" << endl;
            ac.modify();
            int pos = (-1)*static_cast<int>(sizeof(account));
            File.seekp(pos,ios::cur);
            File.write(reinterpret_cast<char*>(&ac),sizeof(account));
            cout << "\n\n\t Record Updated";
            found = true;
        }
    }

    File.close();
    if (found == false)
    cout << "\n\n Record Not Found";
}

// Function to Delete record of File
void delete_account(int n){
    account ac;
    ifstream inFile;
    ofstream outFile;
    inFile.open("account.dat",ios::binary);
    if(!inFile){
        cout << "FIle coudn't be open!! Press any Key...";
        return;
    }
    outFile.open("Temp.dat",ios::binary);
    inFile.seekg(0,ios::beg);
    while (inFile.read(reinterpret_cast<char*>(&ac),sizeof(account)))
    {
        if(ac.retacno() != n){
            outFile.write(reinterpret_cast<char*>(&ac),sizeof(account));
        }
    }
    inFile.close();
    outFile.close();
    remove("account.dat");
    rename("Temp.dat", "account.dat");
    cout << "\n\n\t Record Deleted...";
}

// Function to Display all Accounts Deposit List
void display_all(){
    account ac;
    ifstream inFile;
    inFile.open("account.dat", ios::binary);
    if (!inFile) {
        cout << "File counld not be open !! Press any Key...";
        return;
    }
    cout << "\n\n\t\tACCOUNT HOLDER LIST\n\n";
    cout << "=====================================\n";
    cout << "A/c No.    NAME        Type Balance\n";
    cout << "=====================================";
    while (inFile.read(reinterpret_cast<char *> (&ac), sizeof(account))){
        ac.report();
    }
    inFile.close();
}

// Function to deposit and withdraw amounts
void deposit_withdraw (int n, int option){
    int amt;
    bool found = false;
    account ac;
    fstream File;
    File.open("account.dat", ios::binary | ios::in | ios::out);
    if (!File){
        cout << "File could not be open !! Press any Key...";
        return;
    }
    while (!File.eof() && found == false){
        File.read(reinterpret_cast<char *> (&ac), sizeof(account));
        if (ac.retacno() == n){
            ac.show_account();
            if (option == 1){
                cout << "\n\n\tTO DEPOSITE AMOUNT";
                cout << "\n\nEnter The amount to be deposited";
                cin >> amt;
                ac.dep(amt);
            } if (option == 2){
                cout << "\n\n\tTO WITHDRAW AMOUNT";
                cout << "\n\nEnter The amount to be withdraw";
                cin >> amt;
                int bal = ac.retdeposit() - amt;
                if ((bal<500 && ac.rettype() == 'S') || (bal<1000 && ac.rettype() == 'C')){
                    cout << "Insufficient Balance";
                } else {
                    ac.draw(amt);
                }
            }
            int pos = (-1)*static_cast<int>(sizeof(ac));
            File.seekp(pos, ios::cur);
            File.write(reinterpret_cast<char *> (&ac), sizeof(account));
            cout << "\n\n\t Record Updated";
            found = true;
        }
    }
    File.close();
    if (found == false){
        cout << "\n\n Record Not Found";
    }
}

// Introduction Function
void intro(){
    cout << "\n\n\n\t BANK";
    cout << "\n\n\tMANAGEMENT";
    cout << "\n\n\t SYSTEM";
    cout << "\n\n\n\nMADE BY: SAMARTH AGARWAL";
    cin.get();
}


// PROJECT ENDS
