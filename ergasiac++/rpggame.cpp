/* File: rpggame.cpp */

#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <vector>
#include "rpggame.h"
#include "names.h"

/* ----- Συναρτήσεις της Party ----- */

// Constructor
Party::Party(HeroType* heroTypes, int heroNumInit) : heroNum(heroNumInit), heroes(new Hero*[heroNumInit]) {
    for (int i = 0 ; i < heroNum ; ++i) {
        if (heroTypes[i] == warrior) {
            heroes[i] = new Warrior(livingNames[rand() % 98]);
        }
        else if (heroTypes[i] == sorcerer) {
            heroes[i] = new Sorcerer(livingNames[rand() % 98]);
        }
        else {
            heroes[i] = new Paladin(livingNames[rand() % 98]);
        }
    }
}

// Destructor
Party::~Party() {
    for (int i = 0 ; i < heroNum ; ++i) {
        delete heroes[i];
    }
    delete[] heroes;
}

// Ανοίγει μενού όπου ο χρήστης μπορεί να επιλέξει όπλο ή πανοπλία που έχει διαθέσιμη η ομάδα και να το κάνει equip ο hero.
// Αυτό αφαιρείται από το σύνολο των διαθέσιμων αντικειμένων και προστίθεται σε αυτό ό,τι "πάνω του" πριν ο hero/
// Αν hero == NULL τότε ο χρήστης διαλέγει έναν ήρωα από την ομάδα.
// Επιστρέφει true αν έγινε επιτυχώς η αλλαγή όπλου/πανοπλίας, αλλιώς false.
bool Party::equip(Hero* hero) {

    // επιλογή ήρωα
    if (hero == NULL) {
        int heroPos = 0;
        if (heroNum > 1) {
            do {
                std::cout << "Which hero should equip? (1-" << heroNum << ")" << std::endl;
                std::cin.clear();
                std::cin.ignore(1000, '\n');
                std::cin >> heroPos;
                --heroPos;
            }   while ((heroPos < 0) || (heroPos >= heroNum));
        }
        hero = heroes[heroPos];
    }

    // equip όπλο ή πανοπλία;
    std::cout << "What to equip?" << std::endl;
    while (true) {
        std::string input;
        std::cin >> input;

        // equip όπλο
        if (!input.compare("weapon")) {
            if (ownedWeapons.size() == 0) {
                std::cout << "No weapons owned" << std::endl;
                return false;
            }

            // επιλογή όπλου
            std::cout << "Which weapon to equip?" << std::endl;
            int i = 0;
            for (std::vector<Weapon*>::iterator iter = ownedWeapons.begin() ; iter != ownedWeapons.end() ; ++iter, ++i) {
                std::cout << "\n(" << i + 1 << ")" << std::endl;
                (*iter)->print();
            }
            int weaponPos;
            while (true) {
                std::cin >> input;
                if (!input.compare("back")) {
                    return false;
                }
                else if ((atoi(input.c_str()) > 0) && (atoi(input.c_str()) <= ownedWeapons.size())) {
                    weaponPos = atoi(input.c_str()) - 1;
                    break;
                }
                else {
                    std::cout << "Invalid input" << std::endl;
                }
            }
            Weapon* toEquip = ownedWeapons[weaponPos];

            // equip
            Weapon* oldWeapon;
            if ((oldWeapon = hero->equip(toEquip)) != toEquip) {
                if (oldWeapon != NULL) {
                    ownedWeapons[weaponPos] = oldWeapon;
                }
                else {
                    ownedWeapons.erase(ownedWeapons.begin() + weaponPos);
                }
                return true;
            }
            else {
                return false;
            }
        }

        // equip πανοπλία
        else if (!input.compare("armor")) {
            if (ownedArmors.size() == 0) {
                std::cout << "No armors owned" << std::endl;
                return false;
            }

            // επιλογή πανοπλίας
            std::cout << "Which armor to equip?" << std::endl;
            int i = 0;
            for (std::vector<Armor*>::iterator iter = ownedArmors.begin() ; iter != ownedArmors.end() ; ++iter, ++i) {
                std::cout << "\n(" << i + 1 << ")" << std::endl;
                (*iter)->print();
            }
            int armorPos;
            while (true) {
                std::cin >> input;
                if (!input.compare("back")) {
                    return false;
                }
                else if ((atoi(input.c_str()) > 0) && (atoi(input.c_str()) <= ownedArmors.size())) {
                    armorPos = atoi(input.c_str()) - 1;
                    break;
                }
                else {
                    std::cout << "Invalid input" << std::endl;
                }
            }
            Armor* toEquip = ownedArmors[armorPos];

            // equip
            Armor* oldArmor;
            if ((oldArmor = hero->equip(toEquip)) != toEquip) {
                if (oldArmor != NULL) {
                    ownedArmors[armorPos] = oldArmor;
                }
                else {
                    ownedArmors.erase(ownedArmors.begin() + armorPos);
                }
                return true;
            }
            else {
                return false;
            }
        }

        else if (!input.compare("back")) {
            return false;
        }

        else {
            std::cout << "Invalid input" << std::endl;
        }
    }
}

