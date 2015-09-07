//
//  mynode_constants.cpp
//  mynode
//
//  Created by Hannah Zhang on 15/9/7.
//
//

#include "mynode_constants.h"
#include <unistd.h>
#include <fcntl.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/stat.h>

namespace mynode {
    using v8::Handle;
    using v8::Object;

void DefineSystemConstants(Handle<Object> target) {
    // file access modes
    MYNODE_DEFINE_CONSTANT(target, O_RDONLY);
    MYNODE_DEFINE_CONSTANT(target, O_WRONLY);
    MYNODE_DEFINE_CONSTANT(target, O_RDWR);
    
    MYNODE_DEFINE_CONSTANT(target, S_IFMT);
    MYNODE_DEFINE_CONSTANT(target, S_IFREG);
    MYNODE_DEFINE_CONSTANT(target, S_IFDIR);
    MYNODE_DEFINE_CONSTANT(target, S_IFCHR);
#ifdef S_IFBLK
    MYNODE_DEFINE_CONSTANT(target, S_IFBLK);
#endif
    
#ifdef S_IFIFO
    MYNODE_DEFINE_CONSTANT(target, S_IFIFO);
#endif
    
#ifdef S_IFLNK
    MYNODE_DEFINE_CONSTANT(target, S_IFLNK);
#endif
    
#ifdef S_IFSOCK
    MYNODE_DEFINE_CONSTANT(target, S_IFSOCK);
#endif
    
#ifdef O_CREAT
    MYNODE_DEFINE_CONSTANT(target, O_CREAT);
#endif
    
#ifdef O_EXCL
    MYNODE_DEFINE_CONSTANT(target, O_EXCL);
#endif
    
#ifdef O_NOCTTY
    MYNODE_DEFINE_CONSTANT(target, O_NOCTTY);
#endif
    
#ifdef O_TRUNC
    MYNODE_DEFINE_CONSTANT(target, O_TRUNC);
#endif
    
#ifdef O_APPEND
    MYNODE_DEFINE_CONSTANT(target, O_APPEND);
#endif
    
#ifdef O_DIRECTORY
    MYNODE_DEFINE_CONSTANT(target, O_DIRECTORY);
#endif
    
#ifdef O_EXCL
    MYNODE_DEFINE_CONSTANT(target, O_EXCL);
#endif
    
#ifdef O_NOFOLLOW
    MYNODE_DEFINE_CONSTANT(target, O_NOFOLLOW);
#endif
    
#ifdef O_SYNC
    MYNODE_DEFINE_CONSTANT(target, O_SYNC);
#endif
    
#ifdef O_SYMLINK
    MYNODE_DEFINE_CONSTANT(target, O_SYMLINK);
#endif
    
#ifdef O_DIRECT
    MYNODE_DEFINE_CONSTANT(target, O_DIRECT);
#endif
    
#ifdef O_NONBLOCK
    MYNODE_DEFINE_CONSTANT(target, O_NONBLOCK);
#endif
    
#ifdef S_IRWXU
    MYNODE_DEFINE_CONSTANT(target, S_IRWXU);
#endif
    
#ifdef S_IRUSR
    MYNODE_DEFINE_CONSTANT(target, S_IRUSR);
#endif
    
#ifdef S_IWUSR
    MYNODE_DEFINE_CONSTANT(target, S_IWUSR);
#endif
    
#ifdef S_IXUSR
    MYNODE_DEFINE_CONSTANT(target, S_IXUSR);
#endif
    
#ifdef S_IRWXG
    MYNODE_DEFINE_CONSTANT(target, S_IRWXG);
#endif
    
#ifdef S_IRGRP
    MYNODE_DEFINE_CONSTANT(target, S_IRGRP);
#endif
    
#ifdef S_IWGRP
    MYNODE_DEFINE_CONSTANT(target, S_IWGRP);
#endif
    
#ifdef S_IXGRP
    MYNODE_DEFINE_CONSTANT(target, S_IXGRP);
#endif
    
#ifdef S_IRWXO
    MYNODE_DEFINE_CONSTANT(target, S_IRWXO);
#endif
    
#ifdef S_IROTH
    MYNODE_DEFINE_CONSTANT(target, S_IROTH);
#endif
    
#ifdef S_IWOTH
    MYNODE_DEFINE_CONSTANT(target, S_IWOTH);
#endif
    
#ifdef S_IXOTH
    MYNODE_DEFINE_CONSTANT(target, S_IXOTH);
#endif
    
#ifdef F_OK
    MYNODE_DEFINE_CONSTANT(target, F_OK);
#endif
    
#ifdef R_OK
    MYNODE_DEFINE_CONSTANT(target, R_OK);
#endif
    
#ifdef W_OK
    MYNODE_DEFINE_CONSTANT(target, W_OK);
#endif
    
#ifdef X_OK
    MYNODE_DEFINE_CONSTANT(target, X_OK);
#endif
}
    void DefineConstants(v8::Handle<v8::Object> target){
        DefineSystemConstants(target);
    }
}