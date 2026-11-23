#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <iomanip>
#include <limits>

using namespace std;

// Account Class
class Account
{
public:
    int accountNumber;
    string name;
    double balance;
};

// Bank Management Class
class Bank
{
private:
    vector<Account> accounts;

public:

    // Load accounts from file
    void loadAccounts()
    {
        accounts.clear();

        ifstream file("accounts.txt");

        string line;

        while (getline(file, line))
        {
            stringstream ss(line);

            Account a;
            string number, balance;

            getline(ss, number, '|');
            getline(ss, a.name, '|');
            getline(ss, balance, '|');

            stringstream numberStream(number);
            stringstream balanceStream(balance);

            if (numberStream >> a.accountNumber &&
                balanceStream >> a.balance)
            {
                accounts.push_back(a);
            }
        }

        file.close();
    }

    // Save accounts to file
    void saveAccounts()
    {
        ofstream file("accounts.txt");

        for (int i = 0; i < accounts.size(); i++)
        {
            file << accounts[i].accountNumber << "|"
                 << accounts[i].name << "|"
                 << fixed << setprecision(2)
                 << accounts[i].balance << endl;
        }

        file.close();
    }

    // Create Account
    void createAccount()
    {
        Account a;

        cout << "\nEnter Account Number: ";
        cin >> a.accountNumber;

        for (int i = 0; i < accounts.size(); i++)
        {
            if (accounts[i].accountNumber == a.accountNumber)
            {
                cout << "\nAccount Already Exists!\n";
                return;
            }
        }

        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        cout << "Enter Customer Name: ";
        getline(cin, a.name);

        cout << "Enter Initial Balance: ";
        cin >> a.balance;

        if (!cin || a.balance < 0)
        {
            cout << "\nInvalid Balance!\n";
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return;
        }

        accounts.push_back(a);

        saveAccounts();

        cout << "\nAccount Created Successfully!\n";
    }

    // Deposit Money
    void deposit()
    {
        int number;
        double amount;

        cout << "\nEnter Account Number: ";
        cin >> number;

        for (int i = 0; i < accounts.size(); i++)
        {
            if (accounts[i].accountNumber == number)
            {
                cout << "Enter Deposit Amount: ";
                cin >> amount;

                if (!cin || amount <= 0)
                {
                    cout << "\nInvalid Amount!\n";
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    return;
                }

                accounts[i].balance += amount;

                saveAccounts();

                cout << "\nAmount Deposited Successfully!\n";

                cout << "Updated Balance: "
                     << fixed << setprecision(2)
                     << accounts[i].balance << endl;

                return;
            }
        }

        cout << "\nAccount Not Found!\n";
    }

    // Withdraw Money
    void withdraw()
    {
        int number;
        double amount;

        cout << "\nEnter Account Number: ";
        cin >> number;

        for (int i = 0; i < accounts.size(); i++)
        {
            if (accounts[i].accountNumber == number)
            {
                cout << "Enter Withdrawal Amount: ";
                cin >> amount;

                if (!cin || amount <= 0)
                {
                    cout << "\nInvalid Amount!\n";
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    return;
                }

                if (amount > accounts[i].balance)
                {
                    cout << "\nInsufficient Balance!\n";
                    return;
                }

                accounts[i].balance -= amount;

                saveAccounts();

                cout << "\nWithdrawal Successful!\n";

                cout << "Remaining Balance: "
                     << fixed << setprecision(2)
                     << accounts[i].balance << endl;

                return;
            }
        }

        cout << "\nAccount Not Found!\n";
    }

    // Check Balance
    void checkBalance()
    {
        int number;

        cout << "\nEnter Account Number: ";
        cin >> number;

        for (int i = 0; i < accounts.size(); i++)
        {
            if (accounts[i].accountNumber == number)
            {
                cout << "\nAccount Number: "
                     << accounts[i].accountNumber;

                cout << "\nCustomer Name: "
                     << accounts[i].name;

                cout << "\nAvailable Balance: "
                     << fixed << setprecision(2)
                     << accounts[i].balance << endl;

                return;
            }
        }

        cout << "\nAccount Not Found!\n";
    }

    // Display All Accounts
    void displayAccounts()
    {
        if (accounts.empty())
        {
            cout << "\nNo Accounts Available!\n";
            return;
        }

        cout << "\n========== CUSTOMER DETAILS ==========\n";

        for (int i = 0; i < accounts.size(); i++)
        {
            cout << "\nAccount Number: "
                 << accounts[i].accountNumber;

            cout << "\nCustomer Name: "
                 << accounts[i].name;

            cout << "\nBalance: "
                 << fixed << setprecision(2)
                 << accounts[i].balance;

            cout << "\n--------------------------------------\n";
        }
    }
};

// Main Function
int main()
{
    Bank bank;

    bank.loadAccounts();

    int choice;

    do
    {
        cout << "\n====================================";
        cout << "\n       BANK MANAGEMENT SYSTEM";
        cout << "\n====================================";

        cout << "\n1. Create Account";
        cout << "\n2. Deposit Money";
        cout << "\n3. Withdraw Money";
        cout << "\n4. Check Balance";
        cout << "\n5. Display All Accounts";
        cout << "\n6. Exit";

        cout << "\n====================================";

        cout << "\nEnter Your Choice: ";
        cin >> choice;

        switch (choice)
        {
            case 1:
                bank.createAccount();
                break;

            case 2:
                bank.deposit();
                break;

            case 3:
                bank.withdraw();
                break;

            case 4:
                bank.checkBalance();
                break;

            case 5:
                bank.displayAccounts();
                break;

            case 6:
                cout << "\nThank You for Using Bank Management System!\n";
                break;

            default:
                cout << "\nInvalid Choice! Try Again.\n";
        }

    } while (choice != 6);

    return 0;
}