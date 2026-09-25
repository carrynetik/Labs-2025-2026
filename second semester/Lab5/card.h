#ifndef CARD_H
#define CARD_H

#include <QWidget>
#include <QListWidgetItem>
#include "lib.h"

class MainWindow;
namespace Ui { class MainWindow; }

namespace Ui {
class card;
}

class card : public QWidget
{
    Q_OBJECT
public:
    explicit card(QWidget *parent = nullptr);
    explicit card(NPC* ptr, MainWindow* mw, Ui::MainWindow* mw_ui, QListWidgetItem* item);
    ~card();

private slots:
    void on_cancel_pressed();
    void on_print_pressed();

private:
    Ui::card *ui;
    MainWindow* m_mainWindow = nullptr;
    Ui::MainWindow* m_mainUI = nullptr;
    NPC* m_npc = nullptr;
    QListWidgetItem* m_item = nullptr;
};

#endif // CARD_H