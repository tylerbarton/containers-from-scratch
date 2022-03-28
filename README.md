# Barebones Containers
A container is a lightweight environment which shares a kernel and resources from a host machine but isolates itself from other processes. Think of them as wrappers for your projects.
The resources that are shared by the host can be controlled by set flags by the caller.

**Warning**: This project is not meant to be used as an ultimate solution container such as Docker or Kubernetes. **Proceed with caution.**

# Types of Containers
| Container                | Flag            | Isolates                         |
|--------------------------|-----------------|----------------------------------|
| Process ID (pid)         | CLONE_NEWPID    | Process IDs                      |
| User ID (user)           | CLONE_NEWUSER   | User IDs, Group IDs              |
| Network (net)            | CLONE_NEWNET    | Network devices, ports           |
| Interprocess Comm. (ipc) | CLONE_NEWIPC    | System V IPC, POSIX messages     |
| UNIX Time-Sharing (uts)  | CLONE_NEWUTS    | Host name, NIS Domain name       |
| Mount                    | CLONE_NEWNS     | Mount devices, Mount Filesystems |
| Control Group (cgroup)   | CLONE_NEWCGROUP | Cgroup root directory            |     

# Creating Containers