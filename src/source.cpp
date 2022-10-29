#include "../lib/Chess.cpp"

using namespace std;

int main(){
    Board b;
    string s;
    while(1){
        b.playGame();
        cout << "Play again?    [1] Yes    [Any] Exit\n > ";
        getline(cin, s, '\n');
        if(s != "1") break;
    }
    clearT();
    return 0;
}