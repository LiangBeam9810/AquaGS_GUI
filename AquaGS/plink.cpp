#include "plink.h"
#include "start.h"
#include<QTime>

//延时功能
void sleep(unsigned int msec){
//currnentTime 返回当前时间 用当前时间加上我们要延时的时间msec得到一个新的时刻
    QTime reachTime = QTime::currentTime().addMSecs(msec);
    //用while循环不断比对当前时间与我们设定的时间
    while(QTime::currentTime()<reachTime){
    //如果当前的系统时间尚未达到我们设定的时刻，就让Qt的应用程序类执行默认的处理，
    //以使程序仍处于响应状态。一旦到达了我们设定的时刻，就跳出该循环，继续执行后面的语句。
        QApplication::processEvents(QEventLoop::AllEvents,100);
    }
}

Plink::Plink()
{
    this->paramlist.clear();
}

bool MainWindow::callPlinkGwas(QString* genotype, QString out)
{

    QString runPath1 = QDir::currentPath();

    QString maf = ui->mafcheckBox->isChecked()? ui->mafdoubleSpinBox->text():nullptr;
    QString mind = ui->mindcheckBox->isChecked()? ui->minddoubleSpinBox->text():nullptr;
    QString geno = ui->genocheckBox->isChecked()? ui->genodoubleSpinBox->text():nullptr;
    QString hwe = ui->hwcheckBox->isChecked()? ui->hwdoubleSpinBox->text():nullptr;

    QString plinkpath = runPath1.append("/plink/");
    qDebug() << endl <<"plinkpath:" << plinkpath << endl;

    qDebug() <<"plink_log_path:" << plink_log_path << endl;
    if(isDirExist(plink_log_path))//if plink_log_path if exit ,delete it and rebuild
    {
        qDebug() <<endl <<"the path :"<<plink_log_path<<" exists already.";
        QDir qDir;
        qDir.setPath(plink_log_path);
        qDir.removeRecursively();
        while(isDirExist(plink_log_path));
        QDir qDir1(plink_log_path);
        if(qDir1.mkdir((plink_log_path))) {
            qDebug() <<plink_log_path<<" create success";
        }
        else
        {
            qDebug() <<plink_log_path<<" create fail";
        }
    }
    else { //if not exist , create plink_log_path
        QDir qDir(plink_log_path);
        if(qDir.mkdir((plink_log_path))) {
            qDebug() <<plink_log_path<<" create success";
        }
        else
        {
            qDebug() <<plink_log_path<<" create fail";
        }

    }

    QString file2=plink_log_path+"/file2";
    QString file3=plink_log_path+"/file3";
    QString file4=plink_log_path+"/file4";
    QString file5=plink_log_path+"/file5";
    QString outfile=out+"/vcf_after_qc";

    Plink plink;
    Process* plink_process;
    plink_process = new Process;

    plink.part1(*genotype, file2);
    if (!(plink_process->runExTool(plinkpath+"plink", plink.getParamList())))
    {
        qDebug() << endl <<"plink part1 error:"  << endl;
        return false;
    }
    plink_process = new Process;
    plink.part2(file2, geno, maf, mind, file3);
    if (!(plink_process->runExTool(plinkpath+"plink", plink.getParamList())))
    {
        return false;
    }
    sleep(500);
    plink_process = new Process;
    plink.part3(file3, hwe, file4);
    if (!(plink_process->runExTool(plinkpath+"plink", plink.getParamList())))
    {
        return false;
    }
    sleep(500);
    
    if (ui->swcheckBox->isChecked())
    {
        QString winSize, stepLen, r2Threshold;

        winSize = ui->winsizedoubleSpinBox->text();
        stepLen = ui->steplengthdoubleSpinBox->text();
        r2Threshold = ui->r2doubleSpinBox->text();
        plink_process = new Process;
        plink.part4(file4, winSize, stepLen, r2Threshold, file5);
        if (!(plink_process->runExTool(plinkpath+"plink", plink.getParamList())))
        {
            return false;
        }

        sleep(500);
        plink_process = new Process;
        plink.part5(file5, outfile);
        if (!(plink_process->runExTool(plinkpath+"plink", plink.getParamList())))
        {
            return false;
        }


    }
    else
    {
        plink_process = new Process;
        plink.part6(file4, outfile);
        if (!(plink_process->runExTool(plinkpath+"plink", plink.getParamList())))
        {
            return false;
        }
        sleep(500);

    }
    if(isFileExist(outfile+".vcf")) *genotype = outfile+".vcf"; //update genotype after qc
    else {
        return false;
    }
    return true;

}

