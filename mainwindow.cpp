#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    reset();
    existmemory=false;
    connect(
    ui->pb_0, &QPushButton::clicked, this, &MainWindow::input
    );
    connect(
    ui->pb_1, &QPushButton::clicked, this, &MainWindow::input
    );
    connect(
    ui->pb_2, &QPushButton::clicked, this, &MainWindow::input
    );
    connect(
    ui->pb_3, &QPushButton::clicked, this, &MainWindow::input
    );
    connect(
    ui->pb_4, &QPushButton::clicked, this, &MainWindow::input
    );
    connect(
    ui->pb_5, &QPushButton::clicked, this, &MainWindow::input
    );
    connect(
    ui->pb_6, &QPushButton::clicked, this, &MainWindow::input
    );
    connect(
    ui->pb_7, &QPushButton::clicked, this, &MainWindow::input
    );
    connect(
    ui->pb_8, &QPushButton::clicked, this, &MainWindow::input
    );
    connect(
    ui->pb_9, &QPushButton::clicked, this, &MainWindow::input
    );
    connect(
    ui->pbPLUS, &QPushButton::clicked, this, &MainWindow::calc
    );
    connect(
    ui->pbMINUS, &QPushButton::clicked, this, &MainWindow::calc
    );
    connect(
    ui->pbCOMP, &QPushButton::clicked, this, &MainWindow::calc
    );
    connect(
    ui->pbDELT, &QPushButton::clicked, this, &MainWindow::calc
    );
    connect(
    ui->pbEQUAL, &QPushButton::clicked, this, &MainWindow::calc
    );
    connect(
    ui->pbMEMORYSAVE, &QPushButton::clicked, this, &MainWindow::memorywork
    );
    connect(
    ui->pbMEMORYPLUS, &QPushButton::clicked, this, &MainWindow::memorywork
    );
    connect(
    ui->pbMEMORYMINUS, &QPushButton::clicked, this, &MainWindow::memorywork
    );
    connect(
    ui->pbMEMORYCLEAR, &QPushButton::clicked, this, &MainWindow::memorywork
    );
    connect(
    ui->pbMEMORYRECALL, &QPushButton::clicked, this, &MainWindow::memorywork
    );
}

MainWindow::~MainWindow()
{
    delete ui;

}

void MainWindow::reset() {
    ui->leINPUT->setText("0");
    numl = "";
    numal = "";
    error = false;
    stat=State::FirstDigit;
}
void MainWindow::input() {
    if(!error) {
        if(stat == State::FirstDigit) {
            ui->leINPUT->setText("");
        } else if(stat==State::Calculation) {
            ui->leINPUT->setText("");
            numl="";
            numal="";
            stat = State::FirstDigit;
        }
        QString digit = dynamic_cast<QPushButton*>(sender())->text();
        ui->leINPUT->setText(ui->leINPUT->text()+digit);
        if(digit!="0") {
            stat = State::InputNumber;
        }
    }
}


void MainWindow::on_pbCLEAR_clicked()
{
    reset();
}


void MainWindow::on_pbPandM_clicked()
{
    if(!error) {
        double num = ui->leINPUT->text().toDouble();
        if(num>0) {
            ui->leINPUT->setText("-" + ui->leINPUT->text());
        } else if (num<0) {
            ui->leINPUT->setText(ui->leINPUT->text().mid(1,ui->leINPUT->text().length()));
        }
    }
}


void MainWindow::on_pbPoint_clicked()
{
    if(!error) {
    if(ui->leINPUT->text().indexOf(".")==-1) {
        ui->leINPUT->setText(ui->leINPUT->text()+".");
        if(stat==State::FirstDigit) stat = State::InputNumber;
    }
    }
}

void MainWindow::calc() {
    if(!error) {
    QString oper = dynamic_cast<QPushButton*>(sender())->text();
    QString num = ui->leINPUT->text();
        if(stat==State::Calculation && oper != "=") {
            stat=State::FirstDigit;
            numl = num;
            numal = "";
            lastOper=oper;
        } else {
            if(numl=="") {
                numl = num;
                lastOper=oper;
                stat=State::FirstDigit;
        }
        else {
            if (oper=="="){
                if(numal=="") {
                    numal=num;
                }
                if(lastOper=="+") {
                    numl = QString::number(numl.toDouble()+numal.toDouble());
                    ui->leINPUT->setText(numl);
                }
                else if(lastOper=="-") {
                    numl = QString::number(numl.toDouble()-numal.toDouble());
                    ui->leINPUT->setText(numl);
                }
                else if(lastOper=="*") {
                    numl = QString::number(numl.toDouble()*numal.toDouble());
                    ui->leINPUT->setText(numl);
                }
                else if(lastOper=="/") {
                    if(numal=="0") {
                        error = true;
                        ui->leINPUT->setText("ERROR");
                    } else {
                        numl = QString::number(numl.toDouble()/numal.toDouble());
                        ui->leINPUT->setText(numl);
                    }
                }
                stat=State::Calculation;
            }
            else {
                if(numal!="") {
                if(lastOper=="+") {
                    numl = QString::number(numl.toDouble()+num.toDouble());
                    ui->leINPUT->setText(numl);
                }
                else if(lastOper=="-") {
                    numl = QString::number(numl.toDouble()-num.toDouble());
                    ui->leINPUT->setText(numl);
                }
                else if(lastOper=="*") {
                    numl = QString::number(numl.toDouble()*num.toDouble());
                    ui->leINPUT->setText(numl);
                }
                else if(lastOper=="/") {
                    numl = QString::number(numl.toDouble()/num.toDouble());
                    ui->leINPUT->setText(numl);
                }
                }
                lastOper = oper;
                stat=State::FirstDigit;

            }
        }
        }
    }
}

void MainWindow::memorywork() {
    if(!error) {
    QString oper = dynamic_cast<QPushButton*>(sender())->text();
    if((oper=="MS" || oper=="M+")&&!existmemory) {
        memorynum=ui->leINPUT->text();
        existmemory=true;
    }
    else if (existmemory) {
        if(oper=="M+") memorynum = QString::number(memorynum.toDouble() + ui->leINPUT->text().toDouble());
        else if(oper=="M-") memorynum = QString::number(memorynum.toDouble() - ui->leINPUT->text().toDouble());
        else if(oper=="MS") memorynum = ui->leINPUT->text();
        else if(oper=="MR") ui->leINPUT->setText(memorynum);
        else if(oper=="MC") {
            memorynum="";
            existmemory=false;
        }
    }
    }
}
void MainWindow::on_pbCLEARNUMBER_clicked()
{
    if(!error) {
    ui->leINPUT->setText("0");
    stat = State::FirstDigit;
    }
}

