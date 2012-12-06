#include <QApplication>
#include <QTextCodec>
#include "window.h"

int main(int argc,char* argv[])
{
	QApplication app(argc,argv);
	QTextCodec::setCodecForCStrings(QTextCodec::codecForLocale());
	QTextCodec::setCodecForTr(QTextCodec::codecForLocale());
	CMainWindow wnd;
	return app.exec();
}
