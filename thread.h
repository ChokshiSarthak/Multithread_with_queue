#ifndef THREAD_H
#define THREAD_H
#include<iostream>
#include<pthread.h>
#include<queue>
using namespace std;


class Thread{

public:
     int Run();
     static void* InsertElementHelper(void *obj);
     static void* LookUpElementHelper(void *obj);
     void InsertElement();
     void LookUpElement();
     Thread();
     ~Thread();

private:

    pthread_mutex_t m_queue_mutex;
    pthread_t insert_thread, lookup_thread;
    pthread_cond_t m_startLookup_cond;
    std::queue<char *> myqueue;

};

#endif     
