#ifndef EMSCONFIGEXPORT_H
#define EMSCONFIGEXPORT_H

#include <QString>
#include "./projdata/Tag.h"

class EmsConfigExport
{
public:
    static EmsConfigExport& GetInstance();
    ~EmsConfigExport();
    void Export();
protected:
    EmsConfigExport();
    EmsConfigExport(const EmsConfigExport&) = delete;
    EmsConfigExport& operator=(const EmsConfigExport&) = delete;

    void ExportStationCfg();
    void ExportDevModleCfg();
    void ExportRedisCfg();

    void SaveFile(QString fileName, QString output);

    void ExportBmsDevCfg(QMap<QString, QVector<QSharedPointer<Tag>>>& tagMap, QString devName, QString& output);
    void ExportBmsRedisCfg(QMap<QString, QVector<QSharedPointer<Tag>>>& tagMap, QString devName, QString& output);

    QString m_dirPath;
};

#endif // EMSCONFIGEXPORT_H
