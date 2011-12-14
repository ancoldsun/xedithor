#ifndef EDITWINDOW_H
#define EDITWINDOW_H

#include <QMainWindow>
#include "graphwidgets.h"
#include "moduleslist.h"

QT_BEGIN_NAMESPACE
    class QAction;
    class QActionGroup;
    class QLabel;
    class QMenu;
    class QToolBar;
    class QScrollArea;
    class QScrollBar;
    class QFrame;
QT_END_NAMESPACE

namespace Ui {
    class EditWindow;
}

class EditWindow : public QMainWindow
{
    Q_OBJECT

public:

    explicit EditWindow(QWidget *parent = 0);
    ~EditWindow();
    ModulesList* getModuleList()
    {
        return modulesList;
    }

private slots:
    void ZoomOut();
    void ZoomIn();

private:
    Ui::EditWindow *ui;

    QScrollArea *scrollArea;

    QToolBar *windowEditToolBar;
    QAction* zoomInAct;
    QAction* zoomOutAct;

    void scaleImage(double factor);
    void adjustScrollBar(QScrollBar *scrollBar, double factor);


public:
     GraphWidget *imageLabel;
     QWidget* previewModule;
     QLabel *mouseInfoLabel;
     double scaleFactor;
     ModulesList* modulesList;
};

#endif // EDITWINDOW_H
