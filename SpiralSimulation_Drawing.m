syms i ;
t = (0:0.1:(10-0.1))'; % Time
L1 = 2; L2 = 5 ; L3= 5; %Link length
m1 = 5 ; m2 = 2 ; m3 = 0.3 ;  %Link mass
center = [3 ; 2 ; 1];
radius =1;
numPts = 100;
points = shapePts(center,radius,numPts,'spiral');  
Tx = points(1,:);
Ty = points(2,:);
Tz = points(3,:);

figure(1)
    
%    plot3(center(1),center(2),center(3),'ok','MarkerFaceColor','k') 
    
    hold on 
    grid on
    view(3)
%% Inverse Kinematics 

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
x2 = x1 + L2.*cos(Sol2(1)).*cos(Sol2(2));
y2 = y1 + L2.*cos(Sol2(2)).*sin(Sol2(1));
z2 = z1 + L2.*sin(Sol2(2));

%Position3:
x3 = x2 + L3.*(cos(Sol2(1)).*cos(Sol2(2)+Sol2(3)));
y3 = y2 + L3.*(sin(Sol2(1)).*cos(Sol2(2)+Sol2(3)));
z3 = z2 + L3.*(sin(Sol2(2)+Sol2(3)));

for k = 1: length(x3)
      plot3(points(1,:),points(2,:),points(3,:),'r','linewidth',2)
      hold on   
   plot3([x1;x2(k)],[y1;y2(k)],[z1;z2(k)],'-Or',...
         [x2(k);x3(k)],[y2(k);y3(k)],[z2(k);z3(k)],'-Ob',...
        [0;x1],[0;y1],[0;z1],'-Ok','linewidth',3)
    
     hold on
   plot3(x3(k),y3(k),z3(k),'ok','MarkerFaceColor','k') 
    hold off
      drawing = animatedline('linestyle','none','marker','.');
      addpoints(drawing,points(1,:),points(2,:),points(3,:))
   
    xlabel('X Axis');
    ylabel('Y Axis');
    zlabel('Z Axis');
  %  axis([-10 10 -10  10 -10  10]) %set x y z axis size according to the problem
  grid on
  view(3) 
  
   rotate3d on
   pause(0.0001);
  % title(num2str(t,'time = %4.3f (sec)')); 
  %  hold on;
 
end
end  
% close(obj);
%% Created Timeseries (Motion with Circle Tracking)

function pts = shapePts(center,radius,numPts,type)    
switch type
    case 'circle'
        pts = repmat(center,[1,numPts]) + ...
                     [radius*cosd(linspace(0,360,numPts));
                      radius*sind(linspace(0,360,numPts));
                                          zeros(1,numPts)];
    case 'square'
        c    = repmat(center,[1,numPts]);  
        r    = repmat(radius,[1,numPts/4]);
        span = linspace(-radius,radius,numPts/4);
        pts  = c +  [span,      r,  -span,     -r;
                       -r,   span,      r,  -span;
                                 zeros(1,numPts)];
    case 'flower'
        pts = repmat(center,[1,numPts]) + radius* ...
            [cosd(linspace(0,720,numPts)).*cosd(linspace(0,360,numPts));
             cosd(linspace(0,720,numPts)).*sind(linspace(0,360,numPts));
                                                       zeros(1,numPts)];
    case 'spiral'
        angles = linspace(  0,   5*pi,numPts);
        rVec   = linspace(.01, radius,numPts);
        pts    = repmat(center,[1,numPts]) + [rVec.*cos(angles);
                                              rVec.*sin(angles);
                                              zeros(1,numPts)];
end
end
