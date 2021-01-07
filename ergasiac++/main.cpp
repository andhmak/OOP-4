//Να υλοποιηθεί σε C++ η προσομοίωση ενός παιχνιδιού ρόλων (role playing game). Το παιχνίδι θα έχει  αντικείμενα,  ξόρκια,  ήρωες  και  τέρατα.
//Οι  ήρωες  και  τα  τέρατα  ζουν  σε  έναν  κόσμο  που αναπαρίσταται από ένα πλέγμα.  Οι ήρωες μπορούν να εμπλέκονται σε μάχες με τα τέρατα, όπου και
//χρησιμοποιούν αντικείμενα και ξόρκια για να νικήσουν τα τέρατα, ή μπορούν να αγοράζουν αντικείμεναγια να τους βοηθήσουν στην περιπέτεια τους.
//Κάθε φορά που οι ήρωες νικούν κάποια τέρατα μαζεύουν κάποια  χρήματα  και  κερδίζουν  εμπειρία.
//Οταν  αποκτήσουν  αρκετή  εμπειρία,  οι  ήρωες “ανεβαίνουν” ένα επίπεδο, πράγμα που σημαίνει ότι γίνονται πιο δυνατοί στις επιμέρους ικανότητες τους.
#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <list>
#include "names.h"

using namespace std;

// ́Ενα  αντικείμενο  (Item)  έχει  ένα  όνομα,
//   μία  τιμή  αγοράς  και  έχει  και  κάποιο  ελάχιστο  επίπεδοστο  οποίο  πρέπει  να  βρίσκεται  ο  ήρωας  για  να  το  χρησιμοποιήσει.z

class Item {
    std::string name;
    int price;
    int minLevel;
    public:
        Item(const char* initName, int initPrice, int initMinLevel) : name(initName), price(initPrice), minLevel(initMinLevel) { }
        virtual void print() const {
            cout << "Name:       " << name << '\n';
            cout << "Price:      " << price << '\n';
            cout << "Min Level:  " << minLevel << endl;
        }
        int getPrice() const {
            return price;
        }
        int getMinLevel() const {
            return minLevel;
        }
};

//Ενα  όπλο  (Weapon)  είναι  ένααντικείμενο το οποίο μπορεί να χρησιμοποιηθεί από τον ήρωα για να επιτεθεί σε κάποιο τέρας. Εχει ένα συγκεκριμένο ποσό 
//ζημιάς που προκαλεί στον αντίπαλο του και μπορεί να απαιτεί το ένα ή και ταδύο χέρια του ήρωα για να το χρησιμοποιεί.

class Weapon : public Item {
    int damage;
    bool twoHanded;
    public:
        Weapon(const char* initName, int initDamage, int initTwoHanded)
        :   Item(initName, 10*initDamage*(initTwoHanded ? 2 : 1), initDamage/(initTwoHanded ? 1 : 3) + 1), damage(initDamage), twoHanded(initTwoHanded) { }
        void print() const {
            cout << "Weapon:" << '\n';
            Item::print();
            cout << "Damage:     " << damage << '\n';
            cout << "Two-handed: " << (twoHanded ? "yes" : "no") << endl;
        }
        int getDamage() const {
            return damage;
        }
        bool isTwoHanded() const {
            return twoHanded;
        }
};

// price = 10*damage - 20*two_handed

//Μία πανοπλία (Armor) είναι ένα αντικείμενο το οποίο όταντο φοράει ένας ήρωας, μειώνει την ζημία που δέχεται από μία επίθεση του αντιπάλου του. 

class Armor : public Item {
    int defense;
    public:
        Armor(const char* initName, int initDefense)
        :   Item(initName, 15*initDefense, initDefense/3 + 1), defense(initDefense) { }
        void print() const {
            cout << "Armor:" << '\n';
            Item::print();
            cout << "Defense:    " << defense << endl;
        }
        int getDefense() const {
            return defense;
        }
};

//price = 15*defense

enum Stat { strengthStat, dexterityStat, agilityStat };

//Ενα φίλτρο(Potion) είναι ένα αντικείμενο το οποίο όταν το χρησιμοποιεί ένας ήρωας, αυξάνει κάποιο στατιστικό του
//κατά  κάποιο  ποσό.  Τα  φίλτρα  είναι  μίας  χρήσης,  πράγμα  που  σημαίνει  ότι  μετά  τη  χρήση  τους,δεν μπορούν να ξαναχρησιμοποιηθούν.

class Potion : public Item {
    Stat statAffected;
    int effect;
    public:
        Potion(const char* initName, Stat initStatAffected, int initEffect)
        :   Item(initName, 30*initEffect, initEffect/2 + 1), statAffected(initStatAffected), effect(initEffect) { }
        Stat getStatAffected() const {
            return statAffected;
        }
        int getEffect() const {
            return effect;
        }
        void print() const {
            cout << "Potion:" << '\n';
            Item::print();
            cout << (statAffected == strengthStat ? "Strength: " : (statAffected == dexterityStat) ? "Dexterity:" : "Agility:  ") << "  +" << effect << endl;
        }
};

//price = effect*30

//Ενα ζωντανό ον (Living) αντιπροσωπεύει μια ζωντανή οντότητα του κόσμου του παιχνιδιού.
//Εχει ένα  όνομα,  κάποιο  επίπεδο  (level)  καθώς  και  ένα  ποσό  ζωτικής  ενέργειας  (healthPower).
//Οταν η ζωτική ενέργεια  του  φτάσει  στο  μηδέν,  το  ζωντανό  ον  λιποθυμάει.

