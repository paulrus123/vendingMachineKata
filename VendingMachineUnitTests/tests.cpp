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
#include <array>


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
    
    
    //Setup
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
    
    InsertableObject* unknownCoin = new InsertableObject;
    unknownCoin->weight = 6.5f;
    unknownCoin->diameter = 15.0f;
    
    //Test sections
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
    
    SECTION("WhenInvalidCoinIsInsertedThenReturnCoin"){
        vendingMachine->acceptCoin(*penny);
        REQUIRE(vendingMachine->getCoinReturn() == "Penny, ");
    }
    
    SECTION("WhenNoCoinIsInsertedThenCoinReturnShallBeEmpty"){
        REQUIRE(vendingMachine->getCoinReturn() == "Coin return is empty");
    }
    
    SECTION("WhenTwoInvalidCoinsAreInsertedThenReturnBothCoins"){
        vendingMachine->acceptCoin(*penny);
        vendingMachine->acceptCoin(*unknownCoin);
        REQUIRE(vendingMachine->getCoinReturn() == "UnknownCoin, Penny, ");
    }
    
    SECTION("WhenInvalidAndValidCoinsAreInsertedOnlyReturnInvalidCoins")
    {
        vendingMachine->acceptCoin(*dime);
        vendingMachine->acceptCoin(*unknownCoin);
        vendingMachine->acceptCoin(*nickel);
        vendingMachine->acceptCoin(*penny);
        vendingMachine->acceptCoin(*quarter);
        vendingMachine->acceptCoin(*unknownCoin);
        REQUIRE(vendingMachine->getCoinReturn() == "UnknownCoin, Penny, UnknownCoin, ");
    }
    
    //cleanup
    delete quarter;
    quarter = NULL;
    delete dime;
    dime = NULL;
    delete nickel;
    nickel = NULL;
    delete penny;
    penny = NULL;
    delete unknownCoin;
    unknownCoin = NULL;
    delete vendingMachine;
    vendingMachine = NULL;
}

TEST_CASE("TestSelectProductFunction") {
    
    SECTION("WhenColaIsSelectedThenDispenseCola")
    {
        VendingMachine* vendingMachine = new VendingMachine;
        
        //init array of quarters
        std::array<InsertableObject, 4> quarters;
        for(int i = 0; i < quarters.size(); i++)
        {
            quarters[i].weight = QUARTER_WEIGHT;
            quarters[i].diameter = QUARTER_DIAMETER;
        }
        
        //dispense quarters
        for(int i = 0; i < quarters.size(); i++)
        {
            vendingMachine->acceptCoin(quarters[i]);
        }
        REQUIRE(vendingMachine->display() == "1.00");
                
        vendingMachine->dispenseProduct(VendingMachine::cola);
        REQUIRE(vendingMachine->display() == "THANK YOU");
        REQUIRE(vendingMachine->display() == "INSERT COIN");
    }
    
    SECTION("WhenChipsIsSelectedThenDispenseChips")
    {
        VendingMachine* vendingMachine = new VendingMachine;
        
        //init array of quarters
        std::array<InsertableObject, 2> quarters;
        for(int i = 0; i < quarters.size(); i++)
        {
            quarters[i].weight = QUARTER_WEIGHT;
            quarters[i].diameter = QUARTER_DIAMETER;
        }
        
        //dispense quarters
        for(int i = 0; i < quarters.size(); i++)
        {
            vendingMachine->acceptCoin(quarters[i]);
        }
        REQUIRE(vendingMachine->display() == "0.50");
        
        vendingMachine->dispenseProduct(VendingMachine::chips);
        REQUIRE(vendingMachine->display() == "THANK YOU");
        REQUIRE(vendingMachine->display() == "INSERT COIN");
    }

    
    SECTION("WhenCandyIsSelectedThenDispenseCandy")
    {
        VendingMachine* vendingMachine = new VendingMachine;
        
        //init array of nickels
        std::array<InsertableObject, 13> nickels;
        for(int i = 0; i < nickels.size(); i++)
        {
            nickels[i].weight = NICKEL_WEIGHT;
            nickels[i].diameter = NICKEL_DIAMETER;
        }
        
        //dispense nickels
        for(int i = 0; i < nickels.size(); i++)
        {
            vendingMachine->acceptCoin(nickels[i]);
        }
        REQUIRE(vendingMachine->display() == "0.65");
        
        vendingMachine->dispenseProduct(VendingMachine::candy);
        REQUIRE(vendingMachine->display() == "THANK YOU");
        REQUIRE(vendingMachine->display() == "INSERT COIN");
    }
    
    SECTION("WhenInsufficientFundsThenDisplayPriceOfItemThenInsertCoin")
    {
        VendingMachine* vendingMachine = new VendingMachine;
        
        //init array of nickels
        std::array<InsertableObject, 13> nickels;
        for(int i = 0; i < nickels.size(); i++)
        {
            nickels[i].weight = NICKEL_WEIGHT;
            nickels[i].diameter = NICKEL_DIAMETER;
        }
        
        //dispense nickels
        for(int i = 0; i < nickels.size(); i++)
        {
            vendingMachine->acceptCoin(nickels[i]);
        }
        REQUIRE(vendingMachine->display() == "0.65");
        
        vendingMachine->dispenseProduct(VendingMachine::candy);
        REQUIRE(vendingMachine->display() == "THANK YOU");
        REQUIRE(vendingMachine->display() == "INSERT COIN");
    }
}


