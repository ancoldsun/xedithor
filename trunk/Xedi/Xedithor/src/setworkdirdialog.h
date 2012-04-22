#ifndef SETWORKDIRDIALOG_H
#define SETWORKDIRDIALOG_H


#include <QDialog>
#include <qfiledialog.h>
#include <qdir.h>

namespace Ui {
    class QFileDialog;
    class SetWorkDirDialog;
}

class SetWorkDirDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SetWorkDirDialog(QWidget *parent = 0);
    ~SetWorkDirDialog();
    /*
    * export format
    */
    enum SpriteExportFormat{
        binLibGDX =0,
        binCommon=1
    };
    QString getWorkDir() const {
        return m_pathTexturePacker;
    }
    QString getExportDir() const {
        return m_pathOut;
    }
    int getExportFormat() const {
        return m_expFormat;
    }
    void setPrevWorkDirPath(QString workDir,QString exportDir);

private:
    Ui::SetWorkDirDialog *ui;
    QString m_pathTexturePacker;
    QString m_pathOut;
    int m_expFormat;

private slots:
    void setPathTexturePacker();
    void setPathOut();
    void setExportFormat(int index);
};
#endif // SETWORKDIRDIALOG_H