class Living {
    protected:
        std::string name;
        int level;
        int healthPower;
        int maxHealthPower;
    public:
        Living(const char* initName, int initLevel) : name(initName), level(initLevel), healthPower(50), maxHealthPower(50) { }
        virtual void print() const {
            cout << "Name:       " << name << '\n';
            cout << "Level:      " << level << '\n';
            cout << "HP:         " << healthPower << '\n';
            cout << "Max HP:     " << maxHealthPower << endl;
        }
        int getLevel() const {
            return level;
        }
        std::string getName() const {
            return name;
        }
        int getHealthPower() const {
            return healthPower;
        }
        int getMaxHealthPower() const {
            return maxHealthPower;
        }
        void recoverHealthPower(int amount) {
            healthPower += amount;
            if (healthPower > maxHealthPower) {
                healthPower = maxHealthPower;
            }
        }
        virtual void gainDamage(int damage) {
            if (damage > 0) {
                healthPower -= damage;
            }
            if (healthPower <= 0) {
                healthPower = 0;
                cout << name << " has fainted!" << endl;
            }
        }
};

//Ενα  τέρας  (Monster)  είναι  ένα  ζωντανό  ον.
//Εχει  ένα  εύρος  ζημιάς  που  μπορεί  να  προκαλέσει σε κάθε επίθεση του, ένα ποσό άμυνας το οποίο αφαιρείται από τη ζημιά που δέχεται σε μια επίθεση
//του αντιπάλου του, και μια πιθανότητα να αποφύγει κάποια επίθεση του αντιπάλου του.

class StatusEffect {
    int turns;
    int effect;
    public:
        StatusEffect(int initEffect, int initTurns) : effect(initEffect), turns(initTurns) { }
        bool passTurn() {
            turns--;
            if (turns == 0) {
                return true;
            }
            return false;
        }
        int getEffect() const {
            return effect;
        }
};

class Monster : public Living {
    int minDamage;
    int maxDamage;
    int defense;
    int agility;
    std::list<StatusEffect*> damageStatusEffects;
    std::list<StatusEffect*> defenseStatusEffects;
    std::list<StatusEffect*> agilityStatusEffects;
    public:
        Monster(const char* initName, int initLevel, int initMinDamage, int initMaxDamage, int initDefense, int initAgility)
        :   Living(initName, initLevel), minDamage(initMinDamage), maxDamage(initMaxDamage), defense(initDefense), agility(initAgility) { }
        ~Monster() {
            for (std::list<StatusEffect*>::iterator it = damageStatusEffects.begin() ; it != damageStatusEffects.end() ; it++) {
                delete *it;
            }
            for (std::list<StatusEffect*>::iterator it = defenseStatusEffects.begin() ; it != defenseStatusEffects.end() ; it++) {
                delete *it;
            }
            for (std::list<StatusEffect*>::iterator it = agilityStatusEffects.begin() ; it != agilityStatusEffects.end() ; it++) {
                delete *it;
            }
        }
        virtual void print() const {
            Living::print();
            cout << "Min Damage: " << minDamage << '\n';
            cout << "Max Damage: " << maxDamage << '\n';
            cout << "Defense:    " << defense << '\n';
            cout << "Agility:    " << agility << endl;
        }
        void attack(Living& creature) const {
            int range = maxDamage - minDamage;
            creature.gainDamage(minDamage + (rand() % (range + 1)));
        }
        void gainDamage(int damage) {
            if ((rand() % (50 + agility)) < 50) {
                Living::gainDamage(damage - defense);
            }
            else {
                cout << "Attack evaded!" << endl;
            }
        }
        void gainDamageStatusEffect(int amount, int turns) {
            minDamage += amount;
            maxDamage += amount;
            damageStatusEffects.push_back(new StatusEffect(amount, turns));
        }
        void gainDefenseStatusEffect(int amount, int turns) {
            defense += amount;
            defenseStatusEffects.push_back(new StatusEffect(amount, turns));
        }
        void gainAgilityStatusEffect(int amount, int turns) {
            agility += amount;
            agilityStatusEffects.push_back(new StatusEffect(amount, turns));
        }
        void endTurn() {
            if (getHealthPower() != 0) {
                recoverHealthPower(1);
            }
            for (std::list<StatusEffect*>::iterator it = damageStatusEffects.begin() ; it != damageStatusEffects.end() ; it++) {
                if ((*it)->passTurn()) {
                    minDamage -= (*it)->getEffect();
                    maxDamage -= (*it)->getEffect();
                    delete *it;
                    it = damageStatusEffects.erase(it);
                }
            }
            for (std::list<StatusEffect*>::iterator it = defenseStatusEffects.begin() ; it != defenseStatusEffects.end() ; it++) {
                if ((*it)->passTurn()) {
                    defense -= (*it)->getEffect();
                    delete *it;
                    it = defenseStatusEffects.erase(it);
                }
            }
            for (std::list<StatusEffect*>::iterator it = agilityStatusEffects.begin() ; it != agilityStatusEffects.end() ; it++) {
                if ((*it)->passTurn()) {
                    agility -= (*it)->getEffect();
                    delete *it;
                    it = agilityStatusEffects.erase(it);
                }
            }
        }
};

