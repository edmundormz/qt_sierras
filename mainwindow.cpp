#include "playground.h"
#include "ui_mainwindow.h"
#include <QPixmap>
#include <QMessageBox>
#include "playground.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QPixmap picture(":/Images/disc.png");
    ui->labelLogo->setPixmap(picture.scaled(200,200,Qt::KeepAspectRatio));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    QString user = ui->lineUser->text();
    QString pass = ui->linePassword->text();
    if(user=="user"&&pass=="pass"){

    }
}