// Ανοίγει μενού όπου ο χρήστης μπορεί να επιλέξει ένα φίλτρο που έχει διαθέσιμη η ομάδα και να το κάνει use ο hero.
// Αυτό αφαιρείται από το σύνολο των διαθέσιμων φίλτρων. Αν hero == NULL τότε ο χρήστης διαλέγει έναν ήρωα από την ομάδα.
// Επιστρέφει true αν έγινε επιτυχώς η χρήση, αλλιώς false.
bool Party::use(Hero* hero) {
    if (ownedPotions.size() == 0) {
        std::cout << "No potions owned" << std::endl;
        return false;
    }

    // επιλογή ήρωα
    if (hero == NULL) {
        int heroPos = 0;
        if (heroNum > 1) {
            do {
                std::cout << "Which hero should use it? (1-" << heroNum << ")" << std::endl;
                std::cin.clear();
                std::cin.ignore(1000, '\n');
                std::cin >> heroPos;
                --heroPos;
            }   while ((heroPos < 0) || (heroPos >= heroNum));
        }
        hero = heroes[heroPos];
    }

    // επιλογή φίλτρου
    std::cout << "Which potion to use?" << std::endl;
    int i = 0;
    for (std::vector<Potion*>::iterator iter = ownedPotions.begin() ; iter != ownedPotions.end() ; ++iter, ++i) {
        std::cout << "\n(" << i + 1 << ")" << std::endl;
        (*iter)->print();
    }
    int potionPos;
    while (true) {
        std::string input;
        std::cin >> input;
        if (!input.compare("back")) {
            return false;
        }
        else if ((atoi(input.c_str()) > 0) && (atoi(input.c_str()) <= ownedPotions.size())) {
            potionPos = atoi(input.c_str()) - 1;
            break;
        }
        else {
            std::cout << "Invalid input" << std::endl;
        }
    }
    Potion* toUse = ownedPotions[potionPos];

    // χρήση
    if (hero->use(*toUse)) {
        ownedPotions.erase(ownedPotions.begin() + potionPos);
        return true;
    }
    else {
        return false;
    }
}

