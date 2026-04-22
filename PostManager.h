//
// Created by 16198 on 3/4/2026.
//

#ifndef PROJECT_A1_POSTMANAGER_H
#define PROJECT_A1_POSTMANAGER_H

#include "Post.h"
#include <vector>
#include <QString>
#include <QObject>
#include <QNetworkAccessManager>

using namespace std;

class PostManager : public QObject {
    Q_OBJECT

public:
    explicit PostManager(QObject *parent = nullptr);

    void addPost(const Post& post);
    vector<Post>& getPost();
    void save();
    void load();
    vector<Post> getRelated(const Post &target);

private:
    vector<Post> posts;
    QString firebaseURL = "https://cse360-qa-default-rtdb.firebaseio.com/posts.json";
    QNetworkAccessManager *networkManager;
};


#endif //PROJECT_A1_POSTMANAGER_H