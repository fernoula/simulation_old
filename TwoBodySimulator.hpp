////// TwoBodySimulator.cpp.
/////// Maria Anastasiou.
/////// November15_2015.

class EnergyLoss{

public:
  EnergyLoss(string Eloss_file, double IonMass=0);

  double GetDistance(double InitialE, double FinalE, double StepSize, int MaxSteps);
  
  double GetDistance_new(double InitialE, double FinalE, double StepSize);

  double GetEnergyLoss(double initial_energy, double distance);

  double GetInitialEnergy(double FinalEnergy, double PathLength, double StepSize);

  double GetFinalEnergy(double InitialEnergy, double PathLength, double StepSize);  

  double GetTimeOfFlight(double InitialEnergy, double PathLength, double StepSize);

  void SetIonMass(double IonMass); 

  ////////--------Lookup Functions--------////////////

  void InitializeLookupTables(Double_t MaximumEnergy, Double_t MaximumDistance, Double_t DeltaE, Double_t DeltaD);

  void PrintLookupTables();

  Double_t GetLookupEnergy(Double_t InitialEnergy, Double_t distance);

  ////////////////////////////////////////////////


  bool GoodELossFile;
  TGraph* EvD;

private:
  double c;
  double* IonEnergy;
  double IonMass;
  double* dEdx_e;
  double* dEdx_n;
  int points;
  int last_point;
  int points1;
  int last_point1;
  bool Energy_in_range;

  Double_t MaximumEnergy;//
  Double_t MaximumDistance;//
  Double_t DeltaD;
  Double_t DeltaE;

  Double_t* EtoDtab;
  Double_t* DtoEtab;

};

class Simulator {

public: 
  //Simulator(string FileELoss1,string FileELoss2,string FileELoss3,string FileELoss4,
  //	    string WorldCoordinatesFilename="", string PCWirePCRFile="", Float_t Excitation = 0.0);

  Simulator(string FileELoss1,string FileELoss2,string FileELoss3,string FileELoss4,
  	    string FileELoss5, string WorldCoordinatesFilename="", string PCWirePCRFile="");

  ~Simulator();

  bool GenerateEvent(CS *cross, Strag *straggle);

  bool SetBeamEnergyRange(Float_t MinE, Float_t MaxE);

  bool SetMasses(Float_t mB,Float_t mT,Float_t mL,Float_t mH, Float_t mH2);
 
  bool InitWorldCoordinates(string WorldCoordinatesFilename);
  
  bool InitPCWirePCR(string PCWirePCRFile);

  bool SimThetaPhiE_in(Float_t MinE, Float_t MaxE);

  //bool SecondProton(const Float_t ee_H_lab, const Float_t Ex);

  bool SecondProton(const Float_t ee_H_lab, const Double_t Px_H_lab,
		    const Double_t Py_H_lab, const Double_t Pz_H_lab,
		    const Float_t Ex);
  
  Float_t NeedleEnergy(Float_t heavyEn, Float_t heavyTheta, Float_t IntPoint);

  bool GetSX3Coord(Float_t& X, Float_t& Y, Float_t& Z, Float_t& Xpc, Float_t& Ypc, Float_t& Zpc,
		   const Float_t Theta, const Float_t PHI, int ring=0); 

  bool GetQQQ3FwdCoord(Float_t& X, Float_t& Y, Float_t& Z, Float_t& Xpc, Float_t& Ypc, Float_t& Zpc,
		       Int_t& detid, const Float_t Theta, const Float_t PHI);

  bool TimeOfFlight();

  bool DrawLines(Int_t Det_ID, Int_t m, Float_t& Wx, Float_t& Wy, Float_t& Wz);

  bool Simulation_Parameters(Float_t& z_SIM, Float_t& Path_sim, Float_t& EL_final,
			     const Float_t& Ep_kin, const Float_t& X, const Float_t& Y, const Float_t& Z);

  bool Reac_point_Reconstruction(Float_t& x_br, Float_t& y_br, Float_t& z_br,
				 Float_t& Theta_Rec, Float_t& Path_Rec, Float_t& Phi_Rec,
				 const Float_t& X, const Float_t& Y, const Float_t& Z, 
				 const Float_t& XN, const Float_t& YN, const Float_t& ZN); 

  bool Kinematics_Rec(Float_t& Ex_Heavy_Rec, const Float_t& Ep_Rec,
		      const Float_t& Theta_Rec, const Float_t& Path_Rec, 
		      const Float_t& Phi_Rec, const Float_t& IntPoint);

  bool RecBeam_SecProton(Float_t& BeamRec_20Ne, const Float_t& Ep1_Rec, const Float_t& Ep2_Rec,
			 const Float_t& Theta1_Rec, const Float_t& Theta2_Rec,
			 const Float_t& Path1_Rec, const Float_t& Path2_Rec, 
			 const Float_t& Phi1_Rec, const Float_t& Phi2_Rec);

  bool Reconstruct_20Ne(Float_t& Ex_20Ne, const Float_t& Ep1_Rec, const Float_t& Ep2_Rec,
			const Float_t& Theta1_Rec, const Float_t& Theta2_Rec,
			const Float_t& Path1_Rec, const Float_t& Path2_Rec, 
			const Float_t& Phi1_Rec, const Float_t& Phi2_Rec, const Float_t IntP);
  
  bool WorldCoordinatesLoaded;
  Float_t ConvFromUtoMeV,MB,MT,MH,ML,MH2,mB,mH,mL,mT,mH2;
  
  Float_t dist,D,xr,yr,zr;
  

  Float_t FinalE,InitialEnergy,Ep_in,Eh_in,Ebeam_final;
  Float_t Ex,Ep_final,Eh_final;

  Float_t ResidualEn;

  Float_t theta_L,phi_L;
  Float_t theta_H,phi_H; 
  Float_t theta_h1,theta_h2,phi_h1,phi_h2;
  
  Float_t TOF_p,TOF_h,TOF_rxn,TOF_light,TOF_heavy,TOF_beam;

  Float_t x11,x22,x33,x44,y11,y22,y33,y44;

  Float_t Ra,La;

  Float_t Hi_e,Hi_p,phi_h_rad, phi_h;
 
  TVector3 boostv;

  Float_t ee_L_lab, ee_H_lab;
  Float_t ke_L_lab, ke_H_lab;
  Float_t ee_1_lab, ee_2_lab, ke_1_lab, ke_2_lab;

  Double_t EH_cm, Px_H_cm, Py_H_cm, Pz_H_cm;
  Double_t Px_H_lab, Py_H_lab, Pz_H_lab;
  Double_t ParentE_lab, Px_P_lab, Py_P_lab, Pz_P_lab;

  EnergyLoss* IonInGas;
  EnergyLoss* proton;
  EnergyLoss* Heavy_ion;
  EnergyLoss* Heavy_ion2;
  EnergyLoss* proton_Si;
 
  
  Float_t MinBeamEnergy;
  Float_t MaxBeamEnergy;
  TRandom3* rand;
  Int_t *DetectorID, *Wire_ID;
  Float_t *ZOffset, *XAt0, *XAt4, *YAt0, *YAt4; 
  Float_t *PC_Radius;
};


