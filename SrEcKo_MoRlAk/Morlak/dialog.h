#ifndef DIALOG_H
#define DIALOG_H

#include <QtCharts/QChartView>
#include <QtCharts/QLineSeries>
#include <QtCharts/QValueAxis>

#include <QDialog>
#include <wiringPiI2C.h>
#include <wiringPi.h>
#include <stdlib.h>

#include <string>

QT_CHARTS_USE_NAMESPACE

QT_BEGIN_NAMESPACE
namespace Ui { class Dialog; }
QT_END_NAMESPACE

class Dialog : public QDialog
{
    Q_OBJECT

public:
    Dialog(QWidget *parent = nullptr);
    ~Dialog();

    QLineSeries *series;
    QChart *chart;
    QChartView *chartView;

private slots:
    void function();
    void on_pushButton_clicked();

private:
    Ui::Dialog *ui;

    const char PCF8591 = 0x48;
    int fd, X, Y, Z, W;
    char unsigned adcVal;
    bool start;
};
#endif // DIALOG_H