// Αρχίζει μια μάχη σε γύρους μεταξύ της ομάδας και κάποιων τεράτων. Η διεξάγεται μέσω μενού όπου ο χρήστης μπορεί να
// επιλέξει τις κινήσεις των ηρώων της ομάδας. Μπορεί να κάνει κανονική επίθεση (attack), να κάνει επίθεση με κάποιο
// ξόρκι (castSpell) να χρησιμοποιήσει κάποιο φίλτρο (use) ή να αλλάξει όπλο ή πανοπλία (equip). Τα τέρατα επιτίθενται στον πρώτο
// σε σειρά "ζωντανό" ήρωα. Στο τέλος κάθε γύρου καλούνται οι συναρτήσεις endTurn για τους ήρωες και τα τέρατα.
// Η μάχη τελειώνει όταν φτάσει η ζωτική ενέργεια όλων των τεράτων ή όλων των ηρώων στο μηδέν. Αν η μάχη τελειώσει επειδή νίκησαν οι
// ήρωες, τότε αυτοί λαμβάνουν κάποια χρήματα και εμπειρία βάσει του επιπέδου τους και του πλήθους των τεράτων που αντιμετώπισαν.
// Αλλιώς, οι ήρωες χάνουν τα μισά χρήματα τους. Αν στο τέλος κάποιος ήρωας έχει απομείνει με μηδέν HP, τότε αυτή επαναφέρεται στο μισό της maxHP.
void Party::battle() {
    std::cout << "Battle!" << std::endl;

    // δημιουργία τεράτων επιπέδου όσο του μέσου όρου των ηρώων
    int averageHeroLevel = 0;
    for (int i = 0 ; i < heroNum ; ++i) {
        averageHeroLevel += heroes[i]->getLevel();
    }
    averageHeroLevel /= heroNum;
    int monsterNum = heroNum + (rand() % 2);
    Monster** monsters = new Monster*[monsterNum];
    for (int i = 0 ; i < monsterNum ; ++i) {
        if (!(rand() % 3)) {
            monsters[i] = new Dragon(livingNames[rand() % 98], averageHeroLevel);
        }
        else if (!(rand() % 2)) {
            monsters[i] = new Exoskeleton(livingNames[rand() % 98], averageHeroLevel);
        }
        else {
            monsters[i] = new Spirit(livingNames[rand() % 98], averageHeroLevel);
        }
    }

    // διαδικασία μάχης
    bool won, lost;
    while (true) {  // κάθε επανάληψη είανι ένας γύρος
        std::string input;

        // εκτύπωση στατιστικών
        std::cout << "Display stats? (y/n)" << std::endl;
        while (true) {
            std::cin >> input;
            if (!input.compare("y")) {
                displayHeroStats();
                for (int i = 0 ; i < monsterNum ; ++i) {
                    std::cout << i + 1 << (i == 0 ? "st" : (i == 1 ? "nd" : (i == 2 ? "rd" : "th"))) << " monster's stats: " << std::endl;
                    monsters[i]->print();
                }
                break;
            }
            else if (!input.compare("n")) {
                break;
            }
            else {
                std::cout << "Invalid input" << std::endl;
            }
        }

        won = true, lost = true;

        // σειρά των ηρώων
        for (int i = 0 ; i < heroNum ; ++i) {

            // επιλογή πράξης αν ο ήρωας δεν έχει λιποθυμήσει
            if (heroes[i]->getHealthPower() != 0) {
                lost = false;
                while (true) {
                    std::cout << "What should " << heroes[i]->getName() << " do?" << std::endl;
                    std::cin >> input;

                    // κανονική επίθεση
                    if (!input.compare("attack")) {
                        int numInput;

                        // επιλογή τέρατος στο οποίο θα επιτεθεί
                        std::cout << "Which monster to attack?" << std::endl;
                        for (int j = 0 ; j < monsterNum ; ++j) {
                            std::cout << "(" << j + 1 << ") " << monsters[j]->getName() << ", HP: " << monsters[j]->getHealthPower() <<  std::endl;
                        }
                        while (true) {
                            std::cin.clear();
                            std::cin.ignore(1000, '\n');
                            std::cin >> numInput;
                            if ((numInput > 0) && (numInput <= monsterNum)) {
                                break;
                            }
                            else {
                                std::cout << "Invalid input" << std::endl;
                            }
                        }

                        // επίθεση
                        heroes[i]->attack(*monsters[numInput - 1]);
                        break;
                    }

                    // επίθεση με ξόρκι
                    else if (!input.compare("castSpell")) {
                        if (ownedSpells.size() == 0) {
                            std::cout << "No spells owned" << std::endl;
                            continue;
                        }

                        // επιλογή ξορκιού
                        std::cout << "Which spell to cast?" << std::endl;
                        int j = 0;
                        for (std::vector<Spell*>::iterator iter = ownedSpells.begin() ; iter != ownedSpells.end() ; ++iter, ++j) {
                            std::cout << "\n(" << j + 1 << ")" << std::endl;
                            (*iter)->print();
                        }
                        int spellPos;
                        while (true) {
                            std::string input;
                            std::cin >> input;
                            if ((atoi(input.c_str()) > 0) && (atoi(input.c_str()) <= ownedSpells.size())) {
                                spellPos = atoi(input.c_str()) - 1;
                                break;
                            }
                            else {
                                std::cout << "Invalid input" << std::endl;
                            }
                        }
                        Spell* toCast = ownedSpells[spellPos];

                        // επιλογή τέρατος στο οποίο θα επιτεθεί
                        int numInput;
                        std::cout << "Which monster to cast the spell on?" << std::endl;
                        for (int j = 0 ; j < monsterNum ; ++j) {
                            std::cout << "(" << j + 1 << ") " << monsters[j]->getName() << ", HP: " << monsters[j]->getHealthPower() <<  std::endl;
                        }
                        while (true) {
                            std::cin.clear();
                            std::cin.ignore(1000, '\n');
                            std::cin >> numInput;
                            if ((numInput > 0) && (numInput <= monsterNum)) {
                                break;
                            }
                            else {
                                std::cout << "Invalid input" << std::endl;
                            }
                        }

                        // επίθεση
                        if (heroes[i]->castSpell(*toCast, *monsters[numInput - 1])) {
                            break;
                        }
                    }

                    // χρήση φίλτρου
                    else if (!input.compare("use")) {
                        if (use(heroes[i])) {
                            break;
                        }
                    }

                    // αλλαγή όπλου ή πανοπλίας
                    else if (!input.compare("equip")) {
                        if (equip(heroes[i])) {
                            break;
                        }
                    }

                    else {
                        std::cout << "Unknown command" << std::endl;
                    }
                }
            }
        }

        // σειρά των τεράτων
        for (int i = 0 ; i < monsterNum ; ++i) {
            if (monsters[i]->getHealthPower() != 0) {
                won = false;
                for (int j = 0 ; j < heroNum; ++j) {
                    if (heroes[j]->getHealthPower() != 0) {
                        std::cout << monsters[i]->getName() << " attacks " << heroes[j]->getName() << "!" << std::endl;
                        monsters[i]->attack(*heroes[j]);
                        break;
                    }
                }
            }
        }

        // αν οι ήρωες νίκησαν ή έχασαν, τελειώνει η μάχη
        if (won || lost) {
            break;
        }

        // πέρασμα γύρου για τους ήρωες
        for (int i = 0 ; i < heroNum ; ++i) {
            heroes[i]->endTurn();
        }

        // πέρασμα γύρου για τα τέρατα
        for (int i = 0 ; i < monsterNum ; ++i) {
            monsters[i]->endTurn();
        }
    }

    // κέρδος χρημάτων και εμπειρίας από τους ήρωες σε περίπτωση νίκης
    if (won) {
        std::cout << "The party has won!" << std::endl;
        for (int i = 0 ; i < heroNum ; ++i) {
            heroes[i]->setMoney(heroes[i]->getMoney() + heroes[i]->getLevel()*10 + monsterNum*20);
            heroes[i]->gainExperience(heroes[i]->getLevel()*5 + monsterNum*20);
        }
    }

    // χάσιμο των μισών χρημάρων των ηρώων σε περίπτωση ήττας
    else {
        std::cout << "The party has lost!" << std::endl;
        for (int i = 0 ; i < heroNum ; ++i) {
            heroes[i]->setMoney(heroes[i]->getMoney() / 2);
        }
    }

    // επαναφορά μισής ζωτικής ενέργειας των ηρώων που είχαν μείνει με 0
    for (int i = 0 ; i < heroNum ; ++i) {
        if (heroes[i]->getHealthPower() == 0) {
            heroes[i]->recoverHealthPower(heroes[i]->getMaxHealthPower() / 2);
        }
    }

    // διαγραφή τεράτων
    for (int i = 0 ; i < monsterNum ; ++i) {
        delete monsters[i];
    }
    delete[] monsters;
}

