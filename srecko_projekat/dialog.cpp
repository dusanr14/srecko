#include "dialog.h"
#include "ui_dialog.h"

Dialog::Dialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::Dialog)
{
    ui->setupUi(this);
    wiringPiSetup();
    fd= wiringPiI2CSetup(PCF8591);
    myTimer1 = new QTimer(this);
    connect(myTimer1, SIGNAL(timeout()), this,SLOT(function1()));
    pix_light=QPixmap("/home/pi/srecko/srecko_projekat/light1.PNG");
    ui->light->setPixmap(pix_light);
    ui->light->setScaledContents(true);
    ui->light->show();

    series=new QLineSeries();


    chart=new QChart();
    chart->legend()->hide();
    chart->addSeries(series);
    chart->createDefaultAxes();
    chart->axisX()->setMin(0);
    chart->axisX()->setMax(20);
    chart->axisY()->setRange(25,35);
    chart->setTitle("Merenje temperature");
    chartView =new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
    ui->verticalLayout->addWidget(chartView);
}

Dialog::~Dialog()
{
    delete ui;
}
double Dialog::temperature()//void in the brackets
{
    FILE *ft;
    char tekst[100];
    ft = fopen("/sys/bus/w1/devices/28-00000cfbb0e4/w1_slave","r");
    if(ft == NULL)
        return 0;
    int i = 0;
    for(i=0;i<22;i++)
        fscanf(ft, "%s", tekst);
    fclose(ft);

    for(i=0;i<10;i++)
    {
        tekst[i]=tekst[i+2];
    }
    int temp=atoi(tekst);
    double tem=(double)temp/1000;

    return tem;
};
void Dialog::function1()
{

    double temp_var = temperature();
    wiringPiI2CReadReg8(fd, PCF8591) ;
    adc = wiringPiI2CReadReg8(fd, PCF8591) ;
    ui->lcdNumber->display(adc);
    if(adc>128)
    {
        pix_light=QPixmap("/home/pi/srecko/srecko_projekat/light2.PNG");
    }
    else
    {
        pix_light=QPixmap("/home/pi/srecko/srecko_projekat/light1.PNG");
    }

    ui->light->setPixmap(pix_light);
    ui->light->setScaledContents(true);
    ui->light->show();

            if(del)
            {
                del=0;
                t=0;
                series->clear();
            }
            if(t==21)
            {
                t=0;
                series->clear();
            }
      series->append(t,temp_var);
      t++;
      chartView->update();
}


void Dialog::on_pushButton_clicked()
{
     myTimer1->start(1000);
}

void Dialog::on_pushButton_2_clicked()
{
    del = 1;
}
