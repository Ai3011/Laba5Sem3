#include <iostream>
#include <random>
#include <string>
#include <ctime>

using namespace std;

random_device rd;
    mt19937 gen(rd());

int randomize(int min, int max) {
    uniform_int_distribution<> dis(min, max);
    return dis(gen);
}

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
        if (randomize(1, 100) <= 17) {   //Пассивная способность - Парирование
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
        finalDamage *= getElementDamageModifier(opponent->getElement());
        cout << "Маг атакует! Нанесено " << finalDamage << " урона!" << endl;
        opponent->takeDamage(finalDamage);

        // Проверка на активацию пассивной способности с шансом 17%
        if (randomize(1, 100) <= 17) {
            int healAmount = static_cast<int>(finalDamage * 0.25);  // Восстановление 25% от урона
            health += healAmount;
            cout << "Пассивная способность мага сработала при атаке! Восстановлено " << healAmount << " здоровья!" << endl;
        }
    }

    void takeDamage(int damage) override {
        health -= damage;

        // Проверка на активацию пассивной способности с шансом 17% в случае получения урона
        if (randomize(1, 100) <= 17) {
            int healAmount = static_cast<int>(damage * 0.25);  // Восстановление 25% от полученного урона
            health += healAmount;
            cout << "Пассивная способность мага сработала при защите! Восстановлено " << healAmount << " здоровья!" << endl;
        }
        
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

    void takeDamage(int damage) override {
         // Проверка, что урон может убить Разведчика
    if (damage >= health) {
        // Если урон может убить, то проверяем шанс увернуться
        if (randomize(1, 100) <= 50) {
            cout << "Разведчик уклоняется от смертельной атаки!" << endl;
            return; 
        }
    }

    // Если уклонение не произошло, Разведчик получает урон
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

        if (randomize(1, 100) <= 17) { //Пассивная способность Стрелка - Меткий выстрел
            cout << "Пассивая способность лучника сработала! Урон текущей атаки увеличен на 50%" << endl;
            finalDamage = static_cast<int>(finalDamage * 1.5);
        }

        finalDamage *= getElementDamageModifier(opponent->getElement());
        cout << "Лучник атакует! Нанесено " << finalDamage << " урона!" << endl;
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


// Интерфейс Абстрактной фабрики
class AbstractFactory {
public:
    virtual Character* createWarrior() = 0;
    virtual Character* createMage() = 0;
    virtual Character* createScout() = 0;
    virtual Character* createArcher() = 0;
    virtual ~AbstractFactory() {}
};

// Фабрика для огненного элемента
class FireFactory : public AbstractFactory {
public:
    Character* createWarrior() override {
        return new Warrior("Огонь");
    }

    Character* createMage() override {
        return new Mage("Огонь");
    }

    Character* createScout() override {
        return new Scout("Огонь");
    }

    Character* createArcher() override {
        return new Archer("Огонь");
    }
};

// Фабрика для водного элемента
class WaterFactory : public AbstractFactory {
public:
    Character* createWarrior() override {
        return new Warrior("Вода");
    }

    Character* createMage() override {
        return new Mage("Вода");
    }

    Character* createScout() override {
        return new Scout("Вода");
    }

    Character* createArcher() override {
        return new Archer("Вода");
    }
};

// Фабрика для земного элемента
class EarthFactory : public AbstractFactory {
public:
    Character* createWarrior() override {
        return new Warrior("Земля");
    }

    Character* createMage() override {
        return new Mage("Земля");
    }

    Character* createScout() override {
        return new Scout("Земля");
    }

    Character* createArcher() override {
        return new Archer("Земля");
    }
};

// Фабрика для воздушного элемента
class AirFactory : public AbstractFactory {
public:
    Character* createWarrior() override {
        return new Warrior("Воздух");
    }

    Character* createMage() override {
        return new Mage("Воздух");
    }

    Character* createScout() override {
        return new Scout("Воздух");
    }

    Character* createArcher() override {
        return new Archer("Воздух");
    }
};

int main() {
    Character* player1 = nullptr;
    Character* player2 = nullptr;
    string elementChoice, classChoice;
    AbstractFactory* factory = nullptr;

    cout << "Выбери элемент для своего класса (Огонь, Вода, Земля, Воздух): ";
    cin >> elementChoice;

    // Создание нужной фабрики для игрока 1
    if (elementChoice == "Огонь") {
        factory = new FireFactory();
    } else if (elementChoice == "Вода") {
        factory = new WaterFactory();
    } else if (elementChoice == "Земля") {
        factory = new EarthFactory();
    } else if (elementChoice == "Воздух") {
        factory = new AirFactory();
    } else {
        cout << "Ошибка выбора элемента" << endl;
        return 1;
    }

     // Игрок 1
    cout << "Игрок 1, выберите свой класс (Воин, Разведчик, Маг, Лучник): ";
    cin >> classChoice;

    // Создание персонажа игрока 1
    if (classChoice == "Воин") {
        player1 = factory->createWarrior();
    } else if (classChoice == "Маг") {
        player1 = factory->createMage();
    } else if (classChoice == "Разведчик") {
        player1 = factory->createScout();
    } else if (classChoice == "Лучник") {
        player1 = factory->createArcher();
    } else {
        cout << "Ошибка выбора класса" << endl;
        delete factory;
        return 1;
    }

    delete factory;

    cout << "Выбери элемент для своего класса (Огонь, Вода, Земля, Воздух): ";
    cin >> elementChoice;

    // Создание нужной фабрики для игрока 2
    if (elementChoice == "Огонь") {
        factory = new FireFactory();
    } else if (elementChoice == "Вода") {
        factory = new WaterFactory();
    } else if (elementChoice == "Земля") {
        factory = new EarthFactory();
    } else if (elementChoice == "Воздух") {
        factory = new AirFactory();
    } else {
        cout << "Ошибка выбора элемента" << endl;
        return 1;
    }

     // Игрок 2
    cout << "Игрок 2, выберите свой класс (Воин, Разведчик, Маг, Лучник): ";
    cin >> classChoice;

    // Создание персонажа игрока 2
    if (classChoice == "Воин") {
        player2 = factory->createWarrior();
    } else if (classChoice == "Маг") {
        player2 = factory->createMage();
    } else if (classChoice == "Разведчик") {
        player2 = factory->createScout();
    } else if (classChoice == "Лучник") {
        player2 = factory->createArcher();
    } else {
        cout << "Ошибка выбора класса" << endl;
        delete factory;
        return 1;
    }

    delete factory;

    cout << "====================================" << endl;

    // Вывод выбранных персонажей
    player1->display();
    player2->display();

    cout << "====================================" << endl;

    // Случайный выбор первого игрока
    bool isPlayer1Turn = randomize(0, 1);
    cout << "Первый ход у Игрока " << (isPlayer1Turn ? "1" : "2") << "!" << endl;

    // Бой
    int phase = 1;
    while (player1->isAlive() && player2->isAlive()) {
        cout << "\n--- Фаза " << phase << " ---\n";

        if (isPlayer1Turn) {
            cout << "Ход Игрока 1\n";
            player1->attack(player2);
        } else {
            cout << "Ход Игрока 2\n";
            player2->attack(player1);
        }

        // Проверяем, жив ли противник, если нет — завершаем бой
        if (!player1->isAlive() || !player2->isAlive()) {
            break;
        }

        // Смена хода
        isPlayer1Turn = !isPlayer1Turn;

        // Вывод здоровья игроков после фазы
        cout << "====================================" << endl;
        player1->display();
        player2->display();
        phase++;
    }

    // Определение победителя
    if (player1->isAlive()) {
        cout << "====================================" << endl;
        cout << "Игрок 1 победил!" << endl;
        cout << "====================================" << endl;
    } else {
        cout << "====================================" << endl;
        cout << "Игрок 2 победил!" << endl;
        cout << "====================================" << endl;
    }

    // Удаление объектов
    delete player1;
    delete player2;

    return 0;
}


/*int main() {
    vector<Character*> warriors;
    vector<Character*> mages;
    vector<Character*> scouts;
    vector<Character*> archers;
    
    AbstractFactory* factory = nullptr;

    vector<string> elements = {"Огонь", "Вода", "Земля", "Воздух"};
    vector<string> classes = {"Воин", "Маг", "Разведчик", "Лучник"};

    // Создаем по 20 персонажей каждого класса и стихии
    for (const string& element : elements) {
        if (element == "Огонь") {
            factory = new FireFactory();
        } else if (element == "Вода") {
            factory = new WaterFactory();
        } else if (element == "Земля") {
            factory = new EarthFactory();
        } else if (element == "Воздух") {
            factory = new AirFactory();
        }

        // Создаем 20 персонажей каждого класса для каждого элемента
        for (int i = 0; i < 20; ++i) {
            warriors.push_back(factory->createWarrior());
            mages.push_back(factory->createMage());
            scouts.push_back(factory->createScout());
            archers.push_back(factory->createArcher());
        }

        delete factory;
    }

    // Пример отображения созданных персонажей
    cout << "Все воины (20 каждого элемента):\n";
    for (auto& warrior : warriors) {
        warrior->display();
    }

    cout << "Все маги (20 каждого элемента):\n";
    for (auto& mage : mages) {
        mage->display();
    }

    cout << "Все разведчики (20 каждого элемента):\n";
    for (auto& scout : scouts) {
        scout->display();
    }

    cout << "Все лучники (20 каждого элемента):\n";
    for (auto& archer : archers) {
        archer->display();
    }

    // Очистка памяти
    for (auto& warrior : warriors) {
        delete warrior;
    }
    for (auto& mage : mages) {
        delete mage;
    }
    for (auto& scout : scouts) {
        delete scout;
    }
    for (auto& archer : archers) {
        delete archer;
    }

    return 0;
}
*/
