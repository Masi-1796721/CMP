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

  //in caso mi servisse un file in cui scrivere i dati
  // Open TFile for output
  TString rootfname("./output.root");
  // Overwite output file if it already exists
  TFile rfile(rootfname, "RECREATE");
  // Open the ROOT file and make sure the file was opened successfully.
  // Typical cause for failure are: 1) wrong path, 2) no write privilege
  if( !rfile.IsOpen() ) {
    std::cout << "problems creating root file. existing... " << std::endl;
    exit(-1);
  }
  std::cout << "storing output in root file " << rootfname << std::endl;

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
  // Flat metric, (+ - - -) signature: m^2 = E^2 - p^2
  //B.SetPxPyPzE(p_B, 0, 0, sqrt(p_B*p_B+m_B_2));
  
  // Start up a new random generator(we will need a delete!)
  TRandom*  gen = new TRandom();
  // ...exploiting the machine clock for the seed
  gen->SetSeed(0);
  // # events
  int nsig = 10;//per ora 10
  
  // 4-momentum of the pion in the B rest frame (center of mass of the B meson)
  double p_Pi = sqrt((m_B_2*m_B_2 + m_Pi_2*m_Pi_2 + m_K_2*m_K_2 -2*m_B_2*m_Pi_2 -2*m_B_2*m_K_2 -2*m_Pi_2*m_K_2)/(2*m_B_2));
  
  // 4-momentum of the kaon in the B rest frame (equal to the pion)
  double p_K = p_Pi;
  
  // Once I have the module of the momentum, I generate the random directions for te two particles
  double point_Pi, point_K, px_Pi, py_Pi, pz_Pi, E_Pi, px_K, py_K, pz_K, E_K, psumx, psumy, psumz, Esum, W;

  E_Pi = sqrt(p_Pi*p_Pi+m_Pi_2);
  E_K = sqrt(p_K*p_K+m_K_2);
  Esum = E_Pi+E_K;
  
  // Loop on the 10000 events
  for(int i=0; i<nsig; ++i) {

    // Genarate random direction for pion
    point_Pi = gen.Sphere(px_Pi,py_Pi,pz_Pi,p_Pi);
    // Overwrite the 4-momentum vector for the pion
    Pi.SetPxPyPzE(px_Pi, py_Pi, pz_Pi, E_Pi);
    // Generate random direction for kaon
    point_K = gen.Sphere(px_K,py_K,pz_K,p_K);
    // Overwrite the 4-momentum vector for the kaon
    K.SetPxPyPzE(px_K, py_K, pz_K, E_K);

    // Vector components sum between the two 4-mom
    psumx = px_Pi+px_K;
    psumy = py_Pi+py_K;
    psumz = pz_Pi_pz_K;

    // Calculate invariant mass
    W = sqrt(Esum*Esum - (psumx*psumx + psumy*psumy + psumz*psumz));

    // Fill histogram with invariant mass
    
    // Boost the momenta to the lab reference frame (vedere se sintassi e' giusta)
    Pi.Boost(B.BoostVector());
    K.Boost(B.BoostVector());
    
  }

  // Delete the random generator now we are done with it
  // [We had new, here is delete!]
  delete gen;
  
 

  cout << "--> LAB p4 B: " << endl;
  p4_B.Print();
  cout << "--> CoM p4 pi*: " << endl;
  p4_pi.Print();

  // The TLorentzVector class provides the Beta() and Gamma() methods to
  // compute the boost parameters: we compare them to their definitions
  cout << "--> boost parameters of B reference frame" << endl;
  cout << "\t beta: " << p4_B.Beta() << "\t"
       << "\t p/E:" << p4_B.P()/p4_B.E() << "\n"
       << "\t gamma: " << p4_B.Gamma() << "\t"
       << "\t E/m: " << p4_B.E()/m_B << "\n"
       << "\t beta*gamma: " << p4_B.Beta()*p4_B.Gamma() << "\t"
       << "\t p/m: " << p_B/m_B
       << endl;

  // Boost parameters of the B frame in the LAB frame can be accessed
  // with the BoostVector method
  cout << "--> boost vector of the B meson" << endl;
  p4_B.BoostVector().Print();

  // Let's boost the pion to the LAB frame
  cout << "--> now boost the pion to LAB" << endl;
  p4_pi.Boost(p4_B.BoostVector());
  cout << "--> LAB p4 pi: " << endl;
  p4_pi.Print();

  // Exit
  return 0;
}
