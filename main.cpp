#include <iostream>
#include <random>
#include <string>
#include <ctime>

using namespace std;

class Character {
public:
    virtual void display() = 0;
    virtual int getHealth() const = 0;
    virtual int getDamage() const = 0;
    virtual int getDefense() const = 0;
    virtual string getClass() const = 0;
    virtual string getElement() const = 0;
    virtual void attack(Character* opponent) = 0;
    virtual void passiveAbility() = 0;
    virtual void takeDamage(int damage) = 0;
    virtual bool isAlive() const = 0;
    virtual ~Character() {}
};

int randomize(int min, int max) {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(min, max);
    return dis(gen);
}

class Warrior : public Character {
public:
    Warrior(const string& element) {
        health = randomize(120, 130);
        damage = randomize(20, 30);
        defense = randomize(10, 15);
        this->element = element;
    }

    void display() override {
        cout << "Warrior (" << element << ") - Health: " << health << ", Damage: " << damage << ", Defense: " << defense << endl;
    }

    int getHealth() const override { return health; }
    int getDamage() const override { return damage; }
    int getDefense() const override { return defense; }
    string getClass() const override { return "Warrior"; }
    string getElement() const override { return element; }

    void attack(Character* opponent) override {
        int finalDamage = ((damage - opponent->getDefense()) * 0.5);
        finalDamage *= getElementDamageModifier(opponent->getElement());
        cout << "Warrior attacks! Dealt " << finalDamage << " damage!" << endl;
        opponent->takeDamage(finalDamage);
    }

    void passiveAbility() override {
        if (randomize(1, 100) <= 17) {
            cout << "Warrior reflected the attack!" << endl;
        }
    }

    void takeDamage(int damage) override {
        health -= damage;
        if (health < 0) health = 0;
    }

    bool isAlive() const override {
        return health > 0;
    }

private:
    int health;
    int damage;
    int defense;
    string element;

    float getElementDamageModifier(const string& opponentElement) {
        if (element == "Water" && opponentElement == "Fire") return 1.25;
        if (element == "Fire" && opponentElement == "Earth") return 1.25;
        if (element == "Earth" && opponentElement == "Air") return 1.25;
        if (element == "Air" && opponentElement == "Water") return 1.25;
        return 1.0;
    }
};

class Mage : public Character {
public:
    Mage(const string& element) {
        health = randomize(60, 75);
        damage = randomize(30, 35);
        defense = randomize(5, 7);
        this->element = element;
    }

    void display() override {
        cout << "Mage (" << element << ") - Health: " << health << ", Damage: " << damage << ", Defense: " << defense << endl;
    }

    int getHealth() const override { return health; }
    int getDamage() const override { return damage; }
    int getDefense() const override { return defense; }
    string getClass() const override { return "Mage"; }
    string getElement() const override { return element; }

    void attack(Character* opponent) override {
        int finalDamage = ((damage - opponent->getDefense()) * 0.5);
        finalDamage *= getElementDamageModifier(opponent->getElement());
        cout << "Mage attacks! Dealt " << finalDamage << " damage!" << endl;
        opponent->takeDamage(finalDamage);
    }

    void passiveAbility() override {
        if (randomize(1, 100) <= 17) {
            cout << "Mage's passive ability triggered! +50% damage!" << endl;
            damage = static_cast<int>(damage * 1.5);
        }
    }

    void takeDamage(int damage) override {
        health -= damage;
        if (health < 0) health = 0;
    }

    bool isAlive() const override {
        return health > 0;
    }

private:
    int health;
    int damage;
    int defense;
    string element;

    float getElementDamageModifier(const string& opponentElement) {
        if (element == "Water" && opponentElement == "Fire") return 1.25;
        if (element == "Fire" && opponentElement == "Earth") return 1.25;
        if (element == "Earth" && opponentElement == "Air") return 1.25;
        if (element == "Air" && opponentElement == "Water") return 1.25;
        return 1.0;
    }
};

class Scout : public Character {
public:
    Scout(const string& element) {
        health = randomize(100, 110);
        damage = randomize(20, 25);
        defense = randomize(7, 12);
        this->element = element;
    }

    void display() override {
        cout << "Scout (" << element << ") - Health: " << health << ", Damage: " << damage << ", Defense: " << defense << endl;
    }

    int getHealth() const override { return health; }
    int getDamage() const override { return damage; }
    int getDefense() const override { return defense; }
    string getClass() const override { return "Scout"; }
    string getElement() const override { return element; }

    void attack(Character* opponent) override {
        int finalDamage = ((damage - opponent->getDefense()) * 0.5);
        finalDamage *= getElementDamageModifier(opponent->getElement());
        cout << "Scout attacks! Dealt " << finalDamage << " damage!" << endl;
        opponent->takeDamage(finalDamage);
    }

