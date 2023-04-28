% Definirea simbolic? a matricelor
syms cq1 cq2 cq3 cq4 cq5 cq6 a b c d e sq1 sq2 sq3 sq4 sq5 sq6 tx
matrice1 = [cq1*cq5-sq5*(cq4*(cq3*sq1*sq2-sq1*sq2*sq3)-sq4*(cq3*sq1*sq2+sq1*sq2*sq3)) sq6*(cq4*(cq3*sq1*sq2+sq1*sq2*sq3)+sq4*(cq3*sq1*sq2-sq1*sq2*sq3))-cq6*(cq1*sq5+cq5*(cq4*(cq3*sq1*sq2-sq1*sq2*sq3)-sq4*(cq3*sq1*sq2+sq1*sq2*sq3))) cq6*(cq4*(cq3*sq1*sq2+sq1*sq2*sq3)+sq4*(cq3*sq1*sq2-sq1*sq2*sq3))+sq6*(cq1*sq5+cq5*(cq4*(cq3*sq1*sq2-sq1*sq2*sq3)-sq4*(cq3*sq1*sq2+sq1*sq2*sq3))) (43*sq1*sq2)/100-(27*cq1)/200+(cq4*(cq3*sq1*sq2+sq1*sq2*sq3))/10+(sq4*(cq3*sq1*sq2-sq1*sq2*sq3))/10+(19*cq3*sq1*sq2)/50+(19*sq1*sq2*sq3)/50; cq5*sq1-sq5*(sq4*(cq1*cq2*cq3+cq1*cq3*sq2)-cq4*(cq1*cq2*cq3-cq1*sq2*sq3)) -cq6*(sq1*sq5+cq5*(sq4*(cq1*cq2*cq3+cq1*cq3*sq2)-cq4*(cq1*cq2*cq3-cq1*sq2*sq3)))-sq6*(cq4*(cq1*cq2*sq3+cq1*cq3*sq2)+sq4*(cq1*cq2*cq3-cq1*sq2*sq3)) sq6*(sq1*sq5+cq5*(sq4*(cq1*cq2*cq3+cq1*cq3*sq2)-cq4*(cq1*cq2*cq3-cq1*sq2*sq3)))-cq6*(cq4*(cq1*cq2*sq3+cq1*cq3*sq2)+sq4*(cq1*cq2*cq3-cq1*sq2*sq3)) -(27*sq1)/200-(43*cq1*sq2)/100-(cq4*(cq1*cq2*sq3+cq1*cq3*sq2))/10-(sq4*(cq1*cq2*cq3-cq1*sq2*sq3))/10-(19*cq1*cq2*sq3)/50-(19*cq1*cq3*sq2)/50; sq5*(sq4*(cq2*cq3-sq2*sq3)+cq2*cq4*sq3) sq6*(cq4*(cq2*cq3-sq2*sq3)-cq2*cq3*sq4)+cq5*cq6*(sq4*(cq2*cq3-sq2*sq3)+cq2*cq4*sq3) cq6*(cq4*(cq2*cq3-sq2*sq3)-cq2*cq3*sq4)-cq5*sq6*(sq4*(cq2*cq3-sq2*sq3)+cq2*cq4*sq3) (43*cq2)/100+(19*cq2*cq3)/50-(19*sq2*sq3)/50+(cq4*(cq2*cq3-sq2*sq3))/10-(cq2*cq3*sq4)/10; 0 0 0 1];
matrice2 = [1 0 0 tx; 0 1 0 0; 0 0 1 0; 0 0 0 1 ];

% Verific?m dac? matricele pot fi înmul?ite
[nr_linii1, nr_coloane1] = size(matrice1);
[nr_linii2, nr_coloane2] = size(matrice2);
if nr_coloane1 ~= nr_linii2
    error('Num?rul de coloane al primei matrice trebuie s? fie egal cu num?rul de linii al celei de-a doua matrice.');
end

% Inmultirea matricelor
rezultat = matrice1 * matrice2;

% Afi?area rezultatului
disp('Rezultatul înmul?irii este:');
disp(rezultat);