Dict = {'E':1,'D':2,'C':3,'B':4,'A':5,'G':6,'f':7,'e':8,'d':9,'c':10,'b':11,'a':12,'g':13}

def change(text):
    a=[]
    for i in range(16):
        a.append("0")
    for char in text:
        index = Dict.get(char) - 1
        a[index] = "1"
    s="".join(a)
    return(s)

    
fh = open("happy birthday_notes-1.txt", "r")
gh = open("envisage.txt" , "w")
mylist = fh.read().splitlines()
for line in mylist:
    b = change(line)
    print(b)
    gh.write(b+"\n")
    #gh.write('\n')
fh.close()
gh.close()
