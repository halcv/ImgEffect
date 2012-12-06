#include <QDebug>
#include <QRgb>
#include <math.h>
#include "effect.h"

#define DEBUG (0)
#define PI (3.141592653)
#define TWO_PI (PI * 2.0)


int CEffect::m_iEffectIndex = 0;

void CEffect::SetEffect(QImage* pImage,int iEffectIndex)
{
#if DEBUG
	qDebug() << __func__;
#endif

	switch(iEffectIndex) {
	case 0:
		None();
		break;
	case 1:
		Gray(pImage);
		break;
	case 2:
		Sepia(pImage);
		break;
	case 3:
		Reverse(pImage);
		break;
	case 4:
		Pencil1(pImage);
		break;
	case 5:
		Pencil2(pImage);
		break;
	case 6:
		Pencil3(pImage);
		break;
	case 7:
		ColorPencil1(pImage);
		break;
	case 8:
		VividColor(pImage);
		ColorPencil2(pImage);
		break;
	case 9:
		ColorPencil3(pImage);
		break;
	case 10:
		Nitika1(pImage);
		break;
	case 11:
		Nitika2(pImage);
		break;
	case 12:
		Hekiga(pImage);
		break;
	case 13:
		Gray(pImage);
		GrayPencil1(pImage);
		break;
	case 14:
		Gray(pImage);
		GrayPencil2(pImage);
		break;
	case 15:
		Gray(pImage);
		GrayPencil3(pImage);
		break;
	case 16:
		Enbos(pImage);
		break;
	case 17:
	    ColorPaint(pImage);
		break;
	case 18:
		VividColor(pImage);
		ColorPencil2(pImage);
	    ColorPaint(pImage);
		break;
	case 19:
		Sharpness(pImage);
		ColorPaint(pImage);
		Contrast(pImage,20,20);
		break;
	case 20:
		GrayPaint(pImage);
		break;
	case 21:
		GoldPaint(pImage);
		break;
	case 22:
		Noize(pImage);
		ColorPaint(pImage);
		break;
	case 23:
		Wave(pImage);
		break;
	case 24:
		Lens(pImage);
		break;
	}
}

void CEffect::None()
{
#if DEBUG
	qDebug() << __func__;
#endif

}

void CEffect::Gray(QImage* pImage)
{
#if DEBUG
	qDebug() << __func__;
#endif

	for (int y = 0;y < pImage->height();y++) {
		for (int x = 0;x < pImage->width();x++) {
			QRgb rgb = pImage->pixel(x,y);
			int gray = qGreen(rgb);
			pImage->setPixel(x,y,qRgb(gray,gray,gray));
		}
	}
}

void CEffect::Sepia(QImage* pImage)
{
#if DEBUG
	qDebug() << __func__;
#endif

	int r,g,b;
	
	for (int y = 0;y < pImage->height();y++) {
		for (int x = 0;x < pImage->width();x++) {
			QRgb rgb = pImage->pixel(x,y);
			int gray = qGreen(rgb);
			r = gray * 240 / 255;
			g = gray * 200 / 255;
			b = gray * 145 / 255;
			pImage->setPixel(x,y,qRgb(r,g,b));
		}
	}
}

void CEffect::Reverse(QImage* pImage)
{
#if DEBUG
	qDebug() << __func__;
#endif

	for (int y = 0;y < pImage->height();y++) {
		for (int x = 0;x < pImage->width();x++) {
			QRgb rgb = pImage->pixel(x,y);
			int r = 255 - qRed(rgb);
			int g = 255 - qGreen(rgb);
			int b = 255 - qBlue(rgb);
			pImage->setPixel(x,y,qRgb(r,g,b));
		}
	}
}

void CEffect::Pencil1(QImage* pImage)
{
#if DEBUG
	qDebug() << __func__;
#endif

	QImage tempImage = *pImage;
	int x,y;
	int green,green1,green2;
    /* Sobel Operator (X) */
	char mask_x[] = {
		-2 , 0, 2,
		-4 , 0, 4,
		-2 , 0, 2
	};
    /* Sobel Operator (Y) */
	char mask_y[] = {
		-2 , -4, -2,
		 0 ,  0,  0,
		 2 ,  4,  2
	};
	
	for (y = 0;y < tempImage.height();y++) {
		for (x = 0;x < tempImage.width();x++) {
			green1 = ProcessFilter(&tempImage,x,y,mask_x);
			green2 = ProcessFilter(&tempImage,x,y,mask_y);
			green = sqrt((green1 * green1) + (green2 * green2));
			if (green > 255) {
				green = 255;
			}
			green = 255 - green;
			pImage->setPixel(x,y,qRgb(green,green,green));
		}
	}
}

