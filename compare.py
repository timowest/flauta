import csv

def read(filename):
    f = csv.reader(open(filename, 'rU')) 
    values = []
    for num in f:
        temp = [float(x) for x in num]
        values.append(temp)
    return values
    f.close()

def error(orig_values, faust_values):
    error_out = [abs(orig_values[i]-faust_values[i]) for i in range(0, len(orig_values))]
    average_out = (sum(error_out)) / len(error_out)
    return average_out    

def main():
    modules = ['bernoulli', 'jetdrive','turbulence','vortex']
    one_out_nums = [str(n) for n in [1,2,3,4,5]]
    two_out_nums = [str(n) for n in [11,12,13,14,15,21,22,23,24,25,31,32,33,34,35,41,42,43,44,45,51,52,53,54,55]]
    for i in range(0, len(modules)):
        if i == 0 or i == 1:
            nums = two_out_nums
        elif i == 2 or i == 3:
            nums = one_out_nums
        ##TODO include reseptivity    
        for num in nums:
            ## receptivity has different output count            
            orig_file ='gen/_'+modules[i]+'_out_'+num+'.txt'
            faust_file = 'gen/'+modules[i]+'_out_'+num+'.txt'
            orig_data = read(orig_file)    
            faust_data = read(faust_file)
            if len(orig_data) == 1:
                err1 = error(orig_data[0], faust_data[0])
                print modules[i]+' '+ num, '\n', " error output 1 = ", err1
            elif len(orig_data) == 2:
                err1 = error(orig_data[0], faust_data[0])
                err2 = error(orig_data[1], faust_data[1])
                print modules[i]+' '+ num, '\n', " error output 1 = ", err1, '\n', " error output 2 = ", err2
            elif len(orig_data) == 3:
                err1 = error(orig_data[0], faust_data[0])
                err2 = error(orig_data[1], faust_data[1])
                err3 = error(orig_data[2], faust_data[2])
                print modules[i]+' '+ num, '\n', " error output 1 = ", err1, '\n',  " error output 2 = ", err2, '\n', " error output 3 = ", err3        

if __name__ == '__main__':
    main()
    
