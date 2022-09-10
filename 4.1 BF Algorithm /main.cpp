// 4.1 BF算法
// 1、使用顺序线性表实现BF算法，使用STL库，起始索引为1
// 2、使用顺序线性表实现BF算法，使用STL库，起始索引为0
#include <iostream>
/*
 *  1、起始索引为1的BF搜索
 */
int BF_SearchSubStrOneStart(std::string S, std::string T, int Pos){
    int i = Pos;
    int j = 1;
    int S_Len = S.size() - 1;
    int T_Len = T.size() - 1;
    while(i <= S_Len && j <= T_Len){
        if (S[i] == T[j])
            ++i, ++j;
        else{
            i = i - j + 2;
            j = 1;
        }
    }
    if (j > T_Len)
        return i - T_Len;
    else
        return -1;
}
/*
 *  2、起始索引为0的BF搜索
 */
int BF_SearchSubStrZeroStart(std::string S, std::string T, int Pos){
    int i = Pos;
    int j = 0;
    int S_Len = S.size();
    int T_Len = T.size();
    while(i < S_Len && j < T_Len){
        if (S[i] == T[j])
            ++i, ++j;
        else{
            i = i - j + 1;
            j = 0;
        }
    }
    if (j >= T_Len)
        return i - T_Len;
    else
        return -1;
}

int main()
{
    // 1、1起始索引BF搜索
    std::string S_OneStart(" abcdefg");
    std::string T_OneStart(" cde");
    int Num_OneStart = BF_SearchSubStrOneStart(S_OneStart, T_OneStart, 1);
    if (Num_OneStart < 0)
        std::cout << "[失败]未能找到子串!" << std::endl;
    else
        std::cout << "[成功]子串起始位置为:" << Num_OneStart << std::endl;
    // 2、0起始索引BF搜索
    std::string S_ZeroStart("abcdefg");
    std::string T_ZeroStart("cde");
    int Num_ZeroStart = BF_SearchSubStrZeroStart(S_ZeroStart, T_ZeroStart, 0);
    if (Num_ZeroStart < 0)
        std::cout << "[失败]未能找到子串!" << std::endl;
    else
        std::cout << "[成功]子串起始位置为:" << Num_ZeroStart << std::endl;
    return 0;
}