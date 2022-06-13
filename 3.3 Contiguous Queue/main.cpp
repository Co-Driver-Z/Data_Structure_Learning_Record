// 1、循环队列 (顺序表示)
// 1.1 数据在物理存储上是相邻的
// 1.2 采用书中方案一存储数据，即最大存储数量为 MAXSIZE - 1            即圆环循环
// 以多项式的单项式数据为例子
#include <iostream>
#include <initializer_list>
#define MAXSIZE 10                                              // 顺序队列的最大长度
/*
 *  多项式数据的定义
 */
struct LNode
{
    LNode()=default;                                            // 生成默认构造函数
    LNode(float coef_, int expn_): coef(coef_), expn(expn_){};  // 定义有参构造函数
    float coef = 0;
    int expn = 0;
    LNode& operator=(const LNode& L)= default;                  // 生成默认的=函数
};
typedef LNode* LNodeAdd;
/*
 *  0、队列的顺序存储结构
 */
struct Queue
{
    LNodeAdd base = nullptr;
    int front = 0;
    int rear = 0;
};
/*
 *  1、顺序队列的初始化 or 直接在 SqQueue中赋值 base 成员
 */
bool InitQueue(Queue& Q){
    Q.base = new LNode[MAXSIZE];
    if(!Q.base)
        throw std::runtime_error("InitQueue Failed!");
    return true;
}
/*
 *  2、求顺序队列的长度
 */
int QueueLength(Queue& Q){
    return (Q.rear - Q.front + MAXSIZE) % MAXSIZE;          // 🌟判断长度公式
}
/*
 *  3、循环队列的入队
 */
bool InQueue(Queue& Q, LNode& N){
    if((Q.rear + 1) % MAXSIZE == Q.front)                   // 🌟判断是否满队列公式
        throw std::runtime_error("InQueue Failed!");
    Q.base[Q.rear] = N;
    Q.rear = (Q.rear + 1) % MAXSIZE;                        // 🌟位置指向+1公式
    return true;
}
/*
 *  3、多个元素同时入队列
 */
bool InQueue(Queue& Q, const std::initializer_list<LNode>& il){
    if ((QueueLength(Q) + il.size()) > MAXSIZE - 1)
        throw std::runtime_error("InQueue Failed!");
    for(auto beg : il){
        Q.base[Q.rear] = beg;
        Q.rear = (Q.rear + 1) % MAXSIZE;
    }
    return true;
}
/*
 *  4、循环队列的出队(返回值并删除)
 */
LNode DeQueue(Queue& Q){
    if(Q.rear == Q.front)                                   // 🌟判断是否为空
        throw std::runtime_error("DeQueue Failed!");
    LNode temp =  Q.base[Q.front];
    Q.front = (Q.front + 1) % MAXSIZE;
    return temp;
}
/*
 *  5、取循环队列头部元素(不删除)
 */
LNode GetHead(Queue& Q){
    if(Q.rear == Q.front)
        throw std::runtime_error("GetHead Failed!");
    return Q.base[Q.front];
}
/*
 *  测试函数
 */
void test(){
    // 0、创建3个LNode
    LNode L1(1, 1), L2(2, 2), L3(3, 3);
    // 1、创建一个Queue
    Queue Q;
    InitQueue(Q);
    // 2、将2个LNode推入Queue中
    InQueue(Q, {L1, L2});
    // 3、打印头LNode
    std::cout << "Head.coef = " << GetHead(Q).coef << ";  Head.expn = " << GetHead(Q).expn << std::endl;
    // 4、获取Queue的长度
    std::cout << "Q.Length = " << QueueLength(Q) << std::endl;
    // 5、将第3个LNode推入Queue中
    InQueue(Q, L3);
    // 6、获取Queue的长度
    std::cout << "Q.Length = " << QueueLength(Q) << std::endl;
    // 7、推出头结点
    DeQueue(Q);
    // 8、打印头结点
    std::cout << "Q.Length = " << QueueLength(Q) << std::endl;
    std::cout << "Head.coef = " << GetHead(Q).coef << ";  Head.expn = " << GetHead(Q).expn << std::endl;
}
/*
 *  主函数
 */
int main(){
    std::cout << "Hello world!" << std::endl;

    try {
        test();
    }
    catch (std::runtime_error& error){
        std::cout << error.what() << std::endl;
    }

    return 0;
}