//Ενας δράκος(Dragon) είναι ένα τέρας που είναι ευνοημένο στο εύρος ζημιάς που μπορεί να προκαλέσει.

class Dragon : public Monster {
    public:
        Dragon(const char* initName, int initLevel)
        :   Monster(initName, initLevel, 3*initLevel, 6*initLevel, 2*initLevel, 2*initLevel) { }
        void print() const {
            cout << "Type:       Dragon" << endl;
            Monster::print();
        }
};

//Ενα ον με  εξωσκελετό  (Exoskeleton)  είναι  ένα  τέρας  που  είναι  ευνοημένο  στο  ποσό  άμυνας  που  διαθέτει.

class Exoskeleton : public Monster {
    public:
        Exoskeleton(const char* initName, int initLevel)
        :   Monster(initName, initLevel, 1*initLevel, 2*initLevel, 6*initLevel - 2, 2*initLevel) { }
        void print() const {
            cout << "Type:       Exoskeleton" << endl;
            Monster::print();
        }
};

//Ενα  πνεύμα  (Spirit)  είναι  ένα  τέρας  που  είναι  ευνοημένο  στο  πόσο  συχνά  αποφεύγει  επιθέσεις  του αντιπάλου του.

class Spirit : public Monster {
    public:
        Spirit(const char* initName, int initLevel)
        :   Monster(initName, initLevel, 1*initLevel, 2*initLevel, 2*initLevel, 6*initLevel) { }
        void print() const {
            cout << "Type:       Spirit" << endl;
            Monster::print();
        }
};

//Ενα  ξόρκι  (Spell)  αντιπροσωπεύει  μια  μαγική  επίθεση  που  μπορεί  να  εκτελέσει  κάποιος  ήρωας. ́Ενα ξόρκι έχει όνομα, τιμή και κάποιο ελάχιστο
//επίπεδο στο οποίο πρέπει να βρίσκεται ο ήρωας για να  το  χρησιμοποιήσει.    ́Ενα  ξόρκι  έχει  ένα  εύρος  ζημιάς  που  μπορεί  να  προκαλέσει  καθώς 
//και  ένα ποσό μαγικής ενέργειας που απαιτεί για να εκτελεστεί. Μετά την εκτέλεση, το ποσό αυτό της μαγικής ενέργειας αφαιρείται από τον ήρωα.
//Το επίπεδο της ζημιάς που προκαλεί ένα ξόρκι εξαρτάται από την τιμή της επιδεξιότητας του ήρωα και πάντα βρίσκεται στο εύρος που έχει καθοριστεί.

class Spell : public Item {
    protected:
        int minDamage;
        int maxDamage;
        int magicCost;
    public:
        Spell(const char* initName, int initMinDamage, int initMaxDamage, int initMagicCost)
        :   Item(initName, std::max(5*(initMinDamage + initMaxDamage) - initMagicCost/5, 1), std::max((initMinDamage + initMaxDamage) - initMagicCost/5, 1)),
        minDamage(initMinDamage), maxDamage(initMaxDamage), magicCost(initMagicCost) { }
        virtual void print() const {
            Item::print();
            cout << "Min damage: " << minDamage << '\n';
            cout << "Max damage: " << maxDamage << '\n';
            cout << "Magic cost: " << magicCost << endl;
        }
        int getMagicCost() const {
            return magicCost;
        }
        virtual void cast(Monster& enemy, int efficiency) const = 0;
};

//price = 10*(mindamage+maxdamage)/2
//magiccost = 2*(mindamage+maxdamage)/2

//Ενα ξόρκι πάγου(IceSpell) είναι ένα ξόρκι το οποίο, εκτός από τη ζημιά που προκαλεί, μειώνει και το εύρος ζημιάς του αντιπάλου για κάποιους γύρους.

class IceSpell : public Spell {
    public:
        IceSpell(const char* initName, int initMinDamage, int initMaxDamage, int initMagicCost)
        :   Spell(initName, initMinDamage, initMaxDamage, initMagicCost) { }
        virtual void print() const {
            cout << "Ice spell:" << endl;
            Spell::print();
        }
        void cast(Monster& enemy, int efficiency) const {
            int damage = minDamage + (maxDamage - minDamage)*((efficiency)/(efficiency + 5));
            enemy.gainDamageStatusEffect(-1*damage, 3);
        }
};

//Ενα ξόρκι φωτιάς (FireSpell) είναι ένα ξόρκι το οποίο,  εκτός απότη ζημιά που προκαλεί, μειώνει και το ποσό άμυνας του αντιπάλου για κάποιους γύρους. 

class FireSpell : public Spell {
    public:
        FireSpell(const char* initName, int initMinDamage, int initMaxDamage, int initMagicCost)
        :   Spell(initName, initMinDamage, initMaxDamage, initMagicCost) { }
        virtual void print() const {
            cout << "Fire spell:" << endl;
            Spell::print();
        }
        void cast(Monster& enemy, int efficiency) const {
            int damage = std::max(minDamage, maxDamage*((efficiency)/(efficiency + 1)));
            enemy.gainDefenseStatusEffect(-1*damage, 3);
        }
}; 

//Ενα ξόρκι ηλεκτρισμού (LightingSpell) είναι ένα ξόρκι το οποίο, εκτός από τη ζημιά που προκαλεί, μειώνει καιτην πιθανότητα να αποφύγει μια επίθεση ο
//αντίπαλος για κάποιους γύρους.