void CEffect::Pencil2(QImage* pImage)
{
#if DEBUG
	qDebug() << __func__;
#endif
	
	QImage tempImage = *pImage;
	int x,y;
	int green,green1,green2;
    /* Sobel Operator (X) */
	char mask_x[] = {
		-1 , 0, 1,
		-2 , 0, 2,
		-1 , 0, 1
	};
    /* Sobel Operator (Y) */
	char mask_y[] = {
		-2 , -4, -2,
		 0 ,  0,  0,
		 2 ,  4,  2
	};
	
	for (y = 0;y < tempImage.height();y++) {
		for (x = 0;x < tempImage.width();x++) {
			green1 = ProcessFilter(&tempImage,x,y,mask_x);
			green2 = ProcessFilter(&tempImage,x,y,mask_y);
			green = sqrt((green1 * green1) + (green2 * green2));
			if (green > 255) {
				green = 255;
			}
			green = 255 - green;
			pImage->setPixel(x,y,qRgb(green,green,green));
		}
	}
}

void CEffect::Pencil3(QImage* pImage)
{
#if DEBUG
	qDebug() << __func__;
#endif

	QImage softImage = *pImage;
	
	int x,y,i;
	int green,green1,green2;
    /* Sobel Operator (X) */
	char mask_x[] = {
		-1 , 0, 1,
		-2 , 0, 2,
		-1 , 0, 1
	};
    /* Sobel Operator (Y) */
	char mask_y[] = {
		-1 , -2, -1,
		0 ,  0,  0,
		1 ,  2,  1
	};
	
	for (i = 0;i < 3;i++) {
		SoftFocus(&softImage);
	}

	for (y = 0;y < softImage.height();y++) {
		for (x = 0;x < softImage.width();x++) {
			green1 = ProcessFilter(&softImage,x,y,mask_x);
			green2 = ProcessFilter(&softImage,x,y,mask_y);
			green = sqrt((green1 * green1) + (green2 * green2));
			if (green > 255) {
				green = 255;
			}
			green = 255 - green;
			pImage->setPixel(x,y,qRgb(green,green,green));
		}
	}
}

void CEffect::ColorPencil1(QImage* pImage)
{
#if DEBUG
	qDebug() << __func__;
#endif

	QImage tempImage = *pImage;
	int x,y;
	char r,g,b;

	int green,green1,green2;
    /* Sobel Operator (X) */
	char mask_x[] = {
		-1 , 0, 1,
		-2 , 0, 2,
		-1 , 0, 1
	};
    /* Sobel Operator (Y) */
	char mask_y[] = {
		-1 , -2, -1,
		 0 ,  0,  0,
		 1 ,  2,  1
	};

	for (y = 0;y < tempImage.height();y++) {
		for (x = 0;x < tempImage.width();x++) {
			green1 = ProcessFilter(&tempImage,x,y,mask_x);
			green2 = ProcessFilter(&tempImage,x,y,mask_y);
			green = sqrt((green1 * green1) + (green2 * green2));
			if (green > 255) {
				green = 255;
			}
			green = 255 - green;
			QRgb rgb = pImage->pixel(x,y);
			if (qRed(rgb) <= 50 && qGreen(rgb) <= 50 && qBlue(rgb) <= 50) {
				r = qRed(rgb);
				g = qGreen(rgb);
				b = qBlue(rgb);
			} else {
				r = (qRed(rgb) + green) / 2;
				g = (qGreen(rgb) + green) / 2;
				b = (qBlue(rgb) + green) / 2;
			}
			pImage->setPixel(x,y,qRgb(r,g,b));
		}
	}
}

