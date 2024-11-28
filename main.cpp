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
        cout << "Воин (" << element << ") - Здоровье: " << health << ", Урон: " << damage << ", Защита: " << defense << endl;
    }

    int getHealth() const override { return health; }
    int getDamage() const override { return damage; }
    int getDefense() const override { return defense; }
    string getClass() const override { return "Воин"; }
    string getElement() const override { return element; }

    void attack(Character* opponent) override {
        int finalDamage = ((damage - opponent->getDefense()) * 0.5);
        finalDamage *= getElementDamageModifier(opponent->getElement());
        cout << "Воин атакует! Нанесено " << finalDamage << " урона!" << endl;
        opponent->takeDamage(finalDamage);
    }


    void takeDamage(int damage) override {
        if (randomize(1, 100) <= 17) {   //Пассивная способность - Отражение
            cout << "Воин отразил атаку" << endl;
            damage = 0;
        }
        health -= damage;
        if (health < 0) 
            health = 0;
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
        if (element == "Вода" && opponentElement == "Огонь") return 1.25;
        if (element == "Огонь" && opponentElement == "Земля") return 1.25;
        if (element == "Земля" && opponentElement == "Воздух") return 1.25;
        if (element == "Воздух" && opponentElement == "Вода") return 1.25;
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
        cout << "Маг (" << element << ") - Здоровье: " << health << ", Урон: " << damage << ", Защита: " << defense << endl;
    }

    int getHealth() const override { return health; }
    int getDamage() const override { return damage; }
    int getDefense() const override { return defense; }
    string getClass() const override { return "Маг"; }
    string getElement() const override { return element; }

    void attack(Character* opponent) override {
        int finalDamage = ((damage - opponent->getDefense()) * 0.5);

        if (randomize(1, 100) <= 17) { //Пассивная способность мага - Поджег
            cout << "Пассивая способность мага сработала! Урон текущей атаки увеличен на 50%" << endl;
            finalDamage = static_cast<int>(finalDamage * 1.5);
        }

        finalDamage *= getElementDamageModifier(opponent->getElement());
        cout << "Маг Атакует! Нанесено " << finalDamage << " урона!" << endl;
        opponent->takeDamage(finalDamage);
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
        if (element == "Вода" && opponentElement == "Огонь") return 1.25;
        if (element == "Огонь" && opponentElement == "Земля") return 1.25;
        if (element == "Земля" && opponentElement == "Воздух") return 1.25;
        if (element == "Воздух" && opponentElement == "Вода") return 1.25;
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
        cout << "Разведчик (" << element << ") - Здоровье: " << health << ", Урон: " << damage << ", Защита: " << defense << endl;
    }

    int getHealth() const override { return health; }
    int getDamage() const override { return damage; }
    int getDefense() const override { return defense; }
    string getClass() const override { return "Разведчик"; }
    string getElement() const override { return element; }

    void attack(Character* opponent) override {
        int finalDamage = ((damage - opponent->getDefense()) * 0.5);
        finalDamage *= getElementDamageModifier(opponent->getElement());
        cout << "Разведчик атакует! Нанесено " << finalDamage << " урона!" << endl;
        opponent->takeDamage(finalDamage);
    }

  /*  void passiveAbility() override {
        if (randomize(1, 100) <= 17) {
            cout << "Scout stunned the opponent! They miss their next turn!" << endl;
        }
    }*/

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
        if (element == "Вода" && opponentElement == "Огонь") return 1.25;
        if (element == "Огонь" && opponentElement == "Земля") return 1.25;
        if (element == "Земля" && opponentElement == "Воздух") return 1.25;
        if (element == "Воздух" && opponentElement == "Вода") return 1.25;
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
        cout << "Лучник (" << element << ") - Здоровье: " << health << ", Урон: " << damage << ", Защита: " << defense << endl;
    }

    int getHealth() const override { return health; }
    int getDamage() const override { return damage; }
    int getDefense() const override { return defense; }
    string getClass() const override { return "Лучник"; }
    string getElement() const override { return element; }

    void attack(Character* opponent) override {
        int finalDamage = ((damage - opponent->getDefense()) * 0.5);
        finalDamage *= getElementDamageModifier(opponent->getElement());
        cout << "Лучник атакует! Нанесено " << finalDamage << " урона!" << endl;
        opponent->takeDamage(finalDamage);
    }

    /*void passiveAbility() override {
        if (randomize(1, 100) <= 17) {
            cout << "Archer applies Bleed effect!" << endl;
        }
    }*/

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
        if (element == "Вода" && opponentElement == "Огонь") return 1.25;
        if (element == "Огонь" && opponentElement == "Земля") return 1.25;
        if (element == "Земля" && opponentElement == "Воздух") return 1.25;
        if (element == "Воздух" && opponentElement == "Вода") return 1.25;
        return 1.0;
    }
};


int main() {
    Character* player1 = nullptr;
    Character* player2 = nullptr;
    string elementChoice, classChoice;

    // Игрок 1
    cout << "Игрок 1, выберите свой класс (Воин, Разведчик, Маг, Лучник): ";
    cin >> classChoice;
    cout << "Выбери элемент для своего класса (Огонь, Вода, Земля, Воздух): ";
    cin >> elementChoice;

    if (classChoice == "Воин") {
        player1 = new Warrior(elementChoice);
    } else if (classChoice == "Маг") {
        player1 = new Mage(elementChoice);
    } else if (classChoice == "Разведчик") {
        player1 = new Scout(elementChoice);
    } else if (classChoice == "Лучник") {
        player1 = new Archer(elementChoice);
    } else {
        cout << "Ошибка выбора" << endl;
        return 1;
    }

    //Игрок 2
    cout << "Игрок 2, выберите свой класс (Воин, Разведчик, Маг, Лучник): ";
    cin >> classChoice;
    cout << "Выбери элемент для своего класса (Огонь, Вода, Земля, Воздух): ";
    cin >> elementChoice;

    if (classChoice == "Воин") {
        player2 = new Warrior(elementChoice);
    } else if (classChoice == "Маг") {
        player2 = new Mage(elementChoice);
    } else if (classChoice == "Разведчик") {
        player2 = new Scout(elementChoice);
    } else if (classChoice == "Лучник") {
        player2 = new Archer(elementChoice);
    } else {
        cout << "Ошибка выбора" << endl;
        return 1;
    }

    cout << "====================================" << endl;

    //Вывод выбранных персонажей
    player1->display();
    player2->display();

    cout << "====================================" << endl;

    // Бой
    int phase = 1;
    while (player1->isAlive() && player2->isAlive()) {
        cout << "\n--- Фаза " << phase << " ---\n";
        
        // Ход
         
        cout << "1 Игрок " << endl;
        player1->attack(player2);
        if (player2->isAlive()) {
                cout << "2 Игрок " <<  endl;
                player2->attack(player1);
        }

        // Display health after the phase
         cout << "====================================" << endl;
        cout << "Игрок 1 Здоровье: " << player1->getHealth() << endl;
        cout << "Игрок 2 Здоровье: " << player2->getHealth() << endl;

        phase++;
    }

    // Determine winner
    if (player1->isAlive()) {
        cout << "====================================" << endl;
        cout << "Игрок 1 победил!" << endl;
        cout << "====================================" << endl;
    } else {
        cout << "====================================" << endl;
        cout << "Игрок 2 победил!" << endl;
        cout << "====================================" << endl;
    }


    // Cleanup
    delete player1;
    delete player2;

    return 0;
} 
