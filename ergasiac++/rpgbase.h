/* File: rpgbase.h */

#include <string>
#include <list>

// Κλάση που αναπαριστά ένα αντικείμενο
class Item {
    std::string name;   // όνομα του αντικειμένου 
    int price;          // τιμή αγοράς του
    int minLevel;       // ελάχιστο επίπεδο στο οποίο πρέπει να βρίσκεται ένας ήρωας για να το χρησιμοποιήσει
    public:
        // Constructor
        Item(const char* initName, int initPrice, int initMinLevel);

        int getPrice() const { return price; }          // Accessors
        int getMinLevel() const { return minLevel; }    //

        // Εκτυπώνει το όνομα, την τιμή και το ελάχιστο επίπεδο χρήσης
        virtual void print() const;
};

// Κλάση που αναπαριστά ένα όπλο, αντικείμενο το οποίο μπορεί να χρησιμοποιηθεί από έναν ήρωα για να επιτεθεί σε κάποιο τέρας
class Weapon : public Item {
    int damage;     // ποσό ζημιάς που προκαλεί στον αντίπαλο
    bool twoHanded; // αν χρησιμοποιείται και με τα δύο χέρια
    public:
        // Constructor. Δίνονται όνομα, ζημία και το αν χρησιμοποιείται με τα δύο χέρια.
        // Τιμή και ελάχιστο επίπεδο υπολογίζονται συναρτήσει των τελευταίων δύο.
        Weapon(const char* initName, int initDamage, int initTwoHanded)
        :   Item(initName, 10*initDamage*(initTwoHanded ? 2 : 1), initDamage/(initTwoHanded ? 1 : 3) + 1), damage(initDamage), twoHanded(initTwoHanded) { }
        
        int getDamage() const { return damage; }        // Accessors
        bool isTwoHanded() const { return twoHanded; }  //

        // Εκτυπώνει τα δεδομένα του όπλου και καλεί τον εκτυπωτή της υπερκλάσης (Item)
        void print() const;
};

// Κλάση που αναπαριστά μια πανοπλία, αντικείμενο το οποίο όταν το φοράει ένας ήρωας, μειώνει την ζημία που δέχεται από μία επίθεση του αντιπάλου του
class Armor : public Item {
    int defense;    // άμυνα/ποσό μείωσης ζημίας
    public:
        // Constructor. Δίνονται όνομα και άμυνα. Τιμή και ελάχιστο επίπεδο υπολογίζονται συναρτήσει της άμυνας.
        Armor(const char* initName, int initDefense) : Item(initName, 15*initDefense, initDefense/3 + 1), defense(initDefense) { }

        int getDefense() const { return defense; }  // Accessor

        // Εκτυπώνει τα δεδομένα της πανοπλίας και καλεί τον εκτυπωτή της υπερκλάσης (Item)
        void print() const;
};

class Hero;

// Κλάση που αναπαριστά ένα φίλτρο, αντικείμενο το οποίο όταν το φοράει ένας ήρωας, αυξάνει κάποιο στατιστικό του κατά κάποιο ποσό
class Potion : public Item {
    protected:
        int effect; // δραστικότητα/ποσό αύξησης στατιστικού κατά την χρήση
    public:
        // Constructor. Δίνονται όνομα και δραστικότητα. Τιμή και ελάχιστο επίπεδο υπολογίζονται συναρτήσει της δραστικότητα.
        Potion(const char* initName, int initEffect) : Item(initName, 30*initEffect, initEffect/2 + 1), effect(initEffect) { }

        // Αυξάνεται το κατάλληλο στατιστικό του ήρωα hero κατά effect, αν έχει αρκετά ψηλό επίπεδο. Επιστρέφεται το αν όντως αυξήθηκε.
        virtual void useOn(Hero* hero) = 0;

        // Εκτυπώνει τα δεδομένα του φίλτρου και καλεί τον εκτυπωτή της υπερκλάσης (Item)
        virtual void print() const;
};

// Κλάση που αναπαριστά ένα φίλτρο δύναμης, φίλτρο που αυξάνει την δύναμη του ήρωα τον οποίο χρησιμοποιείται
class StrengthPotion : public Potion {
    public:
        // Constructor
        StrengthPotion(const char* initName, int initEffect) : Potion(initName, initEffect) { }

        // Αυξάνεται η δύναμη του ήρωα hero κατά effect.
        void useOn(Hero* hero);

