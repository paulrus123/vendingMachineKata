//
//  tests.cpp
//  VendingMachineUnitTests
//
//  Created by Paul Sorenson on 5/11/17.
//  Copyright © 2017 Paul Sorenson. All rights reserved.
//

#include <iostream>
#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "catch.hpp"
#include "vendingMachine.hpp"


//#defines for test values of coin weights and diameters
#define QUARTER_WEIGHT 5.67f
#define QUARTER_DIAMETER 24.26f
#define DIME_WEIGHT 2.27f
#define DIME_DIAMETER 17.91f
#define NICKEL_WEIGHT 5.0f
#define NICKEL_DIAMETER 21.21f
#define PENNY_WEIGHT 2.5f
#define PENNY_DIAMETER 19.05f


TEST_CASE("TestAcceptCoinsFunction") {
  
    VendingMachine* vendingMachine = new VendingMachine;
    
    InsertableObject* quarter = new InsertableObject;
    quarter->weight = QUARTER_WEIGHT; //standard weight of a quarter https://mdmetric.com/tech/coinmeasure.htm
    quarter->diameter = QUARTER_DIAMETER; //standard diameter of a quarter
    
    InsertableObject* dime = new InsertableObject;
    dime->weight = DIME_WEIGHT; //standard weight of a dime
    dime->diameter = DIME_DIAMETER; //standard diameter of dime
    
    InsertableObject* nickel = new InsertableObject;
    nickel->weight = NICKEL_WEIGHT; //standard weight of a nickel
    nickel->diameter = NICKEL_DIAMETER; //standard diameter of nickel
    
    InsertableObject* penny = new InsertableObject;
    penny->weight = PENNY_WEIGHT;
    penny->diameter = PENNY_DIAMETER;
    
    SECTION("WhenNoMoneyIsInsertedThenDisplayInsertCoin") {
        REQUIRE(vendingMachine->display() == "INSERT COIN");
    }
    
    SECTION("WhenQuarterIsInsertedThenUpdateDisplay") {
        vendingMachine->acceptCoin(*quarter);
        REQUIRE(vendingMachine->display() == "0.25");
    }
    
    SECTION("WhenDimeIsInsertedThenUpdateDisplay") {
        vendingMachine->acceptCoin(*dime);
        REQUIRE(vendingMachine->display() == "0.10");
    }

    SECTION("WhenNickelIsInsertedThenUpdateDisplay") {
        vendingMachine->acceptCoin(*nickel);
        REQUIRE(vendingMachine->display() == "0.05");
    }
    
    SECTION("WhenMultipleCoinsAreInsertedThenAccumulateAmountAndUpdateDisplay"){
        vendingMachine->acceptCoin(*quarter);
        REQUIRE(vendingMachine->display() == "0.25");
        
        vendingMachine->acceptCoin(*nickel);
        REQUIRE(vendingMachine->display() == "0.30");
        
        vendingMachine->acceptCoin(*dime);
        REQUIRE(vendingMachine->display() == "0.40");
    }
    
    SECTION("WhenInvalidCoinIsInsertedThenReturnCoin")
    {
        vendingMachine->acceptCoin(*penny);
        REQUIRE(vendingMachine->getCoinReturn() == "Penny");
    }
    
    
    
}
