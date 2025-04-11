#include "chat.h"
#include "misc.h"
using namespace  std;

int main(int argc, char* argv[])
{
    set_cons();
    clear_screen();

    Chat* chat = new Chat();
    chat->readChat();

    while (chat->isWork()) {
        chat->initMenu();
    }

    chat->writeChat();
    delete chat;

    return 0;
}
