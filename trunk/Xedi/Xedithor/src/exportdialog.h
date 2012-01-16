// Xedithor : 2D sprite editor
// Copyright (C) 2011-2011 Edi Ermawan <edi.ermawan@gmail.Com>
// License  :
//

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
