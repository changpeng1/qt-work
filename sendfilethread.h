#ifndef SENDFILETHREAD_H
#define SENDFILETHREAD_H

#include <QObject>
#include <QThread>
class SendFileThread : public QThread
{
    Q_OBJECT
public:
    SendFileThread(QObject *parent = 0);
    ~SendFileThread();
protected:
    void run() Q_DECL_OVERRIDE;

};

#endif // SENDFILETHREAD_H
