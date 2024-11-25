#include <iostream>
#include <cstdlib>
#include <ctime>
#include <fstream>
using namespace std;

class Taxi {
public:
    int fare, dist, choice1, pessengernum;
    string destination, pickup, coupon, code, paymentMethod, confirm, passengerNames[3], passengerContacts[3];

    Taxi() : fare(0), dist(0), choice1(0), pessengernum(0) {}

    void vehicle() {
        cout << "Enter the vehicle you want to choose" << endl;    
        cout << "Press 1 to book a car (15 Rs per km)" << endl;
        cout << "Press 2 to book a mini (12 Rs per km)" << endl;
        cout << "Press 3 to book an auto (10 Rs per km)" << endl;
        cout << "Press 4 to book a bike (8 Rs per km)" << endl;
        cin >> choice1;
        switch (choice1) {
            case 1:
                cout << "You have chosen a car" << endl;
                fare = 15;
                break;
            case 2:
                cout << "You have chosen a mini" << endl;
                fare = 12;
                break;
            case 3:
                cout << "You have chosen an auto" << endl;
                fare = 10;
                break;
            case 4:
                cout << "You have chosen a bike" << endl;
                fare = 8;
                break;
            default:
                cout << "Invalid choice !!! Please try again" << endl;
                exit(0);
        }
    }

    void getPassengerDetails() {
        while (true) {
            cout << "Enter the number of passengers (1-3): ";
            cin >> pessengernum;
            if (pessengernum > 0 && pessengernum <= 3) {
                break;
            }
            cout << "Invalid number of passengers! Please enter a number between 1 and 3." << endl;
        }

        for (int i = 0; i < pessengernum; ++i) {
            cout << "Enter name of passenger " << (i + 1) << ": ";
            cin >> passengerNames[i];
            cout << "Enter contact number of passenger " << (i + 1) << ": ";
            cin >> passengerContacts[i];
        }
    }

    void displaySummary(int bookingID, double totalfare, int otp) {
        ofstream outFile("booking_details.txt");
        outFile << "----- Booking Summary -----\n";
        outFile << "Booking ID: " << bookingID << endl;
        outFile << "Destination: " << destination << endl;
        outFile << "Pickup: " << pickup << endl;
        outFile << "Vehicle: ";
        switch (choice1) {
            case 1: outFile << "Car"; break;
            case 2: outFile << "Mini"; break;
            case 3: outFile << "Auto"; break;
            case 4: outFile << "Bike"; break;
        }
        outFile << "\nDistance: " << dist << " km" << endl;
        outFile << "Total Fare: " << totalfare << " Rs" << endl;
        outFile << "Payment Method: " << paymentMethod << endl;
        outFile << "Number of Passengers: " << pessengernum << endl;
        for (int i = 0; i < pessengernum; ++i) {
            outFile << "Passenger " << (i + 1) << ": " << passengerNames[i] << " (Contact: " << passengerContacts[i] << ")\n";
        }
        outFile << "---------------------------\n";
        outFile << "Thank you for booking with OLA Taxi Service!" << endl;
        outFile.close();

        cout << "\n----- Booking Summary -----\n";
        cout << "Booking ID: " << bookingID << endl;
        cout << "Destination: " << destination << endl;
        cout << "Pickup: " << pickup << endl;
        cout << "Vehicle: ";
        switch (choice1) {
            case 1: cout << "Car"; break;
            case 2: cout << "Mini"; break;
            case 3: cout << "Auto"; break;
            case 4: cout << "Bike"; break;
        }
        cout << "\nDistance: " << dist << " km" << endl;
        cout << "Total Fare: " << totalfare << " Rs" << endl;
        cout << "Payment Method: " << paymentMethod << endl;
        cout << "Number of Passengers: " << pessengernum << endl;
        for (int i = 0; i < pessengernum; ++i) {
            cout << "Passenger " << (i + 1) << ": " << passengerNames[i] << " (Contact: " << passengerContacts[i] << ")\n";
        }
        cout << "---------------------------\n";
        cout << "Thank you for booking with OLA Taxi Service!" << endl;
    }
};

int main() {
    Taxi s1;
    int choice, bookingID;
    double totalfare;
    string paymentMethod;

    srand(time(0));
    bookingID = rand() % 9000 + 1000;

    cout << "Welcome to our Taxi Booking app 'OLA'" << endl;
    cout << "Enter your destination: ";
    cin.ignore(); 
    getline(cin, s1.destination);
    
    cout << "Press 1 to choose your current location" << endl;
    cout << "Press 2 to enter your pickup location" << endl;
    cin >> choice;
    
    if (choice == 1) {
        cout << "Your pickup location is your current location" << endl;
        s1.pickup = "Current location";
    } else {
        cout << "Enter your exact location of pickup: ";
        cin.ignore();
        getline(cin, s1.pickup);
    }
    
    cout << "Enter the distance (in km): ";
    cin >> s1.dist;
    
    s1.getPassengerDetails();
    s1.vehicle();
    
    if (s1.pessengernum > 1 && s1.choice1 == 4) { 
        cout << "A bike can only accommodate 1 person. Please choose another vehicle." << endl; 
        exit(0);
    }

    totalfare = s1.fare * s1.dist;
    cout << "Your total fare is: " << totalfare << " Rs" << endl;
    
    cout << "Do you have a coupon code? (YES/NO): ";
    cin >> s1.coupon;
    
    if (s1.coupon == "YES" || s1.coupon == "yes") {
        cout << "Enter your coupon code: ";
        cin >> s1.code;
        if (s1.code == "VHAGAR") {
            cout << "CONGRATULATIONS!! You have successfully redeemed a discount of 30%" << endl;
            totalfare = totalfare - (0.3 * totalfare);
            cout << "Your total fare after discount is: " << totalfare << " Rs" << endl;
        } else {
            cout << "Invalid coupon code. No discount applied." << endl;
        }
    }
    
    cout << "Choose your payment method (Cash/Online): ";
    cin >> paymentMethod;
    
    cout<<"Do you want to confirm the ride(Yes/No)"<<endl;
    cin>>s1.confirm;
    if(cin=="Yes")
    {
	int otp = rand() % 900000 + 100000; 
    cout << "Your OTP is: " << otp << endl;

    s1.paymentMethod = paymentMethod;
    s1.displaySummary(bookingID, totalfare, otp);
}
else{
	cout<<"Thanks for choosing ola taxi services"<<endl;
	exit(0);
}
    return 0;
}

