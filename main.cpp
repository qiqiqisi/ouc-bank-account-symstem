#include "database.h"
#include "account.h"
#include "transaction.h"
#include <algorithm>
#include <limits>
#include <iomanip>
using namespace std;

int main() {
    while (true) {
        Database database;
        char choice, choice1;
        string number,password,name;
        reChooseAll:
        cout<<"---欢迎使用每羊银行系统---"<<endl;
        cout<<"账户登录请按1"<<endl;
        cout<<"账户注册请按2"<<endl;
        cout<<"工作人员请按3"<<endl;
        cout<<"请输入选项：";
        cin >> choice;
        switch(choice) {
            case '1': {
                //登录
                reInput:;
                cout << "请输入账户: ";
                cin >> number;
                cout <<"请输入密码：";
                cin >> password;


                auto underUser = find_if(database.accounts.begin(),database.accounts.end(),
                                                 [number,password](const Account* a) {
                                                     return a->getAccountNumber()==number && a->getPassword()==password;
                                                 });

                if (underUser != database.accounts.end()) {
                    (*underUser)->display();
                }
                else {
                    cout<<"账号或者密码错误"<<endl;
                    goto reInput;
                }

                //办理业务
                cout<<"存钱请按1，取钱请按2，修改密码请按3，查看交易记录请按4，退出请按5：";
                while(true) {
                    cin >> choice1;
                    if(choice1 == '5') break;

                    switch(choice1) {
                        //存钱
                        case '1': {
                            cout<<"请输入存入金额"<<endl;
                            double amount;
                            cin>>amount;
                            while(amount<0||cin.fail()) {
                                cout<<"输入错误，请重新输入：";
                                cin.clear();
                                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                                cin>>amount;
                            }
                            (*underUser)->deposit(amount);
                            // 添加存款记录
                            database.addTransaction(Transaction(number, "存款", amount));
                            cout<<"操作成功"<<endl;
                            break;
                        }
                        case '2': {
                            cout<<"请输入您要取出的金额"<<endl;
                            double amount;
                            cin>>amount;
                            while(amount<0||cin.fail()) {
                                cout<<"输入错误，请重新输入"<<endl;
                                cin.clear();
                                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                                cin>>amount;
                            }

                            if ((*underUser)->withdraw(amount)) {
                                // 添加取款记录
                                database.addTransaction(Transaction(number, "取款", amount));
                                cout<<"操作成功"<<endl;
                            }
                            else {
                                cout<<"取钱失败"<<endl;
                            }
                            break;
                        }
                        case '3': {
                            cout<<"请输入您的新密码：";
                            string newPassword;
                            cin>>newPassword;
                            if ((*underUser)->changePassword(password,newPassword)) {
                                cout<<"修改成功"<<endl;
                            }
                            else {
                                cout<<"修改失败"<<endl;
                            }
                            break;
                        }
                        case '4': {
                            // 查看交易记录
                            auto trans = database.getTransactionsByAccount(number);
                            if (trans.empty()) {
                                cout << "没有交易记录" << endl;
                            } else {
                                cout << "交易记录：" << endl;
                                cout << "时间\t\t\t类型\t金额" << endl;
                                for (const auto& t : trans) {
                                    cout << t.getTime() << "\t"
                                         << t.getType() << "\t"
                                         << fixed << setprecision(2) << t.getAmount() << endl;
                                }
                            }
                            break;
                        }
                        default:
                            cout<<"请输入正确的操作"<<endl;
                    }
                    cout << "继续操作请选择（1-4），退出请按5: ";
                }
                break;
            }
            case '2': {
                cout<<"请选择您要注册的类型，储蓄账户请按1，支票账户请按2："<<endl;
                cin >> choice1;
                cout << "请输入您的账户: ";
                cin >> number;


                auto it1=find_if(database.accounts.begin(),database.accounts.end(),
                                         [number](const Account* a) {
                                             return a->getAccountNumber()==number;  // 修正为比较账号而非持有人
                                         });

                while (it1 != database.accounts.end()) {
                    cout <<"账户已存在，请重新输入:";
                    cin >> number;
                    it1 = find_if(database.accounts.begin(),database.accounts.end(),
                                          [number](const Account* a) {
                                              return a->getAccountNumber()==number;
                                          });
                }
                cout <<"请输入密码：";
                cin >> password;
                cout <<"请输入您的姓名：";
                cin >> name;

                switch (choice1) {
                    case '1': {
                        database.accounts.push_back(new savingAccount(number,name,password,0.0,0));
                        cout << "办理成功"<<endl;
                        break;
                    }
                    case '2': {
                        database.accounts.push_back(new checkingAccount(number,name,password,0.0,0));
                        cout<<"办理成功"<<endl;
                        break;
                    }
                    default:
                        cout<<"输入错误，请重新开始注册流程"<<endl;
                }
                break;
            }
            case '3':
                cout<<"请输入工作人员密码"<<endl;
                cin >> password;
                if (password!="999999") {
                    cout<<"密码错误"<<endl;
                    break;
                }
                reChooseWorker:;
                cout<<"根据余额降序排序请按1"<<endl;
                cout<<"根据账号查找请按2"<<endl;
                cout<<"根据姓名查找请按3"<<endl;
                cout<<"显示所有账号信息请按4"<<endl;
                cout<<"查看所有交易记录请按5"<<endl;  // 新增选项
                cout<<"按时间顺序查看交易记录请按6"<<endl;  // 新增选项
                cout<<"退出请按7"<<endl;
                cout<<"结束程序请按8"<<endl;
                cout<<"请选择：";
                cin >> choice1;
                if (choice1 != '7') {
                    switch(choice1) {
                        case '1': {
                            sort(database.accounts.begin(),database.accounts.end());
                            for (Account* a : database.accounts) {
                                cout<<*a<<endl;
                            }
                            goto reChooseWorker;
                        }
                        case '2': {
                            cout<<"请输入账号：";
                            cin >> number;
                            auto findUser = find_if(database.accounts.begin(),database.accounts.end(),[number](const Account* a) {return a->getAccountNumber()==number;});
                            if (findUser != database.accounts.end()) {
                                cout<<**findUser<<endl;
                            }
                            else {
                                cout<<"数据库中没有该账号"<<endl;
                            }
                            goto reChooseWorker;
                        }
                        case '3': {
                            cout<<"请输入姓名：";
                            cin >> name;
                            auto findUser = find_if(database.accounts.begin(),database.accounts.end(),[name](const Account* a) {return a->getAccountHolder()==name;});
                            if (findUser != database.accounts.end()) {
                                cout<<**findUser<<endl;
                            }
                            else {
                                cout<<"数据库中没有该账号"<<endl;
                            }
                            goto reChooseWorker;
                        }
                        case '4': {
                            for (Account* a : database.accounts) {
                                cout<<*a<<endl;
                            }
                            goto reChooseWorker;
                        }
                        case '5': {  // 查看所有交易记录
                            auto allTrans = database.getAllTransactions();
                            if (allTrans.empty()) {
                                cout << "没有交易记录" << endl;
                            } else {
                                cout << "所有交易记录：" << endl;
                                cout << "账户\t时间\t\t\t类型\t金额" << endl;
                                for (const auto& t : allTrans) {
                                    cout << t.getAccountNumber() << "\t"
                                         << t.getTime() << "\t"
                                         << t.getType() << "\t"
                                         << fixed << setprecision(2) << t.getAmount() << endl;
                                }
                            }
                            goto reChooseWorker;
                        }
                        case '6': {  // 按时间顺序查看交易记录
                            database.sortTransactionsByTime();
                            auto sortedTrans = database.getAllTransactions();
                            if (sortedTrans.empty()) {
                                cout << "没有交易记录" << endl;
                            } else {
                                cout << "按时间排序的交易记录：" << endl;
                                cout << "时间\t\t\t账户\t类型\t金额" << endl;
                                for (const auto& t : sortedTrans) {
                                    cout << t.getTime() << "\t"
                                         << t.getAccountNumber() << "\t"
                                         << t.getType() << "\t"
                                         << fixed << setprecision(2) << t.getAmount() << endl;
                                }
                            }
                            goto reChooseWorker;
                        }
                        case '7': {
                            goto reChooseAll;
                        }
                        case '8': {
                            goto exit;
                        }
                        default: {
                            cout<<"无效选项，请重新选择" << endl;
                            goto reChooseWorker;
                        }
                    }
                }
                break;
            default:
                cout << "无效选项，请重新选择" << endl;
                goto reChooseAll;
        }
    }
    exit:;
    return 0;
}