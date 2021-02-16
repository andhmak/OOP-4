#include <iostream>
#include <string>
#include <vector>
#include <list>

// Κλάση που αναπαριστά ένα αντικείμενο
class Item {
    std::string name;   // όνομα του αντικειμένου 
    int price;          // τιμή αγοράς του
    int minLevel;       // ελάχιστο επίπεδο στο οποίο πρέπει να βρίσκεται ένας ήρωας για να το χρησιμοποιήσει
    public:
        Item(const char* initName, int initPrice, int initMinLevel);    // Constructor
        int getPrice() const { return price; }          // Accessors
        int getMinLevel() const { return minLevel; }    //
        virtual void print() const;                     // Εκτυπώνει το όνομα, την τιμή και το ελάχιστο επίπεδο χρήσης
};

// Κλάση που αναπαριστά ένα όπλο, αντικείμενο το οποίο μπορεί να χρησιμοποιηθεί από έναν ήρωα για να επιτεθεί σε κάποιο τέρας
class Weapon : public Item {
    int damage;     // ποσό ζημιάς που προκαλεί στον αντίπαλο
    bool twoHanded; // αν χρησιμοποιείται και με τα δύο χέρια
    public:
        // Constructor. Δίνονται όνομα, ζημία και το αν χρησιμοποιείται με τα δύο χέρια.
        // Τιμή και ελάχιστο επίπεδο υπολογίζονται συναρτήσει των τελευταίων δύο.
        Weapon(const char* initName, int initDamage, int initTwoHanded);
        int getDamage() const { return damage; }        // Accessors
        bool isTwoHanded() const { return twoHanded; }  //
        void print() const; // Εκτυπώνει τα δεδομένα του όπλου και καλεί τον εκτυπωτή της υπερκλάσης (Item)
};

// Κλάση που αναπαριστά μια πανοπλία, αντικείμενο το οποίο όταν το φοράει ένας ήρωας, μειώνει την ζημία που δέχεται από μία επίθεση του αντιπάλου του
class Armor : public Item {
    int defense;    // άμυνα/ποσό μείωσης ζημίας
    public:
        // Constructor. Δίνονται όνομα και άμυνα. Τιμή και ελάχιστο επίπεδο υπολογίζονται συναρτήσει της άμυνας.
        Armor(const char* initName, int initDefense);
        int getDefense() const { return defense; }  // Accessor
        void print() const; // Εκτυπώνει τα δεδομένα της πανοπλίας και καλεί τον εκτυπωτή της υπερκλάσης (Item)
};

class Hero;

// Κλάση που αναπαριστά ένα φίλτρο, αντικείμενο το οποίο όταν το φοράει ένας ήρωας, αυξάνει κάποιο στατιστικό του κατά κάποιο ποσό
class Potion : public Item {
    protected:
        int effect; // δραστικότητα/ποσό αύξησης στατιστικού κατά την χρήση
    public:
        // Constructor. Δίνονται όνομα και δραστικότητα. Τιμή και ελάχιστο επίπεδο υπολογίζονται συναρτήσει της δραστικότητα.
        Potion(const char* initName, int initEffect);
        // Αυξάνεται το κατάλληλο στατιστικό του ήρωα hero κατά effect, αν έχει αρκετά ψηλό επίπεδο. Επιστρέφεται το αν όντως αυξήθηκε.
        virtual void useOn(Hero* hero) = 0;
        virtual void print() const; // Εκτυπώνει τα δεδομένα του φίλτρου και καλεί τον εκτυπωτή της υπερκλάσης (Item)
};

// Κλάση που αναπαριστά ένα φίλτρο δύναμης, φίλτρο που αυξάνει την δύναμη του ήρωα τον οποίο χρησιμοποιείται
class StrengthPotion : public Potion {
    public:
        StrengthPotion(const char* initName, int initEffect) : Potion(initName, initEffect) { } // Constructor
        // Αυξάνεται η δύναμη του ήρωα hero κατά effect.
        void useOn(Hero* hero);
        void print() const; // Εκτυπώνει την δύναμη που προσίδει το φίλτρο και καλεί τον εκτυπωτή της υπερκλάσης (Potion)
};

