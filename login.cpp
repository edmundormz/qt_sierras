#include "login.h"
#include "ui_login.h"
#include <QPixmap>

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