// Αν οι ήρωες έχουν συνολικά amount χρήματα, αφαιρούνται από αυτούς, και επιστρέφεται true, αλλιώς false.
bool Party::pay(int amount) {
    int totalMoney = 0;
    for (int i = 0 ; i < heroNum ; ++i) {
        totalMoney += heroes[i]->getMoney();
    }
    if (totalMoney < amount) {
        std::cout << "Not enough money" << std::endl;
        return false;
    }
    for (int i = 0 ; i < heroNum ; ++i) {
        if (heroes[i]->spendMoney(amount)) {
            break;
        }
        else {
            amount -= heroes[i]->getMoney();
            heroes[i]->spendMoney(heroes[i]->getMoney());
        }
    }
    return true;
}

// Η ομάδα πληρώνει (pay) την τιμή του όπλου, και αν το κάνει επιτυχώς το όπλο προστίθεται στο σύνολο των διαθέσιμων όπλων.
void Party::buy(Weapon* weapon) {
    if (pay(weapon->getPrice())) {
        ownedWeapons.push_back(weapon);
    }
}

// Η ομάδα πληρώνει (pay) την τιμή της πανοπλίας, και αν το κάνει επιτυχώς το όπλο προστίθεται στο σύνολο των διαθέσιμων πανοπλιών.
void Party::buy(Armor* armor) {
    if (pay(armor->getPrice())) {
        ownedArmors.push_back(armor);
    }
}

// Η ομάδα πληρώνει (pay) την τιμή του φίλτρου, και αν το κάνει επιτυχώς το όπλο προστίθεται στο σύνολο των διαθέσιμων φίλτρων.
void Party::buy(Potion* potion) {
    if (pay(potion->getPrice())) {
        ownedPotions.push_back(potion);
    }
}

// Η ομάδα πληρώνει (pay) την τιμή του ξορκιού, και αν το κάνει επιτυχώς το όπλο προστίθεται στο σύνολο των διαθέσιμων ξορκιών.
void Party::buy(Spell* spell) {
    if (pay(spell->getPrice())) {
        ownedSpells.push_back(spell);
    }
}

