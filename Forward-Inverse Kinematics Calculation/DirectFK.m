function [ FK ] = DirectFK(L1,L2,L3,the1,the2,the3 )
 %syms L1  L2  L3 the1 the2 the3; %Symbolics for links-Leight & Joint-Angle

%DHMATRIX Summary of this function goes here
%     (alp)            (di)        (ai)          (qi)
%   Link twist     Link Offset    Link Leight   Joint variable
% DH = [ 0                0            L1             the1;...       %frame1
%        pi/2             0             0             the2;...       %frame2
%        0                L2            0             the3;...       %frame3 
%        0                Lep           0               0];          %End-point

   % Joint frame with respect to the world coordinates.
T01 = [ cos(the1), -sin(the1), 0,  0;...
        sin(the1),  cos(the1), 0,  0;...
                0,          0, 1,  L1;...
                0,          0, 0,  1]
T12 = [ cos(the2), -sin(the2), 0,  0;...
                0,         0,  1,  0;...
        sin(the2), cos(the2),  0,  0;...
                0,         0,  0,  1];
T23 = [ cos(the3), -sin(the3), 0,  L2;...
        sin(the3),  cos(the3), 0,  0;...
                0,          0, 1,  0;...
                0,          0, 0,  1];
T3EE = [        1,          0, 0,  L3;...
                0,          1, 0,  0;...
                0,          0, 1,  0;...
                0,          0, 0,  1];
 T02 = T01*T12
 T03 = T01*T12*T23
 T0EE = T01*T12*T23*T3EE;
 PEE = [T0EE(1,4) ; T0EE(2,4) ; T0EE(3,4)]
 figure()
 %% plotting the initial frame

init_frame=[2   2    2   1 ; 0 0 0 1];
        plot3(init_frame(:,1),[0;0],[0;0],'g','LineWidth',2)
        hold on
        plot3([0;0],init_frame(:,2),[0;0],'g','LineWidth',2)
        hold on
        plot3([0;0],[0;0],init_frame(:,3),'g','LineWidth',2)
        hold on
        plot3([0;0],[0;0],[0;0],'ok','MarkerFaceColor','k')
        hold on
 
%% plotting the first joint in the z direction (DH rule)
plot3([0;T01(1,4)],[0;T01(2,4)],[0;T01(3,4)],'-Or',...
      [T01(1,4);T02(1,4)],[T01(2,4);T02(2,4)],[T01(3,4);T02(3,4)],'-Ok',...
      [T02(1,4);T03(1,4)],[T02(2,4);T03(2,4)],[T02(3,4);T03(3,4)],'-Ok',...
      [T03(1,4);PEE(1)],[T03(2,4);PEE(2)],[T03(3,4);PEE(3)],'-Ob','linewidth',3)
        plot3(PEE(1),PEE(2),PEE(3),'ok','MarkerFaceColor','k') 
        text(PEE(1),PEE(2),PEE(3),['  (', num2str(PEE(1),3), ', ', num2str(PEE(2),3),', ', num2str(PEE(3),3), ')']);
        hold on
 title('Forward Kinematic Simulation 3d)')
    xlabel('X Axis');
    ylabel('Y Axis');
    zlabel('Z Axis');
%  axis([-20 20 -20  20 -20  20]) %set x y z axis size according to the problem
  view(3) 
  grid on
  rotate3d on
 FK = [T0EE(1,4) ; T0EE(2,4) ; T0EE(3,4)];
