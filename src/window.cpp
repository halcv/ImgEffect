#include <QDesktopWidget>
#include <QApplication>
#include <QDebug>
#include <QStringList>
#include <QString>
#include <QMessageBox>
#include <QFileDialog>
#include "window.h"
#include "resize.h"
#include "dir.h"
#include "effect.h"

#define DEBUG (0)

CMainWindow::CMainWindow()
{
#if DEBUG
	qDebug() << __func__;
#endif
	m_iOffset = 200;
	m_iImageIndex = 0;
	m_iEffectIndex = 0;
	
	Create();
}

CMainWindow::~CMainWindow()
{
#if DEBUG
	qDebug() << __func__;
#endif
}

void CMainWindow::Create()
{
#if DEBUG
	qDebug() << __func__;
#endif

	SetMainWindowSizeAndPosition();
	setStyleSheet("background-color: #000000;");
	ChildWidgetCreate();
	CreateConnect();
	if (CreateImageList() > 0) {
		m_List.setCurrentRow(m_iImageIndex);
	}
	show();
}

void CMainWindow::ChildWidgetCreate()
{
	m_lblSrcImage.setParent(this);
	m_lblSrcImage.resize(width() / 2,height());
	m_lblSrcImage.move(0,0);

	m_lblDstImage.setParent(this);
	m_lblDstImage.resize(width() / 2,height());
	m_lblDstImage.move(width() / 2,0);

	m_List.setParent(this);
	m_List.setGeometry(5,5,m_iOffset - 10,height() - 80);
	m_List.setStyleSheet("background-color: #303030;color: #E0E0E0;");

	m_cmbEffect.setParent(this);
	m_cmbEffect.setGeometry(5,height() - 70,m_iOffset - 10,30);
	m_cmbEffect.setStyleSheet("background-color: #303030;color: #E0E0E0;");
	m_cmbEdit.setStyleSheet("background-color: #303030;color: #E0E0E0;");
	m_cmbEdit.setReadOnly(true);
	m_cmbEffect.setLineEdit(&m_cmbEdit);

	m_btnSave.setParent(this);
	m_btnSave.setText(tr("Save"));
	m_btnSave.setStyleSheet("background-color: #303030;color: #E0E0E0;");
	m_btnSave.setGeometry(60,height() - 35,m_iOffset - 120,30);
	
   	QStringList strList;
	strList << "None"
			<< "Gray"
			<< "Sepia"
			<< "Reverse"
			<< "Pencil1"
			<< "Pencil2"
			<< "Pencil3"
			<< "ColorPencil1"
			<< "ColorPencil2"
			<< "ColorPencil3"
			<< "Nitika1"
			<< "Nitika2"
			<< "Hekiga"
			<< "GrayPencil1"
			<< "GrayPencil2"
			<< "GrayPencil3"
			<< "Enbos"
			<< "ColorPaint1"
			<< "ColorPaint2"
			<< "ColorPaint3"
			<< "GrayPaint"
			<< "GoldPaint"
			<< "WallPaint"
			<< "Wave"
			<< "Lens";
	
	m_cmbEffect.addItems(strList);
}

void CMainWindow::CreateConnect()
{
#if DEBUG
	qDebug() << __func__;
#endif

	QObject::connect(&m_List,SIGNAL(currentRowChanged(int)),this,SLOT(SetImage(int)));
	QObject::connect(&m_cmbEffect,SIGNAL(activated(int)),this,SLOT(EffectChanged(int)));
	QObject::connect(&m_btnSave,SIGNAL(clicked()),this,SLOT(SaveButtonClicked()));
}

int CMainWindow::CreateImageList()
{
#if DEBUG
	qDebug() << __func__;
#endif
	if (CMyDir::GetImageFileList() == 0) {
		return -1;
	}

	for (int i = 0;i < CMyDir::m_ImageFileList.size();i++) {
		m_List.addItem(CMyDir::m_ImageFileList.at(i).fileName());
	}
	return 1;
}