// Ανοίγει μενού όπου ο χρήστης μπορεί να επιλέξει κάτι που έχει διαθέσιμο η ομάδα πουλήσει.
// Η ομάδα λαμβάνει την μισή τιμή του αντικειμένου (ή ξορκιού) σε χρήματα, και αυτό αφαιρείται από τα διαθέσιμα.
void Party::sell() {
    while (true) {
        std::string input;
        std::cout << "What to sell?" << std::endl;
        while (true) {
            // επιλογή τύπου αντικειμένου
            std::cin >> input;
            if (!input.compare("weapon")) {
                if (ownedWeapons.size() == 0) {
                    std::cout << "No weapons owned" << std::endl;
                    return;
                }

                // επιλογή όπλου
                std::cout << "Which weapon to sell?" << std::endl;
                int i = 0;
                for (std::vector<Weapon*>::iterator iter = ownedWeapons.begin() ; iter != ownedWeapons.end() ; ++iter, ++i) {
                    std::cout << "\n(" << i + 1 << ")" << std::endl;
                    (*iter)->print();
                }
                int weaponPos;
                while (true) {
                    std::cin >> input;
                    if (!input.compare("back")) {
                        return;
                    }
                    else if ((atoi(input.c_str()) > 0) && (atoi(input.c_str()) <= ownedWeapons.size())) {
                        weaponPos = atoi(input.c_str()) - 1;
                        break;
                    }
                    else {
                        std::cout << "Invalid input" << std::endl;
                    }
                }

                // πώληση
                heroes[0]->spendMoney(-1*(ownedWeapons[weaponPos]->getPrice()/2));
                ownedWeapons.erase(ownedWeapons.begin() + weaponPos);
                break;
            }
            else if (!input.compare("armor")) {
                if (ownedArmors.size() == 0) {
                    std::cout << "No armors owned" << std::endl;
                    return;
                }

                // επιλογή πανοπλίας
                std::cout << "Which armor to sell?" << std::endl;
                int i = 0;
                for (std::vector<Armor*>::iterator iter = ownedArmors.begin() ; iter != ownedArmors.end() ; ++iter, ++i) {
                    std::cout << "\n(" << i + 1 << ")" << std::endl;
                    (*iter)->print();
                }
                int armorPos;
                while (true) {
                    std::cin >> input;
                    if (!input.compare("back")) {
                        return;
                    }
                    else if ((atoi(input.c_str()) > 0) && (atoi(input.c_str()) <= ownedArmors.size())) {
                        armorPos = atoi(input.c_str()) - 1;
                        break;
                    }
                    else {
                        std::cout << "Invalid input" << std::endl;
                    }
                }

                // πώληση
                heroes[0]->spendMoney(-1*(ownedArmors[armorPos]->getPrice()/2));
                ownedArmors.erase(ownedArmors.begin() + armorPos);
                break;
            }
            else if (!input.compare("potion")) {
                if (ownedPotions.size() == 0) {
                    std::cout << "No potions owned" << std::endl;
                    return;
                }

                // επιλογή φίλτρου
                std::cout << "Which potion to sell?" << std::endl;
                int i = 0;
                for (std::vector<Potion*>::iterator iter = ownedPotions.begin() ; iter != ownedPotions.end() ; ++iter, ++i) {
                    std::cout << "\n(" << i + 1 << ")" << std::endl;
                    (*iter)->print();
                }
                int potionPos;
                while (true) {
                    std::cin >> input;
                    if (!input.compare("back")) {
                        return;
                    }
                    else if ((atoi(input.c_str()) > 0) && (atoi(input.c_str()) <= ownedPotions.size())) {
                        potionPos = atoi(input.c_str()) - 1;
                        break;
                    }
                    else {
                        std::cout << "Invalid input" << std::endl;
                    }
                }

                // πώληση
                heroes[0]->spendMoney(-1*(ownedPotions[potionPos]->getPrice()/2));
                ownedPotions.erase(ownedPotions.begin() + potionPos);
                break;
            }
            else if (!input.compare("spell")) {
                if (ownedSpells.size() == 0) {
                    std::cout << "No spells owned" << std::endl;
                    return;
                }

                // επιλογή ξορκιού
                std::cout << "Which spell to sell?" << std::endl;
                int i = 0;
                for (std::vector<Spell*>::iterator iter = ownedSpells.begin() ; iter != ownedSpells.end() ; ++iter, ++i) {
                    std::cout << "\n(" << i + 1 << ")" << std::endl;
                    (*iter)->print();
                }
                int spellPos;
                while (true) {
                    std::cin >> input;
                    if (!input.compare("back")) {
                        return;
                    }
                    else if ((atoi(input.c_str()) > 0) && (atoi(input.c_str()) <= ownedSpells.size())) {
                        spellPos = atoi(input.c_str()) - 1;
                        break;
                    }
                    else {
                        std::cout << "Invalid input" << std::endl;
                    }
                }

                // πώληση
                heroes[0]->spendMoney(-1*(ownedSpells[spellPos]->getPrice()/2));
                ownedSpells.erase(ownedSpells.begin() + spellPos);
                break;
            }
            else {
                std::cout << "Invalid input" << std::endl;
            }
        }

        // επιλογή συνέχειας ή εξόδου
        bool done;
        std::cout << "Sell more? (y/n)" << std::endl;
        while (true) {
            std::cin >> input;
            if (!input.compare("y")) {
                done = false;
                break;
            }
            else if (!input.compare("n")) {
                done = true;
                break;
            }
            else {
                std::cout << "Invalid input" << std::endl;
            }
        }
        if (done) {
            break;
        }
    }
}

