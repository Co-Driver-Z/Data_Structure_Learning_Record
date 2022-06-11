// 1、顺序栈
// 1.1 数据在物理存储上是相邻的
#include <iostream>
#include <initializer_list>
#define MAXSIZE 100
/*
 *  栈的每个元素为一个类类型，即LNode，用于表示多项式中的一个单项式
 */
struct LNode
{
    LNode()= default;                                               // 使用默认初始化
    LNode(float coef_, int expn_):coef(coef_), expn(expn_){};       // 有参构造函数
    LNode& operator=(const LNode* L1){                              // 重载=运算符
        this->coef = L1->coef;
        this->expn = L1->expn;
    }
    float coef = 0.0;
    int expn = 0;
};
typedef LNode* LNodeStr;
/*
 *  3.0 顺序栈的定义
 */
struct SqStack
{
    LNodeStr base = nullptr;        // 指向栈底
    LNodeStr top = nullptr;         // 指向栈顶
    int stacksize = 0;              // 表示栈的最大数据
};
/*
 *  3.1 栈的初始化
 */
void InitStack(SqStack& S)
{
    S.base = new LNode[MAXSIZE];
    if (!S.base)
        throw std::runtime_error("InitStack Failed!");
    S.top = S.base;
    S.stacksize = MAXSIZE;
};
/*
 *  3.2 入栈操作
 */
bool Push(SqStack& S, LNode& e)
{
    if (S.top - S.base == S.stacksize)
        throw std::runtime_error("Push Failed!");
    *S.top++ = e;
    return true;
};
/*
 *  3.2 入栈操作 - 函数重载，同时入栈多个
 */
bool Push(SqStack& S, const std::initializer_list<LNode>& il)
{
    if ( (S.stacksize - (S.top - S.base)) < il.size())
        throw std::runtime_error("Push Failed!");
    for (auto beg : il) {
        *S.top++ = beg;
    }
    return true;
};
/*
 *  3.3 出栈操作
 */
LNode& Pop(SqStack& S)
{
    if (S.top == S.base)
        throw std::runtime_error("Pop Failed!");
    return *(--S.top);
}
/*
 *  3.4 获取栈顶元素
 */
LNode GetTop(SqStack& S)
{
    if (S.top == S.base)
        throw std::runtime_error("GetTop Failed!");
    return *(S.top-1);
}
/*
 *  测试程序
 */
void test()
{
    // 0、创建3个LNode
    LNode L1(1, 1), L2(2, 2), L3(3, 3);
    // 1、创建一个栈
    SqStack Stack1;
    InitStack(Stack1);
    // 2、将3个LNode入栈
    Push(Stack1, L1);           // 一个入栈，调用 bool Push(SqStack& S, LNode& e)
    Push(Stack1, {L2, L3});     // 多个入栈，调用 bool Push(SqStack& S, const std::initializer_list<LNode>& il)
    // 3、将第3个NLode出栈
    LNode L_temp = Pop(Stack1);
    std::cout << "L_temp.coef  = " << L_temp.coef << ";  L_temp.expn = " << L_temp.expn << std::endl;
    // 4、获取栈顶元素
    std::cout << "Stack.top.coef = " << GetTop(Stack1).coef << ";  Stack.top.expn = " << GetTop(Stack1).expn << std::endl;
}
/*
 *  主程序
 */
int main()
{
    std::cout << "Hello, World!" << std::endl;

    try{
        test();
    }
    catch (std::runtime_error& error){
        std::cout << error.what() << std::endl;
    }

    return 0;
}

