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

#ifndef EXPORTDIALOG_H
#define EXPORTDIALOG_H

#include <QDialog>
#include <qfiledialog.h>
#include <qdir.h>

namespace Ui {
    class QFileDialog;
    class ExportDialog;
}

class ExportDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ExportDialog(QWidget *parent = 0);
    ~ExportDialog();
    /*
    * export format
    */
    enum SpriteExportFormat{
        binLibGDX =0,
        binCommon=1
    };
    QString getTexturePacker() const {
        return m_pathTexturePacker;
    }
    QString getTexturePackerOut() const {
        return m_pathOut;
    }
    int getExportFormat() const {
        return m_expFormat;
    }

private:
    Ui::ExportDialog *ui;
    QString m_pathTexturePacker;
    QString m_pathOut;
    int m_expFormat;

private slots:
    void setPathTexturePacker();
    void setPathOut();
    void setExportFormat(int index);
};

#endif // EXPORTDIALOG_H
