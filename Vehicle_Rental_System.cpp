#include<iostream>
#include<vector>
using namespace std ;
class Vehicle  {
protected:
    string regNumber;
    string brand ;
    bool available;
public:
    Vehicle(string reg, string br) : regNumber(reg), brand(br), available(true) {}
    string getRegNumber(){return regNumber ;}
    string getBrand() {return brand ;}
    bool isAvailable(){return available ;}
    void setAvailable(bool status){available = status;}
    virtual void displayInfo()=0 ;
    virtual float calculateCost(int days)=0;
};
class Car :
public Vehicle {
    bool hasAC;
public :
    Car(string reg, string br, bool ac):Vehicle(reg, br), hasAC(ac) {}
    void displayInfo(){
        cout << "[Car] Reg# : " << regNumber << "|Brand: " << brand;
        cout << "|AC: " << (hasAC?"Yes":"No");
        cout << "|Available: " << (available ? "yes":"no") << endl;
    }
    float calculateCost(int days) {
        return hasAC ? days * 60: days * 50;
    }
};
class Motorcycle:
     public Vehicle {
    bool hasHelmet ;

public:
    Motorcycle(string reg, string br, bool helmet) : Vehicle(reg, br), hasHelmet(helmet) {}

    void displayInfo() {
        cout << "[Motorcycle] Reg#: " << regNumber << " | Brand: " << brand;
        cout << " |Helmet: " << (hasHelmet ? "yes" : "no");
        cout << " |Available: " << (available ? "yes":"no") << endl;
    }

    float calculateCost(int days) {
        return hasHelmet ? days * 30 : days*25;
    }
};
class Truck: public Vehicle {
    double capacity;

public:
    Truck(string reg, string br, double cap) : Vehicle(reg, br), capacity(cap) {}

    void displayInfo() {
        cout << "[Truck] Reg#: " << regNumber << " | Brand: " << brand;
        cout << " |Capacity: " << capacity << "tons";
        cout << " | Available: " << (available ? "yes" : "no") << endl;
    }
    float calculateCost(int days) {
        return days *100;
    }
};
class RentalSystem {
    vector< Vehicle*> vehicles;

public:
    RentalSystem() {
        for (auto v:vehicles) {
            delete v ;
        }
    }
    void addVehicle() {
        cout << "Select vehicle type : "<<endl;
        cout << "1. Car " <<endl;
        cout<<"2. Motorcycle"<<endl;
        cout << "3. Truck" <<endl ;
        cout << "Enter type:  ";
        int type ;
        cin >> type;
        cin.ignore();
        string reg, brand;
        cout << "Enter registration number: ";
        getline(cin, reg);
        cout << "Enter brand: ";
        getline(cin, brand);

        Vehicle* newVehicle =  nullptr;

    switch(type) {
        case 1: {
            int ac;
            cout << "Does it have air conditioning (1 for yes, 0 for no): ";
            cin >> ac;
            newVehicle = new Car(reg, brand, (ac==1));
        break;
        }
        case 2: {
            int helmet;
            cout << "Does it have a helmet (1 for yes,0 for no): ";
            cin >> helmet;
            newVehicle = new Motorcycle(reg, brand, (helmet==1));
        break;
        }
        case 3: {
            double cap;
            cout << "Enter LOad capacity in tons: ";
            cin >> cap;
            newVehicle = new Truck(reg, brand,cap);
        break;
    }
        default:
            cout << "Invalid choice!"<<endl;
        return;
        }

    vehicles.push_back(newVehicle);
    cout << "Vehicle added successfully."<<endl ;
    }

    void displayVehicles() {
        if (vehicles.empty()) {
            cout << "No vehicles in the system!" <<endl ;
        return;
        }

        cout << "--- Available Vehicles ---"<<endl ;
        for (auto v : vehicles) {
            if (v->isAvailable()) {
                v->displayInfo();
        }
    }
}
    void rentVehicle() {
        if (vehicles.empty()) {
            cout << "No vehicles available!"<<endl;
    return;
        }
        string reg;
        cout << "Enter registration number to rent: "<<endl;
        cin.ignore();
        getline(cin,reg);
        for (auto v:vehicles) {
            if (v->getRegNumber() == reg) {
                if (!v->isAvailable()) {
                    cout << "Vehicle is currently unavailable for rental"<<endl ;
        return;
            }
            int days;
            cout << "Enter number of rental days: ";
            cin >> days;
                cout << "--- Rental Summary ---"<<endl ;
                cout << "Vehicle: " << v->getBrand() << " (" << v->getRegNumber() << ")"<<endl;
                cout << "Rental Cost for " << days << " days: $" << v->calculateCost(days) << endl;
                v->setAvailable( false);
                cout << "Vehicle has been rented"<<endl ;
            return;
            }
        }
        cout << "Vehicle not found!"<<endl;
    }

    void returnVehicle() {
        if (vehicles.empty()) {
            cout << "No vehicles in the system!"<<endl;
        return;
        }

    string reg;
    cout << "Enter registration number to return: " <<endl;
    cin.ignore();
    getline(cin, reg);
    for (auto v:vehicles) {
        if (v->getRegNumber() == reg) {
        if (v->isAvailable()) {
        cout <<"Vehicle is not rented!"<<endl ;
        return;
    }
    v->setAvailable(true);
    cout <<"Vehicle " <<reg << "has been returned and is now available." <<endl;
    return;
    }
     }
    cout << "Vehicle not found!"<<endl;
    }
};
void showMenu() {
    cout << "_-=== Vehicle Rental System ===-_"<<endl ;
    cout << "1.Add Vehicle"<<endl ;
    cout << "2.Display All Available Vehicles"<<endl;
    cout << "3.Rent a Vehicle"<<endl;
    cout << "4.Return a Vehicle"<<endl;
    cout << "5. Exit "<<endl;
    cout << "Enter your choice: ";
}

int main() {
    RentalSystem system;
    int choice;

    do {
    showMenu();
    cin >>choice;
    switch(choice) {
        case 1:
            system.addVehicle();
        break;
        case 2:
            system.displayVehicles();
        break;
        case 3:
            system.rentVehicle();
        break;
        case 4:
            system.returnVehicle();
        break;
        case 5:
            cout << "Exiting system... Goodbye !"<<endl;
        break;
        default:
            cout << "Invalid choice ! Try again..."<<endl;
        }
    } while (choice!=5);









    return 0;
}

