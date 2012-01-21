// Xedithor : 2D sprite editor
// Copyright (C) 2011-2011 Edi Ermawan <edi.ermawan@gmail.Com>
// License  :
//

#ifndef SPRITEEXPORTER_H
#define SPRITEEXPORTER_H

#include <QPixmap>
#include <QDir>
#include "mfatablemodel.h"

class SpriteExporter : public QObject
{
    Q_OBJECT
public:
    SpriteExporter(QPixmap& imgSource,MFATableModel* moduleModel,
                   MFATableModel* frameModel,MFATableModel* animModel,int format);
    int DoExporting();
    void setTexturePackerPath(QString texturePackerDir)  {
        m_texturePackerDir = texturePackerDir;
    }
    void setExportOutPath(QString exportOutDir)  {
        m_exportOutDir = exportOutDir;
    }
    void setImgSrcPath(QString imgSourcePath)  {
        m_imgSourcePath =imgSourcePath;
    }

private:
    MFATableModel* m_moduleModel;
    MFATableModel* m_frameModel;
    MFATableModel* m_animModel;
    int m_exportedFormat;
    QPixmap m_imgSource;
    QString m_texturePackerDir;
    QString m_exportOutDir;
    QString m_imgSourcePath;

    int exportFLIBGDX();
    int exportFDefault();
    void writeModules(QDataStream& streamOut);
    void writeFrames(QDataStream& streamOut);
    void writeAnims(QDataStream& streamOut);
};

#endif // SPRITEEXPORTER_H
