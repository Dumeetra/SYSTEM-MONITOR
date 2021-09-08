#include <dirent.h>
#include <unistd.h>
#include <string>
#include <vector>
#include<iostream>
#include <regex>
#include "linux_parser.h"
#define sysconf( _SC_CLK_TCK )  100

using std::stof;
using std::string;
using std::to_string;
using std::vector;

// DONE: An example of how to read data from the filesystem
string LinuxParser::OperatingSystem() {
  string line;
  string key;
  string value;
  std::ifstream filestream(kOSPath);
  if (filestream.is_open()) {
    while (std::getline(filestream, line)) {
      std::replace(line.begin(), line.end(), ' ', '_');
      std::replace(line.begin(), line.end(), '=', ' ');
      std::replace(line.begin(), line.end(), '"', ' ');
      std::istringstream linestream(line);
      while (linestream >> key >> value) {
        if (key == "PRETTY_NAME") {
          std::replace(value.begin(), value.end(), '_', ' ');
          return value;
        }
      }
    }
  }
  return value;
}

// DONE: An example of how to read data from the filesystem
string LinuxParser::Kernel() {
  string os, version, kernel;
  string line;
  std::ifstream stream(kProcDirectory + kVersionFilename);
  if (stream.is_open()) {
    std::getline(stream, line);
    std::istringstream linestream(line);
    linestream >> os >> version >> kernel;
  }
  return kernel;
}

// BONUS: Update this to use std::filesystem
vector<int> LinuxParser::Pids() {
  vector<int> pids;
  DIR* directory = opendir(kProcDirectory.c_str());
  struct dirent* file;
  while ((file = readdir(directory)) != nullptr) {
    // Is this a directory?
    if (file->d_type == DT_DIR) {
      // Is every character of the name a digit?
      string filename(file->d_name);
      if (std::all_of(filename.begin(), filename.end(), isdigit)) {
        int pid = stoi(filename);
        pids.push_back(pid);
      }
    }
  }
  closedir(directory);
  return pids;
}

// TODO: Read and return the system memory utilization
float LinuxParser::MemoryUtilization() { 
 string line, key,unit;
 float mem;
    int Mtot, Mfree, value;
   
    std::ifstream filestream(kProcDirectory + kMeminfoFilename);
    if (filestream.is_open()) {
        while (std::getline(filestream, line)) {
            std::istringstream linestream(line);
           linestream >> key >> value>>unit;
                if (key == "MemTotal:") {
                     Mtot=value;
                }else if (key == "MemFree:") {
                     Mfree=value;
                }
        }
    }
  
   mem=(float)(Mtot-Mfree)/(float)(Mtot);
   return mem;
}

// TODO: Read and return the system uptime
  long int LinuxParser::UpTime() {
   string line, key, value;
    long int uptime;
    std::ifstream filestream(kProcDirectory + kUptimeFilename);
    if (filestream.is_open()) {
        if (std::getline(filestream, line)) {
            std::istringstream linestream(line);
            if (linestream >> key >> value) {
                uptime = stol(key);

            }
        }
    }
    return uptime;
}

// TODO: Read and return the number of jiffies for the system
long LinuxParser::Jiffies() { 
  long jiffies = UpTime() *sysconf( _SC_CLK_TCK );
    return jiffies;
}

// TODO: Read and return the number of active jiffies for a PID
// REMOVE: [[maybe_unused]] once you define the function
long LinuxParser::ActiveJiffies(int pid)
{ 
    string line, value;
    long jiffies{ 0 };
    int i{ 0 };
    std::ifstream filestream(kProcDirectory+ to_string(pid)+kStatFilename);
    if (filestream.is_open()) {
        while (std::getline(filestream, line)) {
            std::istringstream linestream(line);
            while (linestream >> value) {
                i++;
                if (i > 13 && i < 18) {
                    jiffies += stoi(value);
                }
                else if (i>18) {
                    
                  break;
                }
            }
        }
    }
    return jiffies;
}



// TODO: Read and return the number of active jiffies for the system
long LinuxParser::ActiveJiffies() { 
  string line;
    long jiffies{ 0 };
    string key;
    int count{ 0 };

    std::ifstream filestream(kProcDirectory+kStatFilename);
    if (filestream.is_open()) {
        if (std::getline(filestream, line)) {
            std::istringstream linestream(line);
            while (linestream >> key) {
                count++;
                if (count > 1) {
                    jiffies += stoi(key);
                }
            }
        }
    }
    return jiffies;
}

