// 案例3.1  数制的转化：十进制->8进制
// 1、采用栈来实现，由于是"个体"是数字，使用STL标准库
// 2、采用栈来实现，自定义顺序栈
// 3、采用栈来实现，自定义链栈
# include <iostream>
# include <stack>
# define MAXSIZE 100                  // 自定义栈的最大元素
/*
 * 1、STL
 */
void Algorithm_STL(int Num){
    std::stack<int> NumStack;
    while(Num != 0){
        NumStack.push(Num % 8);
        Num = Num / 8;
    }
    while( !NumStack.empty()){
        std::cout << NumStack.top();  // 返回栈顶元素
        NumStack.pop();               // 弹出栈顶元素
    }
    std::cout << "\n";
}
/*
 * 2、自定义顺序表
 */
struct SNode                          // 1、"个体"用结构体的方式实现
{
    SNode() = default;
    SNode(int Value_): Value(Value_){};
    int Value = 0;
};
typedef SNode* SNodePtr;              // 2、类型别名
struct SNodeStack                     // 3、顺序栈的实现，用结构体的方式
{
    SNodePtr base = nullptr;
    SNodePtr top = nullptr;
    int StackSize = 0;
    int Length = 0;
};
void InitialSNodeStack(SNodeStack &S){// 4、顺序栈的初始化
    S.base = new SNode[MAXSIZE];
    S.top = S.base;
    S.StackSize = MAXSIZE;
}
bool Push(SNodeStack &S, SNode &s){   // 5、顺序栈的推入操作
    if (S.top - S.base == S.StackSize)
        throw std::runtime_error("Push Failed!");
    *S.top++ = s;
    ++S.Length;
}
bool Pop(SNodeStack &S){              // 6、顺序栈的弹出操作
    if (S.top == S.base)
        throw std::runtime_error("Pop Failed!");
    --S.top;
    --S.Length;
}
SNode Top(SNodeStack &S){             // 7、顺序栈的返回top操作
    if (S.top == S.base)
        throw std::runtime_error("GetTop Failed!");
    return *(S.top - 1);
}
void Algorithm_MySelfS(int Num){
    // 1、初始化顺序栈
    SNodeStack NumStack;
    InitialSNodeStack(NumStack);
    // 2、While循环求余数
    while(Num != 0){
        SNode s(Num % 8);
        Push(NumStack, s);
        Num = Num / 8;
    }
    // 3、While循环弹出最终8进制数
    while(NumStack.Length){
        std::cout << Top(NumStack).Value;
        Pop(NumStack);
    }
    std::cout << "\n";
}
/*
 * 3、自定义链栈
 */
struct Node                            // 1、个体用结构体的形式表示
{
    Node() = default;
    Node(int Value_): Value(Value_){};
    int Value = 0;
};
struct LNode                           // 2、链表中的单个节点：包括存储的Node以及下一个LNode的指针
{
    Node data;
    LNode* next = nullptr;
};
typedef LNode* StackLink;
bool Push_L(StackLink& S, Node& N){      // 3、链栈的推入操作
    StackLink L = new LNode;
    L->data = N;
    L->next = S;
    S = L;
    return true;
}
Node Pop_L(StackLink& S){                // 4、链栈的推出操作
    if (S == nullptr)
        throw std::runtime_error("Pop Failed!");
    StackLink TempS = S;
    S = S->next;
    Node N(TempS->data);
    delete TempS;
    return N;
}
Node GetElem_L(StackLink& S){            // 5、获取栈顶元素
    if (S == nullptr)
        throw std::runtime_error("GetElem Failed!");
    return S->data;
}
void Algorithm_MySelfL(int Num) {
    // 1、初始化链栈
    StackLink NumStack = nullptr;
    // 2、while对Num求余数并更新Num
    while(Num != 0){
        Node N(Num % 8);
        Push_L(NumStack, N);
        Num = Num / 8;
    }
    // 3、while弹出链栈直至链栈为空
    while(NumStack != nullptr){
        std::cout << Pop_L(NumStack).Value;
    }
}
/*
 * Main Function
 */
int main(){
    int Num = 521;                    // 需要转化为8进制的十进制数字
    std::cout << "十进制数: " << Num << " 的 8 进制数为: \n";
    // 1、使用STL库
    Algorithm_STL(Num);
    // 2、使用自定义顺序栈
    Algorithm_MySelfS(Num);
    // 3、使用自定义链栈
    Algorithm_MySelfL(Num);
    return 0;
}