void CEffect::ColorPencil2(QImage* pImage)
{
#if DEBUG
	qDebug() << __func__;
#endif

	QImage tempImage = *pImage;
	int x,y;
	int r,g,b;

	int green,green1,green2;
    /* Sobel Operator (X) */
	char mask_x[] = {
		-1 , 0, 1,
		-2 , 0, 2,
		-1 , 0, 1
	};
    /* Sobel Operator (Y) */
	char mask_y[] = {
		-1 , -2, -1,
		 0 ,  0,  0,
		 1 ,  2,  1
	};
	for (y = 0;y < tempImage.height();y++) {
		for (x = 0;x < tempImage.width();x++) {
			green1 = ProcessFilter(&tempImage,x,y,mask_x);
			green2 = ProcessFilter(&tempImage,x,y,mask_y);
			green = sqrt((green1 * green1) + (green2 * green2));
			if (green > 255) {
				green = 255;
			}
			if (green < 127) {
				green = 0;
			}
			green = 255 - green;

			QRgb rgb = pImage->pixel(x,y);
			r = (qRed(rgb) * green) / 255;
			g = (qGreen(rgb) * green) / 255;
			b = (qBlue(rgb) * green) / 255;

			pImage->setPixel(x,y,qRgb(r,g,b));
		}
	}
}

void CEffect::ColorPencil3(QImage* pImage)
{
#if DEBUG
	qDebug() << __func__;
#endif

	QImage softImage = *pImage;
	int x,y,i;
	char r,g,b;

	int green,green1,green2;
    /* Sobel Operator (X) */
	char mask_x[] = {
		-2 , 0, 2,
		-4 , 0, 4,
		-2 , 0, 2
	};
    /* Sobel Operator (Y) */
	char mask_y[] = {
		-2 , -4, -2,
		 0 ,  0,  0,
		 2 ,  4,  2
	};

	for (i = 0;i < 3;i++) {
		SoftFocus(&softImage);
	}

	for (y = 0;y < softImage.height();y++) {
		for (x = 0;x < softImage.width();x++) {
			green1 = ProcessFilter(&softImage,x,y,mask_x);
			green2 = ProcessFilter(&softImage,x,y,mask_y);
			green = sqrt((green1 * green1) + (green2 * green2));
			if (green > 255) {
				green = 255;
			}
			green = 255 - green;
			QRgb rgb = softImage.pixel(x,y);
			r = (qRed(rgb) + green) / 2;
			g = (qGreen(rgb) + green) / 2;
			b = (qBlue(rgb) + green) / 2;

			pImage->setPixel(x,y,qRgb(r,g,b));
		}
	}
}

void CEffect::Nitika1(QImage* pImage)
{
#if DEBUG
	qDebug() << __func__;
#endif

	QImage tempImage = *pImage;
	int x,y;
	int totalavg;
	int threshold;
	int nitika;
	
	totalavg = CalcTotalAverage(&tempImage);

	for (y = 0;y < tempImage.height();y++) {
		for (x = 0;x < tempImage.width();x++) {
			QRgb rgb = tempImage.pixel(x,y);
			threshold = totalavg;
			if (qGreen(rgb) > threshold) {
				nitika = 255;
			} else {
				nitika = 0;
			}
			pImage->setPixel(x,y,qRgb(nitika,nitika,nitika));
		}
	}
}

void CEffect::Nitika2(QImage* pImage)
{
#if DEBUG
	qDebug() << __func__;
#endif

	QImage tempImage = *pImage;
	int x,y;
	int totalavg;
	int threshold;
	int lineavg;
	char nitika;
	
	totalavg = CalcTotalAverage(&tempImage);

	for (y = 0;y < tempImage.height();y++) {
		lineavg = CalcLineAverage(&tempImage,y);
		for (x = 0;x < tempImage.width();x++) {
			threshold = totalavg;
			if (totalavg > lineavg) {
				threshold = lineavg;
			}
			QRgb rgb = tempImage.pixel(x,y);
			if (qGreen(rgb) > threshold) {
				nitika = 255;
			} else {
				nitika = 0;
			}
			pImage->setPixel(x,y,qRgb(nitika,nitika,nitika));
		}
	}
}

