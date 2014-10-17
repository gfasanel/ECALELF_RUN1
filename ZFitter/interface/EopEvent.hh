#ifndef Eopevent_hh
#define Eopevent_hh



class EopEvent{//Non ha metodi, solo membri pubblici
  //come trattare il caso double electron?
 public:
  float energy_ele1;
  float momentum_ele1;
  float EoverP;
  float weight;
  float *smearings_ele1;
  
};

typedef std::vector<EopEvent> eop_events_t;
//un vettore di EopEvent si chiama eop_events_t
#endif

