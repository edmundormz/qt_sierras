#ifndef PLAYGROUND_H
#define PLAYGROUND_H

#include <QDialog>

namespace Ui {
class Playground;
}

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

    void on_lineEditMaterialLength_textEdited(const QString &arg1);

private:
    Ui::Playground *ui;
};

#endif // PLAYGROUND_H
