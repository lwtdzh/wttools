#include "wttool.h"

using namespace std;
using namespace wttool;

int main() {
    string a[4];
    a[0] = "432";
    a[1] = "431";
    a[2] = "23";
    a[3] = "232";
    
    msort<string>(a, 4);
    
    for (int i = 0; i < 4; ++i) {
        cout << a[i] << endl;
    }
    
    return 0;
}
