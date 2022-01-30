#include "plink.h"

Plink::Plink()
{
    this->paramlist.clear();
}

bool MainWindow::callPlinkGwas(QString genotype, QString out)
{

    QString runPath1 = QDir::currentPath();
    qDebug() << endl <<"runPath1:" << runPath1 << endl;

    QString maf = ui->mafcheckBox->isChecked()? ui->mafdoubleSpinBox->text():nullptr;
    QString mind = ui->mindcheckBox->isChecked()? ui->minddoubleSpinBox->text():nullptr;
    QString geno = ui->genocheckBox->isChecked()? ui->genodoubleSpinBox->text():nullptr;
    QString hwe = ui->hwcheckBox->isChecked()? ui->hwdoubleSpinBox->text():nullptr;

    QString plinkpath = runPath1.append("/plink/");
    //这里修改生成的中间文件和输出raw的路径
    QString file2=plinkpath+"files/"+"file2";
    QString file3=plinkpath+"files/"+"file3";
    QString file4=plinkpath+"files/"+"file4";
    QString file5=plinkpath+"files/"+"file5";
    QString outfile=out+"/raw_output";
    raw_path = outfile+".raw";
    Plink plink;
    Process* plink_process;
    plink_process = new Process;
    plink.part1(genotype, file2);
    if (!(plink_process->runExTool(plinkpath+"plink", plink.getParamList())))
    {
        qDebug() << endl <<"plink part1 error:"  << endl;
        return false;
    }

    plink.part2(file2, geno, maf, mind, file3);
    if (!(plink_process->runExTool(plinkpath+"plink", plink.getParamList())))
    {
        return false;
    }

    plink.part3(file3, hwe, file4);
    if (!(plink_process->runExTool(plinkpath+"plink", plink.getParamList())))
    {
        return false;
    }

    if (ui->swcheckBox->isChecked())
    {
        QString winSize, stepLen, r2Threshold;

        winSize = ui->winsizedoubleSpinBox->text();
        stepLen = ui->steplengthdoubleSpinBox->text();
        r2Threshold = ui->r2doubleSpinBox->text();
        plink.part4(file4, winSize, stepLen, r2Threshold, file5);
        if (!(plink_process->runExTool(plinkpath+"plink", plink.getParamList())))
        {
            return false;
        }
        plink.part5(file5, outfile);
        if (!(plink_process->runExTool(plinkpath+"plink", plink.getParamList())))
        {
            return false;
        }

    }
    else
    {
        plink.part6(file4, outfile);
        if (!(plink_process->runExTool(plinkpath+"plink", plink.getParamList())))
        {
            return false;
        }

    }

    return true;

}

bool Plink::part1(QString vcfFile, QString file2)
{
    //./plink --vcf snp_abt_630_imput_out_select48K.vcf --allow-extra-chr --threads 20 --const-fid --recode --out file2
    if (vcfFile.isNull() || file2.isNull())
    {
        return false;
    }

    //plink --vcf vcfFile [--maf maf] [--mind mind] [--geno geno] --recode --out out

    this->paramlist.clear();            // Clear paramlist before set parameter.
    this->paramlist.append("--vcf");
    this->paramlist.append(vcfFile);
    this->paramlist.append("--allow-extra-chr");
    this->paramlist.append("--threads");
    this->paramlist.append("20");
    this->paramlist.append("--const-fid");

    this->paramlist.append("--recode");
    this->paramlist.append("--out");
    this->paramlist.append(file2);
    //this->paramlist.append("--noweb");

    return true;
}

bool Plink::part2(QString file2, QString geno, QString maf, QString mind, QString file3)
{
    //./plink --file file2 --allow-extra-chr --geno 0.1 --maf 0.05 --mind 0.1 --recode --out file3
    if (file2.isNull() || file3.isNull())
    {
        return false;
    }
    this->paramlist.clear();
    this->paramlist.append("--file");
    this->paramlist.append(file2);
    this->paramlist.append("--allow-extra-chr");

    if (!geno.isNull())
    {
        this->paramlist.append("--geno");
        this->paramlist.append(geno);
    }
    if (!maf.isNull())
    {
        this->paramlist.append("--maf");
        this->paramlist.append(maf);
    }
    if (!mind.isNull())
    {
        this->paramlist.append("--mind");
        this->paramlist.append(mind);
    }
    this->paramlist.append("--recode");
    this->paramlist.append("--out");
    this->paramlist.append(file3);
    return true;
}

bool Plink::part3(QString file3, QString hwe,QString file4)
{
    //./plink --file file3 --allow-extra-chr --hwe 0.001 -recode --out file4
    if (file3.isNull() || file4.isNull())
    {
        return false;
    }
    this->paramlist.clear();
    this->paramlist.append("--file");
    this->paramlist.append(file3);
    this->paramlist.append("--allow-extra-chr");

    if (!hwe.isNull())
    {
        this->paramlist.append("--hwe");
        this->paramlist.append(hwe);
    }

    this->paramlist.append("--recode");
    this->paramlist.append("--out");
    this->paramlist.append(file4);
    return true;
}

bool Plink::part4(QString file4, QString winsize, QString steplength, QString r2, QString file5)
{
    //./plink --file file4 --allow-extra-chr --indep-pairwise 50 5 0.5 --recode --out file5

    if (file4.isNull() || file5.isNull())
    {
        return false;
    }
    this->paramlist.clear();
    this->paramlist.append("--file");
    this->paramlist.append(file4);
    this->paramlist.append("--allow-extra-chr");

    this->paramlist.append("--indep-pairwise");
    this->paramlist.append(winsize);
    this->paramlist.append(steplength);
    this->paramlist.append(r2);

    this->paramlist.append("--recode");
    this->paramlist.append("--out");
    this->paramlist.append(file5);
    return true;

}

bool Plink::part5(QString file5, QString out)
{
    //./plink --file file5 --allow-extra-chr --recodeA --out out
    if (file5.isNull() || out.isNull())
    {
        return false;
    }
    this->paramlist.clear();
    this->paramlist.append("--file");
    this->paramlist.append(file5);
    this->paramlist.append("--allow-extra-chr");
    this->paramlist.append("--recodeA");
    this->paramlist.append("--out");
    this->paramlist.append(out);
    return true;
}

bool Plink::part6(QString file4, QString out)
{
    if (file4.isNull() || out.isNull())
    {
        return false;
    }
    this->paramlist.clear();
    this->paramlist.append("--file");
    this->paramlist.append(file4);
    this->paramlist.append("--allow-extra-chr");
    this->paramlist.append("--recodeA");
    this->paramlist.append("--out");
    this->paramlist.append(out);
    return true;
}


