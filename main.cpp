#include <iostream>
#include <string>

using namespace std;

class Cat{
    private:
        string name;

    public: 
        Cat(string name) : name{name}{}

        string get_name(){
            return this->name;
        }
};

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

        SharedPointer& operator=(const SharedPointer& sp){
            if(&sp != this){
                if(this->rc->decrease() == 0){
                    cout << "deleted by = " << endl;
                    delete p;
                    delete rc;
                }

                p = sp.p;
                rc = sp.rc;
                rc->increase();
            }
        }

        T* operator-> (){
            return this->p;
        }

         ~SharedPointer(){
            if(this->rc->decrease() == 0){
                 cout << "deleted" << endl;
                 delete p;
                 delete rc;
            }
        }

        T get(){
            return *p;
        }
};

int main(){
    auto sp = SharedPointer(new Cat("snowy"));
    auto sp2{sp};

    //auto sp3 = sp;
    //cout << sp3.get() << endl;
    cout << sp2->get_name() << endl;
    cout << sp->get_name() << endl;
}