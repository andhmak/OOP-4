/* File: rpgbase.cpp */

#include <iostream>
#include <string>
#include <cstdlib>
#include <list>
#include "rpgbase.h"

/* ----- Συναρτήσεις της Item ----- */

// Constructor
Item::Item(const char* initName, int initPrice, int initMinLevel) : name(initName), price(initPrice), minLevel(initMinLevel) { }
void Item::print() const {
    std::cout << "Name:       " << name << '\n';
    std::cout << "Price:      " << price << '\n';
    std::cout << "Min Level:  " << minLevel << std::endl;
}

/* ----- Συναρτήσεις της Weapon ----- */

// Εκτυπώνει τα δεδομένα του όπλου και καλεί τον εκτυπωτή της υπερκλάσης (Item)
void Weapon::print() const {
    std::cout << "Weapon:" << '\n';
    Item::print();
    std::cout << "Damage:     " << damage << '\n';
    std::cout << "Two-handed: " << (twoHanded ? "yes" : "no") << std::endl;
}

/* ----- Συναρτήσεις της Armor ----- */

// Εκτυπώνει τα δεδομένα της πανοπλίας και καλεί τον εκτυπωτή της υπερκλάσης (Item)
void Armor::print() const {
    std::cout << "Armor:" << '\n';
    Item::print();
    std::cout << "Defense:    " << defense << std::endl;
}

/* ----- Συναρτήσεις της Potion ----- */

// Εκτυπώνει τα δεδομένα του φίλτρου και καλεί τον εκτυπωτή της υπερκλάσης (Item)
void Potion::print() const {
    std::cout << "Potion:" << '\n';
    Item::print();
}

/* ----- Συναρτήσεις της StrengthPotion ----- */

// Αυξάνεται η δύναμη του ήρωα hero κατά effect.
void StrengthPotion::useOn(Hero* hero) {
    hero->addStrength(effect);
}

// Εκτυπώνει την δύναμη που προσίδει το φίλτρο και καλεί τον εκτυπωτή της υπερκλάσης (Potion)
void StrengthPotion::print() const {
    Potion::print();
    std::cout << "Strength:   +" << effect << std::endl;
}

/* ----- Συναρτήσεις της DexterityPotion ----- */

// Αυξάνεται η επιδεξιότητα του ήρωα hero κατά effect.
void DexterityPotion::useOn(Hero* hero) {
    hero->addDexterity(effect);
}

// Εκτυπώνει την επιδεξιότητα που προσίδει το φίλτρο και καλεί τον εκτυπωτή της υπερκλάσης (Potion)
void DexterityPotion::print() const {
    Potion::print();
    std::cout << "Dexterity:  +" << effect << std::endl;
}

/* ----- Συναρτήσεις της AgilityPotion ----- */

// Αυξάνεται η ευκινησία του ήρωα hero κατά effect.
void AgilityPotion::useOn(Hero* hero) {
    hero->addAgility(effect);
}

// Εκτυπώνει την ευκινησία που προσίδει το φίλτρο και καλεί τον εκτυπωτή της υπερκλάσης (Potion)
void AgilityPotion::print() const {
    Potion::print();
    std::cout << "Agility:    +" << effect << std::endl;
}

/* ----- Συναρτήσεις της Spell ----- */

// Constructor. Δίνονται όνομα, εύρος ζημίας και μαγικό κόστος. Τιμή και ελάχιστο επίπεδο υπολογίζονται συναρτήσει των προηγούμενων.
Spell::Spell(const char* initName, int initMinDamage, int initMaxDamage, int initMagicCost)
:   Item(initName, std::max(5*(initMinDamage + initMaxDamage) - initMagicCost/5, 1), std::max((initMinDamage + initMaxDamage) - initMagicCost/5, 1)),
minDamage(initMinDamage), maxDamage(initMaxDamage), magicCost(initMagicCost) { }

