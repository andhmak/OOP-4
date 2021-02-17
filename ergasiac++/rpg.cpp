#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <list>
#include "rpg.h"
#include "names.h"

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
:   Hero::Living(initName, 1), magicPower(100), maxMagicPower(100),  strength(strengthInit), dexterity(dexterityInit),
agility(agilityInit), money(50), experience(0), weapon(NULL), armor(NULL) { }

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
    std::cout << "Experience: " << experience << std::endl;
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
    if (getHealthPower() != 0) {
        recoverHealthPower(1);
    }
    for (std::list<StatusEffect*>::iterator it = damageStatusEffects.begin() ; it != damageStatusEffects.end() ; ++it) {
        if ((*it)->passTurn()) {
            minDamage -= (*it)->getEffect();
            maxDamage -= (*it)->getEffect();
            delete *it;
            it = damageStatusEffects.erase(it);
        }
    }
    for (std::list<StatusEffect*>::iterator it = defenseStatusEffects.begin() ; it != defenseStatusEffects.end() ; ++it) {
        if ((*it)->passTurn()) {
            defense -= (*it)->getEffect();
            delete *it;
            it = defenseStatusEffects.erase(it);
        }
    }
    for (std::list<StatusEffect*>::iterator it = agilityStatusEffects.begin() ; it != agilityStatusEffects.end() ; ++it) {
        if ((*it)->passTurn()) {
            agility -= (*it)->getEffect();
            delete *it;
            it = agilityStatusEffects.erase(it);
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

/* ----- Συναρτήσεις της Party ----- */

// Constructor
Party::Party(HeroType* heroTypes, int heroNumInit) : heroNum(heroNumInit), heroes(new Hero*[heroNumInit]) {
    for (int i = 0 ; i < heroNum ; ++i) {
        if (heroTypes[i] == warrior) {
            heroes[i] = new Warrior(names[rand() % 98]);
        }
        else if (heroTypes[i] == sorcerer) {
            heroes[i] = new Sorcerer(names[rand() % 98]);
        }
        else {
            heroes[i] = new Paladin(names[rand() % 98]);
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
// Επιστρέφει true αν έγινε επιτυχώς η αλλαγή, αλλιώς false.
bool Party::equip(Hero* hero) {
    std::cout << "What to equip?" << std::endl;
    while (true) {
        std::string input;
        std::cin >> input;
        if (!input.compare("weapon")) {
            if (ownedWeapons.size() == 0) {
                std::cout << "No weapons owned" << std::endl;
                return false;
            }
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
            if (hero == NULL) {
                int heroPos = 0;
                if (heroNum > 1) {
                    do {
                        std::cout << "Which hero should equip it? (1-" << heroNum << ")" << std::endl;
                        std::cin.clear();
                        std::cin.ignore(1000, '\n');
                        std::cin >> heroPos;
                        --heroPos;
                    }   while ((heroPos < 0) || (heroPos >= heroNum));
                }
                hero = heroes[heroPos];
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
                std::cout << "No armors owned" << std::endl;
                return false;
            }
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
            if (hero == NULL) {
                int heroPos = 0;
                if (heroNum > 1) {
                    do {
                        std::cout << "Which hero should equip it? (1-" << heroNum << ")" << std::endl;
                        std::cin.clear();
                        std::cin.ignore(1000, '\n');
                        std::cin >> heroPos;
                        --heroPos;
                    }   while ((heroPos < 0) || (heroPos >= heroNum));
                }
                hero = heroes[heroPos];
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
    int averageHeroLevel = 0;
    for (int i = 0 ; i < heroNum ; ++i) {
        averageHeroLevel += heroes[i]->getLevel();
    }
    averageHeroLevel /= heroNum;
    int monsterNum = heroNum + (rand() % 2);
    Monster** monsters = new Monster*[monsterNum];
    for (int i = 0 ; i < monsterNum ; ++i) {
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
    bool won, lost;
    while (true) {
        std::string input;
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
        for (int i = 0 ; i < heroNum ; ++i) {
            if (heroes[i]->getHealthPower() != 0) {
                lost = false;
                while (true) {
                    std::cout << "What should " << heroes[i]->getName() << " do?" << std::endl;
                    std::cin >> input;
                    if (!input.compare("attack")) {
                        int numInput;
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
                        heroes[i]->attack(*monsters[numInput - 1]);
                        break;
                    }
                    else if (!input.compare("castSpell")) {
                        if (ownedSpells.size() == 0) {
                            std::cout << "No spells owned" << std::endl;
                            continue;
                        }
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
                        if (heroes[i]->castSpell(*toCast, *monsters[numInput - 1])) {
                            break;
                        }
                    }
                    else if (!input.compare("use")) {
                        if (use(heroes[i])) {
                            break;
                        }
                    }
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
        if (won || lost) {
            break;
        }
        for (int i = 0 ; i < heroNum ; ++i) {
            heroes[i]->endTurn();
        }
        for (int i = 0 ; i < monsterNum ; ++i) {
            monsters[i]->endTurn();
        }
    }
    if (won) {
        std::cout << "The party has won!" << std::endl;
        for (int i = 0 ; i < heroNum ; ++i) {
            heroes[i]->setMoney(heroes[i]->getMoney() + heroes[i]->getLevel()*10 + monsterNum*20);
            heroes[i]->gainExperience(heroes[i]->getLevel()*5 + monsterNum*20);
        }
    }
    else {
        std::cout << "The party has lost!" << std::endl;
        for (int i = 0 ; i < heroNum ; ++i) {
            heroes[i]->setMoney(heroes[i]->getMoney() / 2);
        }
    }
    for (int i = 0 ; i < heroNum ; ++i) {
        if (heroes[i]->getHealthPower() == 0) {
            heroes[i]->recoverHealthPower(heroes[i]->getMaxHealthPower() / 2);
        }
    }
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
            std::cin >> input;
            if (!input.compare("weapon")) {
                if (ownedWeapons.size() == 0) {
                    std::cout << "No weapons owned" << std::endl;
                    return;
                }
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
                heroes[0]->spendMoney(-1*(ownedWeapons[weaponPos]->getPrice()/2));
                ownedWeapons.erase(ownedWeapons.begin() + weaponPos);
                break;
            }
            else if (!input.compare("armor")) {
                if (ownedArmors.size() == 0) {
                    std::cout << "No armors owned" << std::endl;
                    return;
                }
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
                heroes[0]->spendMoney(-1*(ownedArmors[armorPos]->getPrice()/2));
                ownedArmors.erase(ownedArmors.begin() + armorPos);
                break;
            }
            else if (!input.compare("potion")) {
                if (ownedPotions.size() == 0) {
                    std::cout << "No potions owned" << std::endl;
                    return;
                }
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
                heroes[0]->spendMoney(-1*(ownedPotions[potionPos]->getPrice()/2));
                ownedPotions.erase(ownedPotions.begin() + potionPos);
                break;
            }
            else if (!input.compare("spell")) {
                if (ownedSpells.size() == 0) {
                    std::cout << "No spells owned" << std::endl;
                    return;
                }
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
                heroes[0]->spendMoney(-1*(ownedSpells[spellPos]->getPrice()/2));
                ownedSpells.erase(ownedSpells.begin() + spellPos);
                break;
            }
            else {
                std::cout << "Invalid input" << std::endl;
            }
        }
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
    int potionOffset = weaponAmount + armorAmount;
    int spellOffset = potionOffset + potionAmount;
    int itemAmount = spellOffset + spellAmount;
    stock = new Item*[itemAmount];
    for (int i = 0 ; i < weaponAmount ; ++i) {
        stock[i] = new Weapon(weaponNames[i], i + 1, i/(2*weaponAmount/3));
    }
    for (int i = weaponAmount ; i < potionOffset ; ++i) {
        stock[i] = new Armor(armorNames[i - weaponAmount], i - weaponAmount + 1);
    }
    for (int i = potionOffset ; i < potionOffset + potionAmount/3 ; ++i) {
        stock[i] = new StrengthPotion(potionNames[i - potionOffset], i - potionOffset + 1);
    }
    for (int i = potionOffset + potionAmount/3 ; i < potionOffset + (2*potionAmount)/3 ; ++i) {
        stock[i] = new DexterityPotion(potionNames[i - potionOffset], i - (potionOffset + potionAmount/3) + 1);
    }
    for (int i = potionOffset + (2*potionNumInit)/3 ; i < spellOffset ; ++i) {
        stock[i] = new AgilityPotion(potionNames[i - potionOffset], i - (potionOffset + (2*potionNumInit)/3) + 1);
    }
    for (int i = spellOffset ; i < spellOffset + spellAmount/3 ; ++i) {
        stock[i] = new IceSpell(spellNames[i - spellOffset], i - spellOffset + 1, 2*(i - spellOffset + 1), (i - spellOffset + 2)*5);
    }
    for (int i = spellOffset + spellAmount/3 ; i < spellOffset + (2*spellAmount)/3 ; ++i) {
        stock[i] = new FireSpell(spellNames[i - spellOffset],
                                i - (spellOffset + spellAmount/3) + 1,
                                2*(i - (spellOffset + spellAmount/3) + 1),
                                (i - (spellOffset + spellAmount/3) + 2)*5);
    }
    for (int i = spellOffset + (2*spellAmount)/3 ; i < spellOffset + spellAmount ; ++i) {
        stock[i] = new LightingSpell(spellNames[i - spellOffset],
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
                    party.buy((Weapon*) stock[atoi(input.c_str()) - 1 + offset]);
                }
                else if (type == 1) {
                    party.buy((Armor*) stock[atoi(input.c_str()) - 1 + offset]);
                }
                else if (type == 2) {
                    party.buy((Potion*) stock[atoi(input.c_str()) - 1 + offset]);
                }
                else if (type == 3) {
                    party.buy((Spell*) stock[atoi(input.c_str()) - 1 + offset]);
                }
                break;
            }
            else {
                std::cout << "Invalid input" << std::endl;
            }
        }
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
    grid = new Square*[width];
    for (int i = 0 ; i < width ; ++i) {
        grid[i] = new Square[height];
    }
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
    while (true) {
        std::string input;
        std::cin >> input;
        if (!input.compare("quitGame")) {
            break;
        }
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
        else if (!input.compare("displayHeroStats")) {
            party.displayHeroStats();
        }
        else if (!input.compare("checkInventory")) {
            party.checkInventory();
        }
        else if (!input.compare("equip")) {
            party.equip();
        }
        else if (!input.compare("use")) {
            party.use();
        }
        else if (!input.compare("displayMap")) {
            displayMap();
        }
        else if (!input.compare("buy")) {
            if (grid[position[0]][position[1]] != market) {
                std::cout << "Can't buy outiside of the market" << std::endl;
                continue;
            }
            gameMarket.buy(party);
        }
        else if (!input.compare("sell")) {
            if (grid[position[0]][position[1]] != market) {
                std::cout << "Can't sell outiside of the market" << std::endl;
                continue;
            }
            gameMarket.sell(party);
        }
        /*
        else if (!input.compare("up")) {
            for (int i = 0 ; i < heroNum ; ++i) {
                heroes[i]->gainExperience(210);
            }
        }
        */
        /*
        else if (!input.compare("battle")) {
            battle();
        }
        */
        else {
            std::cout << "Unknown command" << std::endl;
        }
    }
}

// Κινεί την ομάδα προς την κατεύθυνση direction.
// Αν πάει σε common τετράγωνο υπάρχει μια πιθανότητα να ξεκινήσει μάχη της ομάδας (battle) με τέρατα.
void Grid::move(Direction direction) {
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