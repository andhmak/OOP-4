//Να υλοποιηθεί σε C++ η προσομοίωση ενός παιχνιδιού ρόλων (role playing game). Το παιχνίδι θα έχει  αντικείμενα,  ξόρκια,  ήρωες  και  τέρατα.
//Οι  ήρωες  και  τα  τέρατα  ζουν  σε  έναν  κόσμο  που αναπαρίσταται από ένα πλέγμα.  Οι ήρωες μπορούν να εμπλέκονται σε μάχες με τα τέρατα, όπου και
//χρησιμοποιούν αντικείμενα και ξόρκια για να νικήσουν τα τέρατα, ή μπορούν να αγοράζουν αντικείμεναγια να τους βοηθήσουν στην περιπέτεια τους.
//Κάθε φορά που οι ήρωες νικούν κάποια τέρατα μαζεύουν κάποια  χρήματα  και  κερδίζουν  εμπειρία.
//Οταν  αποκτήσουν  αρκετή  εμπειρία,  οι  ήρωες “ανεβαίνουν” ένα επίπεδο, πράγμα που σημαίνει ότι γίνονται πιο δυνατοί στις επιμέρους ικανότητες τους.
#include <iostream>
#include <string>
#include <vector>
#include <list>

// ́Ενα  αντικείμενο  (Item)  έχει  ένα  όνομα,
//   μία  τιμή  αγοράς  και  έχει  και  κάποιο  ελάχιστο  επίπεδοστο  οποίο  πρέπει  να  βρίσκεται  ο  ήρωας  για  να  το  χρησιμοποιήσει.z

class Item {
    protected:
        std::string name;
        int price;
        int minLevel;
    public:
        Item(const char* initName, int initPrice, int initMinLevel);
        virtual void print() const;
        int getPrice() const;
        int getMinLevel() const;
};

//Ενα  όπλο  (Weapon)  είναι  ένααντικείμενο το οποίο μπορεί να χρησιμοποιηθεί από τον ήρωα για να επιτεθεί σε κάποιο τέρας. Εχει ένα συγκεκριμένο ποσό 
//ζημιάς που προκαλεί στον αντίπαλο του και μπορεί να απαιτεί το ένα ή και ταδύο χέρια του ήρωα για να το χρησιμοποιεί.

class Weapon : public Item {
    int damage;
    bool twoHanded;
    public:
        Weapon(const char* initName, int initDamage, int initTwoHanded);
        void print() const;
        int getDamage() const;
        bool isTwoHanded() const;
};

// price = 10*damage - 20*two_handed

//Μία πανοπλία (Armor) είναι ένα αντικείμενο το οποίο όταντο φοράει ένας ήρωας, μειώνει την ζημία που δέχεται από μία επίθεση του αντιπάλου του. 

class Armor : public Item {
    int defense;
    public:
        Armor(const char* initName, int initDefense);
        void print() const;
        int getDefense() const;
};

//price = 15*defense

class Hero;

//Ενα φίλτρο(Potion) είναι ένα αντικείμενο το οποίο όταν το χρησιμοποιεί ένας ήρωας, αυξάνει κάποιο στατιστικό του
//κατά  κάποιο  ποσό.  Τα  φίλτρα  είναι  μίας  χρήσης,  πράγμα  που  σημαίνει  ότι  μετά  τη  χρήση  τους,δεν μπορούν να ξαναχρησιμοποιηθούν.

class Potion : public Item {
    protected:
        int effect;
    public:
        Potion(const char* initName, int initEffect);
        virtual bool useOn(Hero* hero) = 0;
        virtual void print() const;
};

//price = effect*30

class StrengthPotion : public Potion {
    public:
        StrengthPotion(const char* initName, int initEffect) : Potion(initName, initEffect) { }
        bool useOn(Hero* hero);
        void print() const;
};

class DexterityPotion : public Potion {
    public:
        DexterityPotion(const char* initName, int initEffect) : Potion(initName, initEffect) { }
        bool useOn(Hero* hero);
        void print() const;
};

