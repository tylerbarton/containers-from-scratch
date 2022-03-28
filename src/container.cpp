//
// Created by Tyler Barton on 3/27/22.
//
#define _GNE_SOURCE
#include <cstdio>
#include <sched.h>
#include <sys/wait.h>
#include <iostream>
#include <sys/mount.h>
#include <cstring>
#include <unistd.h>
#include <sched.h>

#define STACK_SIZE (1024 * 1024)
static char child_stack[STACK_SIZE];

typedef struct clone_args{
    char **argv;
} cloneArgs;

// Container Types
const int DEFAULT       = SIGCHLD | CLONE_NEWNS;
const int PID_Flags     = SIGCHLD | CLONE_NEWPID;
const int MNT_Flags     = SIGCHLD | CLONE_NEWNS;
const int NET_Flags     = SIGCHLD | CLONE_NEWNET;
const int USER_Flags    = SIGCHLD | CLONE_NEWUSER;
const int UTS_Flags     = SIGCHLD | CLONE_NEWUTS;
const int IPC_Flags     = SIGCHLD | CLONE_NEWIPC;

// Change this to modify the container type
static int clone_flags = DEFAULT;

static int child_exec(void *child_args){
    cloneArgs  *args = ((cloneArgs *) child_args);

    // Attempt to mount
    if(mount("cgroup_root", "sys/fs/cgroup", "tmpfs", 0, "") != 0){
        fprintf(stderr, "Failed to unmount /proc.\n");
        exit(EXIT_FAILURE);
    }

    if(clone_flags == PID_Flags){
        //Mount proc with new pid
        if (mount("proc", "/proc", "proc", 0, "") != 0) {
            fprintf(stderr, "Failed to mount /proc: %s\n", strerror(errno));
            exit(EXIT_FAILURE);
        }
    } else if (clone_flags == UTS_Flags){
        char *name = "myhostnamespace";
        if (sethostname(name, strlen(name)) != 0) {
            fprintf(stderr, "Failed to set host name: %s\n", strerror(errno));
            exit(EXIT_FAILURE);
        }
    }

    // Create new child - should never return
    if(execvp(args->argv[0], args->argv) != 0){
        fprintf(stderr, "Failed to execute child: %s\n", strerror(errno));
        exit(EXIT_FAILURE);
    }

    // This should never be reached
    exit(EXIT_FAILURE);
}

int main(int argc, char* argv[]){
    struct clone_args args;
    args.argv = &argv[1];

    // clone(2), spawn our child process
    pid_t pid;
    pid = clone(child_exec, child_stack + STACK_SIZE, clone_flags, &args);

    // Check if child was created
    if(pid < 0){
        fprintf(stderr, "Container creation failed. \n");
        exit(EXIT_FAILURE);
    }

    // Wait on child
    if(waitpid(pid, nullptr, 0) == -1){
        fprintf(stderr, "Failed to wait on pid %d\n", pid);
        exit(EXIT_FAILURE);
    }

    exit(EXIT_SUCCESS);
}