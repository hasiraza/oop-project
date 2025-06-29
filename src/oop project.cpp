#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include <algorithm>
#include <ctime>
using namespace std;

// Room class for hostel rooms
class Room {
private:
    int roomNumber;
    string roomType;
    double pricePerNight;
    bool isOccupied;
    string guestName;
    string checkInDate;
    int nights;

public:
    Room(int num, string type, double price) 
        : roomNumber(num), roomType(type), pricePerNight(price), 
          isOccupied(false), guestName(""), checkInDate(""), nights(0) {}

    // Getters
    int getRoomNumber() const { return roomNumber; }
    string getRoomType() const { return roomType; }
    double getPricePerNight() const { return pricePerNight; }
    bool getIsOccupied() const { return isOccupied; }
    string getGuestName() const { return guestName; }
    string getCheckInDate() const { return checkInDate; }
    int getNights() const { return nights; }

    // Room operations
    void checkIn(string guest, string date, int numNights) {
        if (!isOccupied) {
            isOccupied = true;
            guestName = guest;
            checkInDate = date;
            nights = numNights;
            cout << "Room " << roomNumber << " checked in successfully!" << endl;
            cout << "Guest: " << guest << endl;
            cout << "Check-in Date: " << date << endl;
            cout << "Nights: " << numNights << endl;
            cout << "Total Cost: $" << fixed << setprecision(2) << (pricePerNight * numNights) << endl;
        } else {
            cout << "Room " << roomNumber << " is already occupied by " << guestName << "!" << endl;
        }
    }

    double checkOut() {
        if (isOccupied) {
            double totalCost = pricePerNight * nights;
            cout << "\n========== CHECK OUT SUMMARY ==========" << endl;
            cout << "Room Number: " << roomNumber << endl;
            cout << "Guest Name: " << guestName << endl;
            cout << "Check-in Date: " << checkInDate << endl;
            cout << "Nights Stayed: " << nights << endl;
            cout << "Rate per Night: $" << fixed << setprecision(2) << pricePerNight << endl;
            cout << "Total Amount: $" << fixed << setprecision(2) << totalCost << endl;
            cout << "=======================================" << endl;
            
            // Reset room
            isOccupied = false;
            guestName = "";
            checkInDate = "";
            nights = 0;
            
            return totalCost;
        } else {
            cout << "Room " << roomNumber << " is already vacant!" << endl;
            return 0;
        }
    }

    void display() const {
        cout << setw(8) << roomNumber 
             << setw(15) << roomType 
             << setw(12) << fixed << setprecision(2) << pricePerNight
             << setw(12) << (isOccupied ? "Occupied" : "Available")
             << setw(20) << (isOccupied ? guestName : "N/A")
             << setw(12) << (isOccupied ? checkInDate : "N/A")
             << setw(8) << (isOccupied ? to_string(nights) : "N/A") << endl;
    }

    void setPricePerNight(double newPrice) { pricePerNight = newPrice; }
};

// Guest class
class Guest {
private:
    int guestId;
    string name;
    string phone;
    string email;
    string address;
    int roomNumber;

public:
    Guest(int id, string n, string p, string e, string addr, int room = 0) 
        : guestId(id), name(n), phone(p), email(e), address(addr), roomNumber(room) {}

    // Getters
    int getGuestId() const { return guestId; }
    string getName() const { return name; }
    string getPhone() const { return phone; }
    string getEmail() const { return email; }
    string getAddress() const { return address; }
    int getRoomNumber() const { return roomNumber; }

    // Setters
    void setRoomNumber(int room) { roomNumber = room; }

    void display() const {
        cout << setw(5) << guestId 
             << setw(20) << name 
             << setw(15) << phone 
             << setw(25) << email 
             << setw(30) << address
             << setw(8) << (roomNumber == 0 ? "N/A" : to_string(roomNumber)) << endl;
    }
};

