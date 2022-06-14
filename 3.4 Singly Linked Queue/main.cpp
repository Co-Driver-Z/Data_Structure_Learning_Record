// 1、链队列
// 1.1 在物理存储上不相邻的队列
// 1.2 采用 单链表
#include <iostream>
#include <initializer_list>
/*
 *  多项式中单项式的数据表达
 */
struct LNode
{
    LNode() = default;
    LNode(float coef_, int expn_): coef(coef_), expn(expn_){};
    float coef = 0.0;
    int expn = 0;
    LNode& operator=(const LNode& e) = default;              // 使用自动生成的赋值函数
};
/*
 *  链队的节点
 */
struct QNode
{
    LNode data;
    QNode* next = nullptr;
};
typedef QNode* QueuePtr;
/*
 *  链队的表示形式
 */
struct LinkQueue
{
    QueuePtr front = nullptr;         // 指向头节点QNode(不是首元节点QNode)
    QueuePtr rear = nullptr;          // 指向最后一个QNode
};
/*
 *  1、链队的初始化
 */
bool InitQueue(LinkQueue& Q){
    Q.front  = Q.rear = new QNode;
    if(!Q.front)
        throw std::runtime_error("InitQueue Failed!");
    return true;
}
/*
 *  2、链队的入队
 */
bool InQueue(LinkQueue& Q, LNode& e){
    auto P = new QNode;
    P->data = e;
    Q.rear->next = P;
    Q.rear = P;
    return true;
}
/*
 *  2、链队的入队 - 多个节点同时入队
 */
bool InQueue(LinkQueue& Q, const std::initializer_list<LNode>& il){
    for(auto beg : il){
        auto P = new QNode;
        P->data = beg;
        Q.rear->next = P;
        Q.rear = P;
        return true;
    }
}
/*
 *  3、链队队出队 - 需要销毁操作
 */
LNode DeQueue(LinkQueue& Q){
    if(Q.front == Q.rear)                                // 判断队列是否为空
        throw std::runtime_error("DeQueue Failed!");
    QueuePtr P = Q.front->next;
    LNode temp = P->data;
    Q.front->next = P->next;
    if(Q.rear == P)
        Q.rear = Q.front;
    delete P;
    return temp;
}
/*
 *  4、链队的头部数据获取
 */
LNode GetHead(LinkQueue& Q){
    if(Q.front == Q.rear)
        throw std::runtime_error("GetHead Failed!");
    return Q.front->next->data;
}

/*
 *  测试函数
 */
void test(){
    // 1、创建3个LNode
    LNode L1(1, 1), L2(2, 2), L3(3, 3);
    // 2、创建链队 + 初始化
    LinkQueue Q;
    InitQueue(Q);
    // 3、将1个LNode推入链队
    InQueue(Q, L1);
    // 4、打印头部数据
    std::cout << "Q.front.coef = " << GetHead(Q).coef << ";  Q.front.expn = " << GetHead(Q).expn << std::endl;
    // 5、推出头部数据
    DeQueue(Q);
    // 6、将2个LNode推入链队
    InQueue(Q, {L2, L3});
    // 7、打印头部数据
    std::cout << "Q.front.coef = " << GetHead(Q).coef << ";  Q.front.expn = " << GetHead(Q).expn << std::endl;
}
/*
 *  主程序
 */
int main()
{
    std::cout << "Hello world!" << std::endl;

    try{
        test();
    }
    catch(std::runtime_error& error){
        std::cout << error.what() << std::endl;
    }

    return 0;
}
