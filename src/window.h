#ifndef _WINDOW_H_
#define _WINDOW_H_

#include <QObject>
#include <QMainWindow>
#include <QImage>
#include <QPixmap>
#include <QResizeEvent>
#include <QLabel>
#include <QListWidget>
#include <QComboBox>
#include <QLineEdit>
#include <QPushButton>

class CMainWindow : public QMainWindow {
	Q_OBJECT;

  public:
	CMainWindow();
	~CMainWindow();

  private slots:
	void SetImage(int);
	void EffectChanged(int);
	void SaveButtonClicked();
	
  private:
	void Create();
	void SetMainWindowSizeAndPosition();
	void DrawImage();
	void ChildWidgetCreate();
	void CreateConnect();
	void SaveImage();
	int CreateImageList();
	QImage m_SrcImage;
	QPixmap m_SrcPixmap;
	QImage m_DstImage;
	QPixmap m_DstPixmap;
	QListWidget m_List;
	QLabel m_lblSrcImage;
	QLabel m_lblDstImage;
	QComboBox m_cmbEffect;
	QLineEdit m_cmbEdit;
	QPushButton m_btnSave;
	int m_iOffset;
	int m_iImageIndex;
	int m_iEffectIndex;
	
  protected:
	virtual void resizeEvent(QResizeEvent* pEvent);
};

#endif // _WINDOW_H_
