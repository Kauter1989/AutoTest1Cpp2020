#include <iostream>

#define EXECUTE_LINE(command) std::cout << __LINE__ << ":" << std::endl; command

class A4 {
public:
    A4() { m_x = 4; std::cout << "A" << std::endl; }
    A4(int x) { m_x = x; std::cout << m_x << "->A" << std::endl; }
    A4(const A4&) { m_x = 1;  std::cout << "A->A" << std::endl; }
    A4& operator = (const A4& a) { std::cout << "A = A " << std::endl; return *this; }
    ~A4() { std::cout << "~A" << std::endl; }
    void print() { std::cout << "NVI\n"; v_print(); }
    void do_smth() { std::cout << "do(A)\n"; }
protected:
    int m_x;
    virtual void v_print() { std::cout << "A" << std::endl; }
};//class A4
class B4 : public A4 {
public:
    B4(int a) : A4(a) { std::cout << a << "->A" << std::endl; }
    B4() { std::cout << "B" << std::endl; }
    B4(const B4& b) { std::cout << "B->B" << std::endl; }
    B4& operator = (const B4& a) { std::cout << "B = B " << std::endl; return *this; }
    virtual ~B4() { std::cout << "~B" << std::endl; }
    void do_smth() { std::cout << "do(B)\n"; }
protected:
    virtual void v_print() { std::cout << m_x << std::endl; }
};//class B4
class C4 : public B4 {
public:
    C4() :m_a(10) { std::cout << "C" << std::endl; }
    C4(const C4& b) { std::cout << "C->C" << std::endl; }
    C4& operator = (const A4& a) { this->m_x = 44; std::cout << "C = A" << std::endl; return *this; }
    virtual ~C4() { std::cout << "~C" << std::endl; }
    void do_smth() { std::cout << "do(C)\n"; }
protected:
    virtual void v_print() { std::cout << "C = " << m_x << std::endl; *this = m_a; }
    A4 m_a;
}; //class C4
class D4 : public B4 {
public:
    D4() :B4(10) { std::cout << "D" << std::endl; }
    D4(const C4& c) : B4(c) { std::cout << "C->D" << std::endl; }
protected:
    virtual void v_print() { std::cout << "D = " << m_x << std::endl; A4::v_print(); }
}; //class D4
int main() {
    EXECUTE_LINE(B4 a1;              )
    EXECUTE_LINE(a1.print();         )
    EXECUTE_LINE(A4 & a = a1;        )
    EXECUTE_LINE(a.print();          )
    EXECUTE_LINE(A4 * a2 = new C4;   )
    EXECUTE_LINE(a2->print();        )
    EXECUTE_LINE(delete a2;          )
    EXECUTE_LINE(a2->do_smth();      )
    EXECUTE_LINE(C4 * b1 = new C4;   )
    EXECUTE_LINE(b1->do_smth();      )
    EXECUTE_LINE(A4 * b2 = new C4;   )
    EXECUTE_LINE(b2->do_smth();      )
    EXECUTE_LINE(b2->print();        )
    EXECUTE_LINE(b2->print();        )
    EXECUTE_LINE(*b2 = B4();         )
    EXECUTE_LINE(b2->do_smth();      )
    EXECUTE_LINE(b2->print();        )
    EXECUTE_LINE(D4 d(*b1);          )
    EXECUTE_LINE(delete b1;          )
    EXECUTE_LINE(delete b2;          )
}