// Κλάση που αναπαριστά ένα φίλτρο επιδεξιότητας, φίλτρο που αυξάνει την επιδεξιότητα του ήρωα τον οποίο χρησιμοποιείται
class DexterityPotion : public Potion {
    public:
        DexterityPotion(const char* initName, int initEffect) : Potion(initName, initEffect) { } // Constructor
        // Αυξάνεται η επιδεξιότητα του ήρωα hero κατά effect.
        void useOn(Hero* hero);
        void print() const; // Εκτυπώνει την επιδεξιότητα που προσίδει το φίλτρο και καλεί τον εκτυπωτή της υπερκλάσης (Potion)
};

// Κλάση που αναπαριστά ένα φίλτρο ευκινησίας, φίλτρο που αυξάνει την ευκινησία του ήρωα τον οποίο χρησιμοποιείται
class AgilityPotion : public Potion {
    public:
        AgilityPotion(const char* initName, int initEffect) : Potion(initName, initEffect) { } // Constructor
        // Αυξάνεται η ευκινησία του ήρωα hero κατά effect.
        void useOn(Hero* hero);
        void print() const; // Εκτυπώνει την ευκινησία που προσίδει το φίλτρο και καλεί τον εκτυπωτή της υπερκλάσης (Potion)
};

class Monster;

// Κλάση που αναπαριστά ένα ξόρκι, μια μαγική επίθεση που μπορεί να εκτελέσει κάποιος ήρωας
class Spell : public Item {
    protected:
        int minDamage;  // ελάχιστη ζημία που μπορεί να προκαλέσει
        int maxDamage;  // μέγιστη ζημία που μπορεί να προκαλέσει
        int magicCost;  // ποσό μαγικής ενέργειας που απαιτεί για να εκτελεστεί
    public:
        // Constructor. Δίνονται όνομα, εύρος ζημίας και μαγικό κόστος. Τιμή και ελάχιστο επίπεδο υπολογίζονται συναρτήσει των προηγούμενων.
        Spell(const char* initName, int initMinDamage, int initMaxDamage, int initMagicCost);
        int getMagicCost() const { return magicCost; }  // Accessor
        // Εκτελεί το ξόρκι στο τέρας enemy με αποδοτικότητα efficiency. Όσο μεγαλύτερη
        // η αποδοτικότητα τόσο μεγαλήτερη η ζημία, εντός του καθορισμένου εύρους.
        virtual void cast(Monster& enemy, int efficiency) const;
        virtual void print() const; // Εκτυπώνει τα δεδομένα του ξορκιού και καλεί τον εκτυπωτή της υπερκλάσης (Item)
};

// Κλάση που αναπαριστά ένα ξόρκι πάγου, μια μαγική επίθεση που εκτός από τη ζημιά που προκαλεί,
// μειώνει και το εύρος ζημιάς του αντιπάλου για κάποιους γύρους
class IceSpell : public Spell {
    public:
        // Constructor
        IceSpell(const char* initName, int initMinDamage, int initMaxDamage, int initMagicCost)
        :   Spell(initName, initMinDamage, initMaxDamage, initMagicCost) { }
        // Εκτελεί το ξόρκι στο τέρας enemy με αποδοτικότητα efficiency.
        // Εκτός από ζημία που προκαλεί δίνει και ένα αρνητικό status effect δύναμης στο enemy διάρκειας 3 γύρων.
        void cast(Monster& enemy, int efficiency) const;
        virtual void print() const; // Εκτυπώνει τον τύπο του ξορκιού και καλεί τον εκτυπωτή της υπερκλάσης (Spell)
};

