//
//  vendingMachine.hpp
//  VendingMachineKata
//
//  Created by Paul Sorenson on 5/12/17.
//  Copyright © 2017 Paul Sorenson. All rights reserved.
//

#ifndef vendingMachine_hpp
#define vendingMachine_hpp

#include <stdio.h>
#include <string>
#include <vector>

using namespace std;

struct InsertableObject {
    float weight; //weight in grams
    float diameter; //diameter in millimeters
};


class VendingMachine
{
public:
    VendingMachine() :
        currentUserValueInputSoFar(0.0),
        coinsInCoinReturn(),
        quartersInMachine(),
        dimesInMachine(),
        nickelsInMachine(),
        isDispensedDisplayThankYou(false),
        haveInsufficientFunds(false),
        displayCurrentAmount(false),
        productPriceString("1.00")
    {
    }
    
    //constants
    static const float quarterWeight; 
    static const float quarterDiameter;
    static const float dimeWeight;
    static const float dimeDiameter;
    static const float nickelWeight;
    static const float nickelDiameter;
    static const float pennyWeight;
    static const float pennyDiameter;
    static const float toleranceLevel; //weight/size tolerance at which the machine will still accept object as valid coin
    
    enum ProductName { //products that the vending machine stocks
        cola,
        chips,
        candy
    };
    
    /**
     Returns the display text on the vending machine
     
     @return string containing the text to display on the vending machine output
     */
    string display();
    
    /**
     Accepts an object
     @param coin the (possible) coin object
     */
    void acceptCoin(const InsertableObject &coin);
    
    /**
     Prints an array of Insertable Objects that are in the coin return and empties the coin return
     
     @return comma separated list of coins in the coin return. Unknown coins will printed as "UnknownCoin"
     */
    string getCoinReturn();
    
    /**
    Dispenses selected product if enough money is in the machine

     @param productName the name of the product to dispense (cola, chips, or candy)
    */
    void dispenseProduct(VendingMachine::ProductName productName);
    
    /**
    Returns any inserted money into the coin return and zeros the balance
     */
    void coinReturnPressed();
    
private:
    int currentUserValueInputSoFar; //the amount of money the current user has put in the machine in cents
    std::vector<InsertableObject> coinsInCoinReturn; //array of coins in the coin return
    std::vector<InsertableObject> quartersInMachine; //array of quarters in the machine
    std::vector<InsertableObject> dimesInMachine; //array of dimes in the machine
    std::vector<InsertableObject> nickelsInMachine; //array of nickels in the machine
    bool isDispensedDisplayThankYou; //bool that tells display whether or not to display "THANK YOU"
    bool haveInsufficientFunds; //bool that tells display to show "PRICE ___" (price of product) if insufficient funds
    bool displayCurrentAmount; //bool that is true if display should display the amount the user has input so far
    string productPriceString; //string containing price of a product
    
    /**
     * Adds any extra money that was input and not used into the change return
     */
    void returnChange(int amountToReturn);
};

#endif /* vendingMachine_hpp */
