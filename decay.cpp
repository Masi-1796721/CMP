//randomly simulate 10^4 events -> I distinguish when generating random angles (?)

#include <iostream>
#include <cmath>

// ROOT header files: Lorentz vector, random numbers, plotting, file storage

#include "TLorentzVector.h"
#include "TMath.h"
#include "TRandom3.h"
#include "TH1F.h"
#include "TCanvas.h"
#include "TFile.h"

using std::cout;
using std::endl;

int main() {

  // DECAY SIMULATION

  // Create B meson, pion and kaon
  TLorentzVector B; //particle object w position X(), Y(), Z(), T(), momentum Px(), Py(), Pz(), E()
  double m_B = 5.279; // GeV
  TLorentzVector Pi;
  double m_Pi = 0.140; // GeV
  TLorentzVector K;
  double m_K = 0.500; //GeV
  
  // square masses of convenience
  double m_B_2 = m_B*m_B;
  double m_Pi_2 = m_Pi*m_Pi;
  double m_K_2 = m_K*m_K;
  
  // 4-momentum of B meson in the LAB rest frame
  double p_B = 0.300; // GeV
  B.SetPxPyPzE(p_B, 0, 0, sqrt(p_B*p_B+m_B_2));
  
  // Start up a new random generator(we will need a delete!)
  TRandom*  gen = new TRandom();
  // ...exploiting the machine clock for the seed
  gen->SetSeed(0);
  // # events
  int nsig = 10000;
  
  //create histogram objects which we will fill with our data
  int nbins=10, xlo=5, xhi=6;
  TH1F tmass("True Mass", "Distribution of true invariant mass", nbins, xlo, xhi);
  TH1F mmass("Measured Mass", "Distribution of measured invariant mass", nbins, xlo, xhi);
  int nbins_1=15,xlo_1=3,xhi_1=4;
  TH1F angle("opening angle", "Distribution of angle between K and Pi in Lab frame", nbins_1,xlo_1,xhi_1);
  
  // 4-momentum of the pion in the B rest frame (center of mass of the B meson)
  double p_Pi = sqrt((m_B_2*m_B_2 + m_Pi_2*m_Pi_2 + m_K_2*m_K_2 -2*m_B_2*m_Pi_2 -2*m_B_2*m_K_2 -4*m_Pi_2*m_K_2)/(4*m_B_2));
  
  // 4-momentum of the kaon in the B rest frame (equal to the pion)
  double p_K = p_Pi;
  
  // Once I have the module of the momentum, I generate the random directions for te two particles
  double px_Pi, py_Pi, pz_Pi, E_Pi, px_K, py_K, pz_K, E_K, E_CoM, psumx, psumy, psumz, Esum, Wt, Wm, theta;

  // Calculate energy in the CoM frame
  E_Pi = sqrt(p_Pi*p_Pi+m_Pi_2);
  E_K = sqrt(p_K*p_K+m_K_2);
  E_CoM = E_Pi+E_K;

  // Detector parameters
  double resol = 0.03; //resolution
  double p_Pi_meas, p_K_meas
  
  // Loop on the 10000 events
  for(int i=0; i<nsig; ++i) {

    // Genarate random direction for pion
    gen->Sphere(px_Pi,py_Pi,pz_Pi,p_Pi);
    // Overwrite the 4-momentum vector for the pion
    Pi.SetPxPyPzE(px_Pi, py_Pi, pz_Pi, E_Pi);
    
    // In the center of mass the kaon has opposite direction w respect to the pion
    px_K=-px_Pi;
    py_K=-py_Pi;
    pz_K=-pz_Pi;
    // Overwrite the 4-momentum vector for the kaon
    K.SetPxPyPzE(px_K, py_K, pz_K, E_K);
    
    // Boost the momenta to the LAB frame
    Pi.Boost(B.BoostVector());
    K.Boost(B.BoostVector());

    // Vector components sum between the two 4-mom
    psumx = Pi.Px()+K.Px();
    psumy = Pi.Py()+K.Py();
    psumz = Pi.Pz()+K.Pz();
    Esum = Pi.E()+K.E();

    // Compute true invariant mass
    Wt = sqrt(Esum*Esum - (psumx*psumx + psumy*psumy + psumz*psumz));
    // Fill histogram with true invariant mass
    tmass.Fill(Wt);
    
    // Calculate opening angle in LAB frame
    theta = Pi.Angle(K.Vect());
    // Fill histogram with opening angle
    angle.Fill(theta);

    // SMEARING

    // Generate gaussian measured values based on the true values and resolution
    px_Pi_meas = gen->Gaus(Pi.Px(), Pi.Px()*resol);
    py_Pi_meas = gen->Gaus(Pi.Py(), Pi.Py()*resol);
    pz_Pi_meas = gen->Gaus(Pi.Pz(), Pi.Pz()*resol);
    E_Pi_meas = gen->Gaus(Pi.E(), Pi.E()*resol);
    px_K_meas = gen->Gaus(K.Px(), K.Px()*resol);
    py_K_meas = gen->Gaus(K.Py(), K.Py()*resol);
    pz_K_meas = gen->Gaus(K.Pz(), K.Pz()*resol);
    E_K_meas = gen->Gaus(K.E(), K.E()*resol);

    // Set the new 4-momentum of the particles in the lab
    Pi.SetPxPyPzE(px_Pi_meas, py_Pi_meas, pz_Pi_meas, E_Pi_meas);
    K.SetPxPyPzE(px_K_meas, py_K_meas, pz_K_meas, E_K_meas);

    // Vector components sum between the two 4-mom
    psumx = Pi.Px()+K.Px();
    psumy = Pi.Py()+K.Py();
    psumz = Pi.Pz()+K.Pz();
    Esum = Pi.E()+K.E();
    
    // Compute measured invariant mass
    Wm = sqrt(Esum*Esum - (psumx*psumx + psumy*psumy + psumz*psumz));
    // Fill histogram with measured invariant mass
    mmass.Fill(Wm);
    
  }

  // Delete the random generator now we are done with it
  delete gen;
  
  // Plotting the results
  // for true mass
  TCanvas canv("canv", "canvas for plotting", 1280, 1024);
  tmass.GetXaxis()->SetTitle("Distribution of mass [GeV]");
  tmass.Draw();
  canv.SaveAs("./true-mass.pdf");
  // for measured mass
  TCanvas canv("canv", "canvas for plotting", 1280, 1024);
  tmass.GetXaxis()->SetTitle("Distribution of mass [GeV]");
  tmass.Draw();
  canv.SaveAs("./measured-mass.pdf");
  // for angle
  TCanvas canv1("canv1","canvas for plotting", 1280,1024);
  angle.GetXaxis()->SetTitle( "Angle [rad]");
  angle.Draw();
  canv1.SaveAs("./opening-angle.pdf");

  /* SMEARING SIMULATION

  // True magnitude of the momentum in the LAB
  p_Pi_0= sqrt(Pi.Px()*Pi.Px() + Pi.Py()*Pi.Py() + Pi.Pz()*Pi.Pz());
  p_K_0 = sqrt(K.Px()*K.Px() + K.Py()*K.Py() + K.Pz()*K.Pz());

  // New random generator
  TRandom3*  gen = new TRandom3();
  gen->SetSeed(0);

  // Detector parameters
  double resol = 0.03; //resolution
  double p_Pi_meas, p_K_meas, p_K_x_m,  p_K_y_m, p_K_z_m, E_K_m,  p_Pi_meas, p_Pi_x_m,  p_Pi_y_m, p_Pi_z_m, E_Pi_m; //measured values
  
  // Loop on the measurements
  for(int i=0; i<nsig; ++i) {

    // Generate measured values based on the true values and resolution
    p_Pi_meas = gen->Gaus(p_Pi_0, p_Pi_0*resol);
    p_K_meas = gen->Gaus(p_K_0, p_K_0*resol);

    // Compute 4-components of the particles momenta based on angles I already have
    

    // Invariant mass of measured Pi and K momenta
    
    
  }
  
  //delete generator
  delete gen;*/
  
  
  return 0;
  
}
