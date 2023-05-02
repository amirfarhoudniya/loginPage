#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QMessageBox>

#include <registerpage.h>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void on_login_pushButton_clicked();

    void on_register_pushButton_clicked();

    void on_eye_pushButton_pressed();

    void on_eye_pushButton_released();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
