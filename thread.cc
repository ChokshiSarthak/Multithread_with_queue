#include "thread.h"

Thread::Thread()
{

     pthread_mutex_init(&m_queue_mutex,NULL);
     pthread_cond_init(&m_startLookup_cond,NULL);
}

Thread::~Thread(){

     pthread_mutex_destroy(&m_queue_mutex);
     pthread_cond_destroy(&m_startLookup_cond);
}

int Thread::Run(){

     pthread_create(&insert_thread,NULL,&Thread::InsertElementHelper,this);
     pthread_create(&lookup_thread,NULL,&Thread::LookUpElementHelper,this);
     pthread_join(insert_thread,NULL);
     pthread_join(lookup_thread,NULL);
    
     return 0;
}

void *Thread::InsertElementHelper(void *obj){

     reinterpret_cast<Thread *>(obj)->InsertElement();

     return NULL;
}
void Thread::InsertElement(){

     pthread_mutex_lock(&m_queue_mutex);
     int a = 22;
     std::cout << "Inserting element " << a << " to queue " << "\n";
     myqueue.push(a);
     if(myqueue.size() > 0){
          std::cout << "Send signal to look up thread:" << "\n";
          pthread_cond_signal(&m_startLookup_cond);
     }
     pthread_mutex_unlock(&m_queue_mutex);
}
     
void *Thread::LookUpElementHelper(void *obj){

     reinterpret_cast<Thread *>(obj)->LookUpElement();
 
     return NULL;
}

void Thread::LookUpElement(){

     pthread_mutex_lock(&m_queue_mutex);
     if(myqueue.size() == 0){
          std::cout << "LookUP: Recived signal " << "\n";
          pthread_cond_wait(&m_startLookup_cond,&m_queue_mutex);
     }
     std::cout << "Lookup: wakes up " << "\n";
     int a = myqueue.front();
     std::cout << "element in the queue is: " << a << "\n";
     myqueue.pop();
     pthread_mutex_unlock(&m_queue_mutex);    
}

         