// Εκτελεί το ξόρκι στο τέρας enemy με αποδοτικότητα efficiency. Όσο μεγαλύτερη
// η αποδοτικότητα τόσο μεγαλήτερη η ζημία, εντός του καθορισμένου εύρους.
void Spell::cast(Monster& enemy, int efficiency) const {
    enemy.gainDamage(minDamage + (maxDamage - minDamage)*((efficiency)/(efficiency + 5)));
}

// Εκτυπώνει τα δεδομένα του ξορκιού και καλεί τον εκτυπωτή της υπερκλάσης (Item)
void Spell::print() const {
    Item::print();
    std::cout << "Min damage: " << minDamage << '\n';
    std::cout << "Max damage: " << maxDamage << '\n';
    std::cout << "Magic cost: " << magicCost << std::endl;
}

/* ----- Συναρτήσεις της IceSpell ----- */

// Εκτελεί το ξόρκι στο τέρας enemy με αποδοτικότητα efficiency.
// Εκτός από ζημία που προκαλεί δίνει και ένα αρνητικό status effect δύναμης στο enemy διάρκειας 3 γύρων.
void IceSpell::cast(Monster& enemy, int efficiency) const {
    int damage = minDamage + (maxDamage - minDamage)*((efficiency)/(efficiency + 5));
    enemy.gainDamage(damage);
    enemy.gainDamageStatusEffect(-1*damage, 3);
}

// Εκτυπώνει τον τύπο του ξορκιού και καλεί τον εκτυπωτή της υπερκλάσης (Spell)
void IceSpell::print() const {
    std::cout << "Ice spell:" << std::endl;
    Spell::print();
}

/* ----- Συναρτήσεις της FireSpell ----- */

// Εκτελεί το ξόρκι στο τέρας enemy με αποδοτικότητα efficiency.
// Εκτός από ζημία που προκαλεί δίνει και ένα αρνητικό status effect άμυνας στο enemy διάρκειας 3 γύρων.
void FireSpell::cast(Monster& enemy, int efficiency) const {
    int damage = minDamage + (maxDamage - minDamage)*((efficiency)/(efficiency + 5));
    enemy.gainDamage(damage);
    enemy.gainDefenseStatusEffect(-1*damage, 3);
}

// Εκτυπώνει τον τύπο του ξορκιού και καλεί τον εκτυπωτή της υπερκλάσης (Spell)
void FireSpell::print() const {
    std::cout << "Fire spell:" << std::endl;
    Spell::print();
}

/* ----- Συναρτήσεις της LightingSpell ----- */

// Εκτελεί το ξόρκι στο τέρας enemy με αποδοτικότητα efficiency.
// Εκτός από ζημία που προκαλεί δίνει και ένα αρνητικό status effect ευκινησίας στο enemy διάρκειας 3 γύρων.
void LightingSpell::cast(Monster& enemy, int efficiency) const {
    int damage = minDamage + (maxDamage - minDamage)*((efficiency)/(efficiency + 5));
    enemy.gainDamage(damage);
    enemy.gainAgilityStatusEffect(-1*damage, 3);
}

// Εκτυπώνει τον τύπο του ξορκιού και καλεί τον εκτυπωτή της υπερκλάσης (Spell)
void LightingSpell::print() const {
    std::cout << "Lighting spell:" << std::endl;
    Spell::print();
}

/* ----- Συναρτήσεις της Living ----- */

// Αυξάνει την healthPower κατά amount, χωρίς να ξεπερνά την maxHealthPower
void Living::recoverHealthPower(int amount) {
    healthPower += amount;
    if (healthPower > maxHealthPower) {
        healthPower = maxHealthPower;
    }
}

// Αν damage > 0, μειώνει την healthPower κατά damage. Δεν πέφτει κάτω από το 0 και αν το φτάσει τυπώνει ένα μήνυμα που λέει πως το ον λιποθύμησε.
void Living::gainDamage(int damage) {
    if (damage > 0) {
        healthPower -= damage;
    }
    if (healthPower <= 0) {
        healthPower = 0;
        std::cout << name << " has fainted!" << std::endl;
    }
}

