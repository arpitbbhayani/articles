while 1:
	n,s,d=raw_input().partition(' ')
	if n=="0" and d=="0":
		break
	else:
		print (int(n)**(int(d)))