// Κλάση που αναπαριστά ένα ξόρκι φωτιάς, μια μαγική επίθεση που εκτός από τη ζημιά που προκαλεί,
// μειώνει και το ποσό άμυνας του αντιπάλου για κάποιους γύρους
class FireSpell : public Spell {
    public:
        // Constructor
        FireSpell(const char* initName, int initMinDamage, int initMaxDamage, int initMagicCost)
        :   Spell(initName, initMinDamage, initMaxDamage, initMagicCost) { }
        // Εκτελεί το ξόρκι στο τέρας enemy με αποδοτικότητα efficiency.
        // Εκτός από ζημία που προκαλεί δίνει και ένα αρνητικό status effect άμυνας στο enemy διάρκειας 3 γύρων.
        void cast(Monster& enemy, int efficiency) const;
        virtual void print() const; // Εκτυπώνει τον τύπο του ξορκιού και καλεί τον εκτυπωτή της υπερκλάσης (Spell)
}; 

// Κλάση που αναπαριστά ένα ξόρκι ηλεκτρισμού, μια μαγική επίθεση που εκτός από τη ζημιά που προκαλεί,
// μειώνει καιτην πιθανότητα να αποφύγει μια επίθεση ο αντίπαλος για κάποιους γύρους
class LightingSpell : public Spell {
    public:
        // Constructor
        LightingSpell(const char* initName, int initMinDamage, int initMaxDamage, int initMagicCost)
        :   Spell(initName, initMinDamage, initMaxDamage, initMagicCost) { }
        // Εκτελεί το ξόρκι στο τέρας enemy με αποδοτικότητα efficiency.
        // Εκτός από ζημία που προκαλεί δίνει και ένα αρνητικό status effect ευκινησίας στο enemy διάρκειας 3 γύρων.
        void cast(Monster& enemy, int efficiency) const;
        virtual void print() const; // Εκτυπώνει τον τύπο του ξορκιού και καλεί τον εκτυπωτή της υπερκλάσης (Spell)
};

// Κλάση που αναπαριστά ένα ζωντανό ον
class Living {
    std::string name;   // όνομα
    int healthPower;    // τρέχουσα ζωτική ενέργεια/HP
    int maxHealthPower; // μέγιστη ζωτική ενέργεια
    protected:
        int level;      // επίπεδο
    public:
        // Constructor
        Living(const char* initName, int initLevel);
        std::string getName() const { return name; }                // +
        int getLevel() const { return level; }                      // | Accessors
        int getHealthPower() const { return healthPower; }          // +
        int getMaxHealthPower() const { return maxHealthPower; }    // +
        void recoverHealthPower(int amount);    // Αυξάνει την HP κατά amount, χωρίς να ξεπερνά την maxHP
        // Αν damage > 0, μειώνει την HP κατά damage. Δεν πέφτει κάτω από το 0 και αν το φτάσει τυπώνει ένα μήνυμα που λέει πως το ον λιποθύμησε.
        virtual void gainDamage(int damage);
        void print() const; // Εκτυπώνει τις πληροφορίες του όντος
};

//Ενας ήρωας (Hero) είναι έναζωντανό ον.
//Εχει ένα ποσό μαγικής ενέργειας (magicPower), καθώς και κάποια χαρακτηριστικάπου επηρεάζουν την ικανότητα του στη μάχη.
//Ενας ήρωας έχει κάποια τιμή δύναμης (strength), κάποια τιμή επιδεξιότητας (dexterity) καθώς και κάποια τιμή ευκινησίας (agility).
//Η δύναμη του ήρωα προστίθεται στο ποσό ζημιάς που προκαλεί ένα όπλο, η επιδεξιότητα του επιτρέπει να εκτελεί ταξόρκια πιο αποδοτικά και
//τέλος η ευκινησία του επιτρέπει να μπορεί με κάποια πιθανότητα να αποφύγει κάποια επίθεση του αντιπάλου του.
//Ενας ήρωας διαθέτει ένα ποσό χρημάτων (money) καθώς και ένα ποσό εμπειρίας (experience).
//Οταν ο ήρωας αποκτήσει αρκετή εμπειρία, ανεβαίνει ένα επίπεδο(levelUp).
//Σε κάθε επίπεδο, οι τιμές της δύναμης, της επιδεξιότητας και της ευκινησίας του ήρωα,αυξάνονται κατά κάποιο ποσό.

