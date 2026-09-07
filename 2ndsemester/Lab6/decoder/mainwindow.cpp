#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "../shared/shield.h"

#include <QFile>
#include <QFileDialog>
#include <QFileInfo>
#include <QMessageBox>
#include <QTableWidgetItem>

#include <algorithm>
#include <vector>

struct CheckedShield
{
    Shield shield;
    json originalObject;

    bool titleCorrect = false;
    bool descriptionCorrect = false;
    bool coefficientCorrect = false;
    bool typeCorrect = false;

    QString coefficientText;

    bool isCorrect() const
    {
        return titleCorrect &&
               descriptionCorrect &&
               coefficientCorrect &&
               typeCorrect;
    }
};

QString jsonValueToText(const json& value)
{
    if (value.is_string()) {
        return QString::fromStdString(
            value.get<std::string>()
        );
    }

    if (value.is_null()) {
        return "";
    }

    return QString::fromStdString(value.dump());
}

CheckedShield checkObject(const json& object)
{
    CheckedShield checked;
    checked.originalObject = object;

    if (!object.is_object()) {
        checked.shield.title = jsonValueToText(object);
        return checked;
    }

    if (object.contains("name")) {
        const json& value = object["name"];

        checked.shield.title = jsonValueToText(value);

        checked.titleCorrect =
            value.is_string() &&
            !checked.shield.title.trimmed().isEmpty();
    }

    if (object.contains("desc")) {
        const json& value = object["desc"];

        checked.shield.description =
            jsonValueToText(value);

        checked.descriptionCorrect =
            value.is_string() &&
            !checked.shield.description.trimmed().isEmpty();
    }

    if (object.contains("coef")) {
        const json& value = object["coef"];

        checked.coefficientText =
            jsonValueToText(value);

        if (value.is_number()) {
            checked.shield.defense =
                value.get<double>();

            checked.coefficientCorrect =
                checked.shield.defense > 0;

            checked.coefficientText =
                QString::number(checked.shield.defense);
        }
    }

    if (object.contains("type")) {
        const json& value = object["type"];

        checked.shield.type = jsonValueToText(value);

        checked.typeCorrect =
            value.is_string() &&
            !checked.shield.type.trimmed().isEmpty();
    }

    return checked;
}

bool saveJsonFile(
    const QString& path,
    const json& contents
)
{
    QFile file(path);

    if (!file.open(
            QIODevice::WriteOnly |
            QIODevice::Text |
            QIODevice::Truncate)) {
        return false;
    }

    QByteArray result =
        QByteArray::fromStdString(contents.dump(4));

    bool written = file.write(result) != -1;
    file.close();

    return written;
}

void addCorrectRow(
    QTableWidget* table,
    const CheckedShield& checked
)
{
    int row = table->rowCount();
    table->insertRow(row);

    table->setItem(
        row,
        0,
        new QTableWidgetItem(checked.shield.title)
    );

    table->setItem(
        row,
        1,
        new QTableWidgetItem(
            checked.shield.description
        )
    );

    table->setItem(
        row,
        2,
        new QTableWidgetItem(
            QString::number(checked.shield.defense)
        )
    );

    table->setItem(
        row,
        3,
        new QTableWidgetItem(checked.shield.type)
    );
}

