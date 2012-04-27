// Xedithor : 2D sprite editor
// Copyright [2011] Edi Ermawan <edi.ermawan@gmail.Com>

// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at

// http://www.apache.org/licenses/LICENSE-2.0

// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

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