void CEffect::Hekiga(QImage* pImage)
{
	QImage tempImage = *pImage;
	int x,y;
	int red,green,blue;

	for (y = 0;y < tempImage.height();y++) {
		for (x = 0;x < tempImage.width();x++) {
			ProcessSoftFocusFilter(&tempImage,x,y,&red,&green,&blue);
			QRgb rgb = pImage->pixel(x,y);
			if (qGreen(rgb) > green) {
				green = 255;
			} else {
				green = 0;
			}
			red = (qRed(rgb) + green) >> 1;
			blue = (qBlue(rgb) + green) >> 1;
			green = (qGreen(rgb) + green) >> 1;
			pImage->setPixel(x,y,qRgb(red,green,blue));
		}
	}

	Contrast(pImage,60,0);
}

void CEffect::GrayPencil1(QImage* pImage)
{
#if DEBUG
	qDebug() << __func__;
#endif

	QImage tempImage = *pImage;
	int x,y;
	char r,g,b;

	int green,green1,green2;
    /* Sobel Operator (X) */
	char mask_x[] = {
		-2 , 0, 2,
		-4 , 0, 4,
		-2 , 0, 2
	};
    /* Sobel Operator (Y) */
	char mask_y[] = {
		-2 , -4, -2,
		 0 ,  0,  0,
		 2 ,  4,  2
	};

	for (y = 0;y < tempImage.height();y++) {
		for (x = 0;x < tempImage.width();x++) {
			green1 = ProcessFilter(&tempImage,x,y,mask_x);
			green2 = ProcessFilter(&tempImage,x,y,mask_y);
			green = sqrt((green1 * green1) + (green2 * green2));
			if (green > 255) {
				green = 255;
			}
			green = 255 - green;
			QRgb rgb = pImage->pixel(x,y);
			r = (qRed(rgb) + green) / 2;
			g = (qGreen(rgb) + green) / 2;
			b = (qBlue(rgb) + green) / 2;

			pImage->setPixel(x,y,qRgb(r,g,b));
		}
	}
}

void CEffect::GrayPencil2(QImage* pImage)
{
#if DEBUG
	qDebug() << __func__;
#endif

	QImage tempImage = *pImage;
	int x,y;
	int r,g,b,max;

	int green,green1,green2;
    /* Sobel Operator (X) */
	char mask_x[] = {
		-1 , 0, 1,
		-2 , 0, 2,
		-1 , 0, 1
	};
    /* Sobel Operator (Y) */
	char mask_y[] = {
		-1 , -2, -1,
		 0 ,  0,  0,
		 1 ,  2,  1
	};

	for (y = 0;y < tempImage.height();y++) {
		for (x = 0;x < tempImage.width();x++) {
			green1 = ProcessFilter(&tempImage,x,y,mask_x);
			green2 = ProcessFilter(&tempImage,x,y,mask_y);
			green = sqrt((green1 * green1) + (green2 * green2));
			if (green > 255) {
				green = 255;
			}
			green = 255 - green;
			QRgb rgb = pImage->pixel(x,y);
			r = (qRed(rgb) * green) / 255;
			g = (qGreen(rgb) * green) / 255;
			b = (qBlue(rgb) * green) / 255;
			if (r >= g) {
				max = r;
			} else {
				max = g;
			}
			if (b >= max) {
				max = b;
			}

			max /= 2;
			r += max;
			if (r > 255) {
				r = 255;
			}
			
			g += max;
			if (g > 255) {
				g = 255;
			}

			b += max;
			if (b > 255) {
				b = 255;
			}

			pImage->setPixel(x,y,qRgb(r,g,b));
		}
	}
}

void CEffect::GrayPencil3(QImage* pImage)
{
#if DEBUG
	qDebug() << __func__;
#endif

	QImage softImage = *pImage;
	int x,y,i;
	char r,g,b;

	int green,green1,green2;
    /* Sobel Operator (X) */
	char mask_x[] = {
		-2 , 0, 2,
		-4 , 0, 4,
		-2 , 0, 2
	};
    /* Sobel Operator (Y) */
	char mask_y[] = {
		-2 , -4, -2,
		 0 ,  0,  0,
		 2 ,  4,  2
	};

	for (i = 0;i < 3;i++) {
		SoftFocus(&softImage);
	}

	for (y = 0;y < softImage.height();y++) {
		for (x = 0;x < softImage.width();x++) {
			green1 = ProcessFilter(&softImage,x,y,mask_x);
			green2 = ProcessFilter(&softImage,x,y,mask_y);
			green = sqrt((green1 * green1) + (green2 * green2));
			if (green > 255) {
				green = 255;
			}
			green = 255 - green;
			QRgb rgb = softImage.pixel(x,y);
			r = (qRed(rgb) + green) / 2;
			g = (qGreen(rgb) + green) / 2;
			b = (qBlue(rgb) + green) / 2;
			pImage->setPixel(x,y,qRgb(r,g,b));
		}
	}
}

