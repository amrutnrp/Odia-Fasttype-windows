fw = open ('lut1.txt','a')

while ( 1 ) :
    h= input ('enter --->')
    if  h=='q' or h== 'Q': break
    if h== '' or len(h.split())!=2 : continue

    h1, h2 = h.split()

    h1= h1.upper()

    h2 = str(int(h2,16))

    fw.write(h1+ ' , ' + h2+ '\n')

    print (h1+ ' , ' + h2+ '\n')





fw.close()
