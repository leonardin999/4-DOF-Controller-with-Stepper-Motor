the1 = out.Theta.signals(1).values;
the2 = out.Theta.signals(2).values;
the3 = out.Theta.signals(3).values;
t = out.Theta.time;

%% position
%Position1:
L1 = 3; L2 = 5; L3= 1.5;     %Link length
m1 = 5 ; m2 = 2 ; m3 = 0.3 ; %Link mass
x1 = 0;
y1 = 0;
z1 = L1;

%Position2:
x2 = x1 + L2.*cos(the1).*cos(the2);
y2 = y1 + L2.*cos(the2).*sin(the1);
z2 = z1 + L2.*sin(the2);

%Position3:
x3 = x2 + L3.*(cos(the1).*cos(the2+the3));
y3 = y2 + L3.*(sin(the1).*cos(the2+the3));
z3 = z2 + L3.*(sin(the2+the3));
 

figure
for i = 1: length(the1)
%     t1 = (0:0.1:20)'; % Time
%    count = length(t1);
%    center = [0  0  0];
%    radius = 0.5;
%    theta = t1*(2*pi/t1(end));
%    points = center + radius*[cos(theta) sin(theta) zeros(size(theta))];
%       plot3(points(:,1),points(:,2),points(:,3),'k','linewidth',5)
%       hold on  
  plot3([x1;x2(i)],[y1;y2(i)],[z1;z2(i)],'-or',...
        [x2(i);x3(i)],[y2(i);y3(i)],[z2(i);z3(i)],'-ob',...
        [0;x1],[0;y1],[0;z1],'-Ok','linewidth',3)
%   plot3(x3(i),z3(i),y3(i),'ok','MarkerFaceColor','k') 
       text(x3(i),y3(i),z3(i),['  (', num2str(x3(i),1), ', ', num2str(y3(i),1),', ', num2str(z3(i),1), ')']);
   hold off
   
    xlabel('X Axis');
    ylabel('Y Axis');
    zlabel('Z Axis');
  axis([-10 10 -10  10  -10  10]) %set x y z axis size according to the problem
  grid on
  view(3) 
  rotate3d on
 pause(0.001);
%  hold on;
end