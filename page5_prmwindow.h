#ifndef PAGE5_PRMWINDOW_H
#define PAGE5_PRMWINDOW_H

#include <QWidget>

namespace Ui {
class page5_PRMWindow;
}

class page5_PRMWindow : public QWidget
{
    Q_OBJECT

public:
    explicit page5_PRMWindow(QWidget *parent = 0);
    ~page5_PRMWindow();

signals:
    void closeWindowNP();
    void Error_10Gh();

public slots:

    void slot_getMeasureTok(QVector<QString> list);
    void slot_getMeasureVolt(QVector<QString> list);

    void slot_getUpdateTableSP(QStringList,QStringList,QStringList);

    void slot_countSpytnik_R(int R);
    void slot_countSpytnik_G(int G);

    void slot_countFindSpytnik_R(QString R);
    void slot_countFindSpytnik_G(QString G);

    void slot_updateTikTimer(QString data);

    void slot_clearWindow();

private slots:
    void on_pushButton_close_clicked();

private:
    Ui::page5_PRMWindow *ui;
};

#endif // PAGE5_PRMWINDOW_H
