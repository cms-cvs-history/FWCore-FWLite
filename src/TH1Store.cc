// -*- C++ -*-
#include <iostream>
#include <fstream>
#include <iomanip>
#include <cassert>
#include "FWCore/FWLite/interface/TH1Store.h"

using namespace std;

////////////////////////////////////
// Static Member Data Declaration //
////////////////////////////////////

bool TH1Store::sm_verbose = false;


TH1Store::TH1Store() : m_deleteOnDestruction (false)
{
}

TH1Store::~TH1Store()
{
   if (m_deleteOnDestruction)
   {
      for (STH1PtrMapIter iter = m_ptrMap.begin();
           m_ptrMap.end() != iter;
           ++iter)
      {
         delete iter->second;
      } // for iter
   } // if destroying pointers
}

void
TH1Store::add (TH1 *histPtr)
{
   // Do we have a histogram with this name already?
   string name = histPtr->GetName();
   if (m_ptrMap.end() != m_ptrMap.find (name))
   {
      //  D'oh
      cerr << "TH1Store::add() Error: '" << name 
           << "' already exists.  Aborting." << endl;
      assert (0);
   } // if already exists
   if (sm_verbose)
   {
      cout << "THStore::add() : Adding " << name << endl;
   }
   m_ptrMap[name] = histPtr;
}

TH1*
TH1Store::hist (const string &name)
{
   STH1PtrMapIter iter = m_ptrMap.find (name);
   if (m_ptrMap.end() == iter)
   {
      //  D'oh
      cerr << "TH1Store::hist() Error: '" << name 
           << "' does not exists.  Aborting." << endl;
      assert (0);
   } // doesn't exist
   return iter->second;
}

void
TH1Store::write (const string &filename) const
{
   TFile *filePtr = TFile::Open (filename.c_str(), "RECREATE");
   write (filePtr);
   delete filePtr;
}

void
TH1Store::write (TFile *filePtr) const
{
   filePtr->cd();
   for (STH1PtrMapConstIter iter = m_ptrMap.begin();
        m_ptrMap.end() != iter;
        ++iter)
   {
      iter->second->Write();
   } // for iter   
}

// friends
ostream& operator<< (ostream& o_stream, const TH1Store &rhs)
{
   return o_stream;
} 