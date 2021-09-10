%% tranjactory Direction:
t = (0:0.1:10)'; % Time
L1 = 2; L2 = 5; L3= 3;     %Link length
% Tx = 4; Ty = 3 ;Tz = 1
m1 = 5 ; m2 = 2 ; m3 = 0.3 ; %Link mass
%% Circle Transjactory
count = length(t);
center = [3  2  1];
radius = 1;
theta = t*(6*pi/t(end));
points = center + radius*[cos(theta) sin(theta) zeros(size(theta))];
Tx = points(:,1);
Ty = points(:,2);
Tz = points(:,3);
figure(1)
    plot3(points(:,1),points(:,2),points(:,3),'k','linewidth',2)
    hold on
   plot3(center(1),center(2),center(3),'ok','MarkerFaceColor','k') 
    hold on 
    grid on
    view(3)
%% Inverse Kinematics 
obj =VideoWriter('CircleDrawing.avi');
obj.Quality=100;
obj.FrameRate = 10;
obj.open()
for i = 1:length(Tx)
  Thelta1 = atan2(Ty(i),Tx(i));
  a = Tz(i) - L1;
  b = Tx(i)/cos(Thelta1);
  p2 = (Tx(i)/cos(Thelta1)).^2 + (Tz(i) - L1).^2;
  C3 = (p2 - (L2.*L2) - (L3.*L3))/(2.*L2.*L3);
  r  =  L2 + L3.*C3;
  Thelta3 = [atan2(sqrt(1 - (C3.*C3)), C3);...
             atan2(-(sqrt(1 -(C3.*C3))),C3)];
          
  u1 = a + sqrt( a.^2 + b.^2 - r.^2);
  u2 = a - sqrt( a.^2 + b.^2 - r.^2);
  c = r + b;
  Thelta2 = [2*atan2(u1,c);...
             2*atan2(u2,c)];

 %Therefore, we have a total two solutions (elbow up and down for joint-2 and joint-3) 
    %[Thelta1  Thelta2    Thelta3]
     Sol1 = [Thelta1   ;  Thelta2(1)  ;   Thelta3(1)];
     Sol2 = [Thelta1   ;  Thelta2(1)  ;   Thelta3(2)];
     Sol3 = [Thelta1   ;  Thelta2(2)  ;   Thelta3(1)];
     Sol4 = [Thelta1   ;  Thelta2(2)  ;   Thelta3(2)];

x1 = 0;
y1 = 0;
z1 = L1;

%Position2:
x2 = x1 +  -d1*cosd(the1);
y2 = y1 +  -d1*sind(the1);
z2 = z1 + L2.*sin(Sol2(2));

%Position3:
x3 = x2 + L3.*(cos(Sol2(1)).*cos(Sol2(2)+Sol2(3)));
y3 = y2 + L3.*(sin(Sol2(1)).*cos(Sol2(2)+Sol2(3)));
z3 = z2 + L3.*(sin(Sol2(2)+Sol2(3)));

for k = 1: length(x3)
      plot3(points(:,1),points(:,2),points(:,3),'r','linewidth',2)
      hold on   
   plot3([x1;x2(k)],[y1;y2(k)],[z1;z2(k)],'-Or',...
         [x2(k);x3(k)],[y2(k);y3(k)],[z2(k);z3(k)],'-Ob',...
        [0;x1],[0;y1],[0;z1],'-Ok','linewidth',3)
    
     hold on
   plot3(x3(k),y3(k),z3(k),'ok','MarkerFaceColor','k') 
    hold off
      drawing = animatedline('linestyle','none','marker','.');
      addpoints(drawing,points(:,1),points(:,2),points(:,3))
   
    xlabel('X Axis');
    ylabel('Y Axis');
    zlabel('Z Axis');
    axis([-6 6  -6  6  -6  6]) %set x y z axis size according to the problem
  grid on
  view(3) 
  
  rotate3d on
  %title(num2str(t,'time = %4.3f (sec)'));
  pause(0.0001);
   %hold on; 
end
end  
obj.close();


    
    
