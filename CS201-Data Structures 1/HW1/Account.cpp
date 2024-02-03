//
//  Account.cpp
//  HW1
//
//  Created by Yasemin Akın on 31.03.2023.
//

#include "Account.h"
#include <iostream>
using namespace std;
Account::Account(int newBranchId, int newCustomerId, double newDepositedAmount){
    branchId = newBranchId;
    customerId = newCustomerId;
    depositedAmount = newDepositedAmount;
}
void Account::deepcopy(Account &otherAccount){
    accountId = otherAccount.accountId;
    branchId = otherAccount.branchId;
    customerId = otherAccount.customerId;
    depositedAmount = otherAccount.depositedAmount;
}
Account::~Account(){}
