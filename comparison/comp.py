import csv
def read(filename):
	f = csv.reader(open(filename, 'rU')) 
	valores =[]
	for num in f:
		temp= [float(x) for x in num]
		valores.append(temp)
	return valores
	f.close()

def error(outC,outF):
	error_out = [outC[i] - outF[i] for i in range(0,len(outC))]
	average_out = (sum(error_out))/len(error_out)
	return average_out	

def main():
	for i in range(0,4):
		if i==0 or i==1:
			num = [11,12,13,14,15,21,22,23,24,25,31,32,33,34,35,41,42,43,44,45,51,52,53,54,55]
		if i==2 or i==3:
			num = [1,2,3,4,5]
		##TODO include reseptivity	
		j=0
		while j < len(num):
			## receptivity has different output count
			modulo = ['bernoulli', 'jetdrive','turbulence','vortex']
			C_file ='C'+modulo[i]+'_out_'+str(num[j])+'.txt'
			F_file = modulo[i]+'_out_'+str(num[j])+'.txt'
			inC= read(C_file)	
			inF= read(F_file)
			if len(inC)==1:
				err1 = error(inC[0], inF[0])
				print modulo[i]+' '+ str(num[j]), '\n', "error output 1 = ", err1
			if len(inC)==2:
				err1 = error(inC[0], inF[0])
				err2 = error(inC[1], inF[1])
				print modulo[i]+' '+ str(num[j]), '\n', "error output 1 = ", err1, '\n', "error output 2 = ", err2
			if len(inC)==3:
				err1 = error(inC[0], inF[0])
				err2 = error(inC[1], inF[1])
				err3 = error(inC[2], inF[2])
				print modulo[i]+' '+ str(num[j]), '\n', " error output 1 = ", err1, '\n',  " error output 2 = ", err2, '\n', " error output 3 = ", err3
			j=j+1

if __name__ == '__main__':
	main()
	
