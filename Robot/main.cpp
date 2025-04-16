#include <iostream>
#include <cstring>
using namespace std;
enum Category {
    explorer,
    worker,
    scientist
};

class Robot {
    char name[50];
    int battery;
    bool activeStatus;
    double price;
    Category category;

public:
    Robot(const char* name = "", int battery = 0, bool activeStatus = false, double price = 0.0, Category category = explorer) {
        strncpy(this->name, name, 49);
        this->name[49] = '\0';
        this->battery = battery;
        this->activeStatus = activeStatus;
        this->price = price;
        this->category = category;
    }

    const char* getName() const { return name; }
    int getBattery() const { return battery; }
    bool getActiveStatus() const { return activeStatus; }
    double getPrice() const { return price; }
    Category getCategory() const { return category; }

    void setName(const char* name) {
        strncpy(this->name, name, 49);
        this->name[49] = '\0';
    }

    void setBattery(int battery) { this->battery = battery; }
    void setActiveStatus(bool status) { activeStatus = status; }
    void setPrice(double price) { this->price = price; }
    void setCategory(Category category) { this->category = category; }

    void print() const {
        cout << name << " (";
        switch(category) {
            case explorer: cout << "explorer"; break;
            case worker: cout << "worker"; break;
            case scientist: cout << "scientist"; break;
        }
        cout << ") - Battery: " << battery << " - Price: " << price << "$ - Status: " << (activeStatus ? "ON" : "OFF") << endl;
    }

    void toggleActiveState() {
        activeStatus = !activeStatus;
    }

    void chargeBattery(int amount) {
        battery += amount;
        if (battery > 100) battery = 100;
    }
};

class Colony {
private:
    char name[50];
    int id;
    Robot robots[150];
    int numRobots;
    static int sledno;
    static int brojach;

public:
    Colony(const char* name = "") {
        strncpy(this->name, name, 49);
        this->name[49] = '\0';
        id = sledno;
        sledno -= brojach;
        brojach++;
        numRobots = 0;
    }


    Colony(const Colony& other) {
        strncpy(this->name, other.name, 49);
        this->name[49] = '\0';
        this->id = other.id;
        this->numRobots = other.numRobots;
        for (int i = 0; i < other.numRobots; i++) {
            this->robots[i] = other.robots[i];
            brojach++;
        }
    }

    const char* getName() const { return name; }
    int getId() const { return id; }
    int getNumRobots() const { return numRobots; }

    void setName(const char* name) {
        strncpy(this->name, name, 49);
        this->name[49] = '\0';
    }

    void print() const {
        cout << id << ": " << name << endl;
        cout << "Robots:" << endl;
        for (int i = 0; i < numRobots; i++) {
            robots[i].print();
        }
    }

    void addRobot(const Robot& robot) {
        for (int i = 0; i < numRobots; i++) {
            if (strcmp(robots[i].getName(), robot.getName()) == 0 &&
                robots[i].getCategory() == robot.getCategory()) {
                cout << "Robot already exists!" << endl;
                return;
            }
        }
        if (numRobots < 150) {
            robots[numRobots++] = robot;
        }
    }

    void toggleAllRobotsNotInCategory(Category category) {
        for (int i = 0; i < numRobots; i++) {
            if (robots[i].getCategory() != category) {
                robots[i].toggleActiveState();
            }
        }
    }

    void chargeAllRobotsByCategory(int amount, Category category) {
        for (int i = 0; i < numRobots; i++) {
            if (robots[i].getCategory() == category) {
                robots[i].chargeBattery(amount);
            }
        }
    }
};

int Colony::sledno = 4999;
int Colony::brojach=2;

