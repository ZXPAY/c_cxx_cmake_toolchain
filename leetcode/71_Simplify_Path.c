#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdint.h>
#include <string.h>
#include <assert.h>
#include <math.h>

// char test_path[] = "/home/a/../a/../"; // ans: /home
// char test_path[] = "/home//"; // ans: /home
// char test_path[] = "/home/danny/123/"; // ans: /home/danny/123
char test_path[] = "/home/../home/danny/123/"; // ans: /home/danny/123

/*
Given a string path, which is an absolute path (starting with a slash '/') to a file or directory in a Unix-style file system, convert it to the simplified canonical path.

In a Unix-style file system, a period '.' refers to the current directory, a double period '..' refers to the directory up a level, and any multiple consecutive slashes (i.e. '//') are treated as a single slash '/'. For this problem, any other format of periods such as '...' are treated as file/directory names.

The canonical path should have the following format:

The path starts with a single slash '/'.
Any two directories are separated by a single slash '/'.
The path does not end with a trailing '/'.
The path only contains the directories on the path from the root directory to the target file or directory (i.e., no period '.' or double period '..')
Return the simplified canonical path.
*/


/*
'//' -> '/'
'/../' -> '/'
'/a/../' -> '/'
*/

int get_location_length(char *pos) {
    int cnt = 0;
    while(pos[cnt] != '/' && pos[cnt] != '\0') {
        cnt++;
    }
    return cnt;
}

typedef struct _subpath_struct_t {
    char *subpath;
    int len;
} subpath_struct_t;

subpath_struct_t *sub_path(char *path, int l) {
    char *sub_p = malloc(sizeof(char)*l);
    memcpy(sub_p, path, sizeof(char)*l);
    subpath_struct_t *subpath_struct = malloc(sizeof(subpath_struct));
    subpath_struct->subpath = sub_p;
    subpath_struct->len = l;
    return subpath_struct;
}

char *simplifyPath(char *path) {
    int length = strlen(path);
    subpath_struct_t **pth = malloc(sizeof(subpath_struct_t **)*length);

    if(length <= 1) return path;
    
    int count = 0;
    int i_sub = 0;
    while(count < length) {
        int temp = get_location_length(&path[count]);
        if(temp != 0) {
            if(temp == 2 && path[count] == '.' && path[count+1] == '.') {
                if(i_sub == 0) {
                    path[0] = '/';
                }
                else {
                    i_sub--;
                    free(pth[i_sub]);
                }
            }
            else if(path[count] == '.' && temp == 1) {
                
            }
            else {
                pth[i_sub++] = sub_path(&path[count], temp);
                // printf("sub path: %s\n", pth[i_sub-1]->subpath);
            }
        }

        count += temp + 1;
    }

    int k = 1;
    
    for(int i=0;i<i_sub;i++) {
        // printf("%s\n", pth[i]->subpath);
        memcpy(&path[k], pth[i]->subpath, pth[i]->len*sizeof(char));
        free(pth[i]->subpath);

        k += pth[i]->len;
        path[k++] = '/';
    }
    if(i_sub == 0) {
        memset(path, 0, length);
        path[0] = '/';
    }
    else {
        path[k-1] = '\0';
    }
    
    free(pth);
    
    return path;
}

int main(int argc, char *argv[]) {
    // for(int i=0;i<argc;i++) {
    //     printf("arg[%d]: %s\n", i, argv[i]);
    // }

    printf("%s\n", test_path);

    char *path = simplifyPath(test_path);

    printf("%s\n", path);

}

