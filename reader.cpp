#include <iostream>
#include <sys/ipc.h>
#include <sys/shm.h>
#include "./size.hpp"

int main(int argc, char *argv[]) {
    if(argc <= 1){
        std::cout << "Please providea token to read from shm" << std::endl;
        return 1;
    }

    key_t key = ftok("./sharedMem", std::atoi(argv[1]) );
    key_t id = shmget(key, sizeof(Obj), 0666);

    if(id == -1){
        std::cout<< " NO shm found for this token : " << argv[1] << std::endl;
        return 0;
    }

    void *mem = shmat(id, NULL, 0);

    Obj* obj = static_cast<Obj*>(mem);

    std::cout << "Token: " << obj->token << std::endl;
    std::cout << "Exchange: " << obj->exchange << std::endl;
    std::cout << "Symbol: " << obj->symbol << std::endl;
    std::cout << "ISIN: " << obj->isin << std::endl;
    std::cout << "Scrip Code: " << obj->scripcode << std::endl;
    std::cout << "Security Type: " << obj->securityType << std::endl;
    std::cout << "Security Description: " << obj->securityDesc << std::endl;
    std::cout << "Expiry Date: " << obj->expiryDate << std::endl;
    std::cout << "Option Type: " << obj->optType << std::endl;
    std::cout << "Strike Price: " << obj->strikePrice << std::endl;
    std::cout << "Multiplier: " << obj->multiplier << std::endl;
    std::cout << "Tick Size: " << obj->tickSize << std::endl;
    std::cout << "Lot Size: " << obj->lotSize << std::endl;
    std::cout << "Divider: " << obj->divider << std::endl;
    std::cout << "Base Currency: " << obj->baseCurrency << std::endl;
    std::cout << "Settle Currency: " << obj->settleCurrency << std::endl;
    std::cout << "Digits: " << obj->digits << std::endl;
    std::cout << "Lower Band: " << obj->lowerBand << std::endl;
    std::cout << "Upper Band: " << obj->upperBand << std::endl;
    std::cout << "Previous Close: " << obj->prevClose << std::endl;
    std::cout << "Product ID: " << obj->productId << std::endl;
    std::cout << "Initial Margin: " << obj->initialMargin << std::endl;
    std::cout << "Tender Margin: " << obj->tenderMargin << std::endl;
    std::cout << "Total Margin: " << obj->totalMargin << std::endl;
    std::cout << "Additional Long Margin: " << obj->additionalLongMargin << std::endl;
    std::cout << "Additional Short Margin: " << obj->additionalShortMargin << std::endl;
    std::cout << "Delivery Long Margin: " << obj->deliveryLongMargin << std::endl;
    std::cout << "Delivery Short Margin: " << obj->deliveryShortMargin << std::endl;
    std::cout << "MWPL: " << obj->mwpl << std::endl;
    std::cout << "Suspend: " << (obj->suspend ? "True" : "False") << std::endl;
    std::cout << "Algo Restricted: " << (obj->algoRestricted ? "True" : "False") << std::endl;
    std::cout << "Restricted Script: " << (obj->restrictedScript ? "True" : "False") << std::endl;
    std::cout << "Broadcast Include: " << (obj->bcastInclude ? "True" : "False") << std::endl;
    std::cout << "Product Group Name: " << obj->productGroupName << std::endl;
    std::cout << "Haircut: " << obj->haircut << std::endl;
    std::cout << "Underline Security ID: " << obj->underlineSecurityId << std::endl;
    std::cout << "Underline Symbol: " << obj->underlineSymbol << std::endl;
    std::cout << "Yearly High: " << obj->yearlyHigh << std::endl;
    std::cout << "Yearly Low: " << obj->yearlyLow << std::endl;
    std::cout << "Feed Exchange: " << obj->feedExchange << std::endl;
    std::cout << "Feed Security ID: " << obj->feedSecurityId << std::endl;
    std::cout << "Record Number: " << obj->recNo << std::endl;
    std::cout << "Max Single Transaction Quantity: " << obj->maxSingleTransQty << std::endl;
    std::cout << "Segment: " << obj->segment << std::endl;
    std::cout << "-------------------------------------------------" << std::endl;


    return 0;
}