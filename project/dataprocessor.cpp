
#include "dataprocessor.h"
#include <sstream>
#include <qDebug>

DataProcessor::DataProcessor()
{

}

QString DataProcessor::GCContent(Sequence *Seq) {
    float gc = 0;
    QString seq = Seq->SeqData();
    for (int i = 0; i<seq.length(); i++) {
        if (seq[i] == 'G' || seq[i] == 'C') {
            gc++;
        }
    }
    float gcp = (gc / seq.length()) * 100;
    QString gccontent = "GC Content: ";
    gccontent.append(QString::number(gcp));
    gccontent.append("%");
    return gccontent;
}

Alignment* DataProcessor::globalAlign(Sequence *Seq1, Sequence *Seq2,int matchScore, int mismatchScore, int gapScore) {
    QString Sequence1 = Seq1->SeqData();
    QString Sequence2 = Seq2->SeqData();
    QString Seq1aligned;
    QString Seq2aligned;
    QString matchData;
    int Score = 0;
    std::vector<std::vector<int>> M( Sequence1.length()+1 ,std::vector<int> (Sequence2.length()+1));
    for(int i = 0, j = 0; i<=Sequence1.length(); i++, j+=gapScore) {
        M[i][0] = j;
    }
    for(int i = 0, j = 0; i<=Sequence2.length(); i++, j+=gapScore) {
        M[0][i] = j;
    }
    for(int i = 1; i<=Sequence1.length(); i++) {
        for (int j = 1; j<=Sequence2.length(); j++) {
            int scoring;
            if (QString::compare(Sequence1[i-1], Sequence2[j-1], Qt::CaseInsensitive) == 0) {
                scoring = matchScore;
            } else {
                scoring = mismatchScore;
            }
            M[i][j] = std::max({M[i-1][j-1]+scoring, M[i-1][j]+gapScore, M[i][j-1]+gapScore});
        }
    }
    for(int i = Sequence1.length(), j = Sequence2.length(); i>0 && j>0;) {
        if (i==1 && j==1) {
            if (QString::compare(Sequence1[i-1], Sequence2[j-1], Qt::CaseInsensitive) == 0) {
                Seq1aligned.push_front(Sequence1[i-1]);
                Seq2aligned.push_front(Sequence2[j-1]);
                matchData.push_front('*');
                Score += matchScore;
            } else {
                Seq1aligned.push_front(Sequence1[i-1]);
                Seq2aligned.push_front(Sequence2[j-1]);
                matchData.push_front('|');
                Score += mismatchScore;
            }
            break;
        }
        if (i==1) {
            Seq1aligned.push_front('-');
            Seq2aligned.push_front(Sequence2[j-1]);
            matchData.push_front(' ');
            Score += gapScore;
            j--;
            continue;
        }
        if (j==1) {
            Seq1aligned.push_front(Sequence1[i-1]);
            Seq2aligned.push_front('-');
            matchData.push_front(' ');
            Score += gapScore;
            i--;
            continue;
        }
        if (M[i][j] - matchScore == M[i-1][j-1]) {
            Seq1aligned.push_front(Sequence1[i-1]);
            Seq2aligned.push_front(Sequence2[j-1]);
            matchData.push_front('*');
            Score += matchScore;
            i--;
            j--;
            continue;
        }
        if (M[i][j] - mismatchScore == M[i-1][j-1]) {
            Seq1aligned.push_front(Sequence1[i-1]);
            Seq2aligned.push_front(Sequence2[j-1]);
            matchData.push_front('|');
            Score += mismatchScore;
            i--;
            j--;
            continue;
        }
        if (M[i][j] - gapScore == M[i-1][j]) {
            Seq1aligned.push_front(Sequence1[i-1]);
            Seq2aligned.push_front('-');
            matchData.push_front(' ');
            Score += gapScore;
            i--;
            continue;
        }
        if (M[i][j] - gapScore == M[i][j-1]) {
            Seq1aligned.push_front('-');
            Seq2aligned.push_front(Sequence2[j-1]);
            matchData.push_front(' ');
            Score += gapScore;
            j--;
            continue;
        }
    }
    Alignment *aligned = new Alignment(Seq1aligned, Seq2aligned, matchData, Score);
    return aligned;
}
