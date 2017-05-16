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
#include <iostream>


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
    if(displayCurrentAmount) //display should show how much money the user has input so far
    {
        int cents = currentUserValueInputSoFar % 100;
        int dollars = currentUserValueInputSoFar / 100;
        
        stringstream dollarStream;
        dollarStream << dollars;
        
        stringstream centsStream;
        centsStream << std::setw(2) << std::setfill('0') << cents;
        
        return(dollarStream.str() + "." + centsStream.str());
    }
    else
    {
        if(haveInsufficientFunds == true)
        {
            haveInsufficientFunds = false;
            if(currentUserValueInputSoFar)
            {
                displayCurrentAmount = true;
            }
            return("PRICE " + productPriceString);
        }
        else if(isDispensedDisplayThankYou)
        {
            isDispensedDisplayThankYou = false;
            return "THANK YOU";
        }
        else
        {
            return "INSERT COIN";
        }
    }
}

void VendingMachine::acceptCoin(const InsertableObject &coin)
{
    //Check if weight and diameter of inserted object is within toleranceLevel (gram, millimeter) of an accepted coin type
    if((abs(coin.weight - quarterWeight) < toleranceLevel) && (abs(coin.diameter - quarterDiameter) < toleranceLevel)) //quarter
    {
        currentUserValueInputSoFar+=25;
        displayCurrentAmount = true;
        quartersInMachine.push_back(coin); //add the coin to the quarters stock of the machine
    }
    else if((abs(coin.weight - dimeWeight) < toleranceLevel) && (abs(coin.diameter - dimeDiameter) < toleranceLevel)) //dime
    {
        currentUserValueInputSoFar+=10;
        displayCurrentAmount = true;
    }
    else if((abs(coin.weight - nickelWeight) < toleranceLevel) && (abs(coin.diameter - nickelDiameter) < toleranceLevel)) //nickel
    {
        currentUserValueInputSoFar+=5;
        displayCurrentAmount = true;
    }
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
            else if((abs(it->weight - quarterWeight) < toleranceLevel) && (abs(it->diameter - quarterDiameter) < toleranceLevel)) //penny
                listOfCoins += "Quarter, ";
            else
                listOfCoins += "UnknownCoin, ";
        }
        return listOfCoins;
    }
    else
       return "Coin return is empty";
}

void VendingMachine::dispenseProduct(VendingMachine::ProductName productName)
{
    displayCurrentAmount = false;
    switch (productName){
        case cola:
            if(currentUserValueInputSoFar >= 100)
            {
                isDispensedDisplayThankYou = true;
                currentUserValueInputSoFar = 0;
            }
            else
            {
                haveInsufficientFunds = true;
                productPriceString = "1.00";
            }
            break;
        case chips:
            if(currentUserValueInputSoFar >= 50)
            {
                isDispensedDisplayThankYou = true;
                returnChange();
                currentUserValueInputSoFar = 0;
            }
            else
            {
                haveInsufficientFunds = true;
                productPriceString = "0.50";
            }
            break;
        case candy:
            if(currentUserValueInputSoFar >= 65)
            {
                isDispensedDisplayThankYou = true;
                currentUserValueInputSoFar = 0;
            }
            else
            {
                haveInsufficientFunds = true;
                productPriceString = "0.65";
            }
            break;
        default:
            //do something
            break;
    }
}

void VendingMachine::returnChange()
{
    for(int i = 0; i <2; i++){
        if(!quartersInMachine.empty())
        {
            coinsInCoinReturn.push_back(quartersInMachine.back());
            quartersInMachine.pop_back();
        }
    }
}



