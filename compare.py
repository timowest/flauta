import csv
import sys, os

def read(filename):
    f = csv.reader(open(filename, 'rU')) 
    values = []
    for row in f:
        temp = [float(cell) for cell in row]
        values.append(temp)
    return values
    f.close()
   
def error(orig_values, faust_values):
    val_range = max(orig_values) - min(orig_values)
    error_out = [abs(orig_values[i]-faust_values[i]) for i in range(0, len(orig_values))]
    if (val_range > 0):
        return (sum(error_out)) / len(error_out) / val_range
    else:
        return (sum(error_out)) / len(error_out)

def main(fast):
    files = os.listdir('gen')
    slow = ['jet','sources']
    modules = ['bernoulli', 'jetdrive', 'receptivity','turbulence', 'vortex', 'blow', 'excitation', 'resonator', 'jet', 'sources']

    for module in modules:
        if (fast and module in slow):
            continue
        orig = sorted([fname for fname in files if fname.split('_')[0] == module and fname.split('_')[3] == 'orig.txt'])
	faust = sorted([fname for fname in files if fname.split('_')[0] == module and fname.split('_')[3] == 'faust.txt'])

        for j in range(len(orig)):
            num = orig[j].split('_')[2]
            orig_data = read('gen/' + orig[j])    
	    faust_data = read('gen/' + faust[j])

            if len(orig_data) == 1:
                err1 = error(orig_data[0], faust_data[0])
                print '%s %s \n err1 = %s' %(module, num, err1)
            elif len(orig_data) == 2:
                err1 = error(orig_data[0], faust_data[0])
                err2 = error(orig_data[1], faust_data[1])
                print '%s %s \n err1 = %s\n err2 = %s' %(module, num, err1, err2)                    
            elif len(orig_data) == 3:
                err1 = error(orig_data[0], faust_data[0])
                err2 = error(orig_data[1], faust_data[1])
                err3 = error(orig_data[2], faust_data[2])
                print '%s %s \n err1 = %s\n err2 = %s\n err3 = %s' %(module, num, err1, err2, err3)

if __name__ == '__main__':    
    main(len(sys.argv) > 1)
