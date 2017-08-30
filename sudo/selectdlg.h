#ifndef SELECTDLG_H
#define SELECTDLG_H

#include <QDialog>
#include <QComboBox>
#include <QPushButton>
#include <QLabel>
#include <QDesktopWidget>
namespace Ui {
class selectdlg;
}

class selectdlg : public QDialog
{
    Q_OBJECT

public:
    explicit selectdlg(QWidget *parent = 0);
    ~selectdlg();

private:
    Ui::selectdlg *ui;
    QComboBox *box;
    QPushButton *start,*end;
    QLabel *mes;
private slots:
    void starting();
signals:
    void to_close();
    void to_start(int);
};

#endif // SELECTDLG_H
