#include "thread.h"

Thread::Thread(int s,QObject *parent) :
    QThread(parent)
{
    socket  = s;
    running = true;
}

void Thread::run()
{
    int len;
    struct can_frame frame;
    struct sockaddr_can addr;
    char buf[10];

    while(running)
    {
         recvfrom(socket,&frame,sizeof(struct can_frame),0,(struct sockaddr *)&addr,(socklen_t*)&len);
         memset(buf,0,10);
         strncpy(buf,(char*)frame.data,8);
         emit msg(QString(buf));
    }

}

void Thread::stop()
{
    running = false;
}
