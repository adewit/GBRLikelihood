/*****************************************************************************
 * Project: RooFit                                                           *
 * Package: RooFitModels                                                     *
 *    File: $Id: HGGRooPdfs.h,v 1.1 2012/02/10 15:10:48 gpetrucc Exp $
 * Authors:                                                                  *
 *   WV, Wouter Verkerke, UC Santa Barbara, verkerke@slac.stanford.edu       *
 *   DK, David Kirkby,    UC Irvine,         dkirkby@uci.edu                 *
 *                                                                           *
 * Copyright (c) 2000-2005, Regents of the University of California          *
 *                          and Stanford University. All rights reserved.    *
 *                                                                           *
 * Redistribution and use in source and binary forms,                        *
 * with or without modification, are permitted according to the terms        *
 * listed in LICENSE (http://roofit.sourceforge.net/license.txt)             *
 *****************************************************************************/
#ifndef ROO_HYBRIDBDTAUTOPDF
#define ROO_HYBRIDBDTAUTOPDF

#include "RooAbsPdf.h"
#include "RooRealProxy.h"
#include "RooListProxy.h"
#include "TMatrixDSym.h"
#include "../interface/HybridGBREvent.h"




class RooRealVar;
class RooAbsReal;
class RooArgSet;
class HybridGBRForest;
class HybridGBRTree;
class TNtuple;

class RooTreeConvert {
  
public:
  RooTreeConvert() {}
  virtual ~RooTreeConvert() {}
  
  static RooDataSet *CreateDataSet(std::string name, TTree *tree, std::vector<std::string> vars, std::string weight);
  static RooDataSet *CreateDataSet(std::string name, TTree *tree, RooArgList &vars, RooRealVar &weight);
  
  
private:
  ClassDef(RooTreeConvert,1)  
  
};



class RooRealConstraint : public RooAbsReal {
 
public:
  RooRealConstraint() : _low(0.), _high(1.) {}
  RooRealConstraint(const char *name, const char *title, RooAbsReal &real, double low, double high);
  RooRealConstraint(const RooRealConstraint &other, const char* name=0);
  virtual ~RooRealConstraint() {}
  
  virtual TObject* clone(const char* newname) const { return new RooRealConstraint(*this,newname); }
  
  
protected:
  Double_t evaluate() const;
  
  RooRealProxy _real;
  Double_t     _low;
  Double_t     _high;
  Double_t     _scale;
  Double_t     _offset;
  
  
private:
  ClassDef(RooRealConstraint,1)    
  
};


class RooPowerLaw : public RooAbsPdf {
  
public:
  RooPowerLaw() {}
  RooPowerLaw(const char *name, const char *title, RooAbsReal &x, RooAbsReal &p);
  RooPowerLaw(const RooPowerLaw& other, const char* name=0);
  virtual ~RooPowerLaw() {}
  
  virtual TObject* clone(const char* newname) const { return new RooPowerLaw(*this,newname); }
  
  //virtual Bool_t selfNormalized() const { return kTRUE; }
  
  //virtual ExtendMode extendMode() const { return CanBeExtended ; }  

//   virtual Double_t expectedEvents(const RooArgSet* nset) const { return _norm.arg().getVal(); }
//   virtual Double_t expectedEvents(const RooArgSet& nset) const { return _norm.arg().getVal(); }  
  
  virtual Int_t getAnalyticalIntegral(RooArgSet& allVars, RooArgSet& analVars, const char* rangeName = 0) const;
  virtual Double_t analyticalIntegral(Int_t code, const char* rangeName = 0) const;
  
protected:
  
  Double_t evaluate() const;
  
  
  RooRealProxy _x;
  RooRealProxy _p;  
 
  
private:
  ClassDef(RooPowerLaw,1)  
  
};

class RooCondAddPdf : public RooAbsPdf {
  
public:
  RooCondAddPdf() {}
  RooCondAddPdf(const char *name, const char *title, const RooArgList &pdfs, const RooArgList &coeffs);
  RooCondAddPdf(const RooCondAddPdf& other, const char* name=0);
  virtual ~RooCondAddPdf() {}
  
  virtual TObject* clone(const char* newname) const { return new RooCondAddPdf(*this,newname); }
  
  virtual Bool_t selfNormalized() const { return kTRUE; }
  
  //virtual ExtendMode extendMode() const { return CanBeExtended ; }  

//   virtual Double_t expectedEvents(const RooArgSet* nset) const { return _norm.arg().getVal(); }
//   virtual Double_t expectedEvents(const RooArgSet& nset) const { return _norm.arg().getVal(); }  
  
