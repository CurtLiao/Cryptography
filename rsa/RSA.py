
# coding: utf-8

# In[ ]:


from math import gcd
from random import randint
import sys
import random
import math
import operator

def egcd(a, b):
    if a == 0:
        return (b, 0, 1)
    else:
        g, y, x = egcd(b % a, a)
        return (g, x - (b // a) * y, y)
def modinv(a, m):
    g, x, y = egcd(a, m)
    if g != 1:
        raise Exception('modular inverse does not exist')
    else:
        return x % m

#------------------------------------- function ---------------------------------# 
def findprime():
    prime = []
    for j in range(2):
        temp = ""
        for i in range(512):
            if i == 0 or i == 511:
                temp += '1'
            else:
                x = randint(0,9)
                temp += str(x %2)
        prime.append(temp)
    n = int(prime[0],2) * int(prime[1],2)
    output = bin(n)[2:]
    return prime[0],prime[1],output

def square_multiply(n,x):
    ans = 1
    for i in range(len(bin(x))):
        if i == 0 or i == 1:
            continue
        else:
            ans = pow(ans,2)
            if bin(x)[i] == '1':
                ans = ans * n
    return ans

def miller_rabin_test(n):
    r, s = 0, n - 1
    while s % 2 == 0:
        r += 1
        s = s // 2   
    for round in range(5):
        tmp = random.randrange(2, s)   #random number vetween 2 ~ (n-1)
        v = pow(tmp, s, n)             # v = tmp^s mod n 
        if v != 1:                     # v !=1 means not pass yet
            i = 0
            while v != (n - 1):        # v != (n-1) means not pass yet
                if i == r - 1:
                    return False
                else:
                    i = i + 1
                    v = (v ** 2) % n
    return True

def RSAencrypt(plain,pubkey,n):
    cipher = square_multiply(plain,pubkey) % n
    return cipher
def RSAdecrypt(cipher,prikey,n):
    plain = pow(cipher,prikey,n)
    return plain
#---------------------------------------main function --------------------------------#
def main():
    plain = input("Please input plaintext: ")
    n = False
    count = 0
    while not n:
        count+=1
        p,q,n = findprime()
        if len(n) != 1024:
            continue
        elif n[0] != '1' or n[1023] != '1':
            continue
        else:
            if miller_rabin_test(int(n,2)) != True:
                continue
            else:
                n == True
    print("\n#---------------------------------#\n")
    print("Big prime p is: ", p,"\n")
    print("#---------------------------------#\n")
    print("Big prime q is: ", q,"\n")
    print("#---------------------------------#\n")
    print("p*q is: ", n,"\n")
    print("#---------------------------------#\n")
    
    p, q, n = int(p,2), int(q,2), int(n,2)               #轉 10 進制
    phi = (p-1) * (q-1)
    x = int("011",2)
    e = 0
    for i in range( x, phi ):                            #在 x ~ phi 中找 e(public key)
        if gcd( i, phi ) == 1:
            e = i
            break
    d = modinv( e, phi )                                 #用 e 和 phi 算出 d(private key)
   

    print("Your public key is: ", e,"\n")
    print("Your private key is: ", d,"\n")
    print("#---------------------------------#\n")
    
    cipher = RSAencrypt(int(plain),e,n)
    print("cipher: ",cipher,"\n")
    
    dp = d % (p-1)
    dq = d % (q-1)

    m1 = pow(int(cipher),dp,p)
    m2 = pow(int(cipher),dq,q)
    
    qinv = modinv(q,p)
    h = qinv*((m1 - m2)% p)
    h = h % p
    
    m = m2 +h*q
#--------------------------------------------------------------------------------------#

if __name__ == "__main__":
    d,p = main()

