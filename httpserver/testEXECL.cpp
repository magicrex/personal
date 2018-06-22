#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[])
{
    char * const envp[] = {const_cast<char*>("AA=11"),const_cast<char*>("BB=22"), NULL};
    printf("Entering main ...\n");
    int ret;
   // ret =execl("./wwwroot/login_cgi", "./wwwroot/login_cgi", NULL);
    ret =execle("./wwwroot/login_cgi", "./wwwroot/login_cgi", NULL, envp);
    if(ret == -1)
        perror("execl error");
    printf("Exiting main ...\n");
    return 0;

}
