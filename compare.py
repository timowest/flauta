import csv
import matplotlib.pyplot as plt

def read(filename):
    f = csv.reader(open(filename, 'rU')) 
    values = []
    for row in f:
        temp = [float(cell) for cell in row]
        values.append(temp)
    return values
    f.close()

def plot(plotname,data1,data2, error):
    plt.figure()
    plt.plot(data1, "b")
    plt.plot(data2, "r")
    plt.plot(error, "k")
    plt.xlabel(plotname+"  Blue = C++ Output | Red = Faust Output | Black = Error(C++ Sample - Faust Sample)")
    plt.savefig('gen/'+plotname)
    

def error(orig_values, faust_values):
    error_out = [(orig_values[i]-faust_values[i]) for i in range(0, len(orig_values))] #abs
    #average_out = (sum(error_out)) / len(error_out)
    return error_out    

def main():
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
                err1 = error(orig_data[0], faust_data[0])
                plot(module+' '+ num+' output 1', orig_data[0], faust_data[0], err1)
                #print module+' '+ num, '\n', " error output 1 = ", err1
            elif len(orig_data) == 2:
                err1 = error(orig_data[0], faust_data[0])
                err2 = error(orig_data[1], faust_data[1])
                plot(module+' '+ num+' output 1', orig_data[0], faust_data[0], err1)
                plot(module+' '+ num+' output 2', orig_data[1], faust_data[1], err2)
                #print module+' '+ num, '\n', " error output 1 = ", err1, '\n', " error output 2 = ", err2
            elif len(orig_data) == 3:
                err1 = error(orig_data[0], faust_data[0])
                err2 = error(orig_data[1], faust_data[1])
                err3 = error(orig_data[2], faust_data[2])
                plot(module+' '+ num+' output 1', orig_data[0], faust_data[0], err1)
                plot(module+' '+ num+' output 2', orig_data[1], faust_data[1], err2)
                plot(module+' '+ num+' output 3', orig_data[2], faust_data[2], err3)
                #print module+' '+ num, '\n', " error output 1 = ", err1, '\n',  " error output 2 = ", err2, '\n', " error output 3 = ", err3       
    #plt.show() dont show graph, they are way too many
if __name__ == '__main__':
    main()
    
