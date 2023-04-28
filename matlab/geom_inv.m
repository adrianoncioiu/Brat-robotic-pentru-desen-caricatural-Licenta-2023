function q = geom_inv(q,x)
%UNTITLED3 Summary of this function goes here
%   Detailed explanation goes here

alf=0.01; % coef de invatare
q1=q(1);
q2=q(2);
q3=q(3);
N=100000; % iteratii
n=1;
e=0.001; % eroare
x1=Des(q1,q2,q3,2);
dx=x-x1;
dX=norm(dx);
while and(n<N,dX>e)
      q1=q(1);
      q2=q(2);
      q3=q(3);
      J=[0.11*cos(q1)*sin(q2)-0.092*sin(q1)-0.11*cos(q2)*sin(q1)+0.11*cos(q3)*(cos(q1)*sin(q2)-cos(q2)*sin(q1)), 0.11*cos(q2)*sin(q1)-0.11*cos(q1)*sin(q2)-0.11*cos(q3)*(cos(q1)*sin(q2)-cos(q2)*sin(q1)), -011*sin(q3)*(cos(q1)*cos(q2)+sin(q1)*sin(q2)) ;...
          0.092*cos(q1)+0.11*sin(q2)-0.11*cos(q2)*sin(q1)+0.11*cos(q3)*(cos(q1)*cos(q2)-sin(q2)*sin(q1)),                         0.11*cos(q2)*sin(q1)-0.11*cos(q1)*sin(q2)+0.11*cos(q3)*(cos(q1)*cos(q2)-sin(q2)*sin(q1)),                                                         0.11*sin(q3)*(cos(q1)*sin(q2)+sin(q1)*cos(q2));...
          0,                                                                                                                               0,                                                               -0.11*cos(q3)];
      if det(J)==0
          error ('singularitate')
      else
      end
      %q=q+alf*inv(J)*dx(2:3,1);
      %q1=q(1);
      %q2=q(2);
      %q3=q(3);
      %x1=Des(q1,q2,q3,2);
      %dx=x-x1;
      %X=norm(dx);
      %n=n+1;
end
dX
n
end


