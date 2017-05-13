//
//  main.cpp
//  VendingMachineUnitTests
//
//  Created by Paul Sorenson on 5/11/17.
//  Copyright © 2017 Paul Sorenson. All rights reserved.
//

#include <iostream>
#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "catch.hpp"
#include "vendingMachine.hpp"


TEST_CASE("TestAcceptCoinsFunction") {
    
    SECTION("WhenNoMoneyIsInsertedDisplayInsertCoin") {
        VendingMachine* vendingMachine = new VendingMachine;
        REQUIRE(vendingMachine->display() == "INSERT COIN");
    }
    
    SECTION("WhenQuarterIsInsertedUpdateDisplay") {
        VendingMachine* vendingMachine = new VendingMachine;
        
        InsertableObject* quarter = new InsertableObject;
        quarter->weight = 5.67;
        quarter->diameter = 24.26;
        
        vendingMachine->acceptCoin(*quarter);
        
        REQUIRE(vendingMachine->display() == "0.25");
    }
}
