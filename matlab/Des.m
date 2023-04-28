function  Xe=Des(q1,q2,q3, flag)
%Functia reprezinta configuratia structurii
% Date de intrare: valoarea coordonatelor generalizate q1,q2, q3 [rad]
%                  utilizarea in regim de desen sau animatie flag==1 desen

t1=[0;0;0];
t2=[.092;0;0];
t3=[.11;0;0];
t4=[.055;0;0];

% de la 1-0

R1_0=[cos(q1), -sin(q1), 0;...
      sin(q1), cos(q1), 0;...
      0, 0, 1];
T1_0=[R1_0,t1;...
      zeros(1,3),1];
% de la 2-1
R2_1=[cos(q2), -sin(q2), 0;...
      sin(q2), cos(q2), 0;...
      0, 0, 1];
T2_1=[R2_1,t2;...
      zeros(1,3),1];

% de la 3-2
R3_2=[cos(q3), 0, sin(q3);...
      0, 1, 0;...
      -sin(q3), 0, cos(q3)];
T3_2=[R3_2,t3;...
      zeros(1,3),1];

% prehensor
R4_3=eye(3,3);
T4_3=[R4_3,t4;...
    zeros(1,3),1];

% Transformarile omogene Ti_0 de la i la 0
T2_0=T1_0*T2_1;
T3_0=T2_0*T3_2;
T4_0=T3_0*T4_3;

% elementele
E1=[T1_0(1:3,4),T2_0(1:3,4)];
E2=[T2_0(1:3,4),T3_0(1:3,4)];
E3=[T3_0(1:3,4),T4_0(1:3,4)];

% versorii cuplelor
s=.25; % factor de scara
s2=.25;
w1_0=s*T1_0(1:3,3);
w2_0=s*T2_0(1:3,3);
w3_0=s*T3_0(1:3,2);
w4_0=s*T4_0(1:3,1);

V1=[T1_0(1:3,4),T1_0(1:3,4)+w1_0];
V2=[T2_0(1:3,4),T2_0(1:3,4)+w2_0];
V3=[T3_0(1:3,4),T3_0(1:3,4)+w3_0];
V4=[T4_0(1:3,4),T4_0(1:3,4)+w4_0];

C1=[T1_0(1:3,4)-s2*w1_0,T1_0(1:3,4)+s2*w1_0];
C2=[T2_0(1:3,4)-s2*w2_0,T2_0(1:3,4)+s2*w2_0];
C3=[T3_0(1:3,4)-s2*w3_0,T3_0(1:3,4)+s2*w3_0];
C4=[T4_0(1:3,4)-s2*w4_0,T4_0(1:3,4)+s2*w4_0];

V4x=[T4_0(1:3,4),T4_0(1:3,4)+s*T4_0(1:3,1)];
V4y=[T4_0(1:3,4),T4_0(1:3,4)+s*T4_0(1:3,2)];
V4z=[T4_0(1:3,4),T4_0(1:3,4)+s*T4_0(1:3,3)];

V3x=[T3_0(1:3,4),T3_0(1:3,4)+s*T3_0(1:3,1)];
V3y=[T3_0(1:3,4),T3_0(1:3,4)+s*T3_0(1:3,2)];
V3z=[T3_0(1:3,4),T3_0(1:3,4)+s*T3_0(1:3,3)];

V2x=[T2_0(1:3,4),T2_0(1:3,4)+s*T2_0(1:3,1)];
V2y=[T2_0(1:3,4),T2_0(1:3,4)+s*T2_0(1:3,2)];
V2z=[T2_0(1:3,4),T2_0(1:3,4)+s*T2_0(1:3,3)];


