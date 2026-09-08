#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>
#include <QStringList>

QT_BEGIN_NAMESPACE

namespace Ui {
class MainWindow;
}

QT_END_NAMESPACE

class QEvent;
class QLineEdit;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    bool eventFilter(
        QObject *object,
        QEvent *event
    ) override;

private slots:
    void on_loadPhotoButton_clicked();
    void on_registerButton_clicked();

private:
    Ui::MainWindow *ui;

    QString selectedPhotoPath;

    void setupDoubleClickClear();

    bool validateFields();

    bool checkField(
        QLineEdit *field,
        const QString& expression,
        const QString& errorMessage
    );

    bool nicknameIsAvailable(
        const QString& nickname
    ) const;

    QStringList selectedServers() const;

    QString encryptPassword(
        const QString& password
    ) const;

    bool saveAccount(
        QString& accountPath,
        QString& errorMessage
    );

    bool savePhoto(
        const QString& accountPath,
        QString& errorMessage
    );

    void showError(
        const QString& message,
        QLineEdit *field = nullptr
    );

    void showSuccess(
        const QString& message
    );

    void clearForm();
};

#endif // MAINWINDOW_H