
#ifndef  __receptivity_H__
#define  __receptivity_H__
/************************************************************************
 ************************************************************************
    FAUST Architecture File
	Copyright (C) 2003-2011 GRAME, Centre National de Creation Musicale
    ---------------------------------------------------------------------

	This is sample code. This file is provided as an example of minimal
	FAUST architecture file. Redistribution and use in source and binary
	forms, with or without modification, in part or in full are permitted.
	In particular you can create a derived work of this FAUST architecture
	and distribute that work under terms of your choice.

	This sample code is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 ************************************************************************
 ************************************************************************/

#include <cmath>

#include "gui/GUI.h"
#include "audio/dsp.h"
#include "misc.h"

/******************************************************************************
*******************************************************************************

							       VECTOR INTRINSICS

*******************************************************************************
*******************************************************************************/


/******************************************************************************
*******************************************************************************

			ABSTRACT USER INTERFACE

*******************************************************************************
*******************************************************************************/

//----------------------------------------------------------------------------
//  FAUST generated signal processor
//----------------------------------------------------------------------------

#ifndef FAUSTFLOAT
#define FAUSTFLOAT float
#endif  

typedef long double quad;
/* link with  */
#include <math.h>

float powf(float dummy0, float dummy1);
float faustpower2_f(float value) {
	return (value * value);
	
}
float sqrtf(float dummy0);
float fabsf(float dummy0);
float sinf(float dummy0);
float cosf(float dummy0);
float acosf(float dummy0);

class receptivity : public dsp {
	
  private:
	
	float fRec0[3];
	float fRec1[4];
	float fRec2[4];
	FAUSTFLOAT fhslider0;
	FAUSTFLOAT fhslider1;
	int fSamplingFreq;
	int iConst0;
	float fConst1;
	float fConst2;
	float fConst3;
	float fConst4;
	float fConst5;
	
  public:
	
	void static metadata(Meta* m) { 
		m->declare("music.lib/name", "Music Library");
		m->declare("music.lib/author", "GRAME");
		m->declare("music.lib/copyright", "GRAME");
		m->declare("music.lib/version", "1.0");
		m->declare("music.lib/license", "LGPL");
		m->declare("math.lib/name", "Math Library");
		m->declare("math.lib/author", "GRAME");
		m->declare("math.lib/copyright", "GRAME");
		m->declare("math.lib/version", "1.0");
		m->declare("math.lib/license", "LGPL");
		m->declare("filter.lib/name", "Faust Filter Library");
		m->declare("filter.lib/author", "Julius O. Smith (jos at ccrma.stanford.edu)");
		m->declare("filter.lib/copyright", "Julius O. Smith III");
		m->declare("filter.lib/version", "1.29");
		m->declare("filter.lib/license", "STK-4.3");
		m->declare("filter.lib/reference", "https://ccrma.stanford.edu/~jos/filters/");
		m->declare("oscillator.lib/name", "Faust Oscillator Library");
		m->declare("oscillator.lib/author", "Julius O. Smith (jos at ccrma.stanford.edu)");
		m->declare("oscillator.lib/copyright", "Julius O. Smith III");
		m->declare("oscillator.lib/version", "1.10");
		m->declare("oscillator.lib/license", "STK-4.3");
	}

	virtual ~receptivity() {
		destroy();
	}

	void destroy() {
		
	}
	virtual int getNumInputs() {
		return 3;
		
	}
	virtual int getNumOutputs() {
		return 1;
		
	}
	virtual int getInputRate(int channel) {
		switch (channel) {
			case 0: {
				return 1;
				
			}
			case 1: {
				return 1;
				
			}
			case 2: {
				return 1;
				
			}
			default: {
				return -1;
				
			}
			
		}
		
	}
	virtual int getOutputRate(int channel) {
		switch (channel) {
			case 0: {
				return 0;
				
			}
			default: {
				return -1;
				
			}
			
		}
		
	}
	
	static void classInit(int samplingFreq) {
		
	}
	
