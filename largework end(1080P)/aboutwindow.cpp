#include<header.h>
AboutWindow::AboutWindow(QWidget *parent):
    QWidget(parent)
{
    resize(400, 300);
    setWindowTitle(tr("帮助"));
}

void AboutWindow::paintEvent(QPaintEvent *)
{
    QPainter pen(this);
    QLabel pic(this);
    pen.setPen(QColor(0,160,230));
    pen.translate(80,100);
    pen.drawText(rect(),QStringLiteral("制作人：毛维嘉，董冠辰,张津彬"));
}
