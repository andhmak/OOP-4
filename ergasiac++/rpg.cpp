#include <iostream>
#include <string>
#include <cstdlib>
#include <ctime>
#include <vector>
#include <list>
#include "rpg.h"
#include "names.h"

// ́Ενα  αντικείμενο  (Item)  έχει  ένα  όνομα,
//   μία  τιμή  αγοράς  και  έχει  και  κάποιο  ελάχιστο  επίπεδοστο  οποίο  πρέπει  να  βρίσκεται  ο  ήρωας  για  να  το  χρησιμοποιήσει.

Item::Item(const char* initName, int initPrice, int initMinLevel) : name(initName), price(initPrice), minLevel(initMinLevel) { }
void Item::print() const {
    std::cout << "Name:       " << name << '\n';
    std::cout << "Price:      " << price << '\n';
    std::cout << "Min Level:  " << minLevel << std::endl;
}
int Item::getPrice() const {
    return price;
}
int Item::getMinLevel() const {
    return minLevel;
}

//Ενα  όπλο  (Weapon)  είναι  ένααντικείμενο το οποίο μπορεί να χρησιμοποιηθεί από τον ήρωα για να επιτεθεί σε κάποιο τέρας. Εχει ένα συγκεκριμένο ποσό 
//ζημιάς που προκαλεί στον αντίπαλο του και μπορεί να απαιτεί το ένα ή και ταδύο χέρια του ήρωα για να το χρησιμοποιεί.

Weapon::Weapon(const char* initName, int initDamage, int initTwoHanded)
:   Item(initName, 10*initDamage*(initTwoHanded ? 2 : 1), initDamage/(initTwoHanded ? 1 : 3) + 1), damage(initDamage), twoHanded(initTwoHanded) { }
void Weapon::print() const {
    std::cout << "Weapon:" << '\n';
    Item::print();
    std::cout << "Damage:     " << damage << '\n';
    std::cout << "Two-handed: " << (twoHanded ? "yes" : "no") << std::endl;
}
int Weapon::getDamage() const {
    return damage;
}
bool Weapon::isTwoHanded() const {
    return twoHanded;
}

// price = 10*damage - 20*two_handed

//Μία πανοπλία (Armor) είναι ένα αντικείμενο το οποίο όταντο φοράει ένας ήρωας, μειώνει την ζημία που δέχεται από μία επίθεση του αντιπάλου του. 

Armor::Armor(const char* initName, int initDefense)
:   Item(initName, 15*initDefense, initDefense/3 + 1), defense(initDefense) { }
void Armor::print() const {
    std::cout << "Armor:" << '\n';
    Item::print();
    std::cout << "Defense:    " << defense << std::endl;
}
int Armor::getDefense() const {
    return defense;
}

//price = 15*defense

//Ενα φίλτρο(Potion) είναι ένα αντικείμενο το οποίο όταν το χρησιμοποιεί ένας ήρωας, αυξάνει κάποιο στατιστικό του
//κατά  κάποιο  ποσό.  Τα  φίλτρα  είναι  μίας  χρήσης,  πράγμα  που  σημαίνει  ότι  μετά  τη  χρήση  τους,δεν μπορούν να ξαναχρησιμοποιηθούν.

Potion::Potion(const char* initName, int initEffect)
:   Item(initName, 30*initEffect, initEffect/2 + 1), effect(initEffect) { }
void Potion::print() const {
    std::cout << "Potion:" << '\n';
    Item::print();
}

//price = effect*30

bool StrengthPotion::useOn(Hero* hero) {
    if (hero->getLevel() < minLevel) {
        std::cout << "The hero's level is too low to use this potion" << std::endl;
        return false;
    }
    hero->addStrength(effect);
    return true;
}

void StrengthPotion::print() const {
    Potion::print();
    std::cout << "Strength:   +" << effect << std::endl;
}

bool DexterityPotion::useOn(Hero* hero) {
    if (hero->getLevel() < minLevel) {
        std::cout << "The hero's level is too low to use this potion" << std::endl;
        return false;
    }
    hero->addDexterity(effect);
    return true;
}

void DexterityPotion::print() const {
    Potion::print();
    std::cout << "Dexterity:  +" << effect << std::endl;
}

bool AgilityPotion::useOn(Hero* hero) {
    if (hero->getLevel() < minLevel) {
        std::cout << "The hero's level is too low to use this potion" << std::endl;
        return false;
    }
    hero->addAgility(effect);
    return true;
}

