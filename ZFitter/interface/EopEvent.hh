#ifndef Eopevent_hh
#define Eopevent_hh



class EopEvent{//Non ha metodi, solo membri pubblici
  //come trattare il caso double electron?
 public:
  inline ~EopEvent(){
    if(smearings_ele1!=NULL) delete smearings_ele1;
  }
  float energy_ele1;
  float momentum_ele1;
  float EoverP;
  float weight;
  float *smearings_ele1;
  
  EopEvent(): smearings_ele1(NULL){};
};

typedef std::vector<EopEvent> eop_events_t;
//un vettore di EopEvent si chiama eop_events_t
#endif