void CEffect::Enbos(QImage* pImage)
{
#if DEBUG
	qDebug() << __func__;
#endif

	QImage tempImage = *pImage;
	int x,y;
	int green;
	char mask[] = {
		-3 , 0, 0,
		 0 , 0, 0,
		 0 , 0, 3
	};

	for (y = 0;y < tempImage.height();y++) {
		for (x = 0;x < tempImage.width();x++) {
			green = ProcessEnbosFilter(&tempImage,x,y,mask);
			pImage->setPixel(x,y,qRgb(green,green,green));
		}
	}
}

void CEffect::ColorPaint(QImage* pImage)
{
#if DEBUG
	qDebug() << __func__;
#endif

	QImage tempImage = *pImage;
	int x,y;
	int green;
	int r,g,b;

	char mask[] = {
		 -6 ,  0, 0,
		  0 ,  0, 0,
		  0 ,  0, 6
	};

	SoftFocus(&tempImage);
	
	for (y = 0;y < tempImage.height();y++) {
		for (x = 0;x < tempImage.width();x++) {
			green = ProcessEnbosFilter(&tempImage,x,y,mask);
			QRgb rgb = tempImage.pixel(x,y);
			r = ((qRed(rgb) + green) / 2);
			g = ((qGreen(rgb) + green) / 2);
			b = ((qBlue(rgb) + green) / 2);
			if (r < 0) {
				r = 0;
			}
			if (g < 0) {
				g = 0;
			}
			if (b < 0) {
				b = 0;
			}
			pImage->setPixel(x,y,qRgb(r,g,b));
		}
	}
	Contrast(pImage,60,60);
}

void CEffect::GrayPaint(QImage* pImage)
{
#if DEBUG
	qDebug() << __func__;
#endif

	int x,y;
	int green;
	int r,g,b;

	Gray(pImage);

	QImage tempImage = *pImage;

	char mask[] = {
		 -6 ,  0, 0,
		  0 ,  0, 0,
		  0 ,  0, 6
	};


	SoftFocus(&tempImage);
	
	for (y = 0;y < tempImage.height();y++) {
		for (x = 0;x < tempImage.width();x++) {
			green = ProcessEnbosFilter(&tempImage,x,y,mask);
			QRgb rgb = tempImage.pixel(x,y);
			r = ((qRed(rgb) + green) / 2);
			g = ((qGreen(rgb) + green) / 2);
			b = ((qBlue(rgb) + green) / 2);
			if (r < 0) {
				r = 0;
			}
			if (g < 0) {
				g = 0;
			}
			if (b < 0) {
				b = 0;
			}
			pImage->setPixel(x,y,qRgb(r,g,b));
		}
	}
	Contrast(pImage,60,60);
}

void CEffect::GoldPaint(QImage* pImage)
{
#if DEBUG
	qDebug() << __func__;
#endif

	int x,y;
	int green;
	int r,g,b;

	Gray(pImage);
	
	QImage tempImage = *pImage;
	char mask[] = {
		 -3 ,  0, 0,
		  0 ,  0, 0,
		  0 ,  0, 3
	};

	for (y = 0;y < tempImage.height();y++) {
		for (x = 0;x < tempImage.width();x++) {
			green = ProcessEnbosFilter(&tempImage,x,y,mask);
			r = green * 255 / 255;
			g = green * 215 / 255;
			b = 0;

			pImage->setPixel(x,y,qRgb(r,g,b));
		}
	}
}

