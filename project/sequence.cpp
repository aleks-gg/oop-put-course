
#include "sequence.h"

Sequence::Sequence(QString fasta)
{
    qsizetype FirstEndl = fasta.indexOf('\n', 1);
    this->Name = fasta.first(FirstEndl);
    this->Seq = (fasta.QString::last(fasta.QString::length() - FirstEndl - 1)).simplified().remove(' ');
}

int Sequence::Length() {
    return this->Seq.length();
}

QString Sequence::SeqName() {
    return this->Name;
}

QString Sequence::SeqData() {
    return this->Seq;
}
