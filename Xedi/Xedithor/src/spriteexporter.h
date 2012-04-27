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
    void setSprName(QString sprname)  {
        m_sprName =sprname;
    }

    // QString m_pstdout;
    // QString m_pstderr;

private:
    MFATableModel* m_moduleModel;
    MFATableModel* m_frameModel;
    MFATableModel* m_animModel;
    int m_exportedFormat;
    QPixmap m_imgSource;
    QString m_texturePackerDir;
    QString m_exportOutDir;
    QString m_imgSourcePath;
    QString m_sprName;


    int exportFLIBGDX();
    int exportFDefault();
    void writeModules(QDataStream& streamOut);
    void writeFrames(QDataStream& streamOut);
    void writeAnims(QDataStream& streamOut);
    void createSpriteDataInfo();
};

#endif // SPRITEEXPORTER_H
