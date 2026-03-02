#include <iostream>
#include <fstream>
#include <vector>
using namespace std;

class BankAccount {
private:
    int accountNumber;
    string name;
    double balance;

public:
    // Constructor
    BankAccount(int accNo, string accName, double accBalance) {
        accountNumber = accNo;
        name = accName;
        balance = accBalance;
    }

    int getAccountNumber() const {
        return accountNumber;
    }

    double getBalance() const {
        return balance;
    }

    void deposit(double amount) {
        if (amount <= 0) {
            cout << "Invalid deposit amount.\n";
            return;
        }
        balance += amount;
        cout << "Deposit Successful. Updated Balance: " << balance << endl;
    }

    void withdraw(double amount) {
        if (amount <= 0) {
            cout << "Invalid withdrawal amount.\n";
            return;
        }
        if (amount > balance) {
            cout << "Insufficient Balance.\n";
            return;
        }
        balance -= amount;
        cout << "Withdrawal Successful. Updated Balance: " << balance << endl;
    }

    void display() const {
        cout << "\nAccount Number: " << accountNumber << endl;
        cout << "Account Holder: " << name << endl;
        cout << "Balance: " << balance << endl;
    }

    // Save to file
    void saveToFile(ofstream &file) const {
        file << accountNumber << " " << name << " " << balance << endl;
    }
};

// Load accounts from file
vector<BankAccount> loadAccounts() {
    vector<BankAccount> accounts;
    ifstream file("accounts.txt");

    int accNo;
    string name;
    double balance;

    while (file >> accNo >> name >> balance) {
        accounts.push_back(BankAccount(accNo, name, balance));
    }

    file.close();
    return accounts;
}

// Save all accounts back to file
void saveAllAccounts(const vector<BankAccount>& accounts) {
    ofstream file("accounts.txt");
    for (const auto &acc : accounts) {
        acc.saveToFile(file);
    }
    file.close();
}

int main() {
    vector<BankAccount> accounts = loadAccounts();
    int choice;

    do {
        cout << "\n===== Banking System =====\n";
        cout << "1. Create Account\n";
        cout << "2. Deposit\n";
        cout << "3. Withdraw\n";
        cout << "4. View Account\n";
        cout << "5. Exit\n";
        cout << "Enter Choice: ";
        cin >> choice;

        if (choice == 1) {
            int accNo;
            string name;
            double balance;

            cout << "Enter Account Number: ";
            cin >> accNo;

            // Check duplicate
            bool exists = false;
            for (auto &acc : accounts) {
                if (acc.getAccountNumber() == accNo) {
                    exists = true;
                    break;
                }
            }

            if (exists) {
                cout << "Account Number already exists.\n";
                continue;
            }

            cout << "Enter Account Holder Name: ";
            cin >> name;

            cout << "Enter Initial Balance: ";
            cin >> balance;

            accounts.push_back(BankAccount(accNo, name, balance));
            saveAllAccounts(accounts);

            cout << "Account Created Successfully!\n";
        }

        else if (choice == 2) {
            int accNo;
            double amount;
            cout << "Enter Account Number: ";
            cin >> accNo;

            bool found = false;
            for (auto &acc : accounts) {
                if (acc.getAccountNumber() == accNo) {
                    cout << "Enter Deposit Amount: ";
                    cin >> amount;
                    acc.deposit(amount);
                    saveAllAccounts(accounts);
                    found = true;
                    break;
                }
            }

            if (!found)
                cout << "Account Not Found.\n";
        }

        else if (choice == 3) {
            int accNo;
            double amount;
            cout << "Enter Account Number: ";
            cin >> accNo;

            bool found = false;
            for (auto &acc : accounts) {
                if (acc.getAccountNumber() == accNo) {
                    cout << "Enter Withdrawal Amount: ";
                    cin >> amount;
                    acc.withdraw(amount);
                    saveAllAccounts(accounts);
                    found = true;
                    break;
                }
            }

            if (!found)
                cout << "Account Not Found.\n";
        }

        else if (choice == 4) {
            int accNo;
            cout << "Enter Account Number: ";
            cin >> accNo;

            bool found = false;
            for (auto &acc : accounts) {
                if (acc.getAccountNumber() == accNo) {
                    acc.display();
                    found = true;
                    break;
                }
            }

            if (!found)
                cout << "Account Not Found.\n";
        }

        else if (choice == 5) {
            cout << "Exiting...\n";
        }

        else {
            cout << "Invalid Choice.\n";
        }

    } while (choice != 5);

    return 0;
}
