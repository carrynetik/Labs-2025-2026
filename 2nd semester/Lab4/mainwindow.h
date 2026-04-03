#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_author_textEdited();
    void on_name_textEdited();
    void on_code_textEdited();
    void on_contents_textEdited();
    void on_type_paper_clicked();
    void on_type_digital_clicked();

    void on_discard_pressed();
    void on_save_pressed();

private:
    Ui::MainWindow *ui;
};
#endif 