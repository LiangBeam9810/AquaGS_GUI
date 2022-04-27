#include "h_matrix.h"

bool bilud_H_matrix(QString Rdata_path ,QString output_path,QString* H_matrix_path)
{
    QStringList files_name_of_qc_produce = {"H_matrix.txt"};
    init_file(output_path,files_name_of_qc_produce);
    *H_matrix_path = output_path+"/H_matrix.txt";
    QString runPath = QDir::currentPath();
    runPath.append("/rscript/H_matrix_build.R");
    qDebug() << endl <<"runPath:" << runPath << endl;
    QString param;
    // The sequence of param is not changeable
    param.clear();
    param.append("Rscript");
    param.append(" ");
    param.append(runPath);
    param.append(" ");
    param.append(Rdata_path);
    param.append(" ");
    param.append(H_matrix_path);
    param.append(" ");
    qDebug()<< endl<<"H matirx param :"<<param<< endl;
    Process *H_matirx_build_process;
    H_matirx_build_process = new Process;
    if(!H_matirx_build_process->runRscript(param," Building H matirx "))
    {
        QMessageBox::warning(nullptr, "Process error:", "Can't open the H matirx build process!");
        return false;
    }
    if(!(isFileExist(*H_matrix_path)))
    {
        QMessageBox::warning(nullptr, "Process error:", "Can't find the H matirx file! "+*H_matrix_path);
        return false;
    }
    qDebug()<< endl<<"H matirx done! :"<<param<< endl;


    return true;
}
