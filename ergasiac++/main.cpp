#include <iostream>
#include <string>
#include "rpg.h"

using namespace std;

int main() {
    int width, height, heroNum;
    cout << "Enter grid width:" << endl;
    cin >> width;
    while (width < 1) {
        cout << "Enter grid width:" << endl;
        cin.clear();
        cin.ignore(1000, '\n');
        cin >> width;
    }
    do {
        cout << "Enter grid height:" << endl;
        cin.clear();
        cin.ignore(1000, '\n');
        cin >> height;
    } while (height < 1);
    do {
        cout << "Enter number of heroes in party (between 1 and 3):" << endl;
        cin.clear();
        cin.ignore(1000, '\n');
        cin >> heroNum;
    } while (heroNum < 1 || heroNum > 3);
    HeroType heroTypes[heroNum];
    string input;
    for (int i = 0 ; i  < heroNum ; ++i) {
        cout << "Enter type of " << i + 1 << (i == 0 ? "st" : (i == 1 ? "nd" : "rd")) << " hero:" << endl;
        cin >> input;
        if (!input.compare("warrior")) {
            heroTypes[i] = warrior;
        }
        else if (!input.compare("sorcerer")) {
            heroTypes[i] = sorcerer;
        }
        else if (!input.compare("paladin")) {
            heroTypes[i] = paladin;
        }
        else {
            cout << "Invalid input" << endl;
            --i;
        }
    }
    Grid grid(width, height, heroTypes, heroNum);
    grid.playGame();
    return 0;
}