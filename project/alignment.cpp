#include "alignment.h"
#include <vector>
#include <QDebug>
#include <sstream>
#include <algorithm>

Alignment::Alignment(QString Seq1, QString Seq2, QString MatchData, int Score)
{
    this->Seq1 = Seq1;
    this->Seq2 = Seq2;
    this->MatchData = MatchData;
    this->Score = Score;
    this->creationDate = QDateTime::currentDateTime();
}

QString Alignment::Sequence1() {
    return this->Seq1;
}

QString Alignment::Sequence2() {
    return this->Seq2;
}
QString Alignment::MatchString() {
    return this->MatchData;
}

QString Alignment::Date() {
    return this->creationDate.toString("dd.MM.yyyy hh:mm");
}

QString Alignment::Scoring() {
    QString s = " Score: ";
    s.append(QString::number(this->Score));
    return (s);
}
