#include "resize.h"

QSize CMyResize::CalcResizeSize(int imageWidth,int imageHeight,QWidget* pMainWindow,int iOffset)
{
	QSize size;
	if (imageWidth > imageHeight) { // 横長画像
		if (imageWidth > ((pMainWindow->width() - iOffset)/2)) {
			size.setWidth(((pMainWindow->width() - iOffset)/2));
			size.setHeight((imageHeight * ((pMainWindow->width() - iOffset)/2)) / imageWidth);
			if (size.height() > pMainWindow->height()) {
				size.setHeight(pMainWindow->height());
				size.setWidth((imageWidth * pMainWindow->height()) / imageHeight);
			}
		} else {
			if (imageHeight > pMainWindow->height()) {
				size.setHeight(pMainWindow->height());
				size.setWidth((imageWidth * pMainWindow->height()) / imageHeight);
				if (size.width() > ((pMainWindow->width() - iOffset)/2)) {
					size.setWidth(((pMainWindow->width() - iOffset)/2));
					size.setHeight((imageHeight * ((pMainWindow->width() - iOffset)/2)) / imageWidth);
				}
			} else {
				size.setWidth(imageWidth);
				size.setHeight(imageHeight);
			}
		}
	} else { // 縦長画像 or 正方形
		if (imageHeight > pMainWindow->height()) {
			size.setHeight(pMainWindow->height());
			size.setWidth((imageWidth * pMainWindow->height()) / imageHeight);
			if (size.width() > ((pMainWindow->width() - iOffset)/2)) {
				size.setWidth(((pMainWindow->width() - iOffset)/2));
				size.setHeight((imageHeight * ((pMainWindow->width() - iOffset)/2)) / imageWidth);
			}
		} else {
			if (imageWidth > ((pMainWindow->width() - iOffset)/2)) {
				size.setWidth(((pMainWindow->width() - iOffset)/2));
				size.setHeight((imageHeight * ((pMainWindow->width() - iOffset)/2)) / imageWidth);
				if (size.height() > pMainWindow->height()) {
					size.setHeight(pMainWindow->height());
					size.setWidth((imageWidth * pMainWindow->height()) / imageHeight);
				}
			} else {
				size.setWidth(imageWidth);
				size.setHeight(imageHeight);
			}
		}
	}
	
	return size;
}
