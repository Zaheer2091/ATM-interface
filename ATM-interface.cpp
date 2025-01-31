#include <iostream>
#include <fstream>
#include <string>

using namespace std;

// Account Class
class Account {
private:
    string accountNumber;
    string pin;
    double balance;

public:
    Account(string accNum, string accPin, double bal) {
        accountNumber = accNum;
        pin = accPin;
        balance = bal;
    }

    bool verifyPIN(string enteredPIN) {
        return enteredPIN == pin;
    }

    void displayBalance() {
        cout << "Current Balance: $" << balance << endl;
    }

    void deposit(double amount) {
        balance += amount;
        cout << "Deposit Successful! New Balance: $" << balance << endl;
        saveToFile();
    }

    bool withdraw(double amount) {
        if (amount > balance) {
            cout << "Insufficient funds!" << endl;
            return false;
        }
        balance -= amount;
        cout << "Withdrawal Successful! New Balance: $" << balance << endl;
        saveToFile();
        return true;
    }

    void changePIN(string newPIN) {
        pin = newPIN;
        cout << "PIN Changed Successfully!" << endl;
        saveToFile();
    }

    void saveToFile() {
        ofstream file(accountNumber + ".txt");
        file << accountNumber << endl;
        file << pin << endl;
        file << balance << endl;
        file.close();
    }

    static Account loadFromFile(string accNum) {
        ifstream file(accNum + ".txt");
        string pin;
        double balance;
        if (file) {
            file >> accNum >> pin >> balance;
            return Account(accNum, pin, balance);
        }
        cout << "Account not found! Creating new account..." << endl;
        return Account(accNum, "1234", 1000.0);
    }
};

// Main ATM Menu
void atmMenu(Account &user) {
    int choice;
    do {
        cout << "\nATM Menu:\n";
        cout << "1. Check Balance\n";
        cout << "2. Deposit Money\n";
        cout << "3. Withdraw Money\n";
        cout << "4. Change PIN\n";
        cout << "5. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                user.displayBalance();
                break;
            case 2: {
                double amount;
                cout << "Enter amount to deposit: ";
                cin >> amount;
                user.deposit(amount);
                break;
            }
            case 3: {
                double amount;
                cout << "Enter amount to withdraw: ";
                cin >> amount;
                user.withdraw(amount);
                break;
            }
            case 4: {
                string newPIN;
                cout << "Enter new PIN: ";
                cin >> newPIN;
                user.changePIN(newPIN);
                break;
            }
            case 5:
                cout << "Exiting... Thank you!\n";
                break;
            default:
                cout << "Invalid choice. Try again!\n";
        }
    } while (choice != 5);
}

int main() {
    string accNum, pin;
    cout << "Enter Account Number: ";
    cin >> accNum;
    Account user = Account::loadFromFile(accNum);

    cout << "Enter PIN: ";
    cin >> pin;

    if (user.verifyPIN(pin)) {
        cout << "Login Successful!" << endl;
        atmMenu(user);
    } else {
        cout << "Incorrect PIN. Access Denied!" << endl;
    }

    return 0;
}
