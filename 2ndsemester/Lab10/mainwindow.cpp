#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDir>
#include <QEvent>
#include <QFile>
#include <QFileDialog>
#include <QFont>
#include <QImage>
#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QLineEdit>
#include <QMessageBox>
#include <QPainter>
#include <QPixmap>
#include <QRegularExpression>
#include <QStandardPaths>
#include <QTextStream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setupDoubleClickClear();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setupDoubleClickClear()
{
    ui->nameEdit->installEventFilter(this);
    ui->surnameEdit->installEventFilter(this);
    ui->nicknameEdit->installEventFilter(this);
    ui->passwordEdit->installEventFilter(this);
    ui->emailEdit->installEventFilter(this);
    ui->idKeyEdit->installEventFilter(this);
}

bool MainWindow::eventFilter(
    QObject *object,
    QEvent *event
)
{
    if (event->type() ==
        QEvent::MouseButtonDblClick) {

        QLineEdit *field =
            qobject_cast<QLineEdit *>(object);

        if (field != nullptr) {
            field->clear();
            ui->statusLabel->clear();
            return true;
        }
    }

    return QMainWindow::eventFilter(
        object,
        event
    );
}

void MainWindow::on_loadPhotoButton_clicked()
{
    QString filePath =
        QFileDialog::getOpenFileName(
            this,
            "Выберите фотографию",
            "",
            "Изображения (*.png *.jpg *.jpeg *.bmp)"
        );

    if (filePath.isEmpty()) {
        return;
    }

    QPixmap photo(filePath);

    if (photo.isNull()) {
        showError(
            "Не удалось открыть выбранное изображение"
        );
        return;
    }

    selectedPhotoPath = filePath;

    ui->photoLabel->setText("");

    ui->photoLabel->setPixmap(
        photo.scaled(
            ui->photoLabel->size(),
            Qt::KeepAspectRatio,
            Qt::SmoothTransformation
        )
    );

    showSuccess(
        "Фотография загружена"
    );
}

bool MainWindow::checkField(
    QLineEdit *field,
    const QString& expression,
    const QString& errorMessage
)
{
    QRegularExpression regularExpression(
        expression
    );

    QRegularExpressionMatch match =
        regularExpression.match(
            field->text().trimmed()
        );

    if (!match.hasMatch()) {
        showError(errorMessage, field);
        return false;
    }

    return true;
}

bool MainWindow::validateFields()
{
    if (!checkField(
            ui->nameEdit,
            "^[A-Za-zА-Яа-яЁё-]{2,30}$",
            "Имя должно содержать от 2 до 30 букв"
        )) {
        return false;
    }

    if (!checkField(
            ui->surnameEdit,
            "^[A-Za-zА-Яа-яЁё-]{2,30}$",
            "Фамилия должна содержать от 2 до 30 букв"
        )) {
        return false;
    }

    if (!checkField(
            ui->nicknameEdit,
            "^[A-Za-z0-9_]{3,20}$",
            "Никнейм: от 3 до 20 латинских букв, цифр или _"
        )) {
        return false;
    }

    if (!checkField(
            ui->passwordEdit,
            "^(?=.*[A-Za-zА-Яа-яЁё])"
            "(?=.*[0-9])\\S{6,30}$",
            "Пароль: от 6 до 30 символов, "
            "минимум одна буква и одна цифра"
        )) {
        return false;
    }

    if (!checkField(
            ui->emailEdit,
            "^[A-Za-z0-9._%+-]+"
            "@[A-Za-z0-9.-]+"
            "\\.[A-Za-z]{2,}$",
            "Введите корректный адрес электронной почты"
        )) {
        return false;
    }

    if (!checkField(
            ui->idKeyEdit,
            "^[А-ЯA-Z][0-9]{3}-"
            "[0-9]{2}[А-ЯA-Z]-[А-ЯA-Z]$",
            "ID-Key должен соответствовать формату А111-11А-А"
        )) {
        return false;
    }

    if (selectedServers().isEmpty()) {
        showError(
            "Выберите хотя бы один сервер"
        );
        return false;
    }

    QString nickname =
        ui->nicknameEdit->text().trimmed();

    if (!nicknameIsAvailable(nickname)) {
        showError(
            "Этот никнейм уже занят",
            ui->nicknameEdit
        );
        return false;
    }

    return true;
}

QStringList MainWindow::selectedServers() const
{
    QStringList servers;

    if (ui->europeCheckBox->isChecked()) {
        servers.append("Европа");
    }

    if (ui->asiaCheckBox->isChecked()) {
        servers.append("Азия");
    }

    if (ui->americaCheckBox->isChecked()) {
        servers.append("Америка");
    }

    return servers;
}

bool MainWindow::nicknameIsAvailable(
    const QString& nickname
) const
{
    QString desktopPath =
        QStandardPaths::writableLocation(
            QStandardPaths::DesktopLocation
        );

    QString accountPath =
        desktopPath +
        "/Accounts/" +
        nickname;

    return !QDir(accountPath).exists();
}

QString MainWindow::encryptPassword(
    const QString& password
) const
{
    QByteArray passwordBytes =
        password.toUtf8();

    QByteArray key = "Lab10SecretKey";

    for (int index = 0;
         index < passwordBytes.size();
         ++index) {

        char encryptedCharacter =
            static_cast<char>(
                passwordBytes.at(index) ^
                key.at(index % key.size())
            );

        passwordBytes[index] =
            encryptedCharacter;
    }

    return QString::fromLatin1(
        passwordBytes.toBase64()
    );
}

