#include <string>
#include <iostream>

using namespace std;

class Group {
    private:
        string name;
        int total;

    public:
        Group(string groupName, int NUM_FAMILIES) {
            this->name = groupName;
            this->total = NUM_FAMILIES;
        }

        void printInfo() const {
            cout << "Name of group: " << this->name << endl;
            cout << "total number of families: " << this->total << endl;

        }
};