    void passiveAbility() override {
        if (randomize(1, 100) <= 17) {
            cout << "Scout stunned the opponent! They miss their next turn!" << endl;
        }
    }

    void takeDamage(int damage) override {
        health -= damage;
        if (health < 0) health = 0;
    }

    bool isAlive() const override {
        return health > 0;
    }

private:
    int health;
    int damage;
    int defense;
    string element;

    float getElementDamageModifier(const string& opponentElement) {
        if (element == "Water" && opponentElement == "Fire") return 1.25;
        if (element == "Fire" && opponentElement == "Earth") return 1.25;
        if (element == "Earth" && opponentElement == "Air") return 1.25;
        if (element == "Air" && opponentElement == "Water") return 1.25;
        return 1.0;
    }
};

class Archer : public Character {
public:
    Archer(const string& element) {
        health = randomize(70, 85);
        damage = randomize(25, 35);
        defense = randomize(7, 10);
        this->element = element;
    }

    void display() override {
        cout << "Archer (" << element << ") - Health: " << health << ", Damage: " << damage << ", Defense: " << defense << endl;
    }

    int getHealth() const override { return health; }
    int getDamage() const override { return damage; }
    int getDefense() const override { return defense; }
    string getClass() const override { return "Archer"; }
    string getElement() const override { return element; }

    void attack(Character* opponent) override {
        int finalDamage = ((damage - opponent->getDefense()) * 0.5);
        finalDamage *= getElementDamageModifier(opponent->getElement());
        cout << "Archer attacks! Dealt " << finalDamage << " damage!" << endl;
        opponent->takeDamage(finalDamage);
    }

    void passiveAbility() override {
        if (randomize(1, 100) <= 17) {
            cout << "Archer applies Bleed effect!" << endl;
        }
    }

    void takeDamage(int damage) override {
        health -= damage;
        if (health < 0) health = 0;
    }

    bool isAlive() const override {
        return health > 0;
    }

private:
    int health;
    int damage;
    int defense;
    string element;

    float getElementDamageModifier(const string& opponentElement) {
        if (element == "Water" && opponentElement == "Fire") return 1.25;
        if (element == "Fire" && opponentElement == "Earth") return 1.25;
        if (element == "Earth" && opponentElement == "Air") return 1.25;
        if (element == "Air" && opponentElement == "Water") return 1.25;
        return 1.0;
    }
};


int main() {
    Character* player1 = nullptr;
    Character* player2 = nullptr;
    string elementChoice, classChoice;

    // Player 1's choices
    cout << "Player 1, choose your class (Warrior, Mage, Scout, Archer): ";
    cin >> classChoice;
    cout << "Choose element for player 1 (Water, Fire, Earth, Air): ";
    cin >> elementChoice;

    if (classChoice == "Warrior") {
        player1 = new Warrior(elementChoice);
    } else if (classChoice == "Mage") {
        player1 = new Mage(elementChoice);
    } else if (classChoice == "Scout") {
        player1 = new Scout(elementChoice);
    } else if (classChoice == "Archer") {
        player1 = new Archer(elementChoice);
    } else {
        cout << "Invalid class choice!" << endl;
        return 1;
    }

    // Player 2's choices
    cout << "Player 2, choose your class (Warrior, Mage, Scout, Archer): ";
    cin >> classChoice;
    cout << "Choose element for player 2 (Water, Fire, Earth, Air): ";
    cin >> elementChoice;

    if (classChoice == "Warrior") {
        player2 = new Warrior(elementChoice);
    } else if (classChoice == "Mage") {
        player2 = new Mage(elementChoice);
    } else if (classChoice == "Scout") {
        player2 = new Scout(elementChoice);
    } else if (classChoice == "Archer") {
        player2 = new Archer(elementChoice);
    } else {
        cout << "Invalid class choice!" << endl;
        return 1;
    }

    cout << "====================================" << endl;

    // Display players' information
    player1->display();
    player2->display();

    cout << "====================================" << endl;

    // Battle loop
    int phase = 1;
    while (player1->isAlive() && player2->isAlive()) {
        cout << "\n--- Phase " << phase << " ---\n";
        
        // Player 1's turn
        player1->attack(player2);
        if (player2->isAlive()) {
            player2->attack(player1);
        }

        // Display health after the phase
        cout << "Player 1 Health: " << player1->getHealth() << endl;
        cout << "Player 2 Health: " << player2->getHealth() << endl;

        phase++;
    }

    // Determine winner
    if (player1->isAlive()) {
        cout << "====================================" << endl;
        cout << "Player 1 wins!" << endl;
        cout << "====================================" << endl;
    } else {
        cout << "====================================" << endl;
        cout << "Player 2 wins!" << endl;
        cout << "====================================" << endl;
    }


    // Cleanup
    delete player1;
    delete player2;

    return 0;
} 
