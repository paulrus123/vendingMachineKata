//
//  tests.cpp
//  VendingMachineUnitTests
//
//  Created by Paul Sorenson on 5/11/17.
//  Copyright © 2017 Paul Sorenson. All rights reserved.
//


#define CATCH_CONFIG_MAIN  // This tells Catch to provide a main() - only do this in one cpp file
#include "catch.hpp"

#include "vendingMachine.hpp"

#include <iostream>
#include <array>


//test values of coin weights and diameters
#define QUARTER_WEIGHT 5.67f
#define QUARTER_DIAMETER 24.26f
#define DIME_WEIGHT 2.27f
#define DIME_DIAMETER 17.91f
#define NICKEL_WEIGHT 5.0f
#define NICKEL_DIAMETER 21.21f
#define PENNY_WEIGHT 2.5f
#define PENNY_DIAMETER 19.05f

/************************************************************************************
 * TestAcceptCoinsFunction: Test cases related to the "Accept Coins" section of
 * the requirements.
 */
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

/************************************************************************************
 * TestSelectProductFunction: Test cases related to the "Select Product" section of
 * the requirements.
 */
TEST_CASE("TestSelectProductFunction") {
    VendingMachine* vendingMachine = new VendingMachine;

    SECTION("WhenColaIsSelectedThenDispenseCola")
    {
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
    
    SECTION("WhenNoFundsThenDisplayPriceOfItemThenInsertCoin")
    {
        REQUIRE(vendingMachine->display() == "INSERT COIN");
        
        vendingMachine->dispenseProduct(VendingMachine::cola);
        REQUIRE(vendingMachine->display() == "PRICE 1.00");
        REQUIRE(vendingMachine->display() == "INSERT COIN");
        
        vendingMachine->dispenseProduct(VendingMachine::chips);
        REQUIRE(vendingMachine->display() == "PRICE 0.50");
        REQUIRE(vendingMachine->display() == "INSERT COIN");
        
        vendingMachine->dispenseProduct(VendingMachine::candy);
        REQUIRE(vendingMachine->display() == "PRICE 0.65");
        REQUIRE(vendingMachine->display() == "INSERT COIN");
    }
    
    SECTION("WhenInsufficientFundsThenDisplayPriceOfItemThenCurrentAmount")
    {
        //init array of nickels
        std::array<InsertableObject, 9> nickels; //45 cents of nickels
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
        REQUIRE(vendingMachine->display() == "0.45");
        
        vendingMachine->dispenseProduct(VendingMachine::cola);
        REQUIRE(vendingMachine->display() == "PRICE 1.00");
        REQUIRE(vendingMachine->display() == "0.45");
        
        vendingMachine->dispenseProduct(VendingMachine::chips);
        REQUIRE(vendingMachine->display() == "PRICE 0.50");
        REQUIRE(vendingMachine->display() == "0.45");
        
        vendingMachine->dispenseProduct(VendingMachine::candy);
        REQUIRE(vendingMachine->display() == "PRICE 0.65");
        REQUIRE(vendingMachine->display() == "0.45");
    }
    
    SECTION("WhenAddingMoreFundsThenItemWillBeDispensed")
    {
        VendingMachine* secondVendingMachine = new VendingMachine;
        
        //init array of nickels
        std::array<InsertableObject, 20> nickels; //1 dollar of nickels
        for(int i = 0; i < nickels.size(); i++)
        {
            nickels[i].weight = NICKEL_WEIGHT;
            nickels[i].diameter = NICKEL_DIAMETER;
        }
        
        //dispense 50 cents of nickels
        for(int i = 0; i < (nickels.size() - 10); i++)
        {
            secondVendingMachine->acceptCoin(nickels[i]);
        }
        
        REQUIRE(secondVendingMachine->display() == "0.50");
        
        secondVendingMachine->dispenseProduct(VendingMachine::cola);
        REQUIRE(secondVendingMachine->display() == "PRICE 1.00");
        REQUIRE(secondVendingMachine->display() == "0.50");
        
        //dispense another 50 cents of nickels
        for(int i = (nickels.size() - 10); i < nickels.size(); i++)
        {
            secondVendingMachine->acceptCoin(nickels[i]);
        }
        
        secondVendingMachine->dispenseProduct(VendingMachine::cola);
        REQUIRE(secondVendingMachine->display() == "THANK YOU");
        REQUIRE(secondVendingMachine->display() == "INSERT COIN");
        
        delete secondVendingMachine;
        secondVendingMachine = NULL;
    }
    
    SECTION("WhenProductIsDispensedCurrentAmountIsSetToZero")
    {
        VendingMachine* thirdVendingMachine = new VendingMachine;
        REQUIRE(thirdVendingMachine->display() == "INSERT COIN");
        
        //init array of dimes
        std::array<InsertableObject, 10> dimes; //1 dollar of dimes
        for(int i = 0; i < dimes.size(); i++)
        {
            dimes[i].weight = DIME_WEIGHT;
            dimes[i].diameter = DIME_DIAMETER;
        }
        
        //dispense entire dollar
        for(int i = 0; i < dimes.size(); i++)
        {
            thirdVendingMachine->acceptCoin(dimes[i]);
        }
        
        REQUIRE(thirdVendingMachine->display() == "1.00");
        
        thirdVendingMachine->dispenseProduct(VendingMachine::chips);
        REQUIRE(thirdVendingMachine->display() == "THANK YOU");
        REQUIRE(thirdVendingMachine->display() == "INSERT COIN");
        
        thirdVendingMachine->dispenseProduct(VendingMachine::chips);
        REQUIRE(thirdVendingMachine->display() == "PRICE 0.50");
        REQUIRE(thirdVendingMachine->display() == "INSERT COIN");
        
    }
    
    delete vendingMachine;
    vendingMachine = NULL;
}

/************************************************************************************
 * TestMakeChangeFunction: Test cases related to the "Make Change" section of
 * the requirements.
 */
TEST_CASE("TestMakeChangeFunction") {
    VendingMachine* vendingMachine = new VendingMachine;
    REQUIRE(vendingMachine->display() == "INSERT COIN");
    
    SECTION("MakeChangeFromQuarters")
    {
        //init array of quarters
        std::array<InsertableObject, 4> quarters; //1 dollar of quarters
        for(int i = 0; i < quarters.size(); i++)
        {
            quarters[i].weight = QUARTER_WEIGHT;
            quarters[i].diameter = QUARTER_DIAMETER;
        }
        
        //dispense all the quarters
        for(int i = 0; i < quarters.size(); i++)
        {
            vendingMachine->acceptCoin(quarters[i]);
        }
        
        //select chips
        vendingMachine->dispenseProduct(VendingMachine::chips);
        REQUIRE(vendingMachine->getCoinReturn() == "Quarter, Quarter, ");
    }
    
    
}




