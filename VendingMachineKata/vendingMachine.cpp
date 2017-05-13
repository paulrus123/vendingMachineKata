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
#include <cmath> // abs


//Constants
const float VendingMachine::quarterWeight = 5.67f;
const float VendingMachine::quarterDiameter = 24.26f;
const float VendingMachine::dimeWeight = 2.27f;
const float VendingMachine::dimeDiameter = 17.91f;
const float VendingMachine::nickelWeight = 5.0f;
const float VendingMachine::nickelDiameter = 21.21f;
const float VendingMachine::toleranceLevel = 0.01f;
const float VendingMachine::pennyWeight = 2.5f;
const float VendingMachine::pennyDiameter = 19.05f;

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
    //Check if weight and diameter of inserted object is within toleranceLevel (gram, millimeter) of an accepted coin type
    if((abs(coin.weight - quarterWeight) < toleranceLevel) && (abs(coin.diameter - quarterDiameter) < toleranceLevel)) //quarter
        currentUserValueInputSoFar+=0.25f;
    else if((abs(coin.weight - dimeWeight) < toleranceLevel) && (abs(coin.diameter - dimeDiameter) < toleranceLevel)) //dime
        currentUserValueInputSoFar+=0.1f;
    else if((abs(coin.weight - nickelWeight) < toleranceLevel) && (abs(coin.diameter - nickelDiameter) < toleranceLevel)) //nickel
        currentUserValueInputSoFar+=0.05f;
    else //not valid
        coinsInCoinReturn.push_back(coin);
}

string VendingMachine::getCoinReturn()
{
    if(!coinsInCoinReturn.empty()) //there are objects in the coin return
    {
        string listOfCoins = "";
        for(std::vector<InsertableObject>::reverse_iterator it = coinsInCoinReturn.rbegin(); it != coinsInCoinReturn.rend(); ++it)
        {
            if((abs(it->weight - pennyWeight) < toleranceLevel) && (abs(it->diameter - pennyDiameter) < toleranceLevel)) //penny
                listOfCoins += "Penny, ";
            else
                listOfCoins += "UnknownCoin, ";
        }
        return listOfCoins;
    }
    else
       return "Coin return is empty";
}