// TODO: Read and return the number of idle jiffies for the system
long LinuxParser::IdleJiffies() { 
        string line, value;
        long idle{ 0 };
        int i{ 0 };
        std::ifstream filestream(kProcDirectory+kStatFilename);
        if (filestream.is_open()) {
            while (std::getline(filestream, line)) {
                std::istringstream linestream(line);
                while (linestream >> value) {
                    i++;
                    if (i > 3 && i < 6) {
                        idle += stoi(value);
                    }
                    else if (i >= 6) {
                        break;
                    }
                }
            }
        }
        return idle;
     }

// TODO: Read and return CPU utilization
string LinuxParser::CpuUtilization(int  pid) {  
float total_time=ActiveJiffies(pid);
float seconds=UpTime()-UpTime(pid);
string cpu_usage = to_string(total_time/ seconds);
return cpu_usage;
}

// TODO: Read and return the total number of processes
int LinuxParser::TotalProcesses() { 
 return Pids().size();
}

// TODO: Read and return the number of running processes
int LinuxParser::RunningProcesses() {
string line;
  string rng1, rng2, rng3;
        int count{ 0 };
        for (int pid : Pids()) {
            string a = kProcDirectory +  to_string(pid) + kStatFilename;
           std::ifstream filestream(a);

            if (filestream.is_open()) {
                std::getline(filestream, line);
                std::istringstream linestream(line);
                linestream >> rng1 >> rng2 >> rng3;

                if (rng3=="R" ) {
                    count++;
                }
            }
        }
        return count; 
}

// TODO: Read and return the command associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Command(int pid) {
  string line, value, key;
           std::ifstream filestream(kProcDirectory + to_string(pid) + kCmdlineFilename);
          if (filestream.is_open()) {      
            std::getline(filestream, line);
                  
       		 }
  return line;
}

// TODO: Read and return the memory used by a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Ram(int pid) { 
        string line;
        string key;
        string value;
        string a = kProcDirectory + to_string(pid) + kStatusFilename;

        std::ifstream filestream(a);
        if (filestream.is_open()) {
            while (std::getline(filestream, line)) {
                std::istringstream linestream(line);
                linestream >> key >> value;
                    if (key == "VmSize:") {
                        break;
                    }
            }   
        }
        return value.substr(0,value.size()-3);//string(); 
    }                     
                                           

// TODO: Read and return the user ID associated with a process
// REMOVE: [[maybe_unused]] once you define the function
string LinuxParser::Uid(int pid) {
        string line;
        string key;
        string value, retvalue;
        string a = kProcDirectory + to_string(pid) + kStatusFilename;

        std::ifstream filestream(a);
        if (filestream.is_open()) {
            while (std::getline(filestream, line)) {
                std::istringstream linestream(line);
                while (linestream >> key >> value) {
                    if (key == "Uid:") {
					retvalue=value;
                        break;
                    }
                }
            }
        }
        return retvalue;
}
 
// TODO: Read and return the user associated with a process
// REMOVE: [[maybe_unused]] once you define the function
 string LinuxParser::User(int pid) {
   string line, box, mybox{0};
   string val=Uid(pid);
    string key;
    bool true1{ false };
    bool true2{ false };
    string a = kPasswordPath;

    std::ifstream filestream(a);
    if (filestream.is_open()) {
        while (std::getline(filestream, line,':')) {
          std::istringstream linestream(line);
            while (linestream >> key) {
                if (key == "x") {
                    true1 = true;
                }
                else if (key == val && true1 == true) {
                    true2 = true;
                    true1 = false;
                }
                else if (key == val && true2 == true) {
                  mybox=box;
                    break;
                }else{
                    box = key;
                    true1 = false;
                    true2 = false;
                }
            }
        }
    }
    return mybox;
}

// TODO: Read and return the uptime of a process
// REMOVE: [[maybe_unused]] once you define the function
long LinuxParser::UpTime(int pid) {
                 string line;
        long box;
        string key;
        int count{ 0 };
        string a = kProcDirectory + to_string(pid) + kStatFilename;

        std::ifstream filestream(a);
        if (filestream.is_open()) {
            while (std::getline(filestream, line, ' ')) {
                std::istringstream linestream(line);
                while (linestream >> key) {
                    count++;
                    if (count == 22) {
                        box = stoi(key);
                        break;
                    }
                }
            }
        }
        return box/sysconf( _SC_CLK_TCK );                                  
 }