        // Εκτυπώνει την δύναμη που προσίδει το φίλτρο και καλεί τον εκτυπωτή της υπερκλάσης (Potion)
        void print() const;
};

// Κλάση που αναπαριστά ένα φίλτρο επιδεξιότητας, φίλτρο που αυξάνει την επιδεξιότητα του ήρωα τον οποίο χρησιμοποιείται
class DexterityPotion : public Potion {
    public:
        // Constructor
        DexterityPotion(const char* initName, int initEffect) : Potion(initName, initEffect) { }
        
        // Αυξάνεται η επιδεξιότητα του ήρωα hero κατά effect.
        void useOn(Hero* hero);
        
        // Εκτυπώνει την επιδεξιότητα που προσίδει το φίλτρο και καλεί τον εκτυπωτή της υπερκλάσης (Potion)
        void print() const;
};

// Κλάση που αναπαριστά ένα φίλτρο ευκινησίας, φίλτρο που αυξάνει την ευκινησία του ήρωα τον οποίο χρησιμοποιείται
class AgilityPotion : public Potion {
    public:
        // Constructor
        AgilityPotion(const char* initName, int initEffect) : Potion(initName, initEffect) { }
        
        // Αυξάνεται η ευκινησία του ήρωα hero κατά effect.
        void useOn(Hero* hero);
        
        // Εκτυπώνει την ευκινησία που προσίδει το φίλτρο και καλεί τον εκτυπωτή της υπερκλάσης (Potion)
        void print() const;
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

        // Εκτυπώνει τα δεδομένα του ξορκιού και καλεί τον εκτυπωτή της υπερκλάσης (Item)
        virtual void print() const;
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

        // Εκτυπώνει τον τύπο του ξορκιού και καλεί τον εκτυπωτή της υπερκλάσης (Spell)
        virtual void print() const;
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

        // Εκτυπώνει τον τύπο του ξορκιού και καλεί τον εκτυπωτή της υπερκλάσης (Spell)
        virtual void print() const;
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

        // Εκτυπώνει τον τύπο του ξορκιού και καλεί τον εκτυπωτή της υπερκλάσης (Spell)
        virtual void print() const;
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
        Living(const char* initName, int initLevel) : name(initName), level(initLevel), healthPower(50), maxHealthPower(50) { }

        std::string getName() const { return name; }                // +
        int getLevel() const { return level; }                      // | Accessors
        int getHealthPower() const { return healthPower; }          // +
        int getMaxHealthPower() const { return maxHealthPower; }    // +

        // Αυξάνει την HP κατά amount, χωρίς να ξεπερνά την maxHP
        void recoverHealthPower(int amount);

        // Αν damage > 0, μειώνει την HP κατά damage. Δεν πέφτει κάτω από το 0 και αν το φτάσει τυπώνει ένα μήνυμα που λέει πως το ον λιποθύμησε.
        virtual void gainDamage(int damage);

        // Εκτυπώνει τα δεδομένα του όντος
        void print() const;
};

// Κλάση που αναπαριστά έναν ήρωα, που είναι ζωντανό ον
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

        // Αυξάνει την εμπειρία κατά amount, και ανά 100 μονάδες την μηδενίζει και αυξάνει κατά ένα επίπεδο τον ήρωα
        void gainExperience(int amount);

        // Αυξάνει την MP κατά amount, χωρίς να ξεπερνά την maxMP
        void recoverMagicPower(int amount);

        // Λαμβάνει υπόψιν την πανοπλία και την ευκινησία, και καλεί την gainDamage της υπερκλάσης Living περνόντας την τροποποιημένη damage
        void gainDamage(int damage);

        // Αν money >= amount, αφαιρείται το amount, και επιστρέφεται true. Αλλιώς false.
        bool spendMoney (int amount);

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

        // Καλεί τον εκτυπωτή της υπερκλάσης (Living) και εκτυπώνει τα δεδομένα του ήρωα
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

// Κλάση που αναπαριστά μια προσωρινή μεταβολή στα στατιστικά ενός τέρατος
class StatusEffect {
    int turns;  // υπολοιπόμενη διάρκεια ισχύος σε γύρους
    int effect; // μέγεθος μεταβολής
    public:
        // Constructor
        StatusEffect(int initEffect, int initTurns) : effect(initEffect), turns(initTurns) { }