bool MainWindow::savePhoto(
    const QString& accountPath,
    QString& errorMessage
)
{
    QString photoPath =
        accountPath + "/photo.png";

    if (!selectedPhotoPath.isEmpty()) {
        QImage photo(selectedPhotoPath);

        if (photo.isNull()) {
            errorMessage =
                "Не удалось прочитать фотографию";
            return false;
        }

        if (!photo.save(photoPath, "PNG")) {
            errorMessage =
                "Не удалось сохранить фотографию";
            return false;
        }

        return true;
    }

    QImage defaultPhoto(
        300,
        300,
        QImage::Format_RGB32
    );

    defaultPhoto.fill(
        QColor(210, 215, 220)
    );

    QPainter painter(&defaultPhoto);

    painter.setPen(
        QColor(70, 70, 70)
    );

    painter.setFont(
        QFont("Arial", 18)
    );

    painter.drawText(
        defaultPhoto.rect(),
        Qt::AlignCenter,
        "Фото\nпо умолчанию"
    );

    painter.end();

    if (!defaultPhoto.save(photoPath, "PNG")) {
        errorMessage =
            "Не удалось создать фотографию по умолчанию";
        return false;
    }

    return true;
}

bool MainWindow::saveAccount(
    QString& accountPath,
    QString& errorMessage
)
{
    QString desktopPath =
        QStandardPaths::writableLocation(
            QStandardPaths::DesktopLocation
        );

    QString accountsPath =
        desktopPath + "/Accounts";

    QString nickname =
        ui->nicknameEdit->text().trimmed();

    accountPath =
        accountsPath + "/" + nickname;

    QDir directory;

    if (!directory.mkpath(accountPath)) {
        errorMessage =
            "Не удалось создать папку аккаунта";
        return false;
    }

    QJsonObject accountObject;

    accountObject["name"] =
        ui->nameEdit->text().trimmed();

    accountObject["surname"] =
        ui->surnameEdit->text().trimmed();

    accountObject["nickname"] =
        nickname;

    accountObject["email"] =
        ui->emailEdit->text().trimmed();

    accountObject["idKey"] =
        ui->idKeyEdit->text().trimmed();

    accountObject["servers"] =
        QJsonArray::fromStringList(
            selectedServers()
        );

    QJsonDocument accountDocument(
        accountObject
    );

    QFile jsonFile(
        accountPath + "/account.json"
    );

    if (!jsonFile.open(
            QIODevice::WriteOnly |
            QIODevice::Text |
            QIODevice::Truncate)) {
        errorMessage =
            "Не удалось создать account.json";
        return false;
    }

    if (jsonFile.write(
            accountDocument.toJson(
                QJsonDocument::Indented
            )
        ) == -1) {
        jsonFile.close();

        errorMessage =
            "Ошибка записи account.json";
        return false;
    }

    jsonFile.close();

    QFile passwordFile(
        accountPath + "/password.txt"
    );

    if (!passwordFile.open(
            QIODevice::WriteOnly |
            QIODevice::Text |
            QIODevice::Truncate)) {
        errorMessage =
            "Не удалось создать password.txt";
        return false;
    }

    QTextStream passwordStream(
        &passwordFile
    );

    passwordStream
        << ui->emailEdit->text().trimmed()
        << "/"
        << encryptPassword(
               ui->passwordEdit->text()
           );

    passwordFile.close();

    if (!savePhoto(
            accountPath,
            errorMessage
        )) {
        return false;
    }

    return true;
}

void MainWindow::showError(
    const QString& message,
    QLineEdit *field
)
{
    ui->statusLabel->setStyleSheet(
        "color: #8b2020; font-size: 13px;"
    );

    ui->statusLabel->setText(message);

    if (field != nullptr) {
        field->setFocus();
        field->selectAll();
    }
}

void MainWindow::showSuccess(
    const QString& message
)
{
    ui->statusLabel->setStyleSheet(
        "color: #176b2c; font-size: 13px;"
    );

    ui->statusLabel->setText(message);
}

void MainWindow::clearForm()
{
    ui->nameEdit->clear();
    ui->surnameEdit->clear();
    ui->nicknameEdit->clear();
    ui->passwordEdit->clear();
    ui->emailEdit->clear();
    ui->idKeyEdit->clear();

    ui->europeCheckBox->setChecked(false);
    ui->asiaCheckBox->setChecked(false);
    ui->americaCheckBox->setChecked(false);

    ui->photoLabel->clear();
    ui->photoLabel->setText("Фото");

    selectedPhotoPath.clear();
}

void MainWindow::on_registerButton_clicked()
{
    if (!validateFields()) {
        return;
    }

    QString accountPath;
    QString errorMessage;

    if (!saveAccount(
            accountPath,
            errorMessage
        )) {
        showError(errorMessage);
        return;
    }

    QMessageBox::information(
        this,
        "Регистрация",
        "Аккаунт успешно создан.\n\n"
        "Папка:\n" +
        QDir::toNativeSeparators(accountPath)
    );

    clearForm();

    showSuccess(
        "Регистрация завершена"
    );
}