// Κλάση που αναπαριστά έναν ήρωα, που  είναι ζωντανό ον
class Hero : public Living {
    int magicPower;     // τρέχουσα μαγική ενέργεια/MP
    int maxMagicPower;  // μέγιστη μαγική ενέργεια
    int money;          // χρήματα
    int experience;     // εμπειρία
    Weapon* weapon;     // όπλο που κρατάει
    Armor* armor;       // πανοπλία που φοράει
    protected:
        int strength;   // δύναμη
        int dexterity;  // επιδεξιότητα
        int agility;    // ευκινησία
    public:
        // Constructor
        Hero(const char* initName, int strengthInit, int dexterityInit, int agilityInit);
        int getMagicPower() const { return magicPower; }    // Accessors
        int getMoney() const { return money; }              //
        void setMoney(int newMoney) { money = newMoney; }       // +
        void addStrength(int amount) { strength += amount; }    // +
        void addDexterity(int amount) { dexterity += amount; }  // | Mutators
        void addAgility(int amount) { agility += amount; }      // +
        virtual void levelUp(int times) { level += times; }     // +
        void gainExperience(int amount);    // Αυξάνει την εμπειρία κατά amount, και ανά 100 μονάδες την μηδενίζει και αυξάνει κατά ένα επίπεδο τον ήρωα
        void recoverMagicPower(int amount); // Αυξάνει την MP κατά amount, χωρίς να ξεπερνά την maxMP
        void gainDamage(int damage);    // Λαμβάνει υπόψιν την πανοπλία και την ευκινησία, και καλεί την gainDamage της Living περνόντας την τροποποιημένη damage
        bool spendMoney (int amount);   // Αν money >= amount, αφαιρείται το amount, και επιστρέφεται true. Αλλιώς false.
        // Προκαλεί στο creature ζημία ανάλογα με την δύναμη και το όπλο
        void attack(Living& creature) const { creature.gainDamage(strength + (weapon != NULL ? weapon->getDamage()*weapon->isTwoHanded() : 0)); }
        // Αν έχει αρκετά ψηλό επίπεδο χρησιμοποιεί το potion. Επιστρέφει το αν χρησιμοποιήθηκε.
        bool use(Potion& potion);
        // Αν έχει αρκετά ψηλό επίπεδο και αρκετή MP εκτελεί το spell στο enemy με αποδοτικότητα dexterity. Επιστρέφει το αν εκτελέστηκε.
        bool castSpell(const Spell& spell, Monster& enemy);
        // Αν έχει αρκετά ψηλό επίπεδο παίρνει το newWeapon και επιστρέφει το παλιό. Αλλιώς επιστρέφει το καινούργιο.
        Weapon* equip(Weapon* newWeapon);
        // Αν έχει αρκετά ψηλό επίπεδο βάζει την newArmor και επιστρέφει την παλιά. Αλλιώς επιστρέφει την καινούργια.
        Armor* equip(Armor* newArmor);
        // Αν HP != 0, ανακτά (recover) 1 HP και 1 MP.
        void endTurn();
        // Καλεί τον εκτυπωτή της υπερκλάσης (Living) και εκτυπώνει τα στοιχεία του ήρωα
        virtual void print() const;
};

