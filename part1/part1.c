#include <unistd.h>

int main(){
    dup(0);
    get_current_dir_name();
    fork();
    _exit(-1);
}