  virtual Int_t getAnalyticalIntegral(RooArgSet& allVars, RooArgSet& analVars, const char* rangeName = 0) const;
  virtual Double_t analyticalIntegral(Int_t code, const char* rangeName = 0) const;
  
protected:
  
  Double_t evaluate() const;
  
  
  RooListProxy _pdfs;
  RooListProxy _coeffs;  
  //RooRealProxy _norm;
  bool _selfnorm;
  
private:
  ClassDef(RooCondAddPdf,1)  
  
};

class RooPdfAddReal : public RooAbsReal {
  
public:
  RooPdfAddReal() {}
  RooPdfAddReal(const char *name, const char *title, const RooArgList &pdfs, const RooArgList &coeffs);
  RooPdfAddReal(const RooPdfAddReal& other, const char* name=0);
  virtual ~RooPdfAddReal() {}
  
  virtual TObject* clone(const char* newname) const { return new RooPdfAddReal(*this,newname); }
  
  virtual Int_t getAnalyticalIntegral(RooArgSet& allVars, RooArgSet& analVars, const char* rangeName = 0) const;
  virtual Double_t analyticalIntegral(Int_t code, const char* rangeName = 0) const;
  
protected:
  
  Double_t evaluate() const;
  
  
  RooListProxy _pdfs;
  RooListProxy _coeffs;  
  //RooRealProxy _norm;
  
private:
  ClassDef(RooPdfAddReal,1)  
  
};

class RooGBRFunction : public RooAbsReal {
 
public:
  RooGBRFunction() {}
  RooGBRFunction(const char *name, const char *title, const RooArgList &vars, int ntargets);
  RooGBRFunction(const RooGBRFunction& other, const char* name=0);
  virtual ~RooGBRFunction();
  
  virtual TObject* clone(const char* newname) const { return new RooGBRFunction(*this,newname); }
  
  
  float GetResponse(int itgt) const;
  
  const RooArgList &Vars() const { return _vars; }
  
  
  HybridGBRForest *Forest() { return _forest; }
  void SetForest(HybridGBRForest *forest);
  
protected:
  virtual Double_t evaluate() const { return 0.; }
  
  
  RooListProxy _vars;
  HybridGBRForest *_forest;
  mutable std::vector<float> _eval;
  
private:
  ClassDef(RooGBRFunction,1)

  
  
};

class RooGBRTarget : public RooAbsReal {
  
public:
  RooGBRTarget() {}
  RooGBRTarget(const char *name, const char *title, RooGBRFunction &func, int itgt, RooRealVar &var);
  RooGBRTarget(const RooGBRTarget& other, const char* name=0);
  
  virtual TObject* clone(const char* newname) const { return new RooGBRTarget(*this,newname); }
  
  void SetUseFunc(bool b);
  
  RooRealVar *Var() { return (RooRealVar*)(&_var.arg()); }
  int Index() const { return _itgt; }
  
protected:
  virtual Double_t evaluate() const { return _usefunc ? static_cast<RooGBRFunction*>(_func.absArg())->GetResponse(_itgt) : _var.arg().getVal(); }
  //virtual Double_t evaluate() const { return _var.arg().getVal(); }
  
  RooArgProxy _func;
  int _itgt;
  RooRealProxy _var;
  bool _usefunc;

  
private:
    ClassDef(RooGBRTarget,1)
  
  
  
};

class RooHybridBDTAutoPdf : public TNamed {
public:
  
  //RooHybridBDTAutoPdf() {} ;
  RooHybridBDTAutoPdf(const char *name, const char *title, RooGBRFunction &func, const RooArgList &tgtvars, RooAbsReal &n0, RooRealVar &r, const std::vector<RooAbsData*> &data, const std::vector<RooAbsReal*> &pdfs);


  
  void AddInputVar(std::string var)    { fInputVars.push_back(var); }
  void SetTargetVar(std::string var)   { fTargetVar = var;          }
  //void SetTree(TTree *tree)            { fTree = tree;              }
  //void AddTree(TTree *tree, double w=1.0) { fTrees.push_back(tree); fTreeWeights.push_back(w); }
  void SetTrainingCut(std::string cut) { fTrainingCut = cut;        }
  void SetMinEvents(int n)             { fMinEvents = n;            }
  void SetShrinkage(double x)          { fShrinkage = x;            }
  void SetMinCutSignificance(double x); //  { fMinCutSignificance = x*x/2.0; }
  void SetTransitionQuantile(float x)  { fTransitionQuantile = x;   }
  void SetMinWeights(const std::vector<double> &minweights) { fMinWeights = minweights; }
  void SetMaxDepth(int depth) { fMaxDepth = depth; } 
 
