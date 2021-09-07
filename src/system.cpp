#include <unistd.h>
#include <cstddef>
#include <set>
#include <string>
#include <vector>

#include "linux_parser.h"
#include "process.h"
#include "processor.h"
#include "system.h"

using std::set;
using std::size_t;
using std::string;
using std::vector;

// TODO: Return the system's CPU
Processor& System::Cpu() { 
  return cpu_; 
}

// TODO: Return a container composed of the system's processes
vector<Process>& System::Processes() {
  const vector<int>& pids = LinuxParser::Pids();
  for(const int& pid: pids){
    Process process(pid); 
    processes_.push_back(process); 
  }
  return processes_;
}

// TODO: Return the system's kernel identifier (string)
std::string System::Kernel() {
  kernel_=LinuxParser::Kernel();
  return kernel_; }

// TODO: Return the system's memory utilization
float System::MemoryUtilization() { 
  mem_=LinuxParser::MemoryUtilization();
  return mem_; 
}

// TODO: Return the operating system name
std::string System::OperatingSystem() { 
  os_=LinuxParser::OperatingSystem();
  return os_; }

// TODO: Return the number of processes actively running on the systemi
int System::RunningProcesses() { 
  count_=LinuxParser::RunningProcesses();
  return count_;
  }

// TODO: Return the total number of processes on the system
int System::TotalProcesses() { 
  totproc_=LinuxParser::TotalProcesses();
  return totproc_; }

// TODO: Return the number of seconds since the system started running
long int System::UpTime() { 
uptime_=LinuxParser::UpTime();
 return uptime_;
}