class LightingSpell : public Spell {
    public:
        LightingSpell(const char* initName, int initMinDamage, int initMaxDamage, int initMagicCost)
        :   Spell(initName, initMinDamage, initMaxDamage, initMagicCost) { }
        virtual void print() const {
            cout << "Lighting spell:" << endl;
            Spell::print();
        }
        void cast(Monster& enemy, int efficiency) const {
            int damage = std::max(minDamage, maxDamage*((efficiency)/(efficiency + 1)));
            enemy.gainAgilityStatusEffect(-1*damage, 3);
        }
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
    protected:
        int magicPower;
        int maxMagicPower;
        int strength;
        int dexterity;
        int agility;
        int money;
        int experience;
        Weapon* weapon;
        Armor* armor;
    public:
        Hero(const char* initName, int strengthInit, int dexterityInit, int agilityInit)
        :   Living(initName, 1), magicPower(100), maxMagicPower(100),  strength(strengthInit), dexterity(dexterityInit),
        agility(agilityInit), money(100), experience(0), weapon(NULL), armor(NULL) { }
        virtual void print() const {
            Living::print();
            cout << "MP:         " << magicPower << '\n';
            cout << "Max MP:     " << maxMagicPower << '\n';
            cout << "Strength:   " << strength;
            if (weapon != NULL) {
                cout << "+" << weapon->getDamage();
            }
            cout << '\n';
            cout << "Dexterity:  " << dexterity << '\n';
            cout << "Agility:    " << agility << '\n';
            cout << "Defense:    ";
            if (armor != NULL) {
                cout << armor->getDefense();
            }
            else {
                cout << 0;
            }
            cout << '\n';
            cout << "Money:      " << money << '\n';
            cout << "Experience: " << experience << endl;
        }
        void addExperience(int amount) {
            experience += amount;
            if (experience >= 100) {
                experience -= 100;
                levelUp();
            }
        }
        virtual void levelUp() = 0;
        int getMoney() const {
            return money;
        }
        void setMoney(int newMoney) {
            money = newMoney;
        }
        int getMagicPower() const {
            return magicPower;
        }
        void recoverMagicPower(int amount) {
            magicPower += amount;
            if (magicPower > maxMagicPower) {
                magicPower = maxMagicPower;
            }
        }
        void attack(Living& creature) const {
            creature.gainDamage(strength + (weapon != NULL ? weapon->getDamage()*weapon->isTwoHanded() : 0));
        }
        void gainDamage(int damage) {
            if ((rand() % (50 + agility)) < 50) {
                Living::gainDamage(damage - (armor == NULL ? 0 : armor->getDefense()));
            }
        }
        bool spendMoney (int amount) {
            if (money >= amount) {
                money -= amount;
                return true;
            }
            else {
                return false;
            }
        }
        bool use(Potion& potion) {
            if (potion.getMinLevel() > level) {
                cout << "The hero's level is too low to use this potion" << endl;
                return false;
            }
            if (potion.getStatAffected() == strengthStat) {
                strength += potion.getEffect();
            }
            else if (potion.getStatAffected() == dexterityStat) {
                dexterity += potion.getEffect();
            }
            else if (potion.getStatAffected() == agilityStat) {
                agility += potion.getEffect();
            }
            return true;
        }
        bool castSpell(const Spell& spell, Monster& enemy) {
            if (spell.getMagicCost() > magicPower) {
                cout << "Not enough magic power" << endl;
                return false;
            }
            if (spell.getMinLevel() > level) {
                cout << "Not high enough level to cast this spell" << endl;
                return false;
            }
            spell.cast(enemy, dexterity);
            magicPower -= spell.getMagicCost();
            return true;
        }
        Armor* equip(Armor* newArmor) {
            if (level >= newArmor->getMinLevel()) {
                Armor* oldArmor = armor;
                armor = newArmor;
                return oldArmor;
            }
            else {
                cout << "The hero's level is too low to equip this weapon" << endl;
                return newArmor;
            }
        }
        Weapon* equip(Weapon* newWeapon) {
            if (level >= newWeapon->getMinLevel()) {
                Weapon* oldWeapon = weapon;
                weapon = newWeapon;
                return oldWeapon;
            }
            else {
                cout << "The hero's level is too low to equip this armor" << endl;
                return newWeapon;
            }
        }
        void endTurn() {
            if (getHealthPower() != 0) {
                recoverHealthPower(1);
                recoverMagicPower(1);
            }
        }
};

//Ενας μαχητής (Warrior) είναι ένας ήρωας που είναι ευνοημένος στοντομέα  της  δύναμης  και  της  ευκινησίας.
//Αυτό  σημαίνει  ότι  οι  αρχικές  τιμές  σε  αυτά  τα  στατιστικά,θα είναι υψηλότερες από τα υπόλοιπα, καθώς και ότι όταν ο ήρωας ανεβαίνει επίπεδο,
//τα στατιστικάαυτά  θα  επηρεάζονται  περισσότερο. 

class Warrior : public Hero {
    public:
        Warrior(const char* initName) : Hero(initName, 5, 2, 5) { }
        void print() const {
            cout << "Type:       Warrior" << endl;
            Hero::print();
        }
        void levelUp() {
            strength += 3;
            dexterity++;
            agility += 3;
        }
};

// Ενας  μάγος  (Sorcerer)  είναι  ένας  ήρωας  που  είναι  ευνοημένος στον τομέα της επιδεξιότητας και της ευκινησίας.

