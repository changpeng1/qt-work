#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QLabel>
#include <QDebug>
#include <QSystemTrayIcon>
#include <QDesktopWidget>
#include <QMenu>
MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setGeometry(1366+500,100,800,480);
    qDebug()<<ui->frame->pos()<<ui->frame->width()<<ui->frame->height();
    should_change_color= false;
    setAcceptDrops(true);
    setStyleSheet("background-color:black");
    ui->label->setStyleSheet("color:white");
    ui->label->setText("");
    qDebug()<<QApplication::desktop()->availableGeometry(1).height();

    QMenu *myMenu;
    QAction *quitAction;
    QSystemTrayIcon *myTrayIcon;
    //widget.cpp
    //通知栏相关
    quitAction = new QAction(tr("退出"),this);//右键点图标之后的选项

    myMenu = new QMenu((QWidget*)QApplication::desktop());
    myMenu->addAction(quitAction);
    //判断系统是否支持托盘图标
    if(!QSystemTrayIcon::isSystemTrayAvailable())
    {
        return;
    }
    myTrayIcon = new QSystemTrayIcon(this);
    myTrayIcon->setIcon(QIcon("/home/changpeng/Desktop/imagea/full/137b3d23e1bb91e144d34e53d99b552ea8b8bfb1.jpg"));
    myTrayIcon->setToolTip(tr("学生成绩管理系统"));
    myTrayIcon->showMessage("托盘","托盘管理",QSystemTrayIcon::Information,10000);
    myTrayIcon->setContextMenu(myMenu);
    myTrayIcon->show();
    send_thread.start();
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::closeEvent(QCloseEvent *event)
{
    this->hide();
    event->ignore();
}
void MainWindow::mousePressEvent(QMouseEvent *event)
{
    qDebug()<<"mouse pressed";
}
void MainWindow::mouseReleaseEvent(QMouseEvent *event)
{
    qDebug()<<"mouse released";
    should_change_color = true;
    ui->frame->setStyleSheet("background-color:red");
}
void MainWindow::mouseMoveEvent(QMouseEvent *event)
{

   // qDebug()<<"mouse moved to: "<<event->pos();
    int x = event->pos().x();
    int y = event->pos().y();
    if(((x>ui->frame->pos().x()&&(x<ui->frame->pos().x()+ui->frame->width())))&&((y>ui->frame->pos().y()&&(y<ui->frame->pos().y()+ui->frame->height()))))
    {

        if(!should_change_color)
        {
            qDebug()<<"change color";
            should_change_color = true;
            ui->frame->setStyleSheet("background-color:green");
        }
    }
    else
    {
        if(should_change_color)
        {
            qDebug()<<"change color";
            should_change_color = false;
           ui->frame->setStyleSheet("background-color:red");
        }

    }

}
void MainWindow::dragEnterEvent(QDragEnterEvent *event)
{
    qDebug()<<"drag enter";
    if(event->mimeData()->hasFormat("text/uri-list"))
        event->acceptProposedAction();
}
void MainWindow::dropEvent(QDropEvent *event)
{
    int x = event->pos().x();
    int y = event->pos().y();
    if(((x>ui->frame->pos().x()&&(x<ui->frame->pos().x()+ui->frame->width())))&&((y>ui->frame->pos().y()&&(y<ui->frame->pos().y()+ui->frame->height()))))
    {
    qDebug()<<"drop file"<<event->mimeData()->urls();
    foreach (QUrl url, event->mimeData()->urls()) {
        ui->label->setText(url.toLocalFile());
    }
    }
}
void MainWindow::dragMoveEvent(QDragMoveEvent *event)
{

}