// Εκτυπώνει το σύνολο των αντικειμένων (συμπεριλαμβανομένων των ξορκιών) που έχει διαθέσιμα η ομάδα
void Party::checkInventory() const {
    std::cout << "Weapons in inventory:" << std::endl;
    for (std::vector<Weapon*>::const_iterator iter = ownedWeapons.begin() ; iter != ownedWeapons.end() ; ++iter) {
        (*iter)->print();
    }
    std::cout << "Armors in inventory:" << std::endl;
    for (std::vector<Armor*>::const_iterator iter = ownedArmors.begin() ; iter != ownedArmors.end() ; ++iter) {
        (*iter)->print();
    }
    std::cout << "Potions in inventory:" << std::endl;
    for (std::vector<Potion*>::const_iterator iter = ownedPotions.begin() ; iter != ownedPotions.end() ; ++iter) {
        (*iter)->print();
    }
    std::cout << "Spells in inventory:" << std::endl;
    for (std::vector<Spell*>::const_iterator iter = ownedSpells.begin() ; iter != ownedSpells.end() ; ++iter) {
        (*iter)->print();
    }
}

// Εκτυπώνει τους ήρωες της ομάδας
void Party::displayHeroStats() const {
    for (int i = 0 ; i < heroNum ; ++i) {
        std::cout << i + 1 << (i == 0 ? "st" : (i == 1 ? "nd" : "rd")) << " hero's stats: " << std::endl;
        heroes[i]->print();
    }
}

/* ----- Συναρτήσεις της Market ----- */

// Constructor. Τα αντικείμενα φτιάχνονται κατά αύξουσα "δύναμη". Όσο περισσότερα τόσο πιο "δυνατό" το τελευταίο.
// Τα φίλτρα χωρίζονται δια τρία σε δύναμης, επιδεξιότητας και ετκινησίας, και τα ξόρκια σε πάγου, φωτιάς και ηλεκτρισμού.
Market::Market(int weaponNumInit, int armorNumInit, int potionNumInit, int spellNumInit)
:   weaponAmount(weaponNumInit), armorAmount(armorNumInit), potionAmount(potionNumInit), spellAmount(spellNumInit) {
    int armorOffset = weaponAmount;
    int potionOffset = armorOffset + armorAmount;
    int spellOffset = potionOffset + potionAmount;
    int itemAmount = spellOffset + spellAmount;
    stock = new Item*[itemAmount];
    for (int i = 0 ; i < weaponAmount ; ++i) {
        stock[i] = new Weapon(weaponNames[i % 119], i + 1, i/(2*weaponAmount/3));
    }
    for (int i = armorOffset ; i < armorOffset + armorAmount ; ++i) {
        stock[i] = new Armor(armorNames[(i - armorOffset) % 80], i - armorOffset + 1);
    } 
    for (int i = potionOffset ; i < potionOffset + potionAmount/3 ; ++i) {
        stock[i] = new StrengthPotion(potionNames[(i - potionOffset) % 66], i - potionOffset + 1);
    }
    for (int i = potionOffset + potionAmount/3 ; i < potionOffset + (2*potionAmount)/3 ; ++i) {
        stock[i] = new DexterityPotion(potionNames[(i - potionOffset) % 66], i - (potionOffset + potionAmount/3) + 1);
    }
    for (int i = potionOffset + (2*potionNumInit)/3 ; i < potionOffset + potionAmount ; ++i) {
        stock[i] = new AgilityPotion(potionNames[(i - potionOffset) % 66], i - (potionOffset + (2*potionNumInit)/3) + 1);
    }
    for (int i = spellOffset ; i < spellOffset + spellAmount/3 ; ++i) {
        stock[i] = new IceSpell(spellNames[(i - spellOffset) % 91], i - spellOffset + 1, 2*(i - spellOffset + 1), (i - spellOffset + 2)*5);
    }
    for (int i = spellOffset + spellAmount/3 ; i < spellOffset + (2*spellAmount)/3 ; ++i) {
        stock[i] = new FireSpell(spellNames[(i - spellOffset) % 91],
                                i - (spellOffset + spellAmount/3) + 1,
                                2*(i - (spellOffset + spellAmount/3) + 1),
                                (i - (spellOffset + spellAmount/3) + 2)*5);
    }
    for (int i = spellOffset + (2*spellAmount)/3 ; i < spellOffset + spellAmount ; ++i) {
        stock[i] = new LightingSpell(spellNames[(i - spellOffset) % 91],
                                    i - (spellOffset + (2*spellAmount)/3) + 1,
                                    2*(i - (spellOffset + (2*spellAmount)/3) + 1),
                                    (i - (spellOffset + (2*spellAmount)/3) + 2)*5);
    }
}

// Destructor
Market::~Market() {
    for (int i = 0 ; i < weaponAmount + armorAmount + potionAmount + spellAmount ; ++i) {
        delete stock[i];
    }
    delete[] stock;
}