class Sorcerer : public Hero {
    public:
        Sorcerer(const char* initName) : Hero(initName, 2, 5, 5) { }
        void print() const {
            cout << "Type:       Sorcerer" << endl;
            Hero::print();
        }
        void levelUp() {
            strength++;
            dexterity += 3;
            agility += 3;
        }
};

//Ενας ιππότης (Paladin) είναι ένας ήρωας που είναιευνοημένος στον τομέα της δύναμης και της επιδεξιότητας.

class Paladin : public Hero {
    public:
        Paladin(const char* initName) : Hero(initName, 5, 5, 2) { }
        void print() const {
            cout << "Type:       Paladin" << endl;
            Hero::print();
        }
        void levelUp() {
            strength += 3;
            dexterity += 3;
            agility++;
        }
};

enum Square { nonAccesible, market, common };

enum HeroType { warrior, sorcerer, paladin };

enum Phase { onMap, inBattle, inShop };

enum Direction { upDir, downDir, leftDir, rightDir };

class Grid {
    Square** grid;
    int width;
    int height;
    Hero** party;
    int heroNum;
    int position[2];
    Item* marketItems[60];
    vector<Weapon*> ownedWeapons;
    vector<Armor*> ownedArmors;
    vector<Potion*> ownedPotions;
    vector<Spell*> ownedSpells;
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
            grid[0][0] = common;
            party = new Hero*[heroNum];
            for (int i = 0 ; i < heroNum ; i++) {
                if (heroTypes[i] == warrior) {
                    party[i] = new Warrior(names[rand() % 98]);
                }
                else if (heroTypes[i] == sorcerer) {
                    party[i] = new Sorcerer(names[rand() % 98]);
                }
                else {
                    party[i] = new Paladin(names[rand() % 98]);
                }
            }
            for (int i = 0 ; i < 15 ; i++) {
                marketItems[i] = new Weapon(weaponNames[i], i + 1, i/10);
            }
            for (int i = 15 ; i < 30 ; i++) {
                marketItems[i] = new Armor(armorNames[i - 15], i - 14);
            }
            for (int i = 30 ; i < 35 ; i++) {
                marketItems[i] = new Potion(potionNames[i - 30], strengthStat, i - 29);
            }
            for (int i = 35 ; i < 40 ; i++) {
                marketItems[i] = new Potion(potionNames[i - 30], dexterityStat, i - 34);
            }
            for (int i = 40 ; i < 45 ; i++) {
                marketItems[i] = new Potion(potionNames[i - 30], agilityStat, i - 39);
            }
            for (int i = 45 ; i < 50 ; i++) {
                marketItems[i] = new IceSpell(spellNames[i - 45], i - 44, 2*(i - 44), (i - 43)*5);
            }
            for (int i = 50 ; i < 55 ; i++) {
                marketItems[i] = new FireSpell(spellNames[i - 45], i - 49, 2*(i - 49), (i - 48)*5);
            }
            for (int i = 55 ; i < 60 ; i++) {
                marketItems[i] = new LightingSpell(spellNames[i - 45], i - 54, 2*(i - 54), (i - 53)*5);
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
            for (int i = 0 ; i < 60 ; i++) {
                delete marketItems[i];
            }
        }
        void playGame() {
            while (true) {
                string input;
                cin >> input;
                if (!input.compare("quitGame")) {
                    break;
                }
                else if (!input.compare("move")) {
                    while (true) {
                        cin >> input;
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
                            cout << "Not a valid direction" << endl;
                        }
                    }
                }
                else if (!input.compare("displayHeroStats")) {
                    displayHeroStats();
                }
                else if (!input.compare("checkInventory")) {
                    checkInventory();
                }
                else if (!input.compare("equip")) {
                    equip();
                }
                else if (!input.compare("use")) {
                    use();
                }
                else if (!input.compare("displayMap")) {
                    displayMap();
                }
                else if (!input.compare("buy")) {
                    buy();
                }
                //*
                else if (!input.compare("up")) {
                    for (int i = 0 ; i < heroNum ; i++) {
                        party[i]->addExperience(20);
                    }
                }
                //*/
                //*
                else if (!input.compare("battle")) {
                    battle();
                }
                //*/
                else {
                    cout << "Unknown command" << endl;
                }
            }
        }
        void move(Direction direction) {
            if (direction == upDir) {
                if (position[1] + 1 >= height) {
                    cout << "Can't move out of bounds" << endl;
                    return;
                }
                if (grid[position[0]][position[1] + 1] == nonAccesible) {
                    cout << "Can't move into non-accessible square" << endl;
                    return;
                }
                position[1]++;
            }
            else if (direction == downDir) {
                if (position[1] - 1 < 0) {
                    cout << "Can't move out of bounds" << endl;
                    return;
                }
                if (grid[position[0]][position[1] - 1] == nonAccesible) {
                    cout << "Can't move into non-accessible square" << endl;
                    return;
                }
                position[1]--;
            }
            else if (direction == leftDir) {
                if (position[0] - 1 < 0) {
                    cout << "Can't move out of bounds" << endl;
                    return;
                }
                if (grid[position[0] - 1][position[1]] == nonAccesible) {
                    cout << "Can't move into non-accessible square" << endl;
                    return;
                }
                position[0]--;
            }
            else if (direction == rightDir) {
                if (position[0] + 1 >= width) {
                    cout << "Can't move out of bounds" << endl;
                    return;
                }
                if (grid[position[0] + 1][position[1]] == nonAccesible) {
                    cout << "Can't move into non-accessible square" << endl;
                    return;
                }
                position[0]++;
            }
            cout << "pos: " << position[0] << " " << position[1] << endl;
            if ((grid[position[0]][position[1]] == common) && !(rand() % 4)) {
                battle();
            }
        }
        void displayMap() const {
            for (int i = 0 ; i < width ; i++) {
                for (int j = 0 ; j < height ; j++) {
                    cout << "Square " << i << ", " << j << ":" << '\n';
                    if (grid[i][j] == nonAccesible) {
                        cout << "Non-accessible" << '\n';
                    }
                    else if (grid[i][j] == market) {
                        cout << "Market" << '\n';
                    }
                    else {
                        cout << "Common" << '\n';
                    }
                    if ((i == position[0]) && (j == position[1])) {
                        cout << "The party is here" << '\n';
                    }
                    cout << endl;
                }
            }
        }
        void displayHeroStats() const {
            for (int i = 0 ; i < heroNum ; i++) {
                cout << i + 1 << (i == 0 ? "st" : (i == 1 ? "nd" : "rd")) << " hero's stats: " << endl;
                party[i]->print();
            }
        }
        void checkInventory() const {
            cout << "Weapons in inventory:" << endl;
            for (vector<Weapon*>::iterator iter = ownedWeapons.begin() ; iter != ownedWeapons.end() ; iter++) {
                (*iter)->print();
            }
            cout << "Armors in inventory:" << endl;
            for (vector<Armor*>::iterator iter = ownedArmors.begin() ; iter != ownedArmors.end() ; iter++) {
                (*iter)->print();
            }
            cout << "Potions in inventory:" << endl;
            for (vector<Potion*>::iterator iter = ownedPotions.begin() ; iter != ownedPotions.end() ; iter++) {
                (*iter)->print();
            }
            cout << "Spells in inventory:" << endl;
            for (vector<Spell*>::iterator iter = ownedSpells.begin() ; iter != ownedSpells.end() ; iter++) {
                (*iter)->print();
            }
        }
        bool equip(Hero* hero = NULL) {
            cout << "What to equip?" << endl;
            while (true) {
                string input;
                cin >> input;
                if (!input.compare("weapon")) {
                    if (ownedWeapons.size() == 0) {
                        cout << "No weapons owned" << endl;
                        return false;
                    }
                    cout << "Which weapon to equip?" << endl;
                    int i = 0;
                    for (vector<Weapon*>::iterator iter = ownedWeapons.begin() ; iter != ownedWeapons.end() ; iter++, i++) {
                        cout << "\n(" << i + 1 << ")" << endl;
                        (*iter)->print();
                    }
                    int weaponPos;
                    while (true) {
                        cin >> input;
                        if (!input.compare("back")) {
                            return false;
                        }
                        else if ((atoi(input.c_str()) > 0) && (atoi(input.c_str()) <= ownedWeapons.size())) {
                            weaponPos = atoi(input.c_str()) - 1;
                            break;
                        }
                        else {
                            cout << "Invalid input" << endl;
                        }
                    }
                    Weapon* toEquip = ownedWeapons[weaponPos];
                    if (hero == NULL) {
                        int heroPos = 0;
                        if (heroNum > 1) {
                            do {
                                cout << "Which hero should use it? (1-" << heroNum << ")" << endl;
                                cin.clear();
                                cin.ignore(1000, '\n');
                                cin >> heroPos;
                                heroPos--;
                            }   while ((heroPos < 0) || (heroPos >= heroNum));
                        }
                        hero = party[heroPos];
                    }
                    Weapon* oldWeapon;
                    if ((oldWeapon = hero->equip(toEquip)) != toEquip) {
                        ownedWeapons.erase(ownedWeapons.begin() + weaponPos);
                        if (oldWeapon != NULL) {
                            ownedWeapons.push_back(oldWeapon);
                        }
                        return true;
                    }
                    else {
                        return false;
                    }
                }
                else if (!input.compare("armor")) {
                    if (ownedArmors.size() == 0) {
                        cout << "No armors owned" << endl;
                        return false;
                    }
                    cout << "Which armor to equip?" << endl;
                    int i = 0;
                    for (vector<Armor*>::iterator iter = ownedArmors.begin() ; iter != ownedArmors.end() ; iter++, i++) {
                        cout << "\n(" << i + 1 << ")" << endl;
                        (*iter)->print();
                    }
                    int armorPos;
                    while (true) {
                        cin >> input;
                        if (!input.compare("back")) {
                            return false;
                        }
                        else if ((atoi(input.c_str()) > 0) && (atoi(input.c_str()) <= ownedArmors.size())) {
                            armorPos = atoi(input.c_str()) - 1;
                            break;
                        }
                        else {
                            cout << "Invalid input" << endl;
                        }
                    }
                    Armor* toEquip = ownedArmors[armorPos];
                    if (hero == NULL) {
                        int heroPos = 0;
                        if (heroNum > 1) {
                            do {
                                cout << "Which hero should use it? (1-" << heroNum << ")" << endl;
                                cin.clear();
                                cin.ignore(1000, '\n');
                                cin >> heroPos;
                                heroPos--;
                            }   while ((heroPos < 0) || (heroPos >= heroNum));
                        }
                        hero = party[heroPos];
                    }
                    Armor* oldArmor;
                    if ((oldArmor = hero->equip(toEquip)) != toEquip) {
                        ownedArmors.erase(ownedArmors.begin() + armorPos);
                        if (oldArmor != NULL) {
                            ownedArmors.push_back(oldArmor);
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
                    cout << "Invalid input" << endl;
                }
            }
        }
        bool use(Hero* hero = NULL) {
            if (ownedPotions.size() == 0) {
                cout << "No potions owned" << endl;
                return false;
            }
            cout << "Which potion to use?" << endl;
            int i = 0;
            for (vector<Potion*>::iterator iter = ownedPotions.begin() ; iter != ownedPotions.end() ; iter++, i++) {
                cout << "\n(" << i + 1 << ")" << endl;
                (*iter)->print();
            }
            int potionPos;
            while (true) {
                string input;
                cin >> input;
                if (!input.compare("back")) {
                    return false;
                }
                else if ((atoi(input.c_str()) > 0) && (atoi(input.c_str()) <= ownedPotions.size())) {
                    potionPos = atoi(input.c_str()) - 1;
                    break;
                }
                else {
                    cout << "Invalid input" << endl;
                }
            }
            Potion* toUse = ownedPotions[potionPos];
            if (hero == NULL) {
                int heroPos = 0;
                if (heroNum > 1) {
                    do {
                        cout << "Which hero should use it? (1-" << heroNum << ")" << endl;
                        cin.clear();
                        cin.ignore(1000, '\n');
                        cin >> heroPos;
                        heroPos--;
                    }   while ((heroPos < 0) || (heroPos >= heroNum));
                }
                hero = party[heroPos];
            }
            if (hero->use(*toUse)) {
                ownedPotions.erase(ownedPotions.begin() + potionPos);
                return true;
            }
            else {
                return false;
            }
        }
        void buy() {
//            if (grid[position[0]][position[1]] != market) {
  //              cout << "Can't buy outiside of the market" << endl;
    //            return;
      //      }
            while (true) {
                string input;
                int offset;
                cout << "What to buy?" << endl;
                while (true) {
                    cin >> input;
                    if (!input.compare("weapon")) {
                        offset = 0;
                        break;
                    }
                    else if (!input.compare("armor")) {
                        offset = 15;
                        break;
                    }
                    else if (!input.compare("potion")) {
                        offset = 30;
                        break;
                    }
                    else if (!input.compare("spell")) {
                        offset = 45;
                        break;
                    }
                    else {
                        cout << "Invalid input" << endl;
                    }
                }
                cout << "Choose one:" << endl;
                for (int i = 0 ; i < 15 ; i++) {
                    cout << "\n(" << i + 1 << ")" << endl;
                    marketItems[i + offset]->print();
                }
                while (true) {
                    cin >> input;
                    if (!input.compare("back")) {
                        break;
                    }
                    else if ((atoi(input.c_str()) > 0) && (atoi(input.c_str()) <= 15)) {
                        Item* toBuy = marketItems[atoi(input.c_str()) - 1 + offset];
                        int totalMoney = 0, toPay = toBuy->getPrice();
                        for (int i = 0 ; i < heroNum ; i++) {
                            totalMoney += party[i]->getMoney();
                        }
                        if (totalMoney < toPay) {
                            cout << "Not enough money" << endl;
                            break;
                        }
                        for (int i = 0 ; i < heroNum ; i++) {
                            if (party[i]->spendMoney(toPay)) {
                                break;
                            }
                            else {
                                toPay -= party[i]->getMoney();
                                party[i]->spendMoney(party[i]->getMoney());
                            }
                        }
                        if (offset == 0) {
                            cout << "buying weapon" << endl;
                            ownedWeapons.push_back((Weapon*) toBuy);
                        }
                        else if (offset == 15) {
                            cout << "buying armor" << endl;
                            ownedArmors.push_back((Armor*) toBuy);
                        }
                        else if (offset == 30) {
                            cout << "buying potion" << endl;
                            ownedPotions.push_back((Potion*) toBuy);
                        }
                        else if (offset == 45) {
                            cout << "buying spell" << endl;
                            ownedSpells.push_back((Spell*) toBuy);
                        }
                        break;
                    }
                    else {
                        cout << "Invalid input" << endl;
                    }
                }
                bool done;
                cout << "Buy more? (y/n)" << endl;
                while (true) {
                    cin >> input;
                    if (!input.compare("y")) {
                        done = false;
                        break;
                    }
                    else if (!input.compare("n")) {
                        done = true;
                        break;
                    }
                    else {
                        cout << "Invalid input" << endl;
                    }
                }
                if (done) {
                    break;
                }
            }
        }
        void battle() {
            cout << "Battle!" << endl;
            int averageHeroLevel = 0;
            for (int i = 0 ; i < heroNum ; i++) {
                averageHeroLevel += party[i]->getLevel();
            }
            averageHeroLevel /= heroNum;
            int monsterNum = heroNum + (rand() % 2);
            Monster** monsters = new Monster*[monsterNum];
            for (int i = 0 ; i < monsterNum ; i++) {
                if (!(rand() % 3)) {
                    monsters[i] = new Dragon(names[rand() % 98], averageHeroLevel);
                }
                else if (!(rand() % 2)) {
                    monsters[i] = new Exoskeleton(names[rand() % 98], averageHeroLevel);
                }
                else {
                    monsters[i] = new Spirit(names[rand() % 98], averageHeroLevel);
                }
            }
            bool won = true, lost = true;
            while (true) {
                string input;
                cout << "Display stats? (y/n)" << endl;
                while (true) {
                    cin >> input;
                    if (!input.compare("y")) {
                        displayHeroStats();
                        for (int i = 0 ; i < monsterNum ; i++) {
                            cout << i + 1 << (i == 0 ? "st" : (i == 1 ? "nd" : (i == 2 ? "rd" : "th"))) << " monster's stats: " << endl;
                            monsters[i]->print();
                        }
                        break;
                    }
                    else if (!input.compare("n")) {
                        break;
                    }
                    else {
                        cout << "Invalid input" << endl;
                    }
                }
                won = true, lost = true;
                for (int i = 0 ; i < heroNum ; i++) {
                    if (party[i]->getHealthPower() != 0) {
                        lost = false;
                        while (true) {
                            cout << "What should " << party[i]->getName() << " do?" << endl;
                            cin >> input;
                            if (!input.compare("attack")) {
                                int numInput;
                                cout << "Which monster to attack?" << endl;
                                for (int j = 0 ; j < monsterNum ; j++) {
                                    cout << "(" << j + 1 << ") " << monsters[j]->getName() << ", HP: " << monsters[j]->getHealthPower() <<  endl;
                                }
                                while (true) {
                                    cin.clear();
                                    cin.ignore(1000, '\n');
                                    cin >> numInput;
                                    if ((numInput > 0) && (numInput <= monsterNum)) {
                                        break;
                                    }
                                    else {
                                        cout << "Invalid input" << endl;
                                    }
                                }
                                party[i]->attack(*monsters[numInput - 1]);
                                break;
                            }
                            else if (!input.compare("castSpell")) {
                                if (ownedSpells.size() == 0) {
                                    cout << "No spells owned" << endl;
                                    return;
                                }
                                cout << "Which spell to cast?" << endl;
                                int j = 0;
                                for (vector<Spell*>::iterator iter = ownedSpells.begin() ; iter != ownedSpells.end() ; iter++, j++) {
                                    cout << "\n(" << j + 1 << ")" << endl;
                                    (*iter)->print();
                                }
                                int spellPos;
                                while (true) {
                                    string input;
                                    cin >> input;
                                    if ((atoi(input.c_str()) > 0) && (atoi(input.c_str()) <= ownedSpells.size())) {
                                        spellPos = atoi(input.c_str()) - 1;
                                        break;
                                    }
                                    else {
                                        cout << "Invalid input" << endl;
                                    }
                                }
                                Spell* toUse = ownedSpells[spellPos];
                                int numInput;
                                cout << "Which monster to cast the spell on?" << endl;
                                for (int j = 0 ; j < monsterNum ; j++) {
                                    cout << "(" << j + 1 << ") " << monsters[j]->getName() << ", HP: " << monsters[j]->getHealthPower() <<  endl;
                                }
                                while (true) {
                                    cin.clear();
                                    cin.ignore(1000, '\n');
                                    cin >> numInput;
                                    if ((numInput > 0) && (numInput <= monsterNum)) {
                                        break;
                                    }
                                    else {
                                        cout << "Invalid input" << endl;
                                    }
                                }
                                if (party[i]->castSpell(*toUse, *monsters[numInput - 1])) {
                                    break;
                                }
                            }
                            else if (!input.compare("use")) {
                                if (use(party[i])) {
                                    break;
                                }
                            }
                            else if (!input.compare("equip")) {
                                if (equip(party[i])) {
                                    break;
                                }
                            }
                            else {
                                cout << "Unknown command" << endl;
                            }
                        }
                    }
                }
                for (int i = 0 ; i < monsterNum ; i++) {
                    if (monsters[i]->getHealthPower() != 0) {
                        won = false;
                        for (int j = 0 ; j < heroNum; j++) {
                            if (party[j]->getHealthPower() != 0) {
                                monsters[i]->attack(*party[j]);
                                break;
                            }
                        }
                    }
                }
                if (won || lost) {
                    break;
                }
                for (int i = 0 ; i < heroNum ; i++) {
                    party[i]->endTurn();
                }
                for (int i = 0 ; i < monsterNum ; i++) {
                    monsters[i]->endTurn();
                }
            }
            if (won) {
                cout << "The party has won!" << endl;
                for (int i = 0 ; i < heroNum ; i++) {
                    party[i]->setMoney(party[i]->getMoney() + party[i]->getLevel()*10 + monsterNum*20);
                    party[i]->addExperience(party[i]->getLevel()*5 + monsterNum*20);
                }
            }
            else {
                cout << "The party has lost!" << endl;
                for (int i = 0 ; i < heroNum ; i++) {
                    party[i]->setMoney(party[i]->getMoney() / 2);
                }
            }
            for (int i = 0 ; i < heroNum ; i++) {
                if (party[i]->getHealthPower() == 0) {
                    party[i]->recoverHealthPower(party[i]->getMaxHealthPower() / 2);
                }
            }
            for (int i = 0 ; i < monsterNum ; i++) {
                delete monsters[i];
            }
            delete[] monsters;
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
        cin.clear();
        cin.ignore(1000, '\n');
        cin >> heroNum;
    } while (heroNum < 1 || heroNum > 3);
    HeroType heroTypes[heroNum];
    string input;
    for (int i = 0 ; i  < heroNum ; i++) {
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
            i--;
        }
    }
    Grid grid(width, height, heroTypes, heroNum);
    grid.playGame();
}