¨//Aarni Aliranta, 3pp

#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <string>

using namespace std;

struct Room {
    bool isAvailable;
    string reserverName;
};

int generateRandomNumber(int min, int max);
bool isRoomAvailable(const vector<Room>& rooms, int roomNumber);
int bookRoom(vector<Room>& rooms, int roomNumber, int nights, int roomPrice, const string& name);
void displayMenu();
void searchReservation(const vector<Room>& rooms, const string& name);

int main() {
    srand(time(0));

    int totalRooms = generateRandomNumber(30, 70);
    int roomPrice = generateRandomNumber(80, 100);

    vector<Room> rooms(totalRooms, { true, "" });

    cout << "Tervetuloa hotellin varausjarjestelmaan!\n";
    cout << "Meilla on " << totalRooms << " huonetta saatavilla, hinta on " << roomPrice << " euroa per yo.\n\n";

    bool running = true;

    while (running) {
        displayMenu();

        int choice;
        cout << "Anna valintasi: ";
        cin >> choice;

        if (cin.fail() || choice < 1 || choice > 4) {
            cin.clear();
            cin.ignore(10000, '\n');
            cout << "Virheellinen syote. Yrita uudelleen.\n";
            continue;
        }

        switch (choice) {
        case 1: {
            int roomNumber;
            cout << "Anna varattavan huoneen numero (1-" << totalRooms << "): ";
            cin >> roomNumber;

            if (cin.fail() || roomNumber < 1 || roomNumber > totalRooms) {
                cin.clear();
                cin.ignore(10000, '\n');
                cout << "Virheellinen huonenumero.\n";
                break;
            }

            if (!isRoomAvailable(rooms, roomNumber - 1)) {
                cout << "Huone " << roomNumber << " on jo varattu. Valitse toinen huone.\n";
                break;
            }

            int nights;
            cout << "Anna oiden maara: ";
            cin >> nights;

            if (cin.fail() || nights <= 0) {
                cin.clear();
                cin.ignore(10000, '\n');
                cout << "Virheellinen oiden maara.\n";
                break;
            }

            cin.ignore();
            string name;
            cout << "Anna varaajan nimi: ";
            getline(cin, name);

            int totalCost = bookRoom(rooms, roomNumber - 1, nights, roomPrice, name);
            cout << "Huone " << roomNumber << " varattiin onnistuneesti " << nights << " yoksi. Kokonaishinta: " << totalCost << " euroa.\n";
            break;
        }
        case 2: {
            cout << "Saatavilla olevat huoneet: \n";
            for (int i = 0; i < totalRooms; ++i) {
                if (rooms[i].isAvailable) {
                    cout << "Huone " << (i + 1) << "\n";
                }
            }
            break;
        }
        case 3: {
            cin.ignore();
            string name;
            cout << "Anna varaajan nimi haettavaksi: ";
            getline(cin, name);
            searchReservation(rooms, name);
            break;
        }
        case 4:
            cout << "Poistutaan jarjestelmasta. \n";
            running = false;
            break;
        }
    }

    return 0;
}

int generateRandomNumber(int min, int max) {
    return rand() % (max - min + 1) + min;
}

bool isRoomAvailable(const vector<Room>& rooms, int roomNumber) {
    return rooms[roomNumber].isAvailable;
}

int bookRoom(vector<Room>& rooms, int roomNumber, int nights, int roomPrice, const string& name) {
    rooms[roomNumber].isAvailable = false;
    rooms[roomNumber].reserverName = name;
    return nights * roomPrice;
}

void displayMenu() {
    cout << "\nValikko:\n";
    cout << "1. Varaa huone\n";
    cout << "2. Nayta saatavilla olevat huoneet\n";
    cout << "3. Hae varausta nimella\n";
    cout << "4. Poistu\n";
}

void searchReservation(const vector<Room>& rooms, const string& name) {
    bool found = false;
    for (int i = 0; i < rooms.size(); ++i) {
        if (!rooms[i].isAvailable && rooms[i].reserverName == name) {
            cout << "Loydettiin varaus: Huone " << (i + 1) << " varaajalta " << name << ".\n";
            found = true;
        }
    }
    if (!found) {
        cout << "Varausta nimella " << name << " ei loytynyt.\n";
    }
}