// Ανοίγει μενού όπου ο χρήστης μπορεί να επιλέξει κάτι που έχει διαθέσιμο η αγορά για να το αγοράσει (buy) το party
void Market::buy(Party& party) {
    while (true) {
        std::string input;
        int offset, amount;
        int type;

        // επιλογή τύπου αντικειμένου
        std::cout << "What to buy?" << std::endl;
        while (true) {
            std::cin >> input;
            if (!input.compare("weapon")) {
                offset = 0;
                amount = weaponAmount;
                type = 0;
                break;
            }
            else if (!input.compare("armor")) {
                offset = weaponAmount;
                amount = armorAmount;
                type = 1;
                break;
            }
            else if (!input.compare("potion")) {
                offset = weaponAmount + armorAmount;
                amount = potionAmount;
                type = 2;
                break;
            }
            else if (!input.compare("spell")) {
                offset = weaponAmount + armorAmount + potionAmount;
                amount = spellAmount;
                type = 3;
                break;
            }
            else {
                std::cout << "Invalid input" << std::endl;
            }
        }

        // επιλογή αντικειμένου
        std::cout << "Choose one:" << std::endl;
        for (int i = 0 ; i < amount ; ++i) {
            std::cout << "\n(" << i + 1 << ")" << std::endl;
            stock[i + offset]->print();
        }
        while (true) {
            std::cin >> input;
            if (!input.compare("back")) {
                break;
            }
            else if ((atoi(input.c_str()) > 0) && (atoi(input.c_str()) <= amount)) {
                if (type == 0) {
                    // αγορά όπλου
                    party.buy((Weapon*) stock[atoi(input.c_str()) - 1 + offset]);
                }
                else if (type == 1) {
                    // αγορά πανοπλίας
                    party.buy((Armor*) stock[atoi(input.c_str()) - 1 + offset]);
                }
                else if (type == 2) {
                    // αγορά φίλτρου
                    party.buy((Potion*) stock[atoi(input.c_str()) - 1 + offset]);
                }
                else if (type == 3) {
                    // αγορά ξορκιού
                    party.buy((Spell*) stock[atoi(input.c_str()) - 1 + offset]);
                }
                break;
            }
            else {
                std::cout << "Invalid input" << std::endl;
            }
        }

        // επιλογή συνέχειας ή εξόδου
        bool done;
        std::cout << "Buy more? (y/n)" << std::endl;
        while (true) {
            std::cin >> input;
            if (!input.compare("y")) {
                done = false;
                break;
            }
            else if (!input.compare("n")) {
                done = true;
                break;
            }
            else {
                std::cout << "Invalid input" << std::endl;
            }
        }
        if (done) {
            break;
        }
    }
}

/* ----- Συναρτήσεις της Grid ----- */

