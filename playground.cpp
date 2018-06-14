#include "playground.h"
#include "ui_playground.h"

Playground::Playground(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Playground)
{
    ui->setupUi(this);
}

Playground::~Playground()
{
    delete ui;
}
