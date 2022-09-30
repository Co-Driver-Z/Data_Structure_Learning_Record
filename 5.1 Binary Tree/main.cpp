// 学习使用二叉树
// 1、创建一个二叉树(给出先序序列，对于非完全二叉树，用#进行空位置的补充)
// 2、先序遍历二叉树
// 3、层次遍历二叉树
// 4、计算二叉树的深度
// 5、计算二叉树的结点总数
// 6、计算二叉树的叶子节点总数

#include <iostream>
#include <stack>
#include <queue>

// 二叉树的节点，此处节点即代表一个节点也代表一个树
typedef struct BiTNode
{
    BiTNode(): Data(' '), LChild(nullptr), RChild(nullptr){};
    char Data;
    BiTNode* LChild;
    BiTNode* RChild;
} *BiTree;

// 1、根据先序创建一个二叉树
void CreateBiTree(BiTree& T, std::queue<char>& QUEUE) {
    // 0、从先序中获取当前遍历元素
    if(QUEUE.empty())
        return;
    char C = QUEUE.front();
    QUEUE.pop();
    // 1、如果C为nullptr，则创建一个空树/空节点
    if (C == '#')
        T = nullptr;
    // 2、如果S不为空，则按照先序创建二叉树
    else {
        T = new BiTNode();
        T->Data = C;
        CreateBiTree(T->LChild, QUEUE);
        CreateBiTree(T->RChild, QUEUE);
    }
};

// 2、先序遍历二叉树
void PreOrderTraverse(BiTree& T){
    if(T == nullptr)
        return;
    else{
        std::cout << T->Data;
        PreOrderTraverse(T->LChild);
        PreOrderTraverse(T->RChild);
    }
}

// 3、层次遍历二叉树
void LevelOrder(BiTree& T){
    std::queue<BiTNode*> QUEUE;
    QUEUE.push(T);
    while(!QUEUE.empty()){
        BiTNode* TempNodePos = QUEUE.front();
        QUEUE.pop();
        std::cout << TempNodePos->Data;
        if(TempNodePos->LChild != nullptr)
            QUEUE.push(TempNodePos->LChild);
        if(TempNodePos->RChild != nullptr)
            QUEUE.push(TempNodePos->RChild);
    }
}

// 4、计算二叉树的深度
int Depth(BiTree& T){
    if (T == nullptr)
        return 0;
    else{
        int L = Depth(T->LChild);
        int R = Depth(T->RChild);
        if (L > R)
            return L + 1;
        else
            return R + 1;
    }
}

// 5、计算二叉树节点的总数
int NodeCount(BiTree& T){
    if (T == nullptr)
        return 0;
    else
        return NodeCount(T->LChild) + NodeCount(T->RChild) + 1;
}

// 6、计算二叉树叶子结点的个数
int LeafCount(BiTree& T){
    if (T == nullptr)
        return 0;
    if (T->LChild == nullptr && T->RChild == nullptr)
        return 1;
    else
        return LeafCount(T->LChild) + LeafCount(T->RChild);
}

// main func
int main()
{
    // 1、非完全二叉树的先序序列：
    std::string S = "ABC##DE#G##F###";
    std::queue<char> QUEUE;
    for (auto C : S)
        QUEUE.push(C);
    // 2、构建一个二叉树
    BiTree T = nullptr;
    CreateBiTree(T, QUEUE);
    // 3、遍历二叉树(先序)
    PreOrderTraverse(T);
    std::cout << "\n";
    // 4、层次遍历二叉树
    LevelOrder(T);
    std::cout << "\n";
    // 4、求解二叉树的深度
    int DepthNum = Depth(T);
    std::cout << "The Depth of the T is :" << DepthNum << "\n";
    // 5、求解二叉树的结点个数
    int NodeNum = NodeCount(T);
    std::cout << "The Num of Node is : " << NodeNum << "\n";
    // 6、计算二叉树的叶子结点的个数
    int LeafNum = LeafCount(T);
    std::cout << "The Num of Leaf is :" << LeafNum << "\n";
    return 0;
}