void CEffect::Wave(QImage* pImage)
{
#if DEBUG
	qDebug() << __func__;
#endif

	QImage tempImage = *pImage;
	//double w =  TWO_PI / (tempImage.width() / 2.0);
	double w = TWO_PI / 50.0;
	QRgb rgb;
	
	for (int y = 0;y < tempImage.height();y++) {
		for (int x = 0;x < tempImage.width();x++) {
			double y0 = y + 5 * sin(w * x + 3);
			double x0 = x + 5 * cos(w * y + 3);
			if ((y0 < 0) || (y0 >= tempImage.height()) ||
				(x0 < 0) || (x0 >= tempImage.width())) {
				rgb = qRgb(0,0,0);
			} else {
				rgb = tempImage.pixel((int)x0,(int)y0);
			}

			pImage->setPixel(x,y,rgb);
		}
	}
}

void CEffect::Lens(QImage* pImage)
{
#if DEBUG
	qDebug() << __func__;
#endif
	QImage tempImage = *pImage;
	int lensD; // レンズの直径
	int r;     // レンズの半径
	int sx,sy; // レンズの領域（正方形）の開始位置
	QRgb rgb;
	
	if (tempImage.height() > tempImage.width()) {
		lensD = tempImage.width();
		sx = 0;
		sy = (tempImage.height() - lensD) / 2;
	} else {
		lensD = tempImage.height();
		sx = (tempImage.width() - lensD) / 2;
		sy = 0;
	}
	r = lensD / 2;

	for (int y = sy;y < sy + lensD;y++) {
		for (int x = sx;x < sx + lensD;x++) {
			int tx = x - sx - r;
			int ty = y - sy - r;
			float l = sqrt(tx*tx + ty*ty);
			int x0,y0;
			if (l > (float)r) {
				x0 = x;
				y0 = y;
			} else {
				float z = sqrt(r*r - tx*tx - ty*ty);
				
				// 変換前の座標
				x0 = (((2*r-z)*tx) / (2*r)) + sx + r;
				y0 = (((2*r-z)*ty) / (2*r)) + sy + r;
			}
			rgb = tempImage.pixel(x0,y0);
			pImage->setPixel(x,y,rgb);
		}
	}
}

void CEffect::Noize(QImage* pImage)
{
#if DEBUG
	qDebug() << __func__;
#endif

	int r,g,b;
	int random;
	QRgb rgb;
	srand(100);
	
	for (int y = 0;y < pImage->height();y++) {
		for (int x = 0;x < pImage->width();x++) {
			rgb = pImage->pixel(x,y);
			r = qRed(rgb);
			g = qGreen(rgb);
			b = qBlue(rgb);
			random = rand() % 10;

			switch (random) {
			case 0:
				r += 64;
				if (r > 255) {
					r = 255;
				}

				g += 32;
				if (g > 255) {
					g = 255;
				}

				b += 32;
				if (b > 255) {
					b = 255;
				}
				break;
			case 1:
				r -= 64;
				if (r < 0) {
					r = 0;
				}

				g -= 32;
				if (g < 0) {
					g = 0;
				}

				b -= 32;
				if (b < 0) {
					b = 0;
				}
				break;
			}

			pImage->setPixel(x,y,qRgb(r,g,b));
		}
	}
}

void CEffect::LightColor(QImage* pImage)
{
	int r,g,b,avg;
	QRgb rgb;
	
	for (int y = 0;y < pImage->height();y++) {
		for (int x = 0;x < pImage->width();x++) {
			rgb = pImage->pixel(x,y);
			avg = (qRed(rgb) + qGreen(rgb) + qBlue(rgb)) / 3;
			r = (qRed(rgb) + avg) / 2;
			g = (qGreen(rgb) + avg) / 2;
			b = (qBlue(rgb) + avg) / 2;
			pImage->setPixel(x,y,qRgb(r,g,b));
		}
	}
}

void CEffect::VividColor(QImage* pImage)
{
	int r,g,b,maxcolor,minicolor,temp;
	QRgb rgb;
	
	for (int y = 0;y < pImage->height();y++) {
		for (int x = 0;x < pImage->width();x++) {
			rgb = pImage->pixel(x,y);

			if (qRed(rgb) > qGreen(rgb)) {
				maxcolor = qRed(rgb);
			} else {
				maxcolor = qGreen(rgb);
			}
			if (qBlue(rgb) > maxcolor) {
				maxcolor = qBlue(rgb);
			}

			if (qRed(rgb) < qGreen(rgb)) {
				minicolor = qRed(rgb);
			} else {
				minicolor = qGreen(rgb);
			}
			if (minicolor > qBlue(rgb)) {
				minicolor = qBlue(rgb);
			}

			temp = (maxcolor - minicolor) / 2;
			r = qRed(rgb) + temp;
			if (r > 255) {
				r = 255;
			}

			g = qGreen(rgb) + temp;
			if (g > 255) {
				g = 255;
			}

			b = qBlue(rgb) + temp;
			if (b > 255) {
				b = 255;
			}
			
			pImage->setPixel(x,y,qRgb(r,g,b));
		}
	}
}

