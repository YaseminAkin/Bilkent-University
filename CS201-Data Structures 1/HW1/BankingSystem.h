//
//  BankingSystem.h
//  HW1
//
//  Created by Yasemin Akın on 31.03.2023.
//

#ifndef BankingSystem_h
#define BankingSystem_h

#include <stdio.h>
using namespace std;
#include <string>
#include "Branch.h"
#include "Customer.h"
#include "Account.h"
#include <iomanip>
class BankingSystem {
public :
    Branch* branches;
    int numBranches;
    Customer* customers;
    int numCustomers;
    Account* allAccounts;
    int numAccounts;
    int accountIds;
    BankingSystem () ;
    ~ BankingSystem () ;
    void addBranch ( const int branchId , const string branchName ) ;
    void deleteBranch ( const int branchId ) ;
    void addCustomer ( const int customerId , const string customerName ) ;
    void deleteCustomer ( const int customerId ) ;
    int addAccount ( const int branchId , const int customerId , const double amount ) ;
    void deleteAccount ( const int accountId ) ;
    void showAllAccounts () ;
    void showBranch ( const int branchId ) ;
    void showCustomer ( const int customerId ) ;
    void showAllBranches();
    void showAllCustomers();
};
#endif /* BankingSystem_h */
