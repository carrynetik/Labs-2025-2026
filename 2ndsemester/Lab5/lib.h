#pragma once
#include <QString>
#include <vector>

// Предварительное объявление, чтобы не было ошибок (вместо инклуда)
namespace Ui { class card; }

struct ArmorStats {
    unsigned int head;
    unsigned int body;
    unsigned int legs;
    ArmorStats();
};

class NPC {
protected:
    QString m_name;
    unsigned int m_hp;
    ArmorStats m_armor;
public:
    virtual void Craft(Ui::card* ui) = 0;
    virtual QString getListItem() = 0;
    
    NPC() = default;
    virtual ~NPC() = default;

    QString getName() { return m_name; }
    unsigned int getHp() { return m_hp; }
    ArmorStats getArmor() { return m_armor; }
};

class Mage : public NPC {
private:
    QString m_element;
    unsigned int m_mana;
public:
    Mage() = default;
    Mage(QString name, QString element, unsigned int mana, unsigned int hp, ArmorStats armor);
    void Craft(Ui::card* ui) override;
    QString getListItem() override;

    QString getElement() { return m_element; }
    unsigned int getMana() { return m_mana; }
};

class Monster : public NPC {
private:
    QString m_rarity;
    unsigned int m_damage;
public:
    Monster() = default;
    Monster(QString name, QString rarity, unsigned int dmg, unsigned int hp, ArmorStats armor);
    void Craft(Ui::card* ui) override;
    QString getListItem() override;

    QString getRarity() { return m_rarity; }
    unsigned int getDamage() { return m_damage; }
};