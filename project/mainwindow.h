
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "dataprocessor.h"
#include "historyitem.h"
#include "alignment.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow

{
    Q_OBJECT

public:
    void AddHistoryItem(Alignment *alignment, Sequence *Seq1, Sequence *Seq2);
    void LoadHistoryItem();
    void on_Seq1loadButton_clicked();
    void on_Seq2loadButton_clicked();
    void on_ProcessButton_clicked();
    void on_loadHistoryButton_clicked();
    bool isFASTA(QString fasta);
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    DataProcessor *processor;
};

#endif // MAINWINDOW_H
