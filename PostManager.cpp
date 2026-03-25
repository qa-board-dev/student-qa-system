//
// Created by 16198 on 3/4/2026.
//
#include "PostManager.h"
#include <vector>
#include <QFile>
#include <QJSonArray>
#include <QJSonArray>
#include <QJSonObject>
#include <QJSonDocument>

using namespace std;

void PostManager::addPost(const Post& post) {
   posts.push_back(post);


}
vector<Post>& PostManager::getPost() {

   return posts;

}

void PostManager::save()
   {
 QJsonArray array;
   for(const Post &p : posts) {
      QJsonObject obj;
      obj["author"] = p.getAuthor();
      obj["content"] = p.getContent();
      array.append(obj);
   }
   QJsonDocument doc(array);
  QFile file(filepath);
   if (!file.open(QIODevice::WriteOnly)) return;

   file.write(doc.toJson());
   file.close();
}

void PostManager::load() {
QFile file(filepath);
   if (!file.exists()) return;
   if (!file.open(QIODevice::ReadOnly)) return;

   QByteArray data = file.readAll();
   QJsonDocument doc = QJsonDocument::fromJson(data);
   QJsonArray array = doc.array();
   posts.clear();
   for (const QJsonValue &val : array) {
      QJsonObject obj = val.toObject();
      QString author = obj["author"].toString();
      QString content = obj["content"].toString();

      posts.emplace_back(author,content);
   }
   file.close();
}
vector<Post> PostManager::getRelated(const Post &target) { //keyword search
   vector<Post> result;
   for (const Post &p : posts) {
      if (p.getContent()==target.getContent())
         continue;

      int matches = 0;
      for (const QString &word : target.getKeywords()) {
         if (p.getKeywords().contains(word)) {
            matches++;
         }
      }
      if (matches >= 1) {
         result.push_back(p);
      }
   }
      return result;
}
