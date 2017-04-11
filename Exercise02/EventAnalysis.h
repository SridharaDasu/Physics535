#ifndef EventAnalysis_H
#define EventAnalysis_H

#include <string>
#include <map>

using namespace std;

#include "Pythia.h"
using namespace Pythia8; 

class TH1F;
class TFile;

class EventAnalysis {
 public:
  EventAnalysis(string histFileName);
  //  EventAnalysis(string histFileName = "histograms.root");
  virtual ~EventAnalysis() {;}
  void processEvent(Event& event);
  void finalize();
 private:
  map<string, TH1F*> histograms;
  TFile* file;
};

#endif
