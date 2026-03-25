//
// Created by 16198 on 2/25/2026.
//

#include "Post.h"
#include <iostream>
#include <string>
#include <stdexcept>
using namespace std;

 Post::Post(const QString& author, const QString& content): author(author), content(content), approved(false) {
  if (author.isEmpty()) { //QString change
      throw invalid_argument("Author cannot be empty");
  }
     if (content.isEmpty()) { //QString change
      throw invalid_argument("Post content cannot be empty");
  }
     generateKeywords();// keyword search
}
QString Post::getAuthor() const{
    return author;
}
QString Post::getContent() const{
    return content;
}
bool Post::isApproved() const {
     return approved;
 }
void Post::approve() {
     approved = true;
 }
QStringList Post::getKeywords() const { //keyword search
     return keywords;
 }
void Post::generateKeywords() { //keyword search
     QString text = (author +" "+ content).toLower();
     QStringList words = text.split(" ", Qt::SkipEmptyParts);

     QStringList fillerWords = {
         "how","do","i","the","is","a","to","not","what","when","why"
     };
     keywords.clear();

     for (const QString &w : words) {
         if (!fillerWords.contains(w)) {
             keywords.append(w);
         }
     }
 }

void Post::addAnswer(const Answer &ans) {
    answers.push_back(ans);
}

QVector<Answer> Post::getAnswers() const {
     return answers;
 }

