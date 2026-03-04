//
// Created by 16198 on 2/25/2026.
//

#ifndef USER_UI_POST_H
#define USER_UI_POST_H
#include <iostream>
#include <string>
#include <stdexcept>
using namespace std;


class Post {
private:
    string author;
    string content;
    bool approved;
public:
    Post(const string& author, const string &content);
    string getAuthor() const;
    string getContent() const;
    bool isApproved() const;
    void approve();
};


#endif //USER_UI_DISCUSSIONBOARDTEST_H