void CMainWindow::resizeEvent(QResizeEvent* pEvent)
{
	pEvent->size();

	if (m_SrcImage.isNull() == true || m_DstImage.isNull() == true) {
		m_lblSrcImage.resize((width() - m_iOffset) / 2,height());
		m_lblSrcImage.move(m_iOffset,0);

		m_lblDstImage.resize((width() - m_iOffset) / 2,height());
		m_lblDstImage.move((width() - m_iOffset) / 2 + m_iOffset,0);
	
		return;
	}

	DrawImage();
}

void CMainWindow::SetMainWindowSizeAndPosition()
{
#if DEBUG
	qDebug() << __func__;
#endif

	resize(800,500);
	setMinimumSize(QSize(800,500));
	QDesktopWidget *desktop = QApplication::desktop();
	move((desktop->width() - width()) / 2,(desktop->height() - height()) / 2);
}

void CMainWindow::SetImage(int iIndex)
{
#if DEBUG
	qDebug() << __func__;
#endif

	QImage tempImage;
	m_iImageIndex = iIndex;
	
	m_SrcImage.load(CMyDir::m_ImageFileList.at(m_iImageIndex).fileName());
	tempImage.load(CMyDir::m_ImageFileList.at(m_iImageIndex).fileName());
	m_DstImage = tempImage.convertToFormat(QImage::Format_RGB32);

	CEffect::SetEffect(&m_DstImage,m_iEffectIndex);
	
	DrawImage();
}

void CMainWindow::DrawImage()
{
#if DEBUG
	qDebug() << __func__;
#endif
	if (m_SrcImage.isNull() == false && m_DstImage.isNull() == false) {
		m_SrcPixmap = QPixmap::fromImage(m_SrcImage);
		m_DstPixmap = QPixmap::fromImage(m_DstImage);
		int imageWidth = m_SrcImage.width();
		int imageHeight = m_SrcImage.height();
		QSize size = CMyResize::CalcResizeSize(imageWidth,imageHeight,this,m_iOffset);

		m_SrcPixmap = m_SrcPixmap.scaled(size, Qt::KeepAspectRatio);  // 拡大縮小倍率維持
		m_lblSrcImage.resize(size.width(),size.height());
		m_lblSrcImage.move((((width() - m_iOffset) / 2) - m_lblSrcImage.width()) / 2 + m_iOffset,
						(height() - m_lblSrcImage.height()) / 2 );
		m_lblSrcImage.setPixmap(m_SrcPixmap);

		m_DstPixmap = m_DstPixmap.scaled(size, Qt::KeepAspectRatio);  // 拡大縮小倍率維持
		m_lblDstImage.resize(size.width(),size.height());
		m_lblDstImage.move((((width() - m_iOffset) / 2) - m_lblDstImage.width()) / 2 + (width() - m_iOffset) / 2 + m_iOffset,
						(height() - m_lblDstImage.height()) / 2 );
		m_lblDstImage.setPixmap(m_DstPixmap);

	} else {
#if DEBUG
		qDebug() << "Not image Data";
#endif
	}
}

void CMainWindow::EffectChanged(int iEffect)
{
#if DEBUG
	qDebug() << __func__;
#endif
	m_iEffectIndex = iEffect;

	SetImage(m_iImageIndex);
}

void CMainWindow::SaveButtonClicked()
{
#if DEBUG
	qDebug() << __func__;
#endif
	if (m_DstImage.isNull() == true) {
		return;
	}

	SaveImage();
}

void CMainWindow::SaveImage()
{
	QString strFileName = QFileDialog::getSaveFileName(this,tr("ファイルの保存"),"hoge.jpg",
													   tr("画像ファイル (*.jpg *.JPG)"));
	if (strFileName != "") {
		if (m_DstImage.save(strFileName,"JPG") == false) {
			QMessageBox::critical(this,tr("エラー"),tr("ファイルの保存に失敗しました。"));
		}
	}
}

