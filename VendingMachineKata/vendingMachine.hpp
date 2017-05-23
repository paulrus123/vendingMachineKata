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
    //constructor creating vending machine stocked by default with 10 of each item
    VendingMachine() :
        currentUserValueInputSoFar(0.0),
        colaStock(10),
        chipsStock(10),
        candyStock(10),
        coinsInCoinReturn(),
        quartersInMachine(),
        dimesInMachine(),
        nickelsInMachine(),
        numberOfQuartersDispensedByCurrentUser(0),
        numberOfDimesDispensedByCurrentUser(0),
        numberOfNickelsDispensedByCurrentUser(0),
        isDispensedDisplayThankYou(false),
        haveInsufficientFunds(false),
        displayCurrentAmount(false),
        displaySoldOut(false),
        productPriceString("1.00")
    {
    }
    
    //constructor with specifiable stock of each item
    VendingMachine(int colas, int chips, int candy) :
    colaStock(colas),
    chipsStock(chips),
    candyStock(candy),
    currentUserValueInputSoFar(0.0),
    coinsInCoinReturn(),
    quartersInMachine(),
    dimesInMachine(),
    nickelsInMachine(),
    numberOfQuartersDispensedByCurrentUser(0),
    numberOfDimesDispensedByCurrentUser(0),
    numberOfNickelsDispensedByCurrentUser(0),
    isDispensedDisplayThankYou(false),
    haveInsufficientFunds(false),
    displayCurrentAmount(false),
    displaySoldOut(false),
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
     * Returns the display text on the vending machine
     *
     * @return string containing the text to display on the vending machine output
     */
    string display();
    
    /**
     * Accepts an object
     * @param coin the (possible) coin object
     */
    void acceptCoin(const InsertableObject &coin);
    
    /**
     * Prints an array of Insertable Objects that are in the coin return and empties the coin return
     *
     * @return comma separated list of coins in the coin return. Unknown coins will printed as "UnknownCoin"
     */
    string getCoinReturn();
    
    /**
    * Dispenses selected product if enough money is in the machine
    *
    *@param productName the name of the product to dispense (cola, chips, or candy)
    */
    void dispenseProduct(VendingMachine::ProductName productName);
    
    /**
    Returns any inserted money into the coin return and zeros the balance
     */
    void coinReturnPressed();
    
    /**
     * Stocks the machine money stock with coins
     *
     * @param coins vector of coins to stock in machine
     */
    void stockMoneyInMachine(std::vector<InsertableObject> coins);
    
private:
    int currentUserValueInputSoFar; //the amount of money the current user has put in the machine in cents
    std::vector<InsertableObject> coinsInCoinReturn; //array of coins in the coin return
    std::vector<InsertableObject> quartersInMachine; //array of quarters in the machine
    std::vector<InsertableObject> dimesInMachine; //array of dimes in the machine
    std::vector<InsertableObject> nickelsInMachine; //array of nickels in the machine

    /* 
     * Following ints are counters for how many coins of each type the user has input. this is used to return
     * those coins if the user presses the coin return button
     */
    int numberOfQuartersDispensedByCurrentUser;
    int numberOfDimesDispensedByCurrentUser;
    int numberOfNickelsDispensedByCurrentUser;
    
    bool isDispensedDisplayThankYou; //bool that tells display whether or not to display "THANK YOU"
    bool haveInsufficientFunds; //bool that tells display to show "PRICE ___" (price of product) if insufficient funds
    bool displayCurrentAmount; //bool that is true if display should display the amount the user has input so far
    bool displaySoldOut; //bool is true if display should show "SOLD OUT"
    string productPriceString; //string containing price of a product
    
    int colaStock; //number of colas in the machine
    int chipsStock; //number of bags of chips in the machine
    int candyStock; //number of bags of candy in the machine
    
    /**
     * Adds any extra money that was input and not used into the change return
     */
    void returnChange(int amountToReturn);

    /**
     * Internal function to check if machine has enough change to display "INSERT COIN"
     * @return true if the machine has enough change, false if it does not
     */
    bool doNotNeedToDisplayExactChange();
};

#endif /* vendingMachine_hpp */
