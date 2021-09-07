#ifndef PROCESSOR_H
#define PROCESSOR_H
#include<string>
class Processor{
 public:
  float Utilization();  // TODO: See src/processor.cpp
//System sys;
  // TODO: Declare any necessary private members
 private:
  std::string kUser;
  std::string kNice;
  std::string kSystem;
  std::string kIdle;
  std::string kIOwait;
  std::string kIRQ;
  std::string kSoftIRQ;
  std::string kSteal;
  std::string kGuest;
  std::string kGuestNice;
};


#endif