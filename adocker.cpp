/*
 * main.cpp
 * Copyright (C) 2016 truong-d <truong-d@truongd-ThinkPad-X1-Carbon-3rd>
 *
 * Distributed under terms of the MIT license.
 */

#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <string.h>
#include <cstdlib>
#include <unistd.h>

void split(const std::string &s, const char* delim, std::vector<std::string> & v){
    char * dup = strdup(s.c_str());
    char * token = strtok(dup, delim);
    while(token != NULL){
        v.push_back(std::string(token));
        token = strtok(NULL, delim);
    }
}


std::string getHostPath(std::string comp){
  std::vector<std::string> tmp;
  /* The docker mount command has 2 forms: "-v /host_path" or "-v /host_path:/container_path"
   * so we will split the command based on ":" and take the first item
   */
  split(comp, ":", tmp);
  std::string hostPath = tmp[0];
  return hostPath;
}

bool hasAccess(const char* pathname, int mode){
  std::string newPath(pathname);
  std::string hostPath = getHostPath(newPath);
  if (access(hostPath.c_str(), mode) == 0)
    return true;
  return false;
}

bool mountAsRO(std::string comp){
  int path_length = comp.size();
  if (path_length < 3)
    return false;

  std::string mode = comp.substr(path_length - 3, path_length);
  if (mode == ":ro"){
    return true;
  }
  return false;
}

bool check_validity(const char* comp){
  std::string tmp(comp);
  if (!hasAccess(comp, W_OK)){
    if (hasAccess(comp, R_OK)){
      if (mountAsRO(tmp)){
        return true;
      }else{
        std::cerr << "You only have read permission on \"" << tmp << "\"" << " please mount it as read-only volume" <<  std::endl;
        return false;
      }
    }
    std::cerr << "You don't have any permission on \"" << tmp << "\"" <<  std::endl;
    return false;
  }
  return true;
}

int main(int argc, char *argv[])
{
  std::string command;
  for (int i = 1; i < argc; ++i) {
    char* comp = argv[i];
    if (strcmp(comp, "-v") == 0) {  // docker share volume command looks like this: docker run -v /host_path:/container_path image
      bool code = check_validity(argv[i + 1]);
      if (! code){
        return 1;
      }
    }
    command += std::string(comp) + " ";
  }
  command = "docker " + command;
  system(command.c_str());
  return 0;
}