void addIncorrectRow(
    QTableWidget* table,
    const CheckedShield& checked
)
{
    int row = table->rowCount();
    table->insertRow(row);

    QTableWidgetItem* titleItem =
        new QTableWidgetItem(checked.shield.title);

    QTableWidgetItem* descriptionItem =
        new QTableWidgetItem(
            checked.shield.description
        );

    QTableWidgetItem* coefficientItem =
        new QTableWidgetItem(
            checked.coefficientText
        );

    QTableWidgetItem* typeItem =
        new QTableWidgetItem(checked.shield.type);

    if (!checked.titleCorrect) {
        titleItem->setBackground(Qt::red);
    }

    if (!checked.descriptionCorrect) {
        descriptionItem->setBackground(Qt::red);
    }

    if (!checked.coefficientCorrect) {
        coefficientItem->setBackground(Qt::red);
    }

    if (!checked.typeCorrect) {
        typeItem->setBackground(Qt::red);
    }

    table->setItem(row, 0, titleItem);
    table->setItem(row, 1, descriptionItem);
    table->setItem(row, 2, coefficientItem);
    table->setItem(row, 3, typeItem);
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QStringList headers = {
        "Название",
        "Описание",
        "Коэффициент",
        "Тип защиты"
    };

    ui->table_ok->setColumnCount(4);
    ui->table_ok->setHorizontalHeaderLabels(headers);

    ui->table_bad->setColumnCount(4);
    ui->table_bad->setHorizontalHeaderLabels(headers);

    ui->table_ok->setSortingEnabled(false);
    ui->table_bad->setSortingEnabled(false);

    ui->btn_process->setText("Загрузить JSON");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_btn_process_clicked()
{
    QString path = QFileDialog::getOpenFileName(
        this,
        "Выберите JSON-файл",
        "",
        "JSON-файлы (*.json)"
    );

    if (path.isEmpty()) {
        return;
    }

    QFile inputFile(path);

    if (!inputFile.open(
            QIODevice::ReadOnly |
            QIODevice::Text)) {
        QMessageBox::warning(
            this,
            "Ошибка",
            "Не удалось открыть выбранный файл"
        );
        return;
    }

    QByteArray contents = inputFile.readAll();
    inputFile.close();

    json data;

    try {
        data = json::parse(contents.toStdString());
    }
    catch (...) {
        QMessageBox::warning(
            this,
            "Ошибка",
            "Выбранный файл содержит повреждённый JSON"
        );
        return;
    }

    if (!data.is_array()) {
        QMessageBox::warning(
            this,
            "Ошибка",
            "В JSON должен находиться массив объектов"
        );
        return;
    }

    ui->table_ok->setRowCount(0);
    ui->table_bad->setRowCount(0);

    std::vector<CheckedShield> correctShields;
    std::vector<CheckedShield> incorrectShields;

    json correctJson = json::array();
    json incorrectJson = json::array();

    for (const json& object : data) {
        CheckedShield checked = checkObject(object);

        if (checked.isCorrect()) {
            correctShields.push_back(checked);
        }
        else {
            incorrectShields.push_back(checked);
        }
    }

    std::sort(
        correctShields.begin(),
        correctShields.end(),
        [](const CheckedShield& first,
           const CheckedShield& second) {
            return QString::compare(
                first.shield.title,
                second.shield.title,
                Qt::CaseInsensitive
            ) > 0;
        }
    );

    for (const CheckedShield& checked :
         correctShields) {
        addCorrectRow(ui->table_ok, checked);
        correctJson.push_back(
            checked.originalObject
        );
    }

    for (const CheckedShield& checked :
         incorrectShields) {
        addIncorrectRow(ui->table_bad, checked);
        incorrectJson.push_back(
            checked.originalObject
        );
    }

    QString directory =
        QFileInfo(path).absolutePath();

    QString validPath =
        directory + "/valid.json";

    QString invalidPath =
        directory + "/invalid.json";

    bool validSaved =
        saveJsonFile(validPath, correctJson);

    bool invalidSaved =
        saveJsonFile(invalidPath, incorrectJson);

    ui->table_ok->resizeColumnsToContents();
    ui->table_bad->resizeColumnsToContents();

    if (!validSaved || !invalidSaved) {
        QMessageBox::warning(
            this,
            "Ошибка",
            "Таблицы заполнены, но выходные файлы сохранить не удалось"
        );
        return;
    }

    QMessageBox::information(
        this,
        "Готово",
        "Корректных объектов: " +
            QString::number(correctShields.size()) +
            "\nОшибочных объектов: " +
            QString::number(incorrectShields.size()) +
            "\n\nФайлы valid.json и invalid.json "
            "созданы рядом с исходным JSON."
    );
}