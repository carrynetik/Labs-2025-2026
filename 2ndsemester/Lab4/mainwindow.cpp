#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QRegularExpressionValidator>
#include <QRegularExpression>
#include "book.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QRegularExpression rxAuthor("[А-Я][а-я]{0,} [А-Я]{1,2}");
    ui->author->setValidator(new QRegularExpressionValidator(rxAuthor, this));

    QRegularExpression rxName("\"[а-я А-Я?,.()*\"-+=0-9]{0,}\"");
    ui->name->setValidator(new QRegularExpressionValidator(rxName, this));

    QRegularExpression rxCode("[0-9]{1,3}-[0-9]{1,5}");
    ui->code->setValidator(new QRegularExpressionValidator(rxCode, this));

    QRegularExpression rxContents("[1-9][0-9]{0,}/[1-9][0-9]{0,}");
    ui->contents->setValidator(new QRegularExpressionValidator(rxContents, this));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_author_textEdited() { ui->author_error->setText(""); }
void MainWindow::on_name_textEdited() { ui->name_error->setText(""); }
void MainWindow::on_code_textEdited() { ui->code_error->setText(""); }
void MainWindow::on_contents_textEdited() { ui->contents_error->setText(""); }
void MainWindow::on_type_paper_clicked() { ui->type_error->setText(""); }
void MainWindow::on_type_digital_clicked() { ui->type_error->setText(""); }

void MainWindow::on_discard_pressed()
{
    ui->author->clear();
    ui->name->clear();
    ui->code->clear();
    ui->contents->clear();

    ui->type_paper->setAutoExclusive(false);
    ui->type_paper->setChecked(false);
    ui->type_paper->setAutoExclusive(true);
    
    ui->type_digital->setAutoExclusive(false);
    ui->type_digital->setChecked(false);
    ui->type_digital->setAutoExclusive(true);


    ui->genre_detective->setChecked(false);
    ui->genre_fiction->setChecked(false);
    ui->genre_novel->setChecked(false);

    ui->author_error->setText("");
    ui->name_error->setText("");
    ui->code_error->setText("");
    ui->contents_error->setText("");
    ui->type_error->setText("");
}

void MainWindow::on_save_pressed()
{
    bool hasError = false;

    QString textAuthor = ui->author->text();
    if (textAuthor.isEmpty()) {
        ui->author_error->setText("Поле пустое");
        hasError = true;
    } else if (!textAuthor.contains(" ")) {
        ui->author_error->setText("Нужен пробел перед инициалами");
        hasError = true;
    }
    QString textName = ui->name->text();
    if (textName.isEmpty()) {
        ui->name_error->setText("Поле пустое");
        hasError = true;
    } else if (!textName.endsWith("\"") || textName.length() < 3) {
        ui->name_error->setText("Должно быть в кавычках \"...\"");
        hasError = true;
    }

    QString textCode = ui->code->text();
    if (textCode.isEmpty()) {
        ui->code_error->setText("Поле пустое");
        hasError = true;
    } else if (!textCode.contains("-")) {
        ui->code_error->setText("Нужен дефис '-'");
        hasError = true;
    } else if (textCode.endsWith("-")) {
        ui->code_error->setText("Введите вторую часть кода");
        hasError = true;
    }

    QString textContents = ui->contents->text();
    if (textContents.isEmpty()) {
        ui->contents_error->setText("Поле пустое");
        hasError = true;
    } else {
        int slashIndex = textContents.indexOf("/");
        if (slashIndex == -1) {
            ui->contents_error->setText("Нужен разделитель '/'");
            hasError = true;
        } else if (slashIndex == textContents.length() - 1) {
            ui->contents_error->setText("Нет второго числа");
            hasError = true;
        } else {
            QString num1Str = textContents.left(slashIndex);
            QString num2Str = textContents.mid(slashIndex + 1);
            if (num1Str.toInt() <= num2Str.toInt()) {
                ui->contents_error->setText("Первое число должно быть больше");
                hasError = true;
            }
        }
    }

    if (!ui->type_digital->isChecked() && !ui->type_paper->isChecked()) {
        ui->type_error->setText("Выберите тип");
        hasError = true;
    }

    if (hasError) return;

    QString finalType = ui->type_paper->isChecked() ? "Бумажное" : "Электронное";
    std::vector<QString> finalGenres;

    if (ui->genre_detective->isChecked()) finalGenres.push_back("Детектив");
    if (ui->genre_fiction->isChecked()) finalGenres.push_back("Фантастика");
    if (ui->genre_novel->isChecked()) finalGenres.push_back("Роман");

    
    book newBook(textAuthor, textName, textCode, textContents, finalType, finalGenres);
    newBook.write_to_file();
}
