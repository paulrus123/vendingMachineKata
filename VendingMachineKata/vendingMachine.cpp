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
        else if(displaySoldOut)
        {
            displaySoldOut = false;
            return "SOLD OUT";
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
        numberOfQuartersDispensedByCurrentUser++;
    }
    else if((abs(coin.weight - dimeWeight) < toleranceLevel) && (abs(coin.diameter - dimeDiameter) < toleranceLevel)) //dime
    {
        currentUserValueInputSoFar+=10;
        displayCurrentAmount = true;
        dimesInMachine.push_back(coin); //add the coin to the dimes stock of the machine
        numberOfDimesDispensedByCurrentUser++;
    }
    else if((abs(coin.weight - nickelWeight) < toleranceLevel) && (abs(coin.diameter - nickelDiameter) < toleranceLevel)) //nickel
    {
        currentUserValueInputSoFar+=5;
        displayCurrentAmount = true;
        nickelsInMachine.push_back(coin); //add the coin to the nickels stock of the machine
        numberOfNickelsDispensedByCurrentUser++;
    }
    else //not valid
        coinsInCoinReturn.push_back(coin); //directly put the coin into the coin return
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
            else if((abs(it->weight - quarterWeight) < toleranceLevel) && (abs(it->diameter - quarterDiameter) < toleranceLevel)) //quarter
                listOfCoins += "Quarter, ";
            else if((abs(it->weight - dimeWeight) < toleranceLevel) && (abs(it->diameter - dimeDiameter) < toleranceLevel)) //dime
                listOfCoins += "Dime, ";
            else if((abs(it->weight - nickelWeight) < toleranceLevel) && (abs(it->diameter - nickelDiameter) < toleranceLevel)) //nickel
                listOfCoins += "Nickel, ";
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
            if(colaStock <= 0)
            {
                displaySoldOut = true;
            }
            else if(currentUserValueInputSoFar >= 100)
            {
                isDispensedDisplayThankYou = true;
                returnChange(currentUserValueInputSoFar - 100);
                currentUserValueInputSoFar = 0;
            }
            else
            {
                haveInsufficientFunds = true;
                productPriceString = "1.00";
            }
            break;
        case chips:
            if(chipsStock <= 0)
            {
                displaySoldOut = true;
            }
            else if(currentUserValueInputSoFar >= 50)
            {
                isDispensedDisplayThankYou = true;
                returnChange(currentUserValueInputSoFar - 50);
                currentUserValueInputSoFar = 0;
            }
            else
            {
                haveInsufficientFunds = true;
                productPriceString = "0.50";
            }
            break;
        case candy:
            if(candyStock <= 0)
            {
                displaySoldOut = true;
            }
            else if(currentUserValueInputSoFar >= 65)
            {
                isDispensedDisplayThankYou = true;
                returnChange(currentUserValueInputSoFar - 65);
                currentUserValueInputSoFar = 0;
            }
            else
            {
                haveInsufficientFunds = true;
                productPriceString = "0.65";
            }
            break;
        default:
            break;
    }
}

void VendingMachine::returnChange(int amountToReturn)
{
    int leftToReturn = amountToReturn;
    while((leftToReturn >= 25) && (!quartersInMachine.empty()))
    {
        coinsInCoinReturn.push_back(quartersInMachine.back());
        quartersInMachine.pop_back();
        leftToReturn -= 25;
    }
    while((leftToReturn >= 10) && (!dimesInMachine.empty()))
    {
        coinsInCoinReturn.push_back(dimesInMachine.back());
        dimesInMachine.pop_back();
        leftToReturn-=10;
    }
    while((leftToReturn >= 5) && (!nickelsInMachine.empty()))
    {
        coinsInCoinReturn.push_back(nickelsInMachine.back());
        nickelsInMachine.pop_back();
        leftToReturn-=5;
    }
    
    //zero out the coin counters for the current session
    numberOfNickelsDispensedByCurrentUser = 0;
    numberOfDimesDispensedByCurrentUser = 0;
    numberOfQuartersDispensedByCurrentUser = 0;
}

void VendingMachine::coinReturnPressed()
{

    while((numberOfQuartersDispensedByCurrentUser > 0) && (!quartersInMachine.empty()))
    {
        coinsInCoinReturn.push_back(quartersInMachine.back());
        quartersInMachine.pop_back();
        numberOfQuartersDispensedByCurrentUser--;
    }
    while((numberOfDimesDispensedByCurrentUser > 0) && (!dimesInMachine.empty()))
    {
        coinsInCoinReturn.push_back(dimesInMachine.back());
        dimesInMachine.pop_back();
        numberOfDimesDispensedByCurrentUser--;
    }
    while((numberOfNickelsDispensedByCurrentUser > 0) && (!nickelsInMachine.empty()))
    {
        coinsInCoinReturn.push_back(nickelsInMachine.back());
        nickelsInMachine.pop_back();
        numberOfNickelsDispensedByCurrentUser--;
    }
}





