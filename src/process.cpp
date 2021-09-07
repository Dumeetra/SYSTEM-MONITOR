#include <unistd.h>
#include <cctype>
#include <sstream>
#include <string>
#include <vector>

#include "linux_parser.h"
#include "process.h"
using std::string;
using std::to_string;
using std::vector;

int Process::Pid(){
  return pid_;
}

// TODO: Return this process's CPU utilization
float Process::CpuUtilization() { 
return stof(LinuxParser::CpuUtilization(this->pid_));
}
// TODO: Return the command that generated this process
string Process::Command() { 
  return LinuxParser::Command(this->pid_); 
}

// TODO: Return this process's memory utilization
string Process::Ram() { 
  return  LinuxParser::Ram(this->pid_); 
}

string Process::Uid() { 
  return  LinuxParser::Uid(this->pid_); 
}

// TODO: Return the user (name) that generated this process
string Process::User() { 
  
  return  LinuxParser::User(this->pid_); 
}

// TODO: Return the age of this process (in seconds)
long int Process::UpTime() { 
  
  return LinuxParser::UpTime(this->pid_); 
}

// TODO: Overload the "less than" comparison operator for Process objects
// REMOVE: [[maybe_unused]] once you define the function
bool Process::operator<(Process const& a) const {
  return true; 
}