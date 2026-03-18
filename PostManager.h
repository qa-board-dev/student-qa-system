//
// Created by 16198 on 3/4/2026.
//

#ifndef PROJECT_A1_POSTMANAGER_H
#define PROJECT_A1_POSTMANAGER_H
#include "Post.h"
#include <vector>
using namespace std;

class PostManager {
private:
    vector<Post> posts;
public:
    void addPost(const Post& post);
    vector<Post>& getPost();

};


#endif //PROJECT_A1_POSTMANAGER_H