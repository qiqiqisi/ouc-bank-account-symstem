//
// Created by Administrator on 2025/6/6.
//
#include "account.h"

//Account
//个人信息
string Account::getAccountNumber() const {return accountNumber;}
string Account::getAccountHolder() const {return accountHolder;}
double Account::getBalance() const {return balance;}
string Account::getPassword() const {return password;}
int Account::getTransactionCount() const {return transactionCount;}
bool Account::changePassword(const string &oldPassword, const string &newPassword) {
  if (oldPassword != password) {
    return false;
  }
  password = newPassword;
  return true;
}

//比较账号
bool Account::operator==(const Account &other) const {
  return accountNumber == other.accountNumber&&password == other.password;
}

//打印账号信息
ostream& operator<<(ostream &os, const Account &a){
  os<<"类型："<<a.getType()<<';';
  os<<"账号："<<a.getAccountNumber()<<';';
  os<<"持卡人："<<a.getAccountHolder()<<';';
  os<<"密码："<<a.getPassword()<<';';
  os<<"余额："<<a.getBalance()<<';';
  os<<"取款次数："<<a.getTransactionCount()<<endl;
  return os;
}

void Account::display() const{
  cout<<"尊敬的"<<getAccountHolder()<<':'<<endl;
  cout<<"您正在使用"<<getAccountNumber()<<endl;
  cout<<"您的余额是："<<getBalance()<<endl;
}

//savingAccount
void savingAccount::deposit(double amount) {
  balance += amount;
}

bool savingAccount::withdraw(double amount) {
  if (amount <= balance && maxCount > transactionCount && maxAmount >= amount) {
    balance -= amount;
    transactionCount++;
    cout<<"取款成功"<<endl;
    return true;
  }

  if (amount > balance) {
    cout<<"余额不足"<<endl;
  }
  if (maxCount <= transactionCount) {
    cout<<"本月您已取了最大上限次数"<<endl;
  }
  if (maxAmount < amount) {
    cout<<"您的单笔交易金额已经超过了最大上限"<<endl;
  }
  return false;
}

string savingAccount::getType() const {return "储蓄账户";}

//checkingAccount
void checkingAccount::deposit(double amount) {
  balance += amount;
}

bool checkingAccount::withdraw(double amount) {
  if (transactionCount >= freeCount) {
    amount *= (1+feeRate);
  }
  if (amount > balance) {
    cout<<"余额不足"<<endl;
    return false;
  }
  else{
    balance -= amount;
    transactionCount++;
    return true;
  }
}

string checkingAccount::getType() const {return "支票账户";}