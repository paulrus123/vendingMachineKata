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
    VendingMachine() : currentUserValueInputSoFar(0.0), coinsInCoinReturn(), isDispensedDisplayThankYou(false)
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
    
private:
    int currentUserValueInputSoFar; //the amount of money the current user has put in the machine in cents
    std::vector<InsertableObject> coinsInCoinReturn; //array of coins in the coin return
    bool isDispensedDisplayThankYou;

    
};

#endif /* vendingMachine_hpp */
