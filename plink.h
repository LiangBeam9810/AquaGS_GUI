#include "mainwindow.h"
#ifndef PLINK_H
#define PLINK_H

#include <QFile>
#include <QFileInfo>
#include <QObject>
#include <QStringList>
#include <QProcess>
#include <QMessageBox>
#include <QFile>
#include "tool.h"

#include <QApplication>
#include <QtConcurrent>
#include <QFuture>

class Plink : public Tool
{
public:
    Plink();

/*  !!! NOTICE:
 *
 * Any paht of binary genotype file didn't contain the suffix.
 *
*/
    bool part1(QString vcfFile, QString file2);
    bool part2(QString file2, QString geno, QString maf, QString mind, QString file3);
    bool part3(QString file3, QString hwe, QString file4);
    bool part4(QString file4, QString winsize, QString steplength, QString r2, QString file5);
    bool part5(QString file5, QString out);
    bool part6(QString file4, QString out);
    bool part_convert_format(QString vcfFile, QString out);

private:

    bool isVcfFile(QString file);


};

#endif // PLINK_H