// Κλάση που αναπαριστά έναν μαχητή, έναν ήρωα που είναι ευνοημένος στον τομέα της δύναμης και της ευκινησίας
class Warrior : public Hero {
    public:
        // Constructor. Αρχικοποιεί τον ήρωα ευνοώντας τον στον τομέα της δύναμης και της ευκινησίας
        Warrior(const char* initName) : Hero(initName, 5, 2, 5) { }
        // Καλεί την levelUp της υπερκλάσης (Hero) και αυξάνει τις ικανότητες του μαχητή, κυρίως την δύναμη και την ευκινησία
        void levelUp(int times);
        // Εκτυπώνει τον τύπο του ήρωα και καλεί τον εκτυπωτή της υπερκλάσης (Hero)
        void print() const;
};

// Κλάση που αναπαριστά έναν μάγο, έναν ήρωα που είναι ευνοημένος στον τομέα της επιδεξιότητας και της ευκινησίας
class Sorcerer : public Hero {
    public:
        // Constructor. Αρχικοποιεί τον ήρωα ευνοώντας τον στον τομέα της επιδεξιότητας και της ευκινησίας
        Sorcerer(const char* initName) : Hero(initName, 2, 5, 5) { }
        // Καλεί την levelUp της υπερκλάσης (Hero) και αυξάνει τις ικανότητες του μάγου, κυρίως την επιδεξιότητα και την ευκινησία
        void levelUp(int times);
        // Εκτυπώνει τον τύπο του ήρωα και καλεί τον εκτυπωτή της υπερκλάσης (Hero)
        void print() const;
};

// Κλάση που αναπαριστά έναν ιππότη, έναν ήρωα που είναι ευνοημένος στον τομέα της δύναμης και της επιδεξιότητας
class Paladin : public Hero {
    public:
        // Constructor. Αρχικοποιεί τον ήρωα ευνοώντας τον στον τομέα της δύναμης και της επιδεξιότητας
        Paladin(const char* initName) : Hero(initName, 5, 5, 2) { }
        // Καλεί την levelUp της υπερκλάσης (Hero) και αυξάνει τις ικανότητες του ιππότη, κυρίως την δύναμη και την επιδεξιότητα
        void levelUp(int times);
        // Εκτυπώνει τον τύπο του ήρωα και καλεί τον εκτυπωτή της υπερκλάσης (Hero)
        void print() const;
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
        int getEffect() const { return effect; }
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
        void attack(Living& creature) const;
        void gainDamage(int damage);
        void gainDamageStatusEffect(int amount, int turns);
        void gainDefenseStatusEffect(int amount, int turns);
        void gainAgilityStatusEffect(int amount, int turns);
        void endTurn();
        virtual void print() const;
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

enum HeroType { warrior, sorcerer, paladin };

class Party {
    Hero** heroes;
    int heroNum;
    std::vector<Weapon*> ownedWeapons;
    std::vector<Armor*> ownedArmors;
    std::vector<Potion*> ownedPotions;
    std::vector<Spell*> ownedSpells;
    public:
        Party(HeroType* heroTypes, int heroNumInit);
        ~Party();
        bool equip(Hero* hero = NULL);
        bool use(Hero* hero = NULL);
        bool pay(int amount);
        void buy(Weapon* weapon);
        void buy(Armor* armor);
        void buy(Potion* potion);
        void buy(Spell* spell);
        void sell();
        void battle();
        void checkInventory() const;
        void print() const;
};

class Market {
    Item** stock;
    int weaponAmount;
    int armorAmount;
    int potionAmount;
    int spellAmount;
    public:
        Market(int weaponNumInit, int armorNumInit, int potionNumInit, int spellNumInit);
        ~Market();
        void buy(Party& party);
        void sell(Party& party);
};

enum Square { nonAccesible, market, common };

enum Direction { upDir, downDir, leftDir, rightDir };

class Grid {
    Square** grid;
    int width;
    int height;
    Party party;
    int position[2];
    Market gameMarket;
    public:
        Grid(int initWidth, int initHeight, HeroType* heroTypes, int heroNumInit);
        ~Grid();
        void playGame();
        void move(Direction direction);
        void displayMap() const;
};