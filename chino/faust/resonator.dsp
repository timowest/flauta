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
	geo = 2*(length1/radius1+length2/radius2);
};

lossesFilter = _ <: (_+(2*D));
//lossesFilter = (+ <: _, D : +)~(D);

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

// 2portj
twoportjunc = (_, _) <: (_,_,_,_) : (_,(_-_)*rk,_) : (_, (_ <: (_,_)) ,_ ) : (_+_, _+_)
with {

   rk = ((radius2*radius2) - (radius1*radius1)) / ((radius2*radius2) + (radius1*radius1));

};

// resonador
res = inmix <: (uptube1, downtube2, _): (twoportjunc,_) : (uptube2, downtube1, _) <: (_,_,!,!,_,_) : outmix
with {
   inmix(dt1, ut2, input) = (dt1+input, ut2, dt1);
   outmix(ut2, dt1, p_out, p_in) = (dt1, ut2, p_out, p_in);
};

// calculus of pressure and velocity
calc(p_out, p_in) = ((p_in-p_out)*ONE_OVER_RHO_C, p_out+p_in) <: (_,_,!,_);  // Vac, Pp and Pp for output

resonator(source,impulse) = source+impulse : res~(rad,lossesFilter) : (!,!,_,_) : calc ;




//process = resonator ;
