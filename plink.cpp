#include "plink.h"
#include "process.h"

Plink::Plink()
{
    this->paramlist.clear();
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
}