// Εκτυπώνει τα δεδομένα του όντος
void Living::print() const {
    std::cout << "Name:       " << name << '\n';
    std::cout << "Level:      " << level << '\n';
    std::cout << "HP:         " << healthPower << '\n';
    std::cout << "Max HP:     " << maxHealthPower << std::endl;
}

/* ----- Συναρτήσεις της Hero ----- */

// Constructor
Hero::Hero(const char* initName, int strengthInit, int dexterityInit, int agilityInit)
:   Hero::Living(initName, 3), magicPower(100), maxMagicPower(100),  strength(strengthInit), dexterity(dexterityInit),
agility(agilityInit), money(500), experience(0), weapon(NULL), armor(NULL) { }

// Αυξάνει την εμπειρία κατά amount, και ανά 100 μονάδες την μηδενίζει και αυξάνει κατά ένα επίπεδο τον ήρωα
void Hero::gainExperience(int amount) {
    Hero::experience += amount;
    if (experience >= 100) {
        levelUp(experience/100);
        experience -= 100*(experience/100);
    }
}

// Αυξάνει την MP κατά amount, χωρίς να ξεπερνά την maxMP
void Hero::recoverMagicPower(int amount) {
    magicPower += amount;
    if (magicPower > maxMagicPower) {
        magicPower = maxMagicPower;
    }
}

// Λαμβάνει υπόψιν την πανοπλία και την ευκινησία, και καλεί την gainDamage της Living περνόντας την τροποποιημένη damage
void Hero::gainDamage(int damage) {
    if ((rand() % (50 + agility)) < 50) {
        Living::gainDamage(damage - (armor == NULL ? 0 : armor->getDefense()));
    }
    else {
        std::cout << "Attack evaded!" << std::endl;
    }
}

// Αν money >= amount, αφαιρείται το amount, και επιστρέφεται true. Αλλιώς false.
bool Hero::spendMoney (int amount) {
    if (money >= amount) {
        money -= amount;
        return true;
    }
    else {
        return false;
    }
}

// Αν έχει αρκετά ψηλό επίπεδο χρησιμοποιεί το potion. Επιστρέφει το αν χρησιμοποιήθηκε.
bool Hero::use(Potion& potion) {
    if (getLevel() < potion.getMinLevel()) {
        std::cout << "The hero's level is too low to use this potion" << std::endl;
        return false;
    }
    potion.useOn(this);
    return true;
}

// Αν έχει αρκετά ψηλό επίπεδο και αρκετή MP εκτελεί το spell στο enemy με αποδοτικότητα dexterity. Επιστρέφει το αν εκτελέστηκε.
bool Hero::castSpell(const Spell& spell, Monster& enemy) {
    if (spell.getMagicCost() > magicPower) {
        std::cout << "Not enough magic power" << std::endl;
        return false;
    }
    if (spell.getMinLevel() > level) {
        std::cout << "Not high enough level to cast this spell" << std::endl;
        return false;
    }
    spell.cast(enemy, dexterity);
    magicPower -= spell.getMagicCost();
    return true;
}

// Αν έχει αρκετά ψηλό επίπεδο παίρνει το newWeapon και επιστρέφει το παλιό. Αλλιώς επιστρέφει το καινούργιο.
Weapon* Hero::equip(Weapon* newWeapon) {
    if (level >= newWeapon->getMinLevel()) {
        Weapon* oldWeapon = weapon;
        weapon = newWeapon;
        return oldWeapon;
    }
    else {
        std::cout << "The hero's level is too low to equip this armor" << std::endl;
        return newWeapon;
    }
}

// Αν έχει αρκετά ψηλό επίπεδο βάζει την newArmor και επιστρέφει την παλιά. Αλλιώς επιστρέφει την καινούργια.
Armor* Hero::equip(Armor* newArmor) {
    if (level >= newArmor->getMinLevel()) {
        Armor* oldArmor = armor;
        armor = newArmor;
        return oldArmor;
    }
    else {
        std::cout << "The hero's level is too low to equip this weapon" << std::endl;
        return newArmor;
    }
}

