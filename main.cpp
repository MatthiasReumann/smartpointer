#include <iostream>

using namespace std;

class RefCount{
    private:
        int cnt;

    public:
        void increase(){
            this->cnt++;
        }

        int decrease(){
            return --this->cnt;
        }
};

template <typename T>
class SharedPointer{
    private: 
        T *p;
        RefCount* rc;

    public:
        SharedPointer(T* i) : p{i}{
            this->rc = new RefCount();
            this->rc->increase();
        }

        SharedPointer(const SharedPointer& sp) : p{sp.p}, rc{sp.rc}{
            cout << "copied" << endl;
            this->rc->increase();
        }

        T get(){
            return *p;
        }
};

int main(){
    auto sp = SharedPointer(new double{3.1});
    auto sp2{sp};
    cout << sp2.get() << endl;
    cout << sp.get() << endl;
}