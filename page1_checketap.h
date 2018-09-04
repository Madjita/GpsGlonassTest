#ifndef PAGE1_CHECKETAP_H
#define PAGE1_CHECKETAP_H

#include <QWidget>

#include <QtDebug>

namespace Ui {
class Page1_checketap;
}

class Page1_checketap : public QWidget
{
    Q_OBJECT

public:
    explicit Page1_checketap(QWidget *parent = 0);
    ~Page1_checketap();

    QString getName();
    QString getMode();


signals:
    void OpenDeviceConnect();


private slots:
    void on_pushButton_Work_clicked();

private:
    Ui::Page1_checketap *ui;
};

#endif // PAGE1_CHECKETAP_H
