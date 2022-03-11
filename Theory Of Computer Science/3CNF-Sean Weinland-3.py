
# Code by Sean Weinland
#Initalization
B_outputList = []
A_inputList = []
Verify_B_outputList = []
n = 4
m = 2
InitalList = [1, 6, 8, 6, 3, 1]
BruteForceWorked = 0



#Used for clause comaprison
def CLAUSE(ListVar, TestVar):
    if (ListVar < 0):   #Negation, ~[1] = false. 
        if (TestVar == 1):
            return False
        else:
            return True
    else:               #Un-negation, [1] = true.
        if (TestVar == 1):
            return True
        else:
            return False

#This will check each literal
def SpecificLiteral(ListVar, Literal):
    if (ListVar == Literal or ListVar * -1 == Literal):
        return True
    else:
        return False


#Verify list converts the generated/found 0 & 1 values to a true/false list for the VERIFY function
def Generate_VerifyList():
    Verify_B_outputList.clear() #Since it'll be called twice, we clear on entry.
    #Now we set the output list to our output that could work.

    for R in A_inputList:
        if (R < 0):
            R_temp = (R * -1) - 1
        else:
            R_temp = (R) - 1
        if (CLAUSE(R , B_outputList[R_temp]) == True):
            Verify_B_outputList.append(True)
        else:
             Verify_B_outputList.append(False)

#This function will verify each tuple has at least one True, if not it'll return false.
def VERIFY():
    temp = 0
    for R in range(len(InitalList)):
        if (Verify_B_outputList[R] == True):
            temp = 1
        if (R % 3 == 2 and temp == 0):
            return False
            #Since we have one match within the tuple, skip to the next tuple
        if (R % 3 == 2 and temp == 1):
            temp = 0
    #If it never had a non-matching tuple, it works.
    return True        



#Adjust the A list to fit the speicfications of the A-List
for i in (InitalList):
    if( 1 <= i <= (2 * n)):
        if(i <= n):
            A_inputList.append(i * -(1)) 
        if(i > n):
           A_inputList.append(i - n)

#Main Driver, this is a non brute force approach
#I think it's similar to the B-List approach given by the
#canvas brief for making the B-List, but really brute force approach is guaranteed to work.   
for X in range(n):
    Found = False
    for P in (A_inputList):
        #Now we want to check the first 3 literals for any True's
        if (SpecificLiteral(P, X)):
            for R in range(0, 2):
                if (CLAUSE(P, R) == True):
                   B_outputList.append(1)
                   Found = True
                   break
                else:
                   B_outputList.append(0)
                   break
            if (Found == True):
                break




#Verify, but first we have to generate a True/False table
Generate_VerifyList()
#This was my inital approach, however after I implemented my verified functions, this approach was obselete somewhat
if (VERIFY() == True): 
    print("Phi is satisfiable (My inital Approach): ", *B_outputList)  
  



#Brute Force Approach, probably best to grade based off of this.
#In hind sight, the two verify functions do what is wanted for the B-List
print("============")
print("Brute force approach.")
for L in range(0, 2):
    for M in range (0, 2):
        for A in range(0,2):
            for O in range(0,2):
                B_outputList.clear()
                B_outputList.append(L)
                B_outputList.append(M)
                B_outputList.append(A)
                B_outputList.append(O)
                Generate_VerifyList()
                if (VERIFY() == True):
                    print("This also works, ", *B_outputList)
                    BruteForceWorked = 1

if (BruteForceWorked == 0):
    print("Phi is not satisfiable")