class AgilityPotion : public Potion {
    public:
        AgilityPotion(const char* initName, int initEffect) : Potion(initName, initEffect) { }
        bool useOn(Hero* hero);
        void print() const;
};

//Ενα  ξόρκι  (Spell)  αντιπροσωπεύει  μια  μαγική  επίθεση  που  μπορεί  να  εκτελέσει  κάποιος  ήρωας. ́Ενα ξόρκι έχει όνομα, τιμή και κάποιο ελάχιστο
//επίπεδο στο οποίο πρέπει να βρίσκεται ο ήρωας για να  το  χρησιμοποιήσει.    ́Ενα  ξόρκι  έχει  ένα  εύρος  ζημιάς  που  μπορεί  να  προκαλέσει  καθώς 
//και  ένα ποσό μαγικής ενέργειας που απαιτεί για να εκτελεστεί. Μετά την εκτέλεση, το ποσό αυτό της μαγικής ενέργειας αφαιρείται από τον ήρωα.
//Το επίπεδο της ζημιάς που προκαλεί ένα ξόρκι εξαρτάται από την τιμή της επιδεξιότητας του ήρωα και πάντα βρίσκεται στο εύρος που έχει καθοριστεί.

class Monster;

class Spell : public Item {
    protected:
        int minDamage;
        int maxDamage;
        int magicCost;
    public:
        Spell(const char* initName, int initMinDamage, int initMaxDamage, int initMagicCost);
        virtual void print() const;
        int getMagicCost() const;
        virtual void cast(Monster& enemy, int efficiency) const = 0;
};

//price = 10*(mindamage+maxdamage)/2
//magiccost = 2*(mindamage+maxdamage)/2

//Ενα ξόρκι πάγου(IceSpell) είναι ένα ξόρκι το οποίο, εκτός από τη ζημιά που προκαλεί, μειώνει και το εύρος ζημιάς του αντιπάλου για κάποιους γύρους.

class IceSpell : public Spell {
    public:
        IceSpell(const char* initName, int initMinDamage, int initMaxDamage, int initMagicCost);
        virtual void print() const;
        void cast(Monster& enemy, int efficiency) const;
};

//Ενα ξόρκι φωτιάς (FireSpell) είναι ένα ξόρκι το οποίο,  εκτός απότη ζημιά που προκαλεί, μειώνει και το ποσό άμυνας του αντιπάλου για κάποιους γύρους. 

class FireSpell : public Spell {
    public:
        FireSpell(const char* initName, int initMinDamage, int initMaxDamage, int initMagicCost);
        virtual void print() const;
        void cast(Monster& enemy, int efficiency) const;
}; 

//Ενα ξόρκι ηλεκτρισμού (LightingSpell) είναι ένα ξόρκι το οποίο, εκτός από τη ζημιά που προκαλεί, μειώνει καιτην πιθανότητα να αποφύγει μια επίθεση ο
//αντίπαλος για κάποιους γύρους.

class LightingSpell : public Spell {
    public:
        LightingSpell(const char* initName, int initMinDamage, int initMaxDamage, int initMagicCost);
        virtual void print() const;
        void cast(Monster& enemy, int efficiency) const;
};

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
        Living(const char* initName, int initLevel);
        void print() const;
        int getLevel() const;
        std::string getName() const;
        int getHealthPower() const;
        int getMaxHealthPower() const;
        void recoverHealthPower(int amount);
        virtual void gainDamage(int damage);
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
        Hero(const char* initName, int strengthInit, int dexterityInit, int agilityInit);
        virtual void print() const;
        void addExperience(int amount);
        virtual void levelUp() = 0;
        void addStrength(int amount) { strength += amount; }
        void addDexterity(int amount) { dexterity += amount; }
        void addAgility(int amount) { agility += amount; }
        int getMoney() const;
        void setMoney(int newMoney);
        int getMagicPower() const;
        void recoverMagicPower(int amount);
        void attack(Living& creature) const;
        void gainDamage(int damage);
        bool spendMoney (int amount);
        bool use(Potion& potion);
        bool castSpell(const Spell& spell, Monster& enemy);
        Armor* equip(Armor* newArmor);
        Weapon* equip(Weapon* newWeapon);
        void endTurn();
};