void AgilityPotion::print() const {
    Potion::print();
    std::cout << "Agility:    +" << effect << std::endl;
}

//Ενα  ξόρκι  (Spell)  αντιπροσωπεύει  μια  μαγική  επίθεση  που  μπορεί  να  εκτελέσει  κάποιος  ήρωας. ́Ενα ξόρκι έχει όνομα, τιμή και κάποιο ελάχιστο
//επίπεδο στο οποίο πρέπει να βρίσκεται ο ήρωας για να  το  χρησιμοποιήσει.    ́Ενα  ξόρκι  έχει  ένα  εύρος  ζημιάς  που  μπορεί  να  προκαλέσει  καθώς 
//και  ένα ποσό μαγικής ενέργειας που απαιτεί για να εκτελεστεί. Μετά την εκτέλεση, το ποσό αυτό της μαγικής ενέργειας αφαιρείται από τον ήρωα.
//Το επίπεδο της ζημιάς που προκαλεί ένα ξόρκι εξαρτάται από την τιμή της επιδεξιότητας του ήρωα και πάντα βρίσκεται στο εύρος που έχει καθοριστεί.

Spell::Spell(const char* initName, int initMinDamage, int initMaxDamage, int initMagicCost)
:   Item(initName, std::max(5*(initMinDamage + initMaxDamage) - initMagicCost/5, 1), std::max((initMinDamage + initMaxDamage) - initMagicCost/5, 1)),
minDamage(initMinDamage), maxDamage(initMaxDamage), magicCost(initMagicCost) { }
void Spell::print() const {
    Item::print();
    std::cout << "Min damage: " << minDamage << '\n';
    std::cout << "Max damage: " << maxDamage << '\n';
    std::cout << "Magic cost: " << magicCost << std::endl;
}
int Spell::getMagicCost() const {
    return magicCost;
}

//price = 10*(mindamage+maxdamage)/2
//magiccost = 2*(mindamage+maxdamage)/2

//Ενα ξόρκι πάγου(IceSpell) είναι ένα ξόρκι το οποίο, εκτός από τη ζημιά που προκαλεί, μειώνει και το εύρος ζημιάς του αντιπάλου για κάποιους γύρους.

IceSpell::IceSpell(const char* initName, int initMinDamage, int initMaxDamage, int initMagicCost)
:   Spell(initName, initMinDamage, initMaxDamage, initMagicCost) { }
void IceSpell::print() const {
    std::cout << "Ice spell:" << std::endl;
    Spell::print();
}
void IceSpell::cast(Monster& enemy, int efficiency) const {
    int damage = minDamage + (maxDamage - minDamage)*((efficiency)/(efficiency + 5));
    enemy.gainDamageStatusEffect(-1*damage, 3);
}

//Ενα ξόρκι φωτιάς (FireSpell) είναι ένα ξόρκι το οποίο,  εκτός απότη ζημιά που προκαλεί, μειώνει και το ποσό άμυνας του αντιπάλου για κάποιους γύρους. 

FireSpell::FireSpell(const char* initName, int initMinDamage, int initMaxDamage, int initMagicCost)
:   Spell(initName, initMinDamage, initMaxDamage, initMagicCost) { }
void FireSpell::print() const {
    std::cout << "Fire spell:" << std::endl;
    Spell::print();
}
void FireSpell::cast(Monster& enemy, int efficiency) const {
    int damage = std::max(minDamage, maxDamage*((efficiency)/(efficiency + 1)));
    enemy.gainDefenseStatusEffect(-1*damage, 3);
}

//Ενα ξόρκι ηλεκτρισμού (LightingSpell) είναι ένα ξόρκι το οποίο, εκτός από τη ζημιά που προκαλεί, μειώνει καιτην πιθανότητα να αποφύγει μια επίθεση ο
//αντίπαλος για κάποιους γύρους.

LightingSpell::LightingSpell(const char* initName, int initMinDamage, int initMaxDamage, int initMagicCost)
:   Spell(initName, initMinDamage, initMaxDamage, initMagicCost) { }
void LightingSpell::print() const {
    std::cout << "Lighting spell:" << std::endl;
    Spell::print();
}
void LightingSpell::cast(Monster& enemy, int efficiency) const {
    int damage = std::max(minDamage, maxDamage*((efficiency)/(efficiency + 1)));
    enemy.gainAgilityStatusEffect(-1*damage, 3);
}

