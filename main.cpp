#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

class Passenger{
private:
	string name;
	string surname;
	string gender;
public:
    Passenger(string name, string surname, string gender)
    : name(name), surname(surname), gender(gender){}
	string getname() const{return name;}
	string getsurname() const{return surname;}
	string getgender() const{return gender;}
	void setname(string n){n = name;}
	void setsurname(string sn){sn = surname;}
	void setgender(string g){g = gender;}
    //Overloaded << operator to make printing information about passengers easier.
    friend ostream &operator<<( ostream &output, const Passenger &passenger ) {
        output << "Name: " << passenger.name << ", Surname: " << passenger.surname << ", Gender: " << passenger.gender;
        return output;
    }
    //Overloaded == operator so 1. find function can work and 2. I can compare whether two objects' names and surnames are the same.
    bool operator==(const Passenger &other) const {
        return (this->name == other.name && this->surname == other.surname);
    }
};

string stringToUpper(std::string a) {
    transform(a.begin(), a.end(),a.begin(), ::toupper);
    return a;
}

bool compareSurnames (const Passenger a, const Passenger b) {
    const string aSurname = stringToUpper(a.getsurname());
    const string bSurname = stringToUpper(b.getsurname());
    return (aSurname < bSurname);
}

class Flight{
private:
	string flightNo;
	int maxSeats;
	int numOfPassengers;
    vector<Passenger> listOfPassengers;
public:
    Flight(string flightNo, int maxSeats)
    : flightNo(flightNo), maxSeats(maxSeats), numOfPassengers(0) {}

    string getFlightNo() const{return flightNo;}
	bool reserveSeat(Passenger &client){
        if(numOfPassengers < maxSeats){
            listOfPassengers.push_back(client);
            numOfPassengers++;
            return true;
        }
        else
            return false;
	}

    bool cancelSeat(Passenger &client){
        for(Passenger p : listOfPassengers){
            if(p == client){
                listOfPassengers.erase(find(listOfPassengers.begin(), listOfPassengers.end(), p));
                numOfPassengers--;
                return true;
            }
        }
        return false;
	}

    bool checkTicket(Passenger &client){
        for(Passenger p : listOfPassengers){
            if(p == client){
                cout << "\nReservation:" <<endl;
                cout << p << endl;
                cout << "Flight: " << flightNo <<endl <<endl;
                return true;
            }
        }
        return false;
    }

    int numberOfPassengers(){return numOfPassengers;}


    void printPassengers(){
        sort(listOfPassengers.begin(), listOfPassengers.end(), compareSurnames);
        for(int i = 1; i <= numOfPassengers; i++){
            cout << i << "- " << listOfPassengers[i-1] <<endl;
        }
	}
};

int main(){

    Flight flight("IO - 15042004", 25);
    int choice, check = 1;
    string name, surname, gender;
    do{
        cout << "-------------------------------" << endl;
        cout << "|         Flight Menu         |" << endl;
        cout << "|-----------------------------|" << endl;
        cout << "|1. Reserve a Ticket          |" << endl;
        cout << "|-----------------------------|" << endl;
        cout << "|2. Cancel Reservation        |" << endl;
        cout << "|-----------------------------|" << endl;
        cout << "|3. Check Reservation         |" << endl;
        cout << "|-----------------------------|" << endl;
        cout << "|4. Display Passengers        |" << endl;
        cout << "|-----------------------------|" << endl;
        cout << "|5. Exit                      |" << endl;
        cout << "-------------------------------" << endl;
        cout << "Selection: ";
        cin >> choice;
        cout << endl;
        switch (choice) {
            case 1: {
                do {
                    cout << "Name of passenger: ";
                    cin >> name;
                    check = 1;
                    for (char i: name) {
                        if (i >= 'a' && i <= 'z' || i >= 'A' && i <= 'Z') {}
                        else {
                            cout << "Name contains unexpected characters. Please try again.\n" << endl;
                            check = 0;
                            break;
                        }
                    }
                }while(check == 0);
                check = 1;
                do{
                    cout << "Surname of passenger: ";
                    cin >> surname;
                    check = 1;
                    for (char i: surname) {
                        if (i >= 'a' && i <= 'z' || i >= 'A' && i <= 'Z') {}
                       else {
                           cout << "Surname contains unexpected characters. Please try again.\n" << endl;
                           check = 0;
                           break;
                       }
                    }
                }while(check == 0);
                check = 1;
                cout << "Gender of passenger: ";
                cin >> gender;

                Passenger passenger(name, surname, gender);
                if (flight.reserveSeat(passenger)) {
                    cout << "The seat has been reserved.\n" << endl;
                } else {
                    cout << "The seat has not been reserved. The flight is full.\n" << endl;
                }
                break;
            }
            case 2: {
                cout << "Reservation Cancellation\n" << endl;
                do {
                    cout << "Name of Ticket Owner: ";
                    cin >> name;
                    check = 1;
                    for (char i: name) {
                        if (i >= 'a' && i <= 'z' || i >= 'A' && i <= 'Z') {}
                        else {
                            cout << "Name contains unexpected characters. Please try again.\n" << endl;
                            check = 0;
                            break;
                        }
                    }
                }while(check == 0);
                check = 1;
                do{
                    cout << "Surname of Ticket Owner: ";
                    cin >> surname;
                    check = 1;
                    for (char i: surname) {
                        if (i >= 'a' && i <= 'z' || i >= 'A' && i <= 'Z') {}
                        else {
                            cout << "Surname contains unexpected characters. Please try again.\n" << endl;
                            check = 0;
                            break;
                        }
                    }
                }while(check == 0);
                check = 1;
                Passenger passenger(name, surname, "");
                if (flight.cancelSeat(passenger)) {
                    cout << "Reservation canceled successfully.\n" << endl;
                } else {
                    cout << "Failed to cancel reservation. Passenger was not found!\n" << endl;
                }
                break;
            }
            case 3: {
                cout << "Check Reservation\n" << endl;
                check = 1;
                    do {
                        cout << "Name of Ticket Owner: ";
                        cin >> name;
                        check = 1;
                        for (char i: name) {
                            if (i >= 'a' && i <= 'z' || i >= 'A' && i <= 'Z') {}
                            else {
                                cout << "Name contains unexpected characters. Please try again.\n" << endl;
                                check = 0;
                                break;
                            }
                        }
                    }while(check == 0);
                    check = 1;
                    do{
                        cout << "Surname of Ticket Owner: ";
                        cin >> surname;
                        check = 1;
                        for (char i: surname) {
                            if (i >= 'a' && i <= 'z' || i >= 'A' && i <= 'Z') {}
                            else {
                                cout << "Surname contains unexpected characters. Please try again.\n" << endl;
                                check = 0;
                                break;
                            }
                        }
                    }while(check == 0);
                    check = 1;

                Passenger checkedTicket(name, surname, "");
                if (!flight.checkTicket(checkedTicket)) {
                    cout << "No reservation was found for " << name << " " << surname << endl;
                }
                break;
            }
            case 4:
                cout << "List of passengers:" << endl << endl;
                flight.printPassengers();
                cout << endl;
                break;
            case 5:
                cout << "Exiting...\n" << endl;
                break;
            default:
                cout << "Invalid choice. Please try again.\n" << endl;
        }
    } while (choice != 5);
	
	return 0;
}