	virtual void instanceInit(int samplingFreq) {
		fSamplingFreq = samplingFreq;
		fhslider0 = FAUSTFLOAT(0.004);
		fhslider1 = FAUSTFLOAT(0.001);
		iConst0 = min(192000, max(1, fSamplingFreq));
		fConst1 = (0.1477f / float(iConst0));
		fConst2 = (1.2006f / float(iConst0));
		fConst3 = (0.3278f / float(iConst0));
		fConst4 = (0.3275f / float(iConst0));
		fConst5 = (0.0645f / float(iConst0));
		for (int i = 0; (i < 4); i = (i + 1)) {
			fRec2[i] = 0.f;
			
		}
		for (int i = 0; (i < 4); i = (i + 1)) {
			fRec1[i] = 0.f;
			
		}
		for (int i = 0; (i < 3); i = (i + 1)) {
			fRec0[i] = 0.f;
			
		}
		
	}
	
	virtual void init(int samplingFreq) {
		classInit(samplingFreq);
		instanceInit(samplingFreq);
	}
	
	virtual void buildUserInterface(UI* interface) {
		interface->openVerticalBox("receptivity-test");
		interface->addHorizontalSlider("flue-labium dist", &fhslider0, 0.004f, 0.0005f, 0.0127f, 0.0001f);
		interface->addHorizontalSlider("jet height", &fhslider1, 0.001f, 5e-05f, 0.00127f, 0.0001f);
		interface->closeBox();
		
	}
	
