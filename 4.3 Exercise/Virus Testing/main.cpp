// 4.3、 使用BF算法和KMP算法进行病毒序列检测(环状病毒)
// DataIn.txt:
// Num
// VirusDNA   HumanDNA
// ......
// DataOutBF.txt/DataOutKMP.txt
// HumanDNA   Result
// ......
#include <iostream>
#include <fstream>
/*
 * 1、使用BF算法进行病毒检测(环状病毒)
 */
int BF_SearchSubStr(std::string S, std::string T, int Pos){
    int i = Pos;
    int j = 0;
    while (i < S.size() && j < T.size()){
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
void Virus_Detection_BF() {
    // 1、读取数据
    int Num = 0;
    std::ifstream InFile;
    InFile.open("DataIn.txt", std::ios::in);
    std::ofstream OutFile;
    OutFile.open("DataOutBF.txt", std::ios::out);
    if (!InFile.is_open()){
        std::cout << "读取文件失败!" << "\n";
        return;
    }
    if (!OutFile.is_open()){
        std::cout << "写入文件失败!" << "\n";
        return;
    }
    // 2、获取数据个数
    std::string Data;
    getline(InFile, Data);
    Num = std::stoi(Data);
    std::cout << "数据总数为: " << Num << "; \n";
    // 3、While循环进行检测并输出
    while (getline(InFile, Data)){
        // 4.1、病毒、人的数据初始化
        std::string VirusDNA;
        std::string HumanDNA;
        // 4.1、对数据行进行空格分割，获取病毒、人的数据
        VirusDNA = Data.substr(0, Data.find(' '));
        HumanDNA = Data.substr(Data.rfind(' ') + 1, Data.size());
        std::cout << "VirusDNA: \"" << VirusDNA << "\"; HumanDAN: \"" << HumanDNA << "\"; \n";
        // 5、扩充病毒数据 2m
        auto VirusDNA_Num = VirusDNA.size();
        VirusDNA.append(VirusDNA);
        // 6、m次进行模式匹配
        int Result = -1;
        for (int i = 0; i < VirusDNA_Num; ++i) {
            // 6.1、HumanDAN为主串，并获取长度为m的模式串
            std::string ModeStr = VirusDNA.substr(i, VirusDNA_Num);
            // 6.2、使用BF进行搜索
            Result = BF_SearchSubStr(HumanDNA, ModeStr, 0);
            if (Result < 0)
                continue;
            else{
                break;
            }
        }
        // 7、打印结果并输出至目标文本
        if (Result < 0){
            std::cout << "检测结果: 未感染\n";
            OutFile << "HumanDAN: " + HumanDNA + "; 结果: 未感染" << std::endl;
        }
        else{
            std::cout << "检测结果: 已感染\n";
            OutFile << "HumanDAN: " + HumanDNA + "; 结果: 已感染" << std::endl;
        }
    }
}
/*
 * 2、使用KMP算法进行病毒检测(环状病毒)
 */
void Get_Next(std::string S, int Next[]){
    int i = 0;
    int j = -1;
    Next[0] = -1;
    while (i < S.size()){
        if (j == -1 || S[i] == S[j]){
            ++i, ++j;
            Next[i] = j;
        }
        else
            j = Next[j];
    }
}
int KMP_SearchSubStr(std::string S, int S_Next[], std::string T, int Pos){
    int i = Pos;
    int j = 0;
    while (i < S.size() && j < T.size()){
        if (j == -1 || S[i] == T[j])
            ++i, ++j;
        else
            j = S_Next[j];
    }
    if (i >= S.size())
        return i - T.size();
    else
        return -1;
}
void Virus_Detection_KMP(){
    // 1、读取数据
    int Num = 0;
    std::ifstream InFile;
    InFile.open("DataIn.txt", std::ios::in);
    std::ofstream OutFile;
    OutFile.open("DataOutKMP.txt", std::ios::out);
    if (!InFile.is_open()){
        std::cout << "读取文件失败!" << "\n";
        return;
    }
    if (!OutFile.is_open()){
        std::cout << "写入文件失败!" << "\n";
        return;
    }
    // 2、获取数据的个数
    std::string Data;
    getline(InFile, Data);
    Num = std::stoi(Data);
    std::cout << "数据总数为: " << Num << "; \n";
    // 3、While循环进行检测并输出
    while (getline(InFile, Data)){
        // 4.1、病毒、人的数据初始化
        std::string VirusDNA;
        std::string HumanDNA;
        // 4.1、对数据行进行空格分割，获取病毒、人的数据
        VirusDNA = Data.substr(0, Data.find(' '));
        HumanDNA = Data.substr(Data.rfind(' ') + 1, Data.size());
        std::cout << "VirusDNA: \"" << VirusDNA << "\"; HumanDAN: \"" << HumanDNA << "\"; \n";
        // 5、扩充病毒数据 2m
        auto VirusDNA_Num = VirusDNA.size();
        VirusDNA.append(VirusDNA);
        // 6、m次进行模式匹配
        int Result = -1;
        for (int i = 0; i < VirusDNA_Num; ++i) {
            // 6.1、HumanDAN为主串，并获取长度为m的模式串
            std::string ModeStr = VirusDNA.substr(i, VirusDNA_Num);
            // 6.2、使用BF进行搜索
            Result = BF_SearchSubStr(HumanDNA, ModeStr, 0);
            if (Result < 0)
                continue;
            else{
                break;
            }
        }
        // 7、打印结果并输出至目标文本
        if (Result < 0){
            std::cout << "检测结果: 未感染\n";
            OutFile << "HumanDAN: " + HumanDNA + "; 结果: 未感染" << std::endl;
        }
        else{
            std::cout << "检测结果: 已感染\n";
            OutFile << "HumanDAN: " + HumanDNA + "; 结果: 已感染" << std::endl;
        }
    }
}
/*
 * Main Function
 */
int main()
{
    // 1、BF算法
    Virus_Detection_BF();
    std::cout << "\n";
    // 2、KMP算法
    Virus_Detection_KMP();
    return 0;
}
