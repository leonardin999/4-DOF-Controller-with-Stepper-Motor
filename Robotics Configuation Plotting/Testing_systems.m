%Testing Forward and Inverse Kinematics
syms Thelta
 L2 = 5
 Lep= 3
 Tx = 4
 Ty = 3
 Tz = 1
Thelta = IKSolve(L2,Lep,Tx,Ty,Tz)
% thel = IKCal(L1,L2,Lep,Tx,Ty,Tz)
PEE = DirectFK(L1,L2,Lep,Thelta(1),Thelta(2),Thelta(3))
