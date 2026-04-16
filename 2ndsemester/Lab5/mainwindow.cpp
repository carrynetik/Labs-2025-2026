#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "card.h"
#include <QFileDialog>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow() {
    for (NPC* npc : entities) {
        delete npc;
    }
    delete ui;
}

void MainWindow::on_load_pressed() {
    ui->load_error->setText("");

    QString filePath = QFileDialog::getOpenFileName(this, "Выберите файл", "", "Text Files (*.txt)");
    if (filePath.isEmpty()) {
        ui->load_error->setText("Файл не выбран");
        return;
    }

    QFile file(filePath);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        ui->load_error->setText("Не удалось открыть файл");
        return;
    }

    // Очищаем старые данные при новой загрузке
    for (NPC* npc : entities) delete npc;
    entities.clear();
    ui->list->clear();

    QTextStream in(&file);
    int lineNum = 0;

    while (!in.atEnd()) {
        QString line = in.readLine().trimmed();
        lineNum++;
        if (line.isEmpty()) continue;

        // Разбиваем строку по запятым
        QStringList parts = line.split(QRegularExpression(",\\s*"));
        
        if (parts.size() < 8) {
            ui->load_error->setText("Ошибка в формате на строке: " + QString::number(lineNum));
            return;
        }

        int code = parts[0].toInt();
        QString name = parts[1];
        QString typeInfo = parts[2]; // Стихия или Редкость
        unsigned int val = parts[3].toUInt(); // Мана или Урон
        unsigned int hp = parts[4].toUInt();
        
        ArmorStats armor;
        armor.head = parts[5].toUInt();
        armor.body = parts[6].toUInt();
        armor.legs = parts[7].toUInt();

        if (code == 0) {
            entities.push_back(new Mage(name, typeInfo, val, hp, armor));
        } else if (code == 1) {
            entities.push_back(new Monster(name, typeInfo, val, hp, armor));
        } else {
            ui->load_error->setText("Неизвестный код НПС на строке: " + QString::number(lineNum));
            return;
        }
    }
    file.close();

    // Заполняем список на экране
    for (NPC* npc : entities) {
        ui->list->addItem(npc->getListItem());
    }
}

void MainWindow::on_list_itemDoubleClicked(QListWidgetItem *item) {
    int row = ui->list->row(item);
    card* craftWindow = new card(entities[row], this, ui, item);
    craftWindow->setAttribute(Qt::WA_DeleteOnClose);
    craftWindow->show();
}