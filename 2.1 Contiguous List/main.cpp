/*
 * 作者：Wow-zheng
 * 时间：2022年6月9日
 * 声明：转载请注明出处： https://github.com/Wow-zheng
 * Disclaimer: Please indicate the source for reprint: https://github.com/Wow-zheng
 */



// 1、线性表-顺序表
// 1.1数据元素在逻辑上相邻
// 1.2数据元素在物理存储上也是相邻的
// 以多项式的构造为例
#include <iostream>
#define MAXSIZE 100

/*
 *  用于表示多项式的一项
 */
struct Polynomial
{
    float coef = 0;                             // 属于类内初始值
    int expn = 0;
bool operator==(const Polynomial& e) const{     // 重载关系运算符，用于后续的比较操作
    if (this->coef == e.coef && this->expn == e.expn)
        return true;
    else
        return false;
}
};
/*
 *  多项式的顺序存储结构
 */
struct SqList
{
    Polynomial* elem = nullptr;
    int length = 0;
};
/*
 *  2.1初始化顺序表
 */
bool InitList(SqList& L)
{
    L.elem = new Polynomial[MAXSIZE];
    if (!L.elem)
        throw std::runtime_error("InitList Failed!");
    L.length = 0;
    return true;
}
/*
 *  2.2顺序表的取值
 */
Polynomial& GetElem(SqList& L, int i)
{
    if (i < 1 || i > L.length)
        throw std::runtime_error("GetElem Failed!");
    return L.elem[i-1];
}
/*
 *  2.3顺序表的查找,查找到制定元素返回1，找不到返回0
 */
bool LocationElem(SqList& L, Polynomial& e)
{
    for (int i = 0; i < L.length; ++i) {
        if (L.elem[i] == e)
            return true;
    }
    return false;
}
/*
 *  2.4顺序表的插入操作
 */
bool ListInsert (SqList& L, int i, Polynomial& e)
{
    if (i < 1 || i > L.length + 1)
        throw std::runtime_error("ListInsert Failed!");
    if (L.length == MAXSIZE)
        throw std::runtime_error("ListInsert Failed!");
    for (int j = L.length; j >= i-1; j--)
        L.elem[j+1] = L.elem[j];
    L.elem[i-1] = e;
    ++L.length;
    return true;
}
/*
 *  2.5顺序表的删除操作
 */
bool ListDelete(SqList& L, int i)
{
    if (i < 1 || i > L.length)
        throw std::runtime_error("ListDelete Failed!");
    for (int j = i; j <= L.length; ++j)
        L.elem[j-1] = L.elem[j];
    --L.length;
    return true;
}
/*
 *  测试函数
 */
void test()
{
    Polynomial e1;                      // 0、创建一个单项式e1
    e1.coef = 1, e1.expn = 1;
    Polynomial e2;                      // 0、创建一个单项式e2
    e2.coef = 2, e2.expn = 2;
    Polynomial e3;                      // 0、创建一个单项式e3
    e2.coef = 3, e2.expn = 3;
    SqList List_;                       // 1、创建一个顺序表，长度为0
    InitList(List_);                 // 2、初始化顺序表，长度为100
    ListInsert(List_, 1, e2);   // 3、插入e2
    ListInsert(List_, 1, e1);   // 3、插入e1
    std::cout << "List_[1].coef = " << GetElem(List_, 1).coef << std::endl;  // 4、获取第1个元素的.coef
    std::cout << "List_[1].expn = " << GetElem(List_, 1).expn << std::endl;  // 4、获取第1个元素的.expn
    // 5、查找e2元素
    if (LocationElem(List_, e2)){
        std::cout << "e2 can be find!" << std::endl;
    }
    // 5、查找e3元素
    else if (LocationElem(List_, e3)){
        std::cout << "e3 can be find!" << std::endl;
    }
    // 6、删除第2个元素
    ListDelete(List_, 2);
    std::cout << "List_'s length = " << List_.length << std::endl;

}
/*
 *  主程序函数
 */
int main() {
    std::cout << "Hello, World!" << std::endl;

    try{
        test();                                     // 观察运行是否有异常
    }
    catch (std::runtime_error& error)
    {
        std::cout << error.what() << std::endl;     // 抛出异常
    }

    return 0;
}





