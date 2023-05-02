#ifndef REGISTERPAGE_H
#define REGISTERPAGE_H

#include <QWidget>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QMessageBox>


namespace Ui {
class registerPage;
}

class registerPage : public QWidget
{
    Q_OBJECT

public:
    explicit registerPage(QWidget *parent = nullptr);
    ~registerPage();

private slots:
    void on_register_pushButton_clicked();

    void on_eye_pushButton_pressed();

    void on_eye_pushButton_released();

private:
    Ui::registerPage *ui;
};

#endif // REGISTERPAGE_H