// Booking class for managing reservations
class Booking {
private:
    int bookingId;
    int guestId;
    string guestName;
    int roomNumber;
    string checkInDate;
    string checkOutDate;
    int nights;
    double totalAmount;
    string status; // "Active", "Completed", "Cancelled"

public:
    Booking(int id, int gId, string gName, int room, string inDate, string outDate, int n, double amount) 
        : bookingId(id), guestId(gId), guestName(gName), roomNumber(room), 
          checkInDate(inDate), checkOutDate(outDate), nights(n), totalAmount(amount), status("Active") {}

    // Getters
    int getBookingId() const { return bookingId; }
    int getGuestId() const { return guestId; }
    string getGuestName() const { return guestName; }
    int getRoomNumber() const { return roomNumber; }
    string getStatus() const { return status; }
    double getTotalAmount() const { return totalAmount; }

    void setStatus(string newStatus) { status = newStatus; }

    void display() const {
        cout << setw(8) << bookingId 
             << setw(8) << guestId
             << setw(20) << guestName 
             << setw(8) << roomNumber
             << setw(12) << checkInDate
             << setw(12) << checkOutDate
             << setw(8) << nights
             << setw(12) << fixed << setprecision(2) << totalAmount
             << setw(12) << status << endl;
    }
};

// Main Hostel Management System class
class HostelManagementSystem {
private:
    vector<Room> rooms;
    vector<Guest> guests;
    vector<Booking> bookings;
    int nextGuestId;
    int nextBookingId;

public:
    HostelManagementSystem() : nextGuestId(1), nextBookingId(1) {
        initializeRooms();
    }

    void initializeRooms() {
        // Dormitory rooms (shared)
        rooms.push_back(Room(101, "4-Bed Dorm", 25.00));
        rooms.push_back(Room(102, "4-Bed Dorm", 25.00));
        rooms.push_back(Room(103, "6-Bed Dorm", 20.00));
        rooms.push_back(Room(104, "6-Bed Dorm", 20.00));
        rooms.push_back(Room(105, "8-Bed Dorm", 18.00));
        rooms.push_back(Room(106, "8-Bed Dorm", 18.00));
        
        // Private rooms
        rooms.push_back(Room(201, "Single Private", 45.00));
        rooms.push_back(Room(202, "Single Private", 45.00));
        rooms.push_back(Room(203, "Double Private", 35.00));
        rooms.push_back(Room(204, "Double Private", 35.00));
        rooms.push_back(Room(205, "Twin Private", 40.00));
        rooms.push_back(Room(206, "Twin Private", 40.00));
    }

    void showMainMenu() {
        cout << "\n========== HOSTEL MANAGEMENT SYSTEM ==========" << endl;
        cout << "1. Room Management" << endl;
        cout << "2. Guest Management" << endl;
        cout << "3. Booking Management" << endl;
        cout << "4. Check-In/Check-Out" << endl;
        cout << "5. Reports" << endl;
        cout << "6. Settings" << endl;
        cout << "7. Exit" << endl;
        cout << "=============================================" << endl;
        cout << "Enter your choice: ";
    }

    void roomManagement() {
        int choice;
        do {
            cout << "\n========== ROOM MANAGEMENT ==========" << endl;
            cout << "1. View All Rooms" << endl;
            cout << "2. View Available Rooms" << endl;
            cout << "3. View Occupied Rooms" << endl;
            cout << "4. Search Room" << endl;
            cout << "5. Update Room Rates" << endl;
            cout << "6. Back to Main Menu" << endl;
            cout << "====================================" << endl;
            cout << "Enter your choice: ";
            cin >> choice;

            switch (choice) {
                case 1: viewAllRooms(); break;
                case 2: viewAvailableRooms(); break;
                case 3: viewOccupiedRooms(); break;
                case 4: searchRoom(); break;
                case 5: updateRoomRates(); break;
                case 6: break;
                default: cout << "Invalid choice!" << endl;
            }
        } while (choice != 6);
    }

