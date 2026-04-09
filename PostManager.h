//
// Created by 16198 on 3/4/2026.
//

#ifndef PROJECT_A1_POSTMANAGER_H
#define PROJECT_A1_POSTMANAGER_H
#include "Post.h"
#include <vector>
#include <QString>
using namespace std;

class PostManager {
public:
    void addPost(const Post& post);
    vector<Post>& getPost();
    void save();
    void load();
    vector<Post> getRelated(const Post &target);

private:
    vector<Post> posts;
    QString filepath = "posts.json";

};


#endif //PROJECT_A1_POSTMANAGER_H