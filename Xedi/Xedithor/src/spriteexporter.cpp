#include "spriteexporter.h"
#include "packtextureparser.h"

#include <QApplication>
#include <QProcess>
#include <iostream>

SpriteExporter::SpriteExporter(QPixmap& imgSource,
                               MFATableModel* moduleModel,
                               MFATableModel* frameModel,
                               MFATableModel* animModel,
                               int format)
{
    m_moduleModel    = moduleModel;
    m_frameModel     = frameModel;
    m_animModel      = animModel;
    m_exportedFormat = format;
    m_imgSource      = imgSource;
}

int  SpriteExporter::DoExporting()
{
    if (m_imgSource.isNull()) {
        std::cout<<"image source is NULL "<<std::endl;
        return 1;
    }
    if(m_exportedFormat==0)
    {
        std::cout<<"exportFLIBGDX "<<std::endl;
        // create text interface
        createSpriteDataInfo();
        return exportFLIBGDX();
    }
    else if(m_exportedFormat==1)
    {
        std::cout<<"exportFDefault "<<std::endl;
        // create text interface
        createSpriteDataInfo();
        return exportFDefault();
    }

    return 0;
}

int SpriteExporter::exportFLIBGDX()
{

    QString dirApp = QApplication::applicationDirPath();
    QDir dirTempImg(dirApp);

    dirTempImg.mkpath("temp/img");
    dirTempImg.mkpath("temp/outpack");
    dirTempImg.makeAbsolute();

    QString fileTempImgDir        = dirApp+"/temp/img/";
    QString fileTempPackOutDir    = dirApp+"/temp/outpack/";

    // ------slice image
    for(int i=0;i<m_moduleModel->rowCount();i++)
    {
        //std::cout<<"ROW: "<<i<<std::endl;
        RowData* rd = m_moduleModel->getDatainRow(i);

        QString id_ =rd->getData(1);
        qreal px_   =rd->getData(2).toDouble();
        qreal py_   =rd->getData(3).toDouble();
        qreal w_    =rd->getData(4).toDouble();
        qreal h_    =rd->getData(5).toDouble();

        /* slice image */
        QPixmap pieceImage =m_imgSource.copy(px_, py_, w_, h_);
        pieceImage.save(fileTempImgDir+"mod_"+id_+".png",0,-1);
    }

    // ------execute texture packer (external executable jar)
    QProcess packerProc(this);
    QStringList arg;
    arg.append("-jar");
    arg.append(m_texturePackerDir);
    arg.append(fileTempImgDir);
    arg.append(fileTempPackOutDir);

    //packerProc.waitForFinished(-1);
    //m_pstdout = packerProc.readAllStandardOutput();
    //m_pstderr = packerProc.readAllStandardError();
    packerProc.execute("java",arg);

    // ------read out pack for parse
    QFile fileOut(fileTempPackOutDir+"pack");
    if(!fileOut.open(QIODevice::ReadOnly)) {
        std::cout<<"packout.txt cann't by opened' "<<std::endl;
        return 2;
    }
    PackTextureParser parser(fileOut);
    QList< QList<qint32> > result = parser.doParsing();

    // -------initialize write to stream
    QFile fileBinOut(m_exportOutDir);
    fileBinOut.open(QIODevice::WriteOnly);
    QDataStream streamOut(&fileBinOut);

    // -------write image
    QFile fileimg(fileTempPackOutDir+"img1.png");
    if (!fileimg.open(QIODevice::ReadOnly)){
        return 3;
    }
    QByteArray blob = fileimg.readAll();
    streamOut <<blob;

    // -------writing modules
    streamOut << (quint32)0xEFFE0EEF;
    streamOut << (qint32)result.count(); // N-module

    foreach(QList<qint32> items,result){
        foreach(qint32 item,items){
            streamOut << (qint32)item;
        }
    }
    // -------writing frames
    writeFrames(streamOut);
    // -------writing anim
    writeAnims(streamOut);

    // -------close opened files
    fileBinOut.close();
    fileOut.close();
    fileimg.close();

    // ------ delete temp dirs & files

    QDir delDir(dirApp+"/temp/img/");
    QFileInfoList files = delDir.entryInfoList(QDir::NoDotAndDotDot | QDir::Files);
    for(int file = 0; file < files.count(); file++)
    {
        delDir.remove(files.at(file).fileName());
    }
    delDir.rmdir(delDir.path());

    QDir delDir2(dirApp+"/temp/outpack/");
    QFileInfoList files2 = delDir2.entryInfoList(QDir::NoDotAndDotDot | QDir::Files);
    for(int file = 0; file < files2.count(); file++)
    {
        delDir2.remove(files2.at(file).fileName());
    }
    delDir2.rmdir(delDir2.path());

    QDir delDir3(dirApp+"/temp/");
    delDir3.rmdir(delDir3.path());

    return 0;
}

int SpriteExporter::exportFDefault()
{
    QString dirApp = QApplication::applicationDirPath();
    QDir dirTempImg(dirApp);

    dirTempImg.mkpath("temp/img");
    dirTempImg.mkpath("temp/outpack");
    dirTempImg.makeAbsolute();

    // -------initialize write to stream
    QFile fileBinOut(m_exportOutDir);
    fileBinOut.open(QIODevice::WriteOnly);
    QDataStream streamOut(&fileBinOut);

    // -------write image
    QFile fileimg(m_imgSourcePath);
    if (!fileimg.open(QIODevice::ReadOnly)){
        return 3;
    }
    QByteArray blob = fileimg.readAll();
    streamOut <<blob;

    // -------writing modules
    writeModules(streamOut);
    // -------writing frames
    writeFrames(streamOut);
    // -------writing anim
    writeAnims(streamOut);

    // -------close opened files
    fileBinOut.close();
    fileimg.close();

    return 0;
}

