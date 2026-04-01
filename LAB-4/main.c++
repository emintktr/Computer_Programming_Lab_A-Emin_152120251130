#include <iostream>
using namespace std;
#define fixQueueSize 5

struct Package {
    string packageID;
    string destinationCity;
    int dimensions[3];
    Package* next;
};

struct Courier {
    string courierName;
    string vehicleType;
};

void pushPackage(Package*& top, const string& id, const string& city, int l, int w, int h) {
    Package* newPackage = new Package;
    newPackage->packageID = id;
    newPackage->destinationCity = city;
    newPackage->dimensions[0] = l;
    newPackage->dimensions[1] = w;
    newPackage->dimensions[2] = h;
    newPackage->next = top;
    top = newPackage;
}

bool popPackage(Package*& top, Package& removed) {
    if (top == nullptr) {
        return false;
    }

    Package* temp = top;
    removed.packageID = temp->packageID;
    removed.destinationCity = temp->destinationCity;
    removed.dimensions[0] = temp->dimensions[0];
    removed.dimensions[1] = temp->dimensions[1];
    removed.dimensions[2] = temp->dimensions[2];
    removed.next = nullptr;

    top = top->next;
    delete temp;
    return true;
}

bool enqueueCourier(Courier queue[], int& front, int& rear, int& count, const string& name, const string& type) {
    if (count == fixQueueSize) {
        return false;
    }

    rear = (rear + 1) % fixQueueSize;
    queue[rear].courierName = name;
    queue[rear].vehicleType = type;
    count++;
    return true;
}

bool dequeueCourier(Courier queue[], int& front, int& rear, int& count, Courier& removed) {
    if (count == 0) {
        return false;
    }

    removed = queue[front];
    front = (front + 1) % fixQueueSize;
    count--;

    if (count == 0) {
        front = 0;
        rear = -1;
    }

    return true;
}

void displayPackages(Package* top) {
    cout << "Packages in Stack (Top to Bottom):" << endl;
    if (top == nullptr) {
        cout << "No packages waiting." << endl;
        return;
    }

    Package* current = top;
    while (current != nullptr) {
        cout << "ID: " << current->packageID
             << ", City: " << current->destinationCity
             << ", Dimensions(L,W,H): ["
             << current->dimensions[0] << ", "
             << current->dimensions[1] << ", "
             << current->dimensions[2] << "]" << endl;
        current = current->next;
    }
}

void displayCouriers(Courier queue[], int front, int count) {
    cout << "Couriers in Circular Queue (Front to Rear):" << endl;
    if (count == 0) {
        cout << "No couriers waiting." << endl;
        return;
    }

    for (int i = 0; i < count; i++) {
        int index = (front + i) % fixQueueSize;
        cout << "Name: " << queue[index].courierName
             << ", Vehicle: " << queue[index].vehicleType << endl;
    }
}

void dispatch(Package*& top, Courier queue[], int& front, int& rear, int& count) {
    Package dispatchedPackage;
    Courier dispatchedCourier;

    if (!popPackage(top, dispatchedPackage)) {
        cout << "Dispatch failed: Package stack is empty." << endl;
        return;
    }

    if (!dequeueCourier(queue, front, rear, count, dispatchedCourier)) {
        pushPackage(top,
                    dispatchedPackage.packageID,
                    dispatchedPackage.destinationCity,
                    dispatchedPackage.dimensions[0],
                    dispatchedPackage.dimensions[1],
                    dispatchedPackage.dimensions[2]);
        cout << "Dispatch failed: Courier queue is empty." << endl;
        return;
    }

    cout << "Dispatched -> Courier: " << dispatchedCourier.courierName
         << " (" << dispatchedCourier.vehicleType << ")"
         << " took Package: " << dispatchedPackage.packageID
         << " to " << dispatchedPackage.destinationCity << endl;
}

void clearStack(Package*& top) {
    Package temp;
    while (popPackage(top, temp)) {
    }
}

int main() {
    Package* packageTop = nullptr;
    Courier courierQueue[fixQueueSize];
    int front = 0;
    int rear = -1;
    int count = 0;

    int choice;

    do {
        cout << "Logistics & Cargo Distribution System by emintktr" << endl;
        cout << "1. Arrival (Push Package)" << endl;
        cout << "2. Courier Register (Enqueue Courier)" << endl;
        cout << "3. Dispatch (Pop & Dequeue)" << endl;
        cout << "4. Display" << endl;
        cout << "Enter choice: ";
        cin >> choice;

        if (choice == 0) {
            cout << "Exiting program." << endl;
        }
        else if (choice == 1) {
            string id, city;
            int l, w, h;
            cout << "Enter package ID: ";
            cin >> id;
            cout << "Enter destination city: ";
            cin >> city;
            cout << "DO NOT FORGET TO ENTER DIMENSIONS IN THE ORDER OF LENGTH, WIDTH, HEIGHT!" << endl;
            cout << "DO NOT ENTER ONE VALUE, ENTER ALL THREE!" << endl;
            cout << "Enter dimensions (Length | Width | Height): ";
            cin >> l >> w >> h;
            pushPackage(packageTop, id, city, l, w, h);
            cout << "Package added to stack." << endl;
        } else if (choice == 2) {
            string name, type;
            cout << "Enter courier name: ";
            cin >> name;
            cout << "Enter vehicle type: ";
            cin >> type;

            if (enqueueCourier(courierQueue, front, rear, count, name, type)) {
                cout << "Courier added to circular queue." << endl;
            } else {
                cout << "Queue is full (size " << fixQueueSize << ")." << endl;
            }
        } else if (choice == 3) {
            dispatch(packageTop, courierQueue, front, rear, count);
        } else if (choice == 4) {
            displayPackages(packageTop);
            displayCouriers(courierQueue, front, count);
        } else {
            cout << "Invalid choice. Try again." << endl;
        }
    } while (choice != 0);

    clearStack(packageTop);
    return 0;
}