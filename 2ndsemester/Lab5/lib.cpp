#include "lib.h"
#include "ui_card.h"

ArmorStats::ArmorStats() {
    head = 0;
    body = 0;
    legs = 0;
}

// === МАГ ===
Mage::Mage(QString name, QString element, unsigned int mana, unsigned int hp, ArmorStats armor) {
    m_name = name;
    m_element = element;
    m_mana = mana;
    m_hp = hp;
    m_armor = armor;
}

QString Mage::getListItem() {
    return QString("%1 (Маг: %2) Мана: %3 ХП: %4 Броня: <%5/%6/%7>")
        .arg(m_name, m_element).arg(m_mana).arg(m_hp)
        .arg(m_armor.head).arg(m_armor.body).arg(m_armor.legs);
}

void Mage::Craft(Ui::card* ui) {
    ui->pic->setText("[ ФОТО МАГА ]");
    ui->pic->setStyleSheet("background-color: lightblue; font-weight: bold;");
    
    ui->name->setText(this->getName());
    ui->name->setStyleSheet("color: black;");

    QString el = this->getElement();
    ui->magician_ability->setText(el);
    if (el == "земля") ui->magician_ability->setStyleSheet("color: rgb(139, 69, 19);"); 
    if (el == "вода") ui->magician_ability->setStyleSheet("color: rgb(0, 191, 255);");
    if (el == "огонь") ui->magician_ability->setStyleSheet("color: rgb(255, 69, 0);");

    ui->magician_health->setText("ХП: " + QString::number(this->getHp()));
    ui->magician_mana->setText("Мана: " + QString::number(this->getMana()));

    ui->enemy_armor->setText("");
    ui->enemy_health->setText("");
}

// === ВРАГ ===
Monster::Monster(QString name, QString rarity, unsigned int dmg, unsigned int hp, ArmorStats armor) {
    m_name = name;
    m_rarity = rarity;
    m_damage = dmg;
    m_hp = hp;
    m_armor = armor;
}

QString Monster::getListItem() {
    return QString("%1 (Враг: %2) Урон: %3 ХП: %4 Броня: <%5/%6/%7>")
        .arg(m_name, m_rarity).arg(m_damage).arg(m_hp)
        .arg(m_armor.head).arg(m_armor.body).arg(m_armor.legs);
}

void Monster::Craft(Ui::card* ui) {
    ui->pic->setText("[ ФОТО ВРАГА ]");
    ui->pic->setStyleSheet("background-color: lightcoral; font-weight: bold;");
    
    ui->name->setText(this->getName());
    
    QString rar = this->getRarity();
    if (rar == "Обычный") ui->name->setStyleSheet("color: rgb(34, 139, 34);");
    if (rar == "Редкий") ui->name->setStyleSheet("color: rgb(0, 0, 205);");
    if (rar == "Легенда") ui->name->setStyleSheet("color: rgb(218, 165, 32);");

    ui->enemy_health->setText("ХП: " + QString::number(this->getHp()));
    
    QString arm = QString("Броня: <%1/%2/%3>")
        .arg(m_armor.head).arg(m_armor.body).arg(m_armor.legs);
    ui->enemy_armor->setText(arm);

    ui->magician_mana->setText("");
    ui->magician_ability->setText("");
    ui->magician_health->setText("");
}