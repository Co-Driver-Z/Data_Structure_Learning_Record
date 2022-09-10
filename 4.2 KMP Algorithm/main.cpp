// 4.2 KMP算法
// 1、使用顺序线性表实现KMP算法，使用STl库，字符串的起始索引为1
// 2、使用顺序线性表实现KMP算法，使用STl库，字符串的起始索引为0
#include <iostream>
#include <vector>
/*
 * 1.1、字符串起始索引为1时，计算模式串的Next数组
 */
void Get_NextOneStart(std::string S, int S_Next[])
{
    // i -> 代表"最大重叠尾串"的"末尾索引"
    // j -> 代表"最大重叠首串"的"末尾索引"
    int i = 1;
    int j = 0;
    int S_Len = S.size() - 1;
    S_Next[1] = 0;
    while(i < S_Len){
        if (j == 0 || S[i] == S[j]){
            ++i, ++j;
            S_Next[i] = j;
        }
        else
            j = S_Next[j];
    }
}
/*
 * 1.2、字符串起始索引为1时，寻找子串的位置
 */
int KMP_SearchSubStrOneStart(std::string S, const int S_Next[], std::string T, int Pos){
    int i = Pos;
    int j = 1;
    int S_Len = S.size() - 1;
    int T_Len = T.size() - 1;
    while (i <= S_Len && j <= T_Len){
        if (j == 0 || S[i] == T[j])
            ++i, ++j;
        else
            j = S_Next[j];
    }
    if (j > T_Len)
        return i - T_Len;
    else
        return -1;

}
/*
 * 2.1、字符串起始索引为0时，计算模式串的Next数组
 */
void Get_NextZero(std::string S, int S_Next[]){
    // i -> 代表"最大重叠尾串"的"末尾索引"
    // j -> 代表"最大重叠首串"的"末尾索引"
    int i =  0;
    int j = -1;
    int S_Len = S.size();
    S_Next[0] = -1;
    while (i < S_Len){
        if (j == -1 || S[i] == S[j]){
            ++i, ++j;
            S_Next[i] = j;
        }
        else
            j = S_Next[j];
    }
}
/*
 * 2.2、字符串起始索引为0时，寻找子串的位置
 */
int KMP_SearchSubStrZeroStart(std::string S, const int S_Next[], std::string T, int Pos){
    int i = Pos;
    int j = 0;
    int T_Len = T.size();
    int S_Len = S.size();
    while (i < S_Len && j < T_Len){
        if (j == -1 || S[i] == T[j])
            ++i, ++j;
        else
            j = S_Next[j];
    }
    if (j >= T_Len)
        return i - T_Len;
    else
        return -1;
}
int main()
{
    // 0、模式串、Next数组初始化
    std::string S_OneStart(" abaabc");
    std::string T_OneStart(" aab");
    int S_NextOneStart[S_OneStart.size()];
    S_NextOneStart[0] = -1;
    // 1.1、求解模式串的Next数组
    Get_NextOneStart(S_OneStart, S_NextOneStart);
    // 1.2、打印模式串的Next数组
    for (int NextValue : S_NextOneStart)
        std:: cout << NextValue << " ";
    // 1.3、寻找子串
    int Num = KMP_SearchSubStrOneStart(S_OneStart, S_NextOneStart, T_OneStart, 1);
    if (Num > 0)
        std::cout << "SubStr Pos is " << Num;
    std::cout << std::endl;

    // 0、模式串、Next数组初始化
    std::string S_ZeroStart("abaabc");
    std::string T_ZeroStart("aab");
    int S_NextZeroStart[S_ZeroStart.size()];
    // 2.1、求解模式串的Next数组
    Get_NextZero(S_ZeroStart, S_NextZeroStart);
    // 2.2、打印模式串的Next数组
    for (int NextValue : S_NextZeroStart)
        std:: cout << NextValue << " ";
    // 2.3、寻找字串
    Num = KMP_SearchSubStrZeroStart(S_ZeroStart, S_NextZeroStart, T_ZeroStart, 0);
    if (Num > 0)
        std::cout << "SubStr Pos is " << Num;
    std::cout << std::endl;

    return 0;
}

