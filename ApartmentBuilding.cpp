//
// Created by AM on 10/20/2020.
//

#include <iostream>
#include "ApartmentBuilding.h"
#include "ResidentialTennant.h"

ApartmentBuilding::ApartmentBuilding() {
    switch (rand() % 4){ // is there a better way to do this?
        case 0: loc = NE; break;
        case 1: loc = SE; break;
        case 2: loc = SW; break;
        case 3: loc = NW; break;
    }
    propertyValue = (rand() % 300000) + 300000;
    propertyValueWithEvent = propertyValue;
    mortgageTotal = propertyValue;
    mortgageDuration = (rand() % 180 + 180);
    mortgageMonthly = mortgageTotal / mortgageDuration;
    rooms = 10;
    for(int i = 0 ; i < 10; i++){
        hasTennant[i] = true;
        tennantList[i] = new ResidentialTennant();
    }
    rent = 500;
}

ApartmentBuilding::ApartmentBuilding(const ApartmentBuilding &in) {

}

ApartmentBuilding::~ApartmentBuilding() {
    for(int i = 0 ; i < 10; i++){
        if(&tennantList[i] != nullptr){
            Tennant *  c = tennantList[i];
            delete c;
        }
    }
}


ApartmentBuilding &ApartmentBuilding::operator=(const ApartmentBuilding &in) {
    if(this == &in){
        return *this;
    }
    ApartmentBuilding * newApartmentBuilding = new ApartmentBuilding(in);
    return * newApartmentBuilding;
}

void ApartmentBuilding::adjustRentTo(const int &in, const int &space) {
    rent = in;
    for(int i = 0 ; i < 10; i++) {
        if (hasTennant[i]) {
            if (tennantList[i]->monthlyBudget < in) {
                if (tennantList[i]->agreeability < 2) {
                    std::cout << "\nTenant in space " << i << " is refusing to pay rent!\n";
                    tennantList[i]->willingToPay = false;
                } else {
                    std::cout << "\nTenant in space " << i << " has left the property!\n";
                    tennantList[i]->willingToPay = false;
                    hasTennant[i] = false;
                }
            } else { // if there is a tenant but is refusing to pay, and rent is now less than budget
                if (tennantList[i]->willingToPay == false) {
                    std::cout << "\nTenant in space " << i << " is beginning to pay rent again\n";
                    tennantList[i]->willingToPay = true;
                }
            }
        }
    }
}

std::ostream &ApartmentBuilding::operator<<(std::ostream &_stream) {
    _stream << "[APT " << dictateLocation() << ", mortgage: $" << mortgageMonthly << " for " << mortgageDuration << " months. Rent: " << rent << "]";
    return _stream;
}

ApartmentBuilding::operator std::string() const {
    return "[APT " + dictateLocation() + ":<" + std::to_string(propertyValueWithEvent)+"/"+std::to_string(propertyValue)+"> mortgage: $" + std::to_string(mortgageMonthly) + " for " + std::to_string(mortgageDuration) + " months. Rent: " + std::to_string(rent) + "]";
}

std::string ApartmentBuilding::ts() {
    return "[APT " + dictateLocation() + ":<" + std::to_string(propertyValueWithEvent)+"/"+std::to_string(propertyValue)+"> mortgage: $" + std::to_string(mortgageMonthly) + " for " + std::to_string(mortgageDuration) + " months. Rent: " + std::to_string(rent) + "]";
}