    void viewAllRooms() {
        cout << "\n========== ALL ROOMS ==========" << endl;
        cout << setw(8) << "Room#" 
             << setw(15) << "Type" 
             << setw(12) << "Rate/Night" 
             << setw(12) << "Status" 
             << setw(20) << "Guest Name"
             << setw(12) << "Check-In"
             << setw(8) << "Nights" << endl;
        cout << "-----------------------------------------------------------------------------------------" << endl;
        for (const auto& room : rooms) {
            room.display();
        }
        cout << endl;
    }

    void viewAvailableRooms() {
        cout << "\n========== AVAILABLE ROOMS ==========" << endl;
        cout << setw(8) << "Room#" 
             << setw(15) << "Type" 
             << setw(12) << "Rate/Night" << endl;
        cout << "-----------------------------------" << endl;
        
        bool hasAvailable = false;
        for (const auto& room : rooms) {
            if (!room.getIsOccupied()) {
                hasAvailable = true;
                cout << setw(8) << room.getRoomNumber() 
                     << setw(15) << room.getRoomType() 
                     << setw(12) << fixed << setprecision(2) << room.getPricePerNight() << endl;
            }
        }
        
        if (!hasAvailable) {
            cout << "No rooms available!" << endl;
        }
        cout << endl;
    }

    void viewOccupiedRooms() {
        cout << "\n========== OCCUPIED ROOMS ==========" << endl;
        cout << setw(8) << "Room#" 
             << setw(15) << "Type" 
             << setw(20) << "Guest Name"
             << setw(12) << "Check-In"
             << setw(8) << "Nights"
             << setw(12) << "Total Cost" << endl;
        cout << "-------------------------------------------------------------------------" << endl;
        
        bool hasOccupied = false;
        for (const auto& room : rooms) {
            if (room.getIsOccupied()) {
                hasOccupied = true;
                cout << setw(8) << room.getRoomNumber() 
                     << setw(15) << room.getRoomType() 
                     << setw(20) << room.getGuestName()
                     << setw(12) << room.getCheckInDate()
                     << setw(8) << room.getNights()
                     << setw(12) << fixed << setprecision(2) << (room.getPricePerNight() * room.getNights()) << endl;
            }
        }
        
        if (!hasOccupied) {
            cout << "No occupied rooms!" << endl;
        }
        cout << endl;
    }

    void searchRoom() {
        int roomNum;
        cout << "Enter room number to search: ";
        cin >> roomNum;

        auto it = find_if(rooms.begin(), rooms.end(), 
                         [roomNum](const Room& r) { return r.getRoomNumber() == roomNum; });
        
        if (it != rooms.end()) {
            cout << "\n========== ROOM DETAILS ==========" << endl;
            cout << setw(8) << "Room#" 
                 << setw(15) << "Type" 
                 << setw(12) << "Rate/Night" 
                 << setw(12) << "Status" 
                 << setw(20) << "Guest Name"
                 << setw(12) << "Check-In"
                 << setw(8) << "Nights" << endl;
            cout << "-----------------------------------------------------------------------------------------" << endl;
            it->display();
        } else {
            cout << "Room not found!" << endl;
        }
    }

    void updateRoomRates() {
        int roomNum;
        cout << "Enter room number to update rate: ";
        cin >> roomNum;

        auto it = find_if(rooms.begin(), rooms.end(), 
                         [roomNum](const Room& r) { return r.getRoomNumber() == roomNum; });
        
        if (it != rooms.end()) {
            double newRate;
            cout << "Current rate: $" << fixed << setprecision(2) << it->getPricePerNight() << endl;
            cout << "Enter new rate: $";
            cin >> newRate;
            
            it->setPricePerNight(newRate);
            cout << "Room rate updated successfully!" << endl;
        } else {
            cout << "Room not found!" << endl;
        }
    }

    void guestManagement() {
        int choice;
        do {
            cout << "\n========== GUEST MANAGEMENT ==========" << endl;
            cout << "1. Add New Guest" << endl;
            cout << "2. View All Guests" << endl;
            cout << "3. Search Guest" << endl;
            cout << "4. Update Guest Information" << endl;
            cout << "5. Back to Main Menu" << endl;
            cout << "=====================================" << endl;
            cout << "Enter your choice: ";
            cin >> choice;

            switch (choice) {
                case 1: addGuest(); break;
                case 2: viewAllGuests(); break;
                case 3: searchGuest(); break;
                case 4: updateGuest(); break;
                case 5: break;
                default: cout << "Invalid choice!" << endl;
            }
        } while (choice != 5);
    }