  const HybridGBRForest *TrainForest(int ntrees, bool reuseforest = false);  
  
  void fitWithMinosFast();
  void fitWithMinos();
  
  double DLdR() const { return fdLdR; }
  
  TNtuple *ResTree() { return fResTree; } 
  
  TGraph *DrvGraph() { return fDrvGraph; }
  TGraph *DrvGraphSmooth() { return fDrvGraphSmooth; }
  TGraph *GraphDelta() { return fGraphDelta; }
  
  double RMin() const { return fRMin; }
  double RHigh() const { return fRHigh; }
  double RLow() const { return fRLow; }
  
protected:


  void BuildQuantiles(int nvars, double sumw);
  void UpdateTargets(int nvars, double sumw, int itree);
  void FillDerivatives();
  
  void TrainTree(const std::vector<HybridGBREvent*> &evts, double sumwtotal, HybridGBRTree &tree, int nvars, double transition, int depth, std::vector<std::pair<float,float> > limits, int tgtidx=-1);      
  void BuildLeaf(const std::vector<HybridGBREvent*> &evts, HybridGBRTree &tree, int tgtidx);

  //void FitResponses(const std::vector<HybridGBREvent*> &evts, double sumwtotal, HybridGBRTree &tree);
  void FitResponses(HybridGBRForest *forest);  
  
  TMatrixD vmultT(const TVectorD &v, const TVectorD &vT) const;
  double vmult(const TVectorD &vT, const TVectorD &v) const;
  
  double findCrossing(RooRealVar &r, double level, double rStart, double rBound, double rerr);
  
  void RecomputeTargets();
  void GradientMinos();
  
  double EvalLoss(double lambda, const TVectorD &dpar, TVectorD &dL);
  double EvalLossAvg();
  
  static double EvalLossNull(double dummy);
  
  double EvalLossRooFit();
  double EvalLoss(HybridGBRForest *forest, double lambda, const TVectorD &dL, int itree=-1);

  
  double Derivative1Fast(RooAbsReal *function, double currentval, RooRealVar *var, RooArgSet *nset=0, double step=1e-3);
  double Derivative2Fast(RooAbsReal *function, double currentval, RooRealVar *var, RooArgSet *nset=0, double step=1e-3);  
  double Derivative2Fast(RooAbsReal *function, RooRealVar *var1, RooRealVar *var2, RooArgSet *nset=0, double step1=1e-3, double step2=1e-3);  

  
  double Derivative1(RooAbsReal *function, RooRealVar *var, RooArgSet *nset=0, double step=1e-3);
  double Derivative2(RooAbsReal *function, RooRealVar *var, RooArgSet *nset=0, double step=1e-3);
  double Derivative2(RooAbsReal *function, RooRealVar *var1,RooRealVar *var2, RooArgSet *nset=0, double stepa=1e-3, double stepb=1e-3);
  
  RooArgList fCondVars;
  RooArgList fParmVars;
  RooArgList fTgtVars;
  RooArgList fExtVars;
  RooArgList fFullParms;
  RooArgList fFullFuncs;
  
  
  RooGBRFunction *fFunc;

  TNtuple *fResTree;
  
  
  std::vector<RooAbsReal*> fPdfs;
  std::vector<RooAbsData*> fData;
  
  RooArgList fStaticTgts;
  RooArgList fStaticPdfs;
  
  std::vector<RooArgList> fCondVarsClones;
  std::vector<RooArgList> fParmVarsClones;
  std::vector<RooArgList> fStaticTgtsClones;
  std::vector<RooArgList> fStaticPdfsClones;
  std::vector<RooArgList> fFullParmsClones;
  std::vector<RooArgList> fExtVarsClones;
  std::vector<RooArgSet> fParmSetClones;
  RooArgList fClones;
  
  int fNThreads;
  
  std::vector<RooAbsReal*> fLLRTargets;
  
  std::vector<std::vector<RooAbsReal*> > fDerivatives;
  std::vector<std::vector<std::vector<RooAbsReal*> > > f2Derivatives;
  
  double fLambdaVal;
  TMatrixDSym fHessian;
  //TVectorD fGradient;
  
  std::vector<TMatrixD> fHessians;
  std::vector<TVectorD> fGradients;

