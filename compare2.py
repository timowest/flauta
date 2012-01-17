import csv
import matplotlib.pyplot as plt
import sys, os

def read(filename):
    f = csv.reader(open(filename, 'rU')) 
    values = []
    for row in f:
        temp = [float(cell) for cell in row]
        values.append(temp)
    return values
    f.close()

def plot(plotname, data1, data2, error):
    plt.figure()
    plt.plot(data1, "b")
    plt.plot(data2, "r")
    plt.plot(error, "k")
    plt.xlabel(plotname+"  Blue = C++ Output | Red = Faust Output | Black = Error(C++ Sample - Faust Sample)")
    plt.savefig('plots/'+plotname)
    
def error(use_plot, orig_values, faust_values):
    if use_plot:
        return [(orig_values[i]-faust_values[i]) for i in range(0, len(orig_values))] #abs
    else:
        val_range = max(orig_values) - min(orig_values)
        error_out = [abs(orig_values[i]-faust_values[i]) for i in range(0, len(orig_values))]
        if (val_range > 0):
            return (sum(error_out)) / len(error_out) / val_range
        else:
            return (sum(error_out)) / len(error_out)

def main(use_plot):

	modules = ['bernoulli', 'jetdrive', 'receptivity','turbulence', 'vortex', 'blow', 'excitation', 'resonator']

	files = os.listdir('gen')
	for module in modules:
		orig = sorted([fname for fname in files if fname.split('_')[0] == module and fname.split('_')[3] == 'orig.txt'])
		faust = sorted([fname for fname in files if fname.split('_')[0] == module and fname.split('_')[3] == 'faust.txt'])
		for j in range(len(orig)):
			#print orig[j],faust[j]		
			orig_data = read('gen/' + orig[j])    
	            	faust_data = read('gen/' + faust[j])
			for k in range(len(orig_data)):
				err1 = error(use_plot, orig_data[k], faust_data[k])
				if use_plot:
					plot('out' +'_' + str(k) + orig[j][:-4], orig_data[k], faust_data[k], err1)
				else:
					print '%s %s \n err1 = %s' %(module, orig[j], err1)
    

	
 
if __name__ == '__main__':
    main(len(sys.argv) > 1) # TODO : do better switch