//Ενα ζωντανό ον (Living) αντιπροσωπεύει μια ζωντανή οντότητα του κόσμου του παιχνιδιού.
//Εχει ένα  όνομα,  κάποιο  επίπεδο  (level)  καθώς  και  ένα  ποσό  ζωτικής  ενέργειας  (healthPower).
//Οταν η ζωτική ενέργεια  του  φτάσει  στο  μηδέν,  το  ζωντανό  ον  λιποθυμάει.

Living::Living(const char* initName, int initLevel) : name(initName), level(initLevel), healthPower(50), maxHealthPower(50) { }
void Living::print() const {
    std::cout << "Name:       " << name << '\n';
    std::cout << "Level:      " << level << '\n';
    std::cout << "HP:         " << healthPower << '\n';
    std::cout << "Max HP:     " << maxHealthPower << std::endl;
}
int Living::getLevel() const {
    return level;
}
std::string Living::getName() const {
    return name;
}
int Living::getHealthPower() const {
    return healthPower;
}
int Living::getMaxHealthPower() const {
    return maxHealthPower;
}
void Living::recoverHealthPower(int amount) {
    healthPower += amount;
    if (healthPower > maxHealthPower) {
        healthPower = maxHealthPower;
    }
}
void Living::gainDamage(int damage) {
    if (damage > 0) {
        healthPower -= damage;
    }
    if (healthPower <= 0) {
        healthPower = 0;
        std::cout << name << " has fainted!" << std::endl;
    }
}

//Ενας ήρωας (Hero) είναι έναζωντανό ον.
//Εχει ένα ποσό μαγικής ενέργειας (magicPower), καθώς και κάποια χαρακτηριστικάπου επηρεάζουν την ικανότητα του στη μάχη.
//Ενας ήρωας έχει κάποια τιμή δύναμης (strength), κάποια τιμή επιδεξιότητας (dexterity) καθώς και κάποια τιμή ευκινησίας (agility).
//Η δύναμη του ήρωα προστίθεται στο ποσό ζημιάς που προκαλεί ένα όπλο, η επιδεξιότητα του επιτρέπει να εκτελεί ταξόρκια πιο αποδοτικά και
//τέλος η ευκινησία του επιτρέπει να μπορεί με κάποια πιθανότητα να αποφύγει κάποια επίθεση του αντιπάλου του.
//Ενας ήρωας διαθέτει ένα ποσό χρημάτων (money) καθώς και ένα ποσό εμπειρίας (experience).
//Οταν ο ήρωας αποκτήσει αρκετή εμπειρία, ανεβαίνει ένα επίπεδο(levelUp).
//Σε κάθε επίπεδο, οι τιμές της δύναμης, της επιδεξιότητας και της ευκινησίας του ήρωα,αυξάνονται κατά κάποιο ποσό.

Hero::Hero(const char* initName, int strengthInit, int dexterityInit, int agilityInit)
:   Hero::Living(initName, 1), magicPower(100), maxMagicPower(100),  strength(strengthInit), dexterity(dexterityInit),
agility(agilityInit), money(50), experience(0), weapon(NULL), armor(NULL) { }
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
void Hero::addExperience(int amount) {
    Hero::experience += amount;
    if (experience >= 100) {
        experience -= 100;
        levelUp();
    }
}
int Hero::getMoney() const {
    return money;
}
void Hero::setMoney(int newMoney) {
    money = newMoney;
}
int Hero::getMagicPower() const {
    return magicPower;
}
void Hero::recoverMagicPower(int amount) {
    magicPower += amount;
    if (magicPower > maxMagicPower) {
        magicPower = maxMagicPower;
    }
}
void Hero::attack(Living& creature) const {
    creature.gainDamage(strength + (weapon != NULL ? weapon->getDamage()*weapon->isTwoHanded() : 0));
}
void Hero::gainDamage(int damage) {
    if ((rand() % (50 + agility)) < 50) {
        Living::gainDamage(damage - (armor == NULL ? 0 : armor->getDefense()));
    }
}
bool Hero::spendMoney (int amount) {
    if (money >= amount) {
        money -= amount;
        return true;
    }
    else {
        return false;
    }
}
bool Hero::use(Potion& potion) {
    return potion.useOn(this);
}
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
void Hero::endTurn() {
    if (getHealthPower() != 0) {
        recoverHealthPower(1);
        recoverMagicPower(1);
    }
}

