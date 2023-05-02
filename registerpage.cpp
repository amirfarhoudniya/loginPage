#include "registerpage.h"
#include "ui_registerpage.h"

extern QSqlDatabase db;

registerPage::registerPage(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::registerPage)
{
    ui->setupUi(this);

    this->setWindowTitle("Register Page");

    ui->eye_pushButton->setIcon(QIcon(":/icons/eye.png"));

    // hints
    ui->name_lineEdit->setPlaceholderText("Your Name");
    ui->email_lineEdit->setPlaceholderText("example@email.com");
    ui->username_lineEdit->setPlaceholderText("set username");
    ui->password_lineEdit->setPlaceholderText("set password");
    ui->confirmPassword_lineEdit->setPlaceholderText("confirm password");

    //set type password for lineEdits
    ui->password_lineEdit->setEchoMode(QLineEdit::Password);
    ui->confirmPassword_lineEdit->setEchoMode(QLineEdit::Password);

}

registerPage::~registerPage()
{
    delete ui;
}

void registerPage::on_register_pushButton_clicked()
{
    QSqlQuery query;

    //check the form is filled
    if (ui->name_lineEdit->text().isEmpty()|| ui->email_lineEdit->text().isEmpty()||
        ui->username_lineEdit->text().isEmpty()|| ui->password_lineEdit->text().isEmpty()
        || ui->confirmPassword_lineEdit->text().isEmpty()) {
        QMessageBox::warning(this , "warning" , "please fill all part of form !");

        //set the red border on empty lineEdits
        if (ui->name_lineEdit->text().isEmpty()) {
            ui->name_lineEdit->setStyleSheet("border: 1px solid red;");
        }
        if (ui->email_lineEdit->text().isEmpty()) {
            ui->email_lineEdit->setStyleSheet("border: 1px solid red;");
        }
        if (ui->username_lineEdit->text().isEmpty()) {
            ui->username_lineEdit->setStyleSheet("border: 1px solid red;");
        }
        if (ui->password_lineEdit->text().isEmpty()) {
            ui->password_lineEdit->setStyleSheet("border: 1px solid red;");
        }
        if (ui->confirmPassword_lineEdit->text().isEmpty() || ui->password_lineEdit->text() != ui->confirmPassword_lineEdit->text()) {
            ui->confirmPassword_lineEdit->setStyleSheet("border: 1px solid red;");
        }

        //set the green border on filled lineEdits
        if (ui->name_lineEdit->text() != "") {
            ui->name_lineEdit->setStyleSheet("border: 1px solid green;");
        }
        if (ui->email_lineEdit->text() != "" ) {
            ui->email_lineEdit->setStyleSheet("border: 1px solid green;");
        }
        if (ui->username_lineEdit->text() != "") {
            ui->username_lineEdit->setStyleSheet("border: 1px solid green;");
        }
        if (ui->password_lineEdit->text() != "") {
            ui->password_lineEdit->setStyleSheet("border: 1px solid green;");
        }
        if (ui->confirmPassword_lineEdit->text() != "" && ui->confirmPassword_lineEdit->text() == ui->password_lineEdit->text()){
            ui->confirmPassword_lineEdit->setStyleSheet("border: 1px solid green;");
        }

        return ;
    }

    //check that confirmed password is equal to main password or not
    if (ui->password_lineEdit->text() != ui->confirmPassword_lineEdit->text()) {
        QMessageBox::warning(this , "registeration fail" , "the password doen't match !");
        return ;
    }

    //check the username existance
    QString username = ui->username_lineEdit->text();
    query.prepare("SELECT * FROM users WHERE username = :username ");
    query.bindValue(":username", username);
    if (query.exec() && query.next()) {
        QMessageBox::warning(this , "registeration fail" , "the username exists !");
        return ;
    }

    //conditions are checked so make a record of the form filled information in dataBase
    query.prepare("INSERT INTO users (name , email , username, password ) VALUES (? , ? , ? , ?)");
    query.addBindValue(ui->name_lineEdit->text());
    query.addBindValue(ui->email_lineEdit->text());
    query.addBindValue(ui->username_lineEdit->text());
    query.addBindValue(ui->password_lineEdit->text());
    query.exec();

    //show successful message and close register window
    QMessageBox::information(this , "Registered !" , "successfuly Registered!" );
    this->close();
}


void registerPage::on_eye_pushButton_pressed()
{
    ui->password_lineEdit->setEchoMode(QLineEdit::Normal);
}


void registerPage::on_eye_pushButton_released()
{
     ui->password_lineEdit->setEchoMode(QLineEdit::Password);
}