bool MainWindow::plink_convert_format(QString* genotype, QString out)
{
    QString runPath1 = QDir::currentPath();
    QString plinkpath = runPath1.append("/plink/");
    QString outfile_raw_path = out+"/raw_data";//without .raw
    qDebug() << endl <<"plinkpath:" << plinkpath ;
    qDebug() <<"outfile_raw_path:" << outfile_raw_path ;
    if(isFileExist(*genotype))
    {
        if(isFileExist(outfile_raw_path+".raw"))
        {
            QFile::remove(outfile_raw_path);
        }
        Plink plink;
        Process* plink_process;
        plink_process = new Process;
        plink.part_convert_format(*genotype,outfile_raw_path);
        if (!(plink_process->runExTool(plinkpath+"plink", plink.getParamList())))
        {
            qDebug() << endl <<"plink part_convert_format error:"  << endl;
            return false;
        }
        if (isFileExist(outfile_raw_path+".raw"))
        {
            *genotype = outfile_raw_path+".raw";
            return  true;
        }
        else {
            qDebug() << endl <<(outfile_raw_path+".raw is not finded")<< endl;
            return  false;
        }
    }
    else {
        qDebug() << endl <<(*genotype+" is not finded")<< endl;
        return  false;
    }
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
    this->paramlist.append("0");
    this->paramlist.append("--recode");
    this->paramlist.append("--out");
    this->paramlist.append(file2);
    qDebug()<<("plink out"+this->paramlist.join(" "));

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
    qDebug()<<("plink out"+this->paramlist.join(" "));
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
    qDebug()<<("plink out"+this->paramlist.join(" "));
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
    qDebug()<<("plink out"+this->paramlist.join(" "));
    return true;

}

bool Plink::part5(QString file5, QString out)
{
    //./plink --file file5 --allow-extra-chr --recode vcf-iid --out out
    if (file5.isNull() || out.isNull())
    {
        return false;
    }
    this->paramlist.clear();
    this->paramlist.append("--file");
    this->paramlist.append(file5);
    this->paramlist.append("--allow-extra-chr");
    this->paramlist.append("--recode");
    this->paramlist.append("vcf-iid");
    this->paramlist.append("--out");
    this->paramlist.append(out);
    qDebug()<<("plink out"+this->paramlist.join(" "));
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
    this->paramlist.append("--recode");
    this->paramlist.append("vcf-iid");
    this->paramlist.append("--out");
    this->paramlist.append(out);
    qDebug()<<("plink out"+this->paramlist.join(" "));
    return true;
}

bool Plink::part_convert_format(QString vcfFile, QString out)
{
    if (vcfFile.isNull() || out.isNull())
    {
        return false;
    }
    //plink --vcf vcfFile  --recodeA --const-fid 0 --allow-extra-chr --out file.raw

    this->paramlist.clear();            // Clear paramlist before set parameter.
    this->paramlist.append("--vcf");
    this->paramlist.append(vcfFile);
    this->paramlist.append("--allow-extra-chr");
    this->paramlist.append("--const-fid");
    this->paramlist.append("0");
    this->paramlist.append("--recodeA");
    this->paramlist.append("--out");
    this->paramlist.append(out);
    qDebug()<<("plink out"+this->paramlist.join(" "));

    return true;
}
