#include <iostream>
#include <cstring>
using namespace std;

enum CommunicationStatus {
    Failed = 0,
    Partial = 1,
    Success = 2
};

class Satellite {
    char name[50];
    char operatorCountry[50];
public:
    Satellite(const char* name = "", const char* operatorCountry = "") {
        strncpy(this->name, name, 49);
        this->name[49] = '\0';
        strncpy(this->operatorCountry, operatorCountry, 49);
        this->operatorCountry[49] = '\0';
    }

    const char* getName()  { return name; }
    const char* getOperatorCountry()  { return operatorCountry; }

    void setName(const char* name) {
        strncpy(this->name, name, 49);

    }

    void setOperatorCountry(const char* country) {
        strncpy(this->operatorCountry, country, 49);
        this->operatorCountry[49] = '\0';
    }

    void print() const {
        cout << name << " (" << operatorCountry << ")";
    }
};

class Mission {
    Satellite satellite;
    char missionDate[11];
    int dataTransmitted;
    CommunicationStatus communicationStatus;
public:
    Mission(Satellite s = Satellite(), const char* date = "", int data = 0, CommunicationStatus status = Failed) {
        satellite = s;
        strncpy(missionDate, date, 10);
        missionDate[10] = '\0';
        dataTransmitted = data;
        communicationStatus = status;
    }

    Satellite getSatellite() const { return satellite; }
    const char* getMissionDate() const { return missionDate; }
    int getDataTransmitted() const { return dataTransmitted; }
    CommunicationStatus getCommunicationStatus() const { return communicationStatus; }

    void setSatellite(Satellite s) { satellite = s; }
    void setMissionDate(const char* date) {
        strncpy(missionDate, date, 10);
        missionDate[10] = '\0';
    }
    void setDataTransmitted(int data) { dataTransmitted = data; }
    void setCommunicationStatus(CommunicationStatus status) { communicationStatus = status; }

    void print() const {
        cout << "Mission Date: " << missionDate << endl;
        cout << "Mission Details:" << endl;
        cout << "Satellite: ";
        satellite.print();
        cout << endl;
        cout << "Data Transmitted: " << dataTransmitted << " TB" << endl;
        cout << "Communication Status: ";

        switch(communicationStatus) {
            case Failed: cout << "Failed"; break;
            case Partial: cout << "Partial"; break;
            case Success: cout << "Success"; break;
        }
        cout << endl;
        cout<<endl;
    }

};
 CommunicationStatus intToStatus(int status) {
        switch(status) {
            case 0: return Failed;
            case 1: return Partial;
            case 2: return Success;
            default: return Failed;
        }
    }
int main() {
    int N;
    cin >> N;

    Mission missions[100];

    for(int i = 0; i < N; i++) {
        char date[11];
        char name[50];
        char country[50];
        int data;
        int status;

        cin >> date;
        cin.ignore();
        cin.getline(name, 50);
        cin.getline(country, 50);
        cin >> data >> status;

        Satellite satellite(name, country);
        missions[i] = Mission(satellite, date, data,intToStatus(status));

    }

    for(int i = 0; i < N; i++) {
        missions[i].print();
    }

    return 0;
}