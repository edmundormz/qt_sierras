#include "playground.h"
#include "ui_playground.h"
#include <QMessageBox>
#include <QtDebug>

Playground::Playground(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Playground)
{
    ui->setupUi(this);
    //remaining = ui->lineEditMaterialLength->text().toFloat();
    //remaining = 100;
    //qDebug() << "remaining =" << remaining;

    //qApp->setStyleSheet();
}

Playground::~Playground()
{
    delete ui;
}

void Playground::on_pbExit_clicked()
{
    this->close();
}

void Playground::on_pbCut_clicked()
{
    //qDebug() << "remaining =" << remaining;
    if(ui->comboBoxDiscType->currentText() == "3 mm"
            && ui->comboBoxMaterialType->currentText() == "Metal"){
        QMessageBox::information(this,"Error","Unnapropiate disc for metal");
    }
    else {
        float disc = 0;
        switch (ui->comboBoxDiscType->currentIndex()){
        case 0:
            disc = 1;
            break;
        case 1:
            disc = 2;
            break;
        default:
            disc = 3;
            break;
        }

        float to_cut = ui->lineEditCutLength->text().toFloat();
        qDebug() << "remaining =" << remaining;
        qDebug() << "to cut =" << to_cut;
        QString foo = "foo";
        QString bar = "bar";
        QString zen = foo + bar;
        qDebug() << "zen = " << zen;
        if(to_cut < remaining){
            remaining = remaining - disc - to_cut;
            ui->lbRemainingMaterial->setText(QString::number(remaining));
            QMessageBox::information(this,"Success","Cutting material");
        }
        else {
            QMessageBox::information(this,"Error","Unsufficient material");
        }
    }

}

void Playground::on_pbStop_clicked()
{
    QMessageBox::information(this,"System Stopped","Turning off system");
}


void Playground::on_lineEditMaterialLength_textEdited(const QString &arg1)
{
    remaining = ui->lineEditMaterialLength->text().toFloat();
}
