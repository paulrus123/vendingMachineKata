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

using namespace std;

struct InsertableObject {
    float weight;
    float diameter;
};


class VendingMachine
{
public:
    VendingMachine() : currentUserValueInputSoFar(0.0)
    {
    }
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
    
private:
    float currentUserValueInputSoFar; //the amount of money the current user has put in the machine
    
};

#endif /* vendingMachine_hpp */
