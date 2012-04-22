// Xedithor : 2D sprite editor
// Copyright (C) 2011-2011 Edi Ermawan <edi.ermawan@gmail.Com>
// License  :
//

#ifndef EDITWINDOW_H
#define EDITWINDOW_H


#include <QMainWindow>
#include <qabstractitemmodel.h>

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
    inline ModulesList* getModuleList() {
        return modulesList;
    }

    void setModuleList_Module();
    void setModuleList_Frame();
    void setModuleList_Anim();
    void setupViewModule();
    void setupViewFrame();
    void setupViewAnim();
    void createAnimation();

private slots:
    void ZoomOut();
    void ZoomIn();

private:
    Ui::EditWindow *ui;
    QScrollArea *scrollArea;
    QToolBar *windowEditToolBar;
    QAction* zoomInAct;
    QAction* zoomOutAct;
    QLabel* m_FpsLabel;
    int m_modeView;
    void scaleImage(double factor);
    void adjustScrollBar(QScrollBar *scrollBar, double factor);

public:
     GraphWidget *imageLabel;
     QWidget* previewModule;
     QLabel *mouseInfoLabel;
     double scaleFactor;
     ModulesList* modulesList;
public slots:
     void FrameDoubleClicked(const QModelIndex& index);
     void setTimerInterval(int value);

};

#endif // EDITWINDOW_H
