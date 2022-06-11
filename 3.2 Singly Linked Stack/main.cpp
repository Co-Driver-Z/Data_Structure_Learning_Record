// 1、链栈
// 1.1 数据在物理存储上不是相邻的
#include <iostream>
#include <initializer_list>
/*
 *  多项式数据结构
 */
struct LNode
{
    LNode()= default;                                               // 使用默认构造函数
    LNode(float coef_, int expn_):coef(coef_), expn(expn_){};       // 有参构造函数
    LNode& operator=(const LNode& L){                               // 重载=运算符
        this->coef = L.coef;
        this->expn = L.expn;
        return *this;
    }
    float coef = 0;
    int expn = 0;
};
/*
 *  3.0 链栈的存储结构 - 单个结点
 */
struct StackNode
{
    LNode data;
    StackNode* next = nullptr;
};
typedef StackNode* LinkStack;
/*
 *  3.1 链栈的入栈 - 单个元素的入栈
 */
bool Push(LinkStack& S, LNode& e){
    auto P = new StackNode;
    P->data = e;
    P->next = S;
    S = P;
    return true;
}
/*
 *  3.1 链栈的入栈 - 多个元素的入栈
 */
bool Push(LinkStack& S, const std::initializer_list<LNode>& il){
    for (auto beg : il){
        auto P = new StackNode;
        P->data = beg;
        P->next = S;
        S = P;
    }
    return true;
}
/*
 *  3.2 链栈的出栈
 */
LNode Pop(LinkStack& S){
    if (S == nullptr)
        throw std::runtime_error("Pop Failed!");
    LinkStack temp = S;
    S = S->next;
    LNode L(temp->data);
    delete temp;
    return L;
}
/*
 *  3.3 栈顶元素的获取
 */
LNode GetElem(LinkStack& S){
    if (S == nullptr)
        throw std::runtime_error("GetElem Failed!");
    return S->data;
}

void test()
{
    // 0、创建3个LNode元素
    LNode L1(1, 1), L2(2, 2), L3(3, 3);
    // 1、创建一个链栈
    auto Stack1 = new StackNode;
    // 2、将3个LNode元素推入链栈中 分单个和多个
    Push(Stack1, L1);
    Push(Stack1, {L2, L3});
    // 3、将推出栈顶元素
    LNode L_temp = Pop(Stack1);
    std::cout << "L_temp.coef = " << L_temp.coef << ";  L_temp.expn = " << L_temp.expn << std::endl;
    // 4、获取栈顶元素
    std::cout << "L_top.coef = " << GetElem(Stack1).coef << "; L_top.expn = " << GetElem(Stack1).expn << std::endl;
}

int main()
{
    std::cout << "Hello, World!" << std::endl;

    try {
        test();
    }
    catch (std::runtime_error& error) {
        std::cout << error.what() << std::endl;
    }

    return 0;
}
