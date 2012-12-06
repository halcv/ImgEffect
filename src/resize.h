#ifndef _RESIZE_H_
#define _RESIZE_H_

#include <QSize>
#include <QWidget>

class CMyResize {
  public:
	static QSize CalcResizeSize(int imageWidth,int imageHeight,QWidget* pMainWindow,int iOffset);
};

#endif // _RESIZE_H_
