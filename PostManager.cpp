//
// Created by 16198 on 3/4/2026.
//
#include "PostManager.h"
#include <vector>
using namespace std;

void PostManager::addPost(const Post& post) {
   posts.push_back(post);


}
vector<Post>& PostManager::getPost() {

   return posts;

}

