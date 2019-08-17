a=int(raw_input())
for i in range(0,a):
	b=int(raw_input())
	if (b-1)%4==0:
		str1="192"
	elif (b-1)%4==1:
		str1="442"
	elif (b-1)%4==2:
		str1="692"
	else :
		str1="942"
	if b<=4:
		print str1
	else:
		str2=str((b-1)/4)
		print str2+str1
