#include <iostream>
#include <cstdlib>
#include <conio.h>
#include <Windows.h>
#include <string>
using namespace std;

// 1 часть лабораторной - перекрываемые методы, виртуальные методы, проверка на принадлежность классу
class Figure {
protected:
    int x, y;

    Figure() {
        x = 0;
        y = 0;

        cout << "Figure::Figure()\n";
    }
    Figure(int x, int y) {
        this->x = x;
        this->y = y;

        cout << "Figure::Figure(int x, int y)\n";
    }

public:
    virtual ~Figure() {
        printf("Figure::~Figure()\n");
    }

    void set(int x, int y) {
        this->x = x;
        this->y = y;
    }

    virtual void getInfo() {
        cout << "X: " << x << " Y: " << y << endl;
    }

    void getCords() {
        cout << "Cords of Figure \n";
        cout << "X: " << this->x <<" Y: " << this->y << endl;
    }

    string getVariableClassname() {
        return "Figure";
    }
    virtual string classname() {
        return "Figure";
    }
    //Невиртуальный переопределенный в потомке метод в виртуальном непеопределенном методе
    virtual void classname2() {
        cout << "Figure \n";
        getVariableClassname2();
    }
    void getVariableClassname2() {
        cout << "Figure\n";
    }
    /////////////////
    //Виртуальный переопределенный в потомке метод в невиртуальном непереопределенном методе
    void classname3() {
        cout << "Figure \n";
        getVariableClassname3();
    }
    virtual void getVariableClassname3() {
        cout << "Figure\n";
    }
    /////////////////
    virtual bool isA(string who){
        return (who == "Figure");
    }
};

class ellipse : public Figure {
private:
    int osx;
    int osy;

    float S;
public:
    ellipse() {
        osx = 1;
        osy = 1;

        cout << "ellipse::ellipse()\n";
    }
    ellipse(int x, int y, int osx, int osy) : Figure(x, y) {
        this->osx = osx;
        this->osy = osy;

        cout << "ellipse::ellipse(int x, int y, int osx, int osy)\n";
    }

    void getInfo() {
        cout << "X: " << x << " Y: " << y << endl;
        cout << "osX: " << osx << " osY: " << osy << endl;
        S = 3.14 * 0.5 * osx * osy;
        cout << "Площадь: " << S << endl;
    }

    void getS() {
        S = 3.14 * 0.5 * osx * osy;
        cout << "Площадь: " << S << endl;
    }

    string getVariableClassname() {
        return "ellipse";
    }
    string classname() {
        return "ellipse";
    }
    //Невиртуальный переопределенный в потомке метод в виртуальном непеопределенном методе
    void getVariableClassname2() {
        cout << "ellipse\n";
    }
    /////////////////
    //Виртуальный переопределенный в потомке метод в невиртуальном непереопределенном методе
    void getVariableClassname3() {
        cout << "ellipse\n";
    }
    /////////////////

    bool isA(string who){
        return (who == "ellipse" || Figure::isA(who));
    }

    ~ellipse() {
        cout << "ellipse::~ellipse() \n";
    }
};

class BeatifulEllipse :  public ellipse {
    public:
        BeatifulEllipse() { 
        }

        void getBeatiful() {
            cout << "This beatiful ellipse" << endl;
        }

        string getVariableClassname() {
            return "BeatifulEllipse";
        }
        string classname() {
            return "BeatifulEllipse";
        }

        bool isA(string who){
            return (who == "BeatifulEllipse" || ellipse::isA(who));
        }

};

class square : public Figure {
    int a, b, P;
    public:
    square() {
        a = 1;
        b = 1;

    }
    string getVariableClassname() {
        return "square";
    }
    string classname() {
        return "square";
    }
    void getP() {
        P = (a + b)*2;
        cout << P << endl;
    }
    void getInfo() {
        cout << "X: " << x << " Y: " << y << endl;
        cout << "a: " << a << " b: " << b << endl;
        P = (a+b)*2;
        cout << "Периметр: " << P << endl;
    }

    bool isA(string who){
        return (who == "square" || Figure::isA(who));
    }

};

