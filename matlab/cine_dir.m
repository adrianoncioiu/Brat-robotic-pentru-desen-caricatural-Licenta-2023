function [V] = cine_dir(q,dq,timp,flag)
%Functia calculeza cinematica directa q->v
% Date de intrare q,dq (1xn) [rad]
%                 timpul (1xn) [s]
%                 flag==1 desen
% Date de iesire V=[v;w] (6xn)


n=length(q(1,:));
V=zeros(6,n);
for i=1:n
    q1=q(1,i);
    q2=q(2,i);
    q3=q(1,i);
    dq1=dq(1,i);
    dq2=dq(2,i);
    dq3=dq(1,i);
    J=[0.11*cos(q1)*sin(q2)-0.092*sin(q1)-0.11*cos(q2)*sin(q1)+0.11*cos(q3)*(cos(q1)*sin(q2)-cos(q2)*sin(q1)), 0.11*cos(q2)*sin(q1)-0.11*cos(q1)*sin(q2)-0.11*cos(q3)*(cos(q1)*sin(q2)-cos(q2)*sin(q1)), -011*sin(q3)*(cos(q1)*cos(q2)+sin(q1)*sin(q2)) ;...
                           0.092*cos(q1)+0.11*sin(q2)-0.11*cos(q2)*sin(q1)+0.11*cos(q3)*(cos(q1)*cos(q2)-sin(q2)*sin(q1)),                         0.11*cos(q2)*sin(q1)-0.11*cos(q1)*sin(q2)+0.11*cos(q3)*(cos(q1)*cos(q2)-sin(q2)*sin(q1)),                                                         0.11*sin(q3)*(cos(q1)*sin(q2)+sin(q1)*cos(q2));...
                           0,                        0,                                                         -0.11*cos(q3);...
                           0,                        0,                                                         -cos(q1)*sin(q2)-cos(q2)*sin(q1);...
                           0,                        0,                                                         cos(q1)*cos(q2)-sin(q1)*sin(q2);...
                           1,                        1,                                                         0];
    V(:,i)=J*[dq1;dq2;dq3];
end
 if flag==1
     figure
     hold
     grid
     plot(timp,V(1,:),'Color','r','LineWidth',2)
     plot(timp,V(2,:),'Color','g','LineWidth',2)
     plot(timp,V(3,:),'Color','b','LineWidth',2)
     legend('vx','vy','vz')
     xlabel 'timp [s]'
     ylabel 'viteze liniare [m/s]'
     
     figure
     hold
     grid
     plot(timp,V(4,:),'Color','r','LineWidth',2)
     plot(timp,V(5,:),'Color','g','LineWidth',2)
     plot(timp,V(6,:),'Color','b','LineWidth',2)
     legend('wx','wy','wz')
     xlabel 'timp [s]'
     ylabel 'viteze unghiulare[rad/s]'
 else
 end

end