    void addGuest() {
        string name, phone, email, address;
        cout << "Enter guest name: ";
        cin.ignore();
        getline(cin, name);
        cout << "Enter phone: ";
        getline(cin, phone);
        cout << "Enter email: ";
        getline(cin, email);
        cout << "Enter address: ";
        getline(cin, address);

        guests.push_back(Guest(nextGuestId++, name, phone, email, address));
        cout << "Guest added successfully with ID: " << (nextGuestId - 1) << endl;
    }

    void viewAllGuests() {
        if (guests.empty()) {
            cout << "No guests found!" << endl;
            return;
        }

        cout << "\n========== ALL GUESTS ==========" << endl;
        cout << setw(5) << "ID" 
             << setw(20) << "Name" 
             << setw(15) << "Phone" 
             << setw(25) << "Email" 
             << setw(30) << "Address"
             << setw(8) << "Room#" << endl;
        cout << "--------------------------------------------------------------------------------------------" << endl;
        for (const auto& guest : guests) {
            guest.display();
        }
        cout << endl;
    }

    void searchGuest() {
        int guestId;
        cout << "Enter guest ID: ";
        cin >> guestId;

        auto it = find_if(guests.begin(), guests.end(), 
                         [guestId](const Guest& g) { return g.getGuestId() == guestId; });
        
        if (it != guests.end()) {
            cout << "\n========== GUEST DETAILS ==========" << endl;
            cout << setw(5) << "ID" 
                 << setw(20) << "Name" 
                 << setw(15) << "Phone" 
                 << setw(25) << "Email" 
                 << setw(30) << "Address"
                 << setw(8) << "Room#" << endl;
            cout << "--------------------------------------------------------------------------------------------" << endl;
            it->display();
        } else {
            cout << "Guest not found!" << endl;
        }
    }

    void updateGuest() {
        int guestId;
        cout << "Enter guest ID to update: ";
        cin >> guestId;

        auto it = find_if(guests.begin(), guests.end(), 
                         [guestId](const Guest& g) { return g.getGuestId() == guestId; });
        
        if (it != guests.end()) {
            cout << "Current guest information:" << endl;
            cout << setw(5) << "ID" 
                 << setw(20) << "Name" 
                 << setw(15) << "Phone" 
                 << setw(25) << "Email" << endl;
            cout << "----------------------------------------------------------------" << endl;
            cout << setw(5) << it->getGuestId() 
                 << setw(20) << it->getName() 
                 << setw(15) << it->getPhone() 
                 << setw(25) << it->getEmail() << endl;
            
            cout << "\nNote: Currently, you can view guest information. Update functionality can be extended." << endl;
        } else {
            cout << "Guest not found!" << endl;
        }
    }

    void bookingManagement() {
        int choice;
        do {
            cout << "\n========== BOOKING MANAGEMENT ==========" << endl;
            cout << "1. Create New Booking" << endl;
            cout << "2. View All Bookings" << endl;
            cout << "3. Search Booking" << endl;
            cout << "4. Cancel Booking" << endl;
            cout << "5. Back to Main Menu" << endl;
            cout << "=======================================" << endl;
            cout << "Enter your choice: ";
            cin >> choice;

            switch (choice) {
                case 1: createBooking(); break;
                case 2: viewAllBookings(); break;
                case 3: searchBooking(); break;
                case 4: cancelBooking(); break;
                case 5: break;
                default: cout << "Invalid choice!" << endl;
            }
        } while (choice != 5);
    }

