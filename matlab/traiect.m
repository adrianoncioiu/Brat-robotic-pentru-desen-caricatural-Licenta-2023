function [Traiectorii,timp] = traiect(q,T,n,flag)
%Functia calculeaza traiectoriile dorite din spatiul articular
% Date de intrare: q (2x2) ungiurile de inceput si sfarsit
%                  [q1I,q1F;q2I,q2F;q3I,q3F]; [rad]
%                  T durata [s]
%                  n discretizarea intervalului
%                  Flag==1 se deseneaza
% Date de iesire: Traiectorii (6xn)[Q;dQ;ddQ] [rad] (Q=[q1;q2;q3],....)
%                 timp (1xn) discretizarea intervalului de timp

           
           timp=linspace(0,T,n);
           Q=zeros(3,n);
           dQ=zeros(3,n);
           ddQ=zeros(3,n);
           for i=1:2
               a0=q(i,1);
               a1=0;
               a2=3*(q(i,2)-q(i,1))/T^2;
               a3=-2*(q(i,2)-q(i,1))/T^3;
               
               Q(i,:)=polyval([a3,a2,a1,a0],timp);
               dQ(i,:)=polyval(polyder([a3,a2,a1,a0]),timp);
               ddQ(i,:)=polyval(polyder(polyder([a3,a2,a1,a0])),timp);
               
           end
           if flag==1
               for i=1:2
                   figure
                   subplot(3,1,1)
                   plot(timp,Q(i,:),'b','linewidth',2)
                   xlabel 'timp [s]'
                   ylabel (strcat('q',mat2str(i),'[rad]'))
                   
                   subplot(3,1,2)
                   plot(timp,dQ(i,:),'b','linewidth',2)
                   xlabel 'timp [s]'
                   ylabel (strcat('dq',mat2str(i),'[rad/s]'))
                   
                   subplot(3,1,3)
                   plot(timp,ddQ(i,:),'b','linewidth',2)
                   xlabel 'timp [s]'
                   ylabel (strcat('ddq',mat2str(i),'[rad/s^2]'))
               end
           else
           end
           Traiectorii=[Q;dQ;ddQ];
     
           Q_dor1=[timp;Q(1,:)];
           save Poz_1.mat Q_dor1
           dQ_dor1=[timp;dQ(1,:)];
           save Vit_1.mat dQ_dor1
           ddQ_dor1=[timp;ddQ(1,:)];
           save Acc_1.mat ddQ_dor1

           Q_dor2=[timp;Q(2,:)];
           save Poz_2.mat Q_dor2
           dQ_dor2=[timp;dQ(2,:)];
           save Vit_2.mat dQ_dor2
           ddQ_dor2=[timp;ddQ(2,:)];
           save Acc_2.mat ddQ_dor2

           Q_dor3=[timp;Q(3,:)];
           save Poz_3.mat Q_dor3
           dQ_dor3=[timp;dQ(3,:)];
           save Vit_3.mat dQ_dor3
           ddQ_dor3=[timp;ddQ(3,:)];
           save Acc_3.mat ddQ_dor3
           

end