///*
// * 作者：Wow-zheng
// * 时间：2022年6月10日
// * 声明：转载请注明出处： https://github.com/Wow-zheng
// * Disclaimer: Please indicate the source for reprint: https://github.com/Wow-zheng
// */

// 1、单链表
// 1.1 数据元素在逻辑上相邻
// 1.2 数据在物理存储上不相邻，通过指针连接
// 以多项式的构造为例
#include <iostream>
#include <initializer_list>
/*
 *  用于表示多项式的一项
 */
struct LNode
{
    LNode(): coef(0.0), expn(0){};                                      // 防止被覆盖，定义默认构造函数
    LNode(float coef_, int expn_):coef(coef_), expn(expn_){};           // 有参构造函数
    float coef;
    int expn;
    struct LNode* next = nullptr;               // 连接下一结点
bool operator==(const LNode& e) const{          // 重载 == 运算符，用于后面的比较操作
    if (this->coef == e.coef && this->expn == e.expn)
        return true;
    else
        return false;
}
bool operator!=(const LNode& e) const{          // 重载 != 运算符，用于后面的比较操作
    if (this->coef != e.coef || this->expn != e.expn)
        return true;
    else
        return false;
}
};
typedef LNode* LinkList;
/*
 *  2.1 单链表的取值
 */
LNode& GetElem(LinkList& L, int i)
{
    LinkList P = L->next;                      // P指向首元结点
    int j = 1;
    while (P && j < i)
    {
        P = P->next;
        ++j;
    }
    if (!P || j > i)
        throw std::runtime_error("GetElem Failed!");
    return *P;
}
/*
 *  2.2 单链表的查找
 */
bool LocateElem(LinkList& L, LNode& e)
{
    LinkList P = L->next;                       // P指向首元结点
    while(P && (*P != e))                       // 顺着链表查找
        P = P->next;
    if (P && *P == e)                           // 如果P不为空，且*P==e
        return true;
    else
        return false;
}
/*
 *  2.3 链表的插入操作
 */
void ListInsert(LinkList& L, int i, LNode& e)
{
    LinkList P = L;
    int j = 0;
    while (P && j < i-1){
        P = P->next;
        ++j;
    }
    if (!P || j > i-1)
        throw std::runtime_error("ListInsert Failed!");
    auto s = new LNode;
    s->coef = e.coef, s->expn = e.expn;
    s->next = P->next;
    P->next = s;
}
/*
 *  2.4 单链表的删除
 */
void ListDelete(LinkList& L, int i)
{
    LinkList P = L;
    int j = 0;
    while (P->next && j < i-1)
    {
        P = P->next;
        ++j;
    }
    if (!(P->next) || (j > i-1))
        throw std::runtime_error("ListDelete Failed!");
    LinkList temp = P->next;
    P->next = temp->next;
    delete temp;
}
/*
 *  2.5 创建单链表 - 前插法
 */
void CreateList_H(LinkList& L, const std::initializer_list<LNode>& il)
{
    for (auto beg : il)
    {
        auto P = new LNode;
        P->coef = beg.coef, P->expn = beg.expn;
        P->next = L->next;
        L->next = P;
    }
}
/*
 *  2.6 创建单链表 - 后插法
 */
void CreateList_R(LinkList& L, const std::initializer_list<LNode>& il)
{
    LinkList R = L;
    for (auto beg : il)
    {
        auto P = new LNode;
        P->coef = beg.coef, P->expn = beg.expn;
        R->next = P;
        R = P;
    }
}
/*
 *  test函数
 */
void test()
{
    // 一、使用前插法
    // 1、创建4个多项式结点
    LNode e1(1, 1), e2(2, 2), e3(3, 3), e4(2, 2);
    // 2、使用前插法插入新建的3个结点
    auto L1 = new LNode;
    CreateList_H(L1, {e1, e2, e3});   // ->  L-e3-e2-e1
    // 3、取第一个值
    std::cout << "LNode.coef = " << GetElem(L1, 1).coef << ";  LNode.expn = " << GetElem(L1, 1).expn << std::endl;
    // 4、查找第二个值
    if (LocateElem(L1, e2))
        std::cout << "e2 can be find!" << std::endl;
    else
        std::cout << "e2 can not be find!" << std::endl;
    // 5、插入第4个元素
    ListInsert(L1, 1, e4);
    std::cout << "LNode_1.coef = " << GetElem(L1, 1).coef << ";  LNode_1.expn = " << GetElem(L1, 1).expn << std::endl;
    // 6、删除第四个元素
    ListDelete(L1, 1);
    std::cout << "LNode_1.coef = " << GetElem(L1, 1).coef << ";  LNode_1.expn = " << GetElem(L1, 1).expn << std::endl;
    std::cout << std::endl;
    // 二、使用前插法
    // 1、创建3个多项式结点
    // 2、使用后插法插入新建的链表
    auto L2 = new LNode;
    CreateList_R(L2, {e1, e2, e3});     // L-e1-e2-e3
    // 3、取第一个值
    std::cout << "LNode.coef = " << GetElem(L2, 1).coef << ";  LNode.expn = " << GetElem(L2, 1).expn << std::endl;
    // 4、查找第二个值
    if (LocateElem(L2, e2))
        std::cout << "e2 can be find!" << std::endl;
    else
        std::cout << "e2 can not be find!" << std::endl;
    // 5、插入第4个元素
    ListInsert(L2, 1, e4);
    std::cout << "LNode_1.coef = " << GetElem(L2, 1).coef << ";  LNode_1.expn = " << GetElem(L2, 1).expn << std::endl;
    // 6、删除第四个元素
    ListDelete(L2, 1);
    std::cout << "LNode_1.coef = " << GetElem(L2, 1).coef << ";  LNode_1.expn = " << GetElem(L2, 1).expn << std::endl;
}
/*
 *  主函数
 */
int main()
{
    std::cout << "Hello world!" << std::endl;

    try {
        test();                                     // 查看运行过程中是否有异常
    }
    catch (std::runtime_error& error)
    {
        std::cout << error.what() << std::endl;     // 抛出异常
    }

    return 0;
}