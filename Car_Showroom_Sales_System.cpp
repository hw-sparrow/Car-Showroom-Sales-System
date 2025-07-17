#include <iostream>
#include <fstream>
#include <cstring>
#include <string>
#include <iomanip>

using namespace std;
const int MaxCars = 100;
const int MaxCustomers = 100;

class Showroom {
public:
    string Name, ContactNumber, Address, TaxRegNumber;

    void InputDetails() {
        cout << "Enter Showroom Name: "; getline(cin, Name);
        cout << "Enter Contact Number: "; getline(cin, ContactNumber);
        cout << "Enter Address: "; getline(cin, Address);
        cout << "Enter Sales Tax Registration Number: "; getline(cin, TaxRegNumber);
    }

    void DisplayDetails() {
        cout << "\nShowroom Name: " << Name << "\nContact: " << ContactNumber << "\nAddress: " << Address << "\nSales Tax Reg#: " << TaxRegNumber << endl;
    }
};

class Car {
public:
    string Model, Transmission, EngineNumber, ChassisNumber;
    float Price;
    int EngineSize, ManufactureYear;

    virtual void InputDetails() {
        cin.ignore();
        cout << "Enter Model: "; getline(cin, Model);
        cout << "Enter Price: "; cin >> Price;
        cout << "Enter Engine Size (cc): "; cin >> EngineSize;
        cin.ignore();
        cout << "Enter Transmission Type: "; getline(cin, Transmission);
        cout << "Enter Engine Number: "; getline(cin, EngineNumber);
        cout << "Enter Chassis Number: "; getline(cin, ChassisNumber);
        cout << "Enter Manufacture Year: "; cin >> ManufactureYear;
    }

    virtual void DisplayDetails() {
        cout << fixed << setprecision(2) << "Model: " << Model << " | Price: " << Price << " | Engine: " << EngineSize << "cc | Transmission: " << Transmission;
    }

    virtual float CalculateTax(int CurrentYear) {
        int Age = CurrentYear - ManufactureYear;

        if (Age > 5) {
            return Price * 0.15f;
        }
        else {
            return 0.0f;
        }
    }

    virtual bool Imported() { return false; }

    virtual void SaveToFile(ofstream& ShowroomFile) {
        ShowroomFile << "New Car: " << fixed << setprecision(2) << Model << " " << Price << " " << EngineSize << " " << Transmission << " " << EngineNumber << " " << ChassisNumber << " " << ManufactureYear << endl;
    }

    virtual ~Car() {}
};

class UsedCar : public Car {
protected:
    string RegistrationNo;

public:
    void InputDetails() override {
        Car::InputDetails();
        cout << "Enter Registration Number: "; cin >> RegistrationNo;
    }

    void DisplayDetails() override {
        Car::DisplayDetails();
        cout << " | Registration: " << RegistrationNo;
    }

    string getRegistrationNo() const {
        return RegistrationNo;
    }

    void SaveToFile(ofstream& ShowroomFile) override {
        ShowroomFile << "Used Car: " << fixed << setprecision(2) << Model << " " << Price << " " << EngineSize << " " << Transmission << " " << EngineNumber << " " << ChassisNumber << " " << ManufactureYear << " " << RegistrationNo << endl;
    }
};

class ImportedCar : public UsedCar {
private:
    string AuctionDate, AuctionGrade;

public:
    void InputDetails() override {
        UsedCar::InputDetails();
        cout << "Enter Auction Date (dd-mm-yyyy): "; cin >> AuctionDate;
        cout << "Enter Auction Grade: "; cin >> AuctionGrade;
    }

    void DisplayDetails() override {
        UsedCar::DisplayDetails();
        cout << " | Auction Date: " << AuctionDate << " | Grade: " << AuctionGrade;
    }

    string getAuctionDate() const {
        return AuctionDate;
    }

    string getAuctionGrade() const {
        return AuctionGrade;
    }

    bool Imported() override { return true; }

    void SaveToFile(ofstream& ShowroomFile) override {
        ShowroomFile << "Imported Car: " << fixed << setprecision(2) << Model << " " << Price << " " << EngineSize << " " << Transmission << " " << EngineNumber << " " << ChassisNumber << " " << ManufactureYear << " " << getRegistrationNo() << " " << getAuctionDate() << " " << getAuctionGrade() << endl;
    }
};

void SaveCarToFile(Car* Car) {
    ofstream ShowroomFile("Showroom.txt", ios::app);
    if (!ShowroomFile.is_open()) {
        cout << "Error: Could not open file for writing.\n";
        return;
    }
    Car->SaveToFile(ShowroomFile);
    ShowroomFile.close();
}

class Customer {
public:
    string Name, CNIC, EmployeeID;

    void InputDetails() {
        cin.ignore();
        cout << "Enter Customer Name: "; getline(cin, Name);
        cout << "Enter CNIC: "; getline(cin, CNIC);
        cout << "Enter Employee ID: "; getline(cin, EmployeeID);
    }

    void DisplayDetails() {
        cout << "Customer: " << Name << " | CNIC: " << CNIC << " | ID: " << EmployeeID << endl;
    }
};

