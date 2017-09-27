//
// ********************************************************************
// * License and Disclaimer                                           *
// *                                                                  *
// * The  Geant4 software  is  copyright of the Copyright Holders  of *
// * the Geant4 Collaboration.  It is provided  under  the terms  and *
// * conditions of the Geant4 Software License,  included in the file *
// * LICENSE and available at  http://cern.ch/geant4/license .  These *
// * include a list of copyright holders.                             *
// *                                                                  *
// * Neither the authors of this software system, nor their employing *
// * institutes,nor the agencies providing financial support for this *
// * work  make  any representation or  warranty, express or implied, *
// * regarding  this  software system or assume any liability for its *
// * use.  Please see the license in the file  LICENSE  and URL above *
// * for the full disclaimer and the limitation of liability.         *
// *                                                                  *
// * This  code  implementation is the result of  the  scientific and *
// * technical work of the GEANT4 collaboration.                      *
// * By using,  copying,  modifying or  distributing the software (or *
// * any work based  on the software)  you  agree  to acknowledge its *
// * use  in  resulting  scientific  publications,  and indicate your *
// * acceptance of all terms of the Geant4 Software license.          *
// ********************************************************************
//
/// \file hadronic/Hadr03/src/HistoManager.cc
/// \brief Implementation of the HistoManager class
//
// $Id: HistoManager.cc 67909 2013-03-12 18:51:09Z vnivanch $
//
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

#include "HistoManager.hh"
#include "G4UnitsTable.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

HistoManager::HistoManager()
  : fFileName("Hadr06")
{
  Book();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

HistoManager::~HistoManager()
{
  delete G4AnalysisManager::Instance();
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......

void HistoManager::Book()
{
  // Create or get analysis manager
  // The choice of analysis technology is done via selection of a namespace
  // in HistoManager.hh
  G4AnalysisManager* analysisManager = G4AnalysisManager::Instance();
  analysisManager->SetFileName(fFileName);
  analysisManager->SetVerboseLevel(1);
  analysisManager->SetActivation(true);     //enable inactivation of histograms
  analysisManager->SetFirstHistoId(1);

  // Define histograms start values
  const G4int kMaxHisto = 18;
  const G4String id[] = {"1","2","3","4","5","6","7","8","9",
                         "10","11","12","13","14","15","16","17","18"};
  const G4String title[] =
                {
                  "+/-mu energy",                         //1
                  "+/-mu theta",                 //2
                  "+/-mu r1",                    //3
                  "+/-mu r2",                   //4
                  "+/-mu R xy at ground",                     //5
                  "+/-mu Time",                //6
                  "+/-mu Step range",                 //7
                  "proton energy",               //8
                  "+/-pion energy",                  //9
                  "counter",         //10
                  "+/-mu energy ",      //11
                  "proton energy ",       //12
                  "+/-pion energy ",       //13
                  "proton theta",                 //14
                  "+/-pion theta",                 //15
                  "+/-mu vertical energy ",      //16
                  "proton vertical energy ",       //17
                  "+/-pion vertical energy "    //18
                 };

  // Default values (to be reset via /analysis/h1/set command)
  G4int nbins = 100;
  G4double vmin = 0.;
  G4double vmax = 100.;

  // Create all histograms as inactivated
  // as we have not yet set nbins, vmin, vmax
  G4int ih;
  for (G4int k=0; k<kMaxHisto; k++) {
      ih = analysisManager->CreateH1(id[k], title[k], nbins, vmin, vmax);
      analysisManager->SetH1Activation(ih, false);
      //G4cout<<k<<": "<<id<<": "<<id[k]<<"  "<<title[k]<<G4endl;
  }
  ih = analysisManager->CreateH2("1","mu E vs R xy",nbins,vmin,vmax,nbins,vmin,vmax);
  analysisManager->SetH2Activation(ih, false);
  ih = analysisManager->CreateH2("2","mu Y vs X",nbins,vmin,vmax,nbins,vmin,vmax);
  analysisManager->SetH2Activation(ih, false);
  ih = analysisManager->CreateH2("3","protonY vs X",nbins,vmin,vmax,nbins,vmin,vmax);
  analysisManager->SetH2Activation(ih, false);
  ih = analysisManager->CreateH2("4","pion Y vs X",nbins,vmin,vmax,nbins,vmin,vmax);
  analysisManager->SetH2Activation(ih, false);

}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
