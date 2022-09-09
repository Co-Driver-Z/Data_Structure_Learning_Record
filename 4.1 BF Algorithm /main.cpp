// 4.1 BF(Brute-Force)算法
// 1.1、使用顺序线性表实现BF算法，使用STL库
#include <iostream>
#include <vector>
typedef unsigned int uint;
/*
 *  1.1、使用STL库进行实现
 */
int BF_SearchSubStr(std::vector<char> S, std::vector<char> T, int Pos){
    int i = Pos;
    int j = 0;
    while(i < S.size() && j < T.size()){
        if (S[i] == T[j])
            ++i, ++j;
        else{
            i = i - j + 1;
            j = 0;
        }
    }
    if (j >= T.size())
        return i - T.size();
    else
        return -1;
}

int main()
{
    std::vector<char> S = {'a', 'b', 'c', 'd', 'e', 'f', 'g'};
    std::vector<char> T = {'c', 'd', 'e'};
    uint Num = BF_SearchSubStr(S, T, 0);
    if (Num < 0)
        std::cout << "[失败]未能找到子串!" << std::endl;
    else
        std::cout << "[成功]子串起始位置为:" << Num << std::endl;
    return 0;
}
