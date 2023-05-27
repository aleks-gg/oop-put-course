#ifndef ALIGNMENT_H
#define ALIGNMENT_H

#include <QChar>
#include <QString>
#include <vector>
#include <QDateTime>
#include <QTextStream>

class Alignment
{
public:
    Alignment(QString Seq1, QString Seq2, QString MatchData, int Score);
    QString Sequence1();
    QString Sequence2();
    QString MatchString();
    QString Date();
    QString Scoring();
    ~Alignment();
private:
    int Score;
    QString Seq1;
    QString Seq2;
    QString MatchData;
    QDateTime creationDate;
};

#endif // ALIGNMENT_H