    void createBooking() {
        int guestId, roomNum, nights;
        string checkInDate, checkOutDate;

        cout << "Enter guest ID: ";
        cin >> guestId;

        auto guestIt = find_if(guests.begin(), guests.end(), 
                              [guestId](const Guest& g) { return g.getGuestId() == guestId; });
        
        if (guestIt == guests.end()) {
            cout << "Guest not found! Please add guest first." << endl;
            return;
        }

        viewAvailableRooms();
        cout << "Enter room number: ";
        cin >> roomNum;

        auto roomIt = find_if(rooms.begin(), rooms.end(), 
                             [roomNum](const Room& r) { return r.getRoomNumber() == roomNum; });
        
        if (roomIt == rooms.end()) {
            cout << "Room not found!" << endl;
            return;
        }

        if (roomIt->getIsOccupied()) {
            cout << "Room is already occupied!" << endl;
            return;
        }

        cout << "Enter check-in date (DD/MM/YYYY): ";
        cin >> checkInDate;
        cout << "Enter check-out date (DD/MM/YYYY): ";
        cin >> checkOutDate;
        cout << "Enter number of nights: ";
        cin >> nights;

        double totalAmount = roomIt->getPricePerNight() * nights;

        bookings.push_back(Booking(nextBookingId++, guestId, guestIt->getName(), 
                                 roomNum, checkInDate, checkOutDate, nights, totalAmount));

        cout << "\n========== BOOKING CONFIRMATION ==========" << endl;
        cout << "Booking ID: " << (nextBookingId - 1) << endl;
        cout << "Guest: " << guestIt->getName() << endl;
        cout << "Room: " << roomNum << " (" << roomIt->getRoomType() << ")" << endl;
        cout << "Check-in: " << checkInDate << endl;
        cout << "Check-out: " << checkOutDate << endl;
        cout << "Nights: " << nights << endl;
        cout << "Rate per night: $" << fixed << setprecision(2) << roomIt->getPricePerNight() << endl;
        cout << "Total Amount: $" << fixed << setprecision(2) << totalAmount << endl;
        cout << "=========================================" << endl;
    }

    void viewAllBookings() {
        if (bookings.empty()) {
            cout << "No bookings found!" << endl;
            return;
        }

        cout << "\n========== ALL BOOKINGS ==========" << endl;
        cout << setw(8) << "Book ID" 
             << setw(8) << "Guest ID"
             << setw(20) << "Guest Name" 
             << setw(8) << "Room#"
             << setw(12) << "Check-In"
             << setw(12) << "Check-Out"
             << setw(8) << "Nights"
             << setw(12) << "Total ($)"
             << setw(12) << "Status" << endl;
        cout << "---------------------------------------------------------------------------------------------" << endl;
        for (const auto& booking : bookings) {
            booking.display();
        }
        cout << endl;
    }

    void searchBooking() {
        int bookingId;
        cout << "Enter booking ID: ";
        cin >> bookingId;

        auto it = find_if(bookings.begin(), bookings.end(), 
                         [bookingId](const Booking& b) { return b.getBookingId() == bookingId; });
        
        if (it != bookings.end()) {
            cout << "\n========== BOOKING DETAILS ==========" << endl;
            cout << setw(8) << "Book ID" 
                 << setw(8) << "Guest ID"
                 << setw(20) << "Guest Name" 
                 << setw(8) << "Room#"
                 << setw(12) << "Check-In"
                 << setw(12) << "Check-Out"
                 << setw(8) << "Nights"
                 << setw(12) << "Total ($)"
                 << setw(12) << "Status" << endl;
            cout << "---------------------------------------------------------------------------------------------" << endl;
            it->display();
        } else {
            cout << "Booking not found!" << endl;
        }
    }

    void cancelBooking() {
        int bookingId;
        cout << "Enter booking ID to cancel: ";
        cin >> bookingId;

        auto it = find_if(bookings.begin(), bookings.end(), 
                         [bookingId](Booking& b) { return b.getBookingId() == bookingId; });
        
        if (it != bookings.end()) {
            if (it->getStatus() == "Active") {
                it->setStatus("Cancelled");
                cout << "Booking " << bookingId << " has been cancelled successfully!" << endl;
            } else {
                cout << "Booking is already " << it->getStatus() << "!" << endl;
            }
        } else {
            cout << "Booking not found!" << endl;
        }
    }

