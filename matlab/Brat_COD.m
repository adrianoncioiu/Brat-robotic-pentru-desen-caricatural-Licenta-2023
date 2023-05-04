%% Simularea si modelare Brat
clear
clc
% articulatiile de rotatie sunt in acest exemplu Rz,Rz, Ry 

%% Dezvoltarea 1
Xe=Des(0,0,0,1);

%% animatie Traiectorie aleatorie structura dupa Q dat mai jos
n = 50;
%Aceste valori de unghiuri genereaza o miscare a bratului astfel incat sa atinga trei puncte diferite intr-un plan orizontal:

%In pozitia initiala, bratul va fi extins si orizontal, astfel incat axa z1 va fi paralela cu axa OX si axa z2 paralela cu axa OY.
%Apoi, bratul se va ridica la 45 de grade fata de planul orizontal prin rotatia in jurul axei z1.
%Urmeaza o rotatie de 180 de grade in jurul axei z2, astfel incat bratul va fi intors cu baza in sus.
%In final, bratul se va roti cu 45 de grade in jurul axei y astfel incat varful bratului sa fie orientat catre punctul de coordonate (0, 1, 0) din spatiu.

% Unghiurile generalizate Q1 
Q1_1 = linspace(0, pi/2, n);
Q1_2 = linspace(-pi/3,-pi/3,n);
Q1_3 = linspace(0, pi/2, n);
Q1 = [Q1_1, Q1_2, Q1_3];

% Unghiurile generalizate Q2 
Q2_1 = linspace(0, pi/2, n);
Q2_2 = linspace(-pi/3,-pi/3,n);
Q2_3 = linspace(0, pi/2, n);
Q2 = [Q2_1, Q2_2, Q2_3];

% Unghiurile generalizate Q3 
Q3_1 = linspace(0, pi/2, n);
Q3_2 = linspace(-pi/3,-pi/3,n);
Q3_3 = linspace(0, pi/2, n);
Q3 = [Q3_1, Q3_2, Q3_3];
Anim(Q1,Q2,Q3,2);

  
%% Modelul cinematic
% Traiectoriile dorite
% Sunt in spatiul articular stiu val I, F ma intereseaza functiile
% interpolate
q=[0,pi;...
   0,pi;
   0,pi;]; % [q1;q2;q3]
% Durata
T=60; %[s]
% discret
n=70;
% flag==1 cu desen
flag=1;
[Traiectorii,timp] = traiect(q,T,n,flag);
%% Cinematica directa
% Transformarea din spatiul articular in cel cartezian pt viteze
q=Traiectorii(1:2,:);
dq=Traiectorii(3:4,:);
V=cine_dir(q,dq,timp,1);
%% Geometria inversa 
% Varianta in care punctul de final este in volumul de lucru
clc
clear
q11=0; q21=0;
q12=-pi; q22=pi/2;
q31=0; q32=pi/4;


q_initial=[q11;q21;q31];
q_final_impus=[q12;q22;q32];
x1=Des(q11,q21,q31, 1);
title('config initial')

x_final_impus=Des(q12,q22,q32, 1);% ma asigur ca sunt in volumul de lucru
title('config final impus')

%q_final=geom_inv(q_initial,x_final_impus);

%x_final_calculat=desen(q_final(1),q_final(2),q_final(3),1);
%eroarea_pozitionare=norm(x_final_calculat-x_final_impus)
%title(['config final calculat   ','eroarea = ',num2str(eroarea_pozitionare)])



%% PrototipVirtual

% impunem o traiectorie limita in spatiul articular
q=[-pi/2,-pi;...
   -pi/2,-pi]; % [q1;q2]
% Durata
T=5; %[s]
% discret
n=1000;
% flag==1 cu desen
flag=1;
[Traiectorii,timp] = traiect(q,T,n,flag);% produce si baze de date

%aflam vitezele maxime in [rpm]....Dynamixel ax12-a
vitezele_maxime(1,1)=30*max(abs(Traiectorii(3,:)))/pi;
vitezele_maxime(2,1)=30*max(abs(Traiectorii(4,:)))/pi;

% Simularea pentru traiectoriile impuse
out=sim("Robot.slx");
%
%aflam vitezele maxime in [mNm]....Dynamixel ax12-a
momente_maxime(1,1)=1000*max(abs(out.T1_out.Data));
momente_maxime(2,1)=1000*max(abs(out.T2_out.Data));

figure
hold
plot(out.T1_out.Time,1000*out.T1_out.Data,'LineWidth',2,'Color','b')
plot(out.T2_out.Time,1000*out.T2_out.Data,'LineWidth',2,'Color','r')
grid
xlabel 'Timp [s]'
ylabel 'Momentul motor [mNm]'
legend('T1','T2')
title 'Momentele motoare'

figure
hold
plot(out.T1_out.Time,out.T1_out.Data.*out.dq1_out.Data,'LineWidth',2,'Color','b')
plot(out.T2_out.Time,out.T2_out.Data.*out.dq2_out.Data,'LineWidth',2,'Color','r')
grid
xlabel 'Timp [s]'
ylabel 'Puterea [w]'
legend('P1','P2')
title 'Puterea motoare'
%
figure
hold
fill([0,5,5,0],[0,0,5,5],'g')
plot(abs(out.T1_out.Data),abs(30*out.dq1_out.Data/pi),'LineWidth',2,'Color','b')
plot(abs(out.T2_out.Data),abs(30*out.dq2_out.Data/pi),'LineWidth',2,'Color','r')
grid
xlabel 'Momentul [Nm]'
ylabel 'Turatia [rpm]'
legend('Zona recomandata','Cupla1','Cupla2')
title 'Punctul de functionare'
