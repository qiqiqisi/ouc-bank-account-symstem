//
// Created by Administrator on 2025/6/6.
//
#pragma once
#ifndef ACCOUNT_H
#define ACCOUNT_H
#include <iostream>
using namespace std;
class Account {
  protected:
    string accountNumber;//�˺ű�����Ψһ��
    string accountHolder;
    string password;
    double balance;
    int transactionCount;
  public:
    Account(const string &accountNumber, const string &accountHolder, const string &password, double balance,int transactionCount):accountNumber(accountNumber), accountHolder(accountHolder), password(password), balance(balance), transactionCount(transactionCount) {};
    virtual ~Account()=default;
    //������Ϣ
    string getAccountNumber() const;
    string getAccountHolder() const;
    double getBalance() const;
    string getPassword() const;
    int getTransactionCount() const;
    bool changePassword(const string &oldPassword,const string &newPassword);

    //�Ƚ��˺�
    bool operator==(const Account &other) const;

    //��ӡ�˺���Ϣ
    friend ostream& operator<<(ostream& os,const Account& a);
    void display() const;

    //��ǮȡǮ
    virtual void deposit(double amount)=0;
    virtual bool withdraw(double amount)=0;

    //��ȡ��������
    virtual string getType()const =0;
};

class savingAccount :virtual public Account {
  private:
    constexpr static double insterestRate=0.05;
    static constexpr int maxCount=3;
    static constexpr int maxAmount=500;
    public:
      savingAccount(const string &accountNumber, const string &accountHolder, const string &password, double balance, int transactionCount):Account(accountNumber, accountHolder, password, balance, transactionCount) {};

      void deposit(double amount) override;
      bool withdraw(double amount) override;
      string getType()const override;
};

class checkingAccount :virtual public Account {
  private:
    static const int freeCount=3;
    constexpr static const double feeRate=0.01;
  public:
    checkingAccount(const string &accountNumber, const string &accountHolder, const string &password, double balance, int transactionCount):Account(accountNumber, accountHolder, password, balance, transactionCount) {};

    void deposit(double amount) override;
    bool withdraw(double amount) override;
    string getType() const override;
};
#endif //ACCOUNT_H