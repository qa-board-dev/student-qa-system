//
// Created by 16198 on 3/4/2026.
//
#include "PostManager.h"
#include <vector>
#include <QJsonArray>
#include <QJsonObject>
#include <QJsonDocument>
#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QEventLoop>

using namespace std;

PostManager::PostManager(QObject *parent) : QObject(parent), networkManager(new QNetworkAccessManager(this)) {}

void PostManager::addPost(const Post& post) {
   posts.push_back(post);


}
vector<Post>& PostManager::getPost() {

   return posts;

}

void PostManager::save() {
 QJsonArray array;
   for(const Post &p : posts) {
      QJsonObject obj;
      obj["author"] = p.getAuthor();
      obj["content"] = p.getContent();

      QJsonArray answersArray;
      for (const Answer& ans : p.getAnswers()) {
         QJsonObject answerObject;
         answerObject["author"] = ans.author;
         answerObject["content"] = ans.content;
         answersArray.append(answerObject);
      }
      obj["answers"] = answersArray;
      array.append(obj);
   }
   QJsonDocument doc(array);

   QUrl url(firebaseURL);
   QNetworkRequest request(url);
   request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

   QNetworkReply *reply = networkManager->put(request, doc.toJson());

   connect(reply, &QNetworkReply::finished, this, [reply]() {
      if (reply->error() != QNetworkReply::NoError) {
         qWarning() << "Save failed: " << reply->errorString();
      }
      reply->deleteLater();
   });

}

void PostManager::load() {
   QUrl url(firebaseURL);
   QNetworkRequest request(url);

   QNetworkReply *reply = networkManager->get(request);

   QEventLoop loop;
   connect(reply, &QNetworkReply::finished, &loop, &QEventLoop::quit);
   loop.exec();

   if (reply->error() != QNetworkReply::NoError) {
      qWarning() << "load failed: " << reply->errorString();
      reply->deleteLater();
      return;
   }

   QJsonDocument doc = QJsonDocument::fromJson(reply->readAll());
   QJsonArray array = doc.array();
   posts.clear();
   for (const QJsonValue &val : array) {
      QJsonObject obj = val.toObject();
      QString author = obj["author"].toString();
      QString content = obj["content"].toString();

      posts.emplace_back(author,content);

      QJsonArray answersArray = obj["answers"].toArray();
      for (int j = 0; j < answersArray.size(); j++) {
         QJsonObject answerObject = answersArray[j].toObject();
         Answer ans;
         ans.author = answerObject["author"].toString();
         ans.content = answerObject["content"].toString();
         posts.back().addAnswer(ans);
      }
   }
   reply->deleteLater();
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
