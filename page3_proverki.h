#ifndef PAGE3_PROVERKI_H
#define PAGE3_PROVERKI_H

#include <QWidget>

namespace Ui {
class Page3_Proverki;
}

class Page3_Proverki : public QWidget
{
    Q_OBJECT

public:
    explicit Page3_Proverki(QWidget *parent = 0);
    ~Page3_Proverki();

signals:
    void OpenStartEtapCamber(int numberProverki);


private slots:
    void on_pushButton_1_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

    void on_pushButton_4_clicked();

    void on_pushButton_5_clicked();

    void on_pushButton_6_clicked();

    void on_pushButton_7_clicked();

    void on_pushButton_8_clicked();

    void on_pushButton_9_clicked();

    void on_pushButton_10_clicked();

private:
    Ui::Page3_Proverki *ui;
};

#endif // PAGE3_PROVERKI_H
