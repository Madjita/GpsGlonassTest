#ifndef PAGE4_STARTETAPCAMBER_H
#define PAGE4_STARTETAPCAMBER_H

#include <QWidget>

namespace Ui {
class Page4_StartEtapCamber;
}

class Page4_StartEtapCamber : public QWidget
{
    Q_OBJECT

public:
    explicit Page4_StartEtapCamber(QWidget *parent = 0);
    ~Page4_StartEtapCamber();


    int indexProverka;
    int modeCamber;

    void setIndexProverka(int index);

signals:
    void Beak();

    void StartProverka(int indexProverka, int modeCamber);


private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::Page4_StartEtapCamber *ui;
};

#endif // PAGE4_STARTETAPCAMBER_H
