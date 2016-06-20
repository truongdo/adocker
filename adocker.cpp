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

  std::cerr << "You don't have write permission on \"" << hostPath << "\"" <<  std::endl;
  return false;
}

bool check_validity(const char* comp){
  std::string tmp(comp);
  if (!hasAccess(comp, W_OK)){
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
  command = "dkr " + command;
  system(command.c_str());
  return 0;
}