// Αν HP != 0, ανακτά (recover) 1 HP και 1 MP.
void Hero::endTurn() {
    if (getHealthPower() != 0) {
        recoverHealthPower(1);
        recoverMagicPower(1);
    }
}

// Καλεί τον εκτυπωτή της υπερκλάσης (Living) και εκτυπώνει τα δεδομένα του ήρωα
void Hero::print() const {
    Living::print();
    std::cout << "MP:         " << magicPower << '\n';
    std::cout << "Max MP:     " << maxMagicPower << '\n';
    std::cout << "Strength:   " << strength;
    if (weapon != NULL) {
        std::cout << "+" << weapon->getDamage();
    }
    std::cout << '\n';
    std::cout << "Dexterity:  " << dexterity << '\n';
    std::cout << "Agility:    " << agility << '\n';
    std::cout << "Defense:    ";
    if (armor != NULL) {
        std::cout << armor->getDefense();
    }
    else {
        std::cout << 0;
    }
    std::cout << '\n';
    std::cout << "Money:      " << money << '\n';
    std::cout << "Experience: " << experience << '\n' << std::endl;
}

/* ----- Συναρτήσεις της Warrior ----- */

// Καλεί την levelUp της υπερκλάσης (Hero) και αυξάνει τις ικανότητες του μαχητή, κυρίως την δύναμη και την ευκινησία
void Warrior::levelUp(int times) {
    Hero::levelUp(times);
    strength += 3*times;
    dexterity += times;
    agility += 3*times;
}

// Εκτυπώνει τον τύπο του ήρωα και καλεί τον εκτυπωτή της υπερκλάσης (Hero)
void Warrior::print() const {
    std::cout << "Type:       Warrior" << std::endl;
    Hero::print();
}

/* ----- Συναρτήσεις της Sorcerer ----- */

// Καλεί την levelUp της υπερκλάσης (Hero) και αυξάνει τις ικανότητες του μάγου, κυρίως την επιδεξιότητα και την ευκινησία
void Sorcerer::levelUp(int times) {
    Hero::levelUp(times);
    strength += times;
    dexterity += 3*times;
    agility += 3*times;
}

// Εκτυπώνει τον τύπο του ήρωα και καλεί τον εκτυπωτή της υπερκλάσης (Hero)
void Sorcerer::print() const {
    std::cout << "Type:       Sorcerer" << std::endl;
    Hero::print();
}

/* ----- Συναρτήσεις της Paladin ----- */

// Καλεί την levelUp της υπερκλάσης (Hero) και αυξάνει τις ικανότητες του ιππότη, κυρίως την δύναμη και την επιδεξιότητα
void Paladin::levelUp(int times) {
    Hero::levelUp(times);
    strength += 3*times;
    dexterity += 3*times;
    agility += times;
}

// Εκτυπώνει τον τύπο του ήρωα και καλεί τον εκτυπωτή της υπερκλάσης (Hero)
void Paladin::print() const {
    std::cout << "Type:       Paladin" << std::endl;
    Hero::print();
}

/* ----- Συναρτήσεις της Monster ----- */

// Destructor
Monster::~Monster() {
    for (std::list<StatusEffect*>::iterator it = damageStatusEffects.begin() ; it != damageStatusEffects.end() ; ++it) {
        delete *it;
    }
    for (std::list<StatusEffect*>::iterator it = defenseStatusEffects.begin() ; it != defenseStatusEffects.end() ; ++it) {
        delete *it;
    }
    for (std::list<StatusEffect*>::iterator it = agilityStatusEffects.begin() ; it != agilityStatusEffects.end() ; ++it) {
        delete *it;
    }
}

// Προκαλεί στο creature ζημία τυχαία εντός του εύρους ζημιάς του τέρατος
void Monster::attack(Living& creature) const {
    creature.gainDamage(minDamage + (rand() % (maxDamage - minDamage + 1)));
}

// Λαμβάνει υπόψιν την άμυνα και την ευκινησία, και καλεί την gainDamage της Living περνόντας την τροποποιημένη damage
void Monster::gainDamage(int damage) {
    if ((rand() % (50 + agility)) < 50) {
        Living::gainDamage(damage - defense);
    }
    else {
        std::cout << "Attack evaded!" << std::endl;
    }
}

// Προσθέτει στο τέρας ένα status effect ζημίας ποσού amount και διάρκειας turns
void Monster::gainDamageStatusEffect(int amount, int turns) {
    minDamage += amount;
    maxDamage += amount;
    damageStatusEffects.push_back(new StatusEffect(amount, turns));
}

// Προσθέτει στο τέρας ένα status effect άμυνας ποσού amount και διάρκειας turns
void Monster::gainDefenseStatusEffect(int amount, int turns) {
    defense += amount;
    defenseStatusEffects.push_back(new StatusEffect(amount, turns));
}

// Προσθέτει στο τέρας ένα status effect ευκινησίας ποσού amount και διάρκειας turns
void Monster::gainAgilityStatusEffect(int amount, int turns) {
    agility += amount;
    agilityStatusEffects.push_back(new StatusEffect(amount, turns));
}

// Αν HP != 0, ανακτά (recover) 1 HP και περνάει ένας γύρος για κάθε status effect.
void Monster::endTurn() {
    // ανάκτηση HP
    if (getHealthPower() != 0) {
        recoverHealthPower(1);
    }

    // για τα status effects δύναμης
    for (std::list<StatusEffect*>::iterator it = damageStatusEffects.begin() ; it != damageStatusEffects.end() ; ++it) {
        // αν τελειώσουν οι γύροι
        if ((*it)->passTurn()) {
            minDamage -= (*it)->getEffect();    // αναιρείται
            maxDamage -= (*it)->getEffect();    // η μεταβολή
            delete *it;                         // αφαιρείται το
            it = damageStatusEffects.erase(it); // status effect
        }
    }

    // για τα status effects άμυνας
    for (std::list<StatusEffect*>::iterator it = defenseStatusEffects.begin() ; it != defenseStatusEffects.end() ; ++it) {
        // αν τελειώσουν οι γύροι
        if ((*it)->passTurn()) {
            defense -= (*it)->getEffect();          // αναιρείται  η μεταβολή
            delete *it;                             // αφαιρείται το
            it = defenseStatusEffects.erase(it);    // status effect
        }
    }

    // για τα status effects ευκινησίας
    for (std::list<StatusEffect*>::iterator it = agilityStatusEffects.begin() ; it != agilityStatusEffects.end() ; ++it) {
        // αν τελειώσουν οι γύροι
        if ((*it)->passTurn()) {
            agility -= (*it)->getEffect();          // αναιρείται  η μεταβολή
            delete *it;                             // αφαιρείται το
            it = agilityStatusEffects.erase(it);    // status effect
        }
    }
}

// Καλεί τον εκτυπωτή της υπερκλάσης (Living) και εκτυπώνει τα δεδομένα του τέρατος
void Monster::print() const {
    Living::print();
    std::cout << "Min Damage: " << minDamage << '\n';
    std::cout << "Max Damage: " << maxDamage << '\n';
    std::cout << "Defense:    " << defense << '\n';
    std::cout << "Agility:    " << agility << std::endl;
}

/* ----- Συναρτήσεις της Dragon ----- */

// Εκτυπώνει τον τύπο του τέρατος και καλεί τον εκτυπωτή της υπερκλάσης (Monster)
void Dragon::print() const {
    std::cout << "Type:       Dragon" << std::endl;
    Monster::print();
}

/* ----- Συναρτήσεις της Exoskeleton ----- */

// Εκτυπώνει τον τύπο του τέρατος και καλεί τον εκτυπωτή της υπερκλάσης (Monster)
void Exoskeleton::print() const {
    std::cout << "Type:       Exoskeleton" << std::endl;
    Monster::print();
}

/* ----- Συναρτήσεις της Spirit ----- */

// Εκτυπώνει τον τύπο του τέρατος και καλεί τον εκτυπωτή της υπερκλάσης (Monster)
void Spirit::print() const {
    std::cout << "Type:       Spirit" << std::endl;
    Monster::print();
}