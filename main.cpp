#include <iostream>
#include <random>
#include <string>

using namespace std;

// Абстракция для характеристик персонажа
class Character {
public:
    virtual void display() = 0;
    virtual ~Character() {}
};

// Конкретные классы персонажей
class Warrior : public Character {
public:
    Warrior(int health, int damage, int defense) 
        : health(health), damage(damage), defense(defense) {}

    void display() override {
        cout << "Warrior - Health: " << health << ", Damage: " << damage << ", Defense: " << defense << endl;
    }

private:
    int health;
    int damage;
    int defense;
};

class Mage : public Character {
public:
    Mage(int health, int damage, int defense) 
        : health(health), damage(damage), defense(defense) {}

    void display() override {
        cout << "Mage - Health: " << health << ", Damage: " << damage << ", Defense: " << defense << endl;
    }

private:
    int health;
    int damage;
    int defense;
};

class Archer : public Character {
public:
    Archer(int health, int damage, int defense) 
        : health(health), damage(damage), defense(defense) {}

    void display() override {
        cout << "Archer - Health: " << health << ", Damage: " << damage << ", Defense: " << defense << endl;
    }

private:
    int health;
    int damage;
    int defense;
};

class Scout : public Character {
public:
    Scout(int health, int damage, int defense) 
        : health(health), damage(damage), defense(defense) {}

    void display() override {
        cout << "Scout - Health: " << health << ", Damage: " << damage << ", Defense: " << defense << endl;
    }

private:
    int health;
    int damage;
    int defense;
};

// Абстрактная фабрика
class CharacterFactory {
public:
    virtual Character* createCharacter(const string& type) = 0;
    virtual ~CharacterFactory() {}
};

// Конкретные фабрики для разных стихий
class EarthCharFactory : public CharacterFactory {
public:
    Character* createCharacter(const string& type) override {
        if (type == "Warrior")
            return new Warrior(randomize(100, 150), randomize(10, 20), randomize(5, 10));
        else if (type == "Mage")
            return new Mage(randomize(60, 100), randomize(20, 40), randomize(2, 5));
        else if (type == "Archer")
            return new Archer(randomize(80, 120), randomize(15, 25), randomize(3, 8));
        else if (type == "Scout")
            return new Scout(randomize(90, 130), randomize(10, 20), randomize(4, 9));
        return nullptr;
    }

private:
    int randomize(int min, int max) {
        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<> dis(min, max);
        return dis(gen);
    }
};

class WaterCharFactory : public CharacterFactory {
public:
    Character* createCharacter(const string& type) override {
        if (type == "Warrior")
            return new Warrior(randomize(110, 160), randomize(12, 22), randomize(6, 12));
        else if (type == "Mage")
            return new Mage(randomize(70, 110), randomize(25, 45), randomize(3, 6));
        else if (type == "Archer")
            return new Archer(randomize(90, 130), randomize(18, 28), randomize(4, 9));
        else if (type == "Scout")
            return new Scout(randomize(100, 140), randomize(12, 22), randomize(5, 10));
        return nullptr;
    }

private:
    int randomize(int min, int max) {
        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<> dis(min, max);
        return dis(gen);
    }
};

class AirCharFactory : public CharacterFactory {
public:
    Character* createCharacter(const string& type) override {
        if (type == "Warrior")
            return new Warrior(randomize(110, 160), randomize(12, 22), randomize(6, 12));
        else if (type == "Mage")
            return new Mage(randomize(70, 110), randomize(25, 45), randomize(3, 6));
        else if (type == "Archer")
            return new Archer(randomize(90, 130), randomize(18, 28), randomize(4, 9));
        else if (type == "Scout")
            return new Scout(randomize(100, 140), randomize(12, 22), randomize(5, 10));
        return nullptr;
    }

private:
    int randomize(int min, int max) {
        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<> dis(min, max);
        return dis(gen);
    }
};

class FireCharFactory : public CharacterFactory {
public:
    Character* createCharacter(const string& type) override {
        if (type == "Warrior")
            return new Warrior(randomize(110, 160), randomize(12, 22), randomize(6, 12));
        else if (type == "Mage")
            return new Mage(randomize(70, 110), randomize(25, 45), randomize(3, 6));
        else if (type == "Archer")
            return new Archer(randomize(90, 130), randomize(18, 28), randomize(4, 9));
        else if (type == "Scout")
            return new Scout(randomize(100, 140), randomize(12, 22), randomize(5, 10));
        return nullptr;
    }

private:
    int randomize(int min, int max) {
        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<> dis(min, max);
        return dis(gen);
    }
};

// Клиентский код
int main() {
    CharacterFactory* earthFactory = new FireCharFactory();
    CharacterFactory* waterFactory = new AirCharFactory();

    Character* earthWarrior = earthFactory->createCharacter("Warrior");
    Character* waterMage = waterFactory->createCharacter("Mage");

    earthWarrior->display();
    waterMage->display();

    delete earthWarrior;
    delete waterMage;
    delete earthFactory;
    delete waterFactory;

    return 0;
}
