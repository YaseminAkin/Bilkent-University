//
//  Customer.h
//  HW1
//
//  Created by Yasemin Akın on 31.03.2023.
//

#ifndef Customer_h
#define Customer_h

#include <stdio.h>
using namespace std;
#include "Account.h"
#include <string>
class Customer{
public:
    int customerId;
    string customerName;
    Account *accountsOfCustomer;
    int numAccountsOfCustomer;
    Customer (int newCustomerId = 0, string newCustomerName = "");
    void deepcopy (Customer& otherCustomer);
    ~Customer();
    void addAccountToCustomer(int branchId, double amount, int accountId);
    void deleteAccountFromCustomer(int deleteAccountId);
    void deleteBranchFromCustomer(int branchId);
};
#endif /* Customer_h */
