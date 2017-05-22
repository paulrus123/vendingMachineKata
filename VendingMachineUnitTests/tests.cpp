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


std::vector<InsertableObject> initialStockingOfMoneyInMachine()
{
    std::array<InsertableObject, 12> initialCoinsToStock; // create std::array for ease of use (no manual memory allocation)
    std::vector<InsertableObject> initialCoinsToStockVector;
    for(int i = 0; i < initialCoinsToStock.size(); i++)
    {
        if(i < 4)
        {
            initialCoinsToStock[i].weight = QUARTER_WEIGHT;
            initialCoinsToStock[i].diameter = QUARTER_DIAMETER;
        }
        else if(i<8)
        {
            initialCoinsToStock[i].weight = DIME_WEIGHT;
            initialCoinsToStock[i].diameter = DIME_DIAMETER;
        }
        else
        {
            initialCoinsToStock[i].weight = NICKEL_WEIGHT;
            initialCoinsToStock[i].diameter = NICKEL_DIAMETER;
        }
        initialCoinsToStockVector.push_back(initialCoinsToStock[i]);
    }
    return initialCoinsToStockVector;
}


/************************************************************************************
 * TestAcceptCoinsFunction: Test cases related to the "Accept Coins" section of
 * the requirements.
 ************************************************************************************/