void SpriteExporter::writeModules(QDataStream& streamOut)
{
    streamOut << (quint32)0xEFFE0EEF;
    int numberRow = m_moduleModel->rowCount();
    streamOut << (qint32)numberRow;

    for(int ix=0;ix<numberRow;ix++)
    {
        RowData* rd = m_moduleModel->getDatainRow(ix);
        int _Idmodule = rd->getData(1).toInt();
        int _modX     = rd->getData(2).toInt();
        int _modY     = rd->getData(3).toInt();
        int _modW     = rd->getData(4).toInt();
        int _modH     = rd->getData(5).toInt();

        streamOut << (qint32)_Idmodule;
        streamOut << (qint32)_modX;
        streamOut << (qint32)_modY;
        streamOut << (qint32)_modW;
        streamOut << (qint32)_modH;
    }
}

void SpriteExporter::writeFrames(QDataStream& streamOut)
{
    // write frame
    streamOut << (quint32)0xFFFA0EFF;
    int numberRow = m_frameModel->rowCount();
    streamOut << (qint32)numberRow;
    for(int ix=0;ix<numberRow;ix++)
    {
        RowData* rd = m_frameModel->getDatainRow(ix);
        int IdFrame = rd->getData(1).toInt();
        int nModFrame = rd->getData(2).toInt();
        streamOut << (qint32)IdFrame;
        streamOut << (qint32)nModFrame;

        MFATableModel* m  = m_frameModel->getModel(ix);
        int nModuleInFrame = m->rowCount();

        for(int iy=0;iy<nModuleInFrame;iy++)
        {
            RowData* rd2 = m->getDatainRow(iy);
            int modID = rd2->getData(1).toInt();
            int offX = rd2->getData(2).toInt();
            int offY = rd2->getData(3).toInt();

            streamOut << (qint32)modID;
            streamOut << (qint32)offX;
            streamOut << (qint32)offY;
            streamOut << (qint32)32;//dummy
            streamOut << (qint32)32;//dummy
        }
    }
}

void SpriteExporter::writeAnims(QDataStream& streamOut)
{
    // write anims
    streamOut << (quint32)0xEEEA0EFF;
    int numberRow = m_animModel->rowCount();
    streamOut << (qint32)numberRow;

    for(int ix=0;ix<numberRow;ix++)
    {
        RowData* rd  = m_animModel->getDatainRow(ix);
        int IdAnim   = rd->getData(1).toInt();
        int nFrmAnim = rd->getData(2).toInt();
        streamOut << (qint32)IdAnim;
        streamOut << (qint32)nFrmAnim;

        MFATableModel* m  = m_animModel->getModel(ix);
        int nFrameAnim = m->rowCount();

        for(int iy=0;iy<nFrameAnim;iy++)
        {
            RowData* rd2 = m->getDatainRow(iy);
            int FrmID=rd2->getData(1).toInt();
            int offX =rd2->getData(2).toInt();
            int offY =rd2->getData(3).toInt();

            streamOut << (qint32)FrmID;
            streamOut << (qint32)offX;
            streamOut << (qint32)offY;
            streamOut << (qint32)16;//dummy
            streamOut << (qint32)16;//dummy
        }
    }
}

void SpriteExporter::createSpriteDataInfo()
{
    // create interface
    QFileInfo infof(m_exportOutDir);
    QDir infod= infof.dir();
    QString strDir = infod.absolutePath();
    m_sprName = m_sprName.toUpper();
    QString s=strDir+"/"+m_sprName+".java";
    QFile file(s);
    if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
    {
       return;
    }
    QTextStream interfaceText(&file);
    interfaceText<<"interface SPRITE_"<<m_sprName<<"\n";
    // start brace
    interfaceText<<"{"<<"\n";

    //frame part
    int numberRow = m_frameModel->rowCount();
    for(int ix=0;ix<numberRow;ix++)
    {
        RowData* rd = m_frameModel->getDatainRow(ix);
        QString nameFrame = rd->getData(3);
        nameFrame +="_"+QString::number(ix);
        nameFrame = nameFrame.toUpper();
        interfaceText <<"	public final static int " << nameFrame <<" = "<<ix<<";"<< "\n";
    }
    interfaceText <<"	public final static int FRAME_COUNT" << " = "<<numberRow<<";"<<"\n";

    interfaceText <<"\n";

    //anim part
    numberRow = m_animModel->rowCount();
    for(int ix=0;ix<numberRow;ix++)
    {
        RowData* rd = m_animModel->getDatainRow(ix);
        QString nameAnim = rd->getData(3);
        nameAnim +="_"+QString::number(ix);
        nameAnim = nameAnim.toUpper();
        interfaceText <<"	public final static int " << nameAnim <<" = "<<ix<<";"<< "\n";
    }
    interfaceText <<"	public final static int ANIM_COUNT" << " = "<<numberRow<<";"<<"\n";

    //end brace
    interfaceText<<"}"<<"\n";

    file.close();
}