class SalesTransaction {
public:
    Customer Customer;
    Car* Car;
    float TaxAmount;

    void SellCar(int CurrentYear) {
        TaxAmount = Car->CalculateTax(CurrentYear);
        float Total = Car->Price + TaxAmount;

        cout << "\n-------------------------<:>------------------------- SALE RECEIPT -------------------------<:>------------------------\n\n";
        Customer.DisplayDetails();
        Car->DisplayDetails();
        cout << fixed << setprecision(2) << "\nTax: " << TaxAmount << "\nTotal Price: " << Total;

        ofstream ShowroomFile("SoldCars.txt", ios::app);
        if (!ShowroomFile.is_open()) {
            cout << "Error: Could not open 'SoldCars.txt' for writing.\n";
            return;
        }
        ShowroomFile << "------------------------<:>------------------------ SALE RECEIPT ------------------------<:>------------------------\nCustomer: " << Customer.Name << " | CNIC: " << Customer.CNIC << " | ID: " << Customer.EmployeeID << endl;
        Car->SaveToFile(ShowroomFile);
        ShowroomFile << fixed << setprecision(2) << "Tax: " << TaxAmount << " | Total: " << Total << "\n--------------------------------------------------------------------------------------------------------------------\n";
        ShowroomFile.close();
    }
};

void UpdateShowroomFile(Car* Inventory[], int CarCount) {
    ofstream ShowroomFile("Showroom.txt", ios::trunc);
    if (!ShowroomFile.is_open()) {
        cout << "Error: Could not open Showroom.txt to update inventory.\n";
        return;
    }

    for (int i = 0; i < CarCount; i++) {
        Inventory[i]->SaveToFile(ShowroomFile);
    }

    ShowroomFile.close();
}

int main() {
    Car* Inventory[MaxCars];
    int CarCount = 0;
    int CurrentYear = 2025;

    Showroom Showroom;
    Showroom.InputDetails();

    int Choice;
    do {
        cout << "\n\n---------------------<:><[0]><:>--------------------- SHOWROOM MENU ---------------------<:><[0]><:>--------------------\n\n";
        cout << "1. Add A New Car\n";
        cout << "2. Add A Used Car\n";
        cout << "3. Add An Imported Car\n";
        cout << "4. Display All Cars\n";
        cout << "5. Sell A Car\n";
        cout << "0. Exit\n\n";
        cout << "Enter Choice: ";
        cin >> Choice;
        cout << endl;

        switch (Choice) {
        case 1:
            cout << "-------------------------<:>------------------------- ADD A NEW CAR -------------------------<:>------------------------\n\n";
            Inventory[CarCount] = new Car();
            Inventory[CarCount]->InputDetails();
            SaveCarToFile(Inventory[CarCount]);
            CarCount++;
            cout << "\nCar added successfully!\n";
            break;
        case 2:
            cout << "------------------------<:>------------------------ ADD A USED CAR -----------------------<:>------------------------\n\n";
            Inventory[CarCount] = new UsedCar();
            Inventory[CarCount]->InputDetails();
            SaveCarToFile(Inventory[CarCount]);
            CarCount++;
            cout << "\nCar added successfully!\n";
            break;
        case 3:
            cout << "-----------------------<:>----------------------- ADD AN IMPORTED CAR ----------------------<:>----------------------\n\n";
            Inventory[CarCount] = new ImportedCar();
            Inventory[CarCount]->InputDetails();
            SaveCarToFile(Inventory[CarCount]);
            CarCount++;
            cout << "\nCar added successfully!\n";
            break;
        case 4:
            cout << "------------------------<:>----------------------- DISPLAY ALL CARS -----------------------<:>----------------------\n\n";
            for (int i = 0; i < CarCount; i++) {
                cout << "\nCar " << i + 1 << ":\n";
                Inventory[i]->DisplayDetails();
                cout << endl;
            }
            break;
        case 5: {
            cout << "--------------------------<:>------------------------- SELL A CAR --------------------------<:>-------------------------\n\n";
            int CarIndex;
            cout << "Enter index of Car to sell (1 to " << CarCount << "): ";
            cin >> CarIndex;
            if (CarIndex < 1 || CarIndex > CarCount) {
                cout << "Invalid index.\n";
                break;
            }

            Customer Customer;
            Customer.InputDetails();

            SalesTransaction Sale;
            Sale.Customer = Customer;
            Sale.Car = Inventory[CarIndex - 1];
            Sale.SellCar(CurrentYear);

            delete Inventory[CarIndex - 1];
            for (int i = CarIndex - 1; i < CarCount - 1; i++) {
                Inventory[i] = Inventory[i + 1];
            }
            CarCount--;

            UpdateShowroomFile(Inventory, CarCount);

            cout << "\nCar sold successfully!\n";
            break;
        }
        case 0:
            cout << "-------------------------<:>------------------------- THANK YOU! -------------------------<:>-------------------------\n\n";
            cout << "Exiting...\n";
            break;
        default:
            cout << "Invalid option.\n";
        }

    } while (Choice != 0);

    for (int i = 0; i < CarCount; i++) {
        delete Inventory[i];
    }

    return 0;
}