#include "mainwindow.h"
#include "./ui_mainwindow.h"

#include <QApplication>
#include <QWidget>
#include <QHBoxLayout>
#include <QListWidget>
#include <QLabel>
#include <QPushButton>
#include <QPalette>
#include <QPlainTextEdit>
#include <stdexcept>
#include <QFileDialog>
#include <QTimer>
#include <QRegularExpression>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , processor(new DataProcessor)
{
    ui->setupUi(this);
    connect(ui->Seq1loadButton, &QPushButton::clicked, this, &MainWindow::on_Seq1loadButton_clicked);
    connect(ui->Seq2loadButton, &QPushButton::clicked, this, &MainWindow::on_Seq2loadButton_clicked);
    connect(ui->processButton, &QPushButton::clicked, this, &MainWindow::on_ProcessButton_clicked);
    connect(ui->loadHistoryButton, &QPushButton::clicked, this, &MainWindow::on_loadHistoryButton_clicked);
}

MainWindow::~MainWindow()
{
    delete processor;
    delete ui;
}

bool MainWindow::isFASTA(QString fasta) {
    QRegularExpression regex("^>[\\w\\s]+\\n([ACGTURYMKSWHBVDNXN\\n]+)$");
    QRegularExpressionMatch match = regex.match(fasta);

    return match.hasMatch();
}
void MainWindow::AddHistoryItem(Alignment *alignment, Sequence *Seq1, Sequence *Seq2)
{
    QListWidget *listWidget = this->ui->History_listWidget;

    HistoryItem *newItem = new HistoryItem(listWidget, alignment, Seq1, Seq2);
    QListWidgetItem *item = new QListWidgetItem;

    item->setSizeHint(newItem->size());

    listWidget->addItem(item);
    listWidget->setItemWidget(item, newItem);
}

void MainWindow::LoadHistoryItem() {
    QListWidget *listWidget = this->ui->History_listWidget;
    try {
        HistoryItem *toLoad = dynamic_cast<HistoryItem*>(listWidget->itemWidget(listWidget->currentItem()));
        if (toLoad == nullptr) {
            throw std::exception();
        }
        ui->alignmentBrowser->clear();
        ui->alignmentBrowser->append(toLoad->LoadAlignment()->Sequence1());
        ui->alignmentBrowser->append(toLoad->LoadAlignment()->MatchString());
        ui->alignmentBrowser->append(toLoad->LoadAlignment()->Sequence2());

        ui->Seq1TextEdit->clear();
        ui->Seq1TextEdit->appendPlainText(toLoad->LoadSequence1()->SeqName());
        ui->Seq1TextEdit->appendPlainText(toLoad->LoadSequence1()->SeqData());

        ui->Seq2TextEdit->clear();
        ui->Seq2TextEdit->appendPlainText(toLoad->LoadSequence2()->SeqName());
        ui->Seq2TextEdit->appendPlainText(toLoad->LoadSequence2()->SeqData());
        ui->statusbar->showMessage("Data loaded correctly");

        ui->Seq1GCLabel->setText(processor->GCContent(toLoad->LoadSequence1()));
        ui->Seq2GCLabel->setText(processor->GCContent(toLoad->LoadSequence2()));
    } catch (const std::exception& e) {
        qWarning("No item chosen");
        ui->statusbar->showMessage("No item chosen");
    }
}

void MainWindow::on_loadHistoryButton_clicked()
{
    LoadHistoryItem();
}
void MainWindow::on_ProcessButton_clicked()
{
    try {
        if(!isFASTA(ui->Seq1TextEdit->toPlainText()) || !isFASTA(ui->Seq2TextEdit->toPlainText())) {
            throw std::exception();
        }
        Sequence *seq1 = new Sequence(ui->Seq1TextEdit->toPlainText());
        Sequence *seq2 = new Sequence(ui->Seq2TextEdit->toPlainText());
        int matchScore = ui->Match_spinBox->value();
        int mismatchScore = ui->Mismatch_spinBox->value();
        int gapScore = ui->Gap_spinBox->value();

        Alignment *aligned = (processor->globalAlign(seq1, seq2, matchScore, mismatchScore, gapScore));

        ui->alignmentBrowser->clear();
        ui->alignmentBrowser->append(aligned->Sequence1());
        ui->alignmentBrowser->append(aligned->MatchString());
        ui->alignmentBrowser->append(aligned->Sequence2());

        ui->Seq1GCLabel->setText(processor->GCContent(seq1));
        ui->Seq2GCLabel->setText(processor->GCContent(seq2));
        AddHistoryItem(aligned, seq1, seq2);
        ui->statusbar->showMessage("Data processed correctly");
    } catch (const std::exception& e) {
        qWarning() << "Input does not meet FASTA format";
        ui->statusbar->showMessage("Input does not meet FASTA format");
    }
}
void MainWindow::on_Seq1loadButton_clicked()
{
    QPointer<QPlainTextEdit> seq1Text = ui->Seq1TextEdit;

    auto fileContentReady = [seq1Text](const QString &fileName, const QByteArray &fileContent) {
        if (seq1Text.isNull()) {
            qDebug() << "Seq1TextEdit has been deleted";
        } else if (fileName.isEmpty()) {
            qDebug() << "No file selected";
        } else {
            seq1Text->setPlainText(fileContent);
        }
    };

    QTimer::singleShot(0, this, [=]() {
        QFileDialog::getOpenFileContent("FASTA (*.txt *.fasta)", fileContentReady);
    });
}


void MainWindow::on_Seq2loadButton_clicked()
{
    QPointer<QPlainTextEdit> seq2Text = this->ui->Seq2TextEdit;

    auto fileContentReady = [seq2Text](const QString &fileName, const QByteArray &fileContent) {
        if (seq2Text.isNull()) {
            qDebug() << "Seq2TextEdit has been deleted";
        } else if (fileName.isEmpty()) {
            qDebug() << "No file selected";
        } else {
            seq2Text->setPlainText(fileContent);
        }
    };

    QTimer::singleShot(0, this, [=]() {
        QFileDialog::getOpenFileContent("FASTA (*.txt *.fasta)", fileContentReady);
    });
}


