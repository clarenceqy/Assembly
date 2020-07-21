#include <stdio.h> 
#include <sys/types.h> 
#include <unistd.h>  
#include <stdlib.h> 
#include <errno.h>   
#include <stdio.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/resource.h>
#include <sys/time.h>
#include <signal.h>  
#include <fcntl.h>


pid_t pid;
int outfd;

void sighandler(int sig) {
    if (sig == SIGALRM && pid > 0) {
        printf("kill pid:%d\n", pid);
        write(outfd, "TIMEOUT\n", strlen("TIMEOUT\n"));
        kill(pid, SIGKILL);
    }
}

int main(int argc,char* argv[]){
    // printf("argc: %d\n", argc);
    if (argc < 2) {
        // printf("params error: %s\n", argv[0]);
        return 1;
    }

    outfd = open("confine_result.txt", O_RDWR|O_CREAT|O_TRUNC, 0666);

    int ret = 1; 
    int status;  
    char *program = argv[1];
    // printf("program: %s\n", program);
    int i;
    char buf[128];
    for (i = 1; i < argc; i++) {
        if (i == argc - 1) {
            sprintf(buf, "%s\n", argv[i]);
        } else {
            sprintf(buf, "%s ", argv[i]);
        }
        write(outfd, buf, strlen(buf));
    }

    pid = fork();
    if (pid == -1) {
        printf("can't fork, error occured: %s\n", strerror(errno));
        exit(EXIT_FAILURE);
    }
    if (pid == 0) {
        close(outfd);
        //child
        struct rlimit m_limit;
        struct rlimit file_limit;
        struct rlimit cpu_limit;
        
        m_limit.rlim_cur = 64*1024*1024;
        m_limit.rlim_max = 64*1024*1024;
        if (setrlimit(RLIMIT_DATA, &m_limit) == -1) {
            printf("setrlimit data error: %s\n", strerror(errno));
        }
        if (setrlimit(RLIMIT_AS, &m_limit) == -1) {
            printf("setrlimit as error: %s\n", strerror(errno));
        }
        if (setrlimit(RLIMIT_MEMLOCK, &m_limit) == -1) {
            printf("setrlimit memlock error: %s\n", strerror(errno));
        }

        file_limit.rlim_cur = 4*1024*1024;
        file_limit.rlim_max = 4*1024*1024;
        setrlimit(RLIMIT_FSIZE, &file_limit);

        cpu_limit.rlim_cur = 60;
        cpu_limit.rlim_max = 60;
        setrlimit(RLIMIT_CPU, &cpu_limit);

        // printf("start execve\n");
        execve(program, argv + 1, NULL);
        printf("execve failed: %s\n", strerror(errno));

        return 0;
    }
    //parent
    printf("child: %d\n", pid);
    
    struct sigaction sa_usr;
    sa_usr.sa_flags = 0;
    sa_usr.sa_handler = sighandler;   //信号处理函数
    sigaction(SIGALRM, &sa_usr, 0);

    struct itimerval it_val;

    it_val.it_value.tv_sec = 60;
    it_val.it_value.tv_usec = 0;
    it_val.it_interval.tv_sec = 0;
    it_val.it_interval.tv_usec = 0;

    if(setitimer(ITIMER_REAL, &it_val, NULL) < 0) {
        printf("setitimer failed\n");
        exit(EXIT_FAILURE);
    }
    
    ret = waitpid(pid, &status, 0);
    if (ret < 0) {
        printf("waitpid failed\n");
        return 127;
    }
    if (WIFSIGNALED(status)) {
        ret = WTERMSIG(status);
        printf("program exit signaled: %d\n", ret);
        printf("TERMINATED\n");
        write(outfd, "TERMINATED\n", strlen("TERMINATED\n"));
        if (ret == SIGKILL || ret == SIGXFSZ || ret == SIGSEGV) {
            return 127;
        }
        return 128;
    }
    if (WIFEXITED(status)) {
        ret = WEXITSTATUS(status);
        printf("program exit normally: %d\n", ret);
        write(outfd, "NORMAL\n", strlen("NORMAL\n"));
        return ret;
    }
    close(outfd);
    return 0;
}

