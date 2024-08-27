import numpy as np



def bandpass(C1,R4,fl,fh):
    f0 = np.sqrt(fl*fh)
    Q = f0/(fh-fl)
    H = 1/3.0*(6.5-1.0/Q)
    k = 2*np.pi*f0*C1
    R5 = R4/(H-1)
    C2 = 1/2.0*C1
    R1 = 2.0/k
    R2 = 2.0/(3.0*k)
    R3 = 4.0/k
    print('f0=',f0)
    print('R1=',R1)
    print('R2=',R2)
    print('R3=',R3)
    print('R4=',R4)
    print('R5=',R5)
    print('C1=',C1)
    print('C2=',C2)




def bandpass_mfb(C,f0,B,Kp):
    Q = f0/B
    w0 = 2*np.pi*f0
    R3 = 2*Q/(w0*C)
    R1 = Q/(Kp*w0*C)
    R2 = Q/((2*Q*Q-Kp)*w0*C)
    C1 = C
    C2 = C
    print('R1=',R1)
    print('R2=',R2)
    print('R3=',R3)
    print('C1=',C1)
    print('C2=',C2)

def cal(C,f,q):
    R2=(1-q)/(C*f*0.693)
    R1=q/(C*f*0.693)
    print(R1)
    print(R2)

def cal_lc(f0,C):
    L = 1/(4*np.pi*np.pi*f0*f0*C)
    print(L*1e12,'pF')
# bandpass_mfb(47e-12,250e3,10e3,10)

cal_lc(250e3,622*1e-6)
