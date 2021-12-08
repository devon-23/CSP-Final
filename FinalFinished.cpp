#include <iostream>
#include <array>
#include <vector>
#include <string>
#include "variables.h"
#include "Group.h" 
using namespace std;

int main() {

    int NUM_FAMILIES;
    vector<int> numGroup(NUM_FAMILIES);
    vector<int> chargeFamily(NUM_FAMILIES);
    int totalGroup, i, numRooms, numCots, roomServiceFamily, roomServiceSelection;
    string ans, ans2, groupName;

    string roomServiceFood [6] = {" Mac and Cheese " , " Cheeseburger " , " Ribs " , " Pizza " , " Pasta "}; //what food is available to order
    int roomServicePrices [6] = {8 , 12 , 19 , 20 , 25}; //how much each food costs

    cout << "Hello! Welcome to the Bates Motel in Aldergrove, British Columbia." << endl;
    cout << "We currently have 25 rooms available." << endl;
    cout << "What is the name of the group / person making the reservation?";
    cin >> groupName; //name of the group

    cout << "How many families will be staying?" << endl;
    cin >> NUM_FAMILIES; // total number of families

    Group myGroup = Group(groupName, NUM_FAMILIES); //making an abstract class

    cout << "We have rooms available that can comfortablly sleep 4 guests." << endl;
    cout << "We are able to bring a cot to rooms that will sleep an additional guest at a service fee of 35$." << endl;

    for (i = 1; i <= NUM_FAMILIES; i++) {
        cout << "How many guests are in family " << i << "?" << endl;
        cin >> numGroup.at(i); //inputting the number of people in each family
    }
    for (i = 1; i <= NUM_FAMILIES; i++) {
            if (numGroup.at(i) <= 4) { // if the family number is less than or equal to 4
                numRooms += 1;
                chargeFamily.at(i) += variables::priceRoom;
            }
            else if (numGroup.at(i) == 5) { // if the family number equals 5
                numCots += 1;
                numRooms += 1;
                chargeFamily.at(i) += (variables::priceCot + variables::priceRoom);
            }
            else {
                cout << "We will have to split up family number " << i << " into separate rooms because family number exceeds 5." << endl;
                if (numGroup.at(i) % 4 == 0) {
                    numRooms += (numGroup.at(i) / 4);
                    chargeFamily.at(i) += variables::priceRoom * (numGroup.at(i) / 4) ;
                }
                else if (numGroup.at(i) % 5 == 0) {
                    numRooms += ((numGroup.at(i) / 5));
                    numCots += ((numGroup.at(i) / 5));
                    chargeFamily.at(i) += ((numGroup.at(i) / 5) * variables::priceRoom) + ((numGroup.at(i) / 5) * variables::priceCot);
                }
                else if (numGroup.at(i) % 4 == 1 || numGroup.at(i) % 4 == 3) { //if ends with .25 or .75
                    if (numGroup.at(i) == 7) {
                        numRooms += 2;
                        chargeFamily.at(i) += variables::priceRoom * 2;
                    }
                    else if (numGroup.at(i) == 11) {
                        numRooms += 3;
                        chargeFamily.at(i) += variables::priceRoom * 3;
                    }
                    else {
                        numRooms += ((numGroup.at(i) / 4));
                        numCots += ((numGroup.at(i) % 4));
                        chargeFamily.at(i) += ((numGroup.at(i) / 4) * variables::priceRoom) + ((numGroup.at(i) % 4) * variables::priceCot);
                    }
                }
                else if (numGroup.at(i) % 4 == 2) { //if ends with .25
                    if (numGroup.at(i) < 7) {
                        numRooms += 2;
                        chargeFamily.at(i) += variables::priceRoom * 2;
                    }
                    else {
                        numRooms += ((numGroup.at(i) / 4));
                        numCots += ((numGroup.at(i) % 4));
                        chargeFamily.at(i) += ((numGroup.at(i) / 4) * variables::priceRoom) + ((numGroup.at(i) % 4) * variables::priceCot);
                    }
                }
            }
    }

    if (numRooms > 25) { //since we only have 25 rooms avail, this will exit the program 
        cout << "We are very sorry but we do not have enough rooms available to have your party stay with us." << endl;
        return 0; //exit the program
    }

    cout << "Would a family like to order from the room service?" << endl;
    cout << "answer 'yes' or 'no'" << endl;
    cin >> ans;
    while (ans != "yes" && ans != "no") { //keeps showing up untill they answer yes / no
        cout << "invalid selection. please answer 'yes' or 'no'" << endl;
        cout << "Would you like to order from the room service?" << endl;
        cin >> ans;
    }
    while (ans == "yes") {
        do {
            cout << "Which family number would like to make a room service order?" << endl;
            cin >> roomServiceFamily;
            while (roomServiceFamily > NUM_FAMILIES) {//keeps showing up untill they answer a valid number
                cout << "Invalid selection. family number " << roomServiceFamily << " does not exist." << endl;
                cout << "Number must be less than number of families registered: " << NUM_FAMILIES << endl;
                cout << "Which family number would like to make a room service order?" << endl;
                cin >> roomServiceFamily;
            }

            for (int i = 0; i < 1; i ++) {
                for (int a = 0; a < 5; a ++) {
                    cout <<  "choose " << a + 1 << " " << roomServiceFood [a] << " for a total of $" << roomServicePrices [a] << endl;
                }
                cout << "What would family number " << roomServiceFamily << " like to purchase?" << endl;
                cin >> roomServiceSelection;
                
                    if (roomServiceSelection == 1) {
                        chargeFamily.at(roomServiceFamily) += roomServicePrices [0];
                    }
                    else if (roomServiceSelection == 2) {
                        chargeFamily.at(roomServiceFamily) += roomServicePrices [1];
                    }
                    else if (roomServiceSelection == 3) {
                        chargeFamily.at(roomServiceFamily) += roomServicePrices [2];
                    }
                    else if (roomServiceSelection == 4) {
                        chargeFamily.at(roomServiceFamily) += roomServicePrices [3];
                    }
                    else if (roomServiceSelection == 5) {
                        chargeFamily.at(roomServiceFamily) += roomServicePrices [4];
                    }
            }

            cout << "Would you like to make another selection?" << endl;
            cin >> ans;
        } while (ans == "yes"); //keeps showing up untill they are done ordering
    }
    
    if (numRooms <= 25) {
        myGroup.printInfo(); //print info from Group.h
        cout << "The number of total rooms needed is " << numRooms << endl;
        cout << "The number of total cots needed is " << numCots << endl;
        for (i = 0; i < NUM_FAMILIES; i++ ) {
            cout << "The total cost for family " << i + 1 << " is $" << chargeFamily.at(i + 1) << endl;
        }
        
    }
    }

