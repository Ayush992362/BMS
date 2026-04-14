#include <iostream>
#include <fstream>
#include <iomanip>
using namespace std;
struct Account {
    int accNo;
    char name[50];
    char type[10]; 
    float balance;
};
void createAccount() {
    Account acc;
    ofstream file("bank.dat", ios::binary | ios::app);
    cout << "\nEnter Account Number: "; cin >> acc.accNo;
    cout << "Enter Name: "; cin >> acc.name;
    cout << "Enter Type (Savings/Current): "; cin >> acc.type;
    cout << "Enter Initial Balance: "; cin >> acc.balance;
    file.write((char*)&acc, sizeof(acc));
    file.close();
    cout << "Account Created Successfully\n";
}
void displayAll() {
    Account acc;
    ifstream file("bank.dat", ios::binary);
    cout << "\n" << left << setw(10) << "Acc No"
         << setw(20) << "Name"
         << setw(12) << "Type"
         << "Balance\n";
    cout << string(50, '-') << "\n";
    while (file.read((char*)&acc, sizeof(acc)))
        cout << setw(10) << acc.accNo
             << setw(20) << acc.name
             << setw(12) << acc.type
             << acc.balance << "\n";
    file.close();
}
void deposit() {
    int accNo; float amt;
    cout << "\nEnter Account Number: "; cin >> accNo;
    cout << "Enter Amount to Deposit: "; cin >> amt;
    fstream file("bank.dat", ios::binary | ios::in | ios::out);
    Account acc;
    file.seekg(0);
    while (file.read((char*)&acc, sizeof(acc))) {
        if (acc.accNo == accNo){
            acc.balance += amt;
            file.seekp(-sizeof(acc), ios::cur);
            file.write((char*)&acc, sizeof(acc));
            cout << "Deposited: New Balance: " << acc.balance << "\n";
            file.close(); return;
        }
    }
    cout << "Account not found\n";
    file.close();
}
void withdraw() {
    int accNo; float amt;
    cout << "\nEnter Account Number: "; cin >> accNo;
    cout << "Enter Amount to Withdraw: "; cin >> amt;
    fstream file("bank.dat", ios::binary | ios::in | ios::out);
    Account acc;
    file.seekg(0);
    while (file.read((char*)&acc, sizeof(acc))) {
        if (acc.accNo == accNo) {
            if (acc.balance < amt) { cout << "Insufficient Balance\n"; file.close(); return; }
            acc.balance -= amt;
            file.seekp(-sizeof(acc), ios::cur);
            file.write((char*)&acc, sizeof(acc));
            cout << "Withdrawn: New Balance: " << acc.balance << "\n";
            file.close(); return;
        }
    }
    cout << "Account not found\n";
    file.close();
}
void checkBalance() {
    int accNo;
    cout << "\nEnter Account Number: "; cin >> accNo;
    ifstream file("bank.dat", ios::binary);
    Account acc;
    while (file.read((char*)&acc, sizeof(acc))) {
        if (acc.accNo == accNo) {
            cout << "Name: " << acc.name << "\n"
                 << "Type: " << acc.type << "\n"
                 << "Balance: " << acc.balance << "\n";
            file.close(); return;
        }
    }
    cout << "Account not found\n";
    file.close();
}
int main() {
    int choice;
    do {
        cout << "\nBANK MANAGEMENT SYSTEM \n"
             << "1.Create Account\n"
             << "2.Deposit\n"
             << "3.Withdraw\n"
             << "4.Check Balance\n"
             << "5.Display All Accounts\n"
             << "0.Exit\n"
             << "Choice:";
        cin >> choice;
        switch (choice) {
            case 1: createAccount(); break;
            case 2: deposit();       break;
            case 3: withdraw();      break;
            case 4: checkBalance();  break;
            case 5: displayAll();    break;
            case 0: cout << "Goodbye!\n"; break;
            default: cout << "Invalid choice!\n";
        }
    } while (choice != 0);
    return 0;
}