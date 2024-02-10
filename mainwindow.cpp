#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <qcustomplot.h>
#include <QVector>
#include <QVector2D>
#include <QDebug>
double slope=0 , intercept=0 ;
QString slop,inter;
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
    slope=0,intercept=0;
    QVector<double> xData, yData;
    double x1=ui->lineEdit->text().toDouble();
    double x2=ui->lineEdit_2->text().toDouble();
    double x3=ui->lineEdit_3->text().toDouble();
    double x4=ui->lineEdit_4->text().toDouble();
    double x5=ui->lineEdit_5->text().toDouble();
    double y1=ui->lineEdit_6->text().toDouble();
    double y2=ui->lineEdit_7->text().toDouble();
    double y3=ui->lineEdit_8->text().toDouble();
    double y4=ui->lineEdit_9->text().toDouble();
    double y5=ui->lineEdit_10->text().toDouble();
    double xx1=log10(x1);
    double xx2=log10(x2);
    double xx3=log10(x3);
    double xx4=log10(x4);
    double xx5=log10(x5);
    double yy1=log10(y1);
    double yy2=log10(y2);
    double yy3=log10(y3);
    double yy4=log10(y4);
    double yy5=log10(y5);
    xData={xx1,xx2,xx3,xx4,xx5};
    yData={yy1,yy2,yy3,yy4,yy5};
    ui->customPlot_6->addGraph();
    ui->customPlot_6->graph(0)->setScatterStyle(QCPScatterStyle::ssCircle);
    ui->customPlot_6->graph(0)->setLineStyle(QCPGraph::lsLine);
    ui->customPlot_6->graph(0)->setData(xData, yData);
    // Calculate trendline
    QVector<double> trendline = calculateTrendline(xData, yData);
    // Plot trendline
    ui->customPlot_6->addGraph();
    ui->customPlot_6->graph(1)->setData(xData, trendline);
    ui->customPlot_6->graph(1)->setPen(QPen(Qt::red)); // Change trendline color if necessary
    ui->customPlot_6->xAxis->setLabel("Log(X)");
    ui->customPlot_6->yAxis->setLabel("Log(Y)");
    ui->customPlot_6->xAxis->setRange(xData.first()-0.2, xData.last()+0.2);
    ui->customPlot_6->yAxis->setRange(yData.first()-0.2, yData.last()+0.2);
    ui->customPlot_6->update();
    ui->customPlot_6->replot();
}

// Function to calculate linear regression line
QVector<double> MainWindow:: calculateTrendline(const QVector<double> &xData, const QVector<double> &yData) {
    double sumX = 0, sumY = 0, sumXY = 0, sumXX = 0;
    int n = xData.size();

    for (int i = 0; i < n; ++i) {
        sumX += xData[i];
        sumY += yData[i];
        sumXY += xData[i] * yData[i];
        sumXX += xData[i] * xData[i];
    }
    slope = (n * sumXY - sumX * sumY) / (n * sumXX - sumX * sumX);
    intercept = (sumY -  slope* sumX) / n;
    ui->label_5->setText(QString::number(slope,'f',4));
    ui->label_7->setText(QString::number(intercept,'f',4));
    QVector<double> trendline;
    for (int i = 0; i < n; ++i) {
        trendline.append(slope * xData[i] + intercept);
    }
    return trendline;
}

void MainWindow::on_pushButton_2_clicked()
{
    double y=ui->lineEdit_11->text().toDouble();
    double yy= log10(y);
    double result=(yy-intercept)/slope;
    double Mainresult = qPow(10,result);
    ui->label_4->setText(QString::number(Mainresult,'f',2));
}
