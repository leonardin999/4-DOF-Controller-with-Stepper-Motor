 function [ IK ] = IKSolve( L2,Lep,Tx,Ty,Tz )
 % Denavit-Hartenberg's Parameters

 %% Solutions
  Thelta1 = atan2(Ty ,Tx);
             
  a = Tz;
  b = Tx/cos(Thelta1);
  p2 = (Tx/cos(Thelta1))^2 + (Tz )^2;
  C3 = (p2 - (L2*L2) - (Lep*Lep))/(2*L2*Lep);
  r  =  L2 + Lep*C3;
  Thelta3 = [atan2(sqrt(1 - (C3*C3)), C3);...
             atan2(-(sqrt(1 -(C3*C3))),C3)];
          
  u1 = a + sqrt( a^2 + b^2 - r^2);
  u2 = a - sqrt( a^2 + b^2 - r^2);
  c = r + b;
  Thelta2 = [2*atan2(u1,c);...
             2*atan2(u2,c)];
  Thelta1_1 = atan2(Ty ,Tx);
             
  a = Tz ;
  b = Tx/cos(Thelta1_1);
  p2 = (Tx/cos(Thelta1_1))^2 + (Tz )^2;
  C3 = (p2 - (L2*L2) - (Lep*Lep))/(2*L2*Lep);
  r  =  L2 + Lep*C3;
  Thelta3_1 = [atan2(sqrt(1 - (C3*C3)), C3);...
             atan2(-(sqrt(1 -(C3*C3))),C3)];
          
  u1 = a + sqrt( a^2 + b^2 - r^2);
  u2 = a - sqrt( a^2 + b^2 - r^2);
  c = r + b;
  Thelta2_1 = [2*atan2(u1,c);...
               2*atan2(u2,c)];

 %Therefore, we have a total eight solutions (elbow up and down for joint-2 and joint-3) 
    %[Thelta1  Thelta2    Thelta3]
  Sol1 = [Thelta1   ;  Thelta2(1)  ;   Thelta3(1)]
  Sol2 = [Thelta1   ;  Thelta2(1)  ;   Thelta3(2)]
  Sol3 = [Thelta1   ;  Thelta2(2)  ;   Thelta3(1)]
  Sol4 = [Thelta1   ;  Thelta2(2)  ;   Thelta3(2)]
  Sol5 = [Thelta1_1   ;  Thelta2_1(1)  ;   Thelta3_1(1)]
  Sol6 = [Thelta1_1   ;  Thelta2_1(1)  ;   Thelta3_1(2)]
  Sol7 = [Thelta1_1   ;  Thelta2_1(2)  ;   Thelta3_1(1)]
  Sol8 = [Thelta1_1   ;  Thelta2_1(2)  ;   Thelta3_1(2)]
  
  
  
  Thelta1 = Sol2(1);
  Thelta2 = Sol2(2);
  Thelta3 = Sol2(3);
T01 = [ cos(Thelta1), -sin(Thelta1), 0,  0;...
        sin(Thelta1),  cos(Thelta1), 0,  0;...
                0,          0, 1,  0;...
                0,          0, 0,  1];
T12 = [ cos(Thelta2), -sin(Thelta2), 0,  0;...
                0,          0, -1,  0;...
        sin(Thelta2), cos(Thelta2), 0,  0;...
                0,          0, 0,  1];
T23 = [ cos(Thelta3), -sin(Thelta3), 0,  L2;...
        sin(Thelta3),  cos(Thelta3), 0,  0;...
                0,          0, 1,  0;...
                0,          0, 0,  1];
T3EE = [        1,          0, 0,  Lep;...
                0,          1, 0,  0;...
                0,          0, 1,  0;...
                0,          0, 0,  1];
%  T02 = T01*T12
%  T03 = T01*T12*T23
 T0EE = T01*T12*T23*T3EE;
 PEE = [T0EE(1,4) ; T0EE(2,4) ; T0EE(3,4)];
  figure() 
  %% plotting the initial frame

init_frame=[4   4    4   1 ; 0 0 0 1];
        plot3(init_frame(:,1),[0;0],[0;0],'r','LineWidth',3)
        hold on
        plot3([0;0],init_frame(:,2),[0;0],'g','LineWidth',3)
        hold on
        plot3([0;0],[0;0],init_frame(:,3),'b','LineWidth',3)
        hold on
        plot3([0;0],[0;0],[0;0],'ok','MarkerFaceColor','k')
        hold on
 %% plotting the  XYZ 3D End-Point
        plot3(PEE(1),PEE(2),PEE(3),'or','MarkerFaceColor','k') 
        hold on
        plot3(Tx,Ty,Tz,'ok','MarkerFaceColor','k') 
        hold on
text(PEE(1),PEE(2),PEE(3),['  End-Point:(', num2str(PEE(1),3), ', ', num2str(PEE(2),3),', ', num2str(PEE(3),3), ')']);
 title('End-Point Simulation with Inverse Kinematics')
    xlabel('X');
    ylabel('Y');
    zlabel('Z');
%  axis([-20 20 -20  20 -20 20]) %set x y z axis size according to the problem
  view(3) 
  grid on
  rotate3d on
 IK = [Thelta1;...
       Thelta2;...
       Thelta3]
       