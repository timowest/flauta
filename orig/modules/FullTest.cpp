//Bernoulli Includes
#include "Bernoulli.cpp"

// JetDrive Includes
#include "JetDrive.cpp"
#include "Tanh_table.cpp"

// Receptivity Includes
#include "Receptivity.cpp"
#include "MyFilter.cpp"

// Turbulence Includes
#include "Turbulence.cpp"
 // #include "MyFilter.cpp" Already included for receptivity

// Vortex Includes
#include "Vortex.cpp"

//Blow Includes
#include "Blow.cpp"
#include "ADSR.cpp"
#include "SineWave.cpp"
#include "Generator.cpp"
#include "Envelope.cpp"

//Excitation Includes
#include "Excitation.cpp"

//Jet Includes
#include "Jet.cpp"
#include "Delay.cpp"
#include "DelayL.cpp"
#include "Filter.cpp"

//Sources Includes
#include "Sources.cpp"

// Program Includes

#include <sndfile.h>
#include <iostream>
#include <fstream>
#include <cmath>
#include <stdio.h>
#include <math.h>
#include <cstdlib>
#include <cstdio>
#include <string.h>
#include "Stk.cpp"

// Program Definitions

#define SR       44100
#define SIZE     22050
#define LINESIZE 220500

// Global stuffs

float in1[SIZE],  in2[SIZE],  in3[SIZE];
float out1[SIZE], out2[SIZE], out3[SIZE];

using namespace std;

// Timo Fuction to Write
void write(ofstream* out, float* floats) {
    (*out) << floats[0];
    for (int i = 1; i < SIZE; i++) {
        (*out) << "," << floats[i];
    }
    (*out) << "\n";
}

// Timo Fuction to Read
void read(const char* in_file, float* floats) {
    // TODO : optimize
    char line[LINESIZE];
    ifstream in(in_file);
    in.getline(line, LINESIZE);
    
    char *pch = strtok(line, ",");
    while (pch != NULL) {
        *floats = atof(pch);
        pch = strtok(NULL, ",");
        floats++;
    }

    in.close();
}

// Vortex Test Function 
void Vortex_test(float* in1, const char* format, int index, int out_count) {
   
   // Vortex Definitions
   Vortex *my_Vortex;
   my_Vortex = new Vortex();
   StkFloat Vortex_val;

   for (int i = 0; i < SIZE; i++) {        
        Vortex_val = my_Vortex->tick(in1[i]);    
        out1[i] = Vortex_val;
        //out2[i] = ;
        //out3[i] = ;    
    }
    
    //save_outputs();
    char outfile[40];
    sprintf(outfile, format, index);

    cout << outfile << endl;
    // serialize outputs to file
    ofstream out(outfile);
    write(&out, out1);
    if (out_count > 1) write(&out, out2);
    if (out_count > 2) write(&out, out3);
    out.close();   
    
}

// Turbulence Test Function // 
void Turbulence_test(float* in1, const char* format, int index, int out_count) {
     
     // Turbulence Definitions
     Turbulence *my_Turbulence;
     my_Turbulence = new Turbulence();
     StkFloat current_turbulence;

    for (int i = 0; i < SIZE; i++) {
        current_turbulence = my_Turbulence->tick(in1[i], 1.08e-3);    
        out1[i] = current_turbulence;
        //out2[i] = ;
        //out3[i] = ;
      
    }
 
    //save_outputs();
    char outfile[40];
    sprintf(outfile, format, index);

    cout << outfile << endl;
    // serialize outputs to file
    ofstream out(outfile);
    write(&out, out1);
    if (out_count > 1) write(&out, out2);
    if (out_count > 2) write(&out, out3);
    out.close();    
} 

// Receptivity Test Function
void Receptivity_test(float* in1, float* in2,float in3, const char* format, int index, int out_count) {

     // Receptivity Definitions
     Receptivity *My_Receptivity;
     My_Receptivity = new Receptivity(1.08e-3, 4.0e-3); // parameters need to be identical with Faust code
     StkFloat ETA;
 
   
     for (int i = 0; i < SIZE; i++) {
         My_Receptivity->set_Coefficients(in3);
         // reverse order to match the Faust code
         ETA = My_Receptivity->tick(in2[i],in1[i]);    
         out1[i] = ETA;
         //out2[i] = ;
         //out3[i] = ;
      
    }
    //save_outputs();
     char outfile[40];
     sprintf(outfile, format, index);

     cout << outfile << endl;
     // serialize outputs to file
     ofstream out(outfile);
     write(&out, out1);
     if (out_count > 1) write(&out, out2);
     if (out_count > 2) write(&out, out3);
     out.close();     
}

