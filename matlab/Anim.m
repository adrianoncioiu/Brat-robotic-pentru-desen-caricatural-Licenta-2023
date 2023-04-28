function Anim(Q1,Q2,Q3, flag)
%Functia animeaza configuratia structurii
% Date de intrare: valoarea coordonatelor generalizate Q1,Q2, Q3 [rad] nx1
%                 flag==1->deseneaza si traiectori flag==2 doar traject
    n=length(Q1);


    if flag==1
        figure 
        hold
        grid
        
        for i=1:n
            cla
            Xe(:,i)=Des(Q1(i),Q2(i),Q3(i),2);
            pause(.01)
            xlabel 'x'
            ylabel 'y'
            zlabel 'z' 
            axis([-0,25,0.25,-0.25,0.25,-0.25,0.25])
            view (45,45)
        end
        plot3(Xe(1,:),Xe(2,:),Xe(3,:),'LineStyle','-.')
    elseif flag==2
         for i=1:n
            Xe(:,i)=Des(Q1(i),Q2(i),Q3(i),3);
         end
        plot3(Xe(1,:),Xe(2,:),Xe(3,:),'LineStyle','-.')
        figure
        comet(Xe(2,:),Xe(3,:))
        xlabel 'y'
        ylabel 'z'
        grid
        axis equal
    else
    end
end


