#include "processor.h"
#include <fstream>
#include<sstream>
#include <string>
#include <cmath>
#define sysconf( _SC_CLK_TCK ) 100

using std::string;
using std::to_string;
// TODO: Return the aggregate CPU utilization
float Processor::Utilization() { 
  string line1, line2;
    int idle, nonidle, total;
    float percent;
    int k, k1{ 0 };
    string ans;
    string a = "/proc/stat";
    std::ifstream filestream1(a); 
    std::getline(filestream1, line2);
    k = line2.size();
    if (filestream1.is_open()) {
    
      for(int cnt=0;cnt<10;cnt++){
          if (k > k1) {
              if (k1 == 0) {
                  k1 = line2.find(' ') + 1;
                  
              }
              else {
                  k1 = line2.find(' ');
              }
              switch (cnt) {
              case 0:
                  ans = line2.substr(0, k1);
              case 1:
                 kUser = line2.substr(0, k1);
                  ans = kUser;
              case 2:
                kNice = line2.substr(0, k1);
                  ans = kNice;
              case 3:
               kSystem = line2.substr(0, k1);
                  ans = kSystem;
              case 4:
                  kIdle = line2.substr(0, k1);
                  ans = kIdle;
              case 5:
                  kIOwait = line2.substr(0, k1);
                  ans = kIOwait;
              case 6:
                  kIRQ = line2.substr(0, k1);
                  ans = kIRQ;
              case 7:
                  kSoftIRQ =line2.substr(0, k1);
                  ans = kSoftIRQ;
              case 8:
                  kSteal = line2.substr(0, k1);
                  ans = kSteal;
                  break;
              }
              //ans = line2.substr(0, k1);
              line2.replace(line2.begin(), line2.begin() + k1, k1, ' ');
              line2 = line2.substr(k1 + 1, k - k1);
           
          }
            
          
        }
        
    }
    idle = stoi(kIdle) + stoi(kIOwait);
    nonidle = stoi(kUser) + stoi(kNice) + stoi(kSystem) + stoi(kIRQ) + stoi(kSoftIRQ) + stoi(kSteal);
    total = idle + nonidle;
    percent =trunc(100*(float)nonidle /(float)total)/100;
    return percent;
}