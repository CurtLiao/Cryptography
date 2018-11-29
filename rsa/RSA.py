
# coding: utf-8

# In[ ]:


from math import gcd
from random import randint,randrange
import sys
import random
import math
import operator

#------------------------------------- function ---------------------------------# 
def egcd(a, b):
    if a == 0:
        return (b, 0, 1)
    else:
        g, y, x = egcd(b % a, a)
        return (g, x - (b // a) * y, y)
def modinv(a, m):
    g, x, y = egcd(a, m)
    if g != 1:
        print("Module inverse doesn't exist")
        return False
    else:
        return x % m

def generateNum(num):                            #generate 512 bits number
    output = ""
    for i in range(num):
        if i ==0 or i == num-1:
            output += '1'
        else:
            temp = randint(0,9)
            output += str(temp % 2)
    return int(output,2)

def square_multiply(n,x):                         #Square & multiply
    ans = 1
    for i in range(len(bin(x))):
        if i == 0 or i == 1:
            continue
        else:
            ans = pow(ans,2)
            if bin(x)[i] == '1':
                ans = ans * n
    return ans

def chinese_remainder(d,p,q,cipher):              #Chinese remainder theorem(CRT)
    dp = d % (p-1)
    dq = d % (q-1)
    
    
    x1 = pow(cipher,dp,p)
    x2 = pow(cipher,dq,q)
    
    qinv = modinv(q,p)
    h = qinv*((x1 - x2)% p)
    h = h % p
    
    plaintext = x2 + h * q
    return plaintext

def miller_rabin_test(n):
    test = n
    lowPrimes = [2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41, 43, 47, 53, 59, 61, 67, 71, 73, 79, 83, 89, 97, 101, 103, 107,109, 
                 113, 127, 131, 137, 139, 149, 151, 157, 163, 167, 173, 179, 181, 191, 193, 197, 199, 211, 223, 227, 229, 233, 239,
                 241, 251, 257, 263, 269, 271, 277, 281, 283, 293, 307, 311, 313, 317, 331, 337, 347, 349, 353, 359, 367, 373, 379,
                 383, 389, 397, 401, 409, 419, 421, 431, 433, 439, 443, 449, 457, 461, 463, 467, 479, 487, 491, 499, 503, 509, 521,
                 523, 541, 547, 557, 563, 569, 571, 577, 587, 593, 599, 601, 607, 613, 617, 619, 631, 641, 643, 647, 653, 659, 661,
                 673, 677, 683, 691, 701, 709, 719, 727, 733, 739, 743, 751, 757, 761, 769, 773, 787, 797, 809, 811, 821, 823, 827,
                 829, 839, 853, 857, 859, 863, 877, 881, 883, 887, 907, 911, 919, 929, 937, 941, 947, 953, 967, 971, 977, 983, 991,
                 997]
    for i in lowPrimes:
        if (test % i == 0):
            return False
    r = 0
    s = n -1
    while s % 2 == 0:
        s = s // 2
        r += 1
    for round in range(20):
        tmp = random.randrange(2, (n-1))   #random number between 2 ~ (n-1)
        v = pow(tmp, s, n)                 # v = tmp^s mod n
        if v != 1 and v != (n-1):           # v !=1 means not pass yet
            for i in range(r):
                if i == (r-1):
                    return False
                else:
                    v = (v**2) % n
                if v == 1:
                    return False
                elif v == (n-1):
                    break
    return True

def getPrime():                               #get 1024bits n, and big prime p,q
    flag = False
    p = 0
    q = 0
    n = 0
    while (miller_rabin_test(p)) == False:     #prime p pass, find prime q
        p = generateNum(512)
    while len(bin(n)) !=1026:                  #prime q pass, make sure length of p*q is 1024 bits, otherwise, find new prime q
        q = generateNum(513)
        if (miller_rabin_test(q) == True):
            n = p*q 
    return p,q,n

def RSAencrypt(plain,pubkey,n):
    cipher = square_multiply(plain,pubkey) % n
    return cipher
def RSAdecrypt(d,p,q,cipher):
    plain = chinese_remainder(d,p,q,cipher)
    return plain

#---------------------------------------main function --------------------------------#
def main():
    plain = input("Please input plaintext: ")
    p,q,n = getPrime()

    d = 0
    x = int("10000000000000001",2)
    while not d:
        phi = (p-1) * (q-1)
        e = 0
        for i in range( x, phi ):                            #find  e (public key) between x ~ phi
            if gcd( i, phi ) == 1:
                e = i
                break
        d = modinv( e, phi )                                 #use e and phi compute d(private key)
        if d != False:
            break
        else:                                                #can't find module inverse, find p,q again
            p,q,n = getPrime()
   
    print("\n#---------------------------------#\n")
    print("Big prime p is: ", p,"\n")
    print("#---------------------------------#\n")
    print("Big prime q is: ", q,"\n")
    print("#---------------------------------#\n")
    print("p*q is: ", p*q,"\n")
    print("#---------------------------------#\n")
    print("Your public key is: ", e,"\n")
    print("Your private key is:\n",d,"\n")
    print("#---------------------------------#\n")
    
    cipher = RSAencrypt(int(plain),e,n)                       #encrypt
    print("ciphertext: ",cipher,"\n")
    
    plaintext = RSAdecrypt(d,p,q,cipher)                          #decrypt
    print("plaintext = ",plaintext)
#--------------------------------------------------------------------------------------#

if __name__ == "__main__":
    main()

