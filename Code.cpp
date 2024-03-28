#include <iostream>
#include <string>
#include <vector>
#include <queue>
using namespace std;

class FitnessClass {
private:
    string className;
    int capacity;
    int bookedSlots;
    queue<string> waitlist;            // Queue to store members in the waitlist

public:
    FitnessClass(string name, int cap) : className(name), capacity(cap), bookedSlots(0) {}

    string getName() const {           // Getter function to get the class name
        return className;
    }

    int getCapacity() const {          // Getter function to get the class capacity
        return capacity;
    }

    int getBookedSlots() const {       // Getter function to get the number of booked slots
        return bookedSlots;
    }

    int getAvailableSlots() const {   // Getter function to get the number of available slots
        return capacity - bookedSlots;
    }

    bool bookSlot() {                 // Function to book a slot
        if (bookedSlots < capacity) {
            bookedSlots++;
            return true;
        }
        return false;
    }

    void cancelBooking() {             // Function to cancel a booking
        if (bookedSlots > 0) {
            bookedSlots--;             // Reduce booked slots by 1
            if (!waitlist.empty()) {         // If there are members in the waitlist
                string memberName = waitlist.front();
                waitlist.pop();
                cout << "Booking automatically assigned to " << memberName << " from the waitlist for class: " << className << endl;
            }
        }
    }

    bool isSlotAvailable() const {       // Function to check if a slot is available
        return bookedSlots < capacity;
    }

    void addToWaitlist(const string& memberName) {  // Function to add a member to the waitlist
        waitlist.push(memberName);
        cout << " --> " << memberName << " added to the waitlist for class: " << className << endl;
    }

    void displayWaitlist() const {        // Function to display the waitlist
        if (waitlist.empty()) {
            cout << " -->No waiting list member for class: " << className << endl;
        }
        else {
            cout << " -->Waiting list for class: " << className << endl;
            queue<string> tempWaitlist = waitlist;
            while (!tempWaitlist.empty()) {
                cout << tempWaitlist.front() << endl;
                tempWaitlist.pop();
            }
        }
    }
};

class Booking {                          // Class to store booking information
private:
    string memberName;
    FitnessClass* fitnessClass;

public:
    Booking(string name, FitnessClass* fc) : memberName(name), fitnessClass(fc) {}

    string getMemberName() const {
        return memberName;
    }

    FitnessClass* getFitnessClass() const {
        return fitnessClass;
    }
};

class Gym {                            // Class to store fitness classes
private:
    vector<FitnessClass> classes;

public:
    void addFitnessClass(const FitnessClass& fc) {
        classes.push_back(fc);
    }

    void displayClasses() const {
        cout << " --> Available Fitness Classes:\n";
        for (int i = 0; i < classes.size(); ++i) {
            cout << i + 1 << ". Class: " << classes[i].getName() << " - Available Slots: " << classes[i].getAvailableSlots() << "/" << classes[i].getCapacity() << endl;
            classes[i].displayWaitlist(); // Display waitlist for each class
            cout << endl;
        }
    }

    void bookClass(const string& memberName, int classIndex) {  // Function to book a class
        if (classIndex > 0 && classIndex <= classes.size()) {
            FitnessClass& fc = classes[classIndex - 1];
            if (fc.isSlotAvailable()) {
                fc.bookSlot();
                cout << " --> Booking is made for " << memberName << " for " << fc.getName() << " from 2100-2300." << endl;
            }
            else {
                fc.addToWaitlist(memberName);
            }
        }
        else {
            cout << " -> Invalid class index. Re-check your command" << endl;
        }
    }

    void cancelBooking(const string& memberName, int classIndex) {  // Function to cancel a booking
        if (classIndex > 0 && classIndex <= classes.size()) {
            FitnessClass& fc = classes[classIndex - 1];
            fc.cancelBooking();
        }
        else {
            cout << " -> Invalid class index. Re-check your command" << endl;
        }
    }
};

int main() {                                 // Main function
    Gym gym;
    FitnessClass yoga("Yoga", 2);
    FitnessClass Water_Aerobic("Water Aerobic", 15);
    gym.addFitnessClass(yoga);
    gym.addFitnessClass(Water_Aerobic);

    cout<< "  ======================================" <<endl;
    cout << "   Welcome to the BU Gymnasium Booking System.\n";   // User Interface 
    cout << "  ======================================" << endl;

    while (true) {
        cout << "\n --> Main Menu:\n\n";
        cout << " -> 1. View available fitness classes.\n";
        cout << " -> 2. Book a fitness class,\n";
        cout << " -> 3. Cancel booking.\n";
        cout << " -> 4. Exit.\n";
        cout << " -> Enter your choice you wanna perform: ";

        int choice;
        cin >> choice;

        switch (choice) {
        case 1:
            gym.displayClasses();
            break;
        case 2: {
            string memberName;
            int classIndex;
            cout << " --> Enter your first name: ";
            cin >> memberName;
            cout << " --> Enter the index of the class you want to book (Press 1 for Yoga OR Press 2 for Water Aerobics): ";
            cin >> classIndex;
            gym.bookClass(memberName, classIndex);
            break;
        }
        case 3:{
            string memberName;
            int classIndex;
            cout << " --> Enter your first name to cancel booking: ";
            cin >> memberName;
            cout << " --> Enter the index of the class you want to cancel (Press 1 for Yoga OR Press 2 for Water Aerobics): ";
            cin >> classIndex;
            gym.cancelBooking(memberName, classIndex);
            break;
        }
        case 4:
            cout << " -> Thank you for using the BU Gym Booking System.\n";
            return 0;
        default:
            cout << " -> Invalid command entered. Please re-check your command.\n";
        }
    }
    return 0;
    system("pause");
}
