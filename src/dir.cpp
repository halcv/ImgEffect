#include <QDir>
#include <QStringList>
#include <QObject>
#include "dir.h"

QFileInfoList CMyDir::m_ImageFileList;

int CMyDir::GetImageFileList()
{
    QDir dir(QObject::tr("."));
    QStringList strlFilter;
    strlFilter << "*.jpg" << "*.JPG";
	m_ImageFileList = dir.entryInfoList( strlFilter, QDir::Files );

	return m_ImageFileList.size();
}
