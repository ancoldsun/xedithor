// Xedithor : 2D sprite editor
// Copyright (C) 2011-2011 Edi Ermawan <edi.ermawan@gmail.Com>
// License  :
//

#ifndef PACKTEXTUREPARSER_H
#define PACKTEXTUREPARSER_H

#include <qtextstream.h>
#include <qfile.h>
#include <qstring.h>
#include <QList>

class PackTextureParser
{
public:
    PackTextureParser(QFile& file);
    QList< QList<qint32> > doParsing();
private:
    QTextStream m_textStream;
    bool isStrMatchAvailable(QString str1,QString str2);
    QList<QString> parseValue(int start,QString str);
};

#endif // PACKTEXTUREPARSER_H