    void checkInOut() {
        int choice;
        do {
            cout << "\n========== CHECK-IN/CHECK-OUT ==========" << endl;
            cout << "1. Check-In Guest" << endl;
            cout << "2. Check-Out Guest" << endl;
            cout << "3. Back to Main Menu" << endl;
            cout << "=======================================" << endl;
            cout << "Enter your choice: ";
            cin >> choice;

            switch (choice) {
                case 1: checkInGuest(); break;
                case 2: checkOutGuest(); break;
                case 3: break;
                default: cout << "Invalid choice!" << endl;
            }
        } while (choice != 3);
    }

    void checkInGuest() {
        int roomNum, nights;
        string guestName, checkInDate;

        viewAvailableRooms();
        cout << "Enter room number for check-in: ";
        cin >> roomNum;

        auto roomIt = find_if(rooms.begin(), rooms.end(), 
                             [roomNum](Room& r) { return r.getRoomNumber() == roomNum; });
        
        if (roomIt == rooms.end()) {
            cout << "Room not found!" << endl;
            return;
        }

        if (roomIt->getIsOccupied()) {
            cout << "Room is already occupied!" << endl;
            return;
        }

        cout << "Enter guest name: ";
        cin.ignore();
        getline(cin, guestName);
        cout << "Enter check-in date (DD/MM/YYYY): ";
        getline(cin, checkInDate);
        cout << "Enter number of nights: ";
        cin >> nights;

        roomIt->checkIn(guestName, checkInDate, nights);
    }

    void checkOutGuest() {
        int roomNum;
        cout << "Enter room number for check-out: ";
        cin >> roomNum;

        auto roomIt = find_if(rooms.begin(), rooms.end(), 
                             [roomNum](Room& r) { return r.getRoomNumber() == roomNum; });
        
        if (roomIt == rooms.end()) {
            cout << "Room not found!" << endl;
            return;
        }

        if (!roomIt->getIsOccupied()) {
            cout << "Room is already vacant!" << endl;
            return;
        }

        double totalCost = roomIt->checkOut();
        if (totalCost > 0) {
            cout << "Guest checked out successfully!" << endl;
            cout << "Please collect payment of $" << fixed << setprecision(2) << totalCost << endl;
        }
    }

    void generateReports() {
        int choice;
        do {
            cout << "\n========== REPORTS ==========" << endl;
            cout << "1. Room Occupancy Report" << endl;
            cout << "2. Revenue Report" << endl;
            cout << "3. Guest Report" << endl;
            cout << "4. Booking Summary" << endl;
            cout << "5. Back to Main Menu" << endl;
            cout << "============================" << endl;
            cout << "Enter your choice: ";
            cin >> choice;

            switch (choice) {
                case 1: roomOccupancyReport(); break;
                case 2: revenueReport(); break;
                case 3: guestReport(); break;
                case 4: bookingSummary(); break;
                case 5: break;
                default: cout << "Invalid choice!" << endl;
            }
        } while (choice != 5);
    }

    void roomOccupancyReport() {
        int occupied = 0;
        int total = rooms.size();
        double totalRevenue = 0;

        cout << "\n========== ROOM OCCUPANCY REPORT ==========" << endl;
        
        for (const auto& room : rooms) {
            if (room.getIsOccupied()) {
                occupied++;
                totalRevenue += (room.getPricePerNight() * room.getNights());
            }
        }

        cout << "Total Rooms: " << total << endl;
        cout << "Occupied Rooms: " << occupied << endl;
        cout << "Available Rooms: " << (total - occupied) << endl;
        cout << "Occupancy Rate: " << fixed << setprecision(2) 
             << (double)occupied / total * 100 << "%" << endl;
        cout << "Current Revenue from Occupied Rooms: $" << fixed << setprecision(2) << totalRevenue << endl;
        cout << "===========================================" << endl;
    }

