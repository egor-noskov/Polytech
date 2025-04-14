#include <iostream>
#include <cmath>
using namespace std;

class Division{
    int First;
    int Second;
    public:
    void Show(){
        cout<<"Первый элемент: "<<First<<endl;
        cout<<"Второй элемент: "<<Second<<endl;
    }
    void Read(){ 
    }
    void Init(double F, int S){
        First=F;
        Second=S;
    }
    int Ipart(){
        if(Second!=0) return First/Second;
        else{
            cout<<"Знаменатель равен нулю"<<endl;
            return 0;
        }
    }
};
Division Make_Division(int F,int S){
    Division t;
    t.Init(F,S);
    return t;
}
int main(){
    Division A, B;
    cout<<"1 способ с объектами:"<<endl;
    int First1=4,Second1=2;
    A.Init(First1,Second1);
    A.Show();
    cout<<"Результат деления: "<<endl<<A.Ipart()<<endl;
    
    cout<<"2 способ с объектами:"<<endl;
    B.Read();
    B.Show();
    cout<<"Результат деления: "<<endl<<B.Ipart()<<endl;

    cout<<"3 способ с объектами:"<<endl;
    Division* C = new Division;
    C->Init(100,5);
    C->Show();
    cout<<"Результат деления: "<<endl<<C->Ipart()<<endl;

    Division arr[3];
    cout<<"Статический массив"<<endl;
    for(int i=0;i<3;i++){
        cout<<i+1<<endl;
        arr[i].Read();
    }
    cout<<endl;
    for(int i=0;i<3;i++){
        arr[i].Show();
    }
    cout<<endl;
    for(int i=0;i<3;i++){
        cout<<"Результат деления: "<<arr[i].Ipart()<<endl;
    }

    Division* arr1=new Division[3];
    cout<<"Динамический массив"<<endl;
    for(int i=0;i<3;i++){
        cout<<i+1<<endl;
        arr1[i].Read();
    }
    cout<<endl;
    for(int i=0;i<3;i++){
        arr1[i].Show();
    }
    cout<<endl;
    for(int i=0;i<3;i++){
        cout<<"Результат деления: "<<arr1[i].Ipart()<<endl;
    }
    delete[] arr1;

    int First1,Second1;
    cout<<"Функция Make_Division"<<endl;
    cout<<"Введите первый элемент: "<<endl;
    cin>>First1;
    cout<<"Введите второй элемент: "<<endl;
    cin>>Second1;
    Division division=Make_Division(First1, Second1);
    division.Show();
    cout<<"Результат деления: "<<division.Ipart()<<endl;
    return 0;
}
