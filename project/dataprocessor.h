
#ifndef DATAPROCESSOR_H
#define DATAPROCESSOR_H

#include <QString>
#include <vector>
#include "sequence.h"
#include "alignment.h"

class DataProcessor
{
public:
    DataProcessor();
    QString GCContent(Sequence *Seq);
    Alignment* globalAlign(Sequence *Seq1, Sequence *Seq2, int matchScore, int mismatchScore, int gapScore);
};

#endif // DATAPROCESSOR_H
