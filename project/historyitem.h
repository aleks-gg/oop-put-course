#ifndef HISTORYITEM_H
#define HISTORYITEM_H

#include <QWidget>
#include <QLabel>
#include "alignment.h"
#include "sequence.h"

class HistoryItem : public QWidget {
    Q_OBJECT
public:
    HistoryItem(QWidget *parent = nullptr, Alignment *alignment = nullptr, Sequence *Sequence1 = nullptr, Sequence *Sequence2 = nullptr);
    Alignment* LoadAlignment();
    Sequence* LoadSequence1();
    Sequence* LoadSequence2();
private:
    Alignment *aligned;
    Sequence *Seq1;
    Sequence *Seq2;

    QLabel *seq1Label;
    QLabel *seq2Label;
    QLabel *dateScoreLabel;
};

#endif // HISTORYITEM_H