        int getEffect() const { return effect; }    // Accessor

        // "Περνάει" έναν γύρο/μειώνει τους υπολοιπόμενους γύρους κατά 1. Αν οι γύροι τελειώσουν επιστρέφει true, αλλιώς false.
        bool passTurn() { return --turns == 0; }
};

// Κλάση που αναπαριστά ένα τέρας, που είναι ζωντανό ον
class Monster : public Living {
    int minDamage;  // ελάχιστη ζημία
    int maxDamage;  // μέγιστη ζημία
    int defense;    // άμυνα
    int agility;    // ευκινησία
    std::list<StatusEffect*> damageStatusEffects;   // status effects ζημίας
    std::list<StatusEffect*> defenseStatusEffects;  // status effects άμυνας
    std::list<StatusEffect*> agilityStatusEffects;  // status effects ευκινησίας
    public:
        // Constructor
        Monster(const char* initName, int initLevel, int initMinDamage, int initMaxDamage, int initDefense, int initAgility)
        :   Living(initName, initLevel), minDamage(initMinDamage), maxDamage(initMaxDamage), defense(initDefense), agility(initAgility) { }

        // Destructor
        ~Monster();

        // Προκαλεί στο creature ζημία τυχαία εντός του εύρους ζημιάς του τέρατος
        void attack(Living& creature) const;

        // Λαμβάνει υπόψιν την άμυνα και την ευκινησία, και καλεί την gainDamage της υπερκλάσης Living περνόντας την τροποποιημένη damage
        void gainDamage(int damage);

        // Προσθέτει στο τέρας ένα status effect ζημίας ποσού amount και διάρκειας turns
        void gainDamageStatusEffect(int amount, int turns);

        // Προσθέτει στο τέρας ένα status effect άμυνας ποσού amount και διάρκειας turns
        void gainDefenseStatusEffect(int amount, int turns);

        // Προσθέτει στο τέρας ένα status effect ευκινησίας ποσού amount και διάρκειας turns
        void gainAgilityStatusEffect(int amount, int turns);

        // Αν HP != 0, ανακτά (recover) 1 HP και περνάει ένας γύρος για κάθε status effect.
        void endTurn();

        // Καλεί τον εκτυπωτή της υπερκλάσης (Living) και εκτυπώνει τα δεδομένα του τέρατος
        virtual void print() const;
};

// Κλάση που αναπαριστά έναν δράκο, τέρας ευνοημένο στο εύρος ζημιάς που μπορεί να προκαλέσει
class Dragon : public Monster {
    public:
        // Constructor. Αρχικοποιεί το τέρας ανάλογα με το επίπεδο, ευνοώντας το στο εύρος ζημιάς
        Dragon(const char* initName, int initLevel)
        :   Monster(initName, initLevel, 3*initLevel, 6*initLevel, 2*initLevel, 2*initLevel) { }

        // Εκτυπώνει τον τύπο του τέρατος και καλεί τον εκτυπωτή της υπερκλάσης (Monster)
        void print() const;
};

// Κλάση που αναπαριστά ένα ον με εξωσκελετό, τέρας ευνοημένο στο ποσό άμυνας που διαθέτει
class Exoskeleton : public Monster {
    public:
        // Constructor. Αρχικοποιεί το τέρας ανάλογα με το επίπεδο, ευνοώντας το στην άμυνα
        Exoskeleton(const char* initName, int initLevel)
        :   Monster(initName, initLevel, 1*initLevel, 2*initLevel, 6*initLevel - 2, 2*initLevel) { }

        // Εκτυπώνει τον τύπο του τέρατος και καλεί τον εκτυπωτή της υπερκλάσης (Monster)
        void print() const;
};

// Κλάση που αναπαριστά ένα πνεύμα, τέρας ευνοημένο στο ποσό συχνά αποφεύγει επιθέσεις του αντιπάλου του/ευκινησία
class Spirit : public Monster {
    public:
        // Constructor. Αρχικοποιεί το τέρας ανάλογα με το επίπεδο, ευνοώντας το στην ευκινησία
        Spirit(const char* initName, int initLevel)
        :   Monster(initName, initLevel, 1*initLevel, 2*initLevel, 2*initLevel, 6*initLevel) { }

        // Εκτυπώνει τον τύπο του τέρατος και καλεί τον εκτυπωτή της υπερκλάσης (Monster)
        void print() const;
};