// JetDrive Test Function
void JetDrive_test(float* in1, float* in2, const char* format, int index, int out_count) {

     // JetDrive Definitions
     JetDrive *My_JetDrive;
     My_JetDrive = new JetDrive();
     StkFloat JET_DRIVE;
     StkFloat HYD_FEED;
     StkFloat TEMP;

     for (int i = 0; i < SIZE; i++) {        
         JET_DRIVE = My_JetDrive->tick(in1[i],in2[i],TEMP);    
         HYD_FEED = My_JetDrive->get_Hyd_feedback();      
         out1[i] = HYD_FEED;
         out2[i] = JET_DRIVE;
         //out3[i] = ;
       
     }
     //save_outputs();
     char outfile[40];
     sprintf(outfile, format, index);

     cout << outfile << endl;
     // serialize outputs to file
     ofstream out(outfile);
     write(&out, out1);
     if (out_count > 1) write(&out, out2);
     if (out_count > 2) write(&out, out3);
     out.close();   
}   

// Bernoulli Test Function
void Bernoulli_test(float* in1, float* in2, const char* format, int index, int out_count) {
     
     // Bernoulli definitions
     Bernoulli *my_Bernoulli;
     my_Bernoulli = new Bernoulli();
     StkFloat Uj;
     StkFloat Uj_steady;
     StkFloat Impulse;

     for (int i = 0; i < SIZE; i++) { 
         Uj = my_Bernoulli->tick(in1[i], in2[i], Uj_steady, Impulse);
         out1[i] = Uj;
         out2[i] = Uj_steady;
         out3[i] = Impulse;
     }
    
     //save_outputs();
     char outfile[40];
     sprintf(outfile, format, index);

     cout << outfile << endl;
     // serialize outputs to file
     ofstream out(outfile);
     write(&out, out1);
     if (out_count > 1) write(&out, out2);
     if (out_count > 2) write(&out, out3);
     out.close();   
}
// Blow Test Function
void Blow_test(float* in1, const char* format, int index, int out_count) {
     
     // Blow definitions
     Blow *my_Blow;
     my_Blow = new Blow();
     StkFloat Uj;
     StkFloat Uj_steady;
     StkFloat Impulse;

     for (int i = 0; i < SIZE; i++) { 
         Uj = my_Blow->tick(in1[i], Uj_steady, Impulse); // setting Uj_steady to 0
         out1[i] = Uj;
         out2[i] = Uj_steady;
         out3[i] = Impulse;

         //if (in1[i] <= 0.20027) {
         //in1[i] = 0.20027; 
         //}

          if (std::isinf(out3[i])) { //output is infinite
              // TODO : aggregate
              //cout << in1[i] << " " << Uj_steady << " " << Impulse << " causing Infinite in sample " << i << " previous value in " << in1[i-1] << endl; 
              char temp;
              //cin>>temp;
              
          }
          if (std::isnan(out3[i])) { //output is not a number 0.20027
              // TODO : aggregate
              //cout << in1[i] << " " << Uj_steady << " " << Impulse << " causing Nan in sample " << i << " previous value in " << in1[i-1] << endl; 
              char temp;
              //cin>>temp;
          } 
     }
    
     //save_outputs();
     char outfile[40];
     sprintf(outfile, format, index);
     cout << outfile << endl;
     // serialize outputs to file
     ofstream out(outfile);
     write(&out, out1);
     if (out_count > 1) write(&out, out2);
     if (out_count > 2) write(&out, out3);
     out.close();   
}

// Excitation Test Function
void Excitation_test(float* in1, float* in2, const char* format, int index, int out_count) {
     
     // Excitation definitions
     Excitation *my_Excitation;
     my_Excitation = new Excitation();
     StkFloat Sources;
     StkFloat Impulse;

     for (int i = 0; i < SIZE; i++) { 
         Sources = my_Excitation->tick(in1[i], in2[i], Impulse);
         out1[i] = Sources;
         out2[i] = Impulse;
     }
    
     //save_outputs();
     char outfile[40];
     sprintf(outfile, format, index);

     cout << outfile << endl;
     // serialize outputs to file
     ofstream out(outfile);
     write(&out, out1);
     if (out_count > 1) write(&out, out2);
     if (out_count > 2) write(&out, out3);
     out.close();   
}

