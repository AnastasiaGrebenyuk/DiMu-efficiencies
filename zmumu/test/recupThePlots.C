
//TFile *myFile = new TFile("TnP_ElecID_data_JSON_huguesTest_denom_pt.root");

//TFile *myOutFile = new TFile("thePlotFile.root","RECREATE");
TString thePath = "/afs/cern.ch/user/a/agrebeny/CMSSW_7_4_7/src/MuonAnalysis/TagAndProbe/test/zmumu/test";
TString theOutFileName = "output_data_Mu17_pt.root";


void recupThePlots(){
//	TDirectory *theDr = (TDirectory*) myFile->Get("eleIDdir");///denom_pt/fit_eff_plots");
	//theDr->ls();
	cout << "coucou" << theOutFileName << endl;
	
	TFile *myOutFile = new TFile(theOutFileName,"RECREATE");
	
	TSystemDirectory dir(thePath, thePath);
	TSystemFile *file;
	TString fname;
	TIter next(dir.GetListOfFiles());
	while (((file=(TSystemFile*)next()))) {
		fname = file->GetName();
		if ((fname.BeginsWith("TnP"))&&fname.Contains("data")) {
                        cout <<  "--------------------"<< "\n";
                        cout << fname << "\n";
			TFile *myFile = new TFile(fname);
			TIter nextkey(myFile->GetListOfKeys());                   
			TKey *key;
			while ((key = (TKey*)nextkey())) {
                                // cout << key << "\n";
				TString theTypeClasse = key->GetClassName();
				TString theNomClasse = key->GetTitle();
                                   cout << "theTypeClasse:  "<< theTypeClasse << " ,  " << theNomClasse << "\n";
				if ( theTypeClasse == "TDirectoryFile" ){
                                        //    cout << "we are here 1" << "\n";
					TDirectory *theDr = (TDirectory*) myFile->Get(theNomClasse);
					TIter nextkey2(theDr->GetListOfKeys());
					TKey *key2;
					while ((key2 = (TKey*)nextkey2())) {
						TString theTypeClasse2 = key2->GetClassName();
						TString theNomClasse2 = key2->GetTitle();	
						if ( theTypeClasse == "TDirectoryFile" || theTypeClasse == "TGraphAsymmErrors" ){
							TDirectory *theDr2 = (TDirectory*) myFile->Get(theNomClasse+"/"+theNomClasse2+"/fit_eff_plots");
							TIter nextkey3(theDr2->GetListOfKeys());
							TKey *key3;
							while ((key3 = (TKey*)nextkey3())) {
								TString theTypeClasse3 = key3->GetClassName();
								TString theNomClasse3 = key3->GetName();	
				 				cout << "type = " << theTypeClasse3 << " nom = " << theNomClasse3 << endl;
						
								TCanvas *theCanvas = (TCanvas*) myFile->Get(theNomClasse+"/"+theNomClasse2+"/fit_eff_plots/"+theNomClasse3);
								TIter nextObject(theCanvas->GetListOfPrimitives());
								TObject *obj;
								while ((obj = (TObject*)nextObject())) {
									if (obj->InheritsFrom("TGraphAsymmErrors")) {
					        				cout << "histo: " << obj->GetName() << endl;
										myOutFile->cd();
										obj->Write(theNomClasse2+"_"+theNomClasse3);
										myFile->cd();
									}
									if (obj->InheritsFrom("TH2F")) {
										cout << "the TH2F = " << obj->GetName() << endl;
										myOutFile->cd();
										obj->Write(theNomClasse2+"_"+theNomClasse3);
										myFile->cd();
									}
								}
							}
						}

					}
			
				}
			}
			delete myFile;
		}
	
	}
	myOutFile->Close();

}