void CEffect::Contrast(QImage* pImage,int LowParam,int HighParam)
{
	int r,g,b;
	QRgb rgb;
	
	for (int y = 0;y < pImage->height();y++) {
		for (int x = 0;x < pImage->width();x++) {
			rgb = pImage->pixel(x,y);
			r = qRed(rgb);
			if (r < LowParam) {
				r = 0;
			} else if (r > (255 - HighParam)) {
				r = 255;
			} else {
				r = (int)(((double)r - (double)LowParam) * (256.0 / (256.0 - ((double)LowParam + (double)HighParam))));
			}
			if (r > 255) {
				r = 255;
			}
			if (r < 0) {
				r = 0;
			}

			g = qGreen(rgb);
			if (g < LowParam) {
				g = 0;
			} else if (g > (255 - HighParam)) {
				g = 255;
			} else {
				g = (int)(((double)g - (double)LowParam) * (256.0 / (256.0 - ((double)LowParam + (double)HighParam))));

			}
			if (g > 255) {
				g = 255;
			}
			if (g < 0) {
				g = 0;
			}

			b = qBlue(rgb);
			if (b < LowParam) {
				b = 0;
			} else if (b > (255 - HighParam)) {
				b = 255;
			} else {
				b = (int)(((double)b - (double)LowParam) * (256.0 / (256.0 - ((double)LowParam + (double)HighParam))));
			}
			if (b > 255) {
				b = 255;
			}
			if (b < 0) {
				b = 0;
			}

			pImage->setPixel(x,y,qRgb(r,g,b));
		}
	}
}

void CEffect::SoftFocus(QImage* pImage)
{
	int x,y;
	int red,green,blue;

	for (y = 0;y < pImage->height();y++) {
		for (x = 0;x < pImage->width();x++) {
			ProcessSoftFocusFilter(pImage,x,y,&red,&green,&blue);
			pImage->setPixel(x,y,qRgb(red,green,blue));
		}
	}
}

void CEffect::Sharpness(QImage* pImage)
{
	int x,y;
	int r,g,b;

	QImage tempImage = *pImage;

	char mask[] = {
		-1, -1, -1,
		-1,  9, -1,
		-1, -1, -1
	};

	SoftFocus(&tempImage);
	for (y = 0;y < tempImage.height();y++) {
		for (x = 0;x < tempImage.width();x++) {
			ProcessColorFilter(&tempImage,x,y,mask,&r,&g,&b);
			pImage->setPixel(x,y,qRgb(r,g,b));
		}
	}
}

int CEffect::ProcessFilter(QImage* pImg,int t_x,int t_y,char* mask)
{
	int s_x;
	int s_y;
	int x;
	int y;
	int green = 0;
	int m_index;
	int temp;

	for (y = -1;y <= 1;y++) {
		s_y = t_y + y;
		if (s_y < 0) {
			s_y = 0;
		} else if (s_y >= pImg->height()) {
			s_y = pImg->height() - 1;
		}
		
		for (x = -1;x <= 1;x++) {
			s_x = t_x + x;
			if (s_x < 0) {
				s_x = 0;
			} else if (s_x >= pImg->width()) {
				s_x = pImg->width() - 1;
			}

			m_index = (y + 1) * 3 + (x + 1); 
			QRgb rgb = pImg->pixel(s_x,s_y);
			temp = qGreen(rgb);
			green += (temp * (*(mask + m_index)));
		}
	}
	if (green > 255) {
		green = 255;
	}
	if (green < 0) {
		green *= -1;
	}
	
	return green;
}

