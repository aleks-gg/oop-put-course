#include "historyitem.h"
#include <QVBoxLayout>

HistoryItem::HistoryItem(QWidget *parent, Alignment *alignment, Sequence *Sequence1, Sequence *Sequence2)
    : QWidget(parent)
{
    this->resize(205, 80);
    this->aligned = alignment;
    this->Seq1 = Sequence1;
    this->Seq2 = Sequence2;
    seq1Label = new QLabel(this);
    seq2Label = new QLabel(this);
    dateScoreLabel = new QLabel(this);

    seq1Label->setFixedSize(200,30);
    seq2Label->setMinimumSize(200,30);
    dateScoreLabel->setMinimumSize(200,20);
    seq2Label->setMaximumSize(200,30);
    dateScoreLabel->setMaximumSize(200,20);

    seq1Label->setText(Seq1->SeqName());
    seq2Label->setText(Seq2->SeqName());
    dateScoreLabel->setText(aligned->Date() + " " + alignment->Scoring());
    QVBoxLayout *layout = new QVBoxLayout;
    layout->addWidget(seq1Label);
    layout->addWidget(seq2Label);
    layout->addWidget(dateScoreLabel);
    setLayout(layout);
}

Alignment* HistoryItem::LoadAlignment() {
    return this->aligned;
}

Sequence* HistoryItem::LoadSequence1() {
    return this->Seq1;
}

Sequence* HistoryItem::LoadSequence2() {
    return this->Seq2;
}