//Ενας μαχητής (Warrior) είναι ένας ήρωας που είναι ευνοημένος στοντομέα  της  δύναμης  και  της  ευκινησίας.
//Αυτό  σημαίνει  ότι  οι  αρχικές  τιμές  σε  αυτά  τα  στατιστικά,θα είναι υψηλότερες από τα υπόλοιπα, καθώς και ότι όταν ο ήρωας ανεβαίνει επίπεδο,
//τα στατιστικάαυτά  θα  επηρεάζονται  περισσότερο. 

Warrior::Warrior(const char* initName) : Hero(initName, 5, 2, 5) { }
void Warrior::print() const {
    std::cout << "Type:       Warrior" << std::endl;
    Hero::print();
}
void Warrior::levelUp() {
    strength += 3;
    ++dexterity;
    agility += 3;
}

// Ενας  μάγος  (Sorcerer)  είναι  ένας  ήρωας  που  είναι  ευνοημένος στον τομέα της επιδεξιότητας και της ευκινησίας.

Sorcerer::Sorcerer(const char* initName) : Hero(initName, 2, 5, 5) { }
void Sorcerer::print() const {
    std::cout << "Type:       Sorcerer" << std::endl;
    Hero::print();
}
void Sorcerer::levelUp() {
    ++strength;
    dexterity += 3;
    agility += 3;
}

//Ενας ιππότης (Paladin) είναι ένας ήρωας που είναιευνοημένος στον τομέα της δύναμης και της επιδεξιότητας.

Paladin::Paladin(const char* initName) : Hero(initName, 5, 5, 2) { }
void Paladin::print() const {
    std::cout << "Type:       Paladin" << std::endl;
    Hero::print();
}
void Paladin::levelUp() {
    strength += 3;
    dexterity += 3;
    ++agility;
}

//Ενα  τέρας  (Monster)  είναι  ένα  ζωντανό  ον.
//Εχει  ένα  εύρος  ζημιάς  που  μπορεί  να  προκαλέσει σε κάθε επίθεση του, ένα ποσό άμυνας το οποίο αφαιρείται από τη ζημιά που δέχεται σε μια επίθεση
//του αντιπάλου του, και μια πιθανότητα να αποφύγει κάποια επίθεση του αντιπάλου του.

StatusEffect::StatusEffect(int initEffect, int initTurns) : effect(initEffect), turns(initTurns) { }
bool StatusEffect::passTurn() {
    --turns;
    if (turns == 0) {
        return true;
    }
    return false;
}
int StatusEffect::getEffect() const {
    return effect;
}

Monster::Monster(const char* initName, int initLevel, int initMinDamage, int initMaxDamage, int initDefense, int initAgility)
:   Living(initName, initLevel), minDamage(initMinDamage), maxDamage(initMaxDamage), defense(initDefense), agility(initAgility) { }
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
void Monster::print() const {
    Living::print();
    std::cout << "Min Damage: " << minDamage << '\n';
    std::cout << "Max Damage: " << maxDamage << '\n';
    std::cout << "Defense:    " << defense << '\n';
    std::cout << "Agility:    " << agility << std::endl;
}
void Monster::attack(Living& creature) const {
    int range = maxDamage - minDamage;
    creature.gainDamage(minDamage + (rand() % (range + 1)));
}
void Monster::gainDamage(int damage) {
    if ((rand() % (50 + agility)) < 50) {
        Living::gainDamage(damage - defense);
    }
    else {
        std::cout << "Attack evaded!" << std::endl;
    }
}
void Monster::gainDamageStatusEffect(int amount, int turns) {
    minDamage += amount;
    maxDamage += amount;
    damageStatusEffects.push_back(new StatusEffect(amount, turns));
}
void Monster::gainDefenseStatusEffect(int amount, int turns) {
    defense += amount;
    defenseStatusEffects.push_back(new StatusEffect(amount, turns));
}
void Monster::gainAgilityStatusEffect(int amount, int turns) {
    agility += amount;
    agilityStatusEffects.push_back(new StatusEffect(amount, turns));
}
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

//Ενας δράκος(Dragon) είναι ένα τέρας που είναι ευνοημένο στο εύρος ζημιάς που μπορεί να προκαλέσει.

Dragon::Dragon(const char* initName, int initLevel)
:   Monster(initName, initLevel, 3*initLevel, 6*initLevel, 2*initLevel, 2*initLevel) { }
void Dragon::print() const {
    std::cout << "Type:       Dragon" << std::endl;
    Monster::print();
}

