#ifndef _DIR_H_
#define _DIR_H_

#include <QFileInfoList>

class CMyDir {
  public:
	static int GetImageFileList();
	static QFileInfoList m_ImageFileList;
};

#endif // _DIR_H_
