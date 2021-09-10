
t = (0:0.1:(40-0.1))'; % Time
L1 = 2; L2 = 5 ; L3= 3; %Link length
m1 = 5 ; m2 = 2 ; m3 = 0.3 ;  %Link mass
center = [3 ; 2 ; 1];
radius =1.5;
numPts = 400;
points = shapePts(center,radius,numPts,'spiral');  
Tx = points(1,:);
Ty = points(2,:);
Tz = points(3,:);

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
 k11(i,1) = Thelta1;
 k21(i,1) = Thelta2(1);
 k31(i,1) = Thelta3(2);
 k12(i,1) = Thelta1;
 k22(i,1) = Thelta2(2);
 k32(i,1) = Thelta3(1);
end
 

%% Created Timeseries (Motion with Circle Tracking)
%% first Behavior
ts11 = timeseries(k11,t);
ts21 = timeseries(k21,t);
ts31 = timeseries(k31,t);
save('The1Data1','ts11','-v7.3') 
save('The2Data1','ts21','-v7.3') 
save('The3Data1','ts31','-v7.3') 

load The1Data1
load The2Data1
load The3Data1
%% Second Behavior
ts12 = timeseries(k12,t);
ts22 = timeseries(k22,t);
ts32 = timeseries(k32,t);
save('The1Data2','ts12','-v7.3') 
save('The2Data2','ts22','-v7.3') 
save('The3Data2','ts32','-v7.3') 

load The1Data2
load The2Data2
load The3Data2
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
