#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QFileDialog>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
}

MainWindow::~MainWindow() { delete ui; }

void write_json(const Shield& s) {
    json db;
    std::ifstream in("output.json");
    if (in.is_open()) {
        try { in >> db; } catch(...) { db = json::array(); }
        in.close();
    }
    if (!db.is_array()) db = json::array();
    db.push_back(s.to_json());
    std::ofstream out("output.json");
    out << db.dump(4);
}

void MainWindow::on_btn_add_clicked() {
    Shield s;
    s.title = ui->line_name->text();
    s.description = ui->line_desc->text();
    s.defense = ui->line_coef->text().replace(",", ".").toDouble();
    s.type = ui->line_type->text();
    
    if (s.title.isEmpty()) {
        ui->label_status->setText("Ошибка: введите название");
        return;
    }
    write_json(s);
    ui->label_status->setText("Успешно добавлено!");
}

void MainWindow::on_btn_txt_clicked() {
    QString path = QFileDialog::getOpenFileName(this, "Выбор TXT", "", "*.txt");
    if (path.isEmpty()) return;
    std::ifstream f(path.toStdString());
    std::string line;
    while (std::getline(f, line)) {
        QStringList p = QString::fromStdString(line).split("/");
        if (p.size() == 4) {
            Shield s;
            s.title = p[0]; s.description = p[1];
            s.defense = p[2].replace(",", ".").toDouble(); s.type = p[3];
            write_json(s);
        }
    }
    ui->label_status->setText("Импорт завершен");
}