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
        quarter->weight = 5.67; //standard weight of a quarter https://mdmetric.com/tech/coinmeasure.htm
        quarter->diameter = 24.26; //standard diameter of a quarter
        
        vendingMachine->acceptCoin(*quarter);
        
        REQUIRE(vendingMachine->display() == "0.25");
    }
    
    SECTION("WhenDimeIsInsertedUpdateDisplay") {
        VendingMachine* vendingMachine = new VendingMachine;
        
        InsertableObject* dime = new InsertableObject;
        dime->weight = 2.27; //standard weight of a dime
        dime->diameter = 17.91; //standard diameter of dime
        
        vendingMachine->acceptCoin(*dime);
        
        REQUIRE(vendingMachine->display() == "0.10");
    }

    SECTION("WhenNickelIsInsertedUpdateDisplay") {
        VendingMachine* vendingMachine = new VendingMachine;
        
        InsertableObject* nickel = new InsertableObject;
        nickel->weight = 5.0; //standard weight of a nickel
        nickel->diameter = 21.21; //standard diameter of nickel
        
        vendingMachine->acceptCoin(*nickel);
        
        REQUIRE(vendingMachine->display() == "0.05");
    }
    
    
}