void proverkaPrinadleznosti() {
    // Проблема использование метода classname и isA в том, что нам нужно в каждом новом классе-потомке прописывать их, а также когда метод isA() 
    // ссылается на тот же метод в предке, конструккторы предка очевидно не срабатывают и мы просто используем прописанный метод с имеющимися переменными,
    // т.е. если вывести название в отдельную переменную класса и в методе isA() сравнивать не с в ручную прописанным значением а, например, с переменной класса classname,
    // то функция может некорректно работать, так, например, если мы в такой ситуации вызовем метод isA("ellipse") у потомка BeatifulEllipse,
    // то в процессе выполнения функции ellipse::isA(who) переменная (или аналогичный метод) classname будет всегда ссылаться на переменную класса BeatifulEllipse, а не ellipse
    Figure *mass[21];
    cout << "Создание массива общего класса-предка Figure и заполнение его разными объектами классов-предков: \n";
    for (int i = 0; i<21; i+=3) {
        mass[i] = new ellipse;
        mass[i+1] = new BeatifulEllipse;
        mass[i+2] = new square;
    } 
    cout << "Проверка принадлежности к общему классу-предку c помощью dynamic_cast и вызов метода, принадлежащему только ему: \n"; 
    for (int i = 0; i<21; i++) { 
        ellipse *e = dynamic_cast<ellipse *>(mass[i]);
        if (e) e->getS();
    }
    cout << "Проверка принадлежности к общему классу-предку c помощью в ручную созданной функции isA() и вызов метода, принадлежащему только ему: \n";
    for (int i = 0; i<21; i++) { 
        if (mass[i]->isA("ellipse")){
            ((ellipse*)mass[i])->getS();
        }
    }
    cout << "Освобождение памяти: \n";
    for (int i = 0; i<21; i++) {
        delete mass[i];
    } 
}
void demostrPerekryvatmihMethodov() {
    cout << "Демонстация перекрываемых методов: когда вызывается перекрытый метод, а когда наследуемый, на примере функцций getCords() и getInfo(): \n";
    ellipse e(1,2,3,4);
    cout << "Наследуемый метод от Figure который выводит координаты фигуры \n";
    e.getCords(); //Наследуемый метод
    cout << "Перекрытый метод от ellipse который выводит информацию об объекте \n";
    e.getInfo(); //Перекрытый метод
}
void demostrVirtualMethods() {
    cout << "Демонстрация виртуальных методов: когда вызывается наследуемый виртуальный метод, а когда базовый, на примере функции getVariableClassname() и виртуального classname(), также виртуального деструктора: \n";
    
    Figure *f = new ellipse;
    cout << "Вывод название класса, которому принадлежит переменная-указатель, с помощью НЕ виртуального метода \n";
    cout << f->getVariableClassname() << endl;
    cout << "Вывод название класса, которому принадлежит объект на который ссылается переменная-указатель, с помощью виртуального метода \n";
    cout << f->classname() << endl;
    delete f;
}
void UnvirtualMethod2InMethod1() {
    cout << "Ответ на вопрос из ТЗ: в методе1 базового класса вызывается метод2, который определен в этом же классе как невиртуальный, у класса-потомка метод2 переопределен: что происходит при вызове метода1 у класса-потомка?\n";
    cout << "Здесь метод1 - classname2() (виртуальный), метод2 - getVariableClassname2() (невиртуальный), проверять это имеет смысл только в рамках переменной-указателя класса Figure, который ссылает на объект класса-потомка ellipse\n";
    Figure *f  = new ellipse;
    f->classname2();
    delete f;
    cout << "Таким образом, у объекта ellipse вызывается метод classname2, но так как он не переопределен в ellipse, то он вызывается из ближайшего предка, где он определен, а именно из Figure, далее, из этого метода вызывается метод getVariableClassname2(), и, т.к. он не виртуальный он не \"сваливается\" вниз, а вызывается в том же классе, если он в этом классе определен \n ";
}
void VirtualMethod2InUnvMethod1() {
    cout << "Ответ на вопрос из ТЗ: в методе1 базового класса вызывается метод2, который определен в этом же классе как виртуальный, у класса-потомка метод2 переопределен: что происходит при вызове метода1 у класса-потомка? \n";
    cout << "Здесь метод1 - classname3() (невиртуальный), метод2 - getVariableClassname3() (виртуальный) \n";
    Figure *f = new ellipse;
    f->classname3();
    delete f;
    cout << "Таким образом, у объекта ellipse вызывается метод classname3, но так как он не виртуальный, то он вызывается из предка, а именно из Figure, далее, из этого метода вызывается виртуальный метод getVariableClassname2(), и, т.к. он виртуальный он \"сваливается\" вниз и вызывается в классе-потомке \n ";
}




