import("music.lib"); //adsr
import("math.lib"); //tanh
import("effect.lib"); //dcblocker

import("params.dsp");
import("constants.dsp"); 

//delays
   uptube1 = fdelay(MAX_DELAY_LENGTH, length1*SR/SOUND_SPEED);
   downtube1 = fdelay(MAX_DELAY_LENGTH, length1*SR/SOUND_SPEED);

   uptube2 = fdelay(MAX_DELAY_LENGTH, length2*SR/SOUND_SPEED);
   downtube2 = fdelay(MAX_DELAY_LENGTH, length2*SR/SOUND_SPEED);

   uptube3 = fdelay(MAX_DELAY_LENGTH, length3*SR/SOUND_SPEED);
   downtube3 = fdelay(MAX_DELAY_LENGTH, length3*SR/SOUND_SPEED);

// losses filter
root_approx = iir((b0,b1,b2,b3),(a1,a2,a3))
with {
	b0=244.7430142563924;
	b1=-676.0168364659433;
	b2=618.3351960657661;
	b3=-187.0612061787509;
	a1=-2.1393706026903;
	a2=1.3187938694334;
	a3=-0.1793563731131;
};

D=const_losses * root_approx
with {
	const_losses=-lossescoef*geo/(2*(sqrt(M_PI)));
	geo = 2*(length1/radius1+length2/radius2+length3/radius3);
};

lossesFilter = _ <: (_+(2*D));

//radiation filter
rad=iir((b0/a0,b1/a0,b2/a0),(a1/a0,a2/a0))
with {
	r=radius1;
	A=(r*SR/(2*SOUND_SPEED))^2;
	B=rad_coef*r*SR/SOUND_SPEED;

	a0=A-B-1;
	a1=B-2*A;
	a2=A;

	b0=A+1-B;
	b1=B-2*A;
	b2=A;
};

// first 2 ports junction
twoportjunc1(p1,p2) = (p1, p2) <: (_,_,_,_) : (_,(_-_)*rk,_) : (_, (_ <: (_,_)) ,_ ) : (_+_, _+_)
with {

   rk = ((radius2*radius2) - (radius1*radius1)) / ((radius2*radius2) + (radius1*radius1));
};

// second 2 ports junction
twoportjunc2(p2,p3) = (p2, p3) <: (_,_,_,_) : (_,(_-_)*rk,_) : (_, (_ <: (_,_)) ,_ ) : (_+_, _+_)
with {
   rk = ((radius3*radius3) - (radius2*radius2)) / ((radius3*radius3) + (radius2*radius2));
};

// resonator
res = inmix : (uptube1,downtube2,downtube3,_) : (twoportjunc1,_,_) : (uptube2,downtube1,_,_) <: (_,!,_,!,!,_,!,_) : (twoportjunc2,_,_) : (uptube3,_,_,_) : outmix
with {
   inmix(dt1, p2, ut3, input) = (dt1+input, p2, ut3, dt1);
   outmix(ut3, p2, dt1, p_in) = (dt1, p2, ut3, dt1, p_in);
};

// calculus of pressure and velocity
calc(p_out, p_in) = ((p_in-p_out)*ONE_OVER_RHO_C, p_out+p_in) <: (_,_,!,_);  // Vac, Pp and Pp for output

resonator(source,impulse) = source+impulse : res~(rad,_,lossesFilter) : (!,!,!,_,_) : calc ;

//process = resonator ;
