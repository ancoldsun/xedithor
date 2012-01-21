#include "packtextureparser.h"
#include <iostream>

PackTextureParser::PackTextureParser(QFile& file)
{
    m_textStream.setDevice(&file);
}

bool PackTextureParser::isStrMatchAvailable(QString str1, QString str2)
{
    if(str1.count()>str2.count()){
        return false;
    }
    bool isMatch=true;
    int i=0;

    for(int i=0;i<str1.count();i++){
        if(str1.at(i)!=str2.at(i)){
            isMatch=false;
            break;
        }
    }

    return isMatch;
}

QList<QString> PackTextureParser::parseValue(int start,QString str){
    QList<QString> result;

    QString buff="";
    for(int i=start;i<str.count();i++){
        QChar ch = str.at(i);
        if(ch != QChar::fromAscii(' ')){
            buff+=ch;
        }
    }
    QString buff2;
    int it=0;
    for(int i=0;i<buff.count();i++){
        QChar ch = buff.at(i);
        if(ch!=QChar::fromAscii(',')){
            buff2+=ch;
        }
        else {
            result.insert(it++,buff2);
            buff2="";
        }
    }
    result.insert(it,buff2);
    //foreach(QString s,result){
    //    qDebug(s.toUtf8());
    //}

    return result;
}

QList< QList<qint32> > PackTextureParser::doParsing()
{
    QList< QList<qint32> > result;
    QList<qint32> addResult;
    while(!m_textStream.atEnd()){
        QString str = m_textStream.readLine();

        if(isStrMatchAvailable("  xy:",str)){
            QList<QString>s = parseValue(5,str);
            addResult.append(s.at(0).toInt());
            addResult.append(s.at(1).toInt());
        }else if(isStrMatchAvailable("  size:",str)){
            QList<QString>s = parseValue(7,str);
            addResult.append(s.at(0).toInt());
            addResult.append(s.at(1).toInt());
        }else if(isStrMatchAvailable("  index:",str)){
            QList<QString>s = parseValue(8,str);
            addResult.push_front(s.at(0).toInt());
            result.append(addResult);
            addResult.clear();
        }
    }
    /*
    foreach(QList<qint32> items,result){
        foreach(qint32 item,items){
            std::cout<<item<<" ";
        }
        std::cout<<""<<std::endl;
    }
    */
    return result;
}
