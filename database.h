//
// Created by Administrator on 2025/6/6.
//

#ifndef DATABASE_H
#define DATABASE_H
#pragma once
#include <memory>
#include <vector>
#include "account.h"
#include "transaction.h"
using namespace std;

class Database{
private:
    Account* stringToAccount(string s);
    string AccountToString(Account* a);
public:
    vector<Account*> accounts;
    vector<Transaction> transactions;
    Database();
    ~Database();


    void addTransaction(const Transaction& trans);
    vector<Transaction> getTransactionsByAccount(const string& accountNumber) const;
    vector<Transaction> getAllTransactions() const;
    void sortTransactionsByTime();
};
#endif //DATABASE_H