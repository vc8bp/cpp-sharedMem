#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sys/ipc.h>
#include <sys/shm.h>
#include <memory>
#include <cstring>
#include "./size.hpp"

auto safeStrncpy(char* dest, const char* src, size_t size) {
    if (src) strncpy(dest, src, size - 1);
    dest[size - 1] = '\0'; 
};

void insertValuesToObj(Obj* obj, std::string* str){
    const char* cstrr = str->c_str();
    char* strr = strdup(cstrr);

    if (!strr) {
        std::cerr << "Memory allocation failed for strr" << std::endl;
        return;
    }


    safeStrncpy(obj->exchange, strtok(strr, ","), MAX_STRING_SIZE - 1);

    safeStrncpy(obj->symbol, strtok(NULL, ","), MAX_STRING_SIZE - 1);
    safeStrncpy(obj->isin, strtok(NULL, ","), MAX_STRING_SIZE - 1);
    safeStrncpy(obj->scripcode, strtok(NULL, ","), MAX_STRING_SIZE - 1);
    safeStrncpy(obj->securityType, strtok(NULL, ","), MAX_STRING_SIZE - 1);
    safeStrncpy(obj->securityDesc, strtok(NULL, ","), MAX_STRING_SIZE - 1);
    safeStrncpy(obj->expiryDate, strtok(NULL, ","), MAX_STRING_SIZE - 1);
    safeStrncpy(obj->optType, strtok(NULL, ","), MAX_STRING_SIZE - 1);
    obj->strikePrice = std::stof(strtok(NULL, ","));
    obj->multiplier = std::stof(strtok(NULL, ","));
    obj->tickSize = std::stof(strtok(NULL, ","));
    obj->lotSize = static_cast<uint32_t>(std::atoi(strtok(NULL, ",")));
    obj->divider = std::stof(strtok(NULL, ","));
    safeStrncpy(obj->baseCurrency, strtok(NULL, ","), MAX_STRING_SIZE - 1);
    safeStrncpy(obj->settleCurrency, strtok(NULL, ","), MAX_STRING_SIZE - 1);
    obj->digits = static_cast<uint32_t>(std::atoi(strtok(NULL, ",")));
    obj->lowerBand = std::stof(strtok(NULL, ","));
    obj->upperBand = std::stof(strtok(NULL, ","));
    obj->prevClose = std::stof(strtok(NULL, ","));
    safeStrncpy(obj->productId, strtok(NULL, ","), MAX_STRING_SIZE - 1);
    obj->initialMargin = std::stof(strtok(NULL, ","));
    obj->tenderMargin = std::stof(strtok(NULL, ","));
    obj->totalMargin = std::stof(strtok(NULL, ","));
    obj->additionalLongMargin = std::stof(strtok(NULL, ","));
    obj->additionalShortMargin = std::stof(strtok(NULL, ","));
    obj->deliveryLongMargin = std::stof(strtok(NULL, ","));
    obj->deliveryShortMargin = std::stof(strtok(NULL, ","));
    obj->mwpl = std::stof(strtok(NULL, ","));
    obj->suspend = std::string(strtok(NULL, ",")) == "True";
    obj->algoRestricted = std::string(strtok(NULL, ",")) == "True";
    obj->restrictedScript = std::string(strtok(NULL, ",")) == "True";
    obj->bcastInclude = std::string(strtok(NULL, ",")) == "True";
    safeStrncpy(obj->productGroupName, strtok(NULL, ","), MAX_STRING_SIZE - 1);
    obj->haircut = std::stof(strtok(NULL, ","));
    safeStrncpy(obj->underlineSecurityId, strtok(NULL, ","), MAX_STRING_SIZE - 1);
    safeStrncpy(obj->underlineSymbol, strtok(NULL, ","), MAX_STRING_SIZE - 1);
    obj->yearlyHigh = std::stof(strtok(NULL, ","));
    obj->yearlyLow = std::stof(strtok(NULL, ","));
    safeStrncpy(obj->feedExchange, strtok(NULL, ","), MAX_STRING_SIZE - 1);
    safeStrncpy(obj->feedSecurityId, strtok(NULL, ","), MAX_STRING_SIZE - 1);
    obj->recNo = static_cast<uint32_t>(std::atoi(strtok(NULL, ",")));
    obj->maxSingleTransQty = static_cast<uint32_t>(std::atoi(strtok(NULL, ",")));
    safeStrncpy(obj->segment, strtok(NULL, ","), MAX_STRING_SIZE - 1);
    obj->token = static_cast<uint32_t>(std::atoi(strtok(NULL, ",")));

    free(strr);
}


int main() {
    std::vector<int> shmIds;

    std::string str;

    std::ifstream MyReadFile("./contract.csv");
    if (!MyReadFile) {
        std::cerr << "Error opening file" << std::endl;
        return 1;
    }

    int count = 1;

    while (getline(MyReadFile, str)) {
        if(str.empty()) continue;


        std::cout << "\033[2J\033[H";
        std::cout << "Creating " << count++ << "'th token's shared memory segment...\n";

        Obj contract;
        insertValuesToObj(&contract, &str);

        key_t key = ftok("./sharedMem", contract.token);
        if (key == -1) {
            std::cerr << "ftok failed" << std::endl;
            continue;
        }

        int shmId = shmget(key, sizeof(Obj), 0666 | IPC_CREAT);
        shmIds.push_back(shmId);

        if (shmId == -1) {
            std::cerr << "shmget failed with errno: " << errno << std::endl;
            continue;
        }

        void* mem = shmat(shmId, nullptr, 0);
        if (mem == (void*)-1) {
            std::cerr << "shmat failed" << std::endl;
            continue;
        }
        memcpy(mem, &contract, sizeof(Obj));


        if (shmdt(mem) == -1) {
            std::cerr << "shmdt failed with errno: " << errno << std::endl;
        }
    }

    std::cout<<"closing file" << std::endl;
    MyReadFile.close();
    std::cout<<"Press any key to Delete all the SHMS that we created!!" << std::endl;
    std::cin.get();

    std::cout<< "Deleting shms" << std::endl;



    for(int id: shmIds){
        shmctl(id, IPC_RMID, NULL);
        std::cout << "\033[2J\033[H";
        std::cout << "Deleting shared memory segment with ID: " << id << "...\n";
    }

    return 0;
}
