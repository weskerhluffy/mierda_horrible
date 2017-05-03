import sys
if __name__ == "__main__":
	lineas = list(sys.stdin)
	num_lineas=len(lineas)
	num_cacasos = int(lineas[0])
	print("el num de cacasos %u" % num_cacasos)

	idx_linea=1
	for idx_caso in range(num_cacasos):
		(num_numeros,num_casos)=[int(x) for x in lineas[idx_linea].strip().split(" ")]
		print("num nums %u num caca %u"%(num_numeros,num_casos))
		idx_linea+=1
		mierda=[0]*num_numeros
		for caso_act in range(num_casos):
			tipo_cons=lineas[idx_linea][0]
			if(tipo_cons=="0"):
				(_,idx_ini,idx_fin,nuevo_val)=[int(x) for x in lineas[idx_linea].strip().split(" ")]
				print("actualizacion %u-%u de %u"%(idx_ini,idx_fin,nuevo_val))
			else:
				(_,idx_ini,idx_fin)=[int(x) for x in lineas[idx_linea].strip().split(" ")]
				print("actualizacion %u-%u"%(idx_ini,idx_fin))
			idx_linea+=1
