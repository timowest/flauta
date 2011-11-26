import csv
import matplotlib.pyplot as plt
import sys

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
    plt.savefig('gen/'+plotname)
    
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
    modules = ['bernoulli', 'jetdrive', 'receptivity','turbulence', 'vortex', 'blow']
    one_out = [str(n) for n in [1,2,3,4,5]]
    two_out = [str(n) for n in [11,12,13,14,15,21,22,23,24,25,31,32,33,34,35,41,42,43,44,45,51,52,53,54,55]]
    for module in modules:
        if module == 'bernoulli' or module == 'jetdrive' or module == 'receptivity':
            nums = two_out
        else:
            nums = one_out

        for num in nums:
            orig_file ='gen/'+module+'_out_'+num+'_orig.txt'
            faust_file = 'gen/'+module+'_out_'+num+'.txt'
            orig_data = read(orig_file)    
            faust_data = read(faust_file)
            if len(orig_data) == 1:
                err1 = error(use_plot, orig_data[0], faust_data[0])
                if use_plot:
                    plot(module+' '+ num+' out1', orig_data[0], faust_data[0], err1)
                else:
                    print '%s %s \n err1 = %s' %(module, num, err1)
            elif len(orig_data) == 2:
                err1 = error(use_plot, orig_data[0], faust_data[0])
                err2 = error(use_plot, orig_data[1], faust_data[1])
                if use_plot:
                    plot(module+' '+ num+' out1', orig_data[0], faust_data[0], err1)
                    plot(module+' '+ num+' out2', orig_data[1], faust_data[1], err2)
                else:
                    print '%s %s \n err1 = %s\n err2 = %s' %(module, num, err1, err2)                    
            elif len(orig_data) == 3:
                err1 = error(use_plot, orig_data[0], faust_data[0])
                err2 = error(use_plot, orig_data[1], faust_data[1])
                err3 = error(use_plot, orig_data[2], faust_data[2])
                if use_plot:
                    plot(module+' '+ num+' out1', orig_data[0], faust_data[0], err1)
                    plot(module+' '+ num+' out2', orig_data[1], faust_data[1], err2)
                    plot(module+' '+ num+' out3', orig_data[2], faust_data[2], err3)
                else:
                    print '%s %s \n err1 = %s\n err2 = %s\n err3 = %s' %(module, num, err1, err2, err3)
    #plt.show() dont show graph, they are way too many

if __name__ == '__main__':
    main(len(sys.argv) > 1) # TODO : do better switch
