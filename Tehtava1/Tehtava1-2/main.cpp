#include <iostream>
#include <thread>
#include <mutex>

std::mutex mtx; // Mutex for protecting the account

class BankAccount
{
private:
    int balance;

public:
    BankAccount() : balance(0) {}

    void deposit(int amount)
    {
        std::lock_guard<std::mutex> lock(mtx); // Lukituksen automaattinen hallinta
        balance += amount;
    }

    void withdraw(int amount)
    {
        std::lock_guard<std::mutex> lock(mtx); // Lukituksen automaattinen hallinta
        balance -= amount;
    }

    int getBalance() const
    {
        return balance;
    }
};

void depositMoney(BankAccount& account, int amount, int transactions)
{
    for (int i = 0; i < transactions; ++i)
    {
        account.deposit(amount);
    }
}

void withdrawMoney(BankAccount& account, int amount, int transactions)
{
    for (int i = 0; i < transactions; ++i)
    {
        account.withdraw(amount);
    }
}

int main()
{
    BankAccount account;
    const int transactions = 1000;
    const int depositAmount = 100;
    const int withdrawAmount = 50;

    // Luodaan säikeet
    std::thread depositThread(depositMoney, std::ref(account), depositAmount, transactions);
    std::thread withdrawThread(withdrawMoney, std::ref(account), withdrawAmount, transactions);

    // Odota säikeiden päättymistä
    depositThread.join();
    withdrawThread.join();

    // Tarkista tilin saldo
    int finalBalance = account.getBalance();
    if (finalBalance != (transactions * depositAmount - transactions * withdrawAmount))
    {
        std::cout << "Tilin saldo on virheellinen: " << finalBalance << std::endl;
    }
    else
    {
        std::cout << "Tilin saldo on oikea: " << finalBalance << std::endl;
    }

    return 0;
}