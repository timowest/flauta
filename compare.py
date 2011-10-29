import csv

def read(filename):
	f = csv.reader(open(filename, 'rU')) 
	values = []
	for num in f:
		temp = [float(x) for x in num]
		values.append(temp)
	return values
	f.close()

def error(outC, outF):
	error_out = [abs(outC[i]-outF[i]) for i in range(0, len(outC))]
	average_out = (sum(error_out)) / len(error_out)
	return average_out	

def main():
	for i in range(0, 4):
		if i == 0 or i == 1:
			num = [11,12,13,14,15,21,22,23,24,25,31,32,33,34,35,41,42,43,44,45,51,52,53,54,55]
		elif i == 2 or i == 3:
			num = [1,2,3,4,5]
		##TODO include reseptivity	
		j=0
		while j < len(num):
			## receptivity has different output count
			module = ['bernoulli', 'jetdrive','turbulence','vortex']
			orig_file ='gen/_'+module[i]+'_out_'+str(num[j])+'.txt'
			faust_file = 'gen/'+module[i]+'_out_'+str(num[j])+'.txt'
			orig_data = read(orig_file)	
			faust_data = read(faust_file)
			if len(orig_data) == 1:
				err1 = error(orig_data[0], faust_data[0])
				print module[i]+' '+ str(num[j]), '\n', " error output 1 = ", err1
			elif len(orig_data) == 2:
				err1 = error(orig_data[0], faust_data[0])
				err2 = error(orig_data[1], faust_data[1])
				print module[i]+' '+ str(num[j]), '\n', " error output 1 = ", err1, '\n', " error output 2 = ", err2
			elif len(orig_data) == 3:
				err1 = error(orig_data[0], faust_data[0])
				err2 = error(orig_data[1], faust_data[1])
				err3 = error(orig_data[2], faust_data[2])
				print module[i]+' '+ str(num[j]), '\n', " error output 1 = ", err1, '\n',  " error output 2 = ", err2, '\n', " error output 3 = ", err3
			j=j+1

if __name__ == '__main__':
	main()
	
