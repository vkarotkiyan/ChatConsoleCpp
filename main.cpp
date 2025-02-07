#include "classes.h"
#include "misc.h"
using namespace  std;

int main(int argc, char* argv[])
{
    set_cons();
    clear_screen();
    Chat* chat = new Chat();

	while (chat->isWork()) {
		chat->initMenu();
	}

    delete chat;

    return 0;
}