    void revenueReport() {
        double totalBookingRevenue = 0;
        double currentOccupiedRevenue = 0;
        int activeBookings = 0;
        int completedBookings = 0;

        cout << "\n========== REVENUE REPORT ==========" << endl;
        
        for (const auto& booking : bookings) {
            totalBookingRevenue += booking.getTotalAmount();
            if (booking.getStatus() == "Active") {
                activeBookings++;
            } else if (booking.getStatus() == "Completed") {
                completedBookings++;
            }
        }

        for (const auto& room : rooms) {
            if (room.getIsOccupied()) {
                currentOccupiedRevenue += (room.getPricePerNight() * room.getNights());
            }
        }

        cout << "Total Bookings Revenue: $" << fixed << setprecision(2) << totalBookingRevenue << endl;
        cout << "Current Occupied Rooms Revenue: $" << fixed << setprecision(2) << currentOccupiedRevenue << endl;
        cout << "Active Bookings: " << activeBookings << endl;
        cout << "Completed Bookings: " << completedBookings << endl;
        
        if (!bookings.empty()) {
            cout << "Average Booking Value: $" << fixed << setprecision(2) 
                 << totalBookingRevenue / bookings.size() << endl;
        }
        cout << "===================================" << endl;
    }

    void guestReport() {
        int guestsWithRooms = 0;
        
        cout << "\n========== GUEST REPORT ==========" << endl;
        cout << "Total Registered Guests: " << guests.size() << endl;
        
        for (const auto& guest : guests) {
            if (guest.getRoomNumber() != 0) {
                guestsWithRooms++;
            }
        }
        
        cout << "Guests Currently with Rooms: " << guestsWithRooms << endl;
        cout << "Guests without Current Rooms: " << (guests.size() - guestsWithRooms) << endl;
        cout << "Total Bookings Made: " << bookings.size() << endl;
        cout << "==================================" << endl;
    }

    void bookingSummary() {
        int activeBookings = 0;
        int completedBookings = 0;
        int cancelledBookings = 0;
        double totalRevenue = 0;

        cout << "\n========== BOOKING SUMMARY ==========" << endl;
        
        for (const auto& booking : bookings) {
            totalRevenue += booking.getTotalAmount();
            if (booking.getStatus() == "Active") {
                activeBookings++;
            } else if (booking.getStatus() == "Completed") {
                completedBookings++;
            } else if (booking.getStatus() == "Cancelled") {
                cancelledBookings++;
            }
        }

        cout << "Total Bookings: " << bookings.size() << endl;
        cout << "Active Bookings: " << activeBookings << endl;
        cout << "Completed Bookings: " << completedBookings << endl;
        cout << "Cancelled Bookings: " << cancelledBookings << endl;
        cout << "Total Booking Revenue: $" << fixed << setprecision(2) << totalRevenue << endl;
        
        if (!bookings.empty()) {
            cout << "Average Booking Value: $" << fixed << setprecision(2) 
                 << totalRevenue / bookings.size() << endl;
        }
        cout << "=====================================" << endl;
    }

    void settings() {
        int choice;
        do {
            cout << "\n========== SETTINGS ==========" << endl;
            cout << "1. View Room Types & Rates" << endl;
            cout << "2. Update Room Rates" << endl;
            cout << "3. System Information" << endl;
            cout << "4. Back to Main Menu" << endl;
            cout << "=============================" << endl;
            cout << "Enter your choice: ";
            cin >> choice;

            switch (choice) {
                case 1: viewRoomTypesRates(); break;
                case 2: updateAllRoomRates(); break;
                case 3: systemInformation(); break;
                case 4: break;
                default: cout << "Invalid choice!" << endl;
            }
        } while (choice != 4);
    }