// Sources Test Function
void Sources_test(float* in1, float* in2, float* in3, const char* format, int index, int out_count) {
     
     // Sources definitions
     Sources *my_Sources;
     my_Sources = new Sources();
     StkFloat excitation;
     StkFloat hyd_feed;

     for (int i = 0; i < SIZE; i++) { 
         excitation = my_Sources->tick(in1[i], in2[i], in3[i], hyd_feed);
         out1[i] = hyd_feed;
         out2[i] = excitation;
     }
    
     //save_outputs();
     char outfile[40];
     sprintf(outfile, format, index);

     cout << outfile << endl;
     // serialize outputs to file
     ofstream out(outfile);
     write(&out, out1);
     if (out_count > 1) write(&out, out2);
     if (out_count > 2) write(&out, out3);
     out.close();   
}

// Jet Test Function
void Jet_test(float* in1, float* in2, float in3, float* in4, const char* format, int index, int out_count) {
     
     // Jet definitions
     Jet *my_Jet;
     my_Jet = new Jet();
     StkFloat Eta_d;
     StkFloat Uj_d;

     for (int i = 0; i < SIZE; i++) { 
         Eta_d = my_Jet->tick(in1[i], in2[i], in3, in4[i], Uj_d);
         out1[i] = Eta_d;
         out2[i] = Uj_d;
     }
    
     //save_outputs();
     char outfile[40];
     sprintf(outfile, format, index);

     cout << outfile << endl;
     // serialize outputs to file
     ofstream out(outfile);
     write(&out, out1);
     if (out_count > 1) write(&out, out2);
     if (out_count > 2) write(&out, out3);
     out.close();   
}

int main(int argc, char *argv[]) {
    
    Stk::setSampleRate( 44100.0 );  

    // inputs
    float in_imp[SIZE], in_noise[SIZE], in_ramp[SIZE], in_sine[SIZE], in_triang[SIZE], in_step[SIZE];
    read("tests/in_imp.txt", in_imp);       // 1
    read("tests/in_noise.txt", in_noise);   // 2
    read("tests/in_ramp.txt", in_ramp);     // 3
    read("tests/in_sine.txt", in_sine);     // 4
    read("tests/in_triang.txt", in_triang); // 5
    read("tests/in_step.txt", in_step);     // 6

    float* all_inputs[] = {in_imp, in_noise, in_ramp, in_sine, in_triang, in_step};

    for (int r = 0; r < 6; r++) {
        Vortex_test(all_inputs[r], "../../gen/vortex_out_%d_orig.txt" ,(r+1), 1); 
        Turbulence_test(all_inputs[r], "../../gen/turbulence_out_%d_orig.txt", (r+1), 1);
	Blow_test(all_inputs[r], "../../gen/blow_out_%d_orig.txt", (r+1), 3);
            
        for (int j = 0; j < 6; j++) {            
            Bernoulli_test(all_inputs[r], all_inputs[j], "../../gen/bernoulli_out_%d_orig.txt", (r+1)*10+j+1, 3);
	    Receptivity_test(all_inputs[r], all_inputs[j], 25, "../../gen/receptivity_out_%d_orig.txt", (r+1)*10+j+1, 1);
            JetDrive_test(all_inputs[r], all_inputs[j], "../../gen/jetdrive_out_%d_orig.txt", (r+1)*10+j+1, 2);	    
	    Excitation_test(all_inputs[r], all_inputs[j], "../../gen/excitation_out_%d_orig.txt", (r+1)*10+j+1, 2);

            if (argc > 1) continue;

            for(int i = 0; i < 6; i++) {	       
               Sources_test(all_inputs[r], all_inputs[j], all_inputs[i], "../../gen/sources_out_%d_orig.txt",(i+1)*100+(r+1)*10+j+1 , 2);
               
	       for(int q = 0; q < 6; q++) {	       
               Jet_test(all_inputs[r], all_inputs[j], 25, all_inputs[q], "../../gen/jet_out_%d_orig.txt",(q+1)*1000+(i+1)*100+(r+1)*10+j+1 , 2);
            
               }
            }
        }
 
    }

return 0;

}