  RooAbsReal *fExternal;
  RooAbsReal *fN0;
  RooRealVar *fR;
  double fN0Obs;
  //double fNLLVal;
  RooRealVar *fLambda;  
  
  RooRealVar *fConstraintVal;
  RooRealVar *fConstraintCoeff;
  
  double fRMin;
  double fRHigh;
  double fRLow;
  
  TGraph *fDrvGraph;
  TGraph *fDrvGraphSmooth;
  TGraph *fGraphDelta;
  
  RooArgSet fGarbageCollection;
  
  double fProcNorm;
  
  std::vector<std::vector<int> > fOuterIndices;
  std::vector<std::set<std::pair<int,int> > > fIndices;
  
  
  //std::vector<TTree*>       fTrees;
  std::vector<double>       fTreeWeights;
  std::string               fTrainingCut;
  std::vector<std::string>  fInputVars;  
  std::string               fTargetVar;
  int                       fMinEvents;
  std::vector<double>       fMinWeights;
  double                    fShrinkage;
  int                       fNTrees;
  int                       fNQuantiles;
  unsigned int              fNBinsMax;
  float                     fTransitionQuantile;
  double                    fMinCutSignificance;
  double                    fMinCutSignificanceMulti;
  
  
  
  
  int                       fMaxDepth;

  std::vector<double>       fSigmaConsts;
  
  int                      fNTargets;
  //double                   fNSMCObs;
  double                   fNLLVal;
  double                   fdLdR;
  

  std::vector<float> _sepgains; 
  std::vector<float> _sepgainsigs; 
  std::vector<float> _cutvals;  
  std::vector<int> _nlefts; 
  std::vector<int> _nrights; 
  std::vector<float> _sumwlefts; 
  std::vector<float> _sumwrights;   
  std::vector<float> _sumtgtlefts; 
  std::vector<float> _sumtgtrights; 
  std::vector<float> _leftvars; 
  std::vector<float> _rightvars;       
  std::vector<float> _fullvars; 
  std::vector<int>   _bestbins; 
  
  
  std::vector<std::vector<float> > _ws; 
  std::vector<std::vector<float> > _ws2; 
  std::vector<std::vector<std::vector<float> > > _wscls; 
  std::vector<std::vector<int> > _ns; 
  std::vector<std::vector<int> > _nsd;   
  std::vector<std::vector<std::vector<float> > > _tgts; 
  std::vector<std::vector<float> > _tgt2s; 
  std::vector<std::vector<float> > _sumws; 
  std::vector<std::vector<float> > _sumws2;       
  std::vector<std::vector<std::vector<float> > > _sumwscls; 
  std::vector<std::vector<int> > _sumns; 
  std::vector<std::vector<int> > _sumnsd;   
  std::vector<std::vector<std::vector<float> > > _sumtgts; 
  std::vector<std::vector<float> > _sumtgt2s; 
  std::vector<std::vector<float> > _varvals; 
  std::vector<std::vector<float> > _bsepgains; 
  std::vector<std::vector<float> > _bsepgainsigs;       
  
  std::vector<std::vector<int> > _quants; 
  std::vector<std::vector<int> > _bins; 
  
  std::vector<std::vector<float> > fQuantileMaps;     
  
  
//   float *_sepgains; //!
//   float *_sepgainsigs; //!
//   float *_cutvals;  //!
//   int *_nlefts; //!
//   int *_nrights; //!
//   float *_sumwlefts; //!
//   float *_sumwrights;   //!
//   float *_sumtgtlefts; //!
//   float *_sumtgtrights; //!
//   float *_leftvars; //!
//   float *_rightvars;    //!   
//   float *_fullvars; //!
//   int   *_bestbins; //!
//   
//   
//   float **_ws; //!
//   float **_ws2; //!
//   int **_ns; //!
//   int **_nsd; //!  
//   float **_tgts; //!
//   float **_tgt2s; //!
//   float **_sumws; //!
//   float **_sumws2;    //!   
//   int **_sumns; //!
//   int **_sumnsd; //!  
//   float **_sumtgts; //!
//   float **_sumtgt2s; //!
//   float **_varvals; //!
//   float **_bsepgains; //!
//   float **_bsepgainsigs;  //!     
//   
//   int **_quants; //!
//   int **_bins; //!
//   
//   float **fQuantileMaps;   //!
  
  std::vector<HybridGBREvent*> fEvts;
  
private:
  ClassDef(RooHybridBDTAutoPdf,1) // Exponential PDF
};

#endif
