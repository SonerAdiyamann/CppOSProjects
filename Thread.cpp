#include <iostream>
#include <thread>
#include <mutex>
using namespace std;
class increaser{
    public:
        void operator()(int x,int *data)   {
            for(int i = 0;i < x;i++)   {
                (*data)++;
                cout << "increaser:" << *data << endl;
            }
        }
};

class decreaser{
    public:
        void operator()(int x,int *data)   {
            for(int i = 0;i < x;i++)   {
                (*data)--;
                cout << "decreaser:" << *data << endl;
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