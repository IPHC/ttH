#ifndef Tau_H
#define Tau_H

#include "TObject.h"
#include "TLorentzVector.h"
#include "Base.h"

class Tau : public Base
{
 public:
 
   int   id;
   
   Tau();
   virtual ~Tau();
   
   ClassDef(Tau,1)
};

#endif
