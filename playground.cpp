#include "playground.h"
#include "ui_playground.h"
#include <QSerialPort>
#include <QSerialPortInfo>
#include <QMessageBox>
#include <QDebug>
#include <QTimer>
#include <QDir>
#include <QFile>
#include <QTextStream>
#include <QIODevice>

void Playground::fTimer(){
    if(hw_is_available && hw->isWritable()){
        hw->write("a");
        if(hw->isReadable()){
            QByteArray datosLeidos = hw->read(2);
            //int ADC_Digital = datosLeidos.toHex().toInt(0,16);
            //float ADC_Flotante = (5*(float)ADC_Digital/1023);
            //SOMETHING TO DO WITH SERIAL INFO
        }
    }
}

Playground::Playground(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Playground)
{
    ui->setupUi(this);
    QString hello = "Session started";
    Logger(hello);

    //Timer to check serial ports
    QTimer *cronometro = new QTimer(this);
    connect(cronometro, SIGNAL(timeout()),this, SLOT(fTimer()));
    cronometro->start(100);

    hw_is_available = false;
    hw_port_name = "";
    hw = new QSerialPort;
    ui->lineEditBaudRate->setText("9600");
    ui->lineEditNPorts->setText(QString::number(QSerialPortInfo::availablePorts().length()));
    foreach (const QSerialPortInfo &serialPortInfo, QSerialPortInfo::availablePorts()) {
        if(serialPortInfo.hasVendorIdentifier() && serialPortInfo.hasProductIdentifier()){
            ui->lineEditVendorID->setText(QString::number(serialPortInfo.vendorIdentifier()));
            ui->lineEditProductID->setText(QString::number(serialPortInfo.productIdentifier()));
            hw_port_name = serialPortInfo.portName();
            hw_is_available = true;
        }
    }

    foreach (const QSerialPortInfo &serialPortInfo, QSerialPortInfo::availablePorts()) {
        ui->comboBoxPort->addItem(serialPortInfo.portName());
    }

    //qApp->setStyleSheet();
}

Playground::~Playground()
{
    delete ui;
}

void Playground::on_pbExit_clicked()
{
    QString regards = "Session closed";
    Logger(regards);
    hw->close();
    this->close();
}

void Playground::on_pbCut_clicked()
{
    if(ui->comboBoxDiscType->currentText() == "3 mm"
            && ui->comboBoxMaterialType->currentText() == "Metal"){
        QString error_message = "Unnapropiate disc for metal";
        QMessageBox::information(this,"Error", error_message);
        Logger(error_message);
    }
    else {
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
        //Command log
        QString command;
        command += "D" + QString::number(disc) + ",";
        command += "M" + QString::number(ui->comboBoxMaterialType->currentIndex()) + ",";
        command += "C" + ui->lineEditCutLength->text() + ",";
        command += "R" + ui->lbRemainingMaterial->text();
        ui->lbCommand->setText(command);
        Logger(command);

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


void Playground::on_lineEditMaterialLength_textEdited()
{
    remaining = ui->lineEditMaterialLength->text().toFloat();
}

void Playground::on_pbConnect_clicked()
{
    int bauds = ui->lineEditBaudRate->text().toInt();
    if(bauds == 9600){
        hw->setBaudRate(QSerialPort::Baud9600);
        ui->lineEditBaudRate_2->setText(QString::number(bauds));
    }
    if(hw_is_available){
        hw->setPortName(hw_port_name);
        hw->open(QIODevice::ReadWrite);
        hw->setDataBits(QSerialPort::Data8);
        hw->setParity(QSerialPort::NoParity);
        hw->setStopBits(QSerialPort::OneStop);
        hw->setFlowControl(QSerialPort::NoFlowControl);
        QString connected = "Connected to " + hw_port_name;
        Logger(connected);
    }
    else {
        QString connection_error = "Serial port not available";
        QMessageBox::information(this, "Error", connection_error);
        Logger(connection_error);
    }
}

void Playground::Logger(QString command){
    QString current_day = QString::number(date.currentDate().dayOfYear());
    QString logs_dir_path = "/home/hecmundo/qt_logs";

    //Check if logs directory exists
    if (!QDir(logs_dir_path).exists()){
        QDir().mkdir(logs_dir_path);
    }
    //Check if current log file exists
    QFile log_path(logs_dir_path + "/log_" + current_day + ".csv");
    if (log_path.open(QIODevice::WriteOnly | QIODevice::Append)){
        QTextStream out_log(&log_path);
        QString log = command + "_" + current_day + "\n";
        out_log << log;
        log_path.flush();
        log_path.close();
    }
    else {

        QMessageBox::information(this, "Error", "Unable to open log file");
    }
}
