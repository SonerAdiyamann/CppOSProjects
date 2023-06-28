#include <iostream>
#include <thread>
#include <mutex>
using namespace std;
mutex m;
unique_lock<mutex> lk(m);
class increaser{
    public:
        void operator()(int x,int *data)   {
            for(int i = 0;i < x;i++)   {
                lock_guard<mutex> guard(mutex);
                (*data)++;
                lock_guard<mutex> guard(mutex);
                cout << "increaser:" << *data << endl;
            }
        }
};

class decreaser{
    public:
        void operator()(int x,int *data)   {
            for(int i = 0;i < x;i++)   {
                lk.unlock();
                (*data)--;
                cout << "decreaser:" << *data << endl;
                lk.lock();
            }
        }
};

int main()  {
    int data = 100;

    increaser inc;
    decreaser dec;

    thread th1(inc,100,&data);
    thread th2(dec,100,&data);

    th1.join();
    th2.join();
    
    return 0;
}