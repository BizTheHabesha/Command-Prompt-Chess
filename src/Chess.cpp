#include "../lib/source.cpp"

using namespace std;

int main(){
    Board b;
    string s;
    while(1){
        b.playGame();
        cout << "Play again?\n[1] Yes\nAny key to exit\n > ";
        getline(cin, s, '\n');
        if(s != "1") break;
    }
    system("CLS");
    return 0;
}