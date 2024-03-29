/////////////////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////Code:18Ne_Hist.C////////////////////////////////////////////////////
//////////////////////////////////Date:May_16_2016///////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////////////////
//

//using the TwoBodySimulator (new PC-24WIRES, new length La=53 cm, new Ra=8.9cm)
/*#include <iostream>
#include <iomanip>
#include <fstream>
#include <cstdlib>
#include <cstring>
#include <string>
#include <sstream>
#include <exception>
#include <stdexcept>
#include <map>

//ROOT libraries
#include <TFile.h>
#include <TTree.h>
#include <TROOT.h>
#include <TNtuple.h>
#include <TCanvas.h>
#include <TRint.h>
#include <TObjArray.h>
#include <TGraph.h>
#include <TH1.h>
#include <TH2.h>
#include <TStyle.h>
#include <TMath.h>
#include <TRandom1.h>
#include <TList.h>
#include <TCutG.h>
#include <TLorentzVector.h>
#include <TVector3.h>
#include <TLegend.h>
#include <TRandom3.h>

using namespace std;
#include "test.cpp"
#include "TwoBodySimulator.hpp"
*/
//int main()
{
  gSystem->Load("TwoBodySimulator_kinematics_cpp.so");
 
  
  Simulator* S = new Simulator("18Nesrim/18Ne_in_HeCO2_356Torr_18Nerun_09122018.eloss","18Nesrim/H_in_HeCO2_379Torr_allruns_09122018.eloss","18Nesrim/21Na_in_HeCO2_356Torr_18Nerun_10082018.eloss","18Nesrim/20Ne_in_HeCO2_356Torr_18Nerun_12242018.eloss","H_in_Si.txt","WorldCoordinates2018Dec4","pcr_list_07192018.dat");   //uses the new zr-offsets for the SX3s 2.5 & 14.9 cm 

  Double_t dist = 40.0;
  Double_t y_s = 0.0;
  Double_t z_s = 0.0;
  
  CS *cross = new CS;
  cross->ReadFile("cross.txt");
  //cross->CrossSection(18.0);

  Strag *straggling = new Strag;
  straggling->ReadFile("18Nesrim/18Ne.txt");
  straggling->Range_Straggling(dist,y_s,z_s);
  cout << dist << " " << y_s/10.0 << " " << z_s/10.0 << endl;


  
  //--------- Energy Loss Tables -----------------------///
  S->IonInGas->InitializeLookupTables(90.0,760.0,0.02,0.04);    
  S->Heavy_ion->InitializeLookupTables(90.0,760.0,0.02,0.04);  
  S->proton->InitializeLookupTables(40.0,15000.0,0.02,0.04); 

  /////////////////////////////////////////////////////////////
  
  TCanvas* Tally1=new TCanvas("Ne","Ne",300,100,1500,1500);
  Tally1->Divide(2,2);
 
  TCanvas* Tally2=new TCanvas("Ne2","Ne2",300,100,1500,1500);
  Tally2->Divide(2,2);

  TCanvas* Tally3=new TCanvas("Ne3","Ne3",300,100,1500,1500);
  Tally3->Divide(2,2);

  TCanvas* Tally4=new TCanvas("Ne4","Ne4",300,100,1500,1500);
  Tally4->Divide(2,2);

  TCanvas* Tally5=new TCanvas("Ne5","Ne5",300,100,1500,1500);
  Tally5->Divide(2,2);

  TCanvas* Tally6=new TCanvas("Ne6","Ne6",300,100,1500,1500);
  Tally6->Divide(2,2);


  TH1F* grb1 = new TH1F("grb1","",100,0,100);
  TH1F* grb2 = new TH1F("grb2","",100,0,100);
  TH1F* grb3 = new TH1F("grb3","",100,0,100);
  TH1F* grBeamRec = new TH1F("grBeamRec","",120,0,6);
  TH1F* grbf = new TH1F("grbf","",100,0,100);
  TH1F* grbfa = new TH1F("grbfa","",100,0,100);
  TH1F* grbfb = new TH1F("grbfb","",100,0,100);
  TH1F* grRing1= new TH1F("grRing1","",100,0,100);
  TH1F* grRing2 = new TH1F("grRing2","",100,0,100);

  
  TH1F* grEx = new TH1F("grEx","",100,-10,15);
  TH1F* grEx_20Ne = new TH1F("grEx_20Ne","",100,-10,15);
  TH1F* grEx_2_21Na = new TH1F("grEx_2_21Na","",100,-10,15);


  TGraph* grb = new TGraph();
  TGraph* grd1 = new TGraph();
  TGraph* grd2 = new TGraph();
  TGraph* grRec = new TGraph();
  TGraph* grRec_q = new TGraph();
  TGraph* grRec_x3 = new TGraph();

 
  TGraph* grSX3 = new TGraph();
  TGraph* grQQQ = new TGraph();

  TGraph* grSim1 = new TGraph();
  TGraph* grSim2 = new TGraph();
  TGraph* grSim3 = new TGraph();
  TGraph* grBeam = new TGraph();

  TGraph* grSim_ex1 = new TGraph();
  TGraph* grSim_ex2 = new TGraph();
  
  TGraph* grResprtheta1 = new TGraph();
  TGraph* grResprtheta2 = new TGraph();

  TGraph* grSecp = new TGraph();
  TGraph* grSecp2 = new TGraph();
  TGraph* grSecp3 = new TGraph();
  
  TGraph* grSim1_secP = new TGraph();
  TGraph* grSim2_secP = new TGraph();
  TGraph* grSim3_secP = new TGraph();
  TGraph* grSim4_secP = new TGraph();
  TGraph* grBeam_secP = new TGraph();

  
  /*
  //Masses in amu
  float mB =18.005708213; //mass of 18Ne
  float mT =4.00260325413;  //mass of He-4.  
  //Mass of the Products.  
  float mL =1.00782503223;  //mass of proton; 
  float mH =20.997655206; //mass of 21Na
  */

  //Mass of the Beam and target
  float mB = 16767.09961; //mass of 18Ne
  float mT = 3727.37892;  //mass of He-4.  
  //Mass of the Products.  
  float mL = 938.27197;  //mass of proton 
  float mH = 19553.56837; //mass of 21Na
  float mH2 = 18617.72807; //mass of 20Ne

  Double_t e=72.34;    //Beam energy range max after passing Kapton foil
  Double_t emin=0.0;   //Beam energy range min the E_threshold

  
  
  S->SetMasses(mB, mT, mL, mH, mH2);
  
  S->SetBeamEnergyRange(emin,e);


  //////////--------Variables-----------------////////////////
  Int_t DetID = -1;
  Float_t Xp,Yp,Zp,Xpc,Ypc,Zpc;
  Float_t Xp2,Yp2,Zp2,Xpc2,Ypc2,Zpc2;
  Float_t EL_final, EL2_final, EH_final, EL_afterSi, EL_detected_1, EL_detected_2;
  Float_t DL, DL_Si;
  
  Float_t t, x_br, y_br, z_br, z_sim;
  Float_t x_br2, y_br2, z_br2, z_sim2;
  Float_t Beam_Path, Beam_Path_rec, Beam_Path_sim, Light_Particle_Path ,Heavy_ion_Particle_Path;
  Float_t K_brr_rec, K_brr_sim, K_lrr ,K_hrr;
  Float_t Beam_Path_rec2, Beam_Path_sim2, K_brr_rec2, K_brr_sim2;
  Float_t BeamRec_20Ne;
  
  Float_t theta_rec, phi_rec, path_rec, path_sim, Ex_21Na, Ex_20Ne, Ex_2_21Na;
  Float_t theta_rec2, phi_rec2, path_rec2, path_sim2;
  Float_t L_Si,L_Si1,L_Si2;
  Float_t EL_fin;
  Float_t EL_Ni,EL_Nf;

  Float_t W_Nsi; 
  Float_t W_Nsi1,Dh1; 
  Float_t W_Nsi2,Dh2; 
  //Width of the silicon detectors.
  Float_t W_iSi = 0.1; //cm (options are 1000 micron and 65 micron)

  ///////////////////////////////////////////////////////////////////////////////////////////////////


  /////////////------------Increments-------------/////////////
 
  int Num_Events = 0, EventsOfInt = 0;
  int  FailCount = 0, FailCount1 = 0, FailCount2 = 0, FailCount3 = 0, FailCount4 = 0;
  //--FailCounts for Second Proton events
  int FailCount_1 = 0, FailCount_2 = 0, FailCount_3 = 0, FailCount_4 = 0;

  //---------
  int nb=0,mm=0,ring=0,npR1=0,npR2=0,nd1=0,nd2=0,nRec=0,nRec_q=0,nRec_x3=0;
  int sim_ex1=0, sim_ex2=0, sim_p1=0, sim_p2=0, sim_p3=0, beam_p=0;
  int sim_p1_2=0, sim_p2_2=0, sim_p3_2=0, sim_p4_2=0, beam_p_2=0;
  int Secp=0, Secp2=0, Secp3=0;

  int j=0;
  const Int_t n=1000;
  
  TRandom3 *rand_ = new TRandom3();
 

  rand_->SetSeed();
  Float_t Efficiency =0;
  
  while(j<n)
  {

    grb1->Fill(S->FinalE);  // distribution of Beam-Reaction Energies: "evenly" distributed between MaxE,MinE at the GenerateEvent()

    if(!S->GenerateEvent(cross,straggling)){
      FailCount++;        // check if for some reason events are not generated, FailCount should be zero if no cross section is involved
      continue;
    }
    
    Num_Events++;
    
    //if(S->FinalE > 22)
    //cout << " BeamEnrgy is : " << S->FinalE << endl;
     
    //if(S->FinalE<10 || S->FinalE>35)
    //  continue;

    if(!S->SimThetaPhiE_in(emin,e)){
      FailCount1++;      // check if for some reason events are not kinematically allowed 
      continue;
    }

    if(S->ke_L_lab <= 0.5){ // these protons have such small En when created that will not reach-detected by the time they reach the Si
      FailCount3++;
      continue;
    }
    
   
   
    //////////////////////////////////////////////////////////////////////////////////////////////////////
   
    // given a theta & phi angle from the kinematics of the light particle
    // find the hitting points of Si & PC detectors
    
    bool foundQQQ = S->GetQQQ3FwdCoord(Xp, Yp, Zp, Xpc, Ypc, Zpc, DetID, S->theta_L, S->phi_L);  
    bool foundSX3 = S->GetSX3Coord(Xp, Yp, Zp, Xpc, Ypc, Zpc, S->theta_L, S->phi_L); 
   
   if(!S->GetQQQ3FwdCoord(Xp, Yp, Zp, Xpc, Ypc, Zpc, DetID, S->theta_L, S->phi_L))
    {
     if(!S->GetSX3Coord(Xp, Yp, Zp, Xpc, Ypc, Zpc, S->theta_L, S->phi_L))
     {
       
       FailCount2++;  // how many events are lost because of not hitting a silicon detector due to geometrical gaps
        continue;
     }
    }

   //-- create the interaction point 
   S->Reac_point_Reconstruction(x_br, y_br, z_br, theta_rec, path_rec, phi_rec, Xp, Yp, Zp, Xpc, Ypc, Zpc);

   S->Simulation_Parameters(z_sim, path_sim, EL_final, S->ke_L_lab, Xp, Yp, Zp);


   // EL_final is the calculated Energy of the proton AT THE SI-DET using path_sim & ke_L_lab
   // Sim particle path = path_sim uses (Xp,Yp,Zp) & (xr,yr,zr)!!!! uses the "offseted" from center precise path!!!
   
   if(EL_final <= 0.5)   // the silicon detectors' threshold is 0.5MeV, so anything below that is not useful
    {
       FailCount4++;
       continue;
     }


   // Beam - Reaction Energy for events that make it to Si-detectors after all the excluded events
   // compare grb2 to grb1 for the efficiency of the detector
   grb2->Fill(S->FinalE);
   
     
    if(EL_final > 0) // 
     {
      grbf->Fill(S->FinalE);   // Reaction Energy distribution for events that made it to the detectors - checked and it is equal to grb2 (as it should!!)

      if(S->GetQQQ3FwdCoord(Xp, Yp, Zp, Xpc, Ypc, Zpc, DetID, S->theta_L, S->phi_L))    
        grbfa->Fill(S->FinalE);

      if(S->GetSX3Coord(Xp, Yp, Zp, Xpc, Ypc, Zpc, S->theta_L, S->phi_L)) 	
        grbfb->Fill(S->FinalE);

      if(S->GetQQQ3FwdCoord(Xp, Yp, Zp, Xpc, Ypc, Zpc, DetID, S->theta_L, S->phi_L))    
        {
          grResprtheta1->SetPoint(npR1,(S->theta_L)*180/TMath::Pi(),EL_final);
          npR1++;
        } 
      else if(S->GetSX3Coord(Xp, Yp, Zp, Xpc, Ypc, Zpc, S->theta_L, S->phi_L))    
        {	  
          grResprtheta2->SetPoint(npR2,(S->theta_L)*180/TMath::Pi(),EL_final);
          npR2++;  
        }  
    }
   
   
   
   // Initial Energy of the light particle:
   K_lrr = S->proton->GetLookupEnergy(EL_final,(-path_rec));

   Beam_Path_rec = sqrt( x_br*x_br + y_br*y_br + pow((S->La)-z_br,2)); 
   Beam_Path_sim = sqrt( x_br*x_br + y_br*y_br + pow((S->La)-z_sim,2)); 
     
   K_brr_rec = S->IonInGas->GetLookupEnergy(e, Beam_Path_rec);
   K_brr_sim = S->IonInGas->GetLookupEnergy(e, Beam_Path_sim);

   //compare reconstructed to simulated values

   grBeamRec->Fill(K_brr_rec*4.0/22.0);
   
   grBeam -> SetPoint(beam_p,K_brr_sim,K_brr_rec);
   beam_p++;

   grSim1->SetPoint(sim_p1,abs(z_br-z_sim),Zp);  
   sim_p1++;	

   grSim2->SetPoint(sim_p2,abs(z_br-z_sim),S->theta_L*180/TMath::Pi()); 
   //grSim2->SetPoint(sim_p2,S->theta_L*180/TMath::Pi(),theta_rec*180/TMath::Pi());  
   sim_p2++;

   grSim3->SetPoint(sim_p3,z_sim,z_br);  
   sim_p3++;


   S->Kinematics_Rec(Ex_21Na, EL_final, theta_rec, path_rec, phi_rec, z_br);
     {	
	grEx->Fill(Ex_21Na);
		
	grSim_ex1->SetPoint(sim_ex1,S->Ex,Ex_21Na);
	sim_ex1++;

	grSim_ex2->SetPoint(sim_ex2,K_brr_rec,Ex_21Na);
	sim_ex2++;
	
       }

      /*if(abs((S->Ex)-Ex_21Na) > 2.0)
       cout << " Ex_sim: " << S->Ex << " Ex_rec: " << Ex_21Na 
	    << " Theta_sim: " << S->theta_L*180/TMath::Pi() << " Theta_rec: " << theta_rec*180/TMath::Pi() 
	    << " IntP_sim: " << z_sim << " IntP_rec: " << z_br 
	    << " BeamEnergy_sim: " << S->FinalE 
	    << " p energy: " << S->ke_L_lab << endl;*/


     //-----------Residual Energy of the Heavy Recoil--------------------------------------------------------------------------//
      
     if(EL_final>0)
       {
	 S->NeedleEnergy(S->ke_H_lab,S->theta_H,z_br);

	 if(S->GetQQQ3FwdCoord(Xp, Yp, Zp, Xpc, Ypc, Zpc, DetID, S->theta_L, S->phi_L))    
        {
	  
	  grRec_q->SetPoint(nRec_q,S->ResidualEn,K_brr_rec);   
	  nRec_q++;	 
	 }
	 else if(S->GetSX3Coord(Xp, Yp, Zp, Xpc, Ypc, Zpc, S->theta_L, S->phi_L))    
        {
	  
	  grRec_x3->SetPoint(nRec_x3,S->ResidualEn,K_brr_rec);   
	  nRec_x3++;
	}
       }

//-------------Calculating Energy of the protons AFTER they go through the Silicon Detector------------------------------//
      
     if(EL_final>0)
       {
	 //with a given "entering" angle to the Si-det how much is the distance covered in 1mm Si
	 DL_Si = W_iSi/sin(theta_rec);

	 //DL_inSi = S->proton_Si->GetDistance_new(EL_final,0.01,0.1);       //how much is the distance in Si material before it stops (FinalE = 0.01 MeV = 10keV)
	 // when DL_Si > DL_inSi the particle stops in the Silicon. 

	 EL_afterSi = S->proton_Si->GetFinalEnergy(EL_final, DL_Si,0.01); 
	 
	 //if(EL_afterSi < 0.0)
	 //  cout << " EL_AFTER_SI: " << EL_afterSi << endl;
	 
	 if(EL_afterSi > 0)
	   {
	     EL_detected_1 = EL_final - EL_afterSi;
	     grd1->SetPoint(nd1,(theta_rec)*180/TMath::Pi(),EL_detected_1);
	     nd1++;
	   }
	 else
	   {
	     EL_detected_2 = EL_final;
	     grd2->SetPoint(nd2,(theta_rec)*180/TMath::Pi(),EL_detected_2);
	     nd2++;	     
	   }
       }
     

     
     //////////////////////////////////////////////////////////////////////////////
     //----------Second Proton-------------------------------////////////////
     
     if(!S->SecondProton(S->ee_H_lab, S->Px_H_lab, S->Py_H_lab, S->Pz_H_lab, S->Ex))
       {
	 FailCount_1++;
	 continue;
       }
     
     if(S->ke_1_lab<=0.5)
       {
	 FailCount_2++;
	 continue;
       }
     
     bool foundQQQ_secP = S->GetQQQ3FwdCoord(Xp2, Yp2, Zp2, Xpc2, Ypc2, Zpc2, DetID, S->theta_h1, S->phi_h1);  
     bool foundSX3_secP = S->GetSX3Coord(Xp2, Yp2, Zp2, Xpc2, Ypc2, Zpc2, S->theta_h1, S->phi_h1); 
    
   if(!S->GetQQQ3FwdCoord(Xp2, Yp2, Zp2, Xpc2, Ypc2, Zpc2, DetID, S->theta_h1, S->phi_h1))
    {
     if(!S->GetSX3Coord(Xp2, Yp2, Zp2, Xpc2, Ypc2, Zpc2, S->theta_h1, S->phi_h1))
     {
       
       FailCount_3++;  // how many events are lost because of not hitting a silicon detector due to geometrical gaps
        continue;
     }
    }

  
   S->Reac_point_Reconstruction(x_br2, y_br2, z_br2, theta_rec2, path_rec2, phi_rec2, Xp2, Yp2, Zp2, Xpc2, Ypc2, Zpc2);

   S->Simulation_Parameters(z_sim2, path_sim2, EL2_final, S->ke_1_lab, Xp2, Yp2, Zp2);

   if(EL2_final <= 0.5)   // the silicon detectors' threshold is 0.5MeV, so anything below that is not useful
    {
       FailCount_4++;
       continue;
    }

   grSecp->SetPoint(Secp, (theta_rec)*180/TMath::Pi(), (theta_rec2)*180/TMath::Pi());
   Secp++;
   
   grSecp3->SetPoint(Secp3,EL_final,EL2_final);
   Secp3++;

   grb3->Fill(S->FinalE);   
   
  
   Beam_Path_rec2 = sqrt( x_br*x_br + y_br*y_br + pow((S->La)-z_br2,2)); 
   Beam_Path_sim2 = sqrt( x_br*x_br + y_br*y_br + pow((S->La)-z_sim2,2)); 
     
   K_brr_rec2 = S->IonInGas->GetLookupEnergy(e, Beam_Path_rec2);
   K_brr_sim2 = S->IonInGas->GetLookupEnergy(e, Beam_Path_sim2);

   //compare reconstructed to simulated values
   grBeam_secP -> SetPoint(beam_p_2,K_brr_sim2,K_brr_rec2);
   beam_p_2++;

   grSim1_secP->SetPoint(sim_p1_2,abs(z_br2-z_sim2),Zp2);  
   sim_p1_2++;	

   grSim2_secP->SetPoint(sim_p2_2,abs(z_br2-z_sim2),S->theta_h1*180/TMath::Pi()); 
   sim_p2_2++;

   grSim3_secP->SetPoint(sim_p3_2,z_sim2,z_br2);  
   sim_p3_2++;
   
   S->RecBeam_SecProton(BeamRec_20Ne, EL_final, EL2_final,theta_rec, theta_rec2,
			path_rec, path_rec2,phi_rec, phi_rec2);

   
   grSecp2->SetPoint(Secp2, BeamRec_20Ne, K_brr_rec);
   Secp2++;
   
   
   S->Reconstruct_20Ne(Ex_20Ne, EL_final, EL2_final,theta_rec, theta_rec2,
   		       path_rec, path_rec2,phi_rec, phi_rec2, z_br2);

   grEx_20Ne->Fill(Ex_20Ne);

   grSim4_secP->SetPoint(sim_p4_2,z_br,z_br2);  
   sim_p4_2++;

   S->Kinematics_Rec(Ex_2_21Na, EL2_final, theta_rec2, path_rec2, phi_rec2, z_br2);
   
   grEx_2_21Na->Fill(Ex_2_21Na);



///////////////////--------------j++ ending--------------------////////////////////////////////////////////

      j++;
      cout << "\rDone: " <<setprecision(2) << fixed << showpoint <<  j/double(n)*100 << "% (Efficiency: " <<double(j*100)/(j+FailCount2+FailCount3)<<"%)"<<  " " << Num_Events << " " << flush;
  }

  cout << endl;
 

   cout << "Events: " << Num_Events << endl;
   cout << "Events n: " << n << endl;
   cout << "Event Generator FailCount: " << FailCount << endl;
   cout << "Kinematics FailCount1: " << FailCount1 << endl;
   cout << "Not making it to detector-Geometry FailCount2: " << FailCount2 << endl;
   cout << "proton_En from kinematics less than 0.5MeV - FailCount3: " << FailCount3 << endl;
   cout << "proton_En at the detector less than 0.5MeV - FailCount4: " << FailCount4 << endl;
   cout << "Kinematics 2 protons FailCount_1: " << FailCount_1 << endl;
   cout << "2 proton_En from kinematics less than 0.5MeV - FailCount_2: " << FailCount_2 << endl;
   cout << "2 proton Not making it to detector-Geometry FailCount_3: " << FailCount_3 << endl;
   cout << "2 proton_En at the detector less than 0.5MeV - FailCount4: " << FailCount_4 << endl;
   Efficiency = n*100./(n+(FailCount+FailCount1+FailCount2+FailCount3));

   cout<<"Efficiency = "<< (double)Efficiency <<endl;
  /////////////////////////////////////////////////////////////////////////////////////////////////

   
  Tally1->cd(1); 
  grb1->SetStats(false);
  grb1->GetXaxis()->SetTitle("reaction energy (MeV)");
  grb1->GetYaxis()->SetTitle("counts");
  // grbf->GetYaxis()->SetTitleOffset(1.2);
  grb1->SetLineWidth(3);
  grb1->GetXaxis()->SetLabelFont(62);
  grb1->GetXaxis()->SetLabelSize(0.047);
  grb1->GetXaxis()->SetTitleSize(0.048);
  grb1->GetXaxis()->SetTitleFont(62);
  grb1->GetYaxis()->SetLabelFont(62);
  grb1->GetYaxis()->SetLabelSize(0.047);
  grb1->GetYaxis()->SetTitleSize(0.048);
  grb1->GetYaxis()->SetTitleFont(62);
  grb1->Draw();
  grb2->SetLineWidth(3);
  grb2->SetLineColor(2);
  grb2->Draw("same");

  TLegend* leg1 = new TLegend(0.78,0.7,0.9,0.9); 
  leg1->SetFillColor(0);
  leg1->SetTextSize(0.05);
  leg1->AddEntry(grb1,"all events","l");
  leg1->AddEntry(grb2,"det hits","l");
  leg1->Draw(); 
   

  Tally1->cd(2); 
  grbf->SetStats(false);
  grbf->GetXaxis()->SetTitle("reaction energy (MeV)");
  grbf->GetYaxis()->SetTitle("Efficiency");
  // grbf->GetYaxis()->SetTitleOffset(1.2);
  grbf->SetLineWidth(3);
  grbf->GetXaxis()->SetLabelFont(62);
  grbf->GetXaxis()->SetLabelSize(0.047);
  grbf->GetXaxis()->SetTitleSize(0.048);
  grbf->GetXaxis()->SetTitleFont(62);
  grbf->GetYaxis()->SetLabelFont(62);
  grbf->GetYaxis()->SetLabelSize(0.047);
  grbf->GetYaxis()->SetTitleSize(0.048);
  grbf->GetYaxis()->SetTitleFont(62);
  grbf->Divide(grb1);
  grbf->Draw();
  
 
  Tally1->cd(3);
  grbfb->SetStats(false);  
  grbfb->GetXaxis()->SetTitle("reaction energy (MeV)");
  grbfb->GetYaxis()->SetTitle("Efficiency");
  // grbfb->GetYaxis()->SetTitleOffset(1.2);
  grbfb->SetLineWidth(3);
  grbfb->SetLineColor(2);
  grbfb->GetXaxis()->SetLabelFont(62);
  grbfb->GetXaxis()->SetLabelSize(0.047);
  grbfb->GetXaxis()->SetTitleSize(0.048);
  grbfb->GetXaxis()->SetTitleFont(62);
  grbfb->GetYaxis()->SetLabelFont(62);
  grbfb->GetYaxis()->SetLabelSize(0.047);
  grbfb->GetYaxis()->SetTitleSize(0.048);
  grbfb->GetYaxis()->SetTitleFont(62);
  grbfb->Divide(grb1);
  grbfb->Draw();
  // grRing1->SetLineColor(2);
  // grRing1->Divide(grb1);  
  // grRing1->Draw("same");
  // grRing2->SetLineColor(3);
  // grRing2->Divide(grb1);  
  // grRing2->Draw("same");
  grbfa->SetLineColor(1); 
  grbfa->SetLineWidth(3);
  grbfa->Divide(grb1); 
  grbfa->Draw("same");

  TLegend* leg2 = new TLegend(0.78,0.7,0.9,0.9); 
  leg2->SetFillColor(0);
  leg2->SetTextSize(0.05);
  leg2->AddEntry(grbfa,"QQQs","l");
  leg2->AddEntry(grbfb,"SX3s","l");
  leg2->Draw(); 

  Tally1->cd(4); 
  grb3->SetStats(false);
  grb3->GetXaxis()->SetTitle("reaction energy (MeV)");
  grb3->GetYaxis()->SetTitle("Efficiency 2nd p");
  // grbf->GetYaxis()->SetTitleOffset(1.2);
  grb3->SetLineWidth(3);
  grb3->GetXaxis()->SetLabelFont(62);
  grb3->GetXaxis()->SetLabelSize(0.047);
  grb3->GetXaxis()->SetTitleSize(0.048);
  grb3->GetXaxis()->SetTitleFont(62);
  grb3->GetYaxis()->SetLabelFont(62);
  grb3->GetYaxis()->SetLabelSize(0.047);
  grb3->GetYaxis()->SetTitleSize(0.048);
  grb3->GetYaxis()->SetTitleFont(62);
  grb3->Divide(grb1);
  grb3->Draw();

  
  
  Tally2->cd(1);
  grBeam->SetMarkerColor(2);
  grBeam->SetMarkerSize(1.0);
  grBeam->SetMarkerStyle(7); 
  grBeam->GetXaxis()->SetTitle("Beam_sim (MeV)");
  grBeam->GetYaxis()->SetTitle("Beam_rec (MeV)"); 
  grBeam->GetXaxis()->SetLabelFont(62);
  grBeam->GetXaxis()->SetLabelSize(0.047);
  grBeam->GetXaxis()->SetTitleSize(0.048);
  grBeam->GetXaxis()->SetTitleFont(62);
  grBeam->GetYaxis()->SetLabelFont(62);
  grBeam->GetYaxis()->SetLabelSize(0.047);
  grBeam->GetYaxis()->SetTitleSize(0.048);
  grBeam->GetYaxis()->SetTitleFont(62);
  grBeam->Draw("AP");
  TF1 *fun = new TF1("fun","x",0,80);
  fun->SetLineColor(1);
  fun->SetLineWidth(2);
  fun->Draw("same");


   
  Tally2->cd(2);
  grSim1->SetMarkerColor(2);
  grSim1->SetMarkerSize(1.5);
  grSim1->SetMarkerStyle(7);
  grSim1->GetXaxis()->SetTitle("z_Rec - z_sim (cm)");
  grSim1->GetYaxis()->SetTitle("z_detector (cm)");
  grSim1->GetXaxis()->SetLabelFont(62);
  grSim1->GetXaxis()->SetLabelSize(0.047);
  grSim1->GetXaxis()->SetTitleSize(0.048);
  grSim1->GetXaxis()->SetTitleFont(62);
  grSim1->GetYaxis()->SetLabelFont(62);
  grSim1->GetYaxis()->SetLabelSize(0.047);
  grSim1->GetYaxis()->SetTitleSize(0.048);
  grSim1->GetYaxis()->SetTitleFont(62);
  grSim1->Draw("AP");


  Tally2->cd(3);
  grSim3->SetMarkerColor(2);
  grSim3->SetMarkerSize(1.5);
  grSim3->SetMarkerStyle(7);
  grSim3->GetXaxis()->SetTitle("z_sim (cm)");
  grSim3->GetYaxis()->SetTitle("z_rec (cm)");
  grSim3->GetXaxis()->SetLabelFont(62);
  grSim3->GetXaxis()->SetLabelSize(0.047);
  grSim3->GetXaxis()->SetTitleSize(0.048);
  grSim3->GetXaxis()->SetTitleFont(62);
  grSim3->GetYaxis()->SetLabelFont(62);
  grSim3->GetYaxis()->SetLabelSize(0.047);
  grSim3->GetYaxis()->SetTitleSize(0.048);
  grSim3->GetYaxis()->SetTitleFont(62);
  grSim3->Draw("AP");
  fun->Draw("same");
  
   
  Tally2->cd(4);
  grSim2->SetMarkerColor(2);
  grSim2->SetMarkerSize(1.5);
  grSim2->SetMarkerStyle(7);
  //grSim2->GetXaxis()->SetTitle("theta_sim (deg)");
  //grSim2->GetYaxis()->SetTitle("theta_rec (deg)");
  grSim2->GetXaxis()->SetTitle("z_Rec - z_sim (cm)");
  grSim2->GetYaxis()->SetTitle("theta_lab (deg)"); 
  grSim2->GetXaxis()->SetLabelFont(62);
  grSim2->GetXaxis()->SetLabelSize(0.047);
  grSim2->GetXaxis()->SetTitleSize(0.048);
  grSim2->GetXaxis()->SetTitleFont(62);
  grSim2->GetYaxis()->SetLabelFont(62);
  grSim2->GetYaxis()->SetLabelSize(0.047);
  grSim2->GetYaxis()->SetTitleSize(0.048);
  grSim2->GetYaxis()->SetTitleFont(62);
  grSim2->Draw("AP");
  //fun->Draw("same");


    
  Tally3->cd(1); 
  grEx->SetStats(false);
  grEx->GetXaxis()->SetTitle("Excitation energy (MeV)");
  grEx->GetYaxis()->SetTitle("counts");
  grEx->SetLineWidth(3);
  grEx->GetXaxis()->SetLabelFont(62);
  grEx->GetXaxis()->SetLabelSize(0.047);
  grEx->GetXaxis()->SetTitleSize(0.048);
  grEx->GetXaxis()->SetTitleFont(62);
  grEx->GetYaxis()->SetLabelFont(62);
  grEx->GetYaxis()->SetLabelSize(0.047);
  grEx->GetYaxis()->SetTitleSize(0.048);
  grEx->GetYaxis()->SetTitleFont(62);
  grEx->Draw();
  grEx_2_21Na->SetLineColor(2);
  grEx_2_21Na->SetLineWidth(3);
  grEx_2_21Na->Draw("same");
  

  
  Tally3->cd(2);
  grSim_ex2->SetMarkerColor(2);
  grSim_ex2->SetMarkerSize(1.5);
  grSim_ex2->SetMarkerStyle(7);
  grSim_ex2->GetXaxis()->SetTitle("Beam Energy (MeV)");
  grSim_ex2->GetYaxis()->SetTitle("Ex Reconstructed (MeV)");
  grSim_ex2->GetXaxis()->SetLabelFont(62);
  grSim_ex2->GetXaxis()->SetLabelSize(0.047);
  grSim_ex2->GetXaxis()->SetTitleSize(0.048);
  grSim_ex2->GetXaxis()->SetTitleFont(62);
  grSim_ex2->GetYaxis()->SetLabelFont(62);
  grSim_ex2->GetYaxis()->SetLabelSize(0.047);
  grSim_ex2->GetYaxis()->SetTitleSize(0.048);
  grSim_ex2->GetYaxis()->SetTitleFont(62);
  grSim_ex2->Draw("AP");
 
  Tally3->cd(3);
  grSim_ex1->SetMarkerColor(2);
  grSim_ex1->SetMarkerSize(1.5);
  grSim_ex1->SetMarkerStyle(7);
  grSim_ex1->GetXaxis()->SetTitle("Ex sim (MeV)");
  grSim_ex1->GetYaxis()->SetTitle("Ex Rec(MeV)");
  grSim_ex1->GetXaxis()->SetLabelFont(62);
  grSim_ex1->GetXaxis()->SetLabelSize(0.047);
  grSim_ex1->GetXaxis()->SetTitleSize(0.048);
  grSim_ex1->GetXaxis()->SetTitleFont(62);
  grSim_ex1->GetYaxis()->SetLabelFont(62);
  grSim_ex1->GetYaxis()->SetLabelSize(0.047);
  grSim_ex1->GetYaxis()->SetTitleSize(0.048);
  grSim_ex1->GetYaxis()->SetTitleFont(62);
  grSim_ex1->Draw("AP");


  Tally3->cd(4);
  grResprtheta2->SetMarkerColor(2);
  grResprtheta2->SetMarkerSize(1.5);
  grResprtheta2->SetMarkerStyle(7);
  //grResprtheta2->SetTitle("18Ne(a,p)21Na, Ebeam=10-30MeV, Pressure=379Torr");
  grResprtheta2->SetTitle("18Ne(a,p)21Na, Pressure=379Torr");
  grResprtheta2->GetXaxis()->SetTitle("Theta_lab (deg)");
  grResprtheta2->GetYaxis()->SetTitle("Ep_final_sim (MeV)");
  grResprtheta2->GetXaxis()->SetLimits(0,180);
  grResprtheta2->GetXaxis()->SetLabelFont(62);
  grResprtheta2->GetXaxis()->SetLabelSize(0.047);
  grResprtheta2->GetXaxis()->SetTitleSize(0.048);
  grResprtheta2->GetXaxis()->SetTitleFont(62);
  grResprtheta2->GetYaxis()->SetLabelFont(62);
  grResprtheta2->GetYaxis()->SetLabelSize(0.047);
  grResprtheta2->GetYaxis()->SetTitleSize(0.048);
  grResprtheta2->GetYaxis()->SetTitleFont(62);
  grResprtheta2->Draw("AP");
  grResprtheta1->SetMarkerColor(1);
  grResprtheta1->SetMarkerSize(1.0);
  grResprtheta1->SetMarkerStyle(3);  
  grResprtheta1->Draw("P same"); 


  
  Tally4->cd(1);
  grBeam_secP->SetMarkerColor(2);
  grBeam_secP->SetMarkerSize(1.0);
  grBeam_secP->SetMarkerStyle(7); 
  grBeam_secP->GetXaxis()->SetTitle("Beam_sim 2nd p (MeV)");
  grBeam_secP->GetYaxis()->SetTitle("Beam_rec 2nd p (MeV)"); 
  grBeam_secP->GetXaxis()->SetLabelFont(62);
  grBeam_secP->GetXaxis()->SetLabelSize(0.047);
  grBeam_secP->GetXaxis()->SetTitleSize(0.048);
  grBeam_secP->GetXaxis()->SetTitleFont(62);
  grBeam_secP->GetYaxis()->SetLabelFont(62);
  grBeam_secP->GetYaxis()->SetLabelSize(0.047);
  grBeam_secP->GetYaxis()->SetTitleSize(0.048);
  grBeam_secP->GetYaxis()->SetTitleFont(62);
  grBeam_secP->Draw("AP");
  fun->SetLineColor(1);
  fun->SetLineWidth(2);
  fun->Draw("same");


   
  Tally4->cd(2);
  grSim1_secP->SetMarkerColor(2);
  grSim1_secP->SetMarkerSize(1.5);
  grSim1_secP->SetMarkerStyle(7);
  grSim1_secP->GetXaxis()->SetTitle("z_Rec - z_sim 2nd p (cm)");
  grSim1_secP->GetYaxis()->SetTitle("z_detector 2nd p (cm)");
  grSim1_secP->GetXaxis()->SetLabelFont(62);
  grSim1_secP->GetXaxis()->SetLabelSize(0.047);
  grSim1_secP->GetXaxis()->SetTitleSize(0.048);
  grSim1_secP->GetXaxis()->SetTitleFont(62);
  grSim1_secP->GetYaxis()->SetLabelFont(62);
  grSim1_secP->GetYaxis()->SetLabelSize(0.047);
  grSim1_secP->GetYaxis()->SetTitleSize(0.048);
  grSim1_secP->GetYaxis()->SetTitleFont(62);
  grSim1_secP->Draw("AP");


  Tally4->cd(3);
  grSim3_secP->SetMarkerColor(2);
  grSim3_secP->SetMarkerSize(1.5);
  grSim3_secP->SetMarkerStyle(7);
  grSim3_secP->GetXaxis()->SetTitle("z_sim 2nd p (cm)");
  grSim3_secP->GetYaxis()->SetTitle("z_rec 2nd p (cm)");
  grSim3_secP->GetXaxis()->SetLabelFont(62);
  grSim3_secP->GetXaxis()->SetLabelSize(0.047);
  grSim3_secP->GetXaxis()->SetTitleSize(0.048);
  grSim3_secP->GetXaxis()->SetTitleFont(62);
  grSim3_secP->GetYaxis()->SetLabelFont(62);
  grSim3_secP->GetYaxis()->SetLabelSize(0.047);
  grSim3_secP->GetYaxis()->SetTitleSize(0.048);
  grSim3_secP->GetYaxis()->SetTitleFont(62);
  grSim3_secP->Draw("AP");
  fun->Draw("same");
  
   
  Tally4->cd(4);
  grSim2_secP->SetMarkerColor(2);
  grSim2_secP->SetMarkerSize(1.5);
  grSim2_secP->SetMarkerStyle(7);
  //grSim2->GetXaxis()->SetTitle("theta_sim (deg)");
  //grSim2->GetYaxis()->SetTitle("theta_rec (deg)");
  grSim2_secP->GetXaxis()->SetTitle("z_Rec - z_sim 2nd p (cm)");
  grSim2_secP->GetYaxis()->SetTitle("theta_lab 2nd p (deg)"); 
  grSim2_secP->GetXaxis()->SetLabelFont(62);
  grSim2_secP->GetXaxis()->SetLabelSize(0.047);
  grSim2_secP->GetXaxis()->SetTitleSize(0.048);
  grSim2_secP->GetXaxis()->SetTitleFont(62);
  grSim2_secP->GetYaxis()->SetLabelFont(62);
  grSim2_secP->GetYaxis()->SetLabelSize(0.047);
  grSim2_secP->GetYaxis()->SetTitleSize(0.048);
  grSim2_secP->GetYaxis()->SetTitleFont(62);
  grSim2_secP->Draw("AP");
  //fun->Draw("same");


  Tally5->cd(1); 
  grEx_20Ne->SetStats(false);
  grEx_20Ne->GetXaxis()->SetTitle("Excitation energy of 20Ne (MeV)");
  grEx_20Ne->GetYaxis()->SetTitle("counts");
  grEx_20Ne->SetLineWidth(3);
  grEx_20Ne->GetXaxis()->SetLabelFont(62);
  grEx_20Ne->GetXaxis()->SetLabelSize(0.047);
  grEx_20Ne->GetXaxis()->SetTitleSize(0.048);
  grEx_20Ne->GetXaxis()->SetTitleFont(62);
  grEx_20Ne->GetYaxis()->SetLabelFont(62);
  grEx_20Ne->GetYaxis()->SetLabelSize(0.047);
  grEx_20Ne->GetYaxis()->SetTitleSize(0.048);
  grEx_20Ne->GetYaxis()->SetTitleFont(62);
  grEx_20Ne->Draw();

  Tally5->cd(2);
  grSecp2->SetMarkerColor(2);
  grSecp2->SetMarkerSize(1.5);
  grSecp2->SetMarkerStyle(7);
  grSecp2->GetXaxis()->SetTitle("BeamRec_20Ne 2nd p (MeV)");
  grSecp2->GetYaxis()->SetTitle("BeamRec 1st p (MeV)");
  grSecp2->GetXaxis()->SetLabelFont(62);
  grSecp2->GetXaxis()->SetLabelSize(0.047);
  grSecp2->GetXaxis()->SetTitleSize(0.048);
  grSecp2->GetXaxis()->SetTitleFont(62);
  grSecp2->GetYaxis()->SetLabelFont(62);
  grSecp2->GetYaxis()->SetLabelSize(0.047);
  grSecp2->GetYaxis()->SetTitleSize(0.048);
  grSecp2->GetYaxis()->SetTitleFont(62);
  grSecp2->Draw("AP");
  fun->Draw("same");


  Tally5->cd(3);
  grSim4_secP->SetMarkerColor(2);
  grSim4_secP->SetMarkerSize(1.5);
  grSim4_secP->SetMarkerStyle(7);
  grSim4_secP->GetXaxis()->SetTitle("z_rec 1st p (cm)");
  grSim4_secP->GetYaxis()->SetTitle("z_rec 2nd p (cm)");
  grSim4_secP->GetXaxis()->SetLabelFont(62);
  grSim4_secP->GetXaxis()->SetLabelSize(0.047);
  grSim4_secP->GetXaxis()->SetTitleSize(0.048);
  grSim4_secP->GetXaxis()->SetTitleFont(62);
  grSim4_secP->GetYaxis()->SetLabelFont(62);
  grSim4_secP->GetYaxis()->SetLabelSize(0.047);
  grSim4_secP->GetYaxis()->SetTitleSize(0.048);
  grSim4_secP->GetYaxis()->SetTitleFont(62);
  grSim4_secP->Draw("AP");
  fun->Draw("same");

  Tally5->cd(4);
  grSecp3->SetMarkerColor(2);
  grSecp3->SetMarkerSize(1.5);
  grSecp3->SetMarkerStyle(7);
  grSecp3->GetXaxis()->SetTitle("E proton1 (MeV)");
  grSecp3->GetYaxis()->SetTitle("E proton2 (MeV)");
  grSecp3->GetXaxis()->SetLabelFont(62);
  grSecp3->GetXaxis()->SetLabelSize(0.047);
  grSecp3->GetXaxis()->SetTitleSize(0.048);
  grSecp3->GetXaxis()->SetTitleFont(62);
  grSecp3->GetYaxis()->SetLabelFont(62);
  grSecp3->GetYaxis()->SetLabelSize(0.047);
  grSecp3->GetYaxis()->SetTitleSize(0.048);
  grSecp3->GetYaxis()->SetTitleFont(62);
  grSecp3->Draw("AP");


  Tally6->cd(1);
  grSecp->SetMarkerColor(2);
  grSecp->SetMarkerSize(1.5);
  grSecp->SetMarkerStyle(7);
  grSecp->GetXaxis()->SetTitle("theta proton1 (deg)");
  grSecp->GetYaxis()->SetTitle("theta proton2 (deg)");
  grSecp->GetXaxis()->SetLabelFont(62);
  grSecp->GetXaxis()->SetLabelSize(0.047);
  grSecp->GetXaxis()->SetTitleSize(0.048);
  grSecp->GetXaxis()->SetTitleFont(62);
  grSecp->GetYaxis()->SetLabelFont(62);
  grSecp->GetYaxis()->SetLabelSize(0.047);
  grSecp->GetYaxis()->SetTitleSize(0.048);
  grSecp->GetYaxis()->SetTitleFont(62);
  grSecp->Draw("AP");
  
  Tally6->cd(2); 
  grBeamRec->SetStats(false);
  grBeamRec->GetXaxis()->SetTitle("reaction energy at cm (MeV)");
  grBeamRec->GetYaxis()->SetTitle("counts");
  // grbf->GetYaxis()->SetTitleOffset(1.2);
  grBeamRec->SetLineWidth(3);
  grBeamRec->GetXaxis()->SetLabelFont(62);
  grBeamRec->GetXaxis()->SetLabelSize(0.047);
  grBeamRec->GetXaxis()->SetTitleSize(0.048);
  grBeamRec->GetXaxis()->SetTitleFont(62);
  grBeamRec->GetYaxis()->SetLabelFont(62);
  grBeamRec->GetYaxis()->SetLabelSize(0.047);
  grBeamRec->GetYaxis()->SetTitleSize(0.048);
  grBeamRec->GetYaxis()->SetTitleFont(62);
  grBeamRec->Draw();
  
  
  Tally6->cd(3);
  grd2->SetMarkerColor(2);
  grd2->SetMarkerSize(1.5);
  grd2->SetMarkerStyle(7);
  grd2->GetXaxis()->SetTitle("Theta_lab (kinematics) (deg)");
  grd2->GetYaxis()->SetTitle("Ep_final (MeV)"); 
  grd2->GetXaxis()->SetLabelFont(62);
  grd2->GetXaxis()->SetLabelSize(0.047);
  grd2->GetXaxis()->SetTitleSize(0.048);
  grd2->GetXaxis()->SetTitleFont(62);
  grd2->GetYaxis()->SetLabelFont(62);
  grd2->GetYaxis()->SetLabelSize(0.047);
  grd2->GetYaxis()->SetTitleSize(0.048);
  grd2->GetYaxis()->SetTitleFont(62);
  grd2->Draw("AP");
  grd1->SetMarkerColor(1);
  grd1->SetMarkerSize(1.0);
  grd1->SetMarkerStyle(3);  
  grd1->Draw("P same"); 

  TLegend* leg4 = new TLegend(0.78,0.7,0.9,0.9); 
  leg4->SetFillColor(0);
  leg4->SetTextSize(0.05);
  leg4->AddEntry(grd1,"p-through","p");
  leg4->AddEntry(grd2,"no p-through","p");
  leg4->Draw(); 
  

  Tally6->cd(4); 
  grRec_q->SetMarkerColor(2);
  grRec_q->SetMarkerSize(1.0);
  grRec_q->SetMarkerStyle(7); 
  grRec_q->SetTitle("18Ne(a,p)21Na, pEnergy vs RecoilEn");
  grRec_q->GetXaxis()->SetTitle("ResidualEn (MeV)");
  grRec_q->GetYaxis()->SetTitle("BeamE Rec (MeV)");
  grRec_q->GetXaxis()->SetLimits(-1,40); 
  grRec_q->GetXaxis()->SetLabelFont(62);
  grRec_q->GetXaxis()->SetLabelSize(0.047);
  grRec_q->GetXaxis()->SetTitleSize(0.048);
  grRec_q->GetXaxis()->SetTitleFont(62);
  grRec_q->GetYaxis()->SetLabelFont(62);
  grRec_q->GetYaxis()->SetLabelSize(0.047);
  grRec_q->GetYaxis()->SetTitleSize(0.048);
  grRec_q->GetYaxis()->SetTitleFont(62);
  grRec_q->Draw("AP");     
  grRec_x3->SetMarkerColor(1);
  grRec_x3->SetMarkerSize(1.0);
  grRec_x3->SetMarkerStyle(3);  
  grRec_x3->Draw("P same"); 

  TLegend* leg5 = new TLegend(0.78,0.7,0.9,0.9); 
  leg5->SetFillColor(0);
  leg5->SetTextSize(0.05);
  leg5->AddEntry(grRec_q,"qqq","p");
  leg5->AddEntry(grRec_x3,"sx3","p");
  leg5->Draw();

  
  Tally1->SaveAs("nocross1.png");

  
  return;
  
}
//////////////////////////////////////////////////////////////////////////////////////////////////

