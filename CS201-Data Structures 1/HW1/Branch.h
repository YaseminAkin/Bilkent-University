//
//  Branch.h
//  HW1
//
//  Created by Yasemin Akın on 31.03.2023.
//

#ifndef Branch_h
#define Branch_h

#include <stdio.h>
using namespace std;
#include <iostream>
#include <string>
#include "Account.h"
#include "Customer.h"
class Branch{
public:
    int branchId;
    string branchName;
    Account* accountsInBranch;
    int numAccountsInBranch;
    Branch(int newBranchId = 0, string newBranchName = "");
    void deepcopy(Branch& otherBranch);
    ~Branch();
    void addAccountToBranch(int customerId, double amount, int accountId);
    void deleteAccountFromBanch(int deleteAccountId);
    void deleteCustomerFromBranch(int customerId);
};
#endif /* Branch_h */