    void viewRoomTypesRates() {
        cout << "\n========== ROOM TYPES & RATES ==========" << endl;
        
        // Group rooms by type
        vector<string> roomTypes;
        for (const auto& room : rooms) {
            if (find(roomTypes.begin(), roomTypes.end(), room.getRoomType()) == roomTypes.end()) {
                roomTypes.push_back(room.getRoomType());
            }
        }

        for (const auto& type : roomTypes) {
            cout << "\n" << type << " Rooms:" << endl;
            cout << setw(8) << "Room#" << setw(12) << "Rate/Night" << setw(12) << "Status" << endl;
            cout << "--------------------------------" << endl;
            
            for (const auto& room : rooms) {
                if (room.getRoomType() == type) {
                    cout << setw(8) << room.getRoomNumber() 
                         << setw(12) << fixed << setprecision(2) << room.getPricePerNight()
                         << setw(12) << (room.getIsOccupied() ? "Occupied" : "Available") << endl;
                }
            }
        }
        cout << "=======================================" << endl;
    }

    void updateAllRoomRates() {
        cout << "\n========== UPDATE ROOM RATES ==========" << endl;
        cout << "Select room type to update rates:" << endl;
        cout << "1. 4-Bed Dorm" << endl;
        cout << "2. 6-Bed Dorm" << endl;
        cout << "3. 8-Bed Dorm" << endl;
        cout << "4. Single Private" << endl;
        cout << "5. Double Private" << endl;
        cout << "6. Twin Private" << endl;
        cout << "7. Update Individual Room" << endl;
        cout << "======================================" << endl;
        
        int choice;
        cout << "Enter your choice: ";
        cin >> choice;

        string roomType;
        double newRate;

        switch (choice) {
            case 1: roomType = "4-Bed Dorm"; break;
            case 2: roomType = "6-Bed Dorm"; break;
            case 3: roomType = "8-Bed Dorm"; break;
            case 4: roomType = "Single Private"; break;
            case 5: roomType = "Double Private"; break;
            case 6: roomType = "Twin Private"; break;
            case 7: updateRoomRates(); return;
            default: cout << "Invalid choice!" << endl; return;
        }

        cout << "Enter new rate for " << roomType << ": $";
        cin >> newRate;

        int updated = 0;
        for (auto& room : rooms) {
            if (room.getRoomType() == roomType) {
                room.setPricePerNight(newRate);
                updated++;
            }
        }

        cout << updated << " rooms of type '" << roomType << "' updated to $" 
             << fixed << setprecision(2) << newRate << " per night." << endl;
    }

    void systemInformation() {
        cout << "\n========== SYSTEM INFORMATION ==========" << endl;
        cout << "Hostel Management System v1.0" << endl;
        cout << "=======================================" << endl;
        cout << "System Statistics:" << endl;
        cout << "Total Rooms: " << rooms.size() << endl;
        cout << "Total Guests: " << guests.size() << endl;
        cout << "Total Bookings: " << bookings.size() << endl;
        
        int occupied = 0;
        for (const auto& room : rooms) {
            if (room.getIsOccupied()) occupied++;
        }
        
        cout << "Currently Occupied: " << occupied << " rooms" << endl;
        cout << "=======================================" << endl;
        
        cout << "\nRoom Type Distribution:" << endl;
        cout << "4-Bed Dorm: 2 rooms" << endl;
        cout << "6-Bed Dorm: 2 rooms" << endl;
        cout << "8-Bed Dorm: 2 rooms" << endl;
        cout << "Single Private: 2 rooms" << endl;
        cout << "Double Private: 2 rooms" << endl;
        cout << "Twin Private: 2 rooms" << endl;
        cout << "=======================================" << endl;
    }

    void run() {
        int choice;
        cout << "========================================" << endl;
        cout << "   Welcome to Hostel Management System" << endl;
        cout << "========================================" << endl;

        do {
            showMainMenu();
            cin >> choice;

            switch (choice) {
                case 1: roomManagement(); break;
                case 2: guestManagement(); break;
                case 3: bookingManagement(); break;
                case 4: checkInOut(); break;
                case 5: generateReports(); break;
                case 6: settings(); break;
                case 7: 
                    cout << "\n========================================" << endl;
                    cout << "Thank you for using Hostel Management System!" << endl;
                    cout << "========================================" << endl;
                    break;
                default: 
                    cout << "Invalid choice! Please try again." << endl;
            }
        } while (choice != 7);
    }
};

int main() {
    HostelManagementSystem hms;
    hms.run();
    return 0;
}