#include <iostream>
#include <vector>
#include <memory>
#include <string>

//базовый класс травоядных
class Herbivore {
protected:
    int weight;
    bool isAlive;

public:
    Herbivore(int initWeight) : weight(initWeight), isAlive(true) {}
    virtual ~Herbivore() {}

    virtual void eatGrass() {
        if (isAlive) {
            weight += 10;
            std::cout << "Herbivore eats grass. New weight: " << weight << "\n";
        }
    }

    int getWeight() const { return weight; }
    bool isLife() const { return isAlive; }
    void setLife(bool alive) { isAlive = alive; }
};

//базовый класс хищников
class Carnivore {
protected:
    int power;

public:
    Carnivore(int initPower) : power(initPower) {}
    virtual ~Carnivore() {}

    virtual void eat(std::shared_ptr<Herbivore> herbivore) {
        if (!herbivore->isLife()) {
            std::cout << "Herbivore is already dead.\n";
            return;
        }

        if (power > herbivore->getWeight()) {
            herbivore->setLife(false);
            power += 10;
            std::cout << "Carnivore eats herbivore. New power: " << power << "\n";
        }
        else {
            power -= 10;
            std::cout << "Carnivore fails to hunt. New power: " << power << "\n";
        }
    }

    int getPower() const { return power; }
};

//бовый класс всеядного животного
class Omnivore : public Herbivore, public Carnivore {
public:
    Omnivore(int initWeight, int initPower)
        : Herbivore(initWeight), Carnivore(initPower) {}

    //всеядное животное может есть траву как травоядное
    void eatGrass() override {
        if (isAlive) {
            weight += 10;
            power += 5; //питание травой также немного усиливает всеядное животное
            std::cout << "Omnivore eats grass. New weight: " << weight
                << ", New power: " << power << "\n";
        }
    }

    //всеядное животное может охотиться как хищник
    void eat(std::shared_ptr<Herbivore> herbivore) override {
        if (!herbivore->isLife()) {
            std::cout << "Herbivore is already dead.\n";
            return;
        }

        if (power > herbivore->getWeight()) {
            herbivore->setLife(false);
            power += 10;
            std::cout << "Omnivore eats herbivore. New power: " << power << "\n";
        }
        else {
            power -= 10;
            std::cout << "Omnivore fails to hunt. New power: " << power << "\n";
        }
    }
};

//тестирование нового класса в мейне
int main() {
    //создаем всеядное животное
    std::shared_ptr<Omnivore> bear = std::make_shared<Omnivore>(100, 80);

    //создаем травоядных
    std::shared_ptr<Herbivore> wildebeest = std::make_shared<Wildebeest>();
    std::shared_ptr<Herbivore> bison = std::make_shared<Bison>();

    std::cout << "Testing Omnivore:\n";

    //питание травой
    bear->eatGrass();

    //попытка съесть антилопу гну
    bear->eat(wildebeest);

    //попытка съесть бизона
    bear->eat(bison);

    return 0;
}
