#ifndef PLAYGROUND_H
#define PLAYGROUND_H

#include <QDialog>
#include <QDate>


namespace Ui {
class Playground;
}

class QSerialPort;

class Playground : public QDialog
{
    Q_OBJECT

public:
    explicit Playground(QWidget *parent = 0);
    ~Playground();
    float remaining;

private slots:
    void on_pbExit_clicked();

    void on_pbCut_clicked();

    void on_pbStop_clicked();

    void on_lineEditMaterialLength_textEdited();

//    void fTimer();

    void on_pbConnect_clicked();

    void Logger(QString command);

    void Serialer(QString instruction);

private:
    Ui::Playground *ui;

    QSerialPort *hw;
    QString hw_port_name;
    bool hw_is_available;
    float disc = 0;
    QDate date;

};

#endif // PLAYGROUND_H
