#include "fcntl.h"
#include "stdio.h"
#include <sys/stats.h>

int main(void) {

    int fd = open("salut", O_RDWR | s_IRWXU);

    printf("%d\n", fd);
    
    return (0);
}