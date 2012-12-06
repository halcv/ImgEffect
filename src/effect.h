#ifndef _EFFECT_H_
#define _EFFECT_H_

#include <QImage>

class CEffect {
  public:
	static void SetEffect(QImage* pImage,int iEffectIndex);

  private:
	static void None();
	static void Gray(QImage* pImage);
	static void Sepia(QImage* pImage);
	static void Reverse(QImage* pImage);
	static void Pencil1(QImage* pImage);
	static void Pencil2(QImage* pImage);
	static void Pencil3(QImage* pImage);
	static void ColorPencil1(QImage* pImage);
	static void ColorPencil2(QImage* pImage);
	static void ColorPencil3(QImage* pImage);
	static void Nitika1(QImage* pImage);
	static void Nitika2(QImage* pImage);
	static void Hekiga(QImage* pImage);
	static void GrayPencil1(QImage* pImage);
	static void GrayPencil2(QImage* pImage);
	static void GrayPencil3(QImage* pImage);
	static void Enbos(QImage* pImage);
	static void ColorPaint(QImage* pImage);
	static void GrayPaint(QImage* pImage);
	static void GoldPaint(QImage* pImage);
	static void Wave(QImage* pImage);
	static void Lens(QImage* pImage);
	static void Noize(QImage* pImage);
	static void Contrast(QImage* pImage,int LowParam,int HighParam);
	static void LightColor(QImage* pImage);
	static void VividColor(QImage* pImage);
	static void Sharpness(QImage* pImage);
	static int ProcessFilter(QImage* pImg,int t_x,int t_y,char* mask);
	static void SoftFocus(QImage* pImage);
	static void ProcessSoftFocusFilter(QImage* pImg,int t_x,int t_y,int* pRed,int* pGreen,int* pBlue);
	static void ProcessColorFilter(QImage* pImg,int t_x,int t_y,char* mask,int* pRed,int* pGreen,int* pBlue);
	static int CalcTotalAverage(QImage* pImg);
	static int CalcLineAverage(QImage* pImg,int line);
	static int ProcessEnbosFilter(QImage* pImg,int t_x,int t_y,char* mask);
		
	static int m_iEffectIndex;
};

#endif // _EFFECT_H_
