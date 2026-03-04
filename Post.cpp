//
// Created by 16198 on 2/25/2026.
//

#include "Post.h"
#include <iostream>
#include <string>
#include <stdexcept>
using namespace std;

 Post::Post(const string& author, const string& content): author(author), content(content), approved(false) {
  if (author.empty()) {
      throw invalid_argument("Author cannot be empty");
  }
     if (content.empty()) {
      throw invalid_argument("Post content cannot be empty");
  }
}
string Post::getAuthor() const{
    return author;
}
string Post::getContent() const{
    return content;
}
bool Post::isApproved() const {
     return approved;
 }
void Post::approve() {
     approved = true;
 }
