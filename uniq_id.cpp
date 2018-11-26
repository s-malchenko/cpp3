#include <string>
#include <vector>
using namespace std;

#define CONC(num) var##num
#define LINENUM(num) CONC(num)
#define UNIQ_ID LINENUM(__LINE__)// Реализуйте этот макрос так, чтобы функция main компилировалась

int main()
{
    int UNIQ_ID = 0;
    string UNIQ_ID = "hello";
    vector<string> UNIQ_ID = {"hello", "world"};
    vector<int> UNIQ_ID = {1, 2, 3, 4};
}