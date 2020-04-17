#include <iostream>
using namespace std;

enum eMonster
{
    LION,
    DRAGON,
    GIANT,
    MONSTER_COUNT
};

// class abstract Monster
class Monster
{
public:
    Monster() {};

    ~Monster() {};

    virtual void Appear() = 0;
};

// class monster Lion
class Lion : public Monster
{
public:
    Lion() {};

    ~Lion() {};

    virtual void Appear()
    {
        std::cout << "A Lion has appeared!" << endl;
    }
};

//class monster Dragon
class Dragon : public Monster
{
public:
    Dragon() {};

    ~Dragon() {};

    virtual void Appear()
    {
        cout << "A Dragon has appeared!" << endl;
    }
};

// class monster Giant
class Giant : public Monster
{
public:
    Giant() {};

    ~Giant() {};

    virtual void Appear()
    {
        cout << "A Giant has appeared!" << endl;
    }
};

class MonsterFactory
{
public:
    MonsterFactory() {};

    ~MonsterFactory() {};

    static Monster *createMonster(eMonster _MonsterID)
    {
        switch (_MonsterID)
        {
        case LION:
        {
            return new Lion();
            break;
        }
        case DRAGON:
        {
            return new Dragon();
            break;
        }
        case GIANT:
        {
            return new Giant();
            break;
        }
        default:
        {
            break;
        }
        }
    }
};

int main()
{
    Monster* m_Lion1 = MonsterFactory::createMonster(eMonster::LION);
    Monster* m_Dragon1 = MonsterFactory::createMonster(eMonster::DRAGON);
    Monster* m_Giant1 = MonsterFactory::createMonster(eMonster::GIANT);

    m_Lion1->Appear();
    m_Dragon1->Appear();
    m_Giant1->Appear();

    return 0;
}