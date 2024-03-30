#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

    enum State {
        FirstDigit, InputNumber, Calculation
    };
    State stat;
    QString numl;
    QString lastOper;
    QString numal;
    QString memorynum;
    bool existmemory;
    bool error;
public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void input();
    void reset();
    void calc();
    void memorywork();
    void on_pbCLEAR_clicked();

    void on_pbPandM_clicked();

    void on_pbPoint_clicked();

    void on_pbCLEARNUMBER_clicked();

private:
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