TEST_CASE("TestAcceptCoinsFunction") {
    //Setup
    VendingMachine* vendingMachine = new VendingMachine;
    vendingMachine->stockMoneyInMachine(initialStockingOfMoneyInMachine());
    
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
 ************************************************************************************/
TEST_CASE("TestSelectProductFunction") {
    VendingMachine* vendingMachine = new VendingMachine;
    vendingMachine->stockMoneyInMachine(initialStockingOfMoneyInMachine());

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
        secondVendingMachine->stockMoneyInMachine(initialStockingOfMoneyInMachine());
        
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
        thirdVendingMachine->stockMoneyInMachine(initialStockingOfMoneyInMachine());
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
 ************************************************************************************/
TEST_CASE("TestMakeChangeFunction") {
    VendingMachine* vendingMachine = new VendingMachine;
    vendingMachine->stockMoneyInMachine(initialStockingOfMoneyInMachine());
    REQUIRE(vendingMachine->display() == "INSERT COIN");
    
    //init array of quarters
    std::array<InsertableObject, 8> quarters; //2 dollars of quarters
    for(int i = 0; i < quarters.size(); i++)
    {
        quarters[i].weight = QUARTER_WEIGHT;
        quarters[i].diameter = QUARTER_DIAMETER;
    }
    
    std::array<InsertableObject, 20> dimes; //2 dollars of dimes
    for(int i = 0; i < dimes.size(); i++)
    {
        dimes[i].weight = DIME_WEIGHT;
        dimes[i].diameter = DIME_DIAMETER;
    }
    
    std::array<InsertableObject, 40> nickels; //2 dollars of nickels
    for(int i = 0; i < nickels.size(); i++)
    {
        nickels[i].weight = NICKEL_WEIGHT;
        nickels[i].diameter = NICKEL_DIAMETER;
    }
    
    SECTION("MakeChangeFromQuartersAndChips")
    {
        //dispense all the quarters
        for(int i = 0; i < 4; i++)
        {
            vendingMachine->acceptCoin(quarters[i]);
        }
        
        //select chips
        vendingMachine->dispenseProduct(VendingMachine::chips);
        REQUIRE(vendingMachine->getCoinReturn() == "Quarter, Quarter, ");
    }
    
    SECTION("MakeChangeFromQuartersAndCola")
    {
        //dispense all the quarters
        for(int i = 0; i < quarters.size(); i++)
        {
            vendingMachine->acceptCoin(quarters[i]);
        }
        
        //select chips
        vendingMachine->dispenseProduct(VendingMachine::cola);
        REQUIRE(vendingMachine->getCoinReturn() == "Quarter, Quarter, Quarter, Quarter, ");
    }
    
    SECTION("MakeChangeFromQuartersAndDimesAndCola")
    {
        //dispense 5 quarters
        for(int i = 0; i < 5; i++)
        {
            vendingMachine->acceptCoin(quarters[i]);
        }
        
        //dispense 2 dimes
        for(int i = 0; i < 2; i++)
        {
            vendingMachine->acceptCoin(dimes[i]);
        }
        
        //select cola
        vendingMachine->dispenseProduct(VendingMachine::cola);
        REQUIRE(vendingMachine->getCoinReturn() == "Dime, Dime, Quarter, ");
    }
    
    SECTION("MakeChangeFromQuartersAndDimesAndNickelsAndCola")
    {
        //dispense 5 quarters
        for(int i = 0; i < 5; i++)
        {
            vendingMachine->acceptCoin(quarters[i]);
        }
        
        //dispense 1 dime
        for(int i = 0; i < 1; i++)
        {
            vendingMachine->acceptCoin(dimes[i]);
        }
        
        //dispense 1 nickel
        for(int i = 0; i < 1; i++)
        {
            vendingMachine->acceptCoin(nickels[i]);
        }
        
        //select cola
        vendingMachine->dispenseProduct(VendingMachine::cola);
        REQUIRE(vendingMachine->getCoinReturn() == "Nickel, Dime, Quarter, ");
    }
    
    SECTION("MakeChangeFromQuartersAndDimesAndNickelsAndChips")
    {
        //dispense 3 quarters
        for(int i = 0; i < 3; i++)
        {
            vendingMachine->acceptCoin(quarters[i]);
        }
        
        //dispense 1 dime
        for(int i = 0; i < 1; i++)
        {
            vendingMachine->acceptCoin(dimes[i]);
        }
        
        //dispense 1 nickel
        for(int i = 0; i < 1; i++)
        {
            vendingMachine->acceptCoin(nickels[i]);
        }
        
        //select chips
        vendingMachine->dispenseProduct(VendingMachine::chips);
        REQUIRE(vendingMachine->getCoinReturn() == "Nickel, Dime, Quarter, ");
    }
    
    SECTION("MakeChangeFromQuartersAndDimesAndCandy")
    {
        //dispense 3 quarters
        for(int i = 0; i < 3; i++)
        {
            vendingMachine->acceptCoin(quarters[i]);
        }
        
        //dispense 1 dime
        for(int i = 0; i < 1; i++)
        {
            vendingMachine->acceptCoin(dimes[i]);
        }
        
        //select candy
        vendingMachine->dispenseProduct(VendingMachine::candy);
        REQUIRE(vendingMachine->getCoinReturn() == "Dime, Dime, ");
    }
}

/************************************************************************************
 * TestReturnCoinsFunction: Test cases related to the "Return Coins" section of
 * the requirements.
 ************************************************************************************/
TEST_CASE("TestReturnCoinsFunction")
{
    VendingMachine* vendingMachine = new VendingMachine;
    vendingMachine->stockMoneyInMachine(initialStockingOfMoneyInMachine());
    REQUIRE(vendingMachine->display() == "INSERT COIN");
    
    //init array of quarters
    std::array<InsertableObject, 4> quarters;
    for(int i = 0; i < quarters.size(); i++)
    {
        quarters[i].weight = QUARTER_WEIGHT;
        quarters[i].diameter = QUARTER_DIAMETER;
    }
    
    std::array<InsertableObject, 5> dimes;
    for(int i = 0; i < dimes.size(); i++)
    {
        dimes[i].weight = DIME_WEIGHT;
        dimes[i].diameter = DIME_DIAMETER;
    }
    
    std::array<InsertableObject, 4> nickels;
    for(int i = 0; i < nickels.size(); i++)
    {
        nickels[i].weight = NICKEL_WEIGHT;
        nickels[i].diameter = NICKEL_DIAMETER;
    }
    
    std::array<InsertableObject, 4> pennies;
    for(int i = 0; i < pennies.size(); i++)
    {
        pennies[i].weight = PENNY_WEIGHT;
        pennies[i].diameter = PENNY_DIAMETER;
    }
    
    SECTION("TestReturnQuarters")
    {
        for(int i = 0; i < 3; i++)
        {
            vendingMachine->acceptCoin(quarters[i]);
        }
        vendingMachine->coinReturnPressed();
        REQUIRE(vendingMachine->getCoinReturn() == "Quarter, Quarter, Quarter, ");
    }
    
    SECTION("TestReturnDimes")
    {
        for(int i = 0; i < 3; i++)
        {
            vendingMachine->acceptCoin(dimes[i]);
        }
        vendingMachine->coinReturnPressed();
        REQUIRE(vendingMachine->getCoinReturn() == "Dime, Dime, Dime, ");
    }
    
    SECTION("TestReturnNickels")
    {
        for(int i = 0; i < 3; i++)
        {
            vendingMachine->acceptCoin(nickels[i]);
        }
        vendingMachine->coinReturnPressed();
        REQUIRE(vendingMachine->getCoinReturn() == "Nickel, Nickel, Nickel, ");
    }
    
    SECTION("WhenNoMoneyIsInsertedThenReturnNothing")
    {
        REQUIRE(vendingMachine->getCoinReturn() == "Coin return is empty");
    }
    
    SECTION("TestReturnMultipleValidCoinTypes")
    {
        for(int i = 0; i < 2; i++)
        {
            vendingMachine->acceptCoin(nickels[i]);
            vendingMachine->acceptCoin(dimes[i]);
            vendingMachine->acceptCoin(quarters[i]);

        }
        vendingMachine->coinReturnPressed();
        REQUIRE(vendingMachine->getCoinReturn() == "Nickel, Nickel, Dime, Dime, Quarter, Quarter, ");
    }

    SECTION("TestReturnValidCoinsWhileInvalidCoinsAlreadyInCoinReturn")
    {
        for(int i = 0; i < 2; i++)
        {
            vendingMachine->acceptCoin(nickels[i]);
            vendingMachine->acceptCoin(dimes[i]);
            vendingMachine->acceptCoin(quarters[i]);
            vendingMachine->acceptCoin(pennies[i]);
        }
        
        REQUIRE(vendingMachine->getCoinReturn() == "Penny, Penny, ");
        vendingMachine->coinReturnPressed();
        REQUIRE(vendingMachine->getCoinReturn() == "Nickel, Nickel, Dime, Dime, Quarter, Quarter, Penny, Penny, ");
    }
    
    SECTION("TestReturnCorrectAmountOfMoneyWhenMachineHasMoneyFromPreviousPurchase")
    {
        for(int i = 0; i < 4; i++) //one dollar of quarters
        {
            vendingMachine->acceptCoin(quarters[i]);
        }
        REQUIRE(vendingMachine->display() == "1.00");
        vendingMachine->dispenseProduct(VendingMachine::cola);
        REQUIRE(vendingMachine->display() == "THANK YOU");
        REQUIRE(vendingMachine->display() == "INSERT COIN");
        
        for(int i = 0; i < dimes.size(); i++)
        {
            vendingMachine->acceptCoin(dimes[i]);
        }
        
        vendingMachine->coinReturnPressed();
        REQUIRE(vendingMachine->getCoinReturn() == "Dime, Dime, Dime, Dime, Dime, ");
    }
}

/************************************************************************************
 * TestSoldOutFunction: Test cases related to the "Sold Out" section of
 * the requirements.
 ************************************************************************************/
TEST_CASE("TestSoldOutFunction")
{
    VendingMachine* vendingMachine = new VendingMachine(0,0,0); //new vending machine with 0 of each item
    vendingMachine->stockMoneyInMachine(initialStockingOfMoneyInMachine());
    REQUIRE(vendingMachine->display() == "INSERT COIN");
    
    SECTION("WhenNoMoneyInsertedAndItemIsSoldOutThenDisplaySoldOut")
    {
        //cola
        vendingMachine->dispenseProduct(VendingMachine::cola);
        REQUIRE(vendingMachine->display() == "SOLD OUT");
        REQUIRE(vendingMachine->display() == "INSERT COIN");
        
        //chips
        vendingMachine->dispenseProduct(VendingMachine::chips);
        REQUIRE(vendingMachine->display() == "SOLD OUT");
        REQUIRE(vendingMachine->display() == "INSERT COIN");
        
        //candy
        vendingMachine->dispenseProduct(VendingMachine::candy);
        REQUIRE(vendingMachine->display() == "SOLD OUT");
        REQUIRE(vendingMachine->display() == "INSERT COIN");
    }
    
    SECTION("WhenSomeMoneyInsertedAndItemIsSoldOutThenDisplaySoldOut")
    {
        //init array of quarters
        std::array<InsertableObject, 8> quarters; //$2 of quarters
        for(int i = 0; i < quarters.size(); i++)
        {
            quarters[i].weight = QUARTER_WEIGHT;
            quarters[i].diameter = QUARTER_DIAMETER;
        }
        
        for(int i = 0; i < quarters.size(); i++)
        {
            vendingMachine->acceptCoin(quarters[i]);
        }
        REQUIRE(vendingMachine->display() == "2.00");
        
        //cola
        vendingMachine->dispenseProduct(VendingMachine::cola);
        REQUIRE(vendingMachine->display() == "SOLD OUT");
        REQUIRE(vendingMachine->display() == "2.00");
        
        //chips
        vendingMachine->dispenseProduct(VendingMachine::chips);
        REQUIRE(vendingMachine->display() == "SOLD OUT");
        REQUIRE(vendingMachine->display() == "2.00");
        
        //candy
        vendingMachine->dispenseProduct(VendingMachine::candy);
        REQUIRE(vendingMachine->display() == "SOLD OUT");
        REQUIRE(vendingMachine->display() == "2.00");
    }
    
    SECTION("WhenOneStockLeftThenDispenseProductAndNextCallDisplaySoldOut")
    {
        VendingMachine* stockedVendingMachine = new VendingMachine(1,1,1); //new vending machine with 1 of each item
        stockedVendingMachine->stockMoneyInMachine(initialStockingOfMoneyInMachine());
        REQUIRE(stockedVendingMachine->display() == "INSERT COIN");
        
        //init array of quarters
        std::array<InsertableObject, 8> quarters; //$2 of quarters
        for(int i = 0; i < quarters.size(); i++)
        {
            quarters[i].weight = QUARTER_WEIGHT;
            quarters[i].diameter = QUARTER_DIAMETER;
        }
        
        for(int i = 0; i < quarters.size(); i++)
        {
            stockedVendingMachine->acceptCoin(quarters[i]);
        }
        REQUIRE(stockedVendingMachine->display() == "2.00");
        
        stockedVendingMachine->dispenseProduct(VendingMachine::cola);
        REQUIRE(stockedVendingMachine->display() == "THANK YOU");
        
        stockedVendingMachine->dispenseProduct(VendingMachine::cola);
        REQUIRE(stockedVendingMachine->display() == "SOLD OUT");
        REQUIRE(stockedVendingMachine->display() == "INSERT COIN");
        
        for(int i = 0; i < quarters.size(); i++)
        {
            stockedVendingMachine->acceptCoin(quarters[i]);
        }
        
        stockedVendingMachine->dispenseProduct(VendingMachine::chips);
        REQUIRE(stockedVendingMachine->display() == "THANK YOU");
        
        stockedVendingMachine->dispenseProduct(VendingMachine::chips);
        REQUIRE(stockedVendingMachine->display() == "SOLD OUT");
        REQUIRE(stockedVendingMachine->display() == "INSERT COIN");
        
        for(int i = 0; i < quarters.size(); i++)
        {
            stockedVendingMachine->acceptCoin(quarters[i]);
        }
        
        stockedVendingMachine->dispenseProduct(VendingMachine::candy);
        REQUIRE(stockedVendingMachine->display() == "THANK YOU");
        
        stockedVendingMachine->dispenseProduct(VendingMachine::candy);
        REQUIRE(stockedVendingMachine->display() == "SOLD OUT");
        REQUIRE(stockedVendingMachine->display() == "INSERT COIN");
        
    }
}

/************************************************************************************
 * TestExactChangeFunction: Test cases related to the "Exact Change" section of
 * the requirements.
 ************************************************************************************/
TEST_CASE("TestExactChangeFunction")
{

    /*For the 50cent case (chips) manual calculation reveals that the machine will need at least:
     * 1 nickel (55 cent input) assuming 1 quarter and 3 dimes input
     * nothing (60 cent input) - any case required that at least 2 nickels or one dime is input by user
     * 1 nickel(65 cent input) - assuming one quarter and 4 dimes input
     * Nothing(70 cent input)  - any case requires that user inputs soizme combination of 20cents in nickels/dimes that can be directly returned
     *
     * So if the machine does not contain at least 1 nickel, then must display EXACT CHANGE
     */
    SECTION("MachineDoesNotHaveANickelThereforeDisplayExactChange")
    {
        VendingMachine* vendingMachine = new VendingMachine;
        vendingMachine->stockMoneyInMachine(initialStockingOfMoneyInMachine());
        REQUIRE(vendingMachine->display() == "INSERT COIN");
 
        //init array of quarters and dimes
        std::array<InsertableObject, 8> quartersAndDimes; //2 dollars of quarters
        std::vector<InsertableObject> quartersAndDimesVec;

        for(int i = 0; i < quartersAndDimes.size(); i++)
        {
            if(i%2)
            {
                quartersAndDimes[i].weight = QUARTER_WEIGHT;
                quartersAndDimes[i].diameter = QUARTER_DIAMETER;
            }
            else
            {
                quartersAndDimes[i].weight = DIME_WEIGHT;
                quartersAndDimes[i].diameter = DIME_WEIGHT;
            }
            quartersAndDimesVec.push_back(quartersAndDimes[i]);
        }
    
        vendingMachine->stockMoneyInMachine(quartersAndDimesVec);
        REQUIRE(vendingMachine->display() == "EXACT CHANGE");
        
        delete vendingMachine;
        vendingMachine = NULL;
    }
    
    /* For the 65cent case (candy) manual calculation reveals that the machine will need at least:
     * 1 nickel (70cent input) assuming only quarter and dimes were input
     * 1 dime or 2 nickels (75cents input) assuming only quarters were input
     * 1 nickel (80 cents input) assuming only quarters and dimes input
     * 2 nickels or one dime (85 cents input) assuming three quarters and one dime
     *
     * So if the machine does not contain 2 nickels OR one dime and one nickel, then must display EXACT CHANGE
     */
    SECTION("MachineDoesNotHaveATwoNickelsORADimeAndANickelThereforeDisplayExactChange")
    {
        
    }

    /* No extra tests are needed for the Cola case, since it is 2X the price of chips, there are no unique scenarios that are not covered
     * by the chips cases
     */
    
    
//Deprecated - to be deleted once algorithm is developed //
    /* Exact change for Chips. Chips costs 0.50. The cases in which exact change could be needed are:
     *   User inputs 0.55
     *   User inputs 0.60
     *   User Inputs 0.65
     *   User inputs 0.70
     * Any more than 25cents over the price will repeat those same bases cases (since Quarter is our largest accepted coin
     *
     */
    /* Internal calculations, not external test cases
     
     //Case 55 - must return 5cents
    SECTION("TestExactChangeNotRequiredIfTwoQuartersAndOneNickel") {}
    
    SECTION("TestExactChangeRequiredIfOneQuarterAndThreeDimes") {}
    
    SECTION("TestExactChangeRequiredIfOneQuarterAndThreeDimesButMachineHasANickel") {}
    
    //Case 60 - must return 10 cents
    SECTION("TestExactChangeNotRequiredIfTwoQuartersAndTwoNickels") {}
    
    //Case 65 - must return 15 cents
    SECTION("TestExactChangeRequiredIfOneQuarterAndFourDimes") {}
    
    SECTION("TestExactChangeNotRequiredIfTwoQuartersOneDimeAndOneNickel") {}
    
    SECTION("TestExactChangeNotRequiredIfTwoQuartersAndThreeNickels") {}
    
    //Case 70 - must return 20 cents
    SECTION("TestExactChangeNotRequiredIfTwoQuartersAndTwoDimes") {}
    
        //No cases exist where exact change will be required
    
    */
    
    
    /* Exact change for Candy. Candy costs 0.65. The cases in which exact change could be needed are:
     *   User inputs 0.70
     *   User inputs 0.75
     *   User Inputs 0.80
     *   User inputs 0.85
     * Any more than 25cents over the price will repeat those same bases cases (since Quarter is our largest accepted coin
     */
    
    /* Internal calculations, not external test cases
     
     //Case 70 - must return 5cents
    SECTION("TestExactChangeNotRequiredIfTwoQuartersAndFourNickels") {}
    
    SECTION("TestExactChangeRequiredIfTwoQuartersAndTwoDimes") {}
    
    
    //Case 75 - must return 10 cents
    SECTION("TestExactChangeRequiredIfThreeQuarters") {}
    
    SECTION("TestExactChangeNotRequiredIfTwoQuartersAndTwoDimesAndANickel") {}
    
    //Case 80 - must return 15 cents
    SECTION("TestExactChangeNotRequiredIfOneQuarterFiveDimesAndOneNickel") {}
    
    SECTION("TestExactChangeRequiredIfTenDimes") {}
    
    //Case 85 - must return 20 cents
    SECTION("TestExactChangeNotRequiredIfTenDimesAndOneNickel") {}
    
    SECTION("TestExactChangeRequiredIfThreeQuartersAndOneDime") {}
    
    //Test cases not needed for Cola, since Cola is 2x price of Chips. Therefore the same change cases will apply.
     
     */

}