	virtual void compute(int count, FAUSTFLOAT** inputs, FAUSTFLOAT** outputs) {
		FAUSTFLOAT* input0 = inputs[0];
		FAUSTFLOAT* input1 = inputs[1];
		FAUSTFLOAT* input2 = inputs[2];
		FAUSTFLOAT* output0 = outputs[0];
		float fSlow0 = float(fhslider1);
		float fSlow1 = (float(fhslider0) / fSlow0);
		float fSlow2 = powf(10.f, float((0.11942f * fSlow1)));
		float fSlow3 = (1.f + fSlow2);
		float fSlow4 = (fSlow2 - 1.f);
		float fSlow5 = faustpower2_f(fSlow2);
		float fSlow6 = ((1.f + fSlow5) - (2.f * faustpower2_f(sqrtf(fSlow2))));
		float fSlow7 = (1.f - fSlow5);
		float fSlow8 = (int(int((fSlow6 != 0.f)))?((fSlow7 * (1.f - (sqrtf(((faustpower2_f(fSlow7) / faustpower2_f(fSlow6)) - 1.f)) / fabsf((fSlow7 / fSlow6))))) / fSlow6):0.f);
		float fSlow9 = (fSlow4 * fSlow8);
		float fSlow10 = (fConst1 / fSlow0);
		float fSlow11 = (fSlow3 * fSlow8);
		float fSlow12 = (fSlow4 + fSlow11);
		float fSlow13 = powf(10.f, float((0.253595f * fSlow1)));
		float fSlow14 = (0.25f * fSlow13);
		float fSlow15 = (fConst2 / fSlow0);
		float fSlow16 = (fConst3 / fSlow0);
		float fSlow17 = powf(10.f, float((0.131685f * fSlow1)));
		float fSlow18 = (0.25f * fSlow17);
		float fSlow19 = (fConst4 / fSlow0);
		float fSlow20 = (fConst5 / fSlow0);
		float fSlow21 = (fSlow9 + fSlow3);
		for (int i = 0; (i < count); i = (i + 1)) {
			float fTemp0 = float(input2[i]);
			float fTemp1 = (fSlow10 * fTemp0);
			float fTemp2 = sinf((fTemp1 - 0.785398f));
			float fTemp3 = sinf((0.785398f + fTemp1));
			float fTemp4 = (1.f + ((fSlow8 * fTemp2) / fTemp3));
			float fTemp5 = cosf((fSlow15 * fTemp0));
			float fTemp6 = cosf((fSlow16 * fTemp0));
			float fTemp7 = (fTemp5 + fTemp6);
			float fTemp8 = (1.f + (fTemp5 * fTemp6));
			float fTemp9 = acosf(((fTemp8 * (1.f - (sqrtf(((faustpower2_f(fTemp8) / faustpower2_f(fTemp7)) - 1.f)) / fabsf((fTemp8 / fTemp7))))) / fTemp7));
			float fTemp10 = sinf(fTemp9);
			float fTemp11 = cosf(fTemp9);
			float fTemp12 = (2.f * sqrtf((fSlow14 * ((fTemp7 * faustpower2_f(fTemp10)) / (0.f - (fTemp7 - (2.f * fTemp11)))))));
			float fTemp13 = (fTemp12 - fTemp10);
			float fTemp14 = (fTemp10 + fTemp12);
			float fTemp15 = (fTemp13 / fTemp14);
			float fTemp16 = (1.f + fTemp15);
			float fTemp17 = ((fTemp16 * (0.f - fTemp11)) * fRec1[2]);
			float fTemp18 = cosf((fSlow19 * fTemp0));
			float fTemp19 = cosf((fSlow20 * fTemp0));
			float fTemp20 = (fTemp18 + fTemp19);
			float fTemp21 = (1.f + (fTemp18 * fTemp19));
			float fTemp22 = acosf(((fTemp21 * (1.f - (sqrtf(((faustpower2_f(fTemp21) / faustpower2_f(fTemp20)) - 1.f)) / fabsf((fTemp21 / fTemp20))))) / fTemp20));
			float fTemp23 = sinf(fTemp22);
			float fTemp24 = cosf(fTemp22);
			float fTemp25 = (2.f * sqrtf((fSlow18 * ((fTemp20 * faustpower2_f(fTemp23)) / (0.f - (fTemp20 - (2.f * fTemp24)))))));
			float fTemp26 = (fTemp25 - fTemp23);
			float fTemp27 = (fTemp23 + fTemp25);
			float fTemp28 = (fTemp26 / fTemp27);
			float fTemp29 = (1.f + fTemp28);
			float fTemp30 = ((fTemp29 * (0.f - fTemp24)) * fRec2[2]);
			fRec2[0] = (0.f - (((((fTemp26 * fRec2[3]) / fTemp27) + fRec2[1]) + fTemp30) - (float(input0[i]) + (0.63662f * float(input1[i])))));
			float fTemp31 = (fSlow17 * (1.f - fTemp28));
			fRec1[0] = (0.f - (((((fTemp13 * fRec1[3]) / fTemp14) + fRec1[1]) + fTemp17) - (0.5f * (((2.f * (fTemp30 + fRec2[0])) + ((fTemp29 - fTemp31) * fRec2[3])) + ((1.f + (fTemp28 + fTemp31)) * fRec2[1])))));
			float fTemp32 = (fSlow13 * (1.f - fTemp15));
			fRec0[0] = (0.f - (((((fSlow8 + (fTemp2 / fTemp3)) * fRec0[2]) / fTemp4) + fRec0[1]) - (0.5f * (((2.f * (fTemp17 + fRec1[0])) + ((fTemp16 - fTemp32) * fRec1[3])) + ((1.f + (fTemp15 + fTemp32)) * fRec1[1])))));
			output0[i] = FAUSTFLOAT(((0.5f * ((((fSlow3 + (fSlow9 + ((fTemp2 * fSlow12) / fTemp3))) * fRec0[1]) + (fRec0[2] * (fSlow4 + (((fTemp2 * fSlow21) / fTemp3) + fSlow11)))) / fTemp4)) + fRec0[0]));
			for (int j = 3; (j > 0); j = (j - 1)) {
				fRec2[j] = fRec2[(j - 1)];
				
			}
			for (int j = 3; (j > 0); j = (j - 1)) {
				fRec1[j] = fRec1[(j - 1)];
				
			}
			fRec0[2] = fRec0[1];
			fRec0[1] = fRec0[0];
			
		}
		
	}

	
};


#endif
