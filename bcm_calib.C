////////////////////////////////////////////////////////////////////
///    BCM Calibration : Four Panel Plots : version 1.0          ///
///    This Script is written for BCM Calibration for the Hall C ///
///    JLab in 12 GeV era.                                       ///
///    Author: Debaditya Biswas                                  ///
///    Research Assistant : Hampton University, VA               ///
///    User : Jefferson Lab, VA                                  ///
///    Contact: biswas@jlab.org                                  ///
///    Last Update Date : August 16th, 2020                      ///
////////////////////////////////////////////////////////////////////

#include "TFile.h"
#include "TTree.h"
#include "TH1F.h"
#include "TF1.h"
#include "TGraph.h"
#include <fstream>
#include <iostream>
#include <TROOT.h>

void 

bcm_calib(){


  gStyle->SetOptStat(0);
  gStyle->SetOptStat(0);
  gStyle->SetTitleFont(22,"");
  
  gStyle->SetTitleFontSize(0.05);
  gStyle->SetNdivisions(505);
  gStyle->SetCanvasColor(10);
  gStyle->SetPadTopMargin(0.10);
  gStyle->SetPadLeftMargin(0.12);
  gStyle->SetPadRightMargin(0.08);
  gStyle->SetPadBottomMargin(.14);
  gStyle->SetTitleYOffset(1.0);
  gStyle->SetTitleXOffset(1.4);
  gStyle->SetTitleYSize(0.05);
  gStyle->SetTitleXSize(0.05);
  gStyle->SetLabelFont(22,"X");
  gStyle->SetLabelFont(22,"Y");
  gStyle->SetTitleFont(132,"X");
  gStyle->SetTitleFont(132,"Y");
  gStyle->SetLabelSize(0.04,"X");
  gStyle->SetLabelSize(0.04,"Y");
  gStyle->SetPaperSize(23,24);
  gStyle->SetOptFit(1);
  gStyle->SetStatX(0.50);
  gStyle->SetStatY(0.89);
  
  Double_t cl1,cl2;
  string filename_ranges; 
  cout << "file name for the rages :" << endl; 
  cout << "choose from : " << endl;
  cout << "ranges_dec17_1178.txt" << endl;
  cout << "ranges_dec_1181.txt" << endl;
  cout << "ranges_jan_1892.txt" << endl;
  cout << "ranges_march18_2757.txt "<< endl;
  cout << "ranges_may5_4322.txt"<<endl;
  cout << "bcm_cal_8450/ranges_25jun19_8450.txt" << endl; 
  cout << "bcm_2_param_high_current_fit_plot/ranges_jan_1892.txt" << endl;
  cout << "bcm_2_param_high_current_fit_plot/ranges_march18_2757_high_freq.txt" << endl;
  cout << "bcm_2_param_high_current_fit_plot/ranges_may5_4322.txt" << endl; 
  cout << "--------------------"<<endl;
  cin >> filename_ranges;
  std::vector<Double_t> r1,r2;
  ifstream infile(filename_ranges.c_str());
  //ifstream infile("ranges_march18_2757.txt");
  //ifstream infile("ranges_jan_1892.txt");
  // ifstream infile("ranges_may5_4322.txt");
  if(infile.fail()){
    cout << "Cannot open the file: " << endl;
    cout << "ok" << endl;   
    exit(1);
    
  }else{
    while(!infile.eof()){
      infile >> cl1 >> cl2 ;
      r1.push_back(cl1);
      r2.push_back(cl2);
      
    }
  }
  r1.pop_back();
  r2.pop_back();  
  Int_t size_rfile = r1.size();  
  Int_t size_rfile_trim = (size_rfile - 1)/2 ;  
  

  Int_t hms_run_NUM ;
  cout << "hms_run_NUM "<< endl;
  cin >> hms_run_NUM ; 
  
  string date ;
  cout << "Date <year-month-day>(example : 2020-Aug-12): "<< endl;
  cin >> date ; 

 



   //Enable this for the December(HMS 1178 & HMS 1181) Run 
  // TFile *f = new TFile(Form("../../hallc-replay-f2xem/ROOTfiles/hms_replay_scalers_%d_-1.root",hms_run_NUM),"READ"); // %d : expects integer; %f expects float 


  //Enable this for the March Run 
  //  TFile *f = new TFile(Form("../../hallc-replay-f2xem/ROOTfiles/shms_replay_scalers_%d_-1.root",hms_run_NUM),"READ"); // %d : expects integer; %f expects float 
  //For production runs : 2581
  // TFile *f = new TFile(Form("../../hallc-replay-f2xem/ROOTfiles/../../abishek/ROOTfiles/realpass-0-shms/shms_replay_production_%d_-1.root",hms_run_NUM),"READ");
  // Enable this for the January Run  
  //  TFile *f = new TFile(Form("../../hallc-replay-f2xem/ROOTfiles/coin_replay_scalers_%d_-1.root",hms_run_NUM),"READ"); // %d : expects integer; %f expects float 
  
  // June 2018 
  //TFile *f = new TFile(Form("../../hallc-replay-f2xem/ROOTfiles/coin_replay_scalers_%d_-1.root",hms_run_NUM),"READ");

  //d2 experiment : August 24, 2020
  //TFile *f = new TFile(Form("/group/c-polhe3/Users/murchhana/hallc_replay/ROOTfiles/shms_replay_production_all_%d_200000.root",hms_run_NUM),"READ");

TFile *f = new TFile(Form("/net/cdaq/cdaql1data/cdaq/polhe3/ROOTfiles/shms_replay_production_default_%d_-1.root",hms_run_NUM),"READ"); // %d : expects integer; %f expects float 


  TTree *T = (TTree*)f->Get("TSP"); // TSH : for HMS and TSP : for SHMS
  
  Int_t totev = T->GetEntries();
  
  
  // Read the branch 
  
  Double_t bcm4A;
  Double_t bcm4B;
  Double_t time;
  Double_t Urate; 

  string bcm_name;   
  cout << "BCM NMAE : " << endl;
  cout << "choose from : BCM1, BCM2, BCM4A, BCM4B, BCM4C " << endl; 
  cin>> bcm_name ;

  // writting out variables in a file
  //cout << "result_filename " << endl; 
  // string result_filename = Form("%s_%s_result_file.txt",bcm_name.c_str(),month.c_str()); 
  //cin >> result_filename ; 


  // bcm1 == "P.BCM2.scalerRate" ;
  T->SetBranchAddress(Form("P.%s.scalerRate",bcm_name.c_str()),&bcm4B);  
// T->SetBranchAddress("P.BCM2.scalerRate", &bcm4B);//for hms: H.BCM1.scalerRate
  T->SetBranchAddress("P.1MHz.scalerTime", &time); //for shms: P.BCM1.scalerRate
  T->SetBranchAddress("P.Unser.scalerRate",&Urate);

 
  cout << "---- ok ----" << endl;

 
  


  //Draw the unser rate vs scaler time & bcm rate vs scaler time 

  TCanvas *c1 = new TCanvas("c1","scaler rate vs scaler time Hall C", 1200, 900);
  c1->Divide(1,2);
  Double_t bcm4A_1[totev], time_1[totev],bcm4B_1[totev],Urate_1[totev] ;
  
  for (Int_t i=0 ; i<totev; i++){
    T->GetEntry(i);
    bcm4B_1[i] = bcm4B ;
    Urate_1[i] = Urate;
    time_1[i] = time ; 
    
  }
  
  // Draw bcm rate vs scaler time
   
  c1->cd(1);
  TGraph *gr2 = new TGraph(totev,time_1,bcm4B_1);
  gr2->SetTitle(Form("BCM Rate vs time ; Scaler time (sec)  ; %s Rate (Hz)",bcm_name.c_str()));
  gr2->GetXaxis()->CenterTitle();
  gr2->GetYaxis()->CenterTitle();
  gr2->SetMarkerColor(8);
  //gr2->SetMarkerSize(0.5);
  gr2->SetMarkerStyle(20);
  gr2->Draw("ale");
 
   
  Double_t d[size_rfile], p[size_rfile]; // dip and peak values : number of lines in text file
  
  // fitting gr2(bcm vs scaler time) from r1[i] to r2[i] with polynomial 0
  // then get the parameter 0 which is the average of the gr2 in that range
 
  for (Int_t i=0; i <size_rfile ;i++){
    TF1* d1 = new TF1("d1", "pol0",0,5000);
    gr2->Fit("d1","S","",r1[i],r2[i]);
    // d1->Draw("Same");
    p[i] = d1->GetParameter(0);
    cout << "fit params : "<< i << " " << p[i] << endl;
  }
  
  cout << "ok" << endl;
  // taking two dips on two sides of the a peak and average them,
  // then substract the average of the dips from the peak, that is p_r  
  Double_t p_r[size_rfile_trim];
  for (Int_t i=0; i<size_rfile_trim; i++){
    cout << p[2*i+1] << " " << p[2*i] <<" "<< p[2*i+2] << endl;
    
    p_r[i] = p[2*i+1] ;//- ((p[2*i] + p[2*i+2])/2.);
    cout << p_r[i] << " real" << endl; 
    
  }
  
  
     // draw all the fitted lines //

  for(Int_t i=0; i<size_rfile; i++ ){
     TLine *l8 = new TLine(r1[i],p[i],r2[i],p[i]);
     l8->SetLineColor(3);
     l8->SetLineWidth(2.0);
     l8->Draw("same");
  }
  
  c1->cd(2);
  TGraph *gr3 = new TGraph(totev,time_1,Urate_1);
  gr3->SetTitle("Rate vs time ; Scaler time (sec)  ; Unser Rate (Hz)");
  // gr1->GetXaxis()->SetLimits(100.0,360.0);
  // gr1->GetYaxis()->SetRangeUser(-0.88,-0.76);
  gr3->GetXaxis()->CenterTitle();
  gr3->GetYaxis()->CenterTitle();
  // gr3->SetMarkerSize(0.5);
  //gr3->SetMarkerStyle(20);
  gr3->SetMarkerColor(2);
  gr3->Draw("ale");
  //TImage *img1 = TImage::Create();
  //img1->FromPad(c1);
  //img1->WriteImage(Form("bcm_calib_plots/unser_%s_freq_time_%d.png",bcm_name.c_str(),hms_run_NUM));
  
    
  
  // Double_t d1[20], 
   Double_t p1[size_rfile]; // parameter values or the average values of the several ranges will be stored here 
  
  for (Int_t i=0; i <size_rfile ;i++){
    TF1* f2 = new TF1("f2", "pol0",0, 5000);
    gr3->Fit("f2","S","",r1[i],r2[i]);
    //  f2->Draw("Same");
    p1[i] = f2->GetParameter(0);
    //  cout << p1[i] << endl;
  }


// draw all the fitted lines //

  for(Int_t i=0; i<size_rfile; i++ ){
     TLine *l10 = new TLine(r1[i],p1[i],r2[i],p1[i]);
     l10->SetLineColor(2);
     l10->SetLineWidth(2);
     l10->Draw("same");
  }

  
  cout << "ok" << endl; 
  Double_t p_r1[size_rfile_trim];
  for (Int_t i=0; i<size_rfile_trim; i++){
    //  cout << p1[2*i+1] << " " << p1[2*i] <<" "<< p1[2*i+2] << endl;
    
    p_r1[i] = p1[2*i+1] - ((p1[2*i] + p1[2*i+2])/2.);
    // cout << p_r1[i] << "real" << endl; 
    
  }
  


  
  // calculate beam current I_U[i] from the bcm rate  

  Double_t I_U[size_rfile_trim];
  // Double_t Gain_U = 0.0002399 ;
  Double_t Gain_U = 0.0002492 ;
  for (Int_t i=0 ; i<size_rfile_trim;i++){ 
    I_U[i]= p_r1[i] * Gain_U;
    // cout <<" I_Unser :"<<I_U[i] << "   " << "BCM_rate :" << p_r[i] << endl;    
    
  }
  
  // calculate unser current uncertaintites for the beam on positions 
    Double_t I_U_err[size_rfile_trim], p_r_err[size_rfile_trim];
    for (Int_t i=0; i<size_rfile_trim; i++){
      I_U_err[i] = 2.0 / sqrt(r2[2*i+1]- r1[2*i+1]);
      p_r_err[i] = 0.01;
      cout << I_U[i] << "  "<< I_U_err[i] << "  " << p_r[i] << "  "<< p_r_err[i]  << endl;
    } 
    
    
    cout << "--- understood ---" << endl; 
    
    
    TCanvas *c2 = new TCanvas("c2","Unser current vs BCM1 frequency : RUN 1181", 1200, 900);  
     c2->Divide(2,2);
     c2->cd(1);
    // c2->cd();  
    TGraphErrors *gr4 = new TGraphErrors(size_rfile_trim,I_U,p_r,I_U_err,p_r_err);
    
    // TGraphErrors *gr4 = new TGraphErrors(9,p_r,I_U,I_U_err,p_r_err);
   
    //  TF1 *f4 = new TF1("f4", "[p0]+2049.00*x");
    TF1 *f4 = new TF1("f4", "pol1");
    // f4->SetParameters(0,200000);
    f4->SetLineColor(3);
    f4->SetParameters(250000.,1600.);
    gr4->SetTitle("BCM Frequency vs Unser Current; unser current(#muA) ; BCM frequency(HZ)");
    gr4->GetXaxis()->CenterTitle();
    gr4->GetYaxis()->CenterTitle();
    //gr4->GetXaxis()->SetLimits(0.0,80.0);
    // gr4->GetYaxis()->SetRangeUser(0.0, 180000.0);
    gr4->SetMarkerSize(1.5);
    gr4->SetMarkerStyle(22);
    gr4->SetMarkerColor(6);
    gr4->Fit("f4","Q","");
    gr4->Draw("AP");
    
    
    TText *t1 = new TText(15.0,120000,Form("Date:%s ,run:%d ,%s",date.c_str(),hms_run_NUM,bcm_name.c_str()));
    t1->SetTextFont(22);
    t1->SetTextSize(0.05);
    t1->Draw("Same"); 


    
    Double_t slope; 
    Double_t intersec;
    //slope = 2049.0 ;
    slope = gr4->GetFunction("f4")->GetParameter(1);
    intersec = gr4->GetFunction("f4")->GetParameter(0);
    cout << " slope = " << slope << " intercept = " << intersec << endl;
    
    cout << "residual calculation "<< endl;
    
    // Calculating Residual
    Double_t BCM_I[size_rfile_trim], residual[size_rfile_trim], residual_percent[size_rfile_trim], I_U_resi_err[size_rfile_trim],
      residual_abs[size_rfile_trim],resisual_abs_err[size_rfile_trim];
    for (Int_t i=0 ; i<size_rfile_trim;i++){
      // find the BCM curent from BCM frequency and slope and the offset
      BCM_I[i] =  (p_r[i]  - intersec) / slope ;
      residual[i] = I_U[i] - BCM_I[i];  
      residual_abs[i] = (residual[i]/I_U[i]) ;
      residual_percent[i] = (residual[i]/I_U[i]) * 100.0 ; 
      resisual_abs_err[i] = (I_U_err[i] / I_U[i]) ;
      I_U_resi_err[i] = 100.0 * (I_U_err[i] / I_U[i]) ; 
      cout << BCM_I[i] << " " << I_U[i] << " "<< residual[i] << endl;
 
     } 

    
    c2->cd(2);
    TGraphErrors *gr7 = new TGraphErrors(size_rfile_trim,I_U,residual,p_r_err,I_U_err);
     gr7->SetTitle("Residual vs Unser Current ; unser current (#muA); residual (#muA)");
     gr7->GetXaxis()->CenterTitle();
     gr7->GetYaxis()->CenterTitle();
     gr7->GetXaxis()->SetLimits(0.0,80.0);
     gr7 ->SetMarkerSize(1.1);
     gr7->SetMarkerStyle(21);
     gr7->SetMarkerColor(9);
     gr7->Draw("SAP");
     TLine *l7 = new TLine(0.,0.,76.5,0.);
     l7->SetLineStyle(9);
     l7->SetLineColor(1);
     l7->SetLineWidth(2);
     l7->Draw();

   c2->cd(3);
   TGraphErrors *gr6 = new TGraphErrors(size_rfile_trim,I_U,residual_percent,p_r_err,I_U_resi_err);
     gr6->SetTitle("% Residual vs Unser Current ; unser current(#muA); % residual");
     gr6->GetXaxis()->CenterTitle();
     gr6->GetYaxis()->CenterTitle();
     gr6->GetXaxis()->SetLimits(0.0,80.0);
     gr6 ->SetMarkerSize(1.1);
     gr6->SetMarkerStyle(21);
     gr6->SetMarkerColor(4);
     gr6->Draw("SAP");
     TLine *l6 = new TLine(0.,0.,80.0,0.);
     l6->SetLineStyle(9);
     l6->SetLineColor(1);
     l6->SetLineWidth(2);
     l6->Draw();

     
     // Residual vs time graph Calculation
     Double_t time_start[size_rfile_trim],time_end[size_rfile_trim], time_ave[size_rfile_trim], time_ave_min[size_rfile_trim]; 
     for(Int_t i=0; i<size_rfile_trim; i++ ){
         
        time_start[i] = r1[2*i + 1.];
	 
        time_end[i] = r2[2*i + 1.]; 
        cout << "----------------" << endl; 
        cout <<  time_start[i] << "time start "<< endl; 
        cout << time_end[i] << "time end" << endl;
        time_ave[i] = (time_start[i] + time_end[i] )/2 ; 
        time_ave_min[i] = time_ave[i] /60. ;
      	cout << time_ave[i] << "time ave " <<"::" << residual_abs[i]<< endl;
     }


     //Drawing the Residual vs Time 

     c2->cd(4);
     TGraphErrors *gr8 = new TGraphErrors(size_rfile_trim,time_ave_min,residual,p_r_err,I_U_err);
     gr8->SetTitle(" Residual vs Scaler Time ; Scaler time (minute); residual (#muA)");
     gr8->GetXaxis()->CenterTitle();
     gr8->GetYaxis()->CenterTitle();
     //gr8->GetXaxis()->SetLimits(0.0,80.0);
     gr8 ->SetMarkerSize(1.1);
     gr8->SetMarkerStyle(21);
     gr8->SetMarkerColor(9);
     gr8->Draw("SAP");
     TLine *l8 = new TLine(0.,0.,40.,0.);
     l8->SetLineColor(1);
     l8->SetLineStyle(9);
     l8->SetLineWidth(2);
     l8->Draw();

    
    //////////////////////////////////////
    ///////// Main Code ends here ////////
    ///////// up to 4 pannel plot ////////
    //////////////////////////////////////

     
  
     // opeing a new text file //
     
     // ofstream bcm_text; 
     // bcm_text.open ("bcm.txt");
     // for(i =0; i<size_rfile_trim ; i++){
     //   bcm_text << I_U[i]<< " " << I_U_err[i]<<" " << p_r[i] << " "<<p_r_err[i] <<" " <<residual[i] << " "<<I_U_err[i] << " "<< residual_percent[i]<<" " << I_U_resi_err[i]<< " " << time_ave_min[i] << " " <<p_r_err[i] << endl;   
     // }
     // bcm_text.close();
     
    

          
     
    
     // std::ofstream result_file;

     // result_file.open(result_filename.c_str());
     // for(UInt_t j=0; j<size_rfile_trim; j++){ 
       
     //   result_file << I_U[j] << " "<< p_r[j] << " " <<I_U_err[j]<<" " <<p_r_err[j]<<" " <<std::endl;
       
     //   // cout <<  I_U[j] << " "<< p_r[j] << " " <<I_U_err[j]<<" " <<p_r_err[j]<<" " << BCM_I[j] << " " << residual_percent[j] << " " << I_U_resi_err[j]<<" " <<endl;
       
     // }
     


    
     cout << size_rfile << " :text file lines " << endl; 
     
}