//Ενας μαχητής (Warrior) είναι ένας ήρωας που είναι ευνοημένος στοντομέα  της  δύναμης  και  της  ευκινησίας.
//Αυτό  σημαίνει  ότι  οι  αρχικές  τιμές  σε  αυτά  τα  στατιστικά,θα είναι υψηλότερες από τα υπόλοιπα, καθώς και ότι όταν ο ήρωας ανεβαίνει επίπεδο,
//τα στατιστικάαυτά  θα  επηρεάζονται  περισσότερο. 

class Warrior : public Hero {
    public:
        Warrior(const char* initName);
        void print() const;
        void levelUp();
};

// Ενας  μάγος  (Sorcerer)  είναι  ένας  ήρωας  που  είναι  ευνοημένος στον τομέα της επιδεξιότητας και της ευκινησίας.

class Sorcerer : public Hero {
    public:
        Sorcerer(const char* initName);
        void print() const;
        void levelUp();
};

//Ενας ιππότης (Paladin) είναι ένας ήρωας που είναιευνοημένος στον τομέα της δύναμης και της επιδεξιότητας.

class Paladin : public Hero {
    public:
        Paladin(const char* initName);
        void print() const;
        void levelUp();
};

//Ενα  τέρας  (Monster)  είναι  ένα  ζωντανό  ον.
//Εχει  ένα  εύρος  ζημιάς  που  μπορεί  να  προκαλέσει σε κάθε επίθεση του, ένα ποσό άμυνας το οποίο αφαιρείται από τη ζημιά που δέχεται σε μια επίθεση
//του αντιπάλου του, και μια πιθανότητα να αποφύγει κάποια επίθεση του αντιπάλου του.

class StatusEffect {
    int turns;
    int effect;
    public:
        StatusEffect(int initEffect, int initTurns);
        bool passTurn();
        int getEffect() const;
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
        Monster(const char* initName, int initLevel, int initMinDamage, int initMaxDamage, int initDefense, int initAgility);
        ~Monster();
        virtual void print() const;
        void attack(Living& creature) const;
        void gainDamage(int damage);
        void gainDamageStatusEffect(int amount, int turns);
        void gainDefenseStatusEffect(int amount, int turns);
        void gainAgilityStatusEffect(int amount, int turns);
        void endTurn();
};

//Ενας δράκος(Dragon) είναι ένα τέρας που είναι ευνοημένο στο εύρος ζημιάς που μπορεί να προκαλέσει.

class Dragon : public Monster {
    public:
        Dragon(const char* initName, int initLevel);
        void print() const;
};

//Ενα ον με  εξωσκελετό  (Exoskeleton)  είναι  ένα  τέρας  που  είναι  ευνοημένο  στο  ποσό  άμυνας  που  διαθέτει.

class Exoskeleton : public Monster {
    public:
        Exoskeleton(const char* initName, int initLevel);
        void print() const;
};

//Ενα  πνεύμα  (Spirit)  είναι  ένα  τέρας  που  είναι  ευνοημένο  στο  πόσο  συχνά  αποφεύγει  επιθέσεις  του αντιπάλου του.

class Spirit : public Monster {
    public:
        Spirit(const char* initName, int initLevel);
        void print() const;
};

enum Square { nonAccesible, market, common };

enum HeroType { warrior, sorcerer, paladin };

enum Direction { upDir, downDir, leftDir, rightDir };

class Grid {
    Square** grid;
    int width;
    int height;
    Hero** party;
    int heroNum;
    int position[2];
    Item* marketItems[60];
    std::vector<Weapon*> ownedWeapons;
    std::vector<Armor*> ownedArmors;
    std::vector<Potion*> ownedPotions;
    std::vector<Spell*> ownedSpells;
    public:
        Grid(int initWidth, int initHeight, HeroType* heroTypes, int heroNumInit);
        ~Grid();
        void playGame();
        void move(Direction direction);
        void displayMap() const;
        void displayHeroStats() const;
        void checkInventory() const;
        bool equip(Hero* hero = NULL);
        bool use(Hero* hero = NULL);
        void buy();
        void battle();
};