//2 часть лабораторной - передача объектов в функцию
class Base {
public:
    Base() {
        cout << "Base::Base()\n";
    }
    Base(Base *obj) {
        cout << "Base::Base(Base *obj)\n";
    }
    Base(Base &obj) {
        cout << "Base::Base(Base &obj)\n";
    }
    virtual void qwe() {
        cout << "Base::qwe()\n";
    }

    ~Base() {
        cout << "Base::~Base()\n";
    }
    
};

class Desc : public Base {
public:
    Desc() {
        cout<<"Desc::Desc() \n";
    }
    Desc(Desc *obj) { 
        cout<<"Desc::Desc(Desc *obj) \n";
    }
    Desc(Desc &obj) {
        cout<<"Desc::Desc(Desc &obj) \n";
    }
    void qwe() {
        cout << "Desc::qwe()\n";
    }
    ~Desc() { 
        cout<<"Desc::~Desc() \n";
    }

};

void func1(Base obj) {
    cout << "func1\n";
    obj.qwe();
}
void func2(Base *obj) { 
    cout << "func2\n";
    obj->qwe();
}
void func3(Base &obj) { 
    cout << "func3\n";
    obj.qwe();
}

void secondPart() {
    cout << endl;
    cout << "Вторая часть лабораторной: \n";

    cout << "Переменная Base b1: \n";
    Base b1;
    cout << "Переменная Desc d1: \n";
    Desc d1;
    cout << "Переменная Base *d2 = new Desc: \n";
    Base *d2 = new Desc;
    cout << "Переменная Base *b2 = new Base: \n";
    Base *b2 = new Base;

    cout << "Запуск func1(b1)\n";
    func1(b1);
    cout << "Запуск func1(d1)\n";
    func1(d1);
    cout << "Запуск func1(*d2)\n";
    func1(*d2);
    cout << "Запуск func1(*b2)\n";
    func1(*b2);

    cout << "Во всех случаях func1 вызывает конструктор класса Base::Base(Base &obj), т.к. функция делает локальную копию объекта, который в нее поступает, далее выполняется функция, в конце выполняется уничтожение локальной переменной деструктором Base::~Base()\n";
    cout << "Функция обрабатывает класс Desc, хотя на вход должна принимать объект класса Base, очевидно, потому что Desc является потомком Base\n";

    cout << "Запуск func2(b1)\n";
    func2(&b1);
    cout << "Запуск func2(d1)\n";
    func2(&d1);
    cout << "Запуск func2(*d2)\n";
    func2(d2);
    cout << "Запуск func2(b2)\n";
    func2(b2);

    cout << "В данном случае при работе func2 не срабатывают никакие конструкторы и деструкторы, т.к. функция напрямую работает с объектами, а не с их значениями, поэтому создавать локальные копии не нужно\n";

    cout << "Запуск func3(b1)\n";
    func3(b1);
    cout << "Запуск func3(d1)\n";
    func3(d1);
    cout << "Запуск func3(*d2)\n";
    func3(*d2);
    cout << "Запуск func(b2)\n";
    func3(*b2);
    
    cout << "В данном случае, работа func3 почти не отличается от работы func2, за исключением того, что func2 принимала на вход указатель, поэтому переменные b1 и d1 нужно было использовать вместе с \"&\", чтобы получить адрес, когда как d2 и b2, уже являются адресом, а func3 можно сказать получает адрес переменной \"внутри\", поэтому, как и в случае с func1, мы применяем к ним \"*\"\n";
    delete b2;
    delete d2;
}





int main() {
    setlocale(LC_ALL, "rus");
    proverkaPrinadleznosti();
    demostrPerekryvatmihMethodov();
    demostrVirtualMethods();
    UnvirtualMethod2InMethod1();
    VirtualMethod2InUnvMethod1();
    secondPart();
}