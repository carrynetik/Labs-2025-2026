#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFile>
#include <QFileDialog>
#include <QTextStream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

bool writeJson(const Shield& shield, QString& errorMessage)
{
    json database = json::array();

    QFile inputFile("output.json");

    if (inputFile.exists()) {
        if (!inputFile.open(QIODevice::ReadOnly | QIODevice::Text)) {
            errorMessage = "Не удалось открыть существующий output.json";
            return false;
        }

        QByteArray contents = inputFile.readAll();
        inputFile.close();

        if (!contents.trimmed().isEmpty()) {
            try {
                database = json::parse(contents.toStdString());
            }
            catch (...) {
                errorMessage = "Файл output.json повреждён";
                return false;
            }

            if (!database.is_array()) {
                errorMessage = "В output.json должен находиться массив объектов";
                return false;
            }
        }
    }

    database.push_back(shield.to_json());

    QFile outputFile("output.json");

    if (!outputFile.open(QIODevice::WriteOnly |
                         QIODevice::Text |
                         QIODevice::Truncate)) {
        errorMessage = "Не удалось записать данные в output.json";
        return false;
    }

    QByteArray result =
        QByteArray::fromStdString(database.dump(4));

    if (outputFile.write(result) == -1) {
        outputFile.close();
        errorMessage = "Ошибка во время записи output.json";
        return false;
    }

    outputFile.close();
    return true;
}

void MainWindow::on_btn_add_clicked()
{
    QString title = ui->line_name->text().trimmed();
    QString description = ui->line_desc->text().trimmed();
    QString coefficientText =
        ui->line_coef->text().trimmed();

    coefficientText.replace(",", ".");

    QString protectionType =
        ui->line_type->text().trimmed();

    if (title.isEmpty()) {
        ui->label_status->setText(
            "Ошибка: введите название"
            );
        return;
    }

    if (description.isEmpty()) {
        ui->label_status->setText(
            "Ошибка: введите описание"
            );
        return;
    }

    bool coefficientIsCorrect = false;

    double coefficient =
        coefficientText.toDouble(&coefficientIsCorrect);

    if (!coefficientIsCorrect || coefficient <= 0) {
        ui->label_status->setText(
            "Ошибка: коэффициент должен быть числом больше нуля"
            );
        return;
    }

    if (protectionType.isEmpty()) {
        ui->label_status->setText(
            "Ошибка: введите тип защиты"
            );
        return;
    }

    Shield shield;

    shield.title = title;
    shield.description = description;
    shield.defense = coefficient;
    shield.type = protectionType;

    QString errorMessage;

    if (!writeJson(shield, errorMessage)) {
        ui->label_status->setText(
            "Ошибка: " + errorMessage
            );
        return;
    }

    ui->label_status->setText(
        "Щит успешно добавлен в output.json"
        );

    ui->line_name->clear();
    ui->line_desc->clear();
    ui->line_coef->clear();
    ui->line_type->clear();
}

void MainWindow::on_btn_txt_clicked()
{
    QString path = QFileDialog::getOpenFileName(
        this,
        "Выберите TXT-файл",
        "",
        "Текстовые файлы (*.txt)"
        );

    if (path.isEmpty()) {
        ui->label_status->setText(
            "Файл не выбран"
            );
        return;
    }

    QFile file(path);

    if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        ui->label_status->setText(
            "Ошибка: не удалось открыть TXT-файл"
            );
        return;
    }

    QTextStream input(&file);
    QString line = input.readLine();
    file.close();

    if (line.trimmed().isEmpty()) {
        ui->label_status->setText(
            "Ошибка: TXT-файл пустой"
            );
        return;
    }

    QStringList fields = line.split("/");

    if (fields.size() != 4) {
        ui->label_status->setText(
            "Ошибка: в TXT должно быть 4 поля через символ /"
            );
        return;
    }

    QString title = fields[0].trimmed();
    QString description = fields[1].trimmed();
    QString coefficientText = fields[2].trimmed();
    QString protectionType = fields[3].trimmed();

    coefficientText.replace(",", ".");

    bool coefficientIsCorrect = false;
    coefficientText.toDouble(&coefficientIsCorrect);

    if (title.isEmpty() ||
        description.isEmpty() ||
        coefficientText.isEmpty() ||
        protectionType.isEmpty()) {
        ui->label_status->setText(
            "Ошибка: в TXT есть пустое поле"
            );
        return;
    }

    if (!coefficientIsCorrect) {
        ui->label_status->setText(
            "Ошибка: коэффициент в TXT записан неправильно"
            );
        return;
    }

    ui->line_name->setText(title);
    ui->line_desc->setText(description);
    ui->line_coef->setText(coefficientText);
    ui->line_type->setText(protectionType);

    ui->label_status->setText(
        "Данные загружены в форму. Их можно изменить"
        );
}
