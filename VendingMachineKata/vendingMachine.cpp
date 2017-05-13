//
//  vendingMachine.cpp
//  VendingMachineKata
//
//  Created by Paul Sorenson on 5/12/17.
//  Copyright © 2017 Paul Sorenson. All rights reserved.
//

#include "vendingMachine.hpp"

string VendingMachine::display()
{
    if(currentUserValueInputSoFar)
        return "0.25";
    else
        return "INSERT COIN";
}

void VendingMachine::acceptCoin(const InsertableObject &coin)
{
    currentUserValueInputSoFar+=0.25;
}