// Constructor. Ορίζει τυχαία το είδος των τετργώνων εκτός από το αρχικό, που είναι common.
// Φτιάχνει μια ομάδα όπως ορίζουν τα ορίσματα και μια αγορά με 15 αντικείμενα κάθε είδους,
Grid::Grid(int initWidth, int initHeight, HeroType* heroTypes, int heroNumInit)
:   width(initWidth), height(initHeight), party(heroTypes, heroNumInit), position{0,0}, gameMarket(15, 15, 15, 15) {
    // δημιουργία πλέγματος
    grid = new Square*[width];
    for (int i = 0 ; i < width ; ++i) {
        grid[i] = new Square[height];
    }

    // τυχαία αρχικοποίηση πλέγματος
    srand(time(NULL));
    for (int i = 0 ; i < width ; ++i) {
        for (int j = 0 ; j < height ; ++j) {
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
    // με το αρχικό τετράγωνο να είναι common
    grid[0][0] = common;
}

// Destructor
Grid::~Grid() {
    for (int i = 0 ; i < width ; ++i) {
        delete[] grid[i];
    }
    delete[] grid;
}

// Αρχίζει το παιχνίδι, δίνοντας στον χρήστη την δυνατότητα μέσω εντολών να κινηθεί στο πλέγμα (move).
// Μπορεί επίσης να δει τις πληροφορίες των ηρώων της ομάδας (displayHeroStats), να δει τα αντικείμενα και ξόρκια που διαθέτει
// (checkInventory), να χρησιμοποιήσει όπλα (equip), πανοπλίες (equip) και φίλτρα (use) πάνω στους ήρωες της ομάδας.
// Οταν βρίσκεται σε τετράγωνο αγοράς, μπορεί και να αγοράσει (buy) και να πουλήσει (sell) αντικείμενα και ξόρκια.
// Μπορεί επίσης να σταματήσει το παιχνίδι (quitGame).
void Grid::playGame() {
    // επιλογή εντολής
    while (true) {
        std::string input;
        std::cin >> input;

        // έξοδος από το παιχνίδι
        if (!input.compare("quitGame")) {
            break;
        }

        // κίνηση προς μια κατεύθυνση
        else if (!input.compare("move")) {
            while (true) {
                std::cin >> input;
                if (!input.compare("up")) {
                    move(upDir);
                    break;
                }
                else if (!input.compare("down")) {
                    move(downDir);
                    break;
                }
                else if (!input.compare("left")) {
                    move(leftDir);
                    break;
                }
                else if (!input.compare("right")) {
                    move(rightDir);
                    break;
                }
                else {
                    std::cout << "Not a valid direction" << std::endl;
                }
            }
        }

        // εκτύπωση των στοιχείων των ηρώων της ομάδας
        else if (!input.compare("displayHeroStats")) {
            party.displayHeroStats();
        }

        // εκτύπωση των αντικειμένων (συμπεριλαμβανομένων των ξορκιών) της ομάδας
        else if (!input.compare("checkInventory")) {
            party.checkInventory();
        }

        // equip διαθέσιμου όπλου ή πανοπλίας από ήρωα της ομάδας
        else if (!input.compare("equip")) {
            party.equip();
        }

        // χρήση διαθέσιμου φίλτρου από ήρωα της ομάδας
        else if (!input.compare("use")) {
            party.use();
        }

        // εκτύπωση πλέγματος
        else if (!input.compare("displayMap")) {
            displayMap();
        }

        // αγορά αντικειμένων, μόνο όταν βρίσκεται η ομάδα σε τετράωνο αγοράς
        else if (!input.compare("buy")) {
            if (grid[position[0]][position[1]] != market) {
                std::cout << "Can't buy outiside of the market" << std::endl;
                continue;
            }
            gameMarket.buy(party);
        }

        // πώληση αντικειμένων, μόνο όταν βρίσκεται η ομάδα σε τετράωνο αγοράς
        else if (!input.compare("sell")) {
            if (grid[position[0]][position[1]] != market) {
                std::cout << "Can't sell outiside of the market" << std::endl;
                continue;
            }
            gameMarket.sell(party);
        }

        else {
            std::cout << "Unknown command" << std::endl;
        }
    }
}

// Κινεί την ομάδα προς την κατεύθυνση direction.
// Αν πάει σε common τετράγωνο υπάρχει μια πιθανότητα να ξεκινήσει μάχη της ομάδας (battle) με τέρατα.
void Grid::move(Direction direction) {
    // κίνηση, αν είναι δυνατή
    if (direction == upDir) {
        if (position[1] + 1 >= height) {
            std::cout << "Can't move out of bounds" << std::endl;
            return;
        }
        if (grid[position[0]][position[1] + 1] == nonAccesible) {
            std::cout << "Can't move into non-accessible square" << std::endl;
            return;
        }
        ++position[1];
    }
    else if (direction == downDir) {
        if (position[1] - 1 < 0) {
            std::cout << "Can't move out of bounds" << std::endl;
            return;
        }
        if (grid[position[0]][position[1] - 1] == nonAccesible) {
            std::cout << "Can't move into non-accessible square" << std::endl;
            return;
        }
        --position[1];
    }
    else if (direction == leftDir) {
        if (position[0] - 1 < 0) {
            std::cout << "Can't move out of bounds" << std::endl;
            return;
        }
        if (grid[position[0] - 1][position[1]] == nonAccesible) {
            std::cout << "Can't move into non-accessible square" << std::endl;
            return;
        }
        --position[0];
    }
    else if (direction == rightDir) {
        if (position[0] + 1 >= width) {
            std::cout << "Can't move out of bounds" << std::endl;
            return;
        }
        if (grid[position[0] + 1][position[1]] == nonAccesible) {
            std::cout << "Can't move into non-accessible square" << std::endl;
            return;
        }
        ++position[0];
    }

    // αν το καινούργιο τετράγωνο είναι common υπάρχει μια πιθανότητα έναρξης μάχης
    if ((grid[position[0]][position[1]] == common) && !(rand() % 4)) {
        party.battle();
    }
}

// Εκτυπώνει το πλέγμα, δηλαδή το είδος κάθε κουτιού και το πού βρίκεται η ομάδα.
void Grid::displayMap() const {
    for (int i = 0 ; i < width ; ++i) {
        for (int j = 0 ; j < height ; ++j) {
            std::cout << "Square " << i + 1 << ", " << j + 1 << ":" << '\n';
            if (grid[i][j] == nonAccesible) {
                std::cout << "Non-accessible" << '\n';
            }
            else if (grid[i][j] == market) {
                std::cout << "Market" << '\n';
            }
            else {
                std::cout << "Common" << '\n';
            }
            if ((i == position[0]) && (j == position[1])) {
                std::cout << "The party is here" << '\n';
            }
            std::cout << std::endl;
        }
    }
}