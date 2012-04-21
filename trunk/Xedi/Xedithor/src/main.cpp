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


class XedithorApp : public QApplication {
public:
  XedithorApp(int& argc, char ** argv) :
    QApplication(argc, argv) { }
  virtual ~XedithorApp() { }

  // reimplemented from QApplication so we can throw exceptions in slots
  virtual bool notify(QObject * receiver, QEvent * event) {
    try {
      return QApplication::notify(receiver, event);
    } catch(std::exception& e) {
      std::cout << "XedithorApp Exception thrown:" << e.what()<<std::endl;
    }
    return false;
  }
};

int main(int argc, char *argv[])
{
    XedithorApp a(argc, argv);

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
