#include "login.h"
#include "ui_login.h"
#include <QPixmap>
#include "playground.h"
#include <QMessageBox>

LogIn::LogIn(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::LogIn)
{
    ui->setupUi(this);
    //Display image logo
    QPixmap disc(":/images/resources/images/disc.png");
    ui->labelLogo->setPixmap(disc.scaled(100,100,Qt::KeepAspectRatio));
}

LogIn::~LogIn()
{
    delete ui;
}

void LogIn::on_buttonLogin_clicked()
{
    QString user = ui->lineUser->text();
    QString password = ui->linePassword->text();
    if(user == "" && password == ""){
        Playground playground;
        hide();
        playground.setModal(true);
        playground.exec();
    }
    else {
        QMessageBox::information(this,"Error","Credenciales incorrectas");
    }

}