void CEffect::ProcessSoftFocusFilter(QImage* pImg,int t_x,int t_y,int* pRed,int* pGreen,int* pBlue)
{
	int x,y;
	int s_x;
	int s_y;
	int r = 0;
	int g = 0;
	int b = 0;
	
	for (y = -1;y <= 1;y++) {
		s_y = t_y + y;
		if (s_y < 0) {
			s_y = 0;
		} else if (s_y >= pImg->height()) {
			s_y = pImg->height() - 1;
		}
		
		for (x = -1;x <= 1;x++) {
			s_x = t_x + x;
			if (s_x < 0) {
				s_x = 0;
			} else if (s_x >= pImg->width()) {
				s_x = pImg->width() - 1;
			}

			QRgb rgb = pImg->pixel(s_x,s_y);
			r += qRed(rgb);
			g += qGreen(rgb);
			b += qBlue(rgb);
		}
	}

	*pRed   = r / 9;
	*pGreen = g / 9;
	*pBlue  = b / 9;
}

void CEffect::ProcessColorFilter(QImage* pImg,int t_x,int t_y,char* mask,int* pRed,int* pGreen,int* pBlue)
{
	int s_x;
	int s_y;
	int x;
	int y;
	int m_index;
	int temp;

	*pRed = 0;
	*pGreen = 0;
	*pBlue = 0;
	
	for (y = -1;y <= 1;y++) {
		s_y = t_y + y;
		if (s_y < 0) {
			s_y = 0;
		} else if (s_y >= pImg->height()) {
			s_y = pImg->height() - 1;
		}
		
		for (x = -1;x <= 1;x++) {
			s_x = t_x + x;
			if (s_x < 0) {
				s_x = 0;
			} else if (s_x >= pImg->width()) {
				s_x = pImg->width() - 1;
			}

			m_index = (y + 1) * 3 + (x + 1); 
			QRgb rgb = pImg->pixel(s_x,s_y);
			temp = qRed(rgb);
			*pRed += (temp * (*(mask + m_index)));
			temp = qGreen(rgb);
			*pGreen += (temp * (*(mask + m_index)));
			temp = qBlue(rgb);
			*pBlue += (temp * (*(mask + m_index)));
		}
	}
	if (*pRed > 255) {
		*pRed = 255;
	}
	if (*pRed < 0) {
		*pRed = 0;
	}
	
	if (*pGreen > 255) {
		*pGreen = 255;
	}
	if (*pGreen < 0) {
		*pGreen = 0;
	}

	if (*pBlue > 255) {
		*pBlue = 255;
	}
	if (*pBlue < 0) {
		*pBlue = 0;
	}
}

int CEffect::CalcTotalAverage(QImage* pImg)
{
	int sum = 0;
	int x,y;
	int avg = 0;
	
	for (y = 0;y < pImg->height();y++) {
		for (x = 0;x < pImg->width();x++) {
			QRgb rgb = pImg->pixel(x,y);
			sum += qGreen(rgb);
		}
	}
	avg = sum / (pImg->width() * pImg->height());

	return avg;
}

int CEffect::CalcLineAverage(QImage* pImg,int line)
{
	int x;
	int avg = 0;
	int sum = 0;
	
	for (x = 0;x < pImg->width();x++) {
		QRgb rgb = pImg->pixel(x,line);
		sum += qGreen(rgb);
	}
	avg = sum / pImg->width();

	return avg;
}

int CEffect::ProcessEnbosFilter(QImage* pImg,int t_x,int t_y,char* mask)
{
	int s_x;
	int s_y;
	int x;
	int y;
	int value = 0;
	int m_index;
	int temp;

	for (y = -1;y <= 1;y++) {
		s_y = t_y + y;
		if (s_y < 0) {
			s_y = 0;
		} else if (s_y >= pImg->height()) {
			s_y = pImg->height() - 1;
		}
		
		for (x = -1;x <= 1;x++) {
			s_x = t_x + x;
			if (s_x < 0) {
				s_x = 0;
			} else if (s_x >= pImg->width()) {
				s_x = pImg->width() - 1;
			}

			m_index = (y + 1) * 3 + (x + 1); 
			QRgb rgb = pImg->pixel(s_x,s_y);
			temp = qGreen(rgb);
			value += (temp * (*(mask + m_index)));
		}
	}

	value += 127;
	if (value > 255) {
		value = 255;
	} else if (value < 0) {
		value = 0;
	}
	
	return value;
}
