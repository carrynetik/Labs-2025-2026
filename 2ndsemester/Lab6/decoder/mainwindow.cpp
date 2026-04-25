#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "../shared/shield.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
    QStringList headers = {"Название", "Описание", "Коэф", "Тип"};
    ui->table_ok->setColumnCount(4); ui->table_ok->setHorizontalHeaderLabels(headers);
    ui->table_bad->setColumnCount(4); ui->table_bad->setHorizontalHeaderLabels(headers);
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::on_btn_process_clicked() {
    std::ifstream in("output.json");
    if (!in.is_open()) return;
    json data; in >> data; in.close();

    ui->table_ok->setRowCount(0); ui->table_bad->setRowCount(0);
    json ok_list = json::array(), bad_list = json::array();

    for (auto& item : data) {
        Shield s = Shield::from_json(item);
        if (s.isValid()) {
            int row = ui->table_ok->rowCount(); ui->table_ok->insertRow(row);
            ui->table_ok->setItem(row, 0, new QTableWidgetItem(s.title));
            ui->table_ok->setItem(row, 1, new QTableWidgetItem(s.description));
            ui->table_ok->setItem(row, 2, new QTableWidgetItem(QString::number(s.defense)));
            ui->table_ok->setItem(row, 3, new QTableWidgetItem(s.type));
            ok_list.push_back(item);
        } else {
            int row = ui->table_bad->rowCount(); ui->table_bad->insertRow(row);
            auto set_bad = [&](int col, QString val, bool err) {
                auto* i = new QTableWidgetItem(val);
                if (err) i->setBackground(Qt::red);
                ui->table_bad->setItem(row, col, i);
            };
            set_bad(0, s.title, s.title.isEmpty());
            set_bad(1, s.description, s.description.isEmpty());
            set_bad(2, QString::number(s.defense), s.defense <= 0);
            set_bad(3, s.type, s.type.isEmpty());
            bad_list.push_back(item);
        }
    }
    std::ofstream out_ok("valid.json"); out_ok << ok_list.dump(4);
    std::ofstream out_bad("invalid.json"); out_bad << bad_list.dump(4);
}