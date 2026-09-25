#include "card.h"
#include "ui_card.h"
#include "mainwindow.h"
#include "ui_mainwindow.h"

card::card(QWidget *parent) : QWidget(parent), ui(new Ui::card) {
    ui->setupUi(this);
}

card::card(NPC* ptr, MainWindow* mw, Ui::MainWindow* mw_ui, QListWidgetItem* item)
    : ui(new Ui::card)
{
    ui->setupUi(this);
    m_mainWindow = mw;
    m_mainUI = mw_ui;
    m_npc = ptr;
    m_item = item;

    m_npc->Craft(ui);
    m_mainWindow->setEnabled(false); // Блокируем главное окно
}

card::~card() {
    m_mainWindow->setEnabled(true);
    delete ui;
}

void card::on_cancel_pressed() {
    m_mainWindow->setEnabled(true);
    this->close();
}

void card::on_print_pressed() {
    // Удаляем из вектора
    int row = m_mainUI->list->row(m_item);
    m_mainWindow->entities.erase(m_mainWindow->entities.begin() + row);
    
    // Удаляем с экрана и из памяти
    delete m_npc;
    m_mainUI->list->takeItem(row);
    delete m_item;
    
    m_mainWindow->setEnabled(true);
    this->close();
}