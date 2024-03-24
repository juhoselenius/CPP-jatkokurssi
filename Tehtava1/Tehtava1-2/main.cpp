#include <iostream>
#include <thread>
#include <mutex>

std::mutex mtx; // Mutex for critical section (protecting the account)

class BankAccount
{
private:
    int _balance;

public:
    BankAccount()
    {
        _balance = 0;
    }

    void deposit(int amount)
    {
        std::lock_guard<std::mutex> lock(mtx);
        _balance += amount;
    }

    void withdraw(int amount)
    {
        std::lock_guard<std::mutex> lock(mtx);
        _balance -= amount;
    }

    int getBalance()
    {
        return _balance;
    }
};

void depositMoney(BankAccount* account, int amount, int transactions)
{
    for (int i = 0; i < transactions; i++)
    {
        account->deposit(amount);
    }
}

void withdrawMoney(BankAccount* account, int amount, int transactions)
{
    for (int i = 0; i < transactions; i++)
    {
        account->withdraw(amount);
    }
}

int main()
{
    BankAccount account;
    const int transactions = 10000;
    const int depositAmount = 100;
    const int withdrawAmount = 50;

    // Creating the threads
    std::thread depositThread(depositMoney, &account, depositAmount, transactions);
    std::thread withdrawThread(withdrawMoney, &account, withdrawAmount, transactions);

    // Waiting for the completion of the threads
    depositThread.join();
    withdrawThread.join();

    // Checking the balance of the account
    int calculatedBalance = transactions * depositAmount - transactions * withdrawAmount;
    int finalBalance = account.getBalance();
    if (finalBalance != calculatedBalance)
    {
        std::cout << "The balance of the account is not correct: " << finalBalance << std::endl;
    }
    else
    {
        std::cout << "The balance of the account is correct: " << finalBalance << std::endl;
    }

    return 0;
}