Colony& smallestColony(Colony *colonies, int n) {
    int minRobots = colonies[0].getNumRobots();
    int index = 0;
    for (int i = 1; i < n; i++) {
        if (colonies[i].getNumRobots() <= minRobots) {
            minRobots = colonies[i].getNumRobots();
            index = i;
        }
    }
    return colonies[index];
}
int main() {
    int testCase;
    cin >> testCase;

    if (testCase == 0) {
        cout << "TESTING ROBOT CONSTRUCTORS" << endl;
        Robot d1;
        Robot d2("Rover", 75, true, 1299.50, explorer);
        Robot d3("Scout", 40, false, 799.99, worker);
        Robot d4("Probe", 20, true, 499.99, scientist);
        Robot d5(d2);
        cout << "TEST PASSED" << endl;
    } else if (testCase == 1) {
        cout << "TESTING ROBOT print()" << endl;
        Robot d1("Alpha", 50, true, 1200.0, explorer);
        Robot d2("Beta", 30, false, 850.5, scientist);
        d1.print();
        d2.print();
        cout << "TEST PASSED" << endl;
    } else if (testCase == 2) {
        cout << "TESTING ROBOT toggleActiveState()" << endl;
        Robot d("Gamma", 60, false, 600.0, worker);
        d.print();
        d.toggleActiveState();
        cout << "After toggle: ";
        d.print();
        d.toggleActiveState();
        cout << "After toggle: ";
        d.print();
        cout << "TEST PASSED" << endl;
    } else if (testCase == 3) {
        cout << "TESTING ROBOT chargeBattery()" << endl;
        Robot d("Delta", 30, true, 1000.0, explorer);
        d.print();
        d.chargeBattery(5);
        d.print();
        d.chargeBattery(15);
        d.print();
        cout << "TEST PASSED" << endl;
    } else if (testCase == 4) {
        cout << "TESTING COLONY CONSTRUCTOR" << endl;
        Colony h1("Alpha Colony");
        h1.print();
        Colony h2(h1);
        h2.print();
        cout << "TEST PASSED" << endl;
    } else if (testCase == 5) {
        cout << "TESTING addRobot() and print()" << endl;
        Colony col("Mars Base");
        Robot r1("R1", 50, true, 500.0, explorer);
        Robot r2("R2", 40, false, 450.0, worker);
        Robot r3("R3", 40, true, 450.0, worker);
        Robot r4("R3", 30, true, 400.0, scientist);
        Robot r5("R2", 35, true, 420.0, worker);
        col.addRobot(r1);
        col.addRobot(r2);
        col.addRobot(r3);
        col.addRobot(r4);
        col.addRobot(r5);
        col.print();
        Colony col2(col);
        col2.print();
        cout << "TEST PASSED" << endl;
    } else if (testCase == 6) {
        cout << "TESTING toggleAllRobotsNotInCategory()" << endl;
        Colony col("Luna Outpost");
        Robot a("A", 10, false, 200.0, explorer);
        Robot b("B", 20, true, 300.0, worker);
        Robot c("C", 30, false, 400.0, scientist);
        Robot d("D", 40, true, 500.0, explorer);
        Robot e("E", 50, false, 600.0, scientist);
        Robot f("F", 60, false, 550.0, explorer);
        Robot g("G", 70, true, 530.0, worker);
        col.addRobot(a);
        col.addRobot(b);
        col.addRobot(c);
        col.addRobot(d);
        col.addRobot(e);
        col.addRobot(f);
        col.addRobot(g);
        col.print();
        col.toggleAllRobotsNotInCategory(worker);
        col.print();
        col.toggleAllRobotsNotInCategory(worker);
        col.print();
        col.toggleAllRobotsNotInCategory(scientist);
        col.print();
        cout << "TEST PASSED" << endl;
    } else if (testCase == 7) {
        cout << "TESTING chargeAllRobotsByCategory()" << endl;
        Colony col("Titan Station");
        Robot a("A", 10, false, 200.0, explorer);
        Robot b("B", 20, true, 300.0, worker);
        Robot c("C", 30, false, 400.0, scientist);
        Robot d("D", 40, true, 500.0, explorer);
        Robot e("E", 50, false, 600.0, scientist);
        Robot f("F", 60, false, 550.0, explorer);
        Robot g("G", 70, true, 530.0, worker);
        col.addRobot(a);
        col.addRobot(b);
        col.addRobot(c);
        col.addRobot(d);
        col.addRobot(e);
        col.addRobot(f);
        col.addRobot(g);
        col.chargeAllRobotsByCategory(5, explorer);
        col.print();
        col.chargeAllRobotsByCategory(10, worker);
        col.print();
        cout << "TEST PASSED" << endl;
    } else if (testCase == 8) {
        cout << "TESTING smallestColony()" << endl;
        Colony arr[3] = {
            Colony("ColA"),
            Colony("ColB"),
            Colony("ColC")
        };
        Robot x("X", 10, true, 100.0, worker);
        Robot y("Y", 20, false, 110.0, explorer);
        arr[0].addRobot(x);
        arr[1].addRobot(x);
        arr[1].addRobot(y);
        arr[2].addRobot(y);
        Colony &best1 = smallestColony(arr, 3);
        best1.print();

        Robot z("Z", 15, true, 120.0, explorer);
        arr[0].addRobot(z);
        arr[0].addRobot(y);
        arr[2].addRobot(x);
        arr[2].addRobot(z);
        Colony &best2 = smallestColony(arr, 3);
        best2.print();
        cout << "TEST PASSED" << endl;
    } else if (testCase == 9) {
        cout << "TESTING smallestColony()" << endl;
        Colony arr[3] = {
            Colony("ColA"),
            Colony("ColB"),
            Colony("ColC")
        };
        Robot x("X", 10, true, 100.0, worker);
        Robot y("Y", 20, false, 110.0, explorer);
        arr[0].addRobot(x);
        arr[2].addRobot(x);
        arr[1].addRobot(y);
        arr[1].addRobot(x);
        Colony &best1 = smallestColony(arr, 3);
        best1.print();

        Robot z("Z", 15, true, 120.0, explorer);
        arr[2].addRobot(z);
        arr[2].addRobot(y);
        arr[2].addRobot(z);
        Colony &best2 = smallestColony(arr, 3);
        best2.print();
        cout << "TEST PASSED" << endl;
    }

    return 0;
}