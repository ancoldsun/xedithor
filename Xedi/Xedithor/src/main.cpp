#include <QtGui/QApplication>
#include "mainwindow.h"

bool compareStr(char *str1,char *str2)
{
    while(*str1!='\0')
    {
        if(*str1++ != *str2++)
            return false;
    }
    return true;
}

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    MainWindow w;

    if(argc > 1 ) {
        if(compareStr(argv[1],"export")) {
            return w.exportAllSilent();
        } else {
            std::cout<<"for exporting , usage: xedithor export"<<std::endl;
            return 0;
        }
    }
    else {
        w.show();
        return a.exec();
    }
}
