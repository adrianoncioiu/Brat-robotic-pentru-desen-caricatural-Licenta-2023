syms q1 q2 q3

% Definirea expresiei
expr =0.092*cos(q1)+0.11*cos(q1)*cos(q2)+(0.11*sin(q1)*sin(q2)+0.11*cos(q3)*(cos(q1)*cos(q2)+sin(q1)*sin(q2)));

% Calcularea derivatei par?iale dup? q1
dexprdq1 = diff(expr, q1);

% Calcularea derivatei par?iale dup? q2
dexprdq2 = diff(expr, q2);

% Calcularea derivatei par?iale dup? q3
dexprdq3 = diff(expr, q3);

% Afi?area rezultatelor
disp('Derivata par?ial? a expresiei dup? q1 este:');
disp(dexprdq1);

disp('Derivata par?ial? a expresiei dup? q2 este:');
disp(dexprdq2);

disp('Derivata par?ial? a expresiei dup? q3 este:');
disp(dexprdq3);