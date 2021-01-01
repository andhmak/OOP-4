//Να υλοποιηθεί σε C++ η προσομοίωση ενός παιχνιδιού ρόλων (role playing game). Το παιχνίδι θα έχει  αντικείμενα,  ξόρκια,  ήρωες  και  τέρατα.
//Οι  ήρωες  και  τα  τέρατα  ζουν  σε  έναν  κόσμο  που αναπαρίσταται από ένα πλέγμα.  Οι ήρωες μπορούν να εμπλέκονται σε μάχες με τα τέρατα, όπου και
//χρησιμοποιούν αντικείμενα και ξόρκια για να νικήσουν τα τέρατα, ή μπορούν να αγοράζουν αντικείμεναγια να τους βοηθήσουν στην περιπέτεια τους.
//Κάθε φορά που οι ήρωες νικούν κάποια τέρατα μαζεύουν κάποια  χρήματα  και  κερδίζουν  εμπειρία.
//Οταν  αποκτήσουν  αρκετή  εμπειρία,  οι  ήρωες “ανεβαίνουν” ένα επίπεδο, πράγμα που σημαίνει ότι γίνονται πιο δυνατοί στις επιμέρους ικανότητες τους.

// ́Ενα  αντικείμενο  (Item)  έχει  ένα  όνομα,
//   μία  τιμή  αγοράς  και  έχει  και  κάποιο  ελάχιστο  επίπεδοστο  οποίο  πρέπει  να  βρίσκεται  ο  ήρωας  για  να  το  χρησιμοποιήσει.
#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <vector>
#include "names.h"

using namespace std;

class Item {
    std::string name;
    int price;
    int minLevel;
};

//Ενα  όπλο  (Weapon)  είναι  ένααντικείμενο το οποίο μπορεί να χρησιμοποιηθεί από τον ήρωα για να επιτεθεί σε κάποιο τέρας. Εχει ένα συγκεκριμένο ποσό 
//ζημιάς που προκαλεί στον αντίπαλο του και μπορεί να απαιτεί το ένα ή και ταδύο χέρια του ήρωα για να το χρησιμοποιεί.

class Weapon : public Item {
    int damage;
    bool twoHanded;
};

//Μία πανοπλία (Armor) είναι ένα αντικείμενο το οποίο όταντο φοράει ένας ήρωας, μειώνει την ζημία που δέχεται από μία επίθεση του αντιπάλου του. 

class Armor : public Item {
    int defense;
};

enum Stat { strength, dexterity, agility };

//Ενα φίλτρο(Potion) είναι ένα αντικείμενο το οποίο όταν το χρησιμοποιεί ένας ήρωας, αυξάνει κάποιο στατιστικό του
//κατά  κάποιο  ποσό.  Τα  φίλτρα  είναι  μίας  χρήσης,  πράγμα  που  σημαίνει  ότι  μετά  τη  χρήση  τους,δεν μπορούν να ξαναχρησιμοποιηθούν.

class Potion : public Item {
    Stat statAffected;
    int effect;
};

//Ενα  ξόρκι  (Spell)  αντιπροσωπεύει  μια  μαγική  επίθεση  που  μπορεί  να  εκτελέσει  κάποιος  ήρωας. ́Ενα ξόρκι έχει όνομα, τιμή και κάποιο ελάχιστο
//επίπεδο στο οποίο πρέπει να βρίσκεται ο ήρωας για να  το  χρησιμοποιήσει.    ́Ενα  ξόρκι  έχει  ένα  εύρος  ζημιάς  που  μπορεί  να  προκαλέσει  καθώς 
//και  ένα ποσό μαγικής ενέργειας που απαιτεί για να εκτελεστεί. Μετά την εκτέλεση, το ποσό αυτό της μαγικής ενέργειας αφαιρείται από τον ήρωα.
//Το επίπεδο της ζημιάς που προκαλεί ένα ξόρκι εξαρτάται από την τιμή της επιδεξιότητας του ήρωα και πάντα βρίσκεται στο εύρος που έχει καθοριστεί. 

class Spell {
    std::string name;
    int price;
    int minLevel;
    int minDamage;
    int maxDamage;
    int magicCost;
};

//Ενα ξόρκι πάγου(IceSpell) είναι ένα ξόρκι το οποίο, εκτός από τη ζημιά που προκαλεί, μειώνει και το εύρος ζημιάς του αντιπάλου για κάποιους γύρους.

class IceSpell : public Spell {
};

//Ενα ξόρκι φωτιάς (FireSpell) είναι ένα ξόρκι το οποίο,  εκτός απότη ζημιά που προκαλεί, μειώνει και το ποσό άμυνας του αντιπάλου για κάποιους γύρους. 

class FireSpell : public Spell {
}; 

//Ενα ξόρκι ηλεκτρισμού (LightingSpell) είναι ένα ξόρκι το οποίο, εκτός από τη ζημιά που προκαλεί, μειώνει καιτην πιθανότητα να αποφύγει μια επίθεση ο
//αντίπαλος για κάποιους γύρους.

class LightingSpell : public Spell {
}; 

//Ενα ζωντανό ον (Living) αντιπροσωπεύει μια ζωντανή οντότητα του κόσμου του παιχνιδιού.
//Εχει ένα  όνομα,  κάποιο  επίπεδο  (level)  καθώς  και  ένα  ποσό  ζωτικής  ενέργειας  (healthPower).
//Οταν  ηζωτική  ενέργεια  του  φτάσει  στο  μηδέν,  το  ζωντανό  ον  λιποθυμάει.

class Living {
    std::string name;
    int level;
    int healthPower;
    public:
        Living(const char* initName) : name(initName), level(1), healthPower(100) { }
};

//Ενας ήρωας (Hero) είναι έναζωντανό ον.
//Εχει ένα ποσό μαγικής ενέργειας (magicPower), καθώς και κάποια χαρακτηριστικάπου επηρεάζουν την ικανότητα του στη μάχη.
//Ενας ήρωας έχει κάποια τιμή δύναμης (strength), κάποια τιμή επιδεξιότητας (dexterity) καθώς και κάποια τιμή ευκινησίας (agility).
//Η δύναμη του ήρωα προστίθεται στο ποσό ζημιάς που προκαλεί ένα όπλο, η επιδεξιότητα του επιτρέπει να εκτελεί ταξόρκια πιο αποδοτικά και
//τέλος η ευκινησία του επιτρέπει να μπορεί με κάποια πιθανότητα να αποφύγει κάποια επίθεση του αντιπάλου του.
//Ενας ήρωας διαθέτει ένα ποσό χρημάτων (money) καθώς και ένα ποσό εμπειρίας (experience).
//Οταν ο ήρωας αποκτήσει αρκετή εμπειρία, ανεβαίνει ένα επίπεδο(levelUp).
//Σε κάθε επίπεδο, οι τιμές της δύναμης, της επιδεξιότητας και της ευκινησίας του ήρωα,αυξάνονται κατά κάποιο ποσό.

class Hero : public Living {
    int magicPower;
    int strength;
    int dexterity;
    int agility;
    int money;
    int experience;
    public:
        Hero(const char* initName, int strengthInit, int dexterityInit, int agilityInit)
        :   Living(initName), strength(strengthInit), dexterity(dexterityInit), agility(agilityInit), money(0), experience(0) { }
};

//Ενας μαχητής (Warrior) είναι ένας ήρωας που είναι ευνοημένος στοντομέα  της  δύναμης  και  της  ευκινησίας.
//Αυτό  σημαίνει  ότι  οι  αρχικές  τιμές  σε  αυτά  τα  στατιστικά,θα είναι υψηλότερες από τα υπόλοιπα, καθώς και ότι όταν ο ήρωας ανεβαίνει επίπεδο,
//τα στατιστικάαυτά  θα  επηρεάζονται  περισσότερο. 

class Warrior : public Hero {
    public:
        Warrior(const char* initName) : Hero(initName, 5, 2, 5) {
            cout << "A warrior had been created" << endl;
        }
};

// Ενας  μάγος  (Sorcerer)  είναι  ένας  ήρωας  που  είναι  ευνοημένος στον τομέα της επιδεξιότητας και της ευκινησίας.

class Sorcerer : public Hero {
    public:
        Sorcerer(const char* initName) : Hero(initName, 2, 5, 5) {
            cout << "A sorcerer had been created" << endl;
        }
};

//Ενας ιππότης (Paladin) είναι ένας ήρωας που είναιευνοημένος στον τομέα της δύναμης και της επιδεξιότητας.

class Paladin : public Hero {
    public:
        Paladin(const char* initName) : Hero(initName, 5, 5, 2) {
            cout << "A paladin had been created" << endl;
        }
};

//Ενα  τέρας  (Monster)  είναι  ένα  ζωντανό  ον.
//Εχει  ένα  εύρος  ζημιάς  που  μπορεί  να  προκαλέσει σε κάθε επίθεση του, ένα ποσό άμυνας το οποίο αφαιρείται από τη ζημιά που δέχεται σε μια επίθεση
//του αντιπάλου του, και μια πιθανότητα να αποφύγει κάποια επίθεση του αντιπάλου του.

class Monster : public Living {
    int minDamage;
    int maxDamage;
    int defense;
    int agility;
    public:
        Monster(const char* initName, int initMinDamage, int initMaxDamage, int initDefense, int initAgility)
        :   Living(initName), minDamage(initMinDamage), maxDamage(initMaxDamage), defense(initDefense), agility(initAgility) { }
};

//Ενας δράκος(Dragon) είναι ένα τέρας που είναι ευνοημένο στο εύρος ζημιάς που μπορεί να προκαλέσει.

class Dragon : public Monster {
    public:
        Dragon(const char* initName)
        :   Monster(initName, 3, 6, 2, 2) { }
};

//Ενα ον με  εξωσκελετό  (Exoskeleton)  είναι  ένα  τέρας  που  είναι  ευνοημένο  στο  ποσό  άμυνας  που  διαθέτει.

class Exoskeleton : public Monster {
    public:
        Exoskeleton(const char* initName)
        :   Monster(initName, 1, 2, 6, 2) { }
};

//Ενα  πνεύμα  (Spirit)  είναι  ένα  τέρας  που  είναι  ευνοημένο  στο  πόσο  συχνά  αποφεύγει  επιθέσεις  του αντιπάλου του.

class Spirit : public Monster {
    public:
        Spirit(const char* initName)
        :   Monster(initName, 1, 2, 2, 6) { }
};

enum Square { nonAccesible, market, common };

enum HeroType { warrior, sorcerer, paladin };

enum Phase { onMap, inBattle, inShop };

enum Direction { up, down, left, right };

class Grid {
    Square** grid;
    int width;
    int height;
    Hero** party;
    int heroNum;
    int position[2];
    vector<Item> items;
    vector<Spell> spells;
    public:
        Grid(int initWidth, int initHeight, HeroType* heroTypes, int heroNumInit)
        :   width(initWidth), height(initHeight), heroNum(heroNumInit), position{0,0} {
            grid = new Square*[width];
            for (int i = 0 ; i < width ; i++) {
                grid[i] = new Square[height];
            }
            srand(time(NULL));
            for (int i = 0 ; i < width ; i++) {
                for (int j = 0 ; j < height ; j++) {
                    if (!(rand() % 5)) {
                        grid[i][j] = nonAccesible;
                    }
                    else if (!(rand() % 3)) {
                        grid[i][j] = market;
                    }
                    else {
                        grid[i][j] = common;
                    }
                }
            }
            party = new Hero*[heroNum];
            for (int i = 0 ; i < heroNum ; i++) {
                if (heroTypes[i] == warrior) {
                    party[i] = new Warrior(heroNames[rand() % 98]);
                }
                else if (heroTypes[i] == sorcerer) {
                    party[i] = new Sorcerer(heroNames[rand() % 98]);
                }
                else {
                    party[i] = new Paladin(heroNames[rand() % 98]);
                }
            }
        }
        ~Grid() {
            for (int i = 0 ; i < width ; i++) {
                delete[] grid[i];
            }
            delete[] grid;
            for (int i = 0 ; i < heroNum ; i++) {
                delete party[i];
            }
            delete[] party;
        }
};

int main(int argc, char* argv[]) {
    int width, height, heroNum;
    cout << "Enter grid width:" << endl;
    cin >> width;
    cout << "Enter grid height:" << endl;
    cin >> height;
    do {
    cout << "Enter number of heroes in party (between 1 and 3):" << endl;
    cin >> heroNum;
    } while (heroNum < 1 || heroNum > 3);
    HeroType heroTypes[heroNum];
    string input;
    for (int i = 0 ; i  < heroNum ; i++) {
        cout << "Enter type of " << i + 1 << (i == 0 ? "st" : (i == 1 ? "nd" : "rd")) << " hero:" << endl;
        cin >> input;
        if (!input.compare("Warrior")) {
            heroTypes[i] = warrior;
        }
        else if (!input.compare("Sorcerer")) {
            heroTypes[i] = sorcerer;
        }
        else if (!input.compare("Paladin")) {
            heroTypes[i] = paladin;
        }
        else {
            cout << "Invalid input" << endl;
            i--;
        }
    }
    Grid grid(width, height, heroTypes, heroNum);
    while (true) {
        cin >> input;
        if (!input.compare("quitGame")) {
            break;
        }
        else {
            cout << "Unknown command" << endl;
        }
    }
}