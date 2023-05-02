#include "mainwindow.h"
#include "ui_mainwindow.h"


extern QSqlDatabase db;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    this->setWindowTitle("Login Page");

    ui->eye_pushButton->setIcon(QIcon(":/icons/eye.png"));

    //set type password for lineEdits
    ui->password_lineEdit->setEchoMode(QLineEdit::Password);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_login_pushButton_clicked(){

    QString username = ui->username_lineEdit->text();
    QString password = ui->password_lineEdit->text();

    QSqlQuery query;
    query.prepare("SELECT * FROM users WHERE username = :username");
    query.bindValue(":username", username);

    if (query.exec() && query.next()) {
        query.prepare("SELECT * FROM users WHERE password = :password");
        query.bindValue(":password", password);
        if (query.exec() && query.next()) {
            QMessageBox::information(this, "Success", "Login successful");
        }else{
            QMessageBox::critical(this , "login fail" , "uncorrect password !");
        }
    } else {
        QMessageBox::critical(this , "login fail" , "the username doesn't exist !");
    }

}

void MainWindow::on_register_pushButton_clicked()
{
    registerPage *rp = new registerPage();
    rp->show();
}

void MainWindow::on_eye_pushButton_pressed()
{
    ui->password_lineEdit->setEchoMode(QLineEdit::Normal);
}


void MainWindow::on_eye_pushButton_released()
{
    ui->password_lineEdit->setEchoMode(QLineEdit::Password);
}

