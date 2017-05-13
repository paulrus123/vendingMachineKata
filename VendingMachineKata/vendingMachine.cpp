//
//  vendingMachine.cpp
//  VendingMachineKata
//
//  Created by Paul Sorenson on 5/12/17.
//  Copyright © 2017 Paul Sorenson. All rights reserved.
//

#include "vendingMachine.hpp"
#include <iomanip> // setprecision
#include <sstream> // stringstream
#include <cmath>

string VendingMachine::display()
{

    if(currentUserValueInputSoFar)
    {
        stringstream stream;
        stream << fixed << setprecision(2) << currentUserValueInputSoFar;
        return stream.str();
    }
    else
        return "INSERT COIN";
}

void VendingMachine::acceptCoin(const InsertableObject &coin)
{
    if((abs(coin.weight - 2.27) < 0.01) && (abs(coin.diameter - 17.91) < 0.01)) //dime
        currentUserValueInputSoFar+=0.1;
    else if((abs(coin.weight - 5.67) < 0.01) && (abs(coin.diameter - 24.26) < 0.01)) //quarter
        currentUserValueInputSoFar+=0.25;
    else if((abs(coin.weight - 5.0) < 0.01) && (abs(coin.diameter - 21.21) < 0.01)) //quarter
    currentUserValueInputSoFar+=0.05;
    else //not valid
    {
    }
}
