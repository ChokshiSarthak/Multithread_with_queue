#include "thread.h"
#include <memory>
int main(){

     std::auto_ptr<Thread> a(new Thread);
     a->Run();

     return 0;
}

