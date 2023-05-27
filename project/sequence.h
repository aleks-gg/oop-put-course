
#ifndef SEQUENCE_H
#define SEQUENCE_H

#include <QString>


class Sequence
{
public:
    Sequence(QString fasta);
    int Length();
    QString SeqName();
    QString SeqData();
private:
    QString Name;
    QString Seq;
};

#endif // SEQUENCE_H
