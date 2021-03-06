//
// Created by AM on 10/20/2020.
//

#include <iostream>
#include "ResidentialBuilding.h"
#include "ResidentialTennant.h"

ResidentialBuilding::ResidentialBuilding() {
    switch (rand() % 4){ // is there a better way to do this?
        case 0: loc = NE; break;
        case 1: loc = SE; break;
        case 2: loc = SW; break;
        case 3: loc = NW; break;
    }
    propertyValue = (rand() % 500000) + 100000;
    propertyValueWithEvent = propertyValue;
    mortgageTotal = propertyValue;
    mortgageDuration = (rand() % 180 + 180);
    mortgageMonthly = mortgageTotal / mortgageDuration;

    hasTennant = true;
    myTennant = new ResidentialTennant();

    rent = 500;
}

ResidentialBuilding::ResidentialBuilding(const ResidentialBuilding &in) {

}

ResidentialBuilding::~ResidentialBuilding() {
    if(&myTennant != nullptr) {
        Tennant * c = myTennant;
        delete c;
    }
}


ResidentialBuilding &ResidentialBuilding::operator=(const ResidentialBuilding &in) {
    if(this == &in){
        return *this;
    }
    ResidentialBuilding * newResidentialBuilding = new ResidentialBuilding(in);
    return *newResidentialBuilding;
}

void ResidentialBuilding::adjustRentTo(const int & in, const int & space = 0){
    rent = in;
    if(hasTennant){
        if(myTennant->monthlyBudget < rent){
            if(myTennant->agreeability < 2) {
                std::cout << "\nThe tenant here is refusing to pay rent!";
                myTennant->willingToPay = false;
            }else{
                std::cout << "\nThe tenant here has vacated the property!";
                hasTennant = false;
                myTennant->willingToPay = false;
            }
        }else{ // if now able to pay
            if(myTennant->willingToPay == false) {
                std::cout << "\nThe tenant here is willing to pay again!";
                myTennant->willingToPay = true;
            }
        }
    }
}

std::ostream &ResidentialBuilding::operator<<(std::ostream &_stream) {
    _stream << "[RES: " << dictateLocation() << ". Mortgage: $" << mortgageMonthly << " for " << mortgageDuration << " months. Rent: " <<rent << ", Tenant: " << hasTennant << "]";
    return _stream;
}

ResidentialBuilding::operator std::string() const {
    return "[RES: " + dictateLocation() + ":<" + std::to_string(propertyValueWithEvent)+"/"+std::to_string(propertyValue)+"> Mortgage: $" + std::to_string(mortgageMonthly) + " for " + std::to_string(mortgageDuration) + " months. Rent: " + std::to_string(rent) + ", Tenant: " + std::to_string(hasTennant) + "]";
}

std::string ResidentialBuilding::ts() {
    return "[RES: " + dictateLocation() + ":<" + std::to_string(propertyValueWithEvent)+"/"+std::to_string(propertyValue)+"> Mortgage: $" + std::to_string(mortgageMonthly) + " for " + std::to_string(mortgageDuration) + " months. Rent: " + std::to_string(rent) + ", Tenant: " + std::to_string(hasTennant) + "]";
}
















