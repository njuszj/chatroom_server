# include <iostream>
# include "utilities.h"
# include "log_sys.h"
# include "chatroom.h"

using namespace std;

void demo_test(){
    Chatroom ct(9999);
    ct.startListen();
}

int main(){
    demo_test();
}