//Ενα ον με  εξωσκελετό  (Exoskeleton)  είναι  ένα  τέρας  που  είναι  ευνοημένο  στο  ποσό  άμυνας  που  διαθέτει.

Exoskeleton::Exoskeleton(const char* initName, int initLevel)
:   Monster(initName, initLevel, 1*initLevel, 2*initLevel, 6*initLevel - 2, 2*initLevel) { }
void Exoskeleton::print() const {
    std::cout << "Type:       Exoskeleton" << std::endl;
    Monster::print();
}

//Ενα  πνεύμα  (Spirit)  είναι  ένα  τέρας  που  είναι  ευνοημένο  στο  πόσο  συχνά  αποφεύγει  επιθέσεις  του αντιπάλου του.

Spirit::Spirit(const char* initName, int initLevel)
:   Monster(initName, initLevel, 1*initLevel, 2*initLevel, 2*initLevel, 6*initLevel) { }
void Spirit::print() const {
    std::cout << "Type:       Spirit" << std::endl;
    Monster::print();
}

Grid::Grid(int initWidth, int initHeight, HeroType* heroTypes, int heroNumInit)
:   width(initWidth), height(initHeight), heroNum(heroNumInit), position{0,0} {
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
    party = new Hero*[heroNum];
    for (int i = 0 ; i < heroNum ; ++i) {
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
    for (int i = 0 ; i < 15 ; ++i) {
        marketItems[i] = new Weapon(weaponNames[i], i + 1, i/10);
    }
    for (int i = 15 ; i < 30 ; ++i) {
        marketItems[i] = new Armor(armorNames[i - 15], i - 14);
    }
    for (int i = 30 ; i < 35 ; ++i) {
        marketItems[i] = new StrengthPotion(potionNames[i - 30], i - 29);
    }
    for (int i = 35 ; i < 40 ; ++i) {
        marketItems[i] = new DexterityPotion(potionNames[i - 30], i - 34);
    }
    for (int i = 40 ; i < 45 ; ++i) {
        marketItems[i] = new AgilityPotion(potionNames[i - 30], i - 39);
    }
    for (int i = 45 ; i < 50 ; ++i) {
        marketItems[i] = new IceSpell(spellNames[i - 45], i - 44, 2*(i - 44), (i - 43)*5);
    }
    for (int i = 50 ; i < 55 ; ++i) {
        marketItems[i] = new FireSpell(spellNames[i - 45], i - 49, 2*(i - 49), (i - 48)*5);
    }
    for (int i = 55 ; i < 60 ; ++i) {
        marketItems[i] = new LightingSpell(spellNames[i - 45], i - 54, 2*(i - 54), (i - 53)*5);
    }
}
Grid::~Grid() {
    for (int i = 0 ; i < width ; ++i) {
        delete[] grid[i];
    }
    delete[] grid;
    for (int i = 0 ; i < heroNum ; ++i) {
        delete party[i];
    }
    delete[] party;
    for (int i = 0 ; i < 60 ; ++i) {
        delete marketItems[i];
    }
}
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
        /*
        else if (!input.compare("up")) {
            for (int i = 0 ; i < heroNum ; ++i) {
                party[i]->addExperience(20);
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
    std::cout << "pos: " << position[0] << " " << position[1] << std::endl;
    if ((grid[position[0]][position[1]] == common) && !(rand() % 4)) {
        battle();
    }
}
void Grid::displayMap() const {
    for (int i = 0 ; i < width ; ++i) {
        for (int j = 0 ; j < height ; ++j) {
            std::cout << "Square " << i << ", " << j << ":" << '\n';
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
void Grid::displayHeroStats() const {
    for (int i = 0 ; i < heroNum ; ++i) {
        std::cout << i + 1 << (i == 0 ? "st" : (i == 1 ? "nd" : "rd")) << " hero's stats: " << std::endl;
        party[i]->print();
    }
}
void Grid::checkInventory() const {
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
bool Grid::equip(Hero* hero) {
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
                        std::cout << "Which hero should use it? (1-" << heroNum << ")" << std::endl;
                        std::cin.clear();
                        std::cin.ignore(1000, '\n');
                        std::cin >> heroPos;
                        --heroPos;
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
                        std::cout << "Which hero should use it? (1-" << heroNum << ")" << std::endl;
                        std::cin.clear();
                        std::cin.ignore(1000, '\n');
                        std::cin >> heroPos;
                        --heroPos;
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
            std::cout << "Invalid input" << std::endl;
        }
    }
}
bool Grid::use(Hero* hero) {
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
void Grid::buy() {
    if (grid[position[0]][position[1]] != market) {
        std::cout << "Can't buy outiside of the market" << std::endl;
        return;
    }
    while (true) {
        std::string input;
        int offset;
        std::cout << "What to buy?" << std::endl;
        while (true) {
            std::cin >> input;
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
                std::cout << "Invalid input" << std::endl;
            }
        }
        std::cout << "Choose one:" << std::endl;
        for (int i = 0 ; i < 15 ; ++i) {
            std::cout << "\n(" << i + 1 << ")" << std::endl;
            marketItems[i + offset]->print();
        }
        while (true) {
            std::cin >> input;
            if (!input.compare("back")) {
                break;
            }
            else if ((atoi(input.c_str()) > 0) && (atoi(input.c_str()) <= 15)) {
                Item* toBuy = marketItems[atoi(input.c_str()) - 1 + offset];
                int totalMoney = 0, toPay = toBuy->getPrice();
                for (int i = 0 ; i < heroNum ; ++i) {
                    totalMoney += party[i]->getMoney();
                }
                if (totalMoney < toPay) {
                    std::cout << "Not enough money" << std::endl;
                    break;
                }
                for (int i = 0 ; i < heroNum ; ++i) {
                    if (party[i]->spendMoney(toPay)) {
                        break;
                    }
                    else {
                        toPay -= party[i]->getMoney();
                        party[i]->spendMoney(party[i]->getMoney());
                    }
                }
                if (offset == 0) {
                    std::cout << "buying weapon" << std::endl;
                    ownedWeapons.push_back((Weapon*) toBuy);
                }
                else if (offset == 15) {
                    std::cout << "buying armor" << std::endl;
                    ownedArmors.push_back((Armor*) toBuy);
                }
                else if (offset == 30) {
                    std::cout << "buying potion" << std::endl;
                    ownedPotions.push_back((Potion*) toBuy);
                }
                else if (offset == 45) {
                    std::cout << "buying spell" << std::endl;
                    ownedSpells.push_back((Spell*) toBuy);
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
void Grid::battle() {
    std::cout << "Battle!" << std::endl;
    int averageHeroLevel = 0;
    for (int i = 0 ; i < heroNum ; ++i) {
        averageHeroLevel += party[i]->getLevel();
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
            if (party[i]->getHealthPower() != 0) {
                lost = false;
                while (true) {
                    std::cout << "What should " << party[i]->getName() << " do?" << std::endl;
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
                        party[i]->attack(*monsters[numInput - 1]);
                        break;
                    }
                    else if (!input.compare("castSpell")) {
                        if (ownedSpells.size() == 0) {
                            std::cout << "No spells owned" << std::endl;
                            return;
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
                        Spell* toUse = ownedSpells[spellPos];
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
                        std::cout << "Unknown command" << std::endl;
                    }
                }
            }
        }
        for (int i = 0 ; i < monsterNum ; ++i) {
            if (monsters[i]->getHealthPower() != 0) {
                won = false;
                for (int j = 0 ; j < heroNum; ++j) {
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
        for (int i = 0 ; i < heroNum ; ++i) {
            party[i]->endTurn();
        }
        for (int i = 0 ; i < monsterNum ; ++i) {
            monsters[i]->endTurn();
        }
    }
    if (won) {
        std::cout << "The party has won!" << std::endl;
        for (int i = 0 ; i < heroNum ; ++i) {
            party[i]->setMoney(party[i]->getMoney() + party[i]->getLevel()*10 + monsterNum*20);
            party[i]->addExperience(party[i]->getLevel()*5 + monsterNum*20);
        }
    }
    else {
        std::cout << "The party has lost!" << std::endl;
        for (int i = 0 ; i < heroNum ; ++i) {
            party[i]->setMoney(party[i]->getMoney() / 2);
        }
    }
    for (int i = 0 ; i < heroNum ; ++i) {
        if (party[i]->getHealthPower() == 0) {
            party[i]->recoverHealthPower(party[i]->getMaxHealthPower() / 2);
        }
    }
    for (int i = 0 ; i < monsterNum ; ++i) {
        delete monsters[i];
    }
    delete[] monsters;
}