if flag==1
    figure 
    hold
    plot3(E1(1,:),E1(2,:),E1(3,:),'LineWidth',4,'Color','b')
    plot3(E2(1,:),E2(2,:),E2(3,:),'LineWidth',4,'Color','b')
    plot3(E3(1,:),E3(2,:),E3(3,:),'LineWidth',4,'Color','b')


 %   plot3(E1(1,1)',E1(2,1)',E1(3,1)','o','MarkerSize',12,'MarkerFaceColor','k')
 %   plot3(E1(1,2)',E1(2,2)',E1(3,2)','o','MarkerSize',12,'MarkerFaceColor','r')

    plot3(C1(1,:),C1(2,:),C1(3,:),'LineWidth',6,'Color','k','LineStyle','-')
    plot3(C2(1,:),C2(2,:),C2(3,:),'LineWidth',6,'Color','k','LineStyle','-')
    plot3(C3(1,:),C3(2,:),C3(3,:),'LineWidth',6,'Color','k','LineStyle','-')
    plot3(C4(1,:),C4(2,:),C4(3,:),'LineWidth',6,'Color','k','LineStyle','-')
    

    plot3([0,s],[0,0],[0,0],'LineWidth',1,'Color','r')
    plot3([0,0],[0,s],[0,0],'LineWidth',1,'Color','g')
    plot3([0,0],[0,0],[0,1.5*s],'LineWidth',1,'Color','b')

    plot3(V4x(1,:),V4x(2,:),V4x(3,:),'LineWidth',1,'Color','r','LineStyle','-.')
    plot3(V4y(1,:),V4y(2,:),V4y(3,:),'LineWidth',1,'Color','g','LineStyle','-.')
    plot3(V4z(1,:),V4z(2,:),V4z(3,:),'LineWidth',1,'Color','b','LineStyle','-.')

    plot3(V3x(1,:),V3x(2,:),V3x(3,:),'LineWidth',1,'Color','r','LineStyle','-.')
    plot3(V3y(1,:),V3y(2,:),V3y(3,:),'LineWidth',1,'Color','g','LineStyle','-.')
    plot3(V3z(1,:),V3z(2,:),V3z(3,:),'LineWidth',1,'Color','b','LineStyle','-.')

    plot3(V2x(1,:),V2x(2,:),V2x(3,:),'LineWidth',1,'Color','r','LineStyle','-.')
    plot3(V2y(1,:),V2y(2,:),V2y(3,:),'LineWidth',1,'Color','g','LineStyle','-.')
    plot3(V2z(1,:),V2z(2,:),V2z(3,:),'LineWidth',1,'Color','b','LineStyle','-.')


    plot3(V1(1,:),V1(2,:),V1(3,:),'LineWidth',3,'Color','c','LineStyle','--')
    plot3(V2(1,:),V2(2,:),V2(3,:),'LineWidth',3,'Color','c','LineStyle','--')
    plot3(V3(1,:),V3(2,:),V3(3,:),'LineWidth',3,'Color','c','LineStyle','--')
    
%   plot3(E2(1,2)',E2(2,2)',E2(3,2)','s','MarkerSize',10,'MarkerFaceColor','k')

    xlabel 'x'
    ylabel 'y'
    zlabel 'z'
    grid
    axis([-.21,.21,-.21,.21,-.11,.11])
    axis 'equal'
    view (45,45)
elseif flag==0
    plot3(E1(1,:),E1(2,:),E1(3,:),'LineWidth',4,'Color','b')
    plot3(E2(1,:),E2(2,:),E2(3,:),'LineWidth',4,'Color','b')
    plot3(E3(1,:),E3(2,:),E3(3,:),'LineWidth',4,'Color','b')

    plot3(C1(1,:),C1(2,:),C1(3,:),'LineWidth',6,'Color','k','LineStyle','-')
    plot3(C2(1,:),C2(2,:),C2(3,:),'LineWidth',6,'Color','k','LineStyle','-')
    plot3(C3(1,:),C3(2,:),C3(3,:),'LineWidth',6,'Color','k','LineStyle','-')
    plot3(C4(1,:),C4(2,:),C4(3,:),'LineWidth',6,'Color','k','LineStyle','-')

    plot3([0,s],[0,0],[0,0],'LineWidth',1,'Color','r')
    plot3([0,0],[0,s],[0,0],'LineWidth',1,'Color','g')
    plot3([0,0],[0,0],[0,1.5*s],'LineWidth',1,'Color','b')

    plot4(V4x(1,:),V4x(2,:),V4x(3,:),'LineWidth',1,'Color','r','LineStyle','-.')
    plot4(V4y(1,:),V4y(2,:),V4y(3,:),'LineWidth',1,'Color','g','LineStyle','-.')
    plot4(V4z(1,:),V4z(2,:),V4z(3,:),'LineWidth',1,'Color','b','LineStyle','-.')

    plot3(V3x(1,:),V3x(2,:),V3x(3,:),'LineWidth',1,'Color','r','LineStyle','-.')
    plot3(V3y(1,:),V3y(2,:),V3y(3,:),'LineWidth',1,'Color','g','LineStyle','-.')
    plot3(V3z(1,:),V3z(2,:),V3z(3,:),'LineWidth',1,'Color','b','LineStyle','-.')

    plot3(V2x(1,:),V2x(2,:),V2x(3,:),'LineWidth',1,'Color','r','LineStyle','-.')
    plot3(V2y(1,:),V2y(2,:),V2y(3,:),'LineWidth',1,'Color','g','LineStyle','-.')
    plot3(V2z(1,:),V2z(2,:),V2z(3,:),'LineWidth',1,'Color','b','LineStyle','-.')


    plot3(V1(1,:),V1(2,:),V1(3,:),'LineWidth',3,'Color','c','LineStyle','--')
    plot3(V2(1,:),V2(2,:),V2(3,:),'LineWidth',3,'Color','c','LineStyle','--')
    plot3(V3(1,:),V3(2,:),V3(3,:),'LineWidth',3,'Color','c','LineStyle','--')

    %plot3(E1(1,1)',E1(2,1)',E1(3,1)','o','MarkerSize',12,'MarkerFaceColor','k')
    %plot3(E1(1,2)',E1(2,2)',E1(3,2)','o','MarkerSize',12,'MarkerFaceColor','r')
    %plot3(E2(1,2)',E2(2,2)',E2(3,2)','s','MarkerSize',10,'MarkerFaceColor','k')
else
end
Xe=T4_0(1:3,4);
end