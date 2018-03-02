/*****************************************************************************
 * Project: RooFit                                                           *
 *                                                                           *
  * This code was autogenerated by RooClassFactory                            *
 *****************************************************************************/

#ifndef ROO_MOMENT_MORPH_FUNC
#define ROO_MOMENT_MORPH_FUNC

#include "RooAbsPdf.h"
#include "RooRealProxy.h"
#include "RooCategoryProxy.h"
#include "RooAbsReal.h"
#include "RooAbsCategory.h"
#include "RooSetProxy.h"
#include "RooListProxy.h"
#include "RooArgList.h"

#include "TMatrixD.h"
#include "TVectorD.h"

#include <vector>
#include <string>
class RooChangeTracker;

class RooMomentMorphFunc : public RooAbsReal {
public:
   enum Setting { Linear, NonLinear, NonLinearPosFractions, NonLinearLinFractions, SineLinear };

   RooMomentMorphFunc();

   RooMomentMorphFunc(const char *name, const char *title, RooAbsReal &_m, const RooArgList &varList,
                      const RooArgList &pdfList, const RooArgList &mrefList, Setting setting = NonLinearPosFractions);
   RooMomentMorphFunc(const char *name, const char *title, RooAbsReal &_m, const RooArgList &varList,
                      const RooArgList &pdfList, const TVectorD &mrefpoints, Setting setting = NonLinearPosFractions);
   RooMomentMorphFunc(const RooMomentMorphFunc &other, const char *name = 0);
   virtual TObject *clone(const char *newname) const { return new RooMomentMorphFunc(*this, newname); }
   virtual ~RooMomentMorphFunc();

   void setMode(const Setting &setting) { _setting = setting; }

   void useHorizontalMorphing(bool val) { _useHorizMorph = val; }

   virtual Bool_t selfNormalized() const
   {
      // P.d.f is self normalized
      return kTRUE;
   }

   virtual Double_t getVal(const RooArgSet *set = 0) const;
   RooAbsReal *sumFunc(const RooArgSet *nset);
   const RooAbsReal *sumFunc(const RooArgSet *nset) const;

   virtual std::list<Double_t> *plotSamplingHint(RooAbsRealLValue &obs, Double_t xlo, Double_t xhi) const;
   virtual std::list<Double_t> *binBoundaries(RooAbsRealLValue & /*obs*/, Double_t /*xlo*/, Double_t /*xhi*/) const;
   Bool_t isBinnedDistribution(const RooArgSet &obs) const;

protected:
   class CacheElem : public RooAbsCacheElement {
   public:
      CacheElem(RooAbsReal &sumFunc, RooChangeTracker &tracker, const RooArgList &flist)
         : _sumFunc(&sumFunc), _tracker(&tracker)
      {
         _frac.add(flist);
      };
      void operModeHook(RooAbsArg::OperMode){};
      virtual ~CacheElem();
      virtual RooArgList containedArgs(Action);
      RooAbsReal *_sumFunc;
      RooChangeTracker *_tracker;
      RooArgList _frac;

      RooRealVar *frac(Int_t i);
      const RooRealVar *frac(Int_t i) const;
      void calculateFractions(const RooMomentMorphFunc &self, Bool_t verbose = kTRUE) const;
   };
   mutable RooObjCacheManager _cacheMgr; //! The cache manager
   mutable RooArgSet *_curNormSet;       //! Current normalization set

   friend class CacheElem; // Cache needs to be able to clear _norm pointer

   Double_t evaluate() const;

   void initialize();
   CacheElem *getCache(const RooArgSet *nset) const;

   inline Int_t ij(const Int_t &i, const Int_t &j) const { return (i * _varList.getSize() + j); }
   int idxmin(const double &m) const;
   int idxmax(const double &m) const;

   RooRealProxy m;
   RooSetProxy _varList;
   RooListProxy _pdfList;
   mutable TVectorD *_mref;

   TIterator *_varItr;   //! do not persist
   TIterator *_pdfItr;   //!
   mutable TMatrixD *_M; //

   Setting _setting;

   bool _useHorizMorph;

   ClassDef(RooMomentMorphFunc, 3) // Your